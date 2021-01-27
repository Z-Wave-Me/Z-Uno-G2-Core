#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"

#define PWM_TIMER						TIMER1
#define PWM_TIMER_CLOCK					cmuClock_TIMER1
#define PWM_HGZ							0x1EA
#define PWM_DISABLED					0x0
#define PWM_ENABLED						0xFF
#define PWM_PIN_DISABLED				0x0
#define PWM_PIN_ENABLED					0x1
#define PWM_PIN_PULSE					0x2
#define PWM_TIMER_LOCK					gSyncTIMER1
#define PWM_TIMER_LOCK_KEY				gTonePwm.keyPwm
#define PWM_TIMER_CC_COUNT				(sizeof(PWM_TIMER->CC) / sizeof(TIMER_CC_TypeDef))
#define PWM_OUT_CLOSE					0xFF

#define TONE_DISABLED					0x0
#define TONE_CHANNEL					0x0
#define TONE_TIMER						TIMER0
#define TONE_TIMER_CLOCK				cmuClock_TIMER0
#define TONE_TIMER_LOCK					gSyncTIMER0
#define TONE_TIMER_LOCK_KEY				gTonePwm.keyTone

#define TONE_PWM_ENTER()				zunoSyncLockWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)
#define TONE_PWM_EXIT()					zunoSyncReleseWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)

#if MAX_ZUNO_PWMS != 4
	#error "Error pin pwm!"
#endif

typedef struct						ZunoTonePwm_s
{
	uint16_t						tone_freq;
	uint8_t							tone_pin;
	uint8_t							keyTone;
	uint8_t							keyPwm;
}									ZunoTonePwm_t;

static ZunoSync_t gSyncTonePwm = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterTone);
static ZunoTonePwm_t gTonePwm = {0, 0, 0, 0};
static volatile uint8_t glpKey = true;

static void _noTone(uint8_t pin);

static uint8_t _findPWMChannelBusy(uint8_t location) {
	size_t			tempos;
	uint8_t			channel;

	location = (location + 32 - 0);
	tempos = PWM_TIMER->ROUTELOC0;
	channel = 0;
	while (channel < PWM_TIMER_CC_COUNT) {
		if ((tempos & _TIMER_ROUTELOC0_CC0LOC_MASK) == (location & _TIMER_ROUTELOC0_CC0LOC_MASK))
			return (channel);
		location--;
		channel++;
		tempos = tempos >> 8;
	}
	return (INVALID_PIN_INDEX);
}

static uint8_t _findPWMChannelSpace(void) {
	size_t			tempos;
	uint8_t			channel;

	tempos = PWM_TIMER->ROUTELOC0;
	channel = 0;
	while (channel < PWM_TIMER_CC_COUNT) {
		if ((tempos & _TIMER_ROUTELOC0_CC0LOC_MASK) == 0)
			return (channel);
		channel++;
		tempos = tempos >> 8;
	}
	return (INVALID_PIN_INDEX);
}

static uint8_t _getPrescale(size_t freq) {
	uint8_t					prescale;

	prescale = timerPrescale1;
	while (prescale < timerPrescale1024 && (freq / (1 << prescale)) > 0xFFFF) 
		prescale++;
	return (prescale);
}

#include "Libft.h"

static uint8_t _analogWrite(uint8_t pin, uint8_t value) {
	TIMER_TypeDef				*timer;
	uint8_t						channel;
	size_t						location;

	location = getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), pin);
	channel = _findPWMChannelBusy(location);
	timer = PWM_TIMER;
	switch (value) {
		case PWM_DISABLED:// switch off the led if it was enabled already
			_noTone(pin);
			return (PWM_OUT_CLOSE);
		case PWM_ENABLED:
			_noTone(pin);
			if(channel != INVALID_PIN_INDEX) {
				timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (channel << 3));
				timer->ROUTEPEN &= ~(1UL << channel);//disable CC
			}
			pinMode(pin, OUTPUT_UP);
			return (true);
	}
	if(channel == INVALID_PIN_INDEX) {
		channel = _findPWMChannelSpace();
		if(channel == INVALID_PIN_INDEX)
			return (false);
		_noTone(pin);
		timer->ROUTELOC0 |= (((location + 32 - channel) & _TIMER_ROUTELOC0_CC0LOC_MASK) << (channel << 3));
		timer->ROUTEPEN |= (1UL << channel);//enabled CC
		pinMode(pin, OUTPUT);// enable the output
	}
	TIMER_CompareBufSet(timer, channel, TIMER_TopGet(timer) * value / PWM_ENABLED);
	return (true);
}

static ZunoError_t _initPwm(size_t param) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;
	size_t						freq;
	size_t						channel;

	CMU_ClockEnable(PWM_TIMER_CLOCK, true);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = timerPrescale2;
	freq = CMU_ClockFreqGet(PWM_TIMER_CLOCK) / (1 << timerInit.prescale) / PWM_HGZ;// PWM_HGZ - required frequency //0x25317C0
	timer = PWM_TIMER;
	timer->ROUTELOC0 = _TIMER_ROUTELOC0_RESETVALUE;
	timer->ROUTEPEN = _TIMER_ROUTEPEN_RESETVALUE;//disable CC
	TIMER_TopSet(timer, freq);
	TIMER_Init(timer, &timerInit);
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModePWM;
	timerCCInit.cmoa = timerOutputActionToggle;
	channel = 0;
	while (channel < PWM_TIMER_CC_COUNT)
		TIMER_InitCC(timer, channel++, &timerCCInit);
	return (ZunoErrorOk);
	(void)param;
}
static uint8_t _analogWriteDisable(uint8_t pin) {
	size_t					channel;
	TIMER_TypeDef			*timer;

	channel = _findPWMChannelBusy(getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), pin));
	if(channel != INVALID_PIN_INDEX) {
		timer = PWM_TIMER;
		timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (channel << 3));
		timer->ROUTEPEN &= ~(1UL << channel);//disable CC
		if (timer->ROUTEPEN == _TIMER_ROUTEPEN_RESETVALUE) {
			TIMER_Reset(timer);
			zunoSyncClose(&PWM_TIMER_LOCK, SyncMasterPwm, 0, 0, &PWM_TIMER_LOCK_KEY);
		}
	}
	pinMode(pin, OUTPUT_DOWN);// Switch off this pin anyway
	return (true);
}

