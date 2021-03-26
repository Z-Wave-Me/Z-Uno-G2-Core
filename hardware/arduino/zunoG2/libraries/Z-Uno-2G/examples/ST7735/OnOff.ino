#include "Arduino.h"
#include "SPI.h"
#include "ZUNO_ST7735.h"
#include "MK-907x7.h"

ZUNO_ST7735 lcd_tft(20, 21, 22);

const uint16_t map_w = 16; // map width
const uint16_t map_h = 16; // map height
	const char map[] =	"0000222222220000"\
						"1              0"\
						"1      11111   0"\
						"1     0        0"\
						"0     0  1110000"\
						"0     3        0"\
						"0   10000      0"\
						"0   0   11100  0"\
						"0   0   0      0"\
						"0   0   1  00000"\
						"0       1      0"\
						"2       1      0"\
						"0       0      0"\
						"0 0000000      0"\
						"0              0"\
						"0002222222200000"; // our game map

float player_x = 3.456; // player x position
float player_y = 2.345; // player y position
float player_a = 1.523; // player view direction

const float fov = M_PI/3.; // field of view

void draw_rectangle(const uint16_t img_w, const uint16_t img_h, 
							const uint16_t x, const uint16_t y, const uint16_t w,
									const uint16_t h, const uint16_t color) {
	uint16_t cx, cy;
	for (size_t i=0; i<w; i++) {
		for (size_t j=0; j<h; j++) {
			cx = x+i;
			cy = y+j;
			lcd_tft.drawPixel(cx, cy, color);
		}
	}
}

void setup()
{
	Serial.begin(9600);
	lcd_tft.begin();
	lcd_tft.LCD_Fill(RED);
	lcd_tft.writeLine(0,0,80,80,CYAN);
	lcd_tft.drawCircle(80,64, 20, BLACK);
	lcd_tft.setFont(fontMK_907x7);
	lcd_tft.print("Оно Работает и пишет dsfsd nfd df sdfs sdfdfsd");
	lcd_tft.setFontColor(BLACK);
	lcd_tft.print("Оно Работает и пишет");
	lcd_tft.setFontColor(CYAN);
	lcd_tft.println("Vsemi ByКВАМИ");
	uint16_t win_h = lcd_tft.height(),win_w = lcd_tft.width();
	lcd_tft.LCD_Fill(MAGENTA);
	const uint16_t rect_w = win_w/map_w;
	const uint16_t rect_h = win_h/map_h;
	for (size_t j=0; j<map_h; j++) { // draw the map
		for (size_t i=0; i<map_w; i++) {
			if (map[i+j*map_w]==' ') continue; // skip empty spaces
			uint16_t rect_x = i*rect_w;
			uint16_t rect_y = j*rect_h;
			draw_rectangle(win_w, win_h, rect_x, rect_y, rect_w, rect_h, CYAN);
		}
		WDOG_Feed();
	}
	draw_rectangle(win_w, win_h, player_x*rect_w, player_y*rect_h, 5, 5, WHITE);
	for (uint16_t i=0; i<win_w; i+= 3) { // draw the visibility cone
		float angle = player_a-fov/2 + fov*i/float(win_w);
		for (float t=0; t<20; t+=.2) {
			float cx = player_x + t*cos(angle);
			float cy = player_y + t*sin(angle);
			if (map[int(cx)+int(cy)*map_w]!=' ') break;

			size_t pix_x = cx*rect_w;
			size_t pix_y = cy*rect_h;
			lcd_tft.drawPixel(pix_x, pix_y, WHITE);
		}
		WDOG_Feed();
	}
}

void loop()
{

}