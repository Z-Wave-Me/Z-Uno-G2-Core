#include "Arduino.h"

#define MY_SERIAL Serial0

ZUNO_ENABLE(
		// LOGGING_DBG
		ZUNO_PIN_V=0x704
		DBG_CONSOLE_BAUDRATE=921600
		SKETCH_VERSION=0x0001
		CERT_BUILD
		WITH_CC_THERMOSTAT_OPERATING_STATE
		WITH_CC_THERMOSTAT_FAN_MODE
		WITH_CC_THERMOSTAT_FAN_STATE
);


typedef struct __ThermostatExample_s
{
	ssize_t value;
	ssize_t value_old;
	uint8_t mode;
	uint8_t mode_old;
	uint8_t mode_fan;
	uint8_t mode_fan_old;
	bool mode_fan_off;
	bool mode_fan_off_old;
} __ThermostatExample_t;

static __ThermostatExample_t __heat_thermostat =
{
	.value = 0,
	.value_old = 0,
	.mode = THERMOSTAT_MODE_OFF,
	.mode_old = THERMOSTAT_MODE_OFF,
	.mode_fan = THERMOSTAT_FAN_MODE_AUTO_LOW,
	.mode_fan_old = THERMOSTAT_FAN_MODE_AUTO_LOW,
	.mode_fan_off = false,
	.mode_fan_off_old = false,
};

static __ThermostatExample_t __cool_thermostat =
{
	.value = 0,
	.value_old = 0,
	.mode = THERMOSTAT_MODE_OFF,
	.mode_old = THERMOSTAT_MODE_OFF,
	.mode_fan = THERMOSTAT_FAN_MODE_LOW,
	.mode_fan_old = THERMOSTAT_FAN_MODE_LOW,
	.mode_fan_off = false,
	.mode_fan_off_old = false,
};

int pinPWM1ThermostatTemperatureState;

// Set avaliable S2-keys
ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_ACCESS_BIT | SKETCH_FLAG_S0_BIT);

#define THERMOSTAT_MODES_CHANNEL_ONE (THERMOSTAT_FLAGS_OFF | THERMOSTAT_FLAGS_HEAT | THERMOSTAT_FLAGS_ENERGY_SAVE_HEATING | THERMOSTAT_FLAGS_AWAY_HEATING | THERMOSTAT_FAN_MODE_AUTO_LOW_MASK | THERMOSTAT_FAN_MODE_AUTO_HIGH_MASK | THERMOSTAT_FAN_MODE_AUTO_MEDIUM_MASK)
#define THERMOSTAT_LIMITS_CHANNEL_ONE (5 | THERMOSTAT_SIZE_FOUR_BYTES | THERMOSTAT_PRECISION_FOUR_DECIMALS)
#define THERMOSTAT_MODES_CHANNEL_TWO (THERMOSTAT_FLAGS_OFF | THERMOSTAT_FLAGS_COOL | THERMOSTAT_FLAGS_ENERGY_SAVE_COOLING | THERMOSTAT_FLAGS_AWAY_COOLING | THERMOSTAT_FAN_MODE_LOW_MASK | THERMOSTAT_FAN_MODE_HIGH_MASK | THERMOSTAT_FAN_MODE_MEDIUM_MASK | THERMOSTAT_FAN_MODE_CIRCULATION_MASK)
#define THERMOSTAT_LIMITS_CHANNEL_TWO (5 | THERMOSTAT_SIZE_FOUR_BYTES | THERMOSTAT_PRECISION_SIX_DECIMALS)

