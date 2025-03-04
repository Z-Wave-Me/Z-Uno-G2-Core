/*
  Calibration

  Demonstrates one technique for calibrating sensor input. The sensor readings
  during the first five seconds of the sketch execution define the minimum and
  maximum of expected values attached to the sensor pin.

  The sensor minimum and maximum initial values may seem backwards. Initially,
  you set the minimum high and listen for anything lower, saving it as the new
  minimum. Likewise, you set the maximum low and listen for anything higher as
  the new maximum.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  - LED attached from digital pin 9 to ground

  This example code is in the public domain.

*/

// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {
	// turn on LED to signal the start of the calibration period:
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	// calibrate during the first five seconds
	while (millis() < 5000) {
		sensorValue = analogRead(sensorPin);

		// record the maximum sensor value
		if (sensorValue > sensorMax) {
		sensorMax = sensorValue;
		}

		// record the minimum sensor value
		if (sensorValue < sensorMin) {
		sensorMin = sensorValue;
		}
		delay(1);
	}

	// signal the end of the calibration period
	digitalWrite(LED_BUILTIN, LOW);
	}

void loop() {
	// read the sensor:
	sensorValue = analogRead(sensorPin);

	// apply the calibration to the sensor reading
	sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

	// in case the sensor value is outside the range seen during calibration
	sensorValue = constrain(sensorValue, 0, 255);

	// fade the LED using the calibrated value:
	analogWrite(ledPin, sensorValue);
}
