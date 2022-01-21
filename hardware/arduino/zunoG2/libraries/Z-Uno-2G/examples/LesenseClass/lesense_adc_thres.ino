#include "Arduino.h"
#include "LesenseClass.h"

#define MY_SERIAL Serial

bool functionAdc(uint8_t pin, uint16_t value) {
	MY_SERIAL.printf("pin %d value %d\n", pin, value);
	return (true);
}

void setup(){
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	analogReadResolution(12);
	Lesense.setScanSequence(500000);
	Lesense.addAdc(A2, functionAdc);
	Lesense.adcThres(A2, 1000, lesenseCompModeGreaterOrEq);
}

void loop(){
	delay(1000);
	MY_SERIAL.println("Loop");
}
