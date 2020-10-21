#include "Arduino.h"
#include "CrtxCmu.h"
#include "stdlib.h"
#include "ZDma.h"
#include "ZUNO_NeoPixel_define.h"
#include "ZUNO_NeoPixel_private.h"

static const ZunoNeoTypeConfig_t	usart0_config = {
	{.usart = USART0},
	.dst = (void *)&(USART0->TXDATA),
	.dmaSignal = zdmaPeripheralSignal_USART0_TXBL,
	.bus_clock = cmuClock_USART0,
	.type = NEO_TYPE_USART,
	.coder = NEO_CODER_1TO4
};

static const ZunoNeoTypeConfig_t	usart1_config = {
	{.usart = USART1},
	.dst = (void *)&(USART1->TXDATA),
	.dmaSignal = zdmaPeripheralSignal_USART1_TXBL,
	.bus_clock = cmuClock_USART1,
	.type = NEO_TYPE_USART,
	.coder = NEO_CODER_1TO4
};

static const ZunoNeoTypeConfig_t	usart2_config = {
	{.usart = USART2},
	.dst = (void *)&(USART2->TXDATA),
	.dmaSignal = zdmaPeripheralSignal_USART2_TXBL,
	.bus_clock = cmuClock_USART2,
	.type = NEO_TYPE_USART,
	.coder = NEO_CODER_1TO4
};

static const ZunoNeoTypeConfig_t	timer0_config = {
	{.timer = TIMER0},
	.dst = (void *)&(TIMER0->CC[NEO_TIMER_CHANNEL].CCVB),
	.dmaSignal = zdmaPeripheralSignal_TIMER0_CC0,
	.bus_clock = cmuClock_TIMER0,
	.type = NEO_TYPE_TIMER,
	.coder = NEO_CODER_1TO8
};

static const ZunoNeoTypeConfig_t	timer1_config = {
	{.timer = TIMER1},
	.dst = (void *)&(TIMER1->CC[NEO_TIMER_CHANNEL].CCVB),
	.dmaSignal = zdmaPeripheralSignal_TIMER1_CC0,
	.bus_clock = cmuClock_TIMER1,
	.type = NEO_TYPE_TIMER,
	.coder = NEO_CODER_1TO8
};

static const ZunoNeoTypeConfig_t	wtimer0_config = {
	{.timer = WTIMER0},
	.dst = (void *)&(WTIMER0->CC[NEO_TIMER_CHANNEL].CCVB),
	.dmaSignal = zdmaPeripheralSignal_WTIMER0_CC0,
	.bus_clock = cmuClock_WTIMER0,
	.type = NEO_TYPE_TIMER,
	.coder = NEO_CODER_1TO8
};


static uint8_t _getLocationWtimer(uint8_t pin, uint8_t ch) {
	pin = (getRealPort(pin) << 4) | getRealPin(pin);
	switch (ch) {
		case 0:
			switch (pin) {
				case 0x00:// LOC 0-5 = PA0-PA5
				case 0x01:
				case 0x02:
				case 0x03:
				case 0x04:
				case 0x05:
					break ;
				case 0x1B:// LOC  15-19 = PB11-PB15
				case 0x1C:
				case 0x1D:
				case 0x1E:
				case 0x1F:
				case 0x26:// LOC 26-31 = PC6-PC11
				case 0x27:
				case 0x28:
				case 0x29:
				case 0x2A:
				case 0x2B:
					pin = pin - 12;
					break ;
			}
			break;
		case 1:
			switch (pin) {
				case 0x02:// LOC 0-3 = PA2-PA5
				case 0x03:
				case 0x04:
				case 0x05:
					pin = pin - 2;
					break ;
				case 0x1B:// LOC  13-17 = PB11-PB15
				case 0x1C:
				case 0x1D:
				case 0x1E:
				case 0x1F:
				case 0x26:// LOC 24-29 = PC6-PC11
				case 0x27:
				case 0x28:
				case 0x29:
				case 0x2A:
				case 0x2B:
					pin = pin - 14;
					break ;
				case 0x39:// LOC 31 = PD9
					pin = 31;
					break ;
			}
			break;
		case 2:
			switch (pin) {
				case 0x04:// LOC 0-1 = PA4-PA5
				case 0x05:
					pin = pin - 4;
					break ;
				case 0x1B:// LOC  11-15 = PB11-PB15
				case 0x1C:
				case 0x1D:
				case 0x1E:
				case 0x1F:
				case 0x26:// LOC 22-27 = PC6-PC11
				case 0x27:
				case 0x28:
				case 0x29:
				case 0x2A:
				case 0x2B:
					pin = pin - 16;
					break ;
				case 0x39:// LOC 29 - 31 = PD9 - PD11
				case 0x3A:
				case 0x3B:
					pin = pin - 28;
					break ;
			}
			break;
	}
	return (pin << ch);
}

