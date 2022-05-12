#include "SpiFlash.h"

#define MY_SERIAL							Serial

SpiFlashClass spi_flash = SpiFlashClass();

void setup(void) {
	uint32_t					JEDEC_ID;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println();
	MY_SERIAL.println("SPI Flash Info Example");
	if (spi_flash.begin(&JEDEC_ID) != true) {
		MY_SERIAL.print("Error: cannot initilzed device\n");
		while (0xFF)
			delay(0x10);
	}
	MY_SERIAL.print("JEDEC ID: 0x");
	MY_SERIAL.println(JEDEC_ID, HEX);
}

void loop(void) {

}