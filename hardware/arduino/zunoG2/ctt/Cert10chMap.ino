/* 
 * This scretch was certified by the Z-Wave Alliance as one of the two reference Z-Uno sketches.
 * 
 * 3 switches
 * 3 dimmers
 * 1 motion sensor
 * 1 door sensor
 * 1 temperature sensor
 * 1 humidity sensor
 * 
 */

#include "Arduino.h"
#include "ZUNO_DHT.h"// Additional include for DHT sensor support

ZUNO_ENABLE(LOGGING_DBG LOGGING_UART=Serial0 ZUNO_PIN_V=4);//LOGGING_DBG LOGGING_UART=Serial0 SKETCH_FLAGS=HEADER_FLAGS_DBG
#define MY_SERIAL Serial0

// Pins definitions 
#define LedPin1         9
#define LedPin2         10
#define LedPin3         11
#define LedPin4         PWM2
#define LedPin5         PWM3 
#define LedPin6         PWM4
#define MotionPin       12
#define DoorPin         19
#define DHTPin          8
#define SWITCH_ON       0xff
#define SWITCH_OFF      0

#define TEMP_HYST 5 //0.5 *C
#define HUMIDITY_HYST 5 // 0.5%
#define MOTION_RETRIGGER_TIME 5000 // 5 seconds

// Global variables to store data reported via getters
byte switchValue1 = 0;
byte switchValue2 = 0;
byte switchValue3 = 0;
byte dimValue1 = 0;
byte dimValue2 = 0;
byte dimValue3 = 0;
byte lastMotionValue = 0;
uint16_t lastHumidityValue = 0;
int16_t lastTemperatureValue = 0;
byte lastDoorValue = 0;
uint32_t motionTrigTime;

enum{ 
	SENSOR_MOTION_CHANNEL = 7,
	SENSOR_DOOR_CHANNEL,
	SENSOR_TEMPERATURE_CHANNEL,
	SENSOR_HUMIDITY_CHANNEL,
};

DHT dht22_sensor(DHTPin, DHT22);
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE); 
ZUNO_SETUP_ASSOCIATIONS(ZUNO_ASSOCIATION_GROUP_SET_VALUE); // Send Basic Set to association group
ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);
ZUNO_DISABLE(ZW_CHANNEL_CLUSTERISATION); 
// Setup 10 channels
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

const ZunoCFGParameter_t param64 =
{
	.name = "Temperature hysteresis",
	.info = "Defines hysteresis of temperature reports in 10th of *C",
	.minValue = 0x1,
	.maxValue = 0x14,
	.defaultValue = 0x5,
	.format = ZunoCFGParameterFormatUnsigned,
	.size = ZunoCFGParameterSize32bit
};

const ZunoCFGParameter_t param65 =
{
	.name = "Humidity hysteresis",
	.info = "Defines hysteresis of temperature reports in 10th of %",
	.minValue = 0x1,
	.maxValue = 0x14,
	.defaultValue = 0x5,
	.format = ZunoCFGParameterFormatUnsigned,
	.size = ZunoCFGParameterSize32bit
};

const ZunoCFGParameter_t param66 =
{
	.name = "Motion trigger time",
	.info = "Minimal time interval of the next motion sensor trigger",
	.minValue = 0x0,
	.maxValue = 0x5000,
	.defaultValue = 0x1000,
	.format = ZunoCFGParameterFormatUnsigned,
	.size = ZunoCFGParameterSize32bit
};

const ZunoCFGParameter_t *zunoCFGParameter(size_t param) {
	const ZunoCFGParameter_t			*cfg;

	switch (param) {
		case 64:
			cfg = &param64;
			break;
		case 65:
			cfg = &param65;
			break;
		case 66:
			cfg = &param66;
			break;
		default:
			cfg = ZUNO_CFG_PARAMETER_UNKNOWN;
			break;
	}
	return (cfg);
}

void setup() { 
	MY_SERIAL.begin(115200);
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

void loop() {
	// Switches
	digitalWrite(LedPin1, switchValue1 > 0);
	digitalWrite(LedPin2, switchValue2 > 0);
	digitalWrite(LedPin3, switchValue3 > 0);
	// Dimmers
	analogWrite(LedPin4, ((word)dimValue1)*255/99);
	analogWrite(LedPin5, ((word)dimValue2)*255/99);
	analogWrite(LedPin6, ((word)dimValue3)*255/99);
	// Trigger motion and wait for relax (about 5 sec) before report idle
	byte currentMotionValue = !digitalRead(MotionPin);
	if (currentMotionValue) {
		if ((millis() - motionTrigTime) < MOTION_RETRIGGER_TIME) {
		lastMotionValue = 1;
		zunoSendReport(SENSOR_MOTION_CHANNEL);
		zunoSendToGroupSetValueCommand(CTRL_GROUP_1, SWITCH_ON);
		}
		motionTrigTime = millis();
	}
	if (lastMotionValue && 
		((millis() - motionTrigTime) > MOTION_RETRIGGER_TIME)) {
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
	if(abs(lastTemperatureValue - currentTemperatureValue) > TEMP_HYST){
		lastTemperatureValue = currentTemperatureValue;
		zunoSendReport(SENSOR_TEMPERATURE_CHANNEL);
	}
	// Humidity sensor (based on DHT22 digital sensor)
	uint16_t currentHumidityValue = dht22_sensor.readHumidityH10();
	if(abs(lastHumidityValue - currentHumidityValue) > HUMIDITY_HYST){
		lastHumidityValue = currentHumidityValue;
		zunoSendReport(SENSOR_HUMIDITY_CHANNEL);
	}
	delay(50);
}
