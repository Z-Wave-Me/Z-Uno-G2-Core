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

uint8_t _analogWrite(uint8_t pin, uint8_t value) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	ZUNOOnDemandHW_t			*lp;
	TIMER_TypeDef				*timer;
	size_t						freq;
	uint8_t						channel;

	timer = PWM_TIMER;
	lp = &g_zuno_odhw_cfg;
	if((freq = lp->pwm_freq) == 0) {
		memset(&lp->pwm_pins[0], INVALID_PIN_INDEX, sizeof(lp->pwm_pins));
		CMU_ClockEnable(PWM_TIMER_CLOCK, true);
		timerInit = TIMER_INIT_DEFAULT;
		timerInit.prescale = timerPrescale2;
		freq = CMU_ClockFreqGet(PWM_TIMER_CLOCK) / 2 / 490;//2 = timerPrescale2// 490 - required frequency //0x25317C0
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
			if(channel == INVALID_PIN_INDEX)
				pinMode(pin, OUTPUT);// enable the output
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

#define TONE_DISABLED		0x0
#define TONE_CHANNEL		0x0
#define TONE_TIMER			TIMER0
#define TONE_TIMER_CLOCK	cmuClock_TIMER0

static uint8_t pin_set = INVALID_PIN_INDEX;
static uint8_t bInit = false;
static uint8_t prescale;

void toneDelayed(uint8_t pin, uint16_t freq, uint16_t duration) {
    //  tone(pin, freq);
    //  delay(duration);
    //  noTone(pin);
}

void tone(uint8_t pin, uint16_t freq) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;

	timer = TONE_TIMER;
	CMU_ClockEnable(TONE_TIMER_CLOCK, true);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = timerPrescale1;
	TIMER_TopSet(timer, CMU_ClockFreqGet(TONE_TIMER_CLOCK) / 2 / 1 / freq);// freq - required frequency //0x25317C0
	TIMER_Init(timer, &timerInit);
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModeCompare;
	timerCCInit.cmoa = timerOutputActionToggle;
	TIMER_InitCC(timer, TONE_CHANNEL, &timerCCInit);
	timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (TONE_CHANNEL << 3));
	timer->ROUTELOC0 |= _map_pwmloc2ch( getLocation(g_loc_pa0_pf7_all, g_loc_pa0_pf7_all_size, pin), TONE_CHANNEL);
	timer->ROUTEPEN |= (1UL<< TONE_CHANNEL);
	pinMode(pin, OUTPUT);// enable the output
	TIMER_CompareBufSet(timer, TONE_CHANNEL, 1);
}
void noTone(uint8_t pin) {
	// zunoGPTEnable(0); 
	// digitalWrite(g_tone_pin_ch1, LOW);
}
