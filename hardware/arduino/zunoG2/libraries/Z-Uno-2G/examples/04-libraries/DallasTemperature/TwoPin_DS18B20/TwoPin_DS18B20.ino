// PURPOSE: two pins for two sensors demo
#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial

#define ONE_WIRE_BUS_1	9
#define ONE_WIRE_BUS_2	10

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_inhouse(&oneWire_in);
DallasTemperature sensor_outhouse(&oneWire_out);

void setup(void) {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");

	sensor_inhouse.begin();
	sensor_outhouse.begin();
}

void loop(void) {
	MY_SERIAL.print("Requesting temperatures...");
	sensor_inhouse.requestTemperatures();
	sensor_outhouse.requestTemperatures();
	MY_SERIAL.println(" done");

	MY_SERIAL.print("Inhouse: ");
	MY_SERIAL.println(sensor_inhouse.getTempCByIndex(0));

	MY_SERIAL.print("Outhouse: ");
	MY_SERIAL.println(sensor_outhouse.getTempCByIndex(0));
}