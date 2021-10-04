/*
  String to Integer conversion

  Reads a serial input string until it sees a newline, then converts the string
  to a number if the characters are digits.

  The circuit:
  - No external components needed.

*/

#define MY_SERIAL		Serial

String inString = "";    // string to hold input

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString toInt():");
	MY_SERIAL.println();
}

void loop() {
	// Read serial input:
	while (MY_SERIAL.available() > 0) {
		int inChar = MY_SERIAL.read();
		if (isDigit(inChar)) {
		// convert the incoming byte to a char and add it to the string:
		inString += (char)inChar;
		}
		// if you get a newline, print the string, then the string's value:
		if (inChar == '\n') {
		MY_SERIAL.print("Value:");
		MY_SERIAL.println(inString.toInt());
		MY_SERIAL.print("String: ");
		MY_SERIAL.println(inString);
		// clear the string for new input:
		inString = "";
		}
	}
}