bool analogWrite(uint8_t pin, word value) {
	uint8_t			out;

	if (pin > ZUNO_PIN_LAST_INDEX)
		return (false);
	TONE_PWM_ENTER();
	if (zunoSyncOpen(&PWM_TIMER_LOCK, SyncMasterPwm, _initPwm, 0, &PWM_TIMER_LOCK_KEY) == ZunoErrorOk) {
		out = _analogWrite(pin, ((value > 0xFF) ? 0xFF : value));
		zunoSyncReleseWrite(&PWM_TIMER_LOCK, SyncMasterPwm, &PWM_TIMER_LOCK_KEY);
		if (out == PWM_OUT_CLOSE)
			out = _analogWriteDisable(pin);//disable pwm
	}
	else
		out = false;
	TONE_PWM_EXIT();
	return (out);
}

static ZunoError_t _deInitTone(size_t param) {
	ZunoTonePwm_t			*lp;
	size_t					pin;

	pin = param;
	lp = &gTonePwm;
	if (lp->tone_pin != pin)
		return (ZunoErrorInvalidPin);
	lp->tone_pin = INVALID_PIN_INDEX;
	lp->tone_freq = 0;
	TONE_TIMER->ROUTEPEN = _TIMER_ROUTEPEN_RESETVALUE;//disable CC
	TIMER_Reset(TONE_TIMER);
	pinMode(pin, OUTPUT_DOWN);// Switch off this pin anyway
	return (ZunoErrorOk);
}

static void _noTone(uint8_t pin) {
	zunoSyncClose(&TONE_TIMER_LOCK, SyncMasterTone, _deInitTone, pin, &TONE_TIMER_LOCK_KEY);
}

void noTone(uint8_t pin) {
	if (pin > ZUNO_PIN_LAST_INDEX)
		return ;
	TONE_PWM_ENTER();
	_noTone(pin);
	TONE_PWM_EXIT();
}

static ZunoError_t _tone(uint8_t pin, uint16_t freq) {
	TIMER_TypeDef				*timer;
	ZunoTonePwm_t				*lp;
	size_t						tone_freq_set;
	size_t						prescale;

	lp = &gTonePwm;
	timer = TONE_TIMER;
	if (lp->tone_pin == pin) {
		if (lp->tone_freq == freq)
			return (ZunoErrorOk);
	}
	else {
		lp->tone_pin = pin;
		timer->ROUTELOC0 = getLocationTimer0AndTimer1Chanell(pin, TONE_CHANNEL);
		timer->ROUTEPEN = (1UL << TONE_CHANNEL);
		pinMode(pin, OUTPUT);// enable the output
	}
	lp->tone_freq = freq;
	tone_freq_set = CMU_ClockFreqGet(TONE_TIMER_CLOCK) / 2 / freq;//0x25317C0 get the frequency for one hertz
	prescale = _getPrescale(tone_freq_set);
	TIMER_TopSet(timer, tone_freq_set / (1 << prescale));
	timer->CTRL = (timer->CTRL & (_TIMER_CTRL_PRESC_MASK << _TIMER_CTRL_PRESC_SHIFT)) | (prescale << _TIMER_CTRL_PRESC_SHIFT);
	return (ZunoErrorOk);
}

static ZunoError_t _initTone(size_t param) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;

	CMU_ClockEnable(TONE_TIMER_CLOCK, true);
	gTonePwm.tone_pin = INVALID_PIN_INDEX;
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModeCompare;
	timerCCInit.cmoa = timerOutputActionToggle;
	timer = TONE_TIMER;
	TIMER_InitCC(timer, TONE_CHANNEL, &timerCCInit);
	TIMER_CompareBufSet(timer, TONE_CHANNEL, 1);
	timerInit = TIMER_INIT_DEFAULT;
	TIMER_Init(timer, &timerInit);
	return (ZunoErrorOk);
	(void)param;
}

ZunoError_t tone(uint8_t pin, uint16_t freq) {
	ZunoError_t					ret;

	if (pin > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	TONE_PWM_ENTER();
	_analogWriteDisable(pin);//disable pwm
	if (freq == 0) {
		_noTone(pin);
		ret = ZunoErrorOk;
	}
	else if ((ret = zunoSyncOpen(&TONE_TIMER_LOCK, SyncMasterTone, _initTone, 0, &TONE_TIMER_LOCK_KEY)) == ZunoErrorOk) {
		ret = _tone(pin, freq);
		zunoSyncReleseWrite(&TONE_TIMER_LOCK, SyncMasterTone, &TONE_TIMER_LOCK_KEY);
	}
	TONE_PWM_EXIT();
	return (ret);
}

ZunoError_t toneDelayed(uint8_t pin, uint16_t freq, uint16_t duration) {
	ZunoError_t					ret;

	if ((ret = tone(pin, freq)) != ZunoErrorOk)
		return (ret);
	delay(duration);
	noTone(pin);
	return (ZunoErrorOk);
}

