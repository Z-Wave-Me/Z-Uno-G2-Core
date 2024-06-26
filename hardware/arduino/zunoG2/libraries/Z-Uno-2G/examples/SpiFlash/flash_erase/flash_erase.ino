#include "SpiFlash.h"

#define MY_SERIAL							Serial

SpiFlashClass spi_flash = SpiFlashClass();

const SpiFlashClassDevice_t device = SPI_FLASH_CLASS_M25PE40;

void setup(void) {
	uint32_t							ms;
	uint32_t							JEDEC_ID;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println();
	MY_SERIAL.println("SPI Flash Total Erase Example");
	if (spi_flash.begin(&device) != true) {
		MY_SERIAL.print("Error: cannot initilzed device\n");
		while (0xFF)
			delay(0x10);
	}
	spi_flash.getJEDECID(&JEDEC_ID);
	MY_SERIAL.print("JEDEC ID: 0x");
	MY_SERIAL.println(JEDEC_ID, HEX);
	MY_SERIAL.print("Flash size: ");
	MY_SERIAL.println(device.total_size);
	// Wait for user to send OK to continue.
	MY_SERIAL.setTimeout(30000);  // Increase timeout to print message less frequently.
	do {
		MY_SERIAL.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		MY_SERIAL.println("This sketch will ERASE ALL DATA on the flash chip!");
		MY_SERIAL.println("Type OK (all caps) and press enter to continue.");
		MY_SERIAL.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
	while (!MY_SERIAL.find("OK"));

	MY_SERIAL.println("Erasing flash chip in 1 seconds and more...");
	MY_SERIAL.println("Let it run until the flash erase is finished.");
	MY_SERIAL.println("An error or success message will be printed when complete.");
	ms = millis();
	if (spi_flash.eraseChip() != true) {
		MY_SERIAL.println("Failed to erase chip!");
	}
	else {
		ms = millis() - ms;
		MY_SERIAL.printf("Successfully erased chip! - timed ~ %.1f seconds\n", ((float)ms / 1000));
	}
}

void loop(void) {
}