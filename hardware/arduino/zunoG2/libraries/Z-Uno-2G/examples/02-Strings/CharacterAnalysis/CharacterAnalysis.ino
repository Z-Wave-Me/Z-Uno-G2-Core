/*
  Character analysis operators

  Examples using the character analysis operators.
  Send any byte and the sketch will tell you about it.
*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("send any byte and I'll tell you everything I can about it\n");
}

void loop() {
	// get any incoming bytes:
	if (MY_SERIAL.available() > 0) {
		int thisChar = MY_SERIAL.read();

		// say what was sent:
		MY_SERIAL.print("You sent me: \'");
		MY_SERIAL.write(thisChar);
		MY_SERIAL.print("\'  ASCII Value: ");
		MY_SERIAL.println(thisChar);

		// analyze what was sent:
		if (isAlphaNumeric(thisChar))
			MY_SERIAL.println("it's alphanumeric");

		if (isAlpha(thisChar))
			MY_SERIAL.println("it's alphabetic");

		if (isAscii(thisChar))
			MY_SERIAL.println("it's ASCII");

		if (isWhitespace(thisChar))
			MY_SERIAL.println("it's whitespace");

		if (isControl(thisChar))
		MY_SERIAL.println("it's a control character");

		if (isDigit(thisChar))
			MY_SERIAL.println("it's a numeric digit");

		if (isGraph(thisChar))
			MY_SERIAL.println("it's a printable character that's not whitespace");

		if (isLowerCase(thisChar))
			MY_SERIAL.println("it's lower case");

		if (isPrintable(thisChar))
			MY_SERIAL.println("it's printable");

		if (isPunct(thisChar))
			MY_SERIAL.println("it's punctuation");

		if (isSpace(thisChar))
			MY_SERIAL.println("it's a space character");

		if (isUpperCase(thisChar))
			MY_SERIAL.println("it's upper case");

		if (isHexadecimalDigit(thisChar))
			MY_SERIAL.println("it's a valid hexadecimaldigit (i.e. 0 - 9, a - F, or A - F)");

		// add some space and ask for another byte:
		MY_SERIAL.println();
		MY_SERIAL.println("Give me another byte:");
		MY_SERIAL.println();
	}
}


/* TEST */
/*
void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("send any byte and I'll tell you everything I can about it\n");
}

void loop() {
	int						thisChar;

	delay(10000);
	thisChar = 0x0;
	while (thisChar <= 0x80) {
		// say what was sent:
		MY_SERIAL.print("You sent me: \'");
		MY_SERIAL.write(thisChar);
		MY_SERIAL.print("\'  ASCII Value: ");
		MY_SERIAL.println(thisChar);

		// analyze what was sent:
		if (isAlphaNumeric(thisChar))
			MY_SERIAL.println("it's alphanumeric");

		if (isAlpha(thisChar))
			MY_SERIAL.println("it's alphabetic");

		if (isAscii(thisChar))
			MY_SERIAL.println("it's ASCII");

		if (isWhitespace(thisChar))
			MY_SERIAL.println("it's whitespace");

		if (isControl(thisChar))
		MY_SERIAL.println("it's a control character");

		if (isDigit(thisChar))
			MY_SERIAL.println("it's a numeric digit");

		if (isGraph(thisChar))
			MY_SERIAL.println("it's a printable character that's not whitespace");

		if (isLowerCase(thisChar))
			MY_SERIAL.println("it's lower case");

		if (isPrintable(thisChar))
			MY_SERIAL.println("it's printable");

		if (isPunct(thisChar))
			MY_SERIAL.println("it's punctuation");

		if (isSpace(thisChar))
			MY_SERIAL.println("it's a space character");

		if (isUpperCase(thisChar))
			MY_SERIAL.println("it's upper case");

		if (isHexadecimalDigit(thisChar))
			MY_SERIAL.println("it's a valid hexadecimaldigit (i.e. 0 - 9, a - F, or A - F)");

		// add some space and ask for another byte:
		MY_SERIAL.println();
		MY_SERIAL.println("Give me another byte:");
		MY_SERIAL.println();
		thisChar++;
	}
}
*/