// PURPOSE: show performance of DallasTemperature lib 
//          compared to datasheet times per resolution
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

uint32_t start, stop;


void setup() {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println(__FILE__);
	MY_SERIAL.print("DallasTemperature Library version: ");
	MY_SERIAL.println(DALLASTEMPLIBVERSION);

	sensor.begin();
}

void loop() {
	float ti[4] = { 94, 188, 375, 750 };

	MY_SERIAL.println();
	MY_SERIAL.println("Test takes about 30 seconds for 4 resolutions");
	MY_SERIAL.println("RES\tTIME\tACTUAL\tGAIN");
	for (int r = 9; r < 13; r++) {
		start = micros();
		sensor.setResolution(r);
		MY_SERIAL.println(micros() - start);

		start = micros();
		sensor.setResolution(r);
		MY_SERIAL.println(micros() - start);

		uint32_t duration = run(20);
		float avgDuration = duration / 20.0;

		MY_SERIAL.print(r);
		MY_SERIAL.print("\t");
		MY_SERIAL.print(ti[r - 9]);
		MY_SERIAL.print("\t");
		MY_SERIAL.print(avgDuration, 2);
		MY_SERIAL.print("\t");
		MY_SERIAL.print(avgDuration * 100 / ti[r - 9], 1);
		MY_SERIAL.println("%");
	}
	delay(1000);
}

uint32_t run(int runs) {
	float t;
	start = millis();
	for (int i = 0; i < runs; i++)
	{
		sensor.requestTemperatures();
		t = sensor.getTempCByIndex(0);
	}
	stop = millis();
	return stop - start;
	(void)t;
}
