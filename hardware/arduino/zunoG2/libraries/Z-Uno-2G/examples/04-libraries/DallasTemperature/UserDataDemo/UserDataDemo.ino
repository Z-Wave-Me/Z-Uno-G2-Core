// PURPOSE: use of alarm field as user identification demo
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS	9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uint8_t deviceCount = 0;

// Add 4 prepared sensors to the bus
// use the UserDataWriteBatch demo to prepare 4 different labeled sensors
struct
{
	int id;
	DeviceAddress addr;
} T[4];

float getTempByID(int id) {
	for (uint8_t index = 0; index < deviceCount; index++)
	{
		if (T[index].id == id)
		{
		return sensors.getTempC(T[index].addr);
		}
	}
	return (-999);
}

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
	MY_SERIAL.println("Dallas Temperature Demo");

	sensors.begin();
	
	// count devices
	deviceCount = sensors.getDeviceCount();
	MY_SERIAL.print("#devices: ");
	MY_SERIAL.println(deviceCount);

	// Read ID's per sensor
	// and put them in T array
	for (uint8_t index = 0; index < deviceCount; index++) {
		// go through sensors
		sensors.getAddress(T[index].addr, index);
		T[index].id = sensors.getUserData(T[index].addr);
	}

	// Check all 4 sensors are set
	for (uint8_t index = 0; index < deviceCount; index++) {
		MY_SERIAL.println();
		MY_SERIAL.println(T[index].id);
		printAddress(T[index].addr);
		MY_SERIAL.println();
	}
	MY_SERIAL.println();
}


void loop(void) {
	MY_SERIAL.println();
	MY_SERIAL.print(millis());
	MY_SERIAL.println("\treq temp");
	sensors.requestTemperatures();

	MY_SERIAL.print(millis());
	MY_SERIAL.println("\tGet temp by address");
	for (int i = 0; i < 4; i++) {
		MY_SERIAL.print(millis());
		MY_SERIAL.print("\t temp:\t");
		MY_SERIAL.println(sensors.getTempC(T[i].addr));
	}

	MY_SERIAL.print(millis());
	MY_SERIAL.println("\tGet temp by ID");  // assume ID = 0, 1, 2, 3
	for (int id = 0; id < 4; id++) {
		MY_SERIAL.print(millis());
		MY_SERIAL.print("\t temp:\t");
		MY_SERIAL.println(getTempByID(id));
	}

	delay(1000);
}
