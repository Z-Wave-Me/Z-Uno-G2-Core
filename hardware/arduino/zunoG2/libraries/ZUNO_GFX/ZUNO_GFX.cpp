#include "ZUNO_GFX.h"

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
	font.font_buf = NULL;
	// buff_size = (width * height) >> 3;
	s_height = height;
	s_width = width;
	cur_x = 0;
	cur_y = 0;
}

ZUNO_GFX::~ZUNO_GFX()
{
	// free(buffer);
}

void ZUNO_GFX::drawPixel(int16_t x, int16_t y, uint8_t color)
{
	if (x >= s_width || y >= s_height || x < 0 || y < 0)
		return;
	uint8_t cur_byte = (y * s_width + x) >> 3;
	uint8_t cur_bit = 0x01 << ((y * s_width + x) % 8);
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
	// Serial.printf("\tchar '%c' / cur_x %d",ch, cur_x);
	ch -= font.start_sim;
	uint8_t *buf = font.font_buf + ((font.width + 1) * ch);
	uint8_t w_sim = *buf;
	uint8_t *sim = buf + 1;
	// Serial.printf(" / w_sim %d\n", w_sim);
	for (uint8_t col = 0; col < w_sim; col++)
	{
		for (uint8_t row = 0; row < font.height; row++)
		{
			uint8_t cur_b = col * ((font.height >> 3) + (row >> 8));
			uint8_t cur_bit = 1 << (row % 8);
			if (sim[cur_b] & cur_bit)
				drawPixel(cur_x + col, cur_y + row, 2);
		}
	}
	// Serial.printf("last cur %d | Ch %X-'%c' %d\n",cur_x, ch + font.start_sim, ch + font.start_sim, w_sim);
	cur_x += w_sim;
}

void	ZUNO_GFX::setFont(uint8_t *font_name)
{
	font.width = *font_name;
	font.height = *(font_name + 1);
	font.start_sim = *(font_name + 2);
	font.font_buf = font_name + 3;
};

uint8_t ZUNO_GFX::write(uint8_t c)
{
	uint8_t *buf = font.font_buf + (font.width + 1 * c);
	uint8_t w_sim = *buf;
	if (!font.font_buf)
		return (0);
	if ((cur_x + w_sim) > s_width || c == '\n')
	{
		if ((cur_y + font.height) < s_height)
		{
			cur_y += font.height;
			cur_x = 0;
		}
		else
			return(0);
	}
	if (c >= font.start_sim)
	{
		printChar(c);
		// cur_x += w_sim;
	}
	return (1);
}

size_t ZUNO_GFX::write(const uint8_t *buf, size_t size)
{
	size_t col_sim = 0;
	for(size_t i = 0; i < size; i++)
	{
		if (buf[i] < 128)
			write(buf[i]);
		else if (buf[i] & 0xd0)
			write(buf[++i] - 16);
		else if (buf[i] & 0xd1)
			write(buf[++i] + 48);
		else
			break;
		col_sim++;

	}
	return(1);
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
	// Serial.printf("writeLine pt0(%d, %d) pt1(%d, %d)\n",x0,y0,x1,y1);
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
	_swap_int16_t(x0, y0);
	_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
	_swap_int16_t(x0, x1);
	_swap_int16_t(y0, y1);
	}
	// Serial.printf("writeLine pt0(%d, %d) pt1(%d, %d)\n",x0,y0,x1,y1);

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

	void ZUNO_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
															uint16_t color) {
  writeFastHLine(x, y, w, color);
  writeFastHLine(x, y + h - 1, w, color);
  writeFastVLine(x, y, h, color);
  writeFastVLine(x + w - 1, y, h, color);
}

/**************************************************************************/
/*!
   @brief    Draw a line
    @param    x0  Start point x coordinate
    @param    y0  Start point y coordinate
    @param    x1  End point x coordinate
    @param    y1  End point y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ZUNO_GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
																uint16_t color) {
  // Update in subclasses if desired!
  if (x0 == x1) {
    if (y0 > y1)
      _swap_int16_t(y0, y1);
    drawFastVLine(x0, y0, y1 - y0 + 1, color);
  } else if (y0 == y1) {
    if (x0 > x1)
      _swap_int16_t(x0, x1);
    drawFastHLine(x0, y0, x1 - x0 + 1, color);
  } else {
    writeLine(x0, y0, x1, y1, color);
  }
}

/**************************************************************************/
/*!
   @brief   Draw a rounded rectangle with no fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    r   Radius of corner rounding
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ZUNO_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t r, uint16_t color) {
  int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
  if (r > max_radius)
    r = max_radius;
  // smarter version
  writeFastHLine(x + r, y, w - 2 * r, color);         // Top
  writeFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
  writeFastVLine(x, y + r, h - 2 * r, color);         // Left
  writeFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
  // draw four corners
  drawCircleHelper(x + r, y + r, r, 1, color);
  drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
  drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
  drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

void ZUNO_GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
															uint16_t color) {
  // Overwrite in subclasses if desired!
  fillRect(x, y, w, h, color);
}

void ZUNO_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
													int16_t r, uint16_t color) {
  int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
  if (r > max_radius)
    r = max_radius;
  // smarter version
  writeFillRect(x + r, y, w - 2 * r, h, color);
  // draw four corners
  fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

void ZUNO_GFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
									int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

/**************************************************************************/
/*!
   @brief     Draw a triangle with color-fill
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to fill/draw with
*/
/**************************************************************************/
void ZUNO_GFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int16_t(y0, y1);
    _swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int16_t(y2, y1);
    _swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int16_t(y0, y1);
    _swap_int16_t(x0, x1);
  }

  if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if (x1 < a)
      a = x1;
    else if (x1 > b)
      b = x1;
    if (x2 < a)
      a = x2;
    else if (x2 > b)
      b = x2;
    writeFastHLine(a, y0, b - a + 1, color);
    return;
  }

  int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
          dx12 = x2 - x1, dy12 = y2 - y1;
  int32_t sa = 0, sb = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if (y1 == y2)
    last = y1; // Include y1 scanline
  else
    last = y1 - 1; // Skip it

  for (y = y0; y <= last; y++) {
    a = x0 + sa / dy01;
    b = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      _swap_int16_t(a, b);
    writeFastHLine(a, y, b - a + 1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = (int32_t)dx12 * (y - y1);
  sb = (int32_t)dx02 * (y - y0);
  for (; y <= y2; y++) {
    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      _swap_int16_t(a, b);
    writeFastHLine(a, y, b - a + 1, color);
  }
}