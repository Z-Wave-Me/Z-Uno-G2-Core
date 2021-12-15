#include "Arduino.h"
#include "Spi.h"

#define MY_SERIAL		Serial
#define MESSAGE			"Hello!! You?"

void setup() {
	MY_SERIAL.begin(115200);
	SPI.begin(SCK, MISO, MOSI, SS);
}

void loop(){
	uint8_t			buffer[sizeof(MESSAGE)];

	SPI.beginTransaction();
	SPI.transfer16(0x3031);
	delay(100);
	memcpy(&buffer[0x0], MESSAGE, sizeof(MESSAGE));
	SPI.transfer(&buffer[0x0], sizeof(MESSAGE) - 0x1);
	SPI.endTransaction();
	MY_SERIAL.println((const char *)&buffer[0x0]);
	delay(2000);
}