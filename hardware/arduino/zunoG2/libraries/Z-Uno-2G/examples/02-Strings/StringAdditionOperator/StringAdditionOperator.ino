/*
  Adding Strings together

  Examples of how to add Strings together
  You can also add several different data types to String, as shown here:
*/

#define MY_SERIAL		Serial

// declare three Strings:
String stringOne, stringTwo, stringThree;

void setup() {
	// initialize serial and wait for port to open:
	MY_SERIAL.begin(115200);

	stringOne = String("You added ");
	stringTwo = String("this string");
	stringThree = String();
	// send an intro:
	MY_SERIAL.println("\n\nAdding Strings together (concatenation):");
	MY_SERIAL.println();
}

void loop() {
	// adding a constant integer to a String:
	stringThree =  stringOne + 123;
	MY_SERIAL.println(stringThree);    // prints "You added 123"

	// adding a constant long integer to a String:
	stringThree = stringOne + 123456789;
	MY_SERIAL.println(stringThree);    // prints "You added 123456789"

	// adding a constant character to a String:
	stringThree =  stringOne + 'A';
	MY_SERIAL.println(stringThree);    // prints "You added A"

	// adding a constant string to a String:
	stringThree =  stringOne +  "abc";
	MY_SERIAL.println(stringThree);    // prints "You added abc"

	stringThree = stringOne + stringTwo;
	MY_SERIAL.println(stringThree);    // prints "You added this string"

	// adding a variable integer to a String:
	int sensorValue = analogRead(A0);
	stringOne = "Sensor value: ";
	stringThree = stringOne  + sensorValue;
	MY_SERIAL.println(stringThree);    // prints "Sensor Value: 247" or whatever value analogRead(A0) has

	// adding a variable long integer to a String:
	stringOne = "millis() value: ";
	stringThree = stringOne + millis();
	MY_SERIAL.println(stringThree);    // prints "The millis: 1271" or whatever value millis() has

	// do nothing while true:
	while (true)
		delay(10);
}
