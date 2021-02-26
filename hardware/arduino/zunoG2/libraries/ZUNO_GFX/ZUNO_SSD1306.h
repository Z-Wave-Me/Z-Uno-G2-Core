#ifndef __ZUNO_SSD1306__
#define __ZUNO_SSD1306__

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

#define I2C_SCREEN_ADDRESS		0x3C	///default addres
#define SSD1306_COMMAND			0x00
#define SSD1306_DATA			0xC0
#define SSD1306_DATA_CONTINUE	0x40

#define RST_NOT_IN_USE	255
#define SSD1306_MEMORYMODE 0x20			///< See datasheet
#define SSD1306_COLUMNADDR 0x21			///< See datasheet
#define SSD1306_PAGEADDR 0x22			///< See datasheet
#define SSD1306_SETCONTRAST 0x81		///< See datasheet
#define SSD1306_CHARGEPUMP 0x8D			///< See datasheet
#define SSD1306_SEGREMAP 0xA0			///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4///< See datasheet
#define SSD1306_DISPLAYALLON 0xA5		///< Not currently used
#define SSD1306_NORMALDISPLAY 0xA6		///< See datasheet
#define SSD1306_INVERTDISPLAY 0xA7		///< See datasheet
#define SSD1306_SETMULTIPLEX 0xA8		///< See datasheet
#define SSD1306_DISPLAYOFF 0xAE			///< See datasheet
#define SSD1306_DISPLAYON 0xAF			///< See datasheet
#define SSD1306_COMSCANINC 0xC0			///< Not currently used
#define SSD1306_COMSCANDEC 0xC8			///< See datasheet
#define SSD1306_SETDISPLAYOFFSET 0xD3	///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5	///< See datasheet
#define SSD1306_SETPRECHARGE 0xD9		///< See datasheet
#define SSD1306_SETCOMPINS 0xDA			///< See datasheet
#define SSD1306_SETVCOMDETECT 0xDB		///< See datasheet

#define SSD1306_SETLOWCOLUMN 0x00	///< Not currently used
#define SSD1306_SETHIGHCOLUMN 0x10	///< Not currently used
#define SSD1306_SETSTARTLINE 0x40	///< See datasheet

#define SSD1306_EXTERNALVCC 0x01	///< External display voltage source
#define SSD1306_INTERNALVCC 0x14
#define SSD1306_SWITCHCAPVCC 0x02	///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26				///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27					///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29	///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A	///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL 0x2E						///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL 0x2F						///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3				///< Set scroll range

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
		size_t		buff_size;
		uint8_t		*buffer;
		uint16_t	cur_x;
		uint16_t	cur_y;
		uint16_t	s_width;
		uint16_t	s_height;	
		GLCDfonts	*font;
		void printChar(uint8_t ch);
		
	private:
	public:
		ZUNO_GFX(uint16_t width, uint16_t height);
		~ZUNO_GFX();
		using	Print::write;
		size_t write(const uint8_t *buffer, size_t size);
		uint8_t write(uint8_t);
		void drawPixel(int16_t x, int16_t y, uint8_t color);
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
		void	setFont(uint8_t *font_name) { font = (GLCDfonts*)font_name; };
		int16_t	width(void) const { return s_width; };
		int16_t	height(void) const { return s_height; };
		int16_t	getCursorX(void) const { return cur_x; };
		int16_t	getCursorY(void) const { return cur_y; };
		void	setCursor(uint16_t x, uint16_t y) {cur_x = x; cur_y = y;};
};


class ZUNO_SSD1306 : public ZUNO_GFX
{
	private:
		uint8_t		addr;
		TwoWire		*i2c;
		bool		_invert;
		// SPIClass	*spi;
		void		sendCmd(uint8_t cmd);
		void		sendCmd(uint8_t *cmd, size_t size);

	public:
		ZUNO_SSD1306(uint16_t width, uint16_t height, TwoWire *wire = &Wire,
				uint8_t i2caddr = I2C_SCREEN_ADDRESS);
		// ~ZUNO_SSD1306();
		// size_t write(const uint8_t *buffer, size_t size){};
		// uint8_t write(uint8_t){};
		void begin();
		void display();
		void on() { sendCmd(SSD1306_DISPLAYON); };
		void off() { sendCmd(SSD1306_DISPLAYOFF); };
		void invert() {_invert != _invert;
			sendCmd((_invert) ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY);};
};



#endif