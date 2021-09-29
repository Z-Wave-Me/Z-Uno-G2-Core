#include "Arduino.h"
#include "ZUNO_Buttons.h"

#define MY_SERIAL Serial0

#define BUTTON		23

uint8_t dimmerValue = 100;

// the setup function runs once, when you press reset or power the board
void setup() {
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	pinMode(LED_BUILTIN, OUTPUT);
	Btn.addButton(BUTTON);
}

// the loop function runs over and over again forever
void loop() {
	digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
	delay(dimmerValue*10);           // wait for timeout
	digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
	delay(dimmerValue*10);           // wait for timeout
	process_buttons();
	MY_SERIAL.println("Loop");
}

void process_buttons() {
	if(Btn.isSingleClick(BUTTON)) {
		MY_SERIAL.println("isSingleClick");
		if (dimmerValue == 5)
			dimmerValue = 100;
		else
			dimmerValue = 5;
	}
	if(Btn.isTripleClick(BUTTON)) {
		MY_SERIAL.println("isTripleClick");
		if (dimmerValue == 5)
			dimmerValue = 100;
		else
			dimmerValue = 5;
	}
	if(Btn.isLongClick(BUTTON)) {
		MY_SERIAL.println("isLongClick");
		if (dimmerValue == 5)
			dimmerValue = 100;
		else
			dimmerValue = 5;
	}
	if(Btn.isDoubleClick(BUTTON)) {
		MY_SERIAL.println("isDoubleClick");
		if (dimmerValue == 5)
			dimmerValue = 100;
		else
			dimmerValue = 5;
	}
	if(Btn.isSingleClick(2)) {
		MY_SERIAL.println("isSingleClick");
		Btn.deleteButton(2);
		if (dimmerValue == 5)
			dimmerValue = 100;
		else
			dimmerValue = 5;
	}
}