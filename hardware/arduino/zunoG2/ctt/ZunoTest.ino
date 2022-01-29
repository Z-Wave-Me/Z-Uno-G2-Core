/* 
* This scretch was certified by the Z-Wave Alliance.
* 
* 3 switches
* 3 dimmers
* 1 motion sensor
* 1 door sensor
* 1 temperature sensor
* 1 humidity sensor
* 
*/
#include "ZUNO_DHT.h"// Additional include for DHT sensor support
#include "ZWCCUserCode.h"
#include "ZWCCEntryControl.h"
#include "ZWCCTimerParametrs.h"

// Pins definitions 
#define LedPin1         A0
#define LedPin2         A1
#define LedPin3         A2
#define LedPin4         PWM1
#define LedPin5         PWM2 
#define LedPin6         PWM3
#define MotionPin       A3
#define DoorPin         12
#define DHTPin          11
// Switch levels
#define SWITCH_ON       0xff
#define SWITCH_OFF      0
#define MY_SERIAL       Serial0
// Global variables for device channels
// switches
byte switchValue1 = 0;
byte switchValue2 = 0;
byte switchValue3 = 0;
// dimmers
byte dimValue1 = 0;
byte dimValue2 = 0;
byte dimValue3 = 0;
// binary sensors
byte lastMotionValue = 0;
byte lastDoorValue = 0;
// temperature & humidity sensor
uint16_t lastHumidityValue = 0;
int16_t lastTemperatureValue = 0;
// Last motion sensor trigger time 
uint32_t motionTrigTime;
// enum for some sensors channels, this makes code readable
enum{ 
   SENSOR_MOTION_CHANNEL = 7,
   SENSOR_DOOR_CHANNEL,
   SENSOR_TEMPERATURE_CHANNEL,
   SENSOR_HUMIDITY_CHANNEL,
};
// enum for parameter numbers
enum{
   TEMP_HYST_PARAM=64,
   HUMIDITY_HYST_PARAM,
   MOTION_RETRIGGER_TIME_PARAM 
};
// ZUNO_ENABLE setups some global extra build flags
ZUNO_ENABLE(
            WITH_CC_USER_CODE WITH_CC_ENTRY_CONTROL WITH_CC_TIME_PARAMETERS
            LOGGING_DBG    // Uncomment for console output on TX0
            MODERN_MULTICHANNEL  // No clusterring the first channel is mapped to NIF only
            SUPERVISION_HIGHEST_S2_ONLY // Supervision works on higher S2 level ONLY 
            MODERN_MULTICHANNEL_S2  // S2 encapsulated NIF in multichannel
            MODERN_MULTICHANNEL_S2_ALWAYS // Add S2 to multichannel if device encluded non-secure
            SKETCH_FLAGS=HEADER_FLAGS_NOREBOOT_CFG); // Do not reboot device if we apply some system configuration parameters which normally do it
// Device's endpoints definition
// 3 switch binary
// 3 switch multilevel
// 2 notification sensors
// 2 multilevel sensors 
ZUNO_SETUP_CHANNELS(
   ZUNO_SWITCH_BINARY(switchValue1, NULL),
   ZUNO_SWITCH_BINARY(switchValue2, NULL),
   ZUNO_SWITCH_BINARY(switchValue3, NULL),
   ZUNO_SWITCH_MULTILEVEL(dimValue1, NULL),
   ZUNO_SWITCH_MULTILEVEL(dimValue2, NULL),
   ZUNO_SWITCH_MULTILEVEL(dimValue3, NULL),
   ZUNO_SENSOR_BINARY_MOTION(lastMotionValue),
   ZUNO_SENSOR_BINARY_DOOR_WINDOW(lastDoorValue),
   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, SENSOR_MULTILEVEL_SCALE_CELSIUS, 2, 1, lastTemperatureValue),
   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY, SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE, 2, 1,lastHumidityValue)
);

ZUNO_SETUP_USER_CODE_KEYS('a');

ZUNO_SETUP_USER_CODE(
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE()
);

ZUNO_SETUP_ENTRY_CONTROL_KEYS('0','1', '2', '3', '4', '5', '6', '7', '8', '9');

