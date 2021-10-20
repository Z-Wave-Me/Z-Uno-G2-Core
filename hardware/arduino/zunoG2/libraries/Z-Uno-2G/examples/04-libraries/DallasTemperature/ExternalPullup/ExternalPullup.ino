#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS	9
#define ONE_WIRE_PULLUP	10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire, ONE_WIRE_PULLUP);

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
	
	for(int i=0;i<sensors.getDeviceCount();i++)
		MY_SERIAL.println("Temperature for Device "+String(i)+" is: " + String(sensors.getTempCByIndex(i)));
}
