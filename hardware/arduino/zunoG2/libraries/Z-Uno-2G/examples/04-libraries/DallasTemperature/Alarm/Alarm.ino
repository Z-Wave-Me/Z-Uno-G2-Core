#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;

void setup(void) {
	// start serial port
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Dallas Temperature IC Control Library Demo");

	// Start up the library
	sensors.begin();
	
	// locate devices on the bus
	MY_SERIAL.print("Found ");
	MY_SERIAL.print(sensors.getDeviceCount(), DEC);
	MY_SERIAL.println(" devices.");

	// search for devices on the bus and assign based on an index.
	if (!sensors.getAddress(insideThermometer, 0)) MY_SERIAL.println("Unable to find address for Device 0"); 
	if (!sensors.getAddress(outsideThermometer, 1)) MY_SERIAL.println("Unable to find address for Device 1"); 

	// show the addresses we found on the bus
	MY_SERIAL.print("Device 0 Address: ");
	printAddress(insideThermometer);
	MY_SERIAL.println();

	MY_SERIAL.print("Device 0 Alarms: ");
	printAlarms(insideThermometer);
	MY_SERIAL.println();
	
	MY_SERIAL.print("Device 1 Address: ");
	printAddress(outsideThermometer);
	MY_SERIAL.println();

	MY_SERIAL.print("Device 1 Alarms: ");
	printAlarms(outsideThermometer);
	MY_SERIAL.println();
	
	MY_SERIAL.println("Setting alarm temps...");

	// alarm when temp is higher than 30C
	sensors.setHighAlarmTemp(insideThermometer, 30);
	
	// alarm when temp is lower than -10C
	sensors.setLowAlarmTemp(insideThermometer, -10);
	
	// alarm when temp is higher than 31C
	sensors.setHighAlarmTemp(outsideThermometer, 31);
	
	// alarn when temp is lower than 27C
	sensors.setLowAlarmTemp(outsideThermometer, 27);
	
	MY_SERIAL.print("New Device 0 Alarms: ");
	printAlarms(insideThermometer);
	MY_SERIAL.println();
	
	MY_SERIAL.print("New Device 1 Alarms: ");
	printAlarms(outsideThermometer);
	MY_SERIAL.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++) {
		if (deviceAddress[i] < 16) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress) {
	float tempC = sensors.getTempC(deviceAddress);
	MY_SERIAL.print("Temp C: ");
	MY_SERIAL.print(tempC);
	MY_SERIAL.print(" Temp F: ");
	MY_SERIAL.print(DallasTemperature::toFahrenheit(tempC));
}

void printAlarms(uint8_t deviceAddress[]) {
	char temp;
	temp = sensors.getHighAlarmTemp(deviceAddress);
	MY_SERIAL.print("High Alarm: ");
	MY_SERIAL.print(temp, DEC);
	MY_SERIAL.print("C/");
	MY_SERIAL.print(DallasTemperature::toFahrenheit(temp));
	MY_SERIAL.print("F | Low Alarm: ");
	temp = sensors.getLowAlarmTemp(deviceAddress);
	MY_SERIAL.print(temp, DEC);
	MY_SERIAL.print("C/");
	MY_SERIAL.print(DallasTemperature::toFahrenheit(temp));
	MY_SERIAL.print("F");
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress) {
	MY_SERIAL.print("Device Address: ");
	printAddress(deviceAddress);
	MY_SERIAL.print(" ");
	printTemperature(deviceAddress);
	MY_SERIAL.println();
}

void checkAlarm(DeviceAddress deviceAddress) {
	if (sensors.hasAlarm(deviceAddress)) {
		MY_SERIAL.print("ALARM: ");
		printData(deviceAddress);
	}
}

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature 
	// request to all devices on the bus
	MY_SERIAL.print("Requesting temperatures...");
	sensors.requestTemperatures();
	MY_SERIAL.println("DONE");

	// Method 1:
	// check each address individually for an alarm condition
	checkAlarm(insideThermometer);
	checkAlarm(outsideThermometer);
	/*
	// Alternate method:
	// Search the bus and iterate through addresses of devices with alarms
	
	// space for the alarm device's address
	DeviceAddress alarmAddr;

	MY_SERIAL.println("Searching for alarms...");
	
	// resetAlarmSearch() must be called before calling alarmSearch()
	sensors.resetAlarmSearch();
	
	// alarmSearch() returns 0 when there are no devices with alarms
	while (sensors.alarmSearch(alarmAddr))
	{
		MY_SERIAL.print("ALARM: ");
		printData(alarmAddr);
	}
	*/
}

