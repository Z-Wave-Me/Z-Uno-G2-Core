/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.
*/

#define MY_SERIAL		Serial

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

// the setup routine runs once when you press reset:
void setup() {
	// initialize serial communication at 9600 bits per second:
	MY_SERIAL.begin(9600);
	// make the pushbutton's pin an input:
	pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
	// read the input pin:
	int buttonState = digitalRead(pushButton);
	// print out the state of the button:
	MY_SERIAL.println(buttonState);
	delay(1);        // delay in between reads for stability
}
