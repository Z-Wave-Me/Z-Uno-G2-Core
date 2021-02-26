#include "ZUNO_SSD1306.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)														\
	{																			\
	int16_t t = a;																\
	a = b;																		\
	b = t;																		\
	}
#endif

ZUNO_GFX::ZUNO_GFX(uint16_t width, uint16_t height)
{
	font = NULL;
	buff_size = (width * height) >> 3;
	s_height = height;
	s_width = width;
	buffer = (uint8_t*)malloc(buff_size);
	memset(buffer, 0x00, buff_size);
	cur_x = 0;
	cur_y = 0;
}

ZUNO_GFX::~ZUNO_GFX()
{
	free(buffer);
}

void ZUNO_GFX::drawPixel(int16_t x, int16_t y, uint8_t color)
{
	if (x >= s_width || y >= s_height)
		return;
	uint8_t cur_byte = (y * s_width + x) >> 3;
	uint8_t cur_bit = (y * s_width + x) % 8;
	switch (color)
	{
	case 0:
		buffer[cur_byte] &= (0xff ^ (0x80 >> cur_bit));
		break;
	case 1:
		buffer[cur_byte] ^= (0x80 >> cur_bit);
		break;
	default:
		buffer[cur_byte] |= (0x80 >> cur_bit);
		break;
	}
}

void ZUNO_GFX::writePixel(int16_t x, int16_t y, uint8_t color) {
  drawPixel(x, y, color);
}

void ZUNO_GFX::drawBitmap(uint16_t x, uint16_t y,uint8_t w, uint8_t h,
												 uint8_t *pic, uint8_t color)
{
	uint8_t col;
	if (!pic)
		return;
	for (uint16_t c_y = 0;c_y < h; c_y++)
	{
		for (uint16_t c_x = 0;c_x < w; c_x++)
		{
			int cur_b = c_x / 8 + c_y * w / 8;
			col = pic[cur_b] & (0x80 >> c_x / 8);
			if ((color == 0) || (col == 1 && color >= 1))
				drawPixel(x+c_x, y+c_y, col);
		}
	}
}

void ZUNO_GFX::printChar(uint8_t ch)
{
	ch -= font->start_sim;
	uint8_t *buf = font->font_buf + ((font->width + 1) * ch);
	uint8_t w_sim = *buf;
	uint8_t *sim = buf + 1;
	for (uint8_t col = 0; col < w_sim; col++)
	{
		for (uint8_t row = 0; row < font->height; row++)
		{
			uint8_t cur_b = col * ((font->height >> 3) + (row >> 8));
			uint8_t cur_bit = 0x80 >> (row % 8);
			if (sim[cur_b] & cur_bit)
				drawPixel(cur_x + col, cur_y + row, 2);
		}
	}
}

uint8_t ZUNO_GFX::write(uint8_t c)
{
	uint8_t *buf = font->font_buf + (font->width + 1 * c);
	uint8_t w_sim = *buf;
	if (!font)
		return (0);
	if ((cur_x + w_sim) > s_width || c == '\n')
	{
		if ((cur_y + font->height) < s_height)
		{
			cur_y += font->height;
			cur_x = 0;
		}
		else
			return(0);
	}
	if (c >= font->start_sim)
	{
		printChar(c);
		cur_x += w_sim;
	}
	return (1);
}

size_t ZUNO_GFX::write(const uint8_t *buf, size_t size)
{
	size_t col_sim = 0;
	for(size_t i = 0; i < size; i++)
	{
		if (buf[i] & 0xd0)
			write(buf[++i] - 16);
		else if (buf[i] & 0xd1)
			write(buf[++i] + 48);
		else if (buf[i] < 128)
			write(buf[i]);
		else
			break;
		col_sim++;
	}
	return(col_sim);
}

