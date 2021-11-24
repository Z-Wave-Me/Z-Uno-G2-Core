#include "Arduino.h"
#include "CrtxCmu.h"
#include "stdlib.h"
#include "LdmaClass.h"
#include "ZUNO_NeoPixel.h"
#include <math.h>

#define NEO_RESET_MICROSECONDS			50

#define NEO_FULL_PERIOD					100
#define NEO_ZERO_HIGH_PERIOD_HZ800		32
#define NEO_ONE_HIGH_PERIOD_HZ800		64
#define NEO_ZERO_HIGH_PERIOD_HZ400		20
#define NEO_ONE_HIGH_PERIOD_HZ400		50
#define NEO_MAX_TIMER_COUNT_LED			85

#define NEO_TIMER_HZ800					800000
#define NEO_TIMER_HZ400					400000
#define NEO_TIMER_CHANNEL				0

#define NEO_USART_HZ800					3840000
#define NEO_USART_HZ400					1950000

#define NEO_CODER_1TO8					(8 / 1)
#define NEO_CODER_1TO4					(8 / 2)

#define NEO_TYPE_USART					0x1
#define NEO_TYPE_TIMER					0x2

/* Constants */
const ZunoNeoBaseConfig_t NeoPixelClass::_configTable[] =
{
	{
		{.usart = USART0},
		.lpLock = &gSyncUSART0,
		.dst = (void *)&(USART0->TXDATA),
		.dmaSignal = LdmaClassSignal_USART0_TXBL,
		.bus_clock = cmuClock_USART0,
		.type = NEO_TYPE_USART,
		.coder = NEO_CODER_1TO4
	},
	{
		{.usart = USART1},
		.lpLock = &gSyncUSART1,
		.dst = (void *)&(USART1->TXDATA),
		.dmaSignal = LdmaClassSignal_USART1_TXBL,
		.bus_clock = cmuClock_USART1,
		.type = NEO_TYPE_USART,
		.coder = NEO_CODER_1TO4
	},
	{
		{.usart = USART2},
		.lpLock = &gSyncUSART2,
		.dst = (void *)&(USART2->TXDATA),
		.dmaSignal = LdmaClassSignal_USART2_TXBL,
		.bus_clock = cmuClock_USART2,
		.type = NEO_TYPE_USART,
		.coder = NEO_CODER_1TO4
	},
	{
		{.timer = TIMER0},
		.lpLock = &gSyncTIMER0,
		.dst = (void *)&(TIMER0->CC[NEO_TIMER_CHANNEL].CCVB),
		.dmaSignal = LdmaClassSignal_TIMER0_UFOF,
		.bus_clock = cmuClock_TIMER0,
		.type = NEO_TYPE_TIMER,
		.coder = NEO_CODER_1TO8
	},
	{
		{.timer = TIMER1},
		.lpLock = &gSyncTIMER1,
		.dst = (void *)&(TIMER1->CC[NEO_TIMER_CHANNEL].CCVB),
		.dmaSignal = LdmaClassSignal_TIMER1_UFOF,
		.bus_clock = cmuClock_TIMER1,
		.type = NEO_TYPE_TIMER,
		.coder = NEO_CODER_1TO8
	},
	{
		{.timer = WTIMER0},
		.lpLock = &gSyncWTIMER0,
		.dst = (void *)&(WTIMER0->CC[NEO_TIMER_CHANNEL].CCVB),
		.dmaSignal = LdmaClassSignal_WTIMER0_UFOF,
		.bus_clock = cmuClock_WTIMER0,
		.type = NEO_TYPE_TIMER,
		.coder = NEO_CODER_1TO8
	}
};

const USART_InitSync_TypeDef NeoPixelClass::_initSpi =
{
	.enable = usartDisable,
	.refFreq = 0,
	.baudrate = 1000000,
	.databits = usartDatabits8,
	.master = true,
	.msbf = false,
	.clockMode = usartClockMode0,
	.prsRxEnable = false,
	.prsRxCh = 0,
	.autoTx = false,
	.autoCsEnable = false,
	.autoCsHold = 0,
	.autoCsSetup = 0
};


