#include "Arduino.h"
#include "ZUNO_DHT.h"

#define MY_SERIAL Serial0

DHT dht22_sensor(9, DHT22);

/* the setup function runs once, when you press reset or power the board */
void setup() {
	MY_SERIAL.begin(115200);
	dht22_sensor.begin();
	MY_SERIAL.println("\n **** Sketch is starting... ****\n");
}

void loop() {
	byte		result;
	byte		i;
	byte		raw_data[5]; 

	MY_SERIAL.print("Millis:");
	MY_SERIAL.println(millis());
	result = dht22_sensor.read(true); 
	MY_SERIAL.print("DHT read result:");
	MY_SERIAL.println(result);
	MY_SERIAL.print("Raw data: { ");
	dht22_sensor.getRawData(raw_data);
	for(i=0;i<5;i++) {
		MY_SERIAL.print(raw_data[i], HEX);
		MY_SERIAL.print(" ");
	}
	MY_SERIAL.println("} ");
	MY_SERIAL.print("Temperature:");
	MY_SERIAL.println(dht22_sensor.readTemperature());
	MY_SERIAL.print("Humidity:");
	MY_SERIAL.println(dht22_sensor.readHumidity()); 
	delay(3000);
}
