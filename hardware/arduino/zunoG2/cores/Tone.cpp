#include "Arduino.h"
#include "em_device.h"
#include "em_timer.h"

typedef struct						ZunoTonePwm_s
{
	uint8_t							keyPwm;
}									ZunoTonePwm_t;

static ZunoSync_t gSyncTonePwm = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterTone);
static volatile uint8_t glpKey = true;

#define TONE_PWM_ENTER()				zunoSyncLockWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)
#define TONE_PWM_EXIT()					zunoSyncReleseWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)

// MULTI_CHIP
#if defined(_TIMER_ROUTELOC0_CC0LOC_MASK)
static ZunoTonePwm_t gTonePwm = {0};
static uint32_t _pwm_freq = PWM_FREQ_DEFAULT;
static uint8_t _pwm_resolution = 8;

#define PWM_TIMER						TIMER1
#define PWM_TIMER_CLOCK					cmuClock_TIMER1

#define PWM_HGZ							PWM_FREQ_MIN
#define PWM_DISABLED					0x0
#define PWM_PIN_DISABLED				0x0
#define PWM_PIN_ENABLED					0x1
#define PWM_PIN_PULSE					0x2
#define PWM_TIMER_LOCK					gSyncTIMER1
#define PWM_TIMER_LOCK_KEY				gTonePwm.keyPwm
#define PWM_TIMER_CC_COUNT				(sizeof(PWM_TIMER->CC) / sizeof(TIMER_CC_TypeDef))
#define PWM_OUT_CLOSE					0xFF

#if MAX_ZUNO_PWMS != 4
	#error "Error pin pwm!"
#endif


static void _noTone(uint8_t pin);

static uint8_t _findPWMChannelBusy(uint8_t location) {
	size_t			routeopen;
	size_t			routeloco;
	size_t			channel;

	routeloco = PWM_TIMER->ROUTELOC0;
	routeopen = PWM_TIMER->ROUTEPEN;
	channel = 0;
	while (channel < PWM_TIMER_CC_COUNT) {
		if ((routeopen & (0x1 << channel)) != 0)
			if ((routeloco & _TIMER_ROUTELOC0_CC0LOC_MASK) == ((location - channel) & _TIMER_ROUTELOC0_CC0LOC_MASK))
				return (channel);
		channel++;
		routeloco = routeloco >> 8;
	}
	return (INVALID_PIN_INDEX);
}

static uint8_t _findPWMChannelSpace(void) {
	size_t			routeopen;
	size_t			channel;

	routeopen = PWM_TIMER->ROUTEPEN;
	channel = 0;
	while (channel < PWM_TIMER_CC_COUNT) {
		if ((routeopen & (0x1 << channel)) == 0)
			return (channel);
		channel++;
	}
	return (INVALID_PIN_INDEX);
}

static uint8_t _analogWrite(uint8_t pin, uint16_t value) {
	TIMER_TypeDef				*timer;
	uint8_t						channel;
	size_t						location;
	uint32_t					pwm_enabled;

	location = getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), pin) + 32;
	channel = _findPWMChannelBusy(location);
	timer = PWM_TIMER;
	pwm_enabled = 0xFFFFFFFF >> ((sizeof(pwm_enabled) * 0x8) - _pwm_resolution);
	if (value == PWM_DISABLED) {
		_noTone(pin);
		return (PWM_OUT_CLOSE);
	}
	else if (value >= pwm_enabled) {
		_noTone(pin);
		if(channel != INVALID_PIN_INDEX)
			timer->ROUTEPEN &= ~(1UL << channel);//disable CC
		pinMode(pin, OUTPUT_UP);
		return (true);
	}
	if(channel == INVALID_PIN_INDEX) {
		channel = _findPWMChannelSpace();
		if(channel == INVALID_PIN_INDEX)
			return (false);
		_noTone(pin);
		timer->ROUTELOC0 = (timer->ROUTELOC0 & ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (channel << 3))) | (((location - channel) & _TIMER_ROUTELOC0_CC0LOC_MASK) << (channel << 3));
		timer->ROUTEPEN |= (1UL << channel);//enabled CC
		pinMode(pin, OUTPUT);// enable the output
	}
	TIMER_CompareBufSet(timer, channel, TIMER_TopGet(timer) * value / pwm_enabled);
	return (true);
}

