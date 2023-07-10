#include "Arduino.h"
#include "em_device.h"
#include "em_timer.h"

static uint32_t _pwm_freq = PWM_FREQ_DEFAULT;
static ZunoSync_t gSyncTonePwm = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterTone);
static volatile uint8_t glpKey = true;

static uint8_t _pwm_resolution = 8;
static uint8_t _channel[MAX_ZUNO_PWMS];

#define TONE_PWM_ENTER()				zunoSyncLockWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)
#define TONE_PWM_EXIT()					zunoSyncReleseWrite(&gSyncTonePwm, SyncMasterTone, &glpKey)

#define PWM_HGZ							PWM_FREQ_MIN

#define PWM_TIMER_CCROUTE(ch)			(0x1 << ch)

#if TIMER_COUNT == 0x2
#define PWM_TIMER_NUMBER_0				TIMER1
#define PWM_TIMER_CLOCK_NUMBER_0		cmuClock_TIMER1
#define PWM_TIMER_CC_COUNT				(sizeof(PWM_TIMER_NUMBER_0->CC) / sizeof(PWM_TIMER_NUMBER_0->CC[0x0]))
#define PWM_TIMER_ROUTEPEN_RESET		_TIMER_ROUTEPEN_RESETVALUE
#endif
#if TIMER_COUNT == 0x5
#define PWM_TIMER_NUMBER_0				TIMER0
#define PWM_TIMER_NUMBER_1				TIMER1
#define PWM_TIMER_CLOCK_NUMBER_0		cmuClock_TIMER0
#define PWM_TIMER_CLOCK_NUMBER_1		cmuClock_TIMER1
#define PWM_TIMER_FD_NUMBER_0			0
#define PWM_TIMER_FD_NUMBER_1			1
#define PWM_TIMER_CC_COUNT				(sizeof(PWM_TIMER_NUMBER_0->CC) / sizeof(PWM_TIMER_NUMBER_0->CC[0x0]))
#define PWM_TIMER_ROUTEPEN_RESET		_GPIO_TIMER_ROUTEEN_RESETVALUE

#if _GPIO_TIMER_CC0ROUTE_PORT_SHIFT != _GPIO_TIMER_CC1ROUTE_PORT_SHIFT || _GPIO_TIMER_CC0ROUTE_PORT_SHIFT != _GPIO_TIMER_CC2ROUTE_PORT_SHIFT
	#error "GPIO_TIMER_ROUTE_PORT"
#endif
#if _GPIO_TIMER_CC0ROUTE_PIN_SHIFT != _GPIO_TIMER_CC1ROUTE_PIN_SHIFT || _GPIO_TIMER_CC0ROUTE_PIN_SHIFT != _GPIO_TIMER_CC2ROUTE_PIN_SHIFT
	#error "GPIO_TIMER_ROUTE_PIN"
#endif
#endif

static void _pwm_CMU_ClockEnable(bool enable) {
	#if defined(PWM_TIMER_NUMBER_1)
	CMU_ClockEnable(PWM_TIMER_CLOCK_NUMBER_0, enable);
	CMU_ClockEnable(PWM_TIMER_CLOCK_NUMBER_1, enable);
	#else
	CMU_ClockEnable(PWM_TIMER_CLOCK_NUMBER_0, enable);
	#endif
}

#if MAX_ZUNO_PWMS != 4
	#error "Error pin pwm!"
#endif

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

static uint8_t _findPWMChannelBusy(uint8_t pin) {
	uint8_t					i;

	i = 0x0;
	pin++;
	while (i < sizeof(_channel)) {
		if (_channel[i] == pin)
			return (i);
		i++;
	}
	return (INVALID_PIN_INDEX);
}

static uint8_t _findPWMChannelSpace(uint8_t pin) {
	uint8_t					i;

	i = 0x0;
	while (i < sizeof(_channel)) {
		if (_channel[i] == 0x0) {
			pin++;
			_channel[i] = pin;
			return (i);
		}
		i++;
	}
	return (INVALID_PIN_INDEX);
}

static void _noTone(uint8_t pin, bool disable);

