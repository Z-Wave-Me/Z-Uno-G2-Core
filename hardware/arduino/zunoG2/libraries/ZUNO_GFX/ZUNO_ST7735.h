#ifndef __ZUNO_S7735__
#define __ZUNO_S7735__

#include "ZUNO_GFX.h"
#include "SPI.h"

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 160

#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0  
#define WHITE     0xFFFF 

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_RGB444  0x03
#define ST7735_RGB565  0x05
#define ST7735_RGB666  0x06

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

class ZUNO_ST7735 : public ZUNO_GFX
{
	private:
		uint8_t _cs;
		uint8_t _rst;
		uint8_t _ds;
		uint8_t _width;
		uint8_t _height;

	public:
		void command(uint8_t cmd);
		ZUNO_ST7735(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect,
									uint8_t width = 160, uint8_t height = 128);
		void begin();
		void LCD_Fill(uint16_t color);
		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void data(uint8_t data);
		void data16(uint16_t data);
		void data(uint8_t *data, size_t size);
		void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
};

#endif