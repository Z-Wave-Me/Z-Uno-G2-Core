// Include the libraries we need
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;

// Assign address manually. The addresses below will need to be changed
// to valid device addresses on your bus. Device address can be retrieved
// by using either oneWire.search(deviceAddress) or individually via
// sensors.getAddress(deviceAddress, index)
// DeviceAddress insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
// DeviceAddress outsideThermometer   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature IC Control Library Demo");

	// Start up the library
	sensors.begin();

	// locate devices on the bus
	MY_SERIAL.print("Locating devices...");
	MY_SERIAL.print("Found ");
	MY_SERIAL.print(sensors.getDeviceCount(), DEC);
	MY_SERIAL.println(" devices.");

	// report parasite power requirements
	MY_SERIAL.print("Parasite power is: ");
	if (sensors.isParasitePowerMode()) MY_SERIAL.println("ON");
	else MY_SERIAL.println("OFF");

	// Search for devices on the bus and assign based on an index. Ideally,
	// you would do this to initially discover addresses on the bus and then
	// use those addresses and manually assign them (see above) once you know
	// the devices on your bus (and assuming they don't change).
	//
	// method 1: by index
	if (!sensors.getAddress(insideThermometer, 0)) MY_SERIAL.println("Unable to find address for Device 0");
	if (!sensors.getAddress(outsideThermometer, 1)) MY_SERIAL.println("Unable to find address for Device 1");

	// method 2: search()
	// search() looks for the next device. Returns 1 if a new address has been
	// returned. A zero might mean that the bus is shorted, there are no devices,
	// or you have already retrieved all of them. It might be a good idea to
	// check the CRC to make sure you didn't get garbage. The order is
	// deterministic. You will always get the same devices in the same order
	//
	// Must be called before search()
	//oneWire.reset_search();
	// assigns the first address found to insideThermometer
	//if (!oneWire.search(insideThermometer)) MY_SERIAL.println("Unable to find address for insideThermometer");
	// assigns the seconds address found to outsideThermometer
	//if (!oneWire.search(outsideThermometer)) MY_SERIAL.println("Unable to find address for outsideThermometer");

	// show the addresses we found on the bus
	MY_SERIAL.print("Device 0 Address: ");
	printAddress(insideThermometer);
	MY_SERIAL.println();

	MY_SERIAL.print("Device 1 Address: ");
	printAddress(outsideThermometer);
	MY_SERIAL.println();

	// set the resolution to 9 bit per device
	sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
	sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

	MY_SERIAL.print("Device 0 Resolution: ");
	MY_SERIAL.print(sensors.getResolution(insideThermometer), DEC);
	MY_SERIAL.println();

	MY_SERIAL.print("Device 1 Resolution: ");
	MY_SERIAL.print(sensors.getResolution(outsideThermometer), DEC);
	MY_SERIAL.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++) {
		// zero pad the address if necessary
		if (deviceAddress[i] < 16) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress) {
	float tempC = sensors.getTempC(deviceAddress);
	if(tempC == DEVICE_DISCONNECTED_C) 
	{
		MY_SERIAL.println("Error: Could not read temperature data");
		return;
	}
	MY_SERIAL.print("Temp C: ");
	MY_SERIAL.print(tempC);
	MY_SERIAL.print(" Temp F: ");
	MY_SERIAL.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress) {
	MY_SERIAL.print("Resolution: ");
	MY_SERIAL.print(sensors.getResolution(deviceAddress));
	MY_SERIAL.println();
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress) {
	MY_SERIAL.print("Device Address: ");
	printAddress(deviceAddress);
	MY_SERIAL.print(" ");
	printTemperature(deviceAddress);
	MY_SERIAL.println();
}

/*
   Main function, calls the temperatures in a loop.
*/
void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature
	// request to all devices on the bus
	MY_SERIAL.print("Requesting temperatures...");
	sensors.requestTemperatures();
	MY_SERIAL.println("DONE");

	// print the device information
	printData(insideThermometer);
	printData(outsideThermometer);
}
