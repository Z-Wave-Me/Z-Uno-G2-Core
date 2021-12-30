#include "Arduino.h"
#include "em_emu.h"

#define MY_SERIAL		Serial


static int8_t _getTemp(void)
{
	float tempCelsius;
	int8_t result;

	tempCelsius = EMU_TemperatureGet();

	if (tempCelsius < INT8_MIN) {
		tempCelsius = INT8_MIN;
	} else if (tempCelsius > INT8_MAX) {
		tempCelsius = INT8_MAX;
	}

	// adding extra 0.5 before truncating to simulate rounding behavior
	result = (((int8_t) (tempCelsius + 0.5 - INT8_MIN)) + INT8_MIN);
	return result;
}


void setup(){
	MY_SERIAL.begin(115200);
}

void loop(){
	MY_SERIAL.printf("EMU temperature: %d\n", _getTemp());
	delay(2000);
}