static ZunoError_t _initPwm(size_t param) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;
	size_t						freq;
	size_t						channel;
	TIMER_Prescale_TypeDef		timer_prescale;

	CMU_ClockEnable(PWM_TIMER_CLOCK, true);
	timerInit = TIMER_INIT_DEFAULT;
	freq = CMU_ClockFreqGet(PWM_TIMER_CLOCK);
	timer_prescale = timerPrescale1;
	while ((freq / _pwm_freq / (1 << timer_prescale)) > 0xFFFF)
		timer_prescale = (TIMER_Prescale_TypeDef)(timer_prescale + 1);
	timerInit.prescale = timer_prescale;
	freq /=  (1 << timer_prescale);
	freq /= _pwm_freq;
	timer = PWM_TIMER;
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
		out = _analogWrite(pin, value);
		zunoSyncReleseWrite(&PWM_TIMER_LOCK, SyncMasterPwm, &PWM_TIMER_LOCK_KEY);
		if (out == PWM_OUT_CLOSE)
			out = _analogWriteDisable(pin);//disable pwm
	}
	else
		out = false;
	TONE_PWM_EXIT();
	return (out);
}

void analogWriteResolution(uint8_t bits){
	if (bits > 16)
		bits = 16;
	_pwm_resolution = bits;
}

void analogWriteFrequency(uint32_t freq){
	if ((freq >= PWM_FREQ_MIN) && (freq <= PWM_FREQ_MAX))
		_pwm_freq = freq;
}
#else
static uint8_t _analogWriteDisable(uint8_t pin) {
	return (pin);
}
#endif

#define TONE_CHANNEL					0x0

#if TIMER_COUNT == 0x2
#define TONE_TIMER_NUMBER_0				TIMER0
#define TONE_TIMER_CLOCK_NUMBER_0		cmuClock_TIMER0
#define TONE_TIMER_ROUTEPEN_NUMBER_0	TIMER_ROUTEPEN_CC0PEN
#define TONE_TIMER_ROUTEPEN_RESET		_TIMER_ROUTEPEN_RESETVALUE
#endif
#if TIMER_COUNT == 0x5
#define TONE_TIMER_NUMBER_0				TIMER2
#define TONE_TIMER_NUMBER_1				TIMER3
#define TONE_TIMER_CLOCK_NUMBER_0		cmuClock_TIMER2
#define TONE_TIMER_CLOCK_NUMBER_1		cmuClock_TIMER3
#define TONE_TIMER_FD_NUMBER_0			2
#define TONE_TIMER_FD_NUMBER_1			3
#define TONE_TIMER_ROUTEPEN_NUMBER_0	GPIO_TIMER_ROUTEEN_CC0PEN
#define TONE_TIMER_ROUTEPEN_NUMBER_1	TONE_TIMER_ROUTEPEN_NUMBER_0
#define TONE_TIMER_ROUTEPEN_RESET		_GPIO_TIMER_ROUTEEN_RESETVALUE
#endif

static uint8_t _tone_pin = INVALID_PIN_INDEX;
static uint16_t _tone_freq = 0x0;

static TIMER_TypeDef *_tone_GetTimer(uint8_t pin) {
	#if defined(TONE_TIMER_NUMBER_1)
	uint8_t								port;
	#endif

	#if defined(TONE_TIMER_NUMBER_1)
	port = getRealPort(pin);
	if (port == gpioPortA || port == gpioPortB)
		return (TONE_TIMER_NUMBER_0);
	else
		return (TONE_TIMER_NUMBER_1);
	#else
	return (TONE_TIMER_NUMBER_0);
	(void)pin;
	#endif
}

