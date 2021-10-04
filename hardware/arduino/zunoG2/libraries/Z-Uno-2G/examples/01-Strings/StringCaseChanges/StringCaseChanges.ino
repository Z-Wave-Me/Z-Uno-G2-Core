/*
  String Case changes

  Examples of how to change the case of a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(9600);

	// send an intro:
	MY_SERIAL.println("\n\nString case changes:");
	MY_SERIAL.println();
}

void loop() {
	// toUpperCase() changes all letters to upper case:
	String stringOne = "<html><head><body>";
	MY_SERIAL.println(stringOne);
	stringOne.toUpperCase();
	MY_SERIAL.println(stringOne);

	// toLowerCase() changes all letters to lower case:
	String stringTwo = "</BODY></HTML>";
	MY_SERIAL.println(stringTwo);
	stringTwo.toLowerCase();
	MY_SERIAL.println(stringTwo);


	// do nothing while true:
	while (true)
		delay(10);
}
