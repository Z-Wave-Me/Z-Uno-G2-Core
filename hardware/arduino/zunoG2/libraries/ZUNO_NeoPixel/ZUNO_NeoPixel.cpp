#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"
#include "stdlib.h"
#include "ZUNO_NeoPixel.h"

/* Public Constructors */
NeoPixel::NeoPixel(void): list(0), bHandlerTimer(false) {

}

/* Public Methods */
void NeoPixel::show(uint8_t neo_pin) {
	ZunoNeoList_t			*list;
	ZunoNeoType_t			flag;
	ZunoNeoCountLed			count_led;

	if ((list = this->_findList(neo_pin)) == 0 || list->count_led == 0)
		return ;
	flag = list->flag;
	digitalWrite(neo_pin, LOW);
	delayMicroseconds(NEO_RESET_MICROSECONDS);
	this->freq = CMU_ClockFreqGet(NEO_TIMER_CLOCK) / ((flag.type & NEO_KHZ400 != 0)? 400000 : 800000);
	if ((flag.type & NEO_MODE_TIMER_DMA) != 0)
		;
	else
		this->_showTimer(list, flag, neo_pin);
	count_led = list->count_led;
	delayMicroseconds(count_led * 1 + count_led / 3);
}

void NeoPixel::setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color) {//uint8_t red, uint8_t green, uint8_t blue, uint8_t white
	ZunoNeoList_t			*list;
	ZunoNeoType_t			flag;
	uint8_t					brightness;
	uint8_t					*array;
	uint8_t					redOffset;
	uint8_t					whiteOffset;

	brightness = 255;
	if ((list = this->_findList(neo_pin)) == 0 || id_led >= list->count_led)
		return ;
	flag = list->flag;
	redOffset = flag.redOffset;
	whiteOffset = flag.whiteOffset;
	if (redOffset == whiteOffset)
		array = &list->array[id_led * 3];
	else {
		array = &list->array[id_led * 4];
		array[whiteOffset] = (color.white * brightness) >> 8;
	}
	array[redOffset] = (color.red * brightness) >> 8;
	array[flag.greenOffset] = (color.green * brightness) >> 8;
	array[flag.blueOffset] = (color.blue * brightness) >> 8;
}


ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint16_t type) {
	ZunoError_t				ret;
	ZunoNeoList_t			*list;
	size_t					n;
	ZunoNeoType_t			flag;

	flag.type = type;
	if (g_bit_field.bGPTInit != false)
		return (ZunoErrorTimerAlredy);
	if (g_bit_field.bNeoInit == false) {
		CMU_ClockEnable(NEO_TIMER_CLOCK, true);
		g_bit_field.bNeoInit = true;
	}
	if ((flag.type & NEO_MODE_TIMER_DMA) != 0)
		;
	else {
		if (this->bHandlerTimer == false) {
			if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, NEO_TIMER_HANDLER_ID, (void *)this->_timer_handler)) != ZunoErrorOk)
				return (ret);
			this->bHandlerTimer = true;
		}
	}
	if ((list = this->_findList(neo_pin)) != 0)
		this->_deleteNeo(list);
	n = count_led * ((flag.redOffset == flag.whiteOffset) ? 3 : 4);
	if ((list = (ZunoNeoList_t *)malloc(sizeof(ZunoNeoList_t) + n)) == 0)
		return (ZunoErrorMemory);
	list->count_led = count_led;
	list->neo_pin = neo_pin;
	list->flag.type = flag.type;
	memset(&list->array[0], 0, n);
	this->_addList(list);
	pinMode(neo_pin, OUTPUT);
	return (ZunoErrorOk);
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led) {
	return (this->addNeo(neo_pin, count_led, NEO_GRB | NEO_KHZ800 | NEO_MODE_TIMER));
}

void NeoPixel::deleteNeo(uint8_t neo_pin) {
	ZunoNeoList_t		*list;
	ZunoNeoList_t		*list_prev;
	ZunoNeoList_t		*list_tmp;

	if ((list = this->_findList(neo_pin)) == 0)
		return ;
	this->_deleteNeo(list);
}

static uint8_t test = 0;

