#include "Arduino.h"
#include "ZUNO_ST7735.h"
#include "SPI.h"

ZUNO_ST7735::ZUNO_ST7735(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect,
			uint8_t width, uint8_t height) : ZUNO_GFX::ZUNO_GFX(width, height),
								 _cs(chipSelect), _rst(reset), _ds(dataSelect)
{
	_color = WHITE;
}

void ZUNO_ST7735::command(uint8_t cmd)
{
	digitalWrite(_ds, LOW);
	digitalWrite(_cs, LOW);
	SPI.transfer(cmd);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST7735::data(uint8_t data)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer(data);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST7735::data16(uint16_t data)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer16(data);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST7735::data(uint8_t *data, size_t size)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer((const uint8_t*)data, size);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST7735::setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	command(ST7735_CASET);
	data16(x0);
	data16(x1);
	command(ST7735_RASET);
	data16(y0);
	data16(y1);
}

void ZUNO_ST7735::LCD_Fill(uint16_t color){
	// command(ST7735_DISPOFF);
	setWindow(0, 0, s_width, s_height);
	command(ST7735_RAMWR);
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	uint16_t buf[512];
	color = (color >> 8) | ((color & 0xff) << 8);
	for(int i = 0;i < 512;i++)
	{
		buf[i] = color;
	}
	for (int i = 0; i <160 / 4; i++)
	{
		SPI.transfer((const uint8_t*)buf,1024);
	}
}

void ZUNO_ST7735::begin()
{
	SPI.begin();
	SPI.beginTransaction(4000000u, MSBFIRST, SPI_MODE0);
	delay(50);
	pinMode(_cs, OUTPUT);
	pinMode(_rst, OUTPUT);
	pinMode(_ds, OUTPUT);
	digitalWrite(_cs, HIGH);
	digitalWrite(_cs, LOW);
	digitalWrite(_rst, LOW);
	delay(10);
	digitalWrite(_rst, HIGH);
	command(ST7735_SWRESET);
	command(ST7735_SLPOUT);
	command(ST7735_COLMOD);
	data(ST7735_RGB565);
	command(ST7735_MADCTL);
	data(0xA0);
	command(ST7735_FRMCTR1);
	uint8_t freq[] = {0x00,0x0f,0x00,0x0f,0x00,0x0f};
	data(freq, sizeof(freq));
	command(ST7735_INVOFF);
	LCD_Fill(BLACK);
	command(ST7735_DISPON);
}

void ZUNO_ST7735::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	setWindow(x, y, x + 1, y + 1);
	command(ST7735_RAMWR);
	data16(color);
}