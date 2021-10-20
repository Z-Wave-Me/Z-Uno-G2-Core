#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

#define TEMPERATURE_PRECISION 9 // Lower resolution

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature IC Control Library Demo");

	// Start up the library
	sensors.begin();
	
	// Grab a count of devices on the wire
	numberOfDevices = sensors.getDeviceCount();
	
	// locate devices on the bus
	MY_SERIAL.print("Locating devices...");
	
	MY_SERIAL.print("Found ");
	MY_SERIAL.print(numberOfDevices, DEC);
	MY_SERIAL.println(" devices.");

	// report parasite power requirements
	MY_SERIAL.print("Parasite power is: "); 
	if (sensors.isParasitePowerMode()) MY_SERIAL.println("ON");
	else MY_SERIAL.println("OFF");
	
	// Loop through each device, print out address
	for(int i=0;i<numberOfDevices; i++) {
		// Search the wire for address
		if(sensors.getAddress(tempDeviceAddress, i)) {
			MY_SERIAL.print("Found device ");
			MY_SERIAL.print(i, DEC);
			MY_SERIAL.print(" with address: ");
			printAddress(tempDeviceAddress);
			MY_SERIAL.println();
			
			MY_SERIAL.print("Setting resolution to ");
			MY_SERIAL.println(TEMPERATURE_PRECISION, DEC);
			
			// set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
			sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
			
			MY_SERIAL.print("Resolution actually set to: ");
			MY_SERIAL.print(sensors.getResolution(tempDeviceAddress), DEC); 
			MY_SERIAL.println();
		}
		else {
			MY_SERIAL.print("Found ghost device at ");
			MY_SERIAL.print(i, DEC);
			MY_SERIAL.print(" but could not detect address. Check power and cabling");
		}
	}
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress) {
	// method 1 - slower
	//MY_SERIAL.print("Temp C: ");
	//MY_SERIAL.print(sensors.getTempC(deviceAddress));
	//MY_SERIAL.print(" Temp F: ");
	//MY_SERIAL.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

	// method 2 - faster
	float tempC = sensors.getTempC(deviceAddress);
	if(tempC == DEVICE_DISCONNECTED_C) 
	{
		MY_SERIAL.println("Error: Could not read temperature data");
		return;
	}
	MY_SERIAL.print("Temp C: ");
	MY_SERIAL.print(tempC);
	MY_SERIAL.print(" Temp F: ");
	MY_SERIAL.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature 
	// request to all devices on the bus
	MY_SERIAL.print("Requesting temperatures...");
	sensors.requestTemperatures(); // Send the command to get temperatures
	MY_SERIAL.println("DONE");
	
	
	// Loop through each device, print out temperature data
	for(int i=0;i<numberOfDevices; i++) {
		// Search the wire for address
		if(sensors.getAddress(tempDeviceAddress, i))
		{
			// Output the device ID
			MY_SERIAL.print("Temperature for device: ");
			MY_SERIAL.println(i,DEC);
			
			// It responds almost immediately. Let's print out the data
			printTemperature(tempDeviceAddress); // Use a simple function to print out the data
		} 
		//else ghost device! Check your power requirements and cabling
		
	}
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++) {
		if (deviceAddress[i] < 16) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
}
