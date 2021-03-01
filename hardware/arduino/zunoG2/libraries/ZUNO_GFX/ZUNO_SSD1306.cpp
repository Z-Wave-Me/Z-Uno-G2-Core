#include "ZUNO_SSD1306.h"

ZUNO_SSD1306::ZUNO_SSD1306(uint16_t width, uint16_t height, TwoWire *wire, 
						uint8_t i2caddr) : ZUNO_GFX::ZUNO_GFX(width, height),
						addr(i2caddr), i2c(wire), _invert(false)
{
	buff_size = (width * height) >> 3;
	s_buf = (uint8_t*)malloc(buff_size + 1);
	memset(s_buf, 0x00, buff_size + 1);
	buffer = s_buf + 1;
	*s_buf = SSD1306_DATA_CONTINUE;
}

void ZUNO_SSD1306::drawPixel(int16_t x, int16_t y, uint8_t color)
{
	if (x >= s_width || y >= s_height)
		return;
	uint8_t cur_byte = x + y / 8 * s_width;
	uint8_t cur_bit = 0x80 >> (y % 8);
	switch (color)
	{
	case 0:
		buffer[cur_byte] &= (0xff ^ cur_bit);
		break;
	case 1:
		buffer[cur_byte] ^= cur_bit;
		break;
	default:
		buffer[cur_byte] |= cur_bit;
		break;
	}
}

void ZUNO_SSD1306::sendCmd(uint8_t cmd)
{
	Wire.beginTransmission(addr);
	Wire.write((uint8_t)SSD1306_COMMAND); // Co = 0, D/C = 0
	Wire.write(cmd);
	Wire.endTransmission();
}

void ZUNO_SSD1306::sendCmd(uint8_t *cmd, size_t size)
{
	for (size_t i = 0; i < size; i++)
		sendCmd(cmd[i]);
}


void ZUNO_SSD1306::begin()
{
	uint8_t cmd[] = {
					SSD1306_DISPLAYOFF,		 		// 0xAE
					SSD1306_SETDISPLAYCLOCKDIV, 	// 0xD5
					0x80,							// the suggested ratio 0x80
					SSD1306_SETMULTIPLEX,			// 0xA8
					(uint8_t)(s_height - 1),			 
					SSD1306_SETDISPLAYOFFSET,		// 0xD3
					0x0,							// no offset
					SSD1306_SETSTARTLINE | 0x0,		// line #0
					SSD1306_CHARGEPUMP,		 		// 0x8D
					SSD1306_INTERNALVCC,			// 0x14
					SSD1306_MEMORYMODE,				// 0x20
					0x00,							// 0x0 act like ks0108
					SSD1306_SEGREMAP | 0x1,
					SSD1306_COMSCANDEC,				// COM conf
					SSD1306_SETCOMPINS,
					0x02,
					SSD1306_SETCONTRAST,
					0x01,							//contrast 127 of 255
					SSD1306_SETPRECHARGE,			// 0xd9 phathe dc-dc conv
					0xF1,
					SSD1306_SETVCOMDETECT,			//VcomH level	
					0x40,
					SSD1306_DISPLAYALLON_RESUME,	// 0xA4
					SSD1306_NORMALDISPLAY,			// 0xA6 non invert
					SSD1306_DEACTIVATE_SCROLL,
					SSD1306_DISPLAYON				// Main screen turn on
	};
	i2c->begin();
	sendCmd(cmd, sizeof(cmd));
}

void ZUNO_SSD1306::setArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	sendCmd(SSD1306_COLUMNADDR);
	sendCmd(x0);
	sendCmd(x1);
	sendCmd(SSD1306_PAGEADDR);
	sendCmd(y0 >> 3);
	sendCmd((y1 - 1) >> 3);
}

void ZUNO_SSD1306::display()
{
	setArea(0, 0, s_width - 1, s_height - 1);
	i2c->transfer(addr, (uint8_t*)s_buf, buff_size + 1);
}