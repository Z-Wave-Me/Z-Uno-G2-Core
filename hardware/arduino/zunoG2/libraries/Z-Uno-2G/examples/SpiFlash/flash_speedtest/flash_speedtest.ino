#include "SpiFlash.h"

#define MY_SERIAL							Serial

SpiFlashClass spi_flash(&SPI, SS);

const SpiFlashClassDevice_t device = SPI_FLASH_CLASS_M25PE40;

#define BUFSIZE   4096

// 4 byte aligned buffer has best result with nRF QSPI
uint8_t bufwrite[BUFSIZE] __attribute__ ((aligned(4)));
uint8_t bufread[BUFSIZE] __attribute__ ((aligned(4)));

void setup(void) {
	ZUNO_ERROR_TYPE						ret;
	uint32_t							JEDEC_ID;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println("SPI Flash Speed Test example");
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
	MY_SERIAL.print("\n");
	write_and_compare(0xAA);
	write_and_compare(0x55);
	MY_SERIAL.println("Speed test is completed.");
}

void print_speed(const char* text, uint32_t count, uint32_t ms) {
	MY_SERIAL.print(text);
	MY_SERIAL.print(count);
	MY_SERIAL.print(" bytes in ");
	MY_SERIAL.print(ms / 1000.0F, 2);
	MY_SERIAL.println(" seconds.");

	MY_SERIAL.print("Speed : ");
	MY_SERIAL.print( (count / 1000.0F) / (ms / 1000.0F), 2);
	MY_SERIAL.println(" KB/s.\r\n");
}

bool write_and_compare(uint8_t pattern) {
	ZUNO_ERROR_TYPE						ret;
	uint32_t							ms;
	uint32_t							ms_write;
	uint32_t							ms_read;
	static const uint32_t				flash_sz = device.total_size;

	MY_SERIAL.println("Erase chip");
	if ((ret = spi_flash.eraseChip()) != ZUNO_ERROR_SUCCESS) {
		MY_SERIAL.printf("Error: cannot erase chip device - %08lX\n", ret);
		while (0xFF)
			delay(0x10);
	}
	// write all
	memset(bufwrite, (int) pattern, sizeof(bufwrite));
	MY_SERIAL.printf("Write flash with 0x%02X\n", pattern);
	ms = millis();
	for(uint32_t addr = 0; addr < flash_sz; addr += sizeof(bufwrite)) {
		if ((ret = spi_flash.writeBuffer(addr, bufwrite, sizeof(bufwrite))) != ZUNO_ERROR_SUCCESS) {
			MY_SERIAL.printf("Error: cannot write - %08lX\n", ret);
			while (0xFF)
				delay(0x10);
		}
	}
	ms_write = millis() - ms;
	print_speed("Write ", flash_sz, ms_write);
	// read and compare
	MY_SERIAL.println("Read flash and compare");
	ms_read = 0;
	for(uint32_t addr = 0; addr < flash_sz; addr += sizeof(bufread)) {
		memset(bufread, 0, sizeof(bufread));
		ms = millis();
		if ((ret = spi_flash.read(addr, bufread, sizeof(bufread))) != ZUNO_ERROR_SUCCESS) {
			MY_SERIAL.printf("Error: cannot read - %08lX\n", ret);
			while (0xFF)
				delay(0x10);
		}
		ms_read += millis() - ms;
		if ( memcmp(bufwrite, bufread, BUFSIZE)) {
			MY_SERIAL.printf("Error: flash contents mismatched at address 0x%08lX!!!", addr);
			for(uint32_t i=0; i<sizeof(bufread); i++) {
				if ( i != 0 ) MY_SERIAL.print(' ');
				if ( (i%16 == 0) )
				{
				MY_SERIAL.println();
				MY_SERIAL.printf("%03lX: ", i);
				}

				MY_SERIAL.printf("%02X", bufread[i]);
			}
			MY_SERIAL.println();
			return (false);
		}
	}
	print_speed("Read  ", flash_sz, ms_read);
	return (true);
}

void loop(void) {
	// nothing to do
}
