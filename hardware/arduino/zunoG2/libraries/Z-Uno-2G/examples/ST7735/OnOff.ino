#include "Arduino.h"
#include "SPI.h"
#include "ZUNO_ST7735.h"
#include "MK-907x7.h"

ZUNO_ENABLE(LOGGING_DBG LOGGING_UART=Serial0); 

ZUNO_ST7735 lcd_tft(20, 21, 22);
void setup()
{
	Serial0.begin(115200);
	Serial0.println("!!!!!!!!!!!!!!!!!");
	// Serial.begin(9600);
	lcd_tft.begin();
	lcd_tft.LCD_Fill(RED);
	lcd_tft.writeLine(0,0,80,80,CYAN);
	lcd_tft.drawCircle(80,64, 20, BLACK);
	lcd_tft.setFont(fontMK_907x7);
	lcd_tft.print("Оно Работает и пишет dsfsd nfd\nfsdf sdfs sdfdfsd");
	lcd_tft.setFontColor(BLACK);
	// lcd_tft.setCursor(0,8);
	lcd_tft.print("Оно Работает и пишет");
	// lcd_tft.setFontColor(CYAN);
	// lcd_tft.println("Vsemi ByКВАМИ");
	
}

void loop()
{
	Serial0.println("!!!!!!!!!!!!!!!!!");

	// lcd_tft.command(ST7735_SLPIN);
	// digitalWrite(13,HIGH);
	// digitalWrite(13,LOW);
	delay(1000);
	// digitalWrite(13,HIGH);
	// lcd_tft.LCD_Fill(MAGENTA);
	// digitalWrite(13,LOW);
	// delay(1000);
	// digitalWrite(13,HIGH);
	// lcd_tft.LCD_Fill(RED);
	// digitalWrite(13,LOW);
	// delay(1000);
	// lcd_tft.command(ST7735_SLPIN);

}