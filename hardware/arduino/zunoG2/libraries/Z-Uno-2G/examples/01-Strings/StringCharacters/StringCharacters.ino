/*
  String charAt() and setCharAt()

  Examples of how to get and set characters of a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(9600);

	MY_SERIAL.println("\n\nString charAt() and setCharAt():");
}

void loop() {
	// make a String to report a sensor reading:
	String reportString = "SensorReading: 456";
	MY_SERIAL.println(reportString);

	// the reading's most significant digit is at position 15 in the reportString:
	char mostSignificantDigit = reportString.charAt(15);

	String message = "Most significant digit of the sensor reading is: ";
	MY_SERIAL.println(message + mostSignificantDigit);

	// add blank space:
	MY_SERIAL.println();

	// you can also set the character of a String. Change the : to a = character
	reportString.setCharAt(13, '=');
	MY_SERIAL.println(reportString);

	// do nothing while true:
	while (true)
		delay(10);
}