static void _initTimer(uint8_t neo_pin, const ZunoNeoTypeConfig_t *config) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_InitCC_TypeDef		timerCCInit;
	TIMER_TypeDef				*timer;

	CMU_ClockEnable(config->bus_clock, true);
	timerCCInit = TIMER_INITCC_DEFAULT;
	timerCCInit.mode = timerCCModePWM;
	timer = config->timer;
	TIMER_InitCC(timer, NEO_TIMER_CHANNEL, &timerCCInit);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(timer, &timerInit);
	timer->ROUTEPEN = (1UL << NEO_TIMER_CHANNEL);//enabled CC
}

static void _initUsart(uint8_t neo_pin, const ZunoNeoTypeConfig_t *config) {
	USART_InitSync_TypeDef				init_spi;
	USART_TypeDef						*usart;
	
	CMU_ClockEnable(config->bus_clock, true);
	init_spi = USART_INITSYNC_DEFAULT;
	init_spi.enable = usartDisable;
	usart = config->usart;
	USART_InitSync(usart, &init_spi);
	usart->ROUTEPEN = USART_ROUTEPEN_TXPEN;
}

static void _setColorTimerCoder(uint8_t *b, uint8_t color, uint8_t one_hight, uint8_t zero_hight) {
	uint8_t			i;
	uint8_t			value;

	i = NEO_CODER_1TO8;
	while (i-- != 0) {
		if ((color & 0x80) != 0)
			value = one_hight;
		else
			value = zero_hight;
		color = color << 1;
		b++[0] = value;
	}
}

static void _setColorUsartCoder(uint8_t *b, uint8_t color) {
	uint8_t			i;
	uint8_t			value;

	i = NEO_CODER_1TO4;
	while (i-- != 0) {
		switch (color & 0xC0) {
			case 0xC0:
				value = 0x77;
				break ;
			case 0x80:
				value = 0x17;
				break ;
			case 0x40:
				value = 0x71;
				break ;
			default:
				value = 0x11;
				break ;
		}
		color = color << 2;
		b++[0] = value;
	}
}

/* Public Constructors */
NeoPixel::NeoPixel(void): _list(0), _bInitTimer0(0), _bInitTimer1(0), _bInitWTimer0(0), _bInitUsart0(0), _bInitUsart1(0), _bInitUsart2(0) {
}

/* Public Methods */
void NeoPixel::fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoList_t					*list;

	if ((list = this->_findList(neo_pin)) == 0)
		return ;
	this->_fill(list, first_id_led, count, color, brightness);
}

void NeoPixel::fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color) {
	ZunoNeoList_t					*list;

	if ((list = this->_findList(neo_pin)) == 0)
		return ;
	this->_fill(list, first_id_led, count, color, list->brightness);
}

void NeoPixel::clear(uint8_t neo_pin) {
	ZunoNeoList_t					*list;
	ZunoNeoColor_t					color;

	if ((list = this->_findList(neo_pin)) == 0)
		return ;
	color.color = 0;
	this->_fill(list, 0, list->count_led, color, NEO_BRIGHTNESS_DEFAULT);
}

