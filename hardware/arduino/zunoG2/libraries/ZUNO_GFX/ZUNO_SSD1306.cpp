#include "ZUNO_SSD1306.h"

ZUNO_SSD1306::ZUNO_SSD1306(uint16_t width, uint16_t height, TwoWire *wire, 
						uint8_t i2caddr) : ZUNO_GFX::ZUNO_GFX(width, height),
						addr(i2caddr), i2c(wire), _invert(false)
{
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

void ZUNO_SSD1306::display()
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t col = 0;
	uint8_t count_wire = 2;
	sendCmd(SSD1306_COLUMNADDR);
	sendCmd(0);
	sendCmd(s_width - 1);
	sendCmd(SSD1306_PAGEADDR);
	sendCmd(0);
	sendCmd(s_height - 1);
	i2c->beginTransmission(addr);
	i2c->write(SSD1306_DATA_CONTINUE);
	for (y = 0;y < (s_height >> 3);y++)
	{
		for (x = 0;x < s_width; x++)
		{
			col = 0;
			for (uint8_t bit = 0; bit < 8; bit++)
			{
				uint8_t s_x = x / 8;
				uint8_t cur_b = (s_width >> 3) * 8 * y + (s_x + (s_width >> 3) * bit);
				uint8_t ret = (buffer[cur_b] >> (7 - (x % 8)));
				col |= (ret & 0x01) << bit;
				WDOG_Feed();
				// col |= 1 << bit;
			}
	// // 		// пуляем данные
			if (count_wire >= WIRE_BUFFER_LENGTH)
			{
				i2c->endTransmission();
				i2c->beginTransmission(addr);
				i2c->write(SSD1306_DATA_CONTINUE);
				count_wire = 2;
			}
			i2c->write(col);
			count_wire++;
		}
	}
	i2c->endTransmission();
}


// void test(uint8_t s_width, uint8_t s_height, uint8_t *buffer)
// {
// 	int x = 0;
// 	int y = 0;
// 	uint8_t col;
// 	col = 0;
// 	for (y = 0;y < (s_height >> 3);y++)
// 	{
// 		for (x = 0;x < s_width; x++)
// 		{
// 			col = 0;
// 			for (uint8_t bit = 0; bit < 8; bit++)
// 			{
// 				uint8_t s_x = x / 8;
// 				uint8_t cur_b = (s_width >> 3) * 8 * y + (s_x + (s_width >> 3) * bit);
// 				uint8_t ret = (buffer[cur_b] >> (7 - (x % 8)));
// 				col |= (ret & 1) << bit;
// 			}
// 			// пуляем данные
// 		}
// 	}
// }