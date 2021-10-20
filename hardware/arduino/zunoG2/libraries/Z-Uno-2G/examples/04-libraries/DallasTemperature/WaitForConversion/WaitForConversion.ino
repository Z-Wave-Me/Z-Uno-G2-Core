#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature Control Library - Async Demo");
	MY_SERIAL.println("\nDemo shows the difference in length of the call\n\n");

	// Start up the library
	sensors.begin();
}

void loop(void) {
	// Request temperature conversion (traditional)
	MY_SERIAL.println("Before blocking requestForConversion");
	unsigned long start = millis();    

	sensors.requestTemperatures();

	unsigned long stop = millis();
	MY_SERIAL.println("After blocking requestForConversion");
	MY_SERIAL.print("Time used: ");
	MY_SERIAL.println(stop - start);
	
	// get temperature
	MY_SERIAL.print("Temperature: ");
	MY_SERIAL.println(sensors.getTempCByIndex(0));  
	MY_SERIAL.println("\n");
	
	// Request temperature conversion - non-blocking / async
	MY_SERIAL.println("Before NON-blocking/async requestForConversion");
	start = millis();       
	sensors.setWaitForConversion(false);  // makes it async
	sensors.requestTemperatures();
	sensors.setWaitForConversion(true);
	stop = millis();
	MY_SERIAL.println("After NON-blocking/async requestForConversion");
	MY_SERIAL.print("Time used: ");
	MY_SERIAL.println(stop - start); 
	
	
	// 9 bit resolution by default 
	// Note the programmer is responsible for the right delay
	// we could do something usefull here instead of the delay
	int resolution = 9;
	delay(750/ (1 << (12-resolution)));
	
	// get temperature
	MY_SERIAL.print("Temperature: ");
	MY_SERIAL.println(sensors.getTempCByIndex(0));  
	MY_SERIAL.println("\n\n\n\n");  
	
	delay(5000);
}
