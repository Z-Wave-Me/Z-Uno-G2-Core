#ifndef _ZUNO_GFX_H_
#define _ZUNO_GFX_H_

#include "Arduino.h"

typedef struct GLCDfonts_s
{
	uint8_t		width;
	uint8_t		height;
	uint8_t		start_sim;
	uint8_t		*font_buf;
}				GLCDfonts;

class ZUNO_GFX : public Print
{
	protected:
		uint16_t	cur_x;
		uint16_t	cur_y;
		uint16_t	s_width;
		uint16_t	s_height;	
		GLCDfonts	*font;
		void printChar(uint8_t ch);
		
	private:
	public:
		uint8_t		*buffer;
		size_t		buff_size;
		ZUNO_GFX(uint16_t width, uint16_t height);
		~ZUNO_GFX();
		using	Print::write;
		virtual size_t write(const uint8_t *buffer, size_t size);
		virtual uint8_t write(uint8_t);
		virtual void drawPixel(int16_t x, int16_t y, uint8_t color);
		void writePixel(int16_t x, int16_t y, uint8_t color);
		void drawBitmap(uint16_t x, uint16_t y,uint8_t w, uint8_t h,
												 uint8_t *pic, uint8_t color);
		void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
		void writeFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
		void writeFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
		void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
		void fillScreen(uint8_t color);
		void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
		void drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
											uint8_t cornername, uint8_t color);
		void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
		void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
								uint8_t corners, int16_t delta, uint8_t color);
		void	setFont(uint8_t *font_name);
		void	clearDisp() {memset(buffer, 0x00, buff_size);};
		int16_t	width(void) const { return s_width; };
		int16_t	height(void) const { return s_height; };
		int16_t	getCursorX(void) const { return cur_x; };
		int16_t	getCursorY(void) const { return cur_y; };
		void	setCursor(uint16_t x, uint16_t y) {cur_x = x; cur_y = y;};
		uint8_t *getBuffer() {return buffer;};
};

#endif