#include "Arduino.h"

#define MY_SERIAL		Serial0
#define OFFSET_CURRENT		0
#define OFFSET_OLD			1

ZUNO_ENABLE(
	LOGGING_DBG
	ZUNO_PIN_V=0x704
	DBG_CONSOLE_BAUDRATE=921600

);

uint8_t component_value_channel_0[2][10];
uint8_t component_value_channel_1[2][10];
uint8_t component_brightness_channel_0;
uint8_t component_brightness_channel_0_old;
uint8_t component_brightness_channel_1;
uint8_t component_brightness_channel_1_old;

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_CHANNELS(
	ZUNO_SWITCH_COLOR(SWITCH_COLOR_FLAGS_RED|SWITCH_COLOR_FLAGS_GREEN|SWITCH_COLOR_FLAGS_BLUE, getterFunctionSwitchColor, setterFunctionSwitchColor),
	ZUNO_SWITCH_COLOR(SWITCH_COLOR_FLAGS_CYAN|SWITCH_COLOR_FLAGS_PURPLE|SWITCH_COLOR_FLAGS_AMBER|SWITCH_COLOR_FLAGS_COLD_WHITE, getterFunctionSwitchColor, setterFunctionSwitchColor)
)

void setup(void) {
	MY_SERIAL.begin(DBG_CONSOLE_BAUDRATE);
	MY_SERIAL.println("Command class switch color!");
}

static void _color_print(uint8_t channel, uint8_t component, uint8_t value) {
	MY_SERIAL.print("Channel ");
	MY_SERIAL.print(channel);
	MY_SERIAL.print(" color component ");
	switch (component) {
		case SWITCH_COLOR_COMPONENT_WARM_WHITE:
			MY_SERIAL.print("WARM_WHITE");
			break ;
		case SWITCH_COLOR_COMPONENT_COLD_WHITE:
			MY_SERIAL.print("COLD_WHITE");
			break ;
		case SWITCH_COLOR_COMPONENT_RED:
			MY_SERIAL.print("RED");
			break ;
		case SWITCH_COLOR_COMPONENT_GREEN:
			MY_SERIAL.print("GREEN");
			break ;
		case SWITCH_COLOR_COMPONENT_BLUE:
			MY_SERIAL.print("BLUE");
			break ;
		case SWITCH_COLOR_COMPONENT_AMBER:
			MY_SERIAL.print("AMBER");
			break ;
		default:
			MY_SERIAL.print("UNKNOWN");
			break ;
	}
	MY_SERIAL.print(" value ");
	MY_SERIAL.println(value);
}

void loop(void) {
	size_t									i;

	i = 0;
	while (i < sizeof(component_value_channel_0[OFFSET_CURRENT])) {
		if (component_value_channel_0[OFFSET_OLD][i] != component_value_channel_0[OFFSET_CURRENT][i]) {
			_color_print(0, i, component_value_channel_0[OFFSET_CURRENT][i]);
			component_value_channel_0[OFFSET_OLD][i] = component_value_channel_0[OFFSET_CURRENT][i];
		}
		i++;
	}
	i = 0;
	while (i < sizeof(component_value_channel_1[OFFSET_CURRENT])) {
		if (component_value_channel_1[OFFSET_OLD][i] != component_value_channel_1[OFFSET_CURRENT][i]) {
			_color_print(0, i, component_value_channel_1[OFFSET_CURRENT][i]);
			component_value_channel_1[OFFSET_OLD][i] = component_value_channel_1[OFFSET_CURRENT][i];
		}
		i++;
	}
	if (component_brightness_channel_0 != component_brightness_channel_0_old)
	{
		MY_SERIAL.print("Channel 0 brightness ");
		MY_SERIAL.println(component_brightness_channel_0);
		component_brightness_channel_0_old = component_brightness_channel_0;
	}
	if (component_brightness_channel_1 != component_brightness_channel_1_old)
	{
		MY_SERIAL.print("Channel 1 brightness ");
		MY_SERIAL.println(component_brightness_channel_1);
		component_brightness_channel_1_old = component_brightness_channel_1;
	}
}

uint8_t getterFunctionSwitchColor(uint8_t channel, uint8_t component) {
	if (channel == 0) {
		if (component >= sizeof(component_value_channel_0[OFFSET_CURRENT]))
			return (0);
		return (component_value_channel_0[OFFSET_CURRENT][component]);
	}
	if (channel == 1) {
		if (component >= sizeof(component_value_channel_1[OFFSET_CURRENT]))
			return (0);
		return (component_value_channel_1[OFFSET_CURRENT][component]);
	}
	return (0);
}

void setterFunctionSwitchColor(uint8_t channel, uint8_t component, uint8_t newValue) {
	if (channel == 0) {
		if (component >= sizeof(component_value_channel_0[OFFSET_CURRENT]))
			return ;
		component_value_channel_0[OFFSET_CURRENT][component] = newValue;
	}
	if (channel == 1) {
		if (component >= sizeof(component_value_channel_1[OFFSET_CURRENT]))
			return ;
		component_value_channel_1[OFFSET_CURRENT][component] = newValue;
	}
}

void __zunoSetterSwitchColorBrightness(uint8_t channel, uint8_t newValue) {
	switch (channel) {
		case 0:
			component_brightness_channel_0 = newValue;
			break;
		case 1:
			component_brightness_channel_1 = newValue;
			break;
	}
}

uint8_t __zunoGetterSwitchColorBrightness(uint8_t channel) {
	uint8_t brightness;

	switch (channel) {
		case 0:
			brightness = component_brightness_channel_0;
			break ;
		case 1:
			brightness = component_brightness_channel_1;
			break ;
		default:
			brightness = 0;
			break ;
	}
	return (brightness);
}