static void _tone_CMU_ClockEnable(bool enable) {
	#if defined(TONE_TIMER_NUMBER_1)
	CMU_ClockEnable(cmuClock_TIMER2, enable);
	CMU_ClockEnable(cmuClock_TIMER3, enable);
	#else
	CMU_ClockEnable(TONE_TIMER_CLOCK_NUMBER_0, enable);
	#endif
}

static uint32_t _tone_CMU_ClockFreqGet(uint8_t pin) {
	uint32_t							freq;
	#if defined(TONE_TIMER_NUMBER_1)
	uint8_t								port;
	#endif

	#if defined(TONE_TIMER_NUMBER_1)
	port = getRealPort(pin);
	if (port == gpioPortA || port == gpioPortB)
		freq = CMU_ClockFreqGet(TONE_TIMER_CLOCK_NUMBER_0);
	else
		freq = CMU_ClockFreqGet(TONE_TIMER_CLOCK_NUMBER_1);
	#else
	freq = CMU_ClockFreqGet(TONE_TIMER_CLOCK_NUMBER_0);
	(void)pin;
	#endif
	return (freq);
}

static void _tone_NewPin(uint8_t pin, TIMER_TypeDef *timer_new) {
	#if defined(TONE_TIMER_NUMBER_1)
	TIMER_TypeDef						*timer;
	#endif

	if (pin == INVALID_PIN_INDEX)
		return ;
	#if defined(TONE_TIMER_NUMBER_1)
	timer = _tone_GetTimer(pin);
	if (timer_new != timer) {
		TIMER_Enable(timer, false);
		if (timer == TONE_TIMER_NUMBER_0)
			GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_0].ROUTEEN = TONE_TIMER_ROUTEPEN_RESET;//disable CC
		else
			GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_1].ROUTEEN = TONE_TIMER_ROUTEPEN_RESET;//disable CC
	}
	#else
	(void)timer_new;
	#endif
	pinMode(pin, DISABLED);// Switch off this pin anyway
}

static void _tone_Init(TIMER_TypeDef *timer) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;

	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(timer, &timerInit);
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModeCompare;
	timerCCInit.cmoa = timerOutputActionToggle;
	TIMER_InitCC(timer, TONE_CHANNEL, &timerCCInit);
	TIMER_CompareBufSet(timer, TONE_CHANNEL, 1);

}

static TIMER_Prescale_TypeDef _getPrescale(size_t freq) {
	uint8_t					i;

	i = 0x0;
	while (true) {
		if ((freq / (0x1 << i)) <= 0xFFFF)
			break ;
		i++;
		#if defined (_TIMER_CTRL_PRESC_MASK)
		if (i >= timerPrescale1024)
			break ;
		#endif
		#if defined (_TIMER_CFG_PRESC_MASK)
		if (((0x1 << i) - 0x1) >= timerPrescale1024)
			break ;
		#endif
	}
	#if defined (_TIMER_CTRL_PRESC_MASK)
	return ((TIMER_Prescale_TypeDef)i);
	#endif
	#if defined (_TIMER_CFG_PRESC_MASK)
	return ((TIMER_Prescale_TypeDef)((0x1 << i) - 0x1));
	#endif
}

