#include "SpiFlash.h"

#define MY_SERIAL							Serial

SpiFlashClass spi_flash(&SPI, SS);

void setup(void) {
	ZUNO_ERROR_TYPE						ret;
	uint32_t							JEDEC_ID;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Setup");
	SPI.begin(SCK, MISO, MOSI, UNKNOWN_PIN);
	if ((ret = spi_flash.begin(0x0, &JEDEC_ID)) != ZUNO_ERROR_SUCCESS) {
		MY_SERIAL.printf("Error: cannot initilzed device - %08lX\n", ret);
		while (0xFF)
			delay(0x10);
	}
	MY_SERIAL.print("JEDEC ID: 0x");
	MY_SERIAL.println(JEDEC_ID, HEX);
}

void loop(void) {

}