/* Values */
ZunoNeoList_t *NeoPixelClass::_list = 0;

ZunoSync_t NeoPixelClass::_syncNeo = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterNeoPixel);

/* Public Constructors */
NeoPixelClass::NeoPixelClass(void) {
}

/* Public Methods */
ZunoError_t NeoPixelClass::addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, ZunoNeoBase_t base) {
	const ZunoNeoBaseConfig_t		*config;
	ZunoNeoList_t					*list;
	size_t							len;
	ZunoNeoOption_t					flag;
	ZunoError_t						ret;
	ZunoNeoColor_t					color;
	volatile uint8_t				lpKey;

	if (neo_pin > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	if (base >= sizeof(this->_configTable) / sizeof(ZunoNeoBaseConfig_t))
		return (ZunoErrorNeo);
	config = &this->_configTable[base];
	flag.option = option;
	len = count_led * ((flag.redOffset == flag.whiteOffset) ? 3 : 4) * config->coder + 1;// + 1 LOW
	if ((list = (ZunoNeoList_t *)malloc(sizeof(ZunoNeoList_t) + len)) == 0) {
		return (ZunoErrorMemory);
	}
	list->array[len - 0x1] = 0x0;// + 1 LOW
	list->next = 0;
	list->count_led = count_led;
	list->neo_pin = neo_pin;
	list->flag.option = flag.option;
	list->brightness = brightness;
	list->base = base;
	lpKey = false;
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterNeoPixel, this->_init, (size_t)config, &lpKey)) != ZunoErrorOk) {
		free(list);
		return (ret);
	}
	if (config->type == NEO_TYPE_TIMER)
		list->freq_timer = CMU_ClockFreqGet(config->bus_clock) / (((flag.option & NEO_KHZ400) != 0)? NEO_TIMER_HZ400 : NEO_TIMER_HZ800);//0x25317C0
	pinMode(neo_pin, OUTPUT);
	zunoSyncReleseWrite(config->lpLock, SyncMasterNeoPixel, &lpKey);
	zunoSyncLockWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
	this->_deleteNeo(neo_pin);
	this->_addList(list);
	color.color = 0x0;
	this->_fill(list, 0x0,list->count_led, color, 0x0);
	zunoSyncReleseWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
	return (ZunoErrorOk);
}

