#include "Arduino.h"
#include "ZUNO_SSD1306.h"
#include "Verdana7x8.h"
// #include "ZUNO_GFX.h"
#include "Wire.h"

ZUNO_SSD1306 lcd(128, 32);

void setup()
{
	lcd.begin();
	lcd.display();
	lcd.setFont((uint8_t*)Verdana7x8);
	lcd.setCursor(0,0);
	lcd.println("Привет world");
	lcd.fillCircle(64,16 , 10, 1);
}

void loop()
{

}