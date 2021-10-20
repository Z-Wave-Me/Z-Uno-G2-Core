// PURPOSE: scan for 1-Wire devices + code snippet generator

#include "ZUNO_OneWire.h"

#define MY_SERIAL		Serial

void setup() {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("//\n// Start oneWireSearch.ino \n//");

	for (uint8_t pin = 2; pin < 13; pin++)
		findDevices(pin);
	MY_SERIAL.println("\n//\n// End oneWireSearch.ino \n//");
}

void loop() {
}

uint8_t findDevices(int pin) {
	OneWire ow(pin);

	uint8_t address[8];
	uint8_t count = 0;


	if (ow.search(address)) {
		MY_SERIAL.print("\nuint8_t pin");
		MY_SERIAL.print(pin, DEC);
		MY_SERIAL.println("[][8] = {");
		do {
		count++;
		MY_SERIAL.println("  {");
		for (uint8_t i = 0; i < 8; i++)
		{
			MY_SERIAL.print("0x");
			if (address[i] < 0x10) MY_SERIAL.print("0");
			MY_SERIAL.print(address[i], HEX);
			if (i < 7) MY_SERIAL.print(", ");
		}
		MY_SERIAL.println("  },");
		} while (ow.search(address));

		MY_SERIAL.println("};");
		MY_SERIAL.print("// nr devices found: ");
		MY_SERIAL.println(count);
	}
	return count;
}
