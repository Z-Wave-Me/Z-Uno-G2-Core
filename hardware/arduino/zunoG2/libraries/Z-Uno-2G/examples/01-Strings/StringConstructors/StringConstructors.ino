/*
  String constructors

  Examples of how to create Strings from other data types

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(9600);

	// send an intro:
	MY_SERIAL.println("\n\nString Constructors:");
	MY_SERIAL.println();
}

void loop() {
	// using a constant String:
	String stringOne = "Hello String";
	MY_SERIAL.println(stringOne);      // prints "Hello String"

	// converting a constant char into a String:
	stringOne =  String('a');
	MY_SERIAL.println(stringOne);       // prints "a"

	// converting a constant string into a String object:
	String stringTwo =  String("This is a string");
	MY_SERIAL.println(stringTwo);      // prints "This is a string"

	// concatenating two strings:
	stringOne =  String(stringTwo + " with more");
	// prints "This is a string with more":
	MY_SERIAL.println(stringOne);

	// using a constant integer:
	stringOne =  String(13);
	MY_SERIAL.println(stringOne);      // prints "13"

	// using an int and a base:
	stringOne =  String(analogRead(A0), DEC);
	// prints "453" or whatever the value of analogRead(A0) is
	MY_SERIAL.println(stringOne);

	// using an int and a base (hexadecimal):
	stringOne =  String(45, HEX);
	// prints "2d", which is the hexadecimal version of decimal 45:
	MY_SERIAL.println(stringOne);

	// using an int and a base (binary)
	stringOne =  String(255, BIN);
	// prints "11111111" which is the binary value of 255
	MY_SERIAL.println(stringOne);

	// using a long and a base:
	stringOne =  String(millis(), DEC);
	// prints "123456" or whatever the value of millis() is:
	MY_SERIAL.println(stringOne);

	// using a float and the right decimal places:
	stringOne = String(5.698, 3);
	MY_SERIAL.println(stringOne);

	// using a float and less decimal places to use rounding:
	stringOne = String(5.698, 2);
	MY_SERIAL.println(stringOne);

	// do nothing while true:
	while (true)
		delay(10);
}
