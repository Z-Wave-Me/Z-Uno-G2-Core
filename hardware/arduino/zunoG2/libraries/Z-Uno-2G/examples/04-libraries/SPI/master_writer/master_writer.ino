#include "Arduino.h"
#include "SPI.h"

void setup(){
	SPI.begin(SCK, MISO, MOSI, SS);
}
void loop(){
	SPI.beginTransaction();
	SPI.transfer("Hello!! You?");
	SPI.endTransaction();
	delay(2000);
}