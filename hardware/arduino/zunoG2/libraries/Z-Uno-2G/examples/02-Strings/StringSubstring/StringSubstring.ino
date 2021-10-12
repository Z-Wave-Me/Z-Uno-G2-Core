/*
  String substring()

  Examples of how to use substring in a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString  substring():");
	MY_SERIAL.println();
}

void loop() {
	// Set up a String:
	String stringOne = "Content-Type: text/html";
	MY_SERIAL.println(stringOne);

	// substring(index) looks for the substring from the index position to the end:
	if (stringOne.substring(19) == "html") {
		MY_SERIAL.println("It's an html file");
	}
	// you can also look for a substring in the middle of a string:
	if (stringOne.substring(14, 18) == "text") {
		MY_SERIAL.println("It's a text-based file");
	}

	// do nothing while true:
	while (true)
		delay(10);
}
