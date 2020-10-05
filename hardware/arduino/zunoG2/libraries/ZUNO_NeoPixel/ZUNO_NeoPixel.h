#ifndef ZUNO_NEOPIXEL_H
#define ZUNO_NEOPIXEL_H

#include "ZUNO_NeoPixel_define.h"
#include "ZUNO_NeoPixel_private.h"


class NeoPixel {
	public:
		NeoPixel(void);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led, uint16_t type);
		ZunoError_t						addNeo(uint8_t neo_pin, ZunoNeoCountLed count_led);
		void							deleteNeo(uint8_t neo_pin);
		void							show(uint8_t neo_pin);
		void							setColor(uint8_t neo_pin, ZunoNeoCountLed id_led, ZunoNeoColor_t color);
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
		static void						_timer_handler(void);
		inline void						_showTimer(ZunoNeoList_t *list, ZunoNeoType_t flag, uint8_t neo_pin);
		ZunoNeoList_t					*_findList(uint8_t neo_pin);
		inline void						_addList(ZunoNeoList_t *list);
		void							_deleteNeo(ZunoNeoList_t *list);
		ZunoNeoList_t				*list;
		ZunoNeoSave_t				save;
		uint8_t						freq;
		uint8_t						bHandlerTimer: 1;
};


extern NeoPixel Neo;

#endif //ZUNO_NEOPIXEL_H