#if defined(PWM_TIMER_NUMBER_1)
static void _analogWriteDisable(uint8_t pin) {
	uint8_t							channel;
	uint8_t							fd;

	channel = _findPWMChannelBusy(pin);
	if(channel == INVALID_PIN_INDEX)
		return ;
	_channel[channel] = 0x0;
	if (channel >= (PWM_TIMER_CC_COUNT)) {
		channel = channel - PWM_TIMER_CC_COUNT;
		fd = PWM_TIMER_FD_NUMBER_1;
	}
	else
		fd = PWM_TIMER_FD_NUMBER_0;
	GPIO->TIMERROUTE[fd].ROUTEEN = GPIO->TIMERROUTE[fd].ROUTEEN & ~(PWM_TIMER_CCROUTE(channel));
	if (GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_0].ROUTEEN == PWM_TIMER_ROUTEPEN_RESET && GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_1].ROUTEEN == PWM_TIMER_ROUTEPEN_RESET) {
		TIMER_Reset(PWM_TIMER_NUMBER_0);
		TIMER_Reset(PWM_TIMER_NUMBER_1);
		zunoPeripheryRelese(&gSyncVirtualTimer1, SyncMasterPwm);
	}
}

static bool _analogWriteEnable(uint8_t pin, uint16_t value, uint32_t pwm_enabled) {
	TIMER_TypeDef					*timer;
	uint8_t							channel;
	uint8_t							fd;
	uint8_t							real_pin;
	uint8_t							real_port;
	uint32_t						cc_route;

	channel = _findPWMChannelBusy(pin);
	if(channel == INVALID_PIN_INDEX) {
		channel = _findPWMChannelSpace(pin);
		if(channel == INVALID_PIN_INDEX)
			return (false);
		_noTone(pin, true);
		real_pin = getRealPin(pin);
		real_port = getRealPort(pin);
		cc_route = (real_port << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (real_pin << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
		switch (channel) {
			case 0x0:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_0].CC0ROUTE = cc_route;
				break ;
			case 0x1:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_0].CC1ROUTE = cc_route;
				break ;
			case 0x2:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_0].CC2ROUTE = cc_route;
				break ;
			case 0x3:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_1].CC0ROUTE = cc_route;
				break ;
			case 0x4:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_1].CC1ROUTE = cc_route;
				break ;
			case 0x5:
				GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_1].CC2ROUTE = cc_route;
				break ;
		}
		if (channel >= (PWM_TIMER_CC_COUNT)) {
			channel = channel - PWM_TIMER_CC_COUNT;
			fd = PWM_TIMER_FD_NUMBER_1;
		}
		else
			fd = PWM_TIMER_FD_NUMBER_0;
		GPIO->TIMERROUTE[fd].ROUTEEN = GPIO->TIMERROUTE[fd].ROUTEEN | (PWM_TIMER_CCROUTE(channel));
		pinMode(pin, OUTPUT_UP);// enable the output
	}
	if (channel >= (PWM_TIMER_CC_COUNT)) {
		channel = channel - PWM_TIMER_CC_COUNT;
		timer = PWM_TIMER_NUMBER_1;
	}
	else
		timer = PWM_TIMER_NUMBER_0;
	TIMER_CompareBufSet(timer, channel, TIMER_TopGet(timer) * value / pwm_enabled);
	return (true);
}

#else
static void _analogWriteDisable(uint8_t pin) {
	uint8_t					channel;
	TIMER_TypeDef			*timer;

	channel = _findPWMChannelBusy(pin);
	if(channel == INVALID_PIN_INDEX)
		return ;
	_channel[channel] = 0x0;
	timer = PWM_TIMER_NUMBER_0;
	timer->ROUTEPEN = timer->ROUTEPEN & ~(PWM_TIMER_CCROUTE(channel));
	if (timer->ROUTEPEN == PWM_TIMER_ROUTEPEN_RESET) {
		TIMER_Reset(timer);
		zunoPeripheryRelese(&gSyncVirtualTimer1, SyncMasterPwm);
	}
}

static bool _analogWriteEnable(uint8_t pin, uint16_t value, uint32_t pwm_enabled) {
	TIMER_TypeDef				*timer;
	uint8_t						channel;
	size_t						location;

	channel = _findPWMChannelBusy(pin);
	if(channel == INVALID_PIN_INDEX) {
		channel = _findPWMChannelSpace(pin);
		if(channel == INVALID_PIN_INDEX)
			return (false);
		_noTone(pin, true);
		location = getLocationTimer0AndTimer1Chanell(pin, channel);
		timer = PWM_TIMER_NUMBER_0;
		timer->ROUTELOC0 = (timer->ROUTELOC0 & ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (channel << 3))) | location;
		timer->ROUTEPEN = timer->ROUTEPEN | (PWM_TIMER_CCROUTE(channel));
		pinMode(pin, OUTPUT_UP);// enable the output
	}
	TIMER_CompareBufSet(timer, channel, TIMER_TopGet(timer) * value / pwm_enabled);
	return (true);
}
#endif

