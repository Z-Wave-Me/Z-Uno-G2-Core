#include "Arduino.h"
#include "ZUNO_DHT.h"
#include "ZUNO_BMP280.h"


uint16_t lastHumidityValueDht22 = 0;
int16_t lastTemperatureValueDht22 = 0;

uint16_t lastTemperatureValueBmp280 = 0;
uint16_t lastKiloPascalValueBmp280 = 0;

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_SLEEPING);


#define CHANNEL_DHT22_TEMPERATURE			0x1
#define CHANNEL_DHT22_HUMIDITY				0x2
#define CHANNEL_BMP280_TEMPERATURE			0x3
#define CHANNEL_BMP280_KILOPASCAL			0x4

ZUNO_SETUP_CHANNELS(
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, SENSOR_MULTILEVEL_SCALE_CELSIUS, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL, lastTemperatureValueDht22),
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY, SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL, lastHumidityValueDht22),
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, SENSOR_MULTILEVEL_SCALE_CELSIUS, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_TWO_DECIMALS, lastTemperatureValueBmp280),
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_BAROMETRIC_PRESSURE, SENSOR_MULTILEVEL_SCALE_KILOPASCAL, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_TWO_DECIMALS, lastKiloPascalValueBmp280)
); 

ZUNO_BMP280 bmp;
DHT dht22_sensor(6, DHT21);

/* the setup function runs once, when you press reset or power the board */
void setup() {
	dht22_sensor.begin();
	if (!bmp.begin(0x76)) {
		while (1) delay(10);
	}
	/* Default settings from datasheet. */
	bmp.setSampling(ZUNO_BMP280::MODE_NORMAL,     /* Operating Mode. */
					ZUNO_BMP280::SAMPLING_X2,     /* Temp. oversampling */
					ZUNO_BMP280::SAMPLING_X16,    /* Pressure oversampling */
					ZUNO_BMP280::SAMPLING_X16,
					ZUNO_BMP280::FILTER_X16,      /* Filtering. */
					ZUNO_BMP280::STANDBY_MS_1000); /* Standby time. */
}

/* the loop function runs over and over again forever */
void loop() {
	byte		result;

	if (zunoIsSleepLocked())
	{
		result = dht22_sensor.read(true);
		if (result == ZunoErrorOk) {
			// Temperature sensor (based on DHT22 digital sensor)
			lastTemperatureValueDht22 = dht22_sensor.readTemperatureC10();
			zunoSendReport(CHANNEL_DHT22_TEMPERATURE);

			// Humidity sensor (based on DHT22 digital sensor)
			lastHumidityValueDht22 = dht22_sensor.readHumidityH10();
			zunoSendReport(CHANNEL_DHT22_HUMIDITY);

		}

		// Temperature bmp280
		lastTemperatureValueBmp280 = bmp.readTemperatureC100();
		zunoSendReport(CHANNEL_BMP280_TEMPERATURE);

		// Pascal bmp280
		lastKiloPascalValueBmp280 = bmp.readPressurePa() / 10;
		zunoSendReport(CHANNEL_BMP280_KILOPASCAL);

		zunoSetCustomWUPTimer(180);
		zunoSendDeviceToSleep();
	}
	delay(1000);
}