void NeoPixel::show(uint8_t neo_pin) {
	size_t							base;
	ZunoNeoList_t					*list;
	const ZunoNeoTypeConfig_t		*config;
	ZunoZDmaUser_t					userLp;
	ZunoNeoOption_t					flag;
	ZunoNeoCountLed					len;
	size_t							freq;

	if ((list = this->_findList(neo_pin)) == 0 || (len = list->count_led) == 0)
		return ;
	flag = list->flag;
	config = list->config;
	len = len * (flag.redOffset == flag.whiteOffset ? 3 : 4) * config->coder + 1;//+1 LOW
	base = config->base;
	switch (config->type) {
		case NEO_TYPE_TIMER:
			TIMER_TopSet(((TIMER_TypeDef *)base), list->freq_timer);
			if (((TIMER_TypeDef *)base) == WTIMER0) {
				((TIMER_TypeDef *)base)->ROUTELOC0 = _getLocationWtimer(neo_pin, NEO_TIMER_CHANNEL);
			}
			else
				((TIMER_TypeDef *)base)->ROUTELOC0 = getLocationTimer0AndTimer1Chanell(neo_pin, NEO_TIMER_CHANNEL);
			TIMER_CompareBufSet(((TIMER_TypeDef *)base), NEO_TIMER_CHANNEL, 0);//+1 LOW
			TIMER_Enable(((TIMER_TypeDef *)base), true);
			freq = len * ((((flag.option & NEO_KHZ400) != 0)? NEO_TIMER_HZ400 : NEO_TIMER_HZ800) / NEO_TIMER_HZ800) * 125 / 100 / 1000;
			break;
		case NEO_TYPE_USART:
			if (((USART_TypeDef *)base) == USART2)
				((USART_TypeDef *)base)->ROUTELOC0 = (((((getRealPort(neo_pin) << 4) | getRealPin(neo_pin)) == 5) ? 0 : getLocation(&g_loc_pf0_pf1_pf3_pf7[0], sizeof(g_loc_pf0_pf1_pf3_pf7), neo_pin) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT);
			else
				((USART_TypeDef *)base)->ROUTELOC0 = ((getLocation( &g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), neo_pin)) << _USART_ROUTELOC0_TXLOC_SHIFT);
			freq = (((flag.option & NEO_KHZ400) != 0)? NEO_USART_HZ400 : NEO_USART_HZ800);
			USART_BaudrateSyncSet(((USART_TypeDef *)base), 0, freq);
			USART_Enable(((USART_TypeDef *)base), usartEnableTx);
			USART_SpiTransfer(((USART_TypeDef *)base), 0);//LOW pin
			freq = freq / 1000;
			if (freq != 0)
				freq = len * 8 / freq;
			break;
	}
	delayMicroseconds(NEO_RESET_MICROSECONDS);
	if (ZDMA.toMemoryPeripheral(&userLp, config->dmaSignal, config->dst, &list->array[0], len, zdmaData8) == ZunoErrorOk) {
		delay(freq);
		while (userLp.bProcessing == true)
			__NOP();
	}
	switch (config->type) {
		case NEO_TYPE_TIMER:
			TIMER_Enable(((TIMER_TypeDef *)base), false);
			break;
		case NEO_TYPE_USART:
			USART_Enable(((USART_TypeDef *)base), usartDisable);
			break;
	}
}

void NeoPixel::setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color) {
	ZunoNeoList_t			*list;

	if ((list = this->_findList(neo_pin)) == 0 || id_led >= list->count_led)
		return ;
	this->_setColor(list, id_led, color, list->brightness);
}

void NeoPixel::setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoList_t			*list;

	if ((list = this->_findList(neo_pin)) == 0 || id_led >= list->count_led)
		return ;
	this->_setColor(list, id_led, color, brightness);
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, USART_TypeDef *usart) {
	return (this->_addNeo(neo_pin, count_led, brightness, option, (size_t)usart));
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, TIMER_TypeDef *timer) {
	return (this->_addNeo(neo_pin, count_led, brightness, option, (size_t)timer));
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option) {
	return (this->addNeo(neo_pin, count_led, brightness, option, USART1));
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness) {
	return (this->addNeo(neo_pin, count_led, brightness, NEO_GRB | NEO_KHZ800));
}

ZunoError_t NeoPixel::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led) {
	return (this->addNeo(neo_pin, count_led, NEO_BRIGHTNESS_DEFAULT));
}

void NeoPixel::deleteNeo(uint8_t neo_pin) {
	this->_deleteNeo(neo_pin);
}

ZunoNeoColor_t NeoPixel::HSV(uint16_t hue) {
	this->HSV(hue, 100, 100);
}

