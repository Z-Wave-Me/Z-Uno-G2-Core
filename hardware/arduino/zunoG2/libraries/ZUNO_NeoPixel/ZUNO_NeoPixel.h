#ifndef ZUNO_NEOPIXEL_H
#define ZUNO_NEOPIXEL_H

#include "ZUNO_NeoPixel_define.h"
#include "Sync.h"

typedef enum							ZunoNeoBase_e
{
	ZunoNeoBaseUsart0,
	ZunoNeoBaseUsart1,
	ZunoNeoBaseUsart2,
	ZunoNeoBaseTimer0,
	ZunoNeoBaseTimer1,
	ZunoNeoBaseWTimer0
}										ZunoNeoBase_t;

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

typedef struct							ZunoNeoBaseConfig_s
{
	union
	{
		size_t							base;
		USART_TypeDef					*usart;
		TIMER_TypeDef					*timer;
	};
	ZunoSync_t							*lpLock;
	void								*dst;
	ZDMA_PeripheralSignal_t				dmaSignal;
	CMU_Clock_TypeDef					bus_clock;
	uint8_t								type;
	uint8_t								coder;
}										ZunoNeoBaseConfig_t;

typedef struct							ZunoNeoList_s
{
	struct ZunoNeoList_s				*next;
	ZunoNeoCountLed						count_led;
	ZunoNeoOption_t						flag;
	ZunoNeoBase_t						base;
	uint8_t								neo_pin;
	uint8_t								brightness;
	uint8_t								freq_timer;
	uint8_t								array[];
}										ZunoNeoList_t;

class NeoPixel {
	public:
		NeoPixel(void);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option, ZunoNeoBase_t base);
		inline ZunoError_t				addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness, ZunoNeoOptionMax_t option) {return (this->addNeo(neo_pin, count_led, brightness, option, ZunoNeoBaseUsart1));};
		inline ZunoError_t				addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint8_t brightness) {return (this->addNeo(neo_pin, count_led, brightness, NEO_GRB | NEO_KHZ800));};
		inline ZunoError_t				addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led) {return (this->addNeo(neo_pin, count_led, NEO_BRIGHTNESS_DEFAULT));};
		void							deleteNeo(uint8_t neo_pin);
		void							show(uint8_t neo_pin);
		void							fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness);
		void							fill(uint8_t neo_pin, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color);
		void							clear(uint8_t neo_pin);
		void							setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color);
		void							setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness);
		inline ZunoNeoColor_t			HSV(uint16_t hue) {this->HSV(hue, 100, 100);};
		ZunoNeoColor_t					HSV(uint16_t hue, uint8_t sat, uint8_t val);
		inline uint8_t					gamma(uint8_t x) {return (gNeoGammaTable[x]);};
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
		inline ZunoNeoList_t						*_fillPre(uint8_t neo_pin, volatile uint8_t *lpKey);
		inline ZunoNeoList_t						*_setColorPre(uint8_t neo_pin, ZunoNeoCountLed id_led, volatile uint8_t *lpKey);
		inline uint8_t								_getLocationWtimer(uint8_t pin, uint8_t ch);
		inline void									_setColorTimerCoder(uint8_t *b, uint8_t color, uint8_t one_hight, uint8_t zero_hight);
		inline void									_setColorUsartCoder(uint8_t *b, uint8_t color);
		inline void									_deleteNeo(uint8_t neo_pin);
		inline void									_fill(ZunoNeoList_t *list, ZunoNeoCountLed first_id_led, ZunoNeoCountLed count, ZunoNeoColor_t color, uint8_t brightness);
		inline void									_setColor(ZunoNeoList_t *list, ZunoNeoCountLed id_led, ZunoNeoColor_t color, uint8_t brightness);
		inline void									_showTimer(ZunoNeoList_t *list, ZunoNeoOption_t flag, uint8_t neo_pin);
		inline ZunoNeoList_t						*_findList(uint8_t neo_pin);
		inline void									_cutList(ZunoNeoList_t *list);
		inline void									_addList(ZunoNeoList_t *list);
		static ZunoError_t							_init(size_t param);
		static const ZunoNeoBaseConfig_t			_configTable[];
		static const USART_InitSync_TypeDef			_initSpi;
		static ZunoNeoList_t						*_list;
		static ZunoSync_t							_syncNeo;
};


extern NeoPixel Neo;

#endif //ZUNO_NEOPIXEL_H