// Z-Wave channels
ZUNO_SETUP_CHANNELS(
	ZUNO_THERMOSTAT(THERMOSTAT_MODES_CHANNEL_ONE, THERMOSTAT_UNITS_CELSIUS, THERMOSTAT_RANGE_POS, THERMOSTAT_LIMITS_CHANNEL_ONE, __heat_thermostat_mode_getter, __heat_thermostat_mode_setter, __heat_thermostat_set_point_getter, __heat_thermostat_set_point_setter),
	ZUNO_THERMOSTAT(THERMOSTAT_MODES_CHANNEL_TWO, THERMOSTAT_UNITS_FAHRENHEIT, THERMOSTAT_RANGE_POS | THERMOSTAT_RANGE_NEG, THERMOSTAT_LIMITS_CHANNEL_TWO, __cool_thermostat_mode_getter, __cool_thermostat_mode_setter, __cool_thermostat_set_point_getter, __cool_thermostat_set_point_setter)
);

void setup(void) {
	#if !defined(LOGGING_DBG)
	MY_SERIAL.begin(DBG_CONSOLE_BAUDRATE);
	#endif
	MY_SERIAL.print("example thermostat!!!\n");
}

static const char *__thermostat_mode_print_to_str(size_t mode) {
	const char *out;

	switch (mode) {
		case THERMOSTAT_MODE_OFF:
			out = "MODE OFF";
			break;
		case THERMOSTAT_MODE_HEAT:
			out = "MODE HEAT";
			break;
		case THERMOSTAT_MODE_COOL:
			out = "MODE COOL";
			break;
		case THERMOSTAT_MODE_FURNACE:
			out = "MODE FURNACE";
			break;
		case THERMOSTAT_MODE_DRY:
			out = "MODE DRY";
			break;
		case THERMOSTAT_MODE_MOIST:
			out = "MODE MOIST";
			break;
		case THERMOSTAT_MODE_AUTO_CHANGEOVER:
			out = "MODE AUTO";
			break;
		case THERMOSTAT_MODE_ENERGY_SAVE_HEATING:
			out = "MODE ENERGY SAVE HEATING";
			break;
		case THERMOSTAT_MODE_ENERGY_SAVE_COOLING:
			out = "MODE ENERGY SAVE COOLING";
			break;
		case THERMOSTAT_MODE_AWAY_HEATING:
			out = "MODE AWAY HEATING";
			break;
		case THERMOSTAT_MODE_AWAY_COOLING:
			out = "MODE AWAY COOLING";
			break;
		case THERMOSTAT_MODE_FULL_POWER:
			out = "MODE FULL POWER";
			break;
		default:
			out = "MODE UNKNOWN";
			break;
	}
	return (out);
}

static const char *__thermostat_mode_fan_print_to_str(size_t mode) {
	const char *out;

	switch (mode) {
		case THERMOSTAT_FAN_MODE_AUTO_LOW:
			out = "MODE FAN AUTO LOW";
			break;
		case THERMOSTAT_FAN_MODE_LOW:
			out = "MODE FAN LOW";
			break;
		case THERMOSTAT_FAN_MODE_AUTO_HIGH:
			out = "MODE FAN AUTO HIGH";
			break;
		case THERMOSTAT_FAN_MODE_HIGH:
			out = "MODE FAN HIGH";
			break;
		case THERMOSTAT_FAN_MODE_AUTO_MEDIUM:
			out = "MODE FAN AUTO MEDIUM";
			break;
		case THERMOSTAT_FAN_MODE_MEDIUM:
			out = "MODE FAN MEDIUM";
			break;
		case THERMOSTAT_FAN_MODE_CIRCULATION:
			out = "MODE FAN CIRCULATION";
			break;
		case THERMOSTAT_FAN_MODE_HUMIDITY_CIRCULATION:
			out = "MODE FAN HUMIDITY CIRCULATION";
			break;
		case THERMOSTAT_FAN_MODE_LEFT_RIGHT:
			out = "MODE FAN LEFT & RIGHT";
			break;
		case THERMOSTAT_FAN_MODE_UP_DOWN:
			out = "MODE FAN UP & DOWN";
			break;
		case THERMOSTAT_FAN_MODE_QUIET:
			out = "MODE FAN QUIET";
			break;
		default:
			out = "MODE FAN UNKNOWN";
			break;
	}
	return (out);
}

static const char *__thermostat_mode_fan_off_print_to_str(bool value) {
	if (value == true)
	{
		return "OFF TRUE";
	}
	return "OFF FALSE";
}