ZunoNeoColor_t NeoPixel::HSV(uint16_t hue, uint8_t sat, uint8_t val) {
	float					r;
	float					g;
	float					b;
	ZunoNeoColor_t			color;
	float					x;
	float					m;
	float					c;
	float					v;

	if (sat > 100)
		sat = 100;
	if (val > 100)
		val = 100;
	if (hue > 360)
		hue = 360;
	v = (float)val / 100;
	c = v * ((float)sat / 100);
	x = c * (1 - fabsf(fmodf(((float)hue / 60), 2) - 1));
	m = v - c;
	if (hue >= 0 && hue < 60) {
		r = c;
		g = x;
		b = 0;
	} else if (hue >= 60 && hue < 120) {
		r = x;
		g = c;
		b = 0;
	}
	else if (hue >= 120 && hue < 180) {
		r = 0;
		g = c;
		b = x;
	}
	else if (hue >= 180 && hue < 240) {
		r = 0;
		g = x;
		b = c;
	}
	else if (hue >= 240 && hue < 300) {
		r = x;
		g = 0;
		b = c;
	} else {
		r = c;
		g = 0;
		b = x;
	}
	color.red = (r + m) * 255;
	color.green = (g + m) * 255;
	color.blue = (b + m) * 255;
	color.white = 0;
	return (color);
}

/* Private Methods */
void NeoPixel::_fill(ZunoNeoList_t *list, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoCountLed			count_led;

	count = count + first_id_led;
	if (count > list->count_led)
		return ;
	while (first_id_led < count)
		this->_setColor(list, first_id_led++, color, brightness);
}

void NeoPixel::_setColor(ZunoNeoList_t *list, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoOption_t				flag;
	const ZunoNeoTypeConfig_t	*config;
	uint8_t						*array;
	uint8_t						redOffset;
	uint8_t						whiteOffset;
	uint8_t						*lpRed;
	uint8_t						*lpWite;
	uint8_t						*lpGreen;
	uint8_t						*lpBlue;
	uint8_t						freq;
	uint8_t						one_hight;
	uint8_t						zero_hight;
	uint8_t						coder;

	if (++brightness != 0) {
		color.red = (color.red * brightness) >> 8;
		color.green = (color.green * brightness) >> 8;
		color.blue = (color.blue * brightness) >> 8;
		color.white = (color.white * brightness) >> 8;
	}
	flag = list->flag;
	redOffset = flag.redOffset;
	whiteOffset = flag.whiteOffset;
	config = list->config;
	coder = config->coder;
	array = &list->array[id_led * coder * ((redOffset == whiteOffset)? 3: 4)];
	lpRed = &array[redOffset * coder];
	lpWite = &array[whiteOffset * coder];
	lpGreen = &array[flag.greenOffset * coder];
	lpBlue = &array[flag.blueOffset * coder];
	switch (config->type) {
		case NEO_TYPE_TIMER:
			freq = list->freq_timer;
			one_hight = freq * (((flag.option & NEO_KHZ400) != 0)? NEO_ONE_HIGH_PERIOD_HZ400 : NEO_ONE_HIGH_PERIOD_HZ800) / NEO_FULL_PERIOD;
			zero_hight = freq * (((flag.option & NEO_KHZ400) != 0)? NEO_ZERO_HIGH_PERIOD_HZ400 : NEO_ZERO_HIGH_PERIOD_HZ800) / NEO_FULL_PERIOD;
			if (lpWite != lpRed)
				_setColorTimerCoder(lpWite, color.white, one_hight, zero_hight);
			_setColorTimerCoder(lpRed, color.red , one_hight, zero_hight);
			_setColorTimerCoder(lpGreen, color.green , one_hight, zero_hight);
			_setColorTimerCoder(lpBlue, color.blue , one_hight, zero_hight);
			break;
		case NEO_TYPE_USART:
			if (lpWite != lpRed)
				_setColorUsartCoder(lpWite, color.white);
			_setColorUsartCoder(lpRed, color.red);
			_setColorUsartCoder(lpGreen, color.green);
			_setColorUsartCoder(lpBlue, color.blue);
			break;
	}
}

