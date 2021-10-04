/*
  String length()

  Examples of how to use length() in a String.
  Open the Serial Monitor and start sending characters to see the results.

*/

#define MY_SERIAL		Serial

String txtMsg = "";                         // a string for incoming text
unsigned int lastStringLength = txtMsg.length();     // previous length of the String

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString  length():");
	MY_SERIAL.println();
}

void loop() {
	// add any incoming characters to the String:
	while (MY_SERIAL.available() > 0) {
		char inChar = MY_SERIAL.read();
		txtMsg += inChar;
	}

	// print the message and a notice if it's changed:
	if (txtMsg.length() != lastStringLength) {
		MY_SERIAL.println(txtMsg);
		MY_SERIAL.println(txtMsg.length());
		// if the String's longer than 140 characters, complain:
		if (txtMsg.length() < 140) {
		MY_SERIAL.println("That's a perfectly acceptable text message");
		} else {
		MY_SERIAL.println("That's too long for a text message.");
		}
		// note the length for next time through the loop:
		lastStringLength = txtMsg.length();
	}
}
