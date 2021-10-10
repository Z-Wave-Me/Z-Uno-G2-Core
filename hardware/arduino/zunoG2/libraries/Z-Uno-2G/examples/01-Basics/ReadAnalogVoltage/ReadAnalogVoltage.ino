/*
  ReadAnalogVoltage

  This example code is in the public domain.

*/

#define MY_SERIAL		Serial

// the setup routine runs once when you press reset:
void setup() {
	// initialize serial communication at 115200 bits per second:
	MY_SERIAL.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
	// read the input on analog pin 0:
	int sensorValue = analogRead(A0);
	// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
	float voltage = sensorValue * (5.0 / 1023.0);
	// print out the value you read:
	MY_SERIAL.println(voltage);
}
