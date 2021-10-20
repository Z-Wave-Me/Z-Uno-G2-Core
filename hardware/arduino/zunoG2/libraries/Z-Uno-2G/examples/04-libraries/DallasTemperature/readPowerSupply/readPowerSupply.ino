// Include the libraries we need
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;
// Assign address manually. The addresses below will beed to be changed
// to valid device addresses on your bus. Device address can be retrieved
// by using either oneWire.search(deviceAddress) or individually via
// sensors.getAddress(deviceAddress, index)
// DeviceAddress insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
// DeviceAddress outsideThermometer   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

int devCount = 0;

/*
 * The setup function. We only start the sensors here
 */
void setup(void) {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Arduino Temperature Control Library Demo - readPowerSupply");

	sensors.begin();

	devCount = sensors.getDeviceCount();
	MY_SERIAL.print("#devices: ");
	MY_SERIAL.println(devCount);

	// report parasite power requirements
	MY_SERIAL.print("Parasite power is: ");
	if (sensors.readPowerSupply()) MY_SERIAL.println("ON");  // no address means "scan all devices for parasite mode"
	else MY_SERIAL.println("OFF");

	// Search for devices on the bus and assign based on an index.
	if (!sensors.getAddress(insideThermometer, 0)) MY_SERIAL.println("Unable to find address for Device 0");
	if (!sensors.getAddress(outsideThermometer, 1)) MY_SERIAL.println("Unable to find address for Device 1");

	// show the addresses we found on the bus
	MY_SERIAL.print("Device 0 Address: ");
	printAddress(insideThermometer);
	MY_SERIAL.println();
	MY_SERIAL.print("Power = parasite: ");
	MY_SERIAL.println(sensors.readPowerSupply(insideThermometer));
	MY_SERIAL.println();
	MY_SERIAL.println();

	MY_SERIAL.print("Device 1 Address: ");
	printAddress(outsideThermometer);
	MY_SERIAL.println();
	MY_SERIAL.print("Power = parasite: ");
	MY_SERIAL.println(sensors.readPowerSupply(outsideThermometer));
	MY_SERIAL.println();
	MY_SERIAL.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++) {
		// zero pad the address if necessary
		if (deviceAddress[i] < 0x10) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
}

// empty on purpose
void loop(void) {
}