// Device's configuration parametrs definitions  
ZUNO_SETUP_CONFIGPARAMETERS(
   ZUNO_CONFIG_PARAMETER_INFO("Temperature hysteresis", "Defines hysteresis of temperature", 1, 20, 5),
   ZUNO_CONFIG_PARAMETER_INFO("Humidity hysteresis", "Defines hysteresis of humidity", 1, 20, 5),
   ZUNO_CONFIG_PARAMETER_INFO("Motion trigger time", "Minimal trigger interval in ms", 0, 100000, 5000)
);
// Associations of device
ZUNO_SETUP_ASSOCIATIONS(ZUNO_ASSOCIATION_GROUP_SET_VALUE); // Send Basic Set to association group
// Device's S2 keys
ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);
// Objects for external periphery
DHT dht22_sensor(DHTPin, DHT22); // DHT sensor
// OS calls setup() function on every device boot
void setup() {
	if(zunoStartDeviceConfiguration()) {
		zunoAddChannel(1,0,0);
		zunoSetZWChannel( 0, 0x01 | ZWAVE_CHANNEL_MAPPED_BIT);
		zunoAddChannel(1,0,0);
		zunoSetZWChannel( 1, 0x02);
		zunoAddChannel(1,0,0);
		zunoSetZWChannel( 2, 0x03);
		zunoAddChannel(2,0,0);
		zunoSetZWChannel( 3, 0x04);
		zunoAddChannel(2,0,0);
		zunoSetZWChannel( 4, 0x05);
		zunoAddChannel(2,0,0);
		zunoSetZWChannel( 5, 0x06);
		zunoAddChannel(3,12,0);
		zunoSetZWChannel( 6, 0x07);
		zunoAddChannel(3,10,0);
		zunoSetZWChannel( 7, 0x08);
		zunoAddChannel(4,1,34);
		zunoSetZWChannel( 8, 0x09);
		zunoAddChannel(4,5,34);
		zunoSetZWChannel( 9, 0x0a);
		zunoAddAssociation(1, 0);
		zunoSetS2Keys(0x83);
		zunoAddBaseCCS(COMMAND_CLASS_USER_CODE, USER_CODE_VERSION);
		zunoAddBaseCCS(COMMAND_CLASS_ENTRY_CONTROL, ENTRY_CONTROL_VERSION);
		zunoAddBaseCCS(COMMAND_CLASS_TIME_PARAMETERS, TIME_PARAMETERS_VERSION);
		zunoCommitCfg();
	}
	zunoAppendChannelHandler( 0,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&switchValue1);
	zunoAppendChannelHandler( 1,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&switchValue2);
	zunoAppendChannelHandler( 2,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&switchValue3);
	zunoAppendChannelHandler( 3,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&dimValue1);
	zunoAppendChannelHandler( 4,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&dimValue2);
	zunoAppendChannelHandler( 5,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&dimValue3);
	zunoAppendChannelHandler( 6,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&lastMotionValue);
	zunoAppendChannelHandler( 7,  1, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&lastDoorValue);
	zunoAppendChannelHandler( 8,  2, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&lastTemperatureValue);
	zunoAppendChannelHandler( 9,  2, CHANNEL_HANDLER_SINGLE_VALUEMAPPER, (void*)&lastHumidityValue);
   // Configure I/O pins. Analog and PWM will be automatically set up on analogRead/analogWrite functions call
   pinMode(LedPin1, OUTPUT);
   pinMode(LedPin2, OUTPUT);
   pinMode(LedPin3, OUTPUT);
   pinMode(LedPin4, OUTPUT);
   pinMode(LedPin5, OUTPUT);
   pinMode(LedPin6, OUTPUT);
   pinMode(MotionPin, INPUT_PULLUP);
   pinMode(DoorPin, INPUT_PULLUP);
   // Start dht sensor
   dht22_sensor.begin();
   dht22_sensor.readTemperatureC10(true);
}
// OS calls loop() function repeatedly
void loop() {
   // Switches
   digitalWrite(LedPin1, switchValue1 == 0);
   digitalWrite(LedPin2, switchValue2 == 0);
   digitalWrite(LedPin3, switchValue3 == 0);
   // Dimmers
   analogWrite(LedPin4, ((word)dimValue1)*255/99);
   analogWrite(LedPin5, ((word)dimValue2)*255/99);
   analogWrite(LedPin6, ((word)dimValue3)*255/99);
   // Trigger motion and wait for relax (about 5 sec) before report idle
   byte currentMotionValue = digitalRead(MotionPin);
   if (currentMotionValue) {
       if (!lastMotionValue && ((millis() - motionTrigTime) > (size_t)zunoLoadCFGParam(MOTION_RETRIGGER_TIME_PARAM))) {
           lastMotionValue = 1;
           zunoSendReport(SENSOR_MOTION_CHANNEL);
           zunoSendToGroupSetValueCommand(CTRL_GROUP_1, SWITCH_ON);
           motionTrigTime = millis();
       }
   } else if (lastMotionValue) {
       lastMotionValue = 0; 
       zunoSendReport(SENSOR_MOTION_CHANNEL);
       zunoSendToGroupSetValueCommand(CTRL_GROUP_1, SWITCH_OFF);
   }
   // Door/Window sensor
   byte currentDoorValue = digitalRead(DoorPin); 
   if (currentDoorValue != lastDoorValue) { 
       lastDoorValue = currentDoorValue;
       zunoSendReport(SENSOR_DOOR_CHANNEL);
   }
   // Temperature sensor (based on DHT22 digital sensor)
   
   int16_t currentTemperatureValue = dht22_sensor.readTemperatureC10();
   if(abs(lastTemperatureValue - currentTemperatureValue) > zunoLoadCFGParam(TEMP_HYST_PARAM)){
       lastTemperatureValue = currentTemperatureValue;
       zunoSendReport(SENSOR_TEMPERATURE_CHANNEL);
   }
   // Humidity sensor (based on DHT22 digital sensor)
   uint16_t currentHumidityValue = dht22_sensor.readHumidityH10();
   if(abs(lastHumidityValue - currentHumidityValue) > zunoLoadCFGParam(HUMIDITY_HYST_PARAM)){
       lastHumidityValue = currentHumidityValue;
       zunoSendReport(SENSOR_HUMIDITY_CHANNEL);
   }
   delay(50);
}