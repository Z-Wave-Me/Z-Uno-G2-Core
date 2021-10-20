#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

OneWire ds18x20[] = { 9, 10 };
const int oneWireCount = (sizeof(ds18x20)/sizeof(OneWire));
DallasTemperature sensor[oneWireCount];

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature Multiple Bus Control Library Simple Demo");
	MY_SERIAL.print("============Ready with ");
	MY_SERIAL.print(oneWireCount);
	MY_SERIAL.println(" Sensors================");
	
	// Start up the library on all defined bus-wires
	DeviceAddress deviceAddress;
	for (int i = 0; i < oneWireCount; i++) {;
		sensor[i].setOneWire(&ds18x20[i]);
		sensor[i].begin();
		if (sensor[i].getAddress(deviceAddress, 0)) sensor[i].setResolution(deviceAddress, 12);
	}
}

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature 
	// request to all devices on the bus
	MY_SERIAL.print("Requesting temperatures...");
	for (int i = 0; i < oneWireCount; i++) {
		sensor[i].requestTemperatures();
	}
	MY_SERIAL.println("DONE");
	
	delay(1000);
	for (int i = 0; i < oneWireCount; i++) {
		float temperature = sensor[i].getTempCByIndex(0);
		MY_SERIAL.print("Temperature for the sensor ");
		MY_SERIAL.print(i);
		MY_SERIAL.print(" is ");
		MY_SERIAL.println(temperature);
	}
	MY_SERIAL.println();
}