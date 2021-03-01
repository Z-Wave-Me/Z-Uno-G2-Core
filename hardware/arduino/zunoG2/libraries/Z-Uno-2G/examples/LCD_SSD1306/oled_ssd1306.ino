#include "Arduino.h"
#include "ZUNO_SSD1306.h"
#include "Verdana7x8.h"
// #include "ZUNO_GFX.h"
#include "Wire.h"

typedef struct subbuf_s
{
	uint8_t	cmd;
	uint8_t *buf;
}				subbuf_t;

ZUNO_ENABLE(LOGGING_DBG LOGGING_UART=Serial0); 
ZUNO_SSD1306 lcd(128, 32);

void setup()
{
	Serial.begin(9600);
	lcd.begin();
	lcd.clearDisp();
	lcd.setFont((uint8_t*)Verdana7x8);
	lcd.setCursor(0,0);
	// lcd.setArea(0,0,127,32);
	// int count_byte = 2;
	// memset((lcd.buffer), 0xff, lcd.buff_size);
	// lcd.drawFastVLine(0,0,33,1);
	// for (int i = 0; i < 31; i++)
	// {
	// 	lcd.drawPixel(1 + i,i,1);

	// }
	// lcd.write('h');
	lcd.write("Hello World?\nTesT\nwiTdh");
	// lcd.clearDisp();
	// lcd.drawCircleHelper(64, 16, 10, 2,2);
	// lcd.writeLine(0,0,127,31,1);
	lcd.display();
	delay(2000);
//  delay(2000);
  // lcd.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // lcd.display(). These examples demonstrate both approaches...

  // testdrawline();      // Draw many lines

  // testdrawrect();      // Draw rectangles (outlines)

  // testfillrect();      // Draw rectangles (filled)

  // testdrawcircle();    // Draw circles (outlines)

  // testfillcircle();    // Draw circles (filled)

//   testdrawroundrect(); // Draw rounded rectangles (outlines)

//   testfillroundrect(); // Draw rounded rectangles (filled)

//   testdrawtriangle();  // Draw triangles (outlines)

//   testfilltriangle();  // Draw triangles (filled)

  testdrawchar();      // Draw characters of the default font

//   testdrawstyles();    // Draw 'stylized' characters

//   testscrolltext();    // Draw scrolling text

//   testdrawbitmap();    // Draw a small bitmap image
}

void loop()
{

}

void testdrawrect(void) {
  lcd.clearDisp();

  for(int16_t i=0; i<lcd.height()/2; i+=2) {
    lcd.drawRect(i, i, lcd.width()-2*i, lcd.height()-2*i, 2);
    lcd.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawline() {
  int16_t i;

  lcd.clearDisp(); // Clear display buffer

  for(i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(0, 0, i, lcd.height()-1, SSD1306_WHITE);
    lcd.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<lcd.height(); i+=4) {
    lcd.drawLine(0, 0, lcd.width()-1, i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  delay(250);

  lcd.clearDisp();

  for(i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(0, lcd.height()-1, i, 0, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  for(i=lcd.height()-1; i>=0; i-=4) {
    lcd.drawLine(0, lcd.height()-1, lcd.width()-1, i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  delay(250);

  lcd.clearDisp();

  for(i=lcd.width()-1; i>=0; i-=4) {
    lcd.drawLine(lcd.width()-1, lcd.height()-1, i, 0, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  for(i=lcd.height()-1; i>=0; i-=4) {
    lcd.drawLine(lcd.width()-1, lcd.height()-1, 0, i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  delay(250);

  lcd.clearDisp();

  for(i=0; i<lcd.height(); i+=4) {
    lcd.drawLine(lcd.width()-1, 0, 0, i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }
  for(i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(lcd.width()-1, 0, i, lcd.height()-1, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testfillrect(void) {
  lcd.clearDisp();

  for(int16_t i=0; i<lcd.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    lcd.fillRect(i, i, lcd.width()-i*2, lcd.height()-i*2, SSD1306_INVERSE);
    lcd.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  lcd.clearDisp();

  for(int16_t i=0; i<max(lcd.width(),lcd.height())/2; i+=2) {
    lcd.drawCircle(lcd.width()/2, lcd.height()/2, i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  lcd.clearDisp();

  for(int16_t i=max(lcd.width(),lcd.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    lcd.fillCircle(lcd.width() / 2, lcd.height() / 2, i, SSD1306_INVERSE);
    lcd.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  lcd.clearDisp();
  for(int16_t i=0; i<lcd.height()/2-2; i+=2) {
    lcd.drawRoundRect(i, i, lcd.width()-2*i, lcd.height()-2*i,
      lcd.height()/4, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  lcd.clearDisp();

  for(int16_t i=0; i<lcd.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    lcd.fillRoundRect(i, i, lcd.width()-2*i, lcd.height()-2*i,
      lcd.height()/4, SSD1306_INVERSE);
    lcd.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  lcd.clearDisp();

  for(int16_t i=0; i<max(lcd.width(),lcd.height())/2; i+=5) {
    lcd.drawTriangle(
      lcd.width()/2  , lcd.height()/2-i,
      lcd.width()/2-i, lcd.height()/2+i,
      lcd.width()/2+i, lcd.height()/2+i, SSD1306_WHITE);
    lcd.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  lcd.clearDisp();

  for(int16_t i=max(lcd.width(),lcd.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    lcd.fillTriangle(
      lcd.width()/2  , lcd.height()/2-i,
      lcd.width()/2-i, lcd.height()/2+i,
      lcd.width()/2+i, lcd.height()/2+i, SSD1306_INVERSE);
    lcd.display();
    delay(1);
  }
  delay(2000);
}

void testdrawchar(void) {
  lcd.clearDisp();

  // lcd.setTextSize(1);      // Normal 1:1 pixel scale
//   lcd.setTextColor(SSD1306_WHITE); // Draw white text
  lcd.setCursor(0, 0);     // Start at top-left corner
//   lcd.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the lcd. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') lcd.write(' ');
    else          lcd.write(i);
  }

  lcd.display();
  delay(2000);
}

// void testdrawstyles(void) {
//   lcd.clearDisp();

//   // lcd.setTextSize(1);             // Normal 1:1 pixel scale
//   lcd.setTextColor(SSD1306_WHITE);        // Draw white text
//   lcd.setCursor(0,0);             // Start at top-left corner
//   lcd.println(F("Hello, world!"));

//   lcd.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
//   lcd.println(3.141592);

//   // lcd.setTextSize(2);             // Draw 2X-scale text
//   lcd.setTextColor(SSD1306_WHITE);
//   lcd.print(F("0x")); lcd.println(0xDEADBEEF, HEX);

//   lcd.display();
//   delay(2000);
// }