/**************************************************************************/
/*!
	@brief	Write a line.	Bresenham's algorithm - thx wikpedia
	@param	x0	Start point x coordinate
	@param	y0	Start point y coordinate
	@param	x1	End point x coordinate
	@param	y1	End point y coordinate
	@param	color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ZUNO_GFX::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
							 uint8_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
	_swap_int16_t(x0, y0);
	_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
	_swap_int16_t(x0, x1);
	_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
	ystep = 1;
	} else {
	ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			drawPixel(y0, x0, color);
		} else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void ZUNO_GFX::writeFastVLine(int16_t x, int16_t y, int16_t h,
								  uint8_t color) {
  // Overwrite in subclasses if startWrite is defined!
  // Can be just writeLine(x, y, x, y+h-1, color);
  // or writeFillRect(x, y, 1, h, color);
  drawFastVLine(x, y, h, color);
}
void ZUNO_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color) {
  writeLine(x, y, x, y + h - 1, color);
}

void ZUNO_GFX::writeFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color) {
  // Overwrite in subclasses if startWrite is defined!
  // Example: writeLine(x, y, x+w-1, y, color);
  // or writeFillRect(x, y, w, 1, color);
  drawFastHLine(x, y, w, color);
}

/**************************************************************************/
/*!
   @brief    Draw a perfectly horizontal line (this is often optimized in a
   subclass!)
	@param    x   Left-most x coordinate
	@param    y   Left-most y coordinate
	@param    w   Width in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void ZUNO_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color) {
  writeLine(x, y, x + w - 1, y, color);
}


void ZUNO_GFX::fillRect(int16_t x, int16_t y, int16_t w,
													int16_t h, uint8_t color) {
  for (int16_t i = x; i < x + w; i++) {
	writeFastVLine(i, y, h, color);
  }
}

void ZUNO_GFX::fillScreen(uint8_t color) {
  fillRect(0, 0, s_width, s_height, color);
}

void ZUNO_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  writePixel(x0, y0 + r, color);
  writePixel(x0, y0 - r, color);
  writePixel(x0 + r, y0, color);
  writePixel(x0 - r, y0, color);

  while (x < y) {
	if (f >= 0) {
	  y--;
	  ddF_y += 2;
	  f += ddF_y;
	}
	x++;
	ddF_x += 2;
	f += ddF_x;

	writePixel(x0 + x, y0 + y, color);
	writePixel(x0 - x, y0 + y, color);
	writePixel(x0 + x, y0 - y, color);
	writePixel(x0 - x, y0 - y, color);
	writePixel(x0 + y, y0 + x, color);
	writePixel(x0 - y, y0 + x, color);
	writePixel(x0 + y, y0 - x, color);
	writePixel(x0 - y, y0 - x, color);
  }
}

/**************************************************************************/
/*!
	@brief    Quarter-circle drawer, used to do circles and roundrects
	@param    x0   Center-point x coordinate
	@param    y0   Center-point y coordinate
	@param    r   Radius of circle
	@param    cornername  Mask bit #1 or bit #2 to indicate which quarters of
   the circle we're doing
	@param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ZUNO_GFX::drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
											uint8_t cornername, uint8_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  while (x < y) {
	if (f >= 0) {
	  y--;
	  ddF_y += 2;
	  f += ddF_y;
	}
	x++;
	ddF_x += 2;
	f += ddF_x;
	if (cornername & 0x4) {
	  writePixel(x0 + x, y0 + y, color);
	  writePixel(x0 + y, y0 + x, color);
	}
	if (cornername & 0x2) {
	  writePixel(x0 + x, y0 - y, color);
	  writePixel(x0 + y, y0 - x, color);
	}
	if (cornername & 0x8) {
	  writePixel(x0 - y, y0 + x, color);
	  writePixel(x0 - x, y0 + y, color);
	}
	if (cornername & 0x1) {
	  writePixel(x0 - y, y0 - x, color);
	  writePixel(x0 - x, y0 - y, color);
	}
  }
}

void ZUNO_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color) {
  writeFastVLine(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

/**************************************************************************/
/*!
    @brief  Quarter-circle drawer with fill, used for circles and roundrects
    @param  x0       Center-point x coordinate
    @param  y0       Center-point y coordinate
    @param  r        Radius of circle
    @param  corners  Mask bits indicating which quarters we're doing
    @param  delta    Offset from center-point, used for round-rects
    @param  color    16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void ZUNO_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
								uint8_t corners, int16_t delta, uint8_t color) {

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  int16_t px = x;
  int16_t py = y;

  delta++; // Avoid some +1's in the loop

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    // These checks avoid double-drawing certain lines, important
    // for the SSD1306 library which has an INVERT drawing mode.
    if (x < (y + 1)) {
      if (corners & 1)
        writeFastVLine(x0 + x, y0 - y, 2 * y + delta, color);
      if (corners & 2)
        writeFastVLine(x0 - x, y0 - y, 2 * y + delta, color);
    }
    if (y != py) {
      if (corners & 1)
        writeFastVLine(x0 + py, y0 - px, 2 * px + delta, color);
      if (corners & 2)
        writeFastVLine(x0 - py, y0 - px, 2 * px + delta, color);
      py = y;
    }
    px = x;
  }
}

ZUNO_SSD1306::ZUNO_SSD1306(uint16_t width, uint16_t height, TwoWire *wire, 
	uint8_t i2caddr) : ZUNO_GFX::ZUNO_GFX(width, height),addr(i2caddr), i2c(wire)
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