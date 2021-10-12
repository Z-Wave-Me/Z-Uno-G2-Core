/*
  String length() and trim()

  Examples of how to use length() and trim() in a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString length() and trim():");
	MY_SERIAL.println();
}

void loop() {
	// here's a String with empty spaces at the end (called white space):
	String stringOne = "Hello!       ";
	MY_SERIAL.print(stringOne);
	MY_SERIAL.print("<--- end of string. Length: ");
	MY_SERIAL.println(stringOne.length());

	// trim the white space off the string:
	stringOne.trim();
	MY_SERIAL.print(stringOne);
	MY_SERIAL.print("<--- end of trimmed string. Length: ");
	MY_SERIAL.println(stringOne.length());

	// do nothing while true:
	while (true)
		delay(10);
}
