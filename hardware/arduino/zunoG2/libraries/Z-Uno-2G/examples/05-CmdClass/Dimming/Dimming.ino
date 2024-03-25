
#define MY_SERIAL												Serial0

uint8_t switch_binary_current = 0x0;
#ifndef LOGGING_DBG
uint8_t switch_binary_old = 0x0;
#endif
uint8_t switch_multilevel_current = 0x0;
#ifndef LOGGING_DBG
uint8_t switch_multilevel_old = 0x0;
#endif
uint8_t windows_covering_in_right_left_current = 0x0;
#ifndef LOGGING_DBG
uint8_t windows_covering_in_right_left_old = 0x0;
#endif
uint8_t windows_covering_in_left_current = 0x0;
#ifndef LOGGING_DBG
uint8_t windows_covering_in_left_old = 0x0;
#endif
uint8_t door_lock_current = 0x0;
#ifndef LOGGING_DBG
uint8_t door_lock_old = 0x0;
#endif


ZUNO_ENABLE(
			CERT_BUILD
			// 
			// LOGGING_DBG
			// DBG_CONSOLE_PIN=0xFE
			DBG_CONSOLE_BAUDRATE=921600
);

// //ZUNO_SETUP_ASSOCIATIONS(ZUNO_ASSOCIATION_GROUP_SET_VALUE, ZUNO_ASSOCIATION_GROUP_SET_VALUE_AND_DIM)

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_ACCESS_BIT | SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_CHANNELS(
	ZUNO_SWITCH_BINARY(getterFunctionBinary, setterFunctionBinary),
	ZUNO_SWITCH_MULTILEVEL(getterFunctionSwitchMultilevel, setterFunctionSwitchMultilevel),
	ZUNO_WINDOW_COVERING(WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_DEFAULT, (WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT | WINDOW_COVERING_PARAMETER_ID_IN_LEFT), getWindowCoveringlValue, setWindowCoveringlValue),
	ZUNO_DOORLOCK(getterFunctionDoorLock, setterFunctionDoorLock),
	ZUNO_SOUND_SWITCH(50, 1, playMelody1, stopMelody1, melody_set1)
);

ZUNO_SETUP_SOUND_SWITCH(melody_set1,
						ZUNO_SETUP_SOUND_SWITCH_TONE("Fail  Signal", 3),
						ZUNO_SETUP_SOUND_SWITCH_TONE("Alarm Signal", 3),
						ZUNO_SETUP_SOUND_SWITCH_TONE("Accept Signal", 1),
						ZUNO_SETUP_SOUND_SWITCH_TONE("Horse Signal", 5));

zuno_handler_single_gettersetter_t __hdata_widowCoveringGetter1={(void*)&getWindowCoveringlValue,(void*)&setWindowCoveringlValue};
zuno_handler_soundswitch_t __hdata_playMelodyhghgf = {(void*)&melody_set1, (void*)&playMelody1, (void*)&stopMelody1};
void setup(void) {
	zunoAppendChannelHandler( 2,  1, CHANNEL_HANDLER_SINGLE_WINDOWCOVERING, (void*)&__hdata_widowCoveringGetter1);
	zunoAppendChannelHandler(4, 0, CHANNEL_HANDLER_SOUNDSWITCH, (void*)&__hdata_playMelodyhghgf);
	#ifndef LOGGING_DBG
	MY_SERIAL.begin(DBG_CONSOLE_BAUDRATE);
	#endif
}

#ifndef LOGGING_DBG
void _debug(uint8_t current_value, uint8_t *old_value, const char *str) {
	if (old_value[0x0] != current_value) {
		MY_SERIAL.printf("%010ld - %s: %d\n", millis(), str, current_value);
		old_value[0x0] = current_value;
	}
}
#endif

void loop(void) {
	delay(1000);
	USART_Tx(USART0, 'l');
	USART_Tx(USART0, 'o');
	USART_Tx(USART0, 'o');
	USART_Tx(USART0, 'p');
	USART_Tx(USART0, '!');
	USART_Tx(USART0, '\n');
	#ifndef LOGGING_DBG
	_debug(switch_multilevel_current, &switch_multilevel_old, "ZUNO_SWITCH_MULTILEVEL");
	_debug(switch_binary_current, &switch_binary_old, "ZUNO_SWITCH_BINARY");
	_debug(windows_covering_in_right_left_current, &windows_covering_in_right_left_old, "ZUNO_WINDOW_COVERING IN_RIGHT_LEFT");
	_debug(windows_covering_in_left_current, &windows_covering_in_left_old, "ZUNO_WINDOW_COVERING IN_LEFT");
	_debug(door_lock_current, &door_lock_old, "ZUNO_DOORLOCK");
	#endif
}


void playMelody1(uint8_t melody_id, uint8_t volume) {
	#ifndef LOGGING_DBG
	MY_SERIAL.print("ZUNO_SOUND_SWITCH: PLAY ");
	MY_SERIAL.print(melody_id);
	MY_SERIAL.print(" ");
	MY_SERIAL.println(volume);
	#else
	(void)melody_id;
	(void)volume;
	#endif
}
void stopMelody1(uint8_t melody_id) {
	#ifndef LOGGING_DBG
	MY_SERIAL.print("ZUNO_SOUND_SWITCH: STOP ");
	MY_SERIAL.println(melody_id);
	#else
	(void)melody_id;
	#endif
}


uint8_t getterFunctionDoorLock(void) {
	return (door_lock_current);
}

void setterFunctionDoorLock(uint8_t newValue) {
	door_lock_current = newValue;
}

uint8_t getWindowCoveringlValue(uint8_t parameterId) {
	uint8_t								out;

	switch (parameterId) {
		case WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_DEFAULT:
			out = windows_covering_in_right_left_current;
			break ;
		case WINDOW_COVERING_PARAMETER_ID_IN_LEFT_DEFAULT:
			out = windows_covering_in_left_current;
			break ;
		default:
			out = 0x0;
			break ;
	}
	return (out);
}

void setWindowCoveringlValue(uint8_t parameterId, uint8_t newValue) {
	switch (parameterId) {
		case WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_DEFAULT:
			windows_covering_in_right_left_current = newValue;
			break ;
		case WINDOW_COVERING_PARAMETER_ID_IN_LEFT_DEFAULT:
			windows_covering_in_left_current = newValue;
			break ;
		default:
			break ;
	}
}

#ifndef LOGGING_DBG
void zuno_CCWindowCoveringStop(uint8_t channel, uint8_t parameterId) {
	switch (parameterId) {
		case WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_DEFAULT:
			MY_SERIAL.print("ZUNO_WINDOW_COVERING IN_RIGHT_LEFT: STOP\n");
			break ;
		case WINDOW_COVERING_PARAMETER_ID_IN_LEFT_DEFAULT:
			MY_SERIAL.print("ZUNO_WINDOW_COVERING IN_LEFT: STOP\n");
			break ;
		default:
			break ;
	}
	(void)channel;
}
#endif

uint8_t getterFunctionSwitchMultilevel(void) {
	return (switch_multilevel_current);
}

void setterFunctionSwitchMultilevel(uint8_t newValue) {

	switch_multilevel_current = newValue;
}


uint8_t getterFunctionBinary(void) {
	return (switch_binary_current);
}

void setterFunctionBinary(uint8_t newValue) {
	switch_binary_current = newValue;
}
