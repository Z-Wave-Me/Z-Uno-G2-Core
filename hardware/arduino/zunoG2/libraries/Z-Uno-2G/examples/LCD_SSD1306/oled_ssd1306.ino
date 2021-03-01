#include "Arduino.h"
#include "ZUNO_SSD1306.h"
#include "Verdana7x8.h"
// #include "ZUNO_GFX.h"
#include "Wire.h"

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
	// lcd.drawFastHLine(0, 3, 60, 2);
	lcd.write(119);
	lcd.display();
	// for (int i = 0; i < lcd.buff_size; i++)
	// {
	// 	lcd.buffer[i] = 0xf;
	// }
	// buf.buf[0] = 0x40;
	// lcd.buffer[0] = 0x40;
	// Wire.beginTransmission(0x3c);
	// Wire.write(0x40);

	// for (int i = 0; i < lcd.buff_size; i++)
	// {
	// 	if (count_byte >= WIRE_BUFFER_LENGTH)
	// 	{
	// 		Wire.endTransmission();
	// 		Wire.beginTransmission(0x3c);
	// 		Wire.write(0x40);
	// 		count_byte = 2;
	// 	}
	// 	Wire.write(lcd.buffer[i]);
	// 	count_byte++;
	// }
	// Wire.endTransmission();
	// Wire.beginTransmission(0x3c);
	// Wire.write(0x40);
	// Wire.endTransmission();
	// buf.cmd = 0x40;
	// buf.buf = lcd.buffer;
	// // Wire.transfer((uint8_t)0x3c, (void*)lcd.buffer, (wire_buffer_len)lcd.buff_size);
	// Wire.transfer((uint8_t)0x3c, (void*)&buf, (wire_buffer_len)lcd.buff_size);
}

void loop()
{

}