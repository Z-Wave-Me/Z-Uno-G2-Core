#define MY_SERIAL		Serial
#define OFFSET_CURRENT		0
#define OFFSET_OLD			1

uint8_t component_value_channel_0[2][10];
uint8_t component_value_channel_1[2][10];

ZUNO_SETUP_CHANNELS(
	ZUNO_SWITCH_COLOR(SWITCH_COLOR_FLAGS_RED|SWITCH_COLOR_FLAGS_GREEN|SWITCH_COLOR_FLAGS_BLUE, getterFunctionSwitchColor, setterFunctionSwitchColor),
	ZUNO_SWITCH_COLOR(SWITCH_COLOR_FLAGS_CYAN|SWITCH_COLOR_FLAGS_PURPLE|SWITCH_COLOR_FLAGS_AMBER|SWITCH_COLOR_FLAGS_COLD_WHITE, getterFunctionSwitchColor, setterFunctionSwitchColor)
)

void setup(void) {
	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Command class switch color!");
}

void loop(void) {
	size_t									i;

	i = 0;
	while (i < sizeof(component_value_channel_0[OFFSET_CURRENT])) {
		if (component_value_channel_0[OFFSET_OLD][i] != component_value_channel_0[OFFSET_CURRENT][i]) {
			MY_SERIAL.printf("Channel 0 color component %d new value %d\n", i, component_value_channel_0[OFFSET_CURRENT][i]);
			component_value_channel_0[OFFSET_OLD][i] = component_value_channel_0[OFFSET_CURRENT][i];
		}
		i++;
	}
	i = 0;
	while (i < sizeof(component_value_channel_1[OFFSET_CURRENT])) {
		if (component_value_channel_1[OFFSET_OLD][i] != component_value_channel_1[OFFSET_CURRENT][i]) {
			MY_SERIAL.printf("Channel 1 color component %d new value %d\n", i, component_value_channel_1[OFFSET_CURRENT][i]);
			component_value_channel_1[OFFSET_OLD][i] = component_value_channel_1[OFFSET_CURRENT][i];
		}
		i++;
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
