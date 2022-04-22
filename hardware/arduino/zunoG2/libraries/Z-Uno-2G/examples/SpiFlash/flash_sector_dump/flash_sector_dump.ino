#include "SpiFlash.h"

#define MY_SERIAL							Serial

SpiFlashClass spi_flash(&SPI, SS);

const SpiFlashClassDevice_t device = SPI_FLASH_CLASS_M25PE40;

void setup(void) {
	ZUNO_ERROR_TYPE						ret;
	uint32_t							JEDEC_ID;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println("SPI Flash Sector Dump example");
	SPI.begin(SCK, MISO, MOSI, UNKNOWN_PIN);
	if ((ret = spi_flash.begin(&device, &JEDEC_ID)) != ZUNO_ERROR_SUCCESS) {
		MY_SERIAL.printf("Error: cannot initilzed device - %08lX\n", ret);
		while (0xFF)
			delay(0x10);
	}
	MY_SERIAL.print("JEDEC ID: 0x");
	MY_SERIAL.println(JEDEC_ID, HEX);
	MY_SERIAL.print("Flash size: ");
	MY_SERIAL.println(device.total_size);
}

void dump_sector(uint32_t sector) {
	ZUNO_ERROR_TYPE							ret;
	static uint8_t							buf[4096];

	memset(buf, 0xff, sizeof(buf));
	if ((ret = spi_flash.read(sector*4096, buf, 4096)) != ZUNO_ERROR_SUCCESS) {
		MY_SERIAL.printf("Error: cannot read device - %08lX\n", ret);
		while (0xFF)
			delay(0x10);
	}
	for(uint32_t row=0; row<sizeof(buf)/16; row++) {
		if ( row == 0 ) MY_SERIAL.print("0");
		if ( row < 16 ) MY_SERIAL.print("0");
		MY_SERIAL.print(row*16, HEX);
		MY_SERIAL.print(" : ");
		for(uint32_t col=0; col<16; col++) {
			uint8_t val = buf[row*16 + col];

			if ( val < 16 ) MY_SERIAL.print("0");
			MY_SERIAL.print(val, HEX);

			MY_SERIAL.print(" ");
		}
		MY_SERIAL.println();
	}
}

void loop()
{
	MY_SERIAL.print("Enter the sector number to dump: ");
	while(!MY_SERIAL.available())
		delay(10);
	uint32_t sector = MY_SERIAL.parseInt();

	MY_SERIAL.println(sector); // echo

	if (sector < device.total_size / 4096)
	{
		dump_sector(sector);
	}else
	{
		MY_SERIAL.println("Invalid sector number");
	}

	MY_SERIAL.println();
	delay(10); // a bit of delay
}