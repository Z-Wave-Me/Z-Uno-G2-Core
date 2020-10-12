#ifndef ZUNO_NEOPIXEL_PRIVATE_H
#define ZUNO_NEOPIXEL_PRIVATE_H

#define NEO_RESET_MICROSECONDS			50

#define NEO_FULL_PERIOD					100
#define NEO_ZERO_HIGH_PERIOD_HZ800		32
#define NEO_ONE_HIGH_PERIOD_HZ800		64
#define NEO_ZERO_HIGH_PERIOD_HZ400		20
#define NEO_ONE_HIGH_PERIOD_HZ400		50

#define NEO_TIMER_HZ800					800000
#define NEO_TIMER_HZ400					400000
#define NEO_TIMER_CHANNEL				0

#define NEO_USART_HZ800					3840000
#define NEO_USART_HZ400					1950000

#define NEO_CODER_1TO8					(8 / 1)
#define NEO_CODER_1TO4					(8 / 2)

#define NEO_TYPE_USART					0x1
#define NEO_TYPE_TIMER					0x2

typedef union							ZunoNeoOption_u
{
	ZunoNeoOptionMax_t					option;
	struct
	{
		uint16_t						blueOffset: 2;
		uint16_t						greenOffset: 2;
		uint16_t						redOffset : 2;
		uint16_t						whiteOffset : 2;
	};
}										ZunoNeoOption_t;

typedef struct							ZunoNeoTypeConfig_s
{
	union
	{
		size_t							base;
		USART_TypeDef					*usart;
		TIMER_TypeDef					*timer;
	};
	void								*dst;
	ZDMA_PeripheralSignal_t				dmaSignal;
	CMU_Clock_TypeDef					bus_clock;
	uint8_t								type;
	uint8_t								coder;
}										ZunoNeoTypeConfig_t;

typedef struct							ZunoNeoList_s
{
	struct ZunoNeoList_s				*next;
	const ZunoNeoTypeConfig_t			*config;
	ZunoNeoCountLed						count_led;
	ZunoNeoOption_t						flag;
	uint8_t								neo_pin;
	uint8_t								brightness;
	uint8_t								freq_timer;
	uint8_t								array[];
}										ZunoNeoList_t;

class NeoPixel {
	public:
		NeoPixel(void);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, USART_TypeDef *usart);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, TIMER_TypeDef *timer);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led);
		void							deleteNeo(uint8_t neo_pin);
		void							show(uint8_t neo_pin);
		void							fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness);
		void							fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color);
		void							clear(uint8_t neo_pin);
		void							setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color);
		void							setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness);
		ZunoNeoColor_t					HSV(uint16_t hue);
		ZunoNeoColor_t					HSV(uint16_t hue, uint8_t sat, uint8_t val);
		inline uint8_t					gamma(uint8_t x) {
			return (gNeoGammaTable[x]);
		};
		inline ZunoNeoColor_t			RGB(uint8_t red, uint8_t green, uint8_t blue) {
			ZunoNeoColor_t				color;

			color.red = red;
			color.green = green;
			color.blue = blue;
			color.white = 0;
			return (color);
		};
		inline ZunoNeoColor_t			RGBW(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
			ZunoNeoColor_t				color;

			color.red = red;
			color.green = green;
			color.blue = blue;
			color.white = white;
			return (color);
		}

	private:
		void							_deleteNeo(uint8_t neo_pin);
		void							_fill(ZunoNeoList_t *list, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness);
		void							_setColor(ZunoNeoList_t *list, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness);
		ZunoError_t						_addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, size_t base);
		inline void						_showTimer(ZunoNeoList_t *list, ZunoNeoOption_t flag, uint8_t neo_pin);
		ZunoNeoList_t					*_findList(uint8_t neo_pin);
		inline void						_addList(ZunoNeoList_t *list);
		ZunoNeoList_t					*_list;
		uint8_t							_bInitTimer0;
		uint8_t							_bInitTimer1;
		uint8_t							_bInitWTimer0;
		uint8_t							_bInitUsart0;
		uint8_t							_bInitUsart1;
		uint8_t							_bInitUsart2;
};


extern NeoPixel Neo;


#endif //ZUNO_NEOPIXEL_PRIVATE_H