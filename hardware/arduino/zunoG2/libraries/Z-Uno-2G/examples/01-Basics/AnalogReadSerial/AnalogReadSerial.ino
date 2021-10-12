/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

*/

#define MY_SERIAL		Serial

// the setup routine runs once when you press reset:
void setup() {
	// initialize serial communication at 115200 bits per second:
	MY_SERIAL.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
	// read the input on analog pin A0:
	int sensorValue = analogRead(A0);
	// print out the value you read:
	MY_SERIAL.println(sensorValue);
	delay(1);        // delay in between reads for stability
}