static void __thermostat_print(const char *tag, __ThermostatExample_t *thermostat) {
	size_t mode;
	size_t mode_old;
	ssize_t value;
	ssize_t value_old;
	bool mode_fan_off;
	bool mode_fan_off_old;

	if (thermostat->mode != thermostat->mode_old) {
		mode = thermostat->mode;
		mode_old = thermostat->mode_old;
		thermostat->mode_old = mode;
		MY_SERIAL.print(tag);
		MY_SERIAL.print(__thermostat_mode_print_to_str(mode_old));
		MY_SERIAL.print(" >> ");
		MY_SERIAL.print(__thermostat_mode_print_to_str(mode));
		MY_SERIAL.print("\n");
	}
	if (thermostat->mode_fan != thermostat->mode_fan_old) {
		mode = thermostat->mode_fan;
		mode_old = thermostat->mode_fan_old;
		thermostat->mode_fan_old = mode;
		MY_SERIAL.print(tag);
		MY_SERIAL.print(__thermostat_mode_fan_print_to_str(mode_old));
		MY_SERIAL.print(" >> ");
		MY_SERIAL.print(__thermostat_mode_fan_print_to_str(mode));
		MY_SERIAL.print("\n");
	}
	if (thermostat->mode_fan_off != thermostat->mode_fan_off_old) {
		mode_fan_off = thermostat->mode_fan_off;
		mode_fan_off_old = thermostat->mode_fan_off_old;
		thermostat->mode_fan_off_old = mode_fan_off;
		MY_SERIAL.print(tag);
		MY_SERIAL.print(__thermostat_mode_fan_off_print_to_str(mode_fan_off_old));
		MY_SERIAL.print(" >> ");
		MY_SERIAL.print(__thermostat_mode_fan_off_print_to_str(mode_fan_off));
		MY_SERIAL.print("\n");
	}
	if (thermostat->value != thermostat->value_old) {
		value = thermostat->value;
		value_old = thermostat->value_old;
		thermostat->value_old = value;
		MY_SERIAL.print(tag);
		MY_SERIAL.print(value_old);
		MY_SERIAL.print(" >> ");
		MY_SERIAL.print(value);
		MY_SERIAL.print("\n");
	}
}

void loop(void) {
	__thermostat_print("THERMOSTAT HEAT: ", &__heat_thermostat);
	__thermostat_print("THERMOSTAT COOL: ", &__cool_thermostat);
}

uint8_t __heat_thermostat_mode_getter(void) {
	return __heat_thermostat.mode;
}

void __heat_thermostat_mode_setter(uint8_t value) {
	__heat_thermostat.mode = value;
}

int __heat_thermostat_set_point_getter(uint8_t mode) {
	return __heat_thermostat.value;
	(void)mode;
}

void __heat_thermostat_set_point_setter(uint8_t mode, int value) {
	__heat_thermostat.value = value;
	(void)mode;
}

uint8_t __cool_thermostat_mode_getter(void) {
	return __cool_thermostat.mode;
}

void __cool_thermostat_mode_setter(uint8_t value) {
	__cool_thermostat.mode = value;
}

int __cool_thermostat_set_point_getter(uint8_t mode) {
	return __cool_thermostat.value;
	(void)mode;
}

void __cool_thermostat_set_point_setter(uint8_t mode, int value) {
	__cool_thermostat.value = value;
	(void)mode;
}

static uint8_t __zuno_CCThermostatOperationState_convert(uint8_t mode) {
	uint8_t out;

	switch (mode) {
		case THERMOSTAT_MODE_HEAT:
		case THERMOSTAT_MODE_ENERGY_SAVE_HEATING:
		case THERMOSTAT_MODE_AWAY_HEATING:
			out = THERMOSTAT_OPERATING_STATE_HEATING;
			break;
		case THERMOSTAT_MODE_COOL:
		case THERMOSTAT_MODE_ENERGY_SAVE_COOLING:
		case THERMOSTAT_MODE_AWAY_COOLING:
			out = THERMOSTAT_OPERATING_STATE_COOLING;
			break;
		default:
			out = THERMOSTAT_OPERATING_STATE_IDLE;
			break;
	}
	return (out);
}

