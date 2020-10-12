#ifndef ZUNO_NEOPIXEL_H
#define ZUNO_NEOPIXEL_H

#include "ZUNO_NeoPixel_define.h"


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
};


extern NeoPixel Neo;

#endif //ZUNO_NEOPIXEL_H