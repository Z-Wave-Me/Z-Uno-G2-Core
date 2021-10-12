/*
  String replace()

  Examples of how to replace characters or substrings of a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString replace:\n");
	MY_SERIAL.println();
	}

	void loop() {
	String stringOne = "<html><head><body>";
	MY_SERIAL.println(stringOne);
	// replace() changes all instances of one substring with another:
	// first, make a copy of the original string:
	String stringTwo = stringOne;
	// then perform the replacements:
	stringTwo.replace("<", "</");
	// print the original:
	MY_SERIAL.println("Original string: " + stringOne);
	// and print the modified string:
	MY_SERIAL.println("Modified string: " + stringTwo);

	// you can also use replace() on single characters:
	String normalString = "bookkeeper";
	MY_SERIAL.println("normal: " + normalString);
	String leetString = normalString;
	leetString.replace('o', '0');
	leetString.replace('e', '3');
	MY_SERIAL.println("l33tspeak: " + leetString);

	// do nothing while true:
	while (true)
		delay(10);
}