static uint8_t _analogWrite(uint8_t pin, uint16_t value) {
	uint32_t					pwm_enabled;
	int							mode;

	pwm_enabled = 0xFFFFFFFF >> ((sizeof(pwm_enabled) * 0x8) - _pwm_resolution);
	if (value == 0x0 || value >= pwm_enabled) {
		_noTone(pin, true);
		_analogWriteDisable(pin);
		if (value == 0x0)
			mode = OUTPUT_DOWN;
		else
			mode = OUTPUT_UP;
		pinMode(pin, mode);
		return (true);
	}
	return (_analogWriteEnable(pin, value, pwm_enabled));
}

static void _initPwm(TIMER_TypeDef *timer, CMU_Clock_TypeDef clock) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	size_t						freq;
	size_t						channel;
	TIMER_Prescale_TypeDef		timer_prescale;

	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(timer, &timerInit);
	freq = CMU_ClockFreqGet(clock) / _pwm_freq;
	timer_prescale = _getPrescale(freq);
	timerInit.prescale = timer_prescale;
	#if defined (_TIMER_CFG_PRESC_MASK)
	freq = freq / (timer_prescale + 0x1);
	#endif
	#if defined (_TIMER_CTRL_PRESC_MASK)
	freq = freq / (0x1 << timer_prescale);
	#endif
	TIMER_Init(timer, &timerInit);
	TIMER_TopSet(timer, freq);
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModePWM;
	timerCCInit.cmoa = timerOutputActionToggle;
	channel = 0;
	while (channel < (PWM_TIMER_CC_COUNT))
		TIMER_InitCC(timer, channel++, &timerCCInit);
	TIMER_Enable(timer, true);
}

bool analogWrite(uint8_t pin, word value) {
	SyncPeripheryCaptureStatus_t				status;
	uint8_t										out;

	if (pin > ZUNO_PIN_LAST_INDEX)
		return (false);
	if (TONE_PWM_ENTER() != ZunoErrorOk)
		return (false);
	if ((status = zunoPeripheryCapture(&gSyncVirtualTimer1, SyncMasterPwm)) == SyncPeripheryCaptureStatusBad) {
		out = false;
	}
	else {
		if (status == SyncPeripheryCaptureStatusOk) {
			_pwm_CMU_ClockEnable(true);
			#if defined(PWM_TIMER_NUMBER_1)
			_initPwm(PWM_TIMER_NUMBER_0, PWM_TIMER_CLOCK_NUMBER_0);
			_initPwm(PWM_TIMER_NUMBER_1, PWM_TIMER_CLOCK_NUMBER_1);
			GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_0].ROUTEEN = PWM_TIMER_ROUTEPEN_RESET;
			GPIO->TIMERROUTE[PWM_TIMER_FD_NUMBER_1].ROUTEEN = PWM_TIMER_ROUTEPEN_RESET;
			#else
			_initPwm(PWM_TIMER_NUMBER_0, PWM_TIMER_CLOCK_NUMBER_0);
			PWM_TIMER_NUMBER_0->ROUTEPEN = PWM_TIMER_ROUTEPEN_RESET;//disable CC
			#endif
			
		}
		out = _analogWrite(pin, value);
	}
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
	CMU_ClockEnable(TONE_TIMER_CLOCK_NUMBER_0, enable);
	CMU_ClockEnable(TONE_TIMER_CLOCK_NUMBER_1, enable);
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

static void _noTone(uint8_t pin, bool disable) {
	if (pin == INVALID_PIN_INDEX)
		return ;
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
	zunoPeripheryRelese(&gSyncVirtualTimer0, SyncMasterTone);
	if (disable == true)
		pinMode(pin, DISABLED);// Switch off this pin anyway
}

void noTone(uint8_t pin) {
	if (TONE_PWM_ENTER() != ZunoErrorOk)
		return ;
	_noTone(pin, true);
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

	if (pin > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	_analogWriteDisable(pin);//disable pwm
	if (freq == 0) {
		Serial0.println("freq == 0");
		_noTone(_tone_pin, false);
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
		_noTone(pin, true);
	}
	TONE_PWM_EXIT();
	return (ret);
}