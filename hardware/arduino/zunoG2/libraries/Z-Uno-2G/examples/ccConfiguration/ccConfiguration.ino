#include "Arduino.h"

#define MY_SERIAL Serial0

//initial period of the blink is 1 second
byte dimmerValue=100;
byte savedimmerValue;

//Next line sets up Z-Uno channels. In this case it adds the Switch Multilevel channel
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getSwitchMultilevelValue,setSwitchMultilevelValue));

// the setup function runs once, when you press reset or power the board
void setup() {
	size_t				tempos;

	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	// set digital pin 13 as an output.
	pinMode(LED_BUILTIN, OUTPUT);
	tempos = zunoLoadCFGParam(64);
	dimmerValue = tempos >= 0xFF ? dimmerValue : tempos;
	savedimmerValue = dimmerValue;
}

// the loop function runs over and over again forever
void loop() {
	MY_SERIAL.println("Loop");
	digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
	delay(dimmerValue*10);           // wait for timeout
	digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
	delay(dimmerValue*10);           // wait for timeout
	if (savedimmerValue != dimmerValue) {
		savedimmerValue = dimmerValue;
		zunoSaveCFGParam(64, dimmerValue);
	}
}

//The setSwitchMultilevelValue runs only when a new value comes from the controller by Z-Wave
void setSwitchMultilevelValue(byte newValue) {
	//save new value in a variable
	dimmerValue = newValue;
}

//The setSwitchMultilevelValue runs only when the controller asks for the current blink rate by Z-Wave
byte getSwitchMultilevelValue(void) {
	//return previously saved value
	return dimmerValue;
}

ZUNO_SETUP_CFGPARAMETER_HANDLER(config_parameter_changed);


void config_parameter_changed(byte param, word value) {
	if (param == 64) { // The first user-defined parameter
		dimmerValue = value;
	}
}