static void _noTone(uint8_t pin) {
	if (_tone_pin != pin)
		return ;
	_tone_pin = INVALID_PIN_INDEX;
	_tone_freq = 0;
	#if defined(TONE_TIMER_NUMBER_1)
	TIMER_Reset(TONE_TIMER_NUMBER_0);
	TIMER_Reset(TONE_TIMER_NUMBER_1);
	GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_0].ROUTEEN = TONE_TIMER_ROUTEPEN_RESET;//disable CC
	GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_1].ROUTEEN = TONE_TIMER_ROUTEPEN_RESET;//disable CC
	#else
	TIMER_Reset(TONE_TIMER_NUMBER_0);
	TONE_TIMER_NUMBER_0->ROUTEPEN = TONE_TIMER_ROUTEPEN_RESET;
	#endif
	_tone_CMU_ClockEnable(false);
	pinMode(pin, DISABLED);// Switch off this pin anyway
	zunoPeripheryRelese(&gSyncVirtualTimer0, SyncMasterTone);
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
	size_t						tone_freq_set;
	TIMER_Prescale_TypeDef		prescale;
	uint8_t						pin_old;
	TIMER_Init_TypeDef			timerInit;
	#if defined(TONE_TIMER_NUMBER_1)
	uint8_t						real_pin;
	uint8_t						real_port;
	#endif

	if (_tone_pin == pin && _tone_freq == freq)
		return (ZunoErrorOk);
	timer = _tone_GetTimer(pin);
	TIMER_Enable(timer, false);
	if ((pin_old = _tone_pin) != pin) {
		_tone_NewPin(pin_old, timer);
		_tone_pin = pin;
		pinMode(pin, OUTPUT_DOWN);
		#if defined(TONE_TIMER_NUMBER_1)
		real_pin = getRealPin(pin);
		real_port = getRealPort(pin);
		if (timer == TONE_TIMER_NUMBER_0)
			GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_0].CC0ROUTE = (real_port << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (real_pin << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
		else
			GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_1].CC0ROUTE = (real_port << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (real_pin << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
		#else
		timer->ROUTELOC0 = getLocationTimer0AndTimer1Chanell(pin, TONE_CHANNEL);
		#endif
	}
	if (_tone_freq == freq) {
		TIMER_Enable(timer, true);
		return (ZunoErrorOk);
	}
	_tone_freq = freq;
	tone_freq_set = _tone_CMU_ClockFreqGet(pin) / 2 / freq;// get the frequency for one hertz
	prescale = _getPrescale(tone_freq_set);
	#if defined (_TIMER_CFG_PRESC_MASK)
	tone_freq_set = tone_freq_set / (prescale + 0x1);
	#endif
	#if defined (_TIMER_CTRL_PRESC_MASK)
	tone_freq_set = tone_freq_set / (0x1 << prescale);
	#endif
	TIMER_TopSet(timer, tone_freq_set);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = true;
	timerInit.prescale = prescale;
	TIMER_Init(timer, &timerInit);
	return (ZunoErrorOk);
}

static ZunoError_t _tone_pre(uint8_t pin, uint16_t freq) {
	ZunoError_t						ret;
	SyncPeripheryCaptureStatus_t	status;
	uint8_t							pin_old;

	if (pin > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	_analogWriteDisable(pin);//disable pwm
	if (freq == 0) {
		if ((pin_old = _tone_pin) != pin)
			_noTone(pin_old);
		pinMode(pin, OUTPUT_DOWN);
		ret = ZunoErrorOk;
	}
	else{
		if ((status = zunoPeripheryCapture(&gSyncVirtualTimer0, SyncMasterTone)) == SyncPeripheryCaptureStatusBad)
			ret = ZunoErrorNotInit;
		else {
			if (status == SyncPeripheryCaptureStatusOk) {
				_tone_CMU_ClockEnable(true);
				#if defined(TONE_TIMER_NUMBER_1)
				_tone_Init(TONE_TIMER_NUMBER_0);
				_tone_Init(TONE_TIMER_NUMBER_1);
				GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_0].ROUTEEN = TONE_TIMER_ROUTEPEN_NUMBER_0;
				GPIO->TIMERROUTE[TONE_TIMER_FD_NUMBER_1].ROUTEEN = TONE_TIMER_ROUTEPEN_NUMBER_0;
				#else
				_tone_Init(TONE_TIMER_NUMBER_0);
				TONE_TIMER_NUMBER_0->ROUTEPEN = TONE_TIMER_ROUTEPEN_NUMBER_0;
				#endif
			}
			ret = _tone(pin, freq);
		}
	}
	return (ret);
}

ZunoError_t tone(uint8_t pin, uint16_t freq, uint32_t duration) {
	ZunoError_t						ret;

	if ((ret = TONE_PWM_ENTER()) != ZunoErrorOk)
		return (ret);
	ret = _tone_pre(pin, freq);
	if (duration != 0x0 && ret == ZunoErrorOk) {
		delay(duration);
		_noTone(pin);
	}
	TONE_PWM_EXIT();
	return (ret);
}