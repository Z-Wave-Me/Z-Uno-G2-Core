#include "Arduino.h"
#include "ZUNO_CCS811.h"

#define MY_SERIAL		Serial

ZUNO_CCS811 ccs;

void setup() {
	MY_SERIAL.begin(115200);

	MY_SERIAL.println("CCS811 test");
	delay(100);
	if(!ccs.begin()){
		MY_SERIAL.println("Failed to start sensor! Please check your wiring.");
		while(1)
			delay(100);
	}
	MY_SERIAL.println("begin ok");

	// Wait for the sensor to be ready
	while(!ccs.available()){
		delay(100);
	};
}

void loop() {
	if(ccs.available()){
		if(!ccs.readData()){
			MY_SERIAL.print("CO2: ");
			MY_SERIAL.print(ccs.geteCO2());
			MY_SERIAL.print("ppm, TVOC: ");
			MY_SERIAL.println(ccs.getTVOC());
		}
		else{
			MY_SERIAL.println("ERROR!");
			while(1)
				delay(100);
		}
		
	}
	delay(500);
}