/* Private Methods */
void NeoPixel::_timer_handler(void) {
	TIMER_TypeDef				*timer;
	uint8_t						bit_count;
	uint8_t						bState;
	uint8_t						divider;

	
	timer = NEO_TIMER;
	if (test == 0)
	{
		digitalWrite(0, HIGH);
		test = 1;
	}
	else {
		digitalWrite(0, LOW);
		test = 0;
	}
	
	TIMER_IntClear(timer, TIMER_IF_OF);/* Clear the interrupt flag in the beginning */
	return ;
	if ((bit_count = Neo.save.timer.bit_count) == 0) {
		if (Neo.save.timer.b++ < Neo.save.timer.e) {
			bit_count = 8;
			Neo.save.timer.bState = HIGH;
		}
		else
			TIMER_Enable(timer, false);
	}
	if (bit_count != 0) {
		bState = Neo.save.timer.bState;
		if (bState == LOW)
			Neo.save.timer.bit_count = --bit_count;
		if (((Neo.save.timer.b[0] >> bit_count) & 0x1) != 0)
			divider = (bState == HIGH) ? NEO_ONE_HIGH_PERIOD : NEO_ONE_LOW_PERIOD;
		else
			divider = (bState == HIGH) ? NEO_ZERO_HIGH_PERIOD : NEO_ZERO_LOW_PERIOD;
		Neo.save.timer.bState = (bState == HIGH) ? LOW : HIGH;
		digitalWrite(Neo.save.timer.neo_pin, bState);
		TIMER_TopSet(timer, Neo.freq * divider / NEO_FULL_PERIOD);
	}
	TIMER_IntClear(timer, TIMER_IF_OF);/* Clear the interrupt flag in the beginning */
}
 static uint32_t _map_pwmloc2ch(uint8_t loc, uint8_t ch) {
 	loc = (loc + 32 - ch) & 0x1F;
 	ch <<= 3;
 	return (loc << ch);
 }
#define PWM_TIMER						WTIMER0
#define PWM_TIMER_CLOCK					cmuClock_WTIMER0
#define PWM_HGZ							1600000
#define PWM_DISABLED					0x0
#define PWM_ENABLED						0xFF
#define PWM_PIN_DISABLED				0x0
#define PWM_PIN_ENABLED					0x1
#define PWM_PIN_PULSE					0x2

inline void NeoPixel::_showTimer(ZunoNeoList_t *list, ZunoNeoType_t flag, uint8_t neo_pin) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_TypeDef				*timer;
	uint8_t						*b;
	uint8_t						redOffset;
	uint8_t						whiteOffset;


	timer = NEO_TIMER;
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(timer, &timerInit);
	NVIC_EnableIRQ(NEO_TIMER_IRQ);/* Enable TIMER0 interrupt in NVIC */
	TIMER_IntEnable(timer, TIMER_IF_OF);/* Enable TIMER0 IRQ on Overflow */
	TIMER_TopSet(timer, CMU_ClockFreqGet(NEO_TIMER_CLOCK) / 2 / 35000);
	//TIMER_TopSet(timer, this->freq * NEO_ZERO_HIGH_PERIOD / NEO_FULL_PERIOD);
	redOffset = flag.redOffset;
	whiteOffset = flag.whiteOffset;
	b = &list->array[-1];
	this->save.timer.b = b;
	this->save.timer.e = &b[list->count_led + 1];
	this->save.timer.bit_count = 0;
	this->save.timer.neo_pin = neo_pin;
	TIMER_Enable(timer, true);
	// TIMER_Init_TypeDef			timerInit = TIMER_INIT_DEFAULT;
	// TIMER_InitCC_TypeDef		timerCCInit = TIMER_INITCC_DEFAULT;
	// TIMER_TypeDef				*timer;
	// size_t						freq;

	// timer = PWM_TIMER;
	// CMU_ClockEnable(PWM_TIMER_CLOCK, true);
	// timerInit.prescale = timerPrescale1;
	// freq = CMU_ClockFreqGet(PWM_TIMER_CLOCK) / (1 << timerInit.prescale) / PWM_HGZ;// PWM_HGZ - required frequency //0x25317C0
	// TIMER_TopSet(timer, freq);
	// TIMER_Init(timer, &timerInit);

	// timerCCInit.mode = timerCCModePWM;
	// timerCCInit.cmoa = timerOutputActionToggle;
	// TIMER_InitCC(timer, 0, &timerCCInit);
	// timer->ROUTELOC0 &= ~(_TIMER_ROUTELOC0_CC0LOC_MASK << (0 << 3));
	// timer->ROUTELOC0 |= _map_pwmloc2ch( _TIMER_ROUTELOC0_CC0LOC_LOC28, 0);
	// timer->ROUTEPEN |= (1UL << 0);//enabled CC
	// TIMER_CompareBufSet(timer, 0, freq * 80 / 125);
}

ZunoNeoList_t *NeoPixel::_findList(uint8_t neo_pin) {
	ZunoNeoList_t			*list;

	list = this->list;
	while (list != 0) {
		if (list->neo_pin == neo_pin)
			break ;
		list = list->next;
	}
	return (list);
}

void NeoPixel::_deleteNeo(ZunoNeoList_t *list) {
	ZunoNeoList_t		*list_prev;
	ZunoNeoList_t		*list_tmp;

	list_prev = this->list;
	if (list == list_prev)
		this->list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
	free(list);
}

inline void NeoPixel::_addList(ZunoNeoList_t *list) {
	ZunoNeoList_t			*list_next;
	ZunoNeoList_t			*list_tmp;

	if ((list_next = this->list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->list = list;
}


/* Preinstantiate Objects */
NeoPixel Neo = NeoPixel();