void NeoPixelClass::fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoList_t					*list;
	volatile uint8_t				lpKey;

	if ((list = this->_fillPre(neo_pin, &lpKey)) != 0)
		this->_fill(list, first_id_led, count, color, brightness);
	zunoSyncReleseRead(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color) {
	ZunoNeoList_t					*list;

	volatile uint8_t				lpKey;

	if ((list = this->_fillPre(neo_pin, &lpKey)) != 0)
		this->_fill(list, first_id_led, count, color, list->brightness);
	zunoSyncReleseRead(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::clear(uint8_t neo_pin) {
	ZunoNeoList_t					*list;
	ZunoNeoColor_t					color;

	volatile uint8_t				lpKey;

	if ((list = this->_fillPre(neo_pin, &lpKey)) != 0) {
		color.color = 0;
		this->_fill(list, 0, list->count_led, color, list->brightness);
	}
	zunoSyncReleseRead(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::show(uint8_t neo_pin) {
	size_t							base;
	ZunoNeoList_t					*list;
	const ZunoNeoBaseConfig_t		*config;
	ZunoNeoOption_t					flag;
	ZunoNeoCountLed					len;
	volatile uint8_t				lpKey;
	const uint8_t					*location_ptr;
	size_t							location_sz;
	ssize_t							channel;
	LdmaClassTransferSingle_t		array;

	lpKey = true;
	zunoSyncLockWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
	if ((list = this->_findList(neo_pin)) != 0 && (len = list->count_led) != 0) {
		flag = list->flag;
		config = &this->_configTable[list->base];
		len = len * (flag.redOffset == flag.whiteOffset ? 3 : 4) * config->coder;
		base = config->base;
		switch (config->type) {
			case NEO_TYPE_TIMER:
				len++;// + 1 LOW
				TIMER_TopSet(((TIMER_TypeDef *)base), list->freq_timer);
				if (((TIMER_TypeDef *)base) == WTIMER0) {
					((TIMER_TypeDef *)base)->ROUTELOC0 = _getLocationWtimer(neo_pin, NEO_TIMER_CHANNEL);
				}
				else
					((TIMER_TypeDef *)base)->ROUTELOC0 = getLocationTimer0AndTimer1Chanell(neo_pin, NEO_TIMER_CHANNEL);
				TIMER_CompareBufSet(((TIMER_TypeDef *)base), NEO_TIMER_CHANNEL, 0);// + 1 LOW
				TIMER_Enable(((TIMER_TypeDef *)base), true);
				break;
			case NEO_TYPE_USART:
				if ((USART_TypeDef *)base == USART2) {
					location_ptr = g_loc_pa5_pf0_pf1_pf3_pf7;// USART2 has a cropped location set
					location_sz = sizeof(g_loc_pa5_pf0_pf1_pf3_pf7);
				}
				else {
					location_ptr = g_loc_pa0_pf7_all;
					location_sz = sizeof(g_loc_pa0_pf7_all);
				}
				((USART_TypeDef *)base)->ROUTELOC0 = getLocation(location_ptr, location_sz, neo_pin) << _USART_ROUTELOC0_TXLOC_SHIFT;
				USART_BaudrateSyncSet(((USART_TypeDef *)base), 0, (((flag.option & NEO_KHZ400) != 0)? NEO_USART_HZ400 : NEO_USART_HZ800));
				USART_Enable(((USART_TypeDef *)base), usartEnableTx);
				break;
		}
		delayMicroseconds(NEO_RESET_MICROSECONDS);
		if ((channel = LdmaClass::transferSingle(&list->array[0], config->dst, len, config->dmaSignal, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) > 0x0)
			while (LdmaClass::transferDone(channel) == false)
				delay(0x1);
		switch (config->type) {
			case NEO_TYPE_TIMER:
				TIMER_Enable(((TIMER_TypeDef *)base), false);
				break;
			case NEO_TYPE_USART:
				while (!(((USART_TypeDef *)base)->STATUS & USART_STATUS_TXC))//Waiting for the last byte to go before we finish the transfer protocol
					__NOP();
				USART_Enable(((USART_TypeDef *)base), usartDisable);
				break;
		}
	}
	zunoSyncReleseWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color) {
	ZunoNeoList_t					*list;
	volatile uint8_t				lpKey;

	if ((list = this->_setColorPre(neo_pin, id_led, &lpKey)) != 0)
		this->_setColor(list, id_led, color, list->brightness);
	zunoSyncReleseRead(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoList_t					*list;
	volatile uint8_t				lpKey;

	if ((list = this->_setColorPre(neo_pin, id_led, &lpKey)) != 0)
		this->_setColor(list, id_led, color, brightness);
	zunoSyncReleseRead(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

void NeoPixelClass::deleteNeo(uint8_t neo_pin) {
	volatile uint8_t				lpKey;

	lpKey = true;
	zunoSyncLockWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
	this->_deleteNeo(neo_pin);
	zunoSyncReleseWrite(&this->_syncNeo, SyncMasterNeoPixel, &lpKey);
}

ZunoNeoColor_t NeoPixelClass::HSV(uint16_t hue, uint8_t sat, uint8_t val) {
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
	if (hue < 60) {
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

ZunoNeoColor_t NeoPixelClass::ColorHSV(uint16_t hue, uint8_t sat, uint8_t val) {
	ZunoNeoColor_t			color;
	uint8_t r, g, b;

	// Remap 0-65535 to 0-1529. Pure red is CENTERED on the 64K rollover;
	// 0 is not the start of pure red, but the midpoint...a few values above
	// zero and a few below 65536 all yield pure red (similarly, 32768 is the
	// midpoint, not start, of pure cyan). The 8-bit RGB hexcone (256 values
	// each for red, green, blue) really only allows for 1530 distinct hues
	// (not 1536, more on that below), but the full unsigned 16-bit type was
	// chosen for hue so that one's code can easily handle a contiguous color
	// wheel by allowing hue to roll over in either direction.
	hue = (hue * 1530L + 32768) / 65536;
	// Because red is centered on the rollover point (the +32768 above,
	// essentially a fixed-point +0.5), the above actually yields 0 to 1530,
	// where 0 and 1530 would yield the same thing. Rather than apply a
	// costly modulo operator, 1530 is handled as a special case below.

	// So you'd think that the color "hexcone" (the thing that ramps from
	// pure red, to pure yellow, to pure green and so forth back to red,
	// yielding six slices), and with each color component having 256
	// possible values (0-255), might have 1536 possible items (6*256),
	// but in reality there's 1530. This is because the last element in
	// each 256-element slice is equal to the first element of the next
	// slice, and keeping those in there this would create small
	// discontinuities in the color wheel. So the last element of each
	// slice is dropped...we regard only elements 0-254, with item 255
	// being picked up as element 0 of the next slice. Like this:
	// Red to not-quite-pure-yellow is:        255,   0, 0 to 255, 254,   0
	// Pure yellow to not-quite-pure-green is: 255, 255, 0 to   1, 255,   0
	// Pure green to not-quite-pure-cyan is:     0, 255, 0 to   0, 255, 254
	// and so forth. Hence, 1530 distinct hues (0 to 1529), and hence why
	// the constants below are not the multiples of 256 you might expect.

	// Convert hue to R,G,B (nested ifs faster than divide+mod+switch):
	if(hue < 510) {         // Red to Green-1
		b = 0;
		if(hue < 255) {       //   Red to Yellow-1
		r = 255;
		g = hue;            //     g = 0 to 254
		} else {              //   Yellow to Green-1
		r = 510 - hue;      //     r = 255 to 1
		g = 255;
		}
	} else if(hue < 1020) { // Green to Blue-1
		r = 0;
		if(hue <  765) {      //   Green to Cyan-1
		g = 255;
		b = hue - 510;      //     b = 0 to 254
		} else {              //   Cyan to Blue-1
		g = 1020 - hue;     //     g = 255 to 1
		b = 255;
		}
	} else if(hue < 1530) { // Blue to Red-1
		g = 0;
		if(hue < 1275) {      //   Blue to Magenta-1
		r = hue - 1020;     //     r = 0 to 254
		b = 255;
		} else {              //   Magenta to Red-1
		r = 255;
		b = 1530 - hue;     //     b = 255 to 1
		}
	} else {                // Last 0.5 Red (quicker than % operator)
		r = 255;
		g = b = 0;
	}

	// Apply saturation and value to R,G,B, pack into 32-bit result:
	uint32_t v1 =   1 + val; // 1 to 256; allows >>8 instead of /255
	uint16_t s1 =   1 + sat; // 1 to 256; same reason
	uint8_t  s2 = 255 - sat; // 255 to 0
	color.red = ((((r * s1) >> 8) + s2) * v1) >> 8;
	color.green = ((((g * s1) >> 8) + s2) * v1) >> 8;
	color.blue = ((((b * s1) >> 8) + s2) * v1) >> 8;
	color.white = 0x0;
	return (color);
}

ZunoNeoColor_t NeoPixelClass::gamma32(ZunoNeoColor_t color) {
	color.red = this->gamma8(color.red);
	color.green = this->gamma8(color.green);
	color.blue = this->gamma8(color.blue);
	color.white = this->gamma8(color.white);
	return (color);
}

/* Private Methods */
inline ZunoNeoList_t *NeoPixelClass::_fillPre(uint8_t neo_pin, volatile uint8_t *lpKey) {
	lpKey[0] = true;
	zunoSyncLockRead(&this->_syncNeo, SyncMasterNeoPixel, lpKey);
	return (this->_findList(neo_pin));
}

inline void NeoPixelClass::_fill(ZunoNeoList_t *list, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness) {

	count = count + first_id_led;
	if (count > list->count_led)
		return ;
	while (first_id_led < count)
		this->_setColor(list, first_id_led++, color, brightness);
}

inline ZunoNeoList_t *NeoPixelClass::_setColorPre(uint8_t neo_pin, ZunoNeoCountLed id_led, volatile uint8_t *lpKey) {
	ZunoNeoList_t			*list;

	lpKey[0] = true;
	zunoSyncLockRead(&this->_syncNeo, SyncMasterNeoPixel, lpKey);
	if ((list = this->_findList(neo_pin)) == 0 || id_led >= list->count_led)
		return (0);
	return (list);
}

inline void NeoPixelClass::_setColor(ZunoNeoList_t *list, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness) {
	ZunoNeoOption_t				flag;
	const ZunoNeoBaseConfig_t	*config;
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
	config = &this->_configTable[list->base];
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
				this->_setColorTimerCoder(lpWite, color.white, one_hight, zero_hight);
			this->_setColorTimerCoder(lpRed, color.red , one_hight, zero_hight);
			this->_setColorTimerCoder(lpGreen, color.green , one_hight, zero_hight);
			this->_setColorTimerCoder(lpBlue, color.blue , one_hight, zero_hight);
			break;
		case NEO_TYPE_USART:
			if (lpWite != lpRed)
				this->_setColorUsartCoder(lpWite, color.white);
			this->_setColorUsartCoder(lpRed, color.red);
			this->_setColorUsartCoder(lpGreen, color.green);
			this->_setColorUsartCoder(lpBlue, color.blue);
			break;
	}
}

inline ZunoNeoList_t *NeoPixelClass::_findList(uint8_t neo_pin) {
	ZunoNeoList_t			*list;

	list = this->_list;
	while (list != 0) {
		if (list->neo_pin == neo_pin)
			break ;
		list = list->next;
	}
	return (list);
}

inline void NeoPixelClass::_cutList(ZunoNeoList_t *list) {
	ZunoNeoList_t		*list_prev;
	ZunoNeoList_t		*list_tmp;

	list_prev = this->_list;
	if (list == list_prev)
		this->_list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
}

inline void NeoPixelClass::_addList(ZunoNeoList_t *list) {
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

inline void NeoPixelClass::_deleteNeo(uint8_t neo_pin) {
	ZunoNeoList_t					*list;
	volatile uint8_t				lpKey;

	if ((list = this->_findList(neo_pin)) != 0) {
		this->_cutList(list);
		lpKey = true;
		zunoSyncClose(this->_configTable[list->base].lpLock, SyncMasterNeoPixel, 0, 0, &lpKey);
		free(list);
	}
}

ZunoError_t NeoPixelClass::_init(size_t param) {
	const ZunoNeoBaseConfig_t			*config;
	USART_TypeDef						*usart;
	TIMER_Init_TypeDef					timerInit;
	TIMER_InitCC_TypeDef				timerCCInit;
	TIMER_TypeDef						*timer;
	size_t								base;

	config = (const ZunoNeoBaseConfig_t *)param;
	CMU_ClockEnable(config->bus_clock, true);
	base = config->base;
	switch (config->type) {
		case NEO_TYPE_TIMER:
			timerCCInit = TIMER_INITCC_DEFAULT;
			timerCCInit.mode = timerCCModePWM;
			timer = (TIMER_TypeDef *)base;
			TIMER_InitCC(timer, NEO_TIMER_CHANNEL, &timerCCInit);
			timerInit = TIMER_INIT_DEFAULT;
			timerInit.enable = false;
			timerInit.dmaClrAct = true;
			TIMER_Init(timer, &timerInit);
			timer->ROUTEPEN = (1UL << NEO_TIMER_CHANNEL);//enabled CC
			break ;
		default:
			usart = (USART_TypeDef *)base;
			USART_InitSync(usart, &NeoPixelClass::_initSpi);
			usart->ROUTEPEN = USART_ROUTEPEN_TXPEN;
			break ;
	}
	return (ZunoErrorOk);
}

inline uint8_t NeoPixelClass::_getLocationWtimer(uint8_t pin, uint8_t ch) {
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

inline void NeoPixelClass::_setColorTimerCoder(uint8_t *b, uint8_t color, uint8_t one_hight, uint8_t zero_hight) {
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

inline void NeoPixelClass::_setColorUsartCoder(uint8_t *b, uint8_t color) {
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

/* Preinstantiate Objects */
NeoPixelClass NeoPixel = NeoPixelClass();