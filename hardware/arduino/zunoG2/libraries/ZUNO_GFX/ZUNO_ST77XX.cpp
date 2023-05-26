#include "Arduino.h"
#include "ZUNO_ST77XX.h"
#include "SPI.h"

ZUNO_ST77XX::ZUNO_ST77XX(uint8_t chipSelect, uint8_t reset, uint8_t dataSelect,
				uint8_t width, uint8_t height, uint8_t color_mode,
							uint8_t inv_mode, uint8_t shift_h, uint8_t shift_w)
	: ZUNO_GFX::ZUNO_GFX(width, height), _cs(chipSelect), _rst(reset), _ds(dataSelect)
{
	_color = WHITE;
	_color_mode = color_mode;
	_shift_h = shift_h;
	_shift_w = shift_w;
	_inv_mode = inv_mode;
}

void ZUNO_ST77XX::command(uint8_t cmd)
{
	digitalWrite(_ds, LOW);
	digitalWrite(_cs, LOW);
	SPI.transfer(cmd);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::data(uint8_t data)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer(data);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::data16(uint16_t data)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	// data = (data >> 8) | ((data & 0xff) << 8);
	SPI.transfer16(data);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::data(uint8_t *data, size_t size)
{
	digitalWrite(_ds, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer((const uint8_t*)data, size);
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	x0 += _shift_w;
	x1 += _shift_w;
	y0 += _shift_h;
	y1 += _shift_h;
	// if (s_height == 80){
	// 	y0 += 25;
	// 	y1 += 25;
	// }
	command(ST77XX_CASET);
	data16(x0);
	data16(x1);
	command(ST77XX_RASET);
	data16(y0);
	data16(y1);
}

void ZUNO_ST77XX::LCD_Fill(uint16_t color){
	// command(ST77XX_DISPOFF);
	fillRect(0, 0, s_width, s_height,color);
}

void ZUNO_ST77XX::begin()
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
	command(ST77XX_SWRESET);
	delay(10);
	command(ST77XX_SLPOUT);
	delay(10);
	command(ST77XX_COLMOD);
	data(ST77XX_RGB565);
	command(ST77XX_MADCTL);
	data(_color_mode);
	command(ST77XX_FRMCTR1);
	uint8_t freq[] = {0x00,0x0f,0x00,0x0f,0x00,0x0f};
	data(freq, sizeof(freq));
	command(ST77XX_DISPON);
	command(_inv_mode);

	LCD_Fill(BLACK);
}

void ZUNO_ST77XX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	setWindow(x, y, x, y);
	command(ST77XX_RAMWR);
	data16(color);
}

void ZUNO_ST77XX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	uint16_t buf[h];
	color = (color >> 8) | ((color & 0xff) << 8);
	for (int i = 0; i < h; i++)
		buf[i] = color;
	// memset(buf, color, sizeof(buf));
	setWindow(x, y, x, y + h);
	command(ST77XX_RAMWR);
	digitalWrite(_cs, LOW);
	digitalWrite(_ds, HIGH);
	SPI.transfer(buf,sizeof(buf));
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	uint16_t buf[w];
	color = (color >> 8) | ((color & 0xff) << 8);
	for (int i = 0; i < w; i++)
		buf[i] = color;
	setWindow(x, y, x + w, y);
	// memset(buf, color, sizeof(buf));
	command(ST77XX_RAMWR);
	digitalWrite(_cs, LOW);
	digitalWrite(_ds, HIGH);
	SPI.transfer(buf,sizeof(buf));
	digitalWrite(_cs, HIGH);
}

void ZUNO_ST77XX::drawImage_1bpp(uint16_t x, uint16_t y, uint8_t *img,uint16_t color, uint32_t bg_color)
{
	uint8_t w = img[0];
	uint8_t h = img[1];
	uint8_t w_byte = (w >> 3) + (w % 8 ? 1 : 0);
	uint8_t *buf = &img[2];

	if (bg_color != (uint32_t)-1){
		color = (color >> 8) | ((color & 0xff) << 8);
		bg_color = (bg_color >> 8) | ((bg_color & 0xff) << 8);
		uint16_t *buf_img = (uint16_t*)malloc(w * sizeof(uint16_t));
		for (uint16_t line = 0; line < h; line++)
		{
			for (uint16_t col = 0; col < w; col++)
			{
				uint16_t pt_color = (buf[w_byte * line + (col >> 3)] & (0x80 >> (col % 8))) ? color : bg_color;
				buf_img[col] = pt_color;
			}
			setWindow(x, line + y, x + w, line + y);
			command(ST77XX_RAMWR);
			digitalWrite(_cs, LOW);
			digitalWrite(_ds, HIGH);
			SPI.transfer((void*)buf_img,w * sizeof(uint16_t));
			digitalWrite(_cs, HIGH);
		}
		free(buf_img);
	}
	else 
	{
		uint8_t cur_b = 0;
		int16_t st=-1, end = -1;
		for (int line = 0; line < h; line++)
		{
			WDOG_Feed();
			for (int col = 0; col < w; col++){
				cur_b = buf[w_byte * line + (col >> 3)];
				if ((cur_b & (0x80 >> (col % 8))) && st == -1)
					st = col;
				else if ((!(cur_b & (0x80 >> (col % 8))) || col == w - 1) && (end == -1) && (st >= 0))
					end = col;
				
				if (st >= 0 && end >= 0)
				{
					setWindow(x + st, line + y, x + end, line + y);
					command(ST77XX_RAMWR);
					digitalWrite(_cs, LOW);
					digitalWrite(_ds, HIGH);
					for (int i = st; i < end; i++)
						SPI.transfer16(color);
					digitalWrite(_cs, HIGH);
					st = -1;
					end = -1;
				}
			}
		}
	}
}