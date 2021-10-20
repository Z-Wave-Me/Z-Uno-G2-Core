//
// This sketch does not use the ALARM registers and uses those 2 bytes as a counter
// these 2 bytes can be used for other purposes as well e.g. last temperature or
// a specific ID.
// 

#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int count = 0;

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature IC Control Library Demo");

	// Start up the library
	sensors.begin();
}

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature 
	// request to all devices on the bus
	MY_SERIAL.print("Requesting temperatures...");
	sensors.requestTemperatures(); // Send the command to get temperatures
	MY_SERIAL.println("DONE");
	
	MY_SERIAL.print("Temperature for the device 1 (index 0) is: ");
	MY_SERIAL.println(sensors.getTempCByIndex(0));  
	
	count++;
	sensors.setUserDataByIndex(0, count);
	int x = sensors.getUserDataByIndex(0);
	MY_SERIAL.println(count);
	(void)x;
}
