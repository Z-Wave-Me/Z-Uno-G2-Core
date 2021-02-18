#include "Arduino.h"

#define MY_SERIAL Serial0

const byte ledPin = LED_BUILTIN;
const byte interruptPin = 23;
volatile byte state = LOW;

// the setup function runs once, when you press reset or power the board
void setup() {
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	pinMode(ledPin, OUTPUT_UP);
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(interruptPin, blink, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
	digitalWrite(ledPin, state);
}


void blink() {
	state = !state;
}