#include "Arduino.h"
#include "ZUNO_CCS811.h"

ZUNO_CCS811 ccs;

void setup() {
	Serial.begin(9600);

	Serial.println("CCS811 test");
	delay(100);
	if(!ccs.begin()){
		Serial.println("Failed to start sensor! Please check your wiring.");
		while(1);
	}
	Serial.println("begin ok");

	// Wait for the sensor to be ready
	while(!ccs.available()){
		delay(100);
	};
}

void loop() {
	if(ccs.available()){
		if(!ccs.readData()){
			Serial.print("CO2: ");
			Serial.print(ccs.geteCO2());
			Serial.print("ppm, TVOC: ");
			Serial.println(ccs.getTVOC());
		}
		else{
			Serial.println("ERROR!");
			while(1);
		}
		
	}
	delay(500);
}
