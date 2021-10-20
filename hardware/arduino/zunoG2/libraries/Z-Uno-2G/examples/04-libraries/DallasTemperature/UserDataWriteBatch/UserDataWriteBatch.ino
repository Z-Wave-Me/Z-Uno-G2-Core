// PURPOSE: use of alarm field as user identification demo

#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS	9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uint8_t deviceCount = 0;

void printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++)
	{
		// zero pad the address if necessary
		if (deviceAddress[i] < 16) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
}



void setup(void) {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println(__FILE__);
	MY_SERIAL.println("Write user ID to DS18B20\n");

	sensors.begin();

	// count devices
	deviceCount = sensors.getDeviceCount();
	MY_SERIAL.print("#devices: ");
	MY_SERIAL.println(deviceCount);
	
	MY_SERIAL.println();
	MY_SERIAL.println("current ID's");
	for (uint8_t index = 0; index < deviceCount; index++) {
		DeviceAddress t;
		sensors.getAddress(t, index);
		printAddress(t);
		MY_SERIAL.print("\t\tID: ");
		int id = sensors.getUserData(t);
		MY_SERIAL.println(id);
	}
	
	MY_SERIAL.println();
	MY_SERIAL.print("Enter ID for batch: ");
	int c = 0;
	int id = 0;
	while (c != '\n' && c != '\r') {
		c = MY_SERIAL.read();
		switch(c) {
			case '0'...'9':
				id *= 10;
				id += (c - '0');
				break;
			default:
				break;
		}
	}
	MY_SERIAL.println();
	MY_SERIAL.println(id);
	MY_SERIAL.println();

	MY_SERIAL.println("Start labeling ...");
	for (uint8_t index = 0; index < deviceCount; index++) {
		MY_SERIAL.print(".");
		DeviceAddress t;
		sensors.getAddress(t, index);
		sensors.setUserData(t, id);
	}
	MY_SERIAL.println();

	MY_SERIAL.println();
	MY_SERIAL.println("Show results ...");
	for (uint8_t index = 0; index < deviceCount; index++) {
		DeviceAddress t;
		sensors.getAddress(t, index);
		printAddress(t);
		MY_SERIAL.print("\t\tID: ");
		int id = sensors.getUserData(t);
		MY_SERIAL.println(id);
	}
	MY_SERIAL.println("Done ...");
}

void loop(void) {}
