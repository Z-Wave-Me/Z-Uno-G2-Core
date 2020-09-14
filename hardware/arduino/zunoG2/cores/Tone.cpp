#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"
#include "includes\Tone_private.h"

static uint8_t _aux_findPWMChannel(uint8_t pin) {
	int							i;
	ZUNOOnDemandHW_t			*lp;

	lp = &g_zuno_odhw_cfg;
	for(i=0;i < MAX_ZUNO_PWMS; i++) {
		if(lp->pwm_pins[i] == pin)
			return i;
	}
	return INVALID_PIN_INDEX;
}


static uint32_t _map_pwmloc2ch(uint8_t loc, uint8_t ch) {
	loc = (loc + 32 - ch) & 0x1F;
	ch <<= 3;
	return (loc << ch);
}

void noTone(uint8_t pin) {
	ZUNOOnDemandHW_t			*lp;

	if (pin == INVALID_PIN_INDEX)
		return ;
	lp = &g_zuno_odhw_cfg;
	if (lp->tone_pin != pin)
		return ;
	lp->tone_pin = INVALID_PIN_INDEX;
	lp->tone_freq = 0;
	TONE_TIMER->ROUTEPEN &= ~(1UL << TONE_CHANNEL);//disable CC
	digitalWrite(pin, LOW);// Switch off this pin anyway
}

uint8_t _analogWrite(uint8_t pin, uint8_t value) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	ZUNOOnDemandHW_t			*lp;
	TIMER_TypeDef				*timer;
	size_t						freq;
	uint8_t						channel;

	if (pin == INVALID_PIN_INDEX)
		return (false);
	timer = PWM_TIMER;
	lp = &g_zuno_odhw_cfg;
	if((freq = lp->pwm_freq) == 0) {
		memset(&lp->pwm_pins[0], INVALID_PIN_INDEX, sizeof(lp->pwm_pins));
		CMU_ClockEnable(PWM_TIMER_CLOCK, true);
		timerInit = TIMER_INIT_DEFAULT;
		timerInit.prescale = timerPrescale2;
		freq = CMU_ClockFreqGet(PWM_TIMER_CLOCK) / (1 << timerInit.prescale) / PWM_HGZ;// PWM_HGZ - required frequency //0x25317C0
		lp->pwm_freq = freq;
		TIMER_TopSet(timer, freq);
		TIMER_Init(timer, &timerInit);
	}
	channel = _aux_findPWMChannel(pin);
	switch (value) {
		case PWM_DISABLED:// switch off the led if it was enabled already
			if(channel == INVALID_PIN_INDEX)
				return (false); // We don't have this pin is occupied by the PWM - go out
			lp->pwm_pins[channel] = INVALID_PIN_INDEX;
			lp->pwm_pins_state = lp->pwm_pins_state ^ (1 << channel);
			timer->ROUTEPEN &= ~(1UL << channel);//disable CC
			digitalWrite(pin, LOW);// Switch off this pin anyway
			return (true);
		case PWM_ENABLED:
			if(channel == INVALID_PIN_INDEX) {
				channel = _aux_findPWMChannel(INVALID_PIN_INDEX);
				if(channel == INVALID_PIN_INDEX)
					return (false);
				lp->pwm_pins[channel] = pin;
				noTone(pin);
				pinMode(pin, OUTPUT);// enable the output
			}
			else if ((lp->pwm_pins_state & (1 << channel)) != 0) {
				timer->ROUTEPEN &= ~(1UL << channel);//disable CC
				lp->pwm_pins_state = lp->pwm_pins_state ^ (1 << channel);
			}
			digitalWrite(pin, HIGH);
			return (true);
	}
	if(channel == INVALID_PIN_INDEX) {
		channel = _aux_findPWMChannel(INVALID_PIN_INDEX);
		if(channel == INVALID_PIN_INDEX)
			return (false);
		noTone(pin);
		timerCCInit = TIMER_INITCC_DEFAULT;
		timerCCInit.mode = timerCCModePWM;
		timerCCInit.cmoa = timerOutputActionToggle;
		TIMER_InitCC(timer, channel, &timerCCInit);
		lp->pwm_pins[channel] = pin;// We occupied this channel with the needed pin
		lp->pwm_pins_state = lp->pwm_pins_state | (1 << channel);
		timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (channel << 3));
		timer->ROUTELOC0 |= _map_pwmloc2ch( getLocation(g_loc_pa0_pf7_all, g_loc_pa0_pf7_all_size, pin), channel);
		timer->ROUTEPEN |= (1UL << channel);//enabled CC
		pinMode(pin, OUTPUT);// enable the output
	}
	else if ((lp->pwm_pins_state & (1 << channel)) == 0) {
		timer->ROUTEPEN |= (1UL << channel);//enabled CC
		lp->pwm_pins_state = lp->pwm_pins_state ^ (1 << channel);
	}
	TIMER_CompareBufSet(timer, channel, freq * value / PWM_ENABLED);
	return (true);
}

uint8_t _tonePrescale(size_t freq) {
	uint8_t					prescale;

	prescale = timerPrescale1;
	while (prescale < timerPrescale1024 && (freq / (1 << prescale)) > 0xFFFF) 
		prescale++;
	return (prescale);
}

void tone(uint8_t pin, uint16_t freq) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;
	ZUNOOnDemandHW_t			*lp;
	size_t						tone_freq_set;
	uint8_t						prescale;

	if (pin == INVALID_PIN_INDEX)
		return ;
	if (_aux_findPWMChannel(pin) != INVALID_PIN_INDEX)
		_analogWrite(pin, 0);//disable pwm
	lp = &g_zuno_odhw_cfg;
	timer = TONE_TIMER;
	if ((tone_freq_set = lp->tone_freq_set) == 0) {
		lp->tone_pin = INVALID_PIN_INDEX;
		CMU_ClockEnable(TONE_TIMER_CLOCK, true);
		tone_freq_set = CMU_ClockFreqGet(TONE_TIMER_CLOCK) / 2;//0x25317C0 get the frequency for one hertz
		lp->tone_freq_set = tone_freq_set;
		timerCCInit = TIMER_INITCC_DEFAULT;
		timerCCInit.mode = timerCCModeCompare;
		timerCCInit.cmoa = timerOutputActionToggle;
		TIMER_InitCC(timer, TONE_CHANNEL, &timerCCInit);
	}
	if (lp->tone_pin == pin) {
		if (lp->tone_freq == freq)
			return ;
		if (freq == 0)
			return (noTone(pin));
	}
	lp->tone_freq = freq;
	timerInit = TIMER_INIT_DEFAULT;
	tone_freq_set = tone_freq_set / freq;
	prescale = _tonePrescale(tone_freq_set);
	timerInit.prescale = (TIMER_Prescale_TypeDef)prescale;
	TIMER_TopSet(timer, tone_freq_set / (1 << prescale));
	TIMER_Init(timer, &timerInit);
	pinMode(pin, OUTPUT);// enable the output
	TIMER_CompareBufSet(timer, TONE_CHANNEL, 1);
	if (lp->tone_pin != pin) {
		lp->tone_pin = pin;
		timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (TONE_CHANNEL << 3));
		timer->ROUTELOC0 |= _map_pwmloc2ch(getLocation(g_loc_pa0_pf7_all, g_loc_pa0_pf7_all_size, pin), TONE_CHANNEL);
		timer->ROUTEPEN |= (1UL << TONE_CHANNEL);
	}
}

void toneDelayed(uint8_t pin, uint16_t freq, uint16_t duration) {
	tone(pin, freq);
	delay(duration);
	noTone(pin);
}