uint8_t zuno_CCThermostatOperationState(uint8_t channel) {
	if (channel == 0)
		return (__zuno_CCThermostatOperationState_convert(__heat_thermostat.mode));
	if (channel == 1)
		return (__zuno_CCThermostatOperationState_convert(__cool_thermostat.mode));
	return (THERMOSTAT_OPERATING_STATE_IDLE);
}


uint8_t zuno_CCThermostatFanModeGet(uint8_t channel) {
	if (channel == 0) {
		return (__heat_thermostat.mode_fan);
	}
	if (channel == 1)
		return (__cool_thermostat.mode_fan);
	return (THERMOSTAT_FAN_MODE_AUTO_LOW);
}

bool zuno_CCThermostatFanModeIsOff(uint8_t channel) {
	if (channel == 0) {
		return (__heat_thermostat.mode_fan_off);
	}
	if (channel == 1)
		return (__cool_thermostat.mode_fan_off);
	return (false);
}

void zuno_CCThermostatFanModeSet(uint8_t channel, uint8_t mode, bool off) {

	switch (channel) {
		case 0:
			__heat_thermostat.mode_fan_off = off;
			__heat_thermostat.mode_fan = mode;
			break ;
		case 1:
			__cool_thermostat.mode_fan_off = off;
			__cool_thermostat.mode_fan = mode;
			break ;
	}
}

static uint8_t __zuno_CCThermostatFanState_convert(uint8_t mode) {
	uint8_t out;

	switch (mode) {
		case THERMOSTAT_FAN_MODE_AUTO_LOW:
		case THERMOSTAT_FAN_MODE_LOW:
			out = THERMOSTAT_FAN_STATE_RUNNING;
			break;
		case THERMOSTAT_FAN_MODE_AUTO_HIGH:
		case THERMOSTAT_FAN_MODE_HIGH:
			out = THERMOSTAT_FAN_STATE_RUNNING_HIGH;
			break;
		case THERMOSTAT_FAN_MODE_AUTO_MEDIUM:
		case THERMOSTAT_FAN_MODE_MEDIUM:
			out = THERMOSTAT_FAN_STATE_RUNNING_MEDIUM;
			break;
		case THERMOSTAT_FAN_MODE_CIRCULATION:
			out = THERMOSTAT_FAN_STATE_CIRCULATION;
			break;
		case THERMOSTAT_FAN_MODE_HUMIDITY_CIRCULATION:
			out = THERMOSTAT_FAN_STATE_HUMIDITY_CIRCULATION;
			break;
		case THERMOSTAT_FAN_MODE_LEFT_RIGHT:
			out = THERMOSTAT_FAN_STATE_LEFT_RIGHT;
			break;
		case THERMOSTAT_FAN_MODE_UP_DOWN:
			out = THERMOSTAT_FAN_STATE_UP_DOWN;
			break;
		case THERMOSTAT_FAN_MODE_QUIET:
			out = THERMOSTAT_FAN_STATE_QUIET;
			break;
		default:
			out = THERMOSTAT_FAN_STATE_IDLE;
			break;
	}
	return (out);
}


uint8_t zuno_CCThermostatFanState(uint8_t channel) {
	if (channel == 0) {
		if (__heat_thermostat.mode_fan_off == true)
			return (THERMOSTAT_FAN_STATE_IDLE);
		return (__zuno_CCThermostatFanState_convert(__heat_thermostat.mode_fan));
	}
	if (channel == 1) {
		if (__cool_thermostat.mode_fan_off == true)
			return (THERMOSTAT_FAN_STATE_IDLE);
		return (__zuno_CCThermostatFanState_convert(__cool_thermostat.mode_fan));
	}
	return (THERMOSTAT_FAN_STATE_IDLE);
}
