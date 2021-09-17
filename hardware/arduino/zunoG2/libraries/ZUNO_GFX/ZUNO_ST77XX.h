#ifndef __ZUNO_S77XX__
#define __ZUNO_S77XX__

#include "ZUNO_GFX.h"
#include "SPI.h"

#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0  
#define WHITE     0xFFFF 

#define ST77XX_COL_BGR 0xA8
#define ST77XX_COL_RGB 0xA0

#define ST77XX_NOP     0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID   0x04
#define ST77XX_RDDST   0x09

#define ST77XX_SLPIN   0x10
#define ST77XX_SLPOUT  0x11
#define ST77XX_PTLON   0x12
#define ST77XX_NORON   0x13

#define ST77XX_PTLAR   0x30
#define ST77XX_COLMOD  0x3A
#define ST77XX_MADCTL  0x36

#define ST77XX_RGB444  0x03
#define ST77XX_RGB565  0x05
#define ST77XX_RGB666  0x06

#define ST77XX_FRMCTR1 0xB1
#define ST77XX_FRMCTR2 0xB2
#define ST77XX_FRMCTR3 0xB3
#define ST77XX_INVCTR  0xB4
#define ST77XX_DISSET5 0xB6

#define ST77XX_INVOFF  0x20
#define ST77XX_INVON   0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON  0x29
#define ST77XX_CASET   0x2A
#define ST77XX_RASET   0x2B
#define ST77XX_RAMWR   0x2C
#define ST77XX_RAMRD   0x2E

class ZUNO_ST77XX : public ZUNO_GFX
{
	private:
		uint8_t _cs;
		uint8_t _rst;
		uint8_t _ds;
		uint8_t _width;
		uint8_t _height;
		uint8_t _shift_h;
		uint8_t _shift_w;
		uint8_t _color_mode;
		uint8_t _inv_mode;


	public:
		void command(uint8_t cmd);
		ZUNO_ST77XX(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect,
				uint8_t width = 160, uint8_t height = 128, uint8_t color_mode = ST77XX_COL_RGB, 
							uint8_t inv_mode = ST77XX_INVOFF, uint8_t shift_h = 2, uint8_t shift_w = 1);
		void begin();
		void LCD_Fill(uint16_t color);
		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void data(uint8_t data);
		void data16(uint16_t data);
		void data(uint8_t *data, size_t size);
		void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
		void drawImage_1bpp(uint16_t x, uint16_t y, uint8_t *img,uint16_t color, 
																uint32_t bg_color = -1);
};

class ZUNO_ST7735_128_160 : public ZUNO_ST77XX
{
	public:
	ZUNO_ST7735_128_160(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect)
		: ZUNO_ST77XX(chipSelect, reset, dataSelect, 160, 128, ST77XX_COL_RGB, ST77XX_INVOFF, 2,1)
	{ }
};

class ZUNO_ST7735_80_160 : public ZUNO_ST77XX
{
	public:
	ZUNO_ST7735_80_160(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect)
		: ZUNO_ST77XX(chipSelect, reset, dataSelect, 160, 128, ST77XX_COL_BGR, ST77XX_INVON, 25,1)
	{ }
};
#endif