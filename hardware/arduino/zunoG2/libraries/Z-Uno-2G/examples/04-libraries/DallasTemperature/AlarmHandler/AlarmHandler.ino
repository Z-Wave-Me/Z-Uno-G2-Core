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

// function that will be called when an alarm condition exists during DallasTemperatures::processAlarms();
void newAlarmHandler(const uint8_t* deviceAddress) {
	MY_SERIAL.println("Alarm Handler Start"); 
	printAlarmInfo(deviceAddress);
	printTemp(deviceAddress);
	MY_SERIAL.println();
	MY_SERIAL.println("Alarm Handler Finish");
}

void printCurrentTemp(DeviceAddress deviceAddress) {
	printAddress(deviceAddress);
	printTemp(deviceAddress);
	MY_SERIAL.println();
}

void printAddress(const DeviceAddress deviceAddress) {
	MY_SERIAL.print("Address: ");
	for (uint8_t i = 0; i < 8; i++) {
		if (deviceAddress[i] < 16) MY_SERIAL.print("0");
		MY_SERIAL.print(deviceAddress[i], HEX);
	}
	MY_SERIAL.print(" ");
}

void printTemp(const DeviceAddress deviceAddress) {
	float tempC = sensors.getTempC(deviceAddress);
	if (tempC != DEVICE_DISCONNECTED_C)
	{
		MY_SERIAL.print("Current Temp C: ");
		MY_SERIAL.print(tempC);
	}
	else MY_SERIAL.print("DEVICE DISCONNECTED");
	MY_SERIAL.print(" ");
}

void printAlarmInfo(const DeviceAddress deviceAddress) {
	char temp;
	printAddress(deviceAddress);
	temp = sensors.getHighAlarmTemp(deviceAddress);
	MY_SERIAL.print("High Alarm: ");
	MY_SERIAL.print(temp, DEC);
	MY_SERIAL.print("C");
	MY_SERIAL.print(" Low Alarm: ");
	temp = sensors.getLowAlarmTemp(deviceAddress);
	MY_SERIAL.print(temp, DEC);
	MY_SERIAL.print("C");
	MY_SERIAL.print(" ");
}

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

	// search for devices on the bus and assign based on an index
	if (!sensors.getAddress(insideThermometer, 0)) MY_SERIAL.println("Unable to find address for Device 0"); 
	if (!sensors.getAddress(outsideThermometer, 1)) MY_SERIAL.println("Unable to find address for Device 1"); 

	MY_SERIAL.print("Device insideThermometer ");
	printAlarmInfo(insideThermometer);
	MY_SERIAL.println();
	
	MY_SERIAL.print("Device outsideThermometer ");
	printAlarmInfo(outsideThermometer);
	MY_SERIAL.println();
	
	// set alarm ranges
	MY_SERIAL.println("Setting alarm temps...");
	sensors.setHighAlarmTemp(insideThermometer, 26);
	sensors.setLowAlarmTemp(insideThermometer, 22);
	sensors.setHighAlarmTemp(outsideThermometer, 25);
	sensors.setLowAlarmTemp(outsideThermometer, 21);
	
	MY_SERIAL.print("New insideThermometer ");
	printAlarmInfo(insideThermometer);
	MY_SERIAL.println();
	
	MY_SERIAL.print("New outsideThermometer ");
	printAlarmInfo(outsideThermometer);
	MY_SERIAL.println();

	// attach alarm handler
	sensors.setAlarmHandler(&newAlarmHandler);
}

void loop(void) {
	// ask the devices to measure the temperature
	sensors.requestTemperatures();
	
	// if an alarm condition exists as a result of the most recent 
	// requestTemperatures() request, it exists until the next time 
	// requestTemperatures() is called AND there isn't an alarm condition
	// on the device
	if (sensors.hasAlarm())
		MY_SERIAL.println("Oh noes!  There is at least one alarm on the bus.");

	// call alarm handler function defined by sensors.setAlarmHandler
	// for each device reporting an alarm
	sensors.processAlarms();

	if (!sensors.hasAlarm()) {
		// just print out the current temperature
		printCurrentTemp(insideThermometer);
		printCurrentTemp(outsideThermometer);
	}
	delay(1000);
}
