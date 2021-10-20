//
// Sample of using Async reading of Dallas Temperature Sensors
// 
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress;

int  resolution = 12;
unsigned long lastTempRequest = 0;
unsigned long delayInMillis = 0;
float temperature = 0.0;
int idle = 0;

void setup(void) {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature Control Library - Async Demo");
	MY_SERIAL.print("Library Version: ");
	MY_SERIAL.println(DALLASTEMPLIBVERSION);
	MY_SERIAL.println("\n");

	sensors.begin();
	sensors.getAddress(tempDeviceAddress, 0);
	sensors.setResolution(tempDeviceAddress, resolution);
	
	sensors.setWaitForConversion(false);
	sensors.requestTemperatures();
	delayInMillis = 750 / (1 << (12 - resolution)); 
	lastTempRequest = millis(); 
	
	pinMode(13, OUTPUT); 
}

void loop(void) {
	if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
	{
		digitalWrite(13, LOW);
		MY_SERIAL.print(" Temperature: ");
		temperature = sensors.getTempCByIndex(0);
		MY_SERIAL.println(temperature, resolution - 8); 
		MY_SERIAL.print("  Resolution: ");
		MY_SERIAL.println(resolution); 
		MY_SERIAL.print("Idle counter: ");
		MY_SERIAL.println(idle);     
		MY_SERIAL.println(); 
		
		idle = 0; 
			
		// immediately after fetching the temperature we request a new sample 
		// in the async modus
		// for the demo we let the resolution change to show differences
		resolution++;
		if (resolution > 12) resolution = 9;
		
		sensors.setResolution(tempDeviceAddress, resolution);
		sensors.requestTemperatures(); 
		delayInMillis = 750 / (1 << (12 - resolution));
		lastTempRequest = millis(); 
	}
	
	digitalWrite(13, HIGH);
	// we can do usefull things here 
	// for the demo we just count the idle time in millis
	delay(1);
	idle++;
}
