#include "ZUNO_BMP280.h"

#define MY_SERIAL		Serial

ZUNO_BMP280 bmp;

void setup() {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println(F("BMP280/BME280 test"));

	if (!bmp.begin()) {
		MY_SERIAL.println("Could not find a valid BMP280 sensor, check wiring or "
						"try a different address!");
		while (1) delay(10);
	}
	/* Default settings from datasheet. */
	bmp.setSampling(ZUNO_BMP280::MODE_NORMAL,     /* Operating Mode. */
					ZUNO_BMP280::SAMPLING_X2,     /* Temp. oversampling */
					ZUNO_BMP280::SAMPLING_X16,    /* Pressure oversampling */
					ZUNO_BMP280::SAMPLING_X16,
					ZUNO_BMP280::FILTER_X16,      /* Filtering. */
					ZUNO_BMP280::STANDBY_MS_0_5); /* Standby time. */
}

void loop() {
	MY_SERIAL.print("Temperature = ");
	MY_SERIAL.print(bmp.readTemperature());
	MY_SERIAL.println(" *C");

	MY_SERIAL.print("Pressure = ");
	MY_SERIAL.print(bmp.readPressure());
	MY_SERIAL.println(" Pa");

	MY_SERIAL.print("Humidity = ");
	MY_SERIAL.print(bmp.readHumidity());
	MY_SERIAL.println(" %");

	MY_SERIAL.print("Approx altitude = ");
	MY_SERIAL.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
	MY_SERIAL.println(" m");

	MY_SERIAL.println();
	delay(1000);
}