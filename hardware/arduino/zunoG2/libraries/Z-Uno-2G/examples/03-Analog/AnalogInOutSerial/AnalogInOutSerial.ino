/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  This example code is in the public domain.

*/

#define MY_SERIAL		Serial

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
	// initialize serial communications at 115200 bps:
	MY_SERIAL.begin(115200);
}

void loop() {
	// read the analog in value:
	sensorValue = analogRead(analogInPin);
	// map it to the range of the analog out:
	outputValue = map(sensorValue, 0, 1023, 0, 255);
	// change the analog out value:
	analogWrite(analogOutPin, outputValue);

	// print the results to the Serial Monitor:
	MY_SERIAL.print("sensor = ");
	MY_SERIAL.print(sensorValue);
	MY_SERIAL.print("\t output = ");
	MY_SERIAL.println(outputValue);

	// wait 2 milliseconds before the next loop for the analog-to-digital
	// converter to settle after the last reading:
	delay(2);
}
