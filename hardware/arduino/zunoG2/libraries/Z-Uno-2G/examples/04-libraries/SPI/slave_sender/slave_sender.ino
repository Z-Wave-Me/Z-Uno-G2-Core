#include "Arduino.h"
#include "Spi.h"

void handler(void) {
	size_t			cmd;

	switch (SPI.available()) {
		case 2:
			cmd = (SPI.read() << 0x8 )| SPI.read();
			if (cmd == 0x3031 && SPI.available() == 0x0)
				SPI.write((uint8_t *)"Yes!! this I", 12);
			break;
		default:
			break;
	}
	while (SPI.available())
		;
}

void setup(){
	Serial0.begin();
	SPI.begin(SCK, MISO, MOSI, SS);
	SPI.setSlave(true);
	SPI.onRequest(handler);
}

void loop(){
}