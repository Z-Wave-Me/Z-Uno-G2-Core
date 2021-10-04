/*
  Appending to Strings using the += operator and concat()

  Examples of how to append different data types to Strings
*/

#define MY_SERIAL		Serial

String stringOne, stringTwo;

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(9600);

	stringOne = String("Sensor ");
	stringTwo = String("value");
	// send an intro:
	MY_SERIAL.println("\n\nAppending to a String:");
	MY_SERIAL.println();
}

void loop() {
	MY_SERIAL.println(stringOne);  // prints  "Sensor "

	// adding a string to a String:
	stringOne += stringTwo;
	MY_SERIAL.println(stringOne);  // prints "Sensor value"

	// adding a constant string to a String:
	stringOne += " for input ";
	MY_SERIAL.println(stringOne);  // prints "Sensor value for input"

	// adding a constant character to a String:
	stringOne += 'A';
	MY_SERIAL.println(stringOne);   // prints "Sensor value for input A"

	// adding a constant integer to a String:
	stringOne += 0;
	MY_SERIAL.println(stringOne);   // prints "Sensor value for input A0"

	// adding a constant string to a String:
	stringOne += ": ";
	MY_SERIAL.println(stringOne);  // prints "Sensor value for input"

	// adding a variable integer to a String:
	stringOne += analogRead(A0);
	MY_SERIAL.println(stringOne);   // prints "Sensor value for input A0: 456" or whatever analogRead(A0) is

	MY_SERIAL.println("\n\nchanging the Strings' values");
	stringOne = "A long integer: ";
	stringTwo = "The millis(): ";

	// adding a constant long integer to a String:
	stringOne += 123456789;
	MY_SERIAL.println(stringOne);   // prints "A long integer: 123456789"

	// using concat() to add a long variable to a String:
	stringTwo.concat(millis());
	MY_SERIAL.println(stringTwo); // prints "The millis(): 43534" or whatever the value of the millis() is

	// do nothing while true:
	while (true)
		delay(10);
}
