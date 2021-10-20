// PURPOSE: Show DallasTemperature lib functionality to
//          save/recall ScratchPad values to/from EEPROM

#include "ZUNO_OneWire.h"
#include "DallasTemperature.h"

#define MY_SERIAL		Serial
#define ONE_WIRE_BUS	9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

void setup() {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println(__FILE__);
	MY_SERIAL.println("Dallas Temperature Demo");
	
	sensors.begin();
	
	// Get ID of first sensor (at index 0)
	sensors.getAddress(deviceAddress,0);

	// By default configuration and alarm/userdata registers are also saved to EEPROM
	// when they're changed. Sensors recall these values automatically when powered up.
	
	// Turn OFF automatic saving of configuration and alarm/userdata registers to EEPROM
	sensors.setAutoSaveScratchPad(false);
	
	// Change configuration and alarm/userdata registers on the scratchpad
	int8_t resolution = 12;
	sensors.setResolution(deviceAddress,resolution);
	int16_t userdata = 24680;
	sensors.setUserData(deviceAddress,userdata);

	// Save configuration and alarm/userdata registers to EEPROM
	sensors.saveScratchPad(deviceAddress);

	// saveScratchPad can also be used without a parameter to save the configuration
	// and alarm/userdata registers of ALL connected sensors to EEPROM:
	//
	//   sensors.saveScratchPad();
	//
	// Or the configuration and alarm/userdata registers of a sensor can be saved to
	// EEPROM by index:
	//
	//   sensors.saveScratchPadByIndex(0);
	
	// Print current values on the scratchpad (resolution = 12, userdata = 24680)
	printValues();
}

void loop() {
	// Change configuration and alarm/userdata registers on the scratchpad
	int8_t resolution = 10;
	sensors.setResolution(deviceAddress,resolution);
	int16_t userdata = 12345;
	sensors.setUserData(deviceAddress,userdata);
	
	// Print current values on the scratchpad (resolution = 10, userdata = 12345)
	printValues();
	
	delay(2000);
	
	// Recall configuration and alarm/userdata registers from EEPROM
	sensors.recallScratchPad(deviceAddress);
	
	// recallScratchPad can also be used without a parameter to recall the configuration
	// and alarm/userdata registers of ALL connected sensors from EEPROM:
	//
	//   sensors.recallScratchPad();
	//
	// Or the configuration and alarm/userdata registers of a sensor can be recalled
	// from EEPROM by index:
	//
	//   sensors.recallScratchPadByIndex(0);
	
	// Print current values on the scratchpad (resolution = 12, userdata = 24680)
	printValues();
	
	delay(2000);
}

void printValues() {
	MY_SERIAL.println();
	MY_SERIAL.println("Current values on the scratchpad:");
	
	MY_SERIAL.print("Resolution:\t");
	MY_SERIAL.println(sensors.getResolution(deviceAddress));
	
	MY_SERIAL.print("User data:\t");
	MY_SERIAL.println(sensors.getUserData(deviceAddress));
}
