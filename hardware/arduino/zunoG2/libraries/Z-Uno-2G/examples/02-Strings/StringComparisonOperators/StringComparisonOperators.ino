/*
  Comparing Strings

  Examples of how to compare Strings using the comparison operators

*/

#define MY_SERIAL		Serial

String stringOne, stringTwo;

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);


	stringOne = String("this");
	stringTwo = String("that");
	// send an intro:
	MY_SERIAL.println("\n\nComparing Strings:");
	MY_SERIAL.println();
}

void loop() {
	// two Strings equal:
	if (stringOne == "this")
		MY_SERIAL.println("StringOne == \"this\"");

	// two Strings not equal:
	if (stringOne != stringTwo)
		MY_SERIAL.println(stringOne + " =! " + stringTwo);

	// two Strings not equal (case sensitivity matters):
	stringOne = "This";
	stringTwo = "this";
	if (stringOne != stringTwo)
		MY_SERIAL.println(stringOne + " =! " + stringTwo);

	// you can also use equals() to see if two Strings are the same:
	if (stringOne.equals(stringTwo))
		MY_SERIAL.println(stringOne + " equals " + stringTwo);
	else
		MY_SERIAL.println(stringOne + " does not equal " + stringTwo);

	// or perhaps you want to ignore case:
	if (stringOne.equalsIgnoreCase(stringTwo))
		MY_SERIAL.println(stringOne + " equals (ignoring case) " + stringTwo);
	else
		MY_SERIAL.println(stringOne + " does not equal (ignoring case) " + stringTwo);

	// a numeric String compared to the number it represents:
	stringOne = "1";
	int numberOne = 1;
	if (stringOne.toInt() == numberOne)
		MY_SERIAL.println(stringOne + " = " + numberOne);

	// two numeric Strings compared:
	stringOne = "2";
	stringTwo = "1";
	if (stringOne >= stringTwo)
		MY_SERIAL.println(stringOne + " >= " + stringTwo);

	// comparison operators can be used to compare Strings for alphabetic sorting too:
	stringOne = String("Brown");
	if (stringOne < "Charles") 
		MY_SERIAL.println(stringOne + " < Charles");

	if (stringOne > "Adams")
		MY_SERIAL.println(stringOne + " > Adams");

	if (stringOne <= "Browne")
		MY_SERIAL.println(stringOne + " <= Browne");


	if (stringOne >= "Brow")
		MY_SERIAL.println(stringOne + " >= Brow");

	// the compareTo() operator also allows you to compare Strings
	// it evaluates on the first character that's different.
	// if the first character of the String you're comparing to comes first in
	// alphanumeric order, then compareTo() is greater than 0:
	stringOne = "Cucumber";
	stringTwo = "Cucuracha";
	if (stringOne.compareTo(stringTwo) < 0)
		MY_SERIAL.println(stringOne + " comes before " + stringTwo);
	else
		MY_SERIAL.println(stringOne + " comes after " + stringTwo);

	delay(10000);  // because the next part is a loop:

	// compareTo() is handy when you've got Strings with numbers in them too:

	while (true) {
		stringOne = "Sensor: ";
		stringTwo = "Sensor: ";

		stringOne += analogRead(A0);
		stringTwo += analogRead(A3);

		if (stringOne.compareTo(stringTwo) < 0)
			MY_SERIAL.println(stringOne + " comes before " + stringTwo);
		else 
			MY_SERIAL.println(stringOne + " comes after " + stringTwo);
	}
}