ZunoError_t NeoPixel::_addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, size_t base) {
	const ZunoNeoTypeConfig_t		*config;
	ZunoNeoList_t					*list;
	size_t							len;
	ZunoNeoOption_t					flag;

	flag.option = option;
	this->_deleteNeo(neo_pin);
	pinMode(neo_pin, OUTPUT);
	switch (base) {
		case TIMER0_BASE:
			config = &timer0_config;
			if (this->_bInitTimer0++ == 0) {
				if (g_bit_field.bLockTimer0 == true) {
					return (ZunoErrorTimerAlredy);
				}
				g_bit_field.bLockTimer0 = true;
				_initTimer(neo_pin, config);
			}
			break ;
		case TIMER1_BASE:
			config = &timer1_config;
			if (this->_bInitTimer1++ == 0) {
				if (g_bit_field.bLockTimer1 == true) {
					return (ZunoErrorTimerAlredy);
				}
				g_bit_field.bLockTimer1 = true;
				_initTimer(neo_pin, config);
			}
			break ;
		case WTIMER0_BASE:
			config = &wtimer0_config;
			if (this->_bInitWTimer0++ == 0) {
				if (g_bit_field.bLockWTimer0 == true) {
					return (ZunoErrorTimerAlredy);
				}
				g_bit_field.bLockWTimer0 = true;
				_initTimer(neo_pin, config);
			}
			break ;
		case USART0_BASE:
			config = &usart0_config;
			if (this->_bInitUsart0++ == 0) {
				if (g_bit_field.bLockUsart0 == true) {
					return (ZunoErrorUsartAlredy);
				}
				g_bit_field.bLockUsart0 = true;
				_initUsart(neo_pin, config);
			}
			break ;
		case USART1_BASE:
			config = &usart1_config;
			if (this->_bInitUsart1++ == 0) {
				if (g_bit_field.bLockUsart1 == true) {
					return (ZunoErrorUsartAlredy);
				}
				g_bit_field.bLockUsart1 = true;
				_initUsart(neo_pin, config);
			}
			break ;
		case USART2_BASE:
			config = &usart2_config;
			if (this->_bInitUsart2++ == 0) {
				if (g_bit_field.bLockUsart2 == true) {
					return (ZunoErrorUsartAlredy);
				}
				g_bit_field.bLockUsart2 = true;
				_initUsart(neo_pin, config);
			}
			break ;
		default:
			return (ZunoErrorNeo);
			break ;
	}
	len = count_led * ((flag.redOffset == flag.whiteOffset) ? 3 : 4) * config->coder + 1;// + 1 LOW
	if ((list = (ZunoNeoList_t *)malloc(sizeof(ZunoNeoList_t) + len)) == 0) {
		return (ZunoErrorMemory);
	}
	memset(&list->array[0], 0, len);
	list->next = 0;
	list->count_led = count_led;
	list->neo_pin = neo_pin;
	list->flag.option = flag.option;
	list->brightness = brightness;
	list->config = config;
	if (config->type == NEO_TYPE_TIMER)
		list->freq_timer = CMU_ClockFreqGet(config->bus_clock) / (((flag.option & NEO_KHZ400) != 0)? NEO_TIMER_HZ400 : NEO_TIMER_HZ800);//0x25317C0
	this->_addList(list);
	return (ZunoErrorOk);
}

void NeoPixel::_deleteNeo(uint8_t neo_pin) {
	ZunoNeoList_t		*list;
	ZunoNeoList_t		*list_prev;
	ZunoNeoList_t		*list_tmp;

	if ((list = this->_findList(neo_pin)) == 0)
		return ;
	switch (list->config->base) {
		case TIMER0_BASE:
			if (--this->_bInitTimer0 == 0)
				g_bit_field.bLockTimer0 = false;
			break ;
		case TIMER1_BASE:
			if (--this->_bInitTimer1 == 0)
				g_bit_field.bLockTimer1 = false;
			break ;
		case WTIMER0_BASE:
			if (--this->_bInitWTimer0 == 0)
				g_bit_field.bLockWTimer0 = false;
			break ;
		case USART0_BASE:
			if (--this->_bInitUsart0 == 0)
				g_bit_field.bLockUsart0 = false;
			break ;
		case USART1_BASE:
			if (--this->_bInitUsart1 == 0)
				g_bit_field.bLockUsart1 = false;
			break ;
		case USART2_BASE:
			if (--this->_bInitUsart2 == 0)
				g_bit_field.bLockUsart2 = false;
			break ;
	}
	list_prev = this->_list;
	if (list == list_prev)
		this->_list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
	free(list);
}

ZunoNeoList_t *NeoPixel::_findList(uint8_t neo_pin) {
	ZunoNeoList_t			*list;

	list = this->_list;
	while (list != 0) {
		if (list->neo_pin == neo_pin)
			break ;
		list = list->next;
	}
	return (list);
}

inline void NeoPixel::_addList(ZunoNeoList_t *list) {
	ZunoNeoList_t			*list_next;
	ZunoNeoList_t			*list_tmp;

	if ((list_next = this->_list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_list = list;
}


/* Preinstantiate Objects */
NeoPixel Neo = NeoPixel();