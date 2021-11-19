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

ZUNO_ENABLE(LOGGING_DBG LOGGING_UART=Serial0 MODERN_MULTICHANNEL WITH_CC_MULTICHANNEL WITH_CC_TIME_PARAMETERS WITH_CC_WAKEUP WITH_CC_BATTERY);//LOGGING_DBG LOGGING_UART=Serial0 SKETCH_FLAGS=HEADER_FLAGS_DBG
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

#define TEMP_HYST_PARAM 64 //0.5 *C
#define HUMIDITY_HYST_PARAM 65 // 0.5%
#define MOTION_RETRIGGER_TIME_PARAM 66 // 5 seconds

#define MIN_CFG_PARAM		64
#define MAX_CFG_PARAM		68

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
ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_ACCESS_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);
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
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY, SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE, 2, 1,lastHumidityValue),
	ZUNO_SWITCH_COLOR(SWITCH_COLOR_FLAGS_RED|SWITCH_COLOR_FLAGS_GREEN|SWITCH_COLOR_FLAGS_BLUE, getterFunction, setterFunction),
	ZUNO_THERMOSTAT(THERMOSTAT_FLAGS_OFF | THERMOSTAT_FLAGS_COOL,THERMOSTAT_UNITS_CELSIUS, THERMOSTAT_RANGE_NEG|THERMOSTAT_RANGE_POS, 3,thermModeGetterC,thermModeSetterC,thermPointGetterC,thermPointSetterC),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_ENABLE, ZUNO_METER_WATER_SCALE_METERS3, METER_SIZE_FOUR_BYTES, METER_PRECISION_THREE_DECIMALS, getterFunctionMeter, resetterFunction),
	ZUNO_DOORLOCK(getterFunctionDoor, setterFunctionDoor)
);


uint32_t  currentValueMeter;
uint8_t currentValueDoor= 0;
uint8_t _color[10] = {0};

BYTE g_therm_mode = THERMOSTAT_MODE_OFF;
int g_therm_point;//[] = {250,250,250,250, 250,250,250,250}; // 25.0
BYTE g_update = FALSE;
dword last_report_time = 0;

BYTE getterFunctionDoor() {
    return currentValueDoor;
}

void setterFunctionDoor(BYTE newValue) {
    currentValueDoor = newValue;
}


DWORD getterFunctionMeter() {
    return  currentValueMeter;
}

void resetterFunction(uint32_t v) {
     currentValueMeter = v;
}

BYTE getterFunction(BYTE component) {
	return (_color[component]);
}

void setterFunction(BYTE component, BYTE newValue) {
	_color[component] = newValue;
}

BYTE thermModeGetterC(){
  return g_therm_mode;
}
void thermModeSetterC(BYTE mode){
	g_therm_mode = mode;
	g_update = TRUE;
}
WORD thermPointGetterC(BYTE mode){
	return g_therm_point;
	(void)mode;
}
void thermPointSetterC(BYTE mode,WORD point){
	g_update = TRUE;
	g_therm_point = point;
	(void)mode;
}

static const ZunoCFGParameter_t lp_param[] =
{
	{
		.name = "Temperature hysteresis",
		.info = "Defines hysteresis of temperature reports in 10th of *C",
		.minValue = 0x1,
		.maxValue = 0x14,
		.defaultValue = 0x5,
		.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
		.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
		.readOnly = false,
		.altering = false
	},
	{
		.name = "Humidity hysteresis",
		.info = "Defines hysteresis of temperature reports in 10th of %",
		.minValue = 0x1,
		.maxValue = 0x14,
		.defaultValue = 0x5,
		.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
		.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
		.readOnly = false,
		.altering = false
	},
	{
		.name = "Motion trigger time",
		.info = "Minimal time interval of the next motion sensor trigger",
		.minValue = 0x0,
		.maxValue = 0x5000,
		.defaultValue = 0x1000,
		.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
		.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
		.readOnly = false,
		.altering = false
	},
	{
		.name = "param67",
		.info = "param67",
		.minValue = 0xAB,
		.maxValue = 0x37,
		.defaultValue = 0x20,
		.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
		.format = ZUNO_CFG_PARAMETER_FORMAT_SIGNED,
		.readOnly = false,
		.altering = false
	},
	{
		.name = "param68",
		.info = "param68",
		.minValue = 0xFFAB,
		.maxValue = 0x3FAB,
		.defaultValue = 0x20,
		.size = ZUNO_CFG_PARAMETER_SIZE_16BIT,
		.format = ZUNO_CFG_PARAMETER_FORMAT_SIGNED,
		.readOnly = true,
		.altering = false
	}
};

const ZunoCFGParameter_t *zunoCFGParameter(size_t param) {

	if (param < MIN_CFG_PARAM || param > MAX_CFG_PARAM)
		return (ZUNO_CFG_PARAMETER_UNKNOWN);
	return (&lp_param[param - MIN_CFG_PARAM]);
}

static void _default_cfg(void)
{
	uint32_t					value;
	uint32_t					i;

	if (zunoNID() == 0x0) {
		i = MIN_CFG_PARAM;
		while (i <= MAX_CFG_PARAM) {
			zunoSaveCFGParam(i, (uint32_t)lp_param[i - MIN_CFG_PARAM].defaultValue);
			i++;
		}
		return ;
	}
	i = MIN_CFG_PARAM;
	while (i <= MAX_CFG_PARAM) {
		value = zunoLoadCFGParam(i);
		if (lp_param[i - MIN_CFG_PARAM].format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED)
		{
			if ((ssize_t)value < lp_param[i - MIN_CFG_PARAM].minValue || (ssize_t)value > lp_param[i - MIN_CFG_PARAM].maxValue)
				zunoSaveCFGParam(i, (uint32_t)lp_param[i - MIN_CFG_PARAM].defaultValue);
		}
		else {
			if (value < (uint32_t)lp_param[i - MIN_CFG_PARAM].minValue || value > (uint32_t)lp_param[i - MIN_CFG_PARAM].maxValue)
				zunoSaveCFGParam(i, (uint32_t)lp_param[i - MIN_CFG_PARAM].defaultValue);
		}
		i++;
	}
	return ;
	
}
bool zunoAddBaseCCS(byte ccs, byte version);

void setup() {
	// if(zunoStartDeviceConfiguration()) {
		// zunoAddBaseCCS(COMMAND_CLASS_TIME_PARAMETERS, 0x1);
		// zunoAddBaseCCS(COMMAND_CLASS_BATTERY, 0x1);
		// zunoAddBaseCCS(COMMAND_CLASS_WAKE_UP, 0x3);
	// 	zunoCommitCfg();
	// }
	_default_cfg();
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
		if ((millis() - motionTrigTime) < zunoLoadCFGParam(MOTION_RETRIGGER_TIME_PARAM)) {
		lastMotionValue = 1;
		zunoSendReport(SENSOR_MOTION_CHANNEL);
		zunoSendToGroupSetValueCommand(CTRL_GROUP_1, SWITCH_ON);
		}
		motionTrigTime = millis();
	}
	if (lastMotionValue && 
		((millis() - motionTrigTime) > zunoLoadCFGParam(MOTION_RETRIGGER_TIME_PARAM))) {
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