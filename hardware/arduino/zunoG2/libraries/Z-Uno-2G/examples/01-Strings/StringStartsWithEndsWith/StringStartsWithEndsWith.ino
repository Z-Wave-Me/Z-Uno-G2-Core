/*
  String startWith() and endsWith()

  Examples of how to use startsWith() and endsWith() in a String

*/

#define MY_SERIAL		Serial

void setup() {
	// Open serial communications and wait for port to open:
	MY_SERIAL.begin(115200);

	// send an intro:
	MY_SERIAL.println("\n\nString startsWith() and endsWith():");
	MY_SERIAL.println();
}

void loop() {
	// startsWith() checks to see if a String starts with a particular substring:
	String stringOne = "HTTP/1.1 200 OK";
	MY_SERIAL.println(stringOne);
	if (stringOne.startsWith("HTTP/1.1")) {
		MY_SERIAL.println("Server's using http version 1.1");
	}

	// you can also look for startsWith() at an offset position in the string:
	stringOne = "HTTP/1.1 200 OK";
	if (stringOne.startsWith("200 OK", 9)) {
		MY_SERIAL.println("Got an OK from the server");
	}

	// endsWith() checks to see if a String ends with a particular character:
	String sensorReading = "sensor = ";
	sensorReading += analogRead(A0);
	MY_SERIAL.print(sensorReading);
	if (sensorReading.endsWith("0")) {
		MY_SERIAL.println(". This reading is divisible by ten");
	} else {
		MY_SERIAL.println(". This reading is not divisible by ten");
	}

	// do nothing while true:
	while (true)
		delay(10);
}
