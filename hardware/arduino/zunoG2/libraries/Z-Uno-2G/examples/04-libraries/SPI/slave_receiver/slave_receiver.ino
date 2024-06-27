#include "Arduino.h"
#include "SPI.h"

#define MY_SERIAL Serial

void setup(){
	MY_SERIAL.begin();
	SPI.begin(SCK, MISO, MOSI, SS);
	SPI.setSlave(true);
}
void loop(){
	if (SPI.available()) {
		while (SPI.available()) { // slave may send less than requested
			char c = SPI.read(); // receive a byte as character
			MY_SERIAL.print(c);         // print the character
		}
		MY_SERIAL.print('\n');         // print the character
	}
}