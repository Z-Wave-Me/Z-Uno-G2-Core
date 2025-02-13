#include "ZUNO_DependenciesCC.h"
#include "ZWCCDoorLock.h"
#include "ZWCCThermostat.h"
#include "ZWCCSwitchColor.h"

typedef struct __ZUnoDevTypeDef_s
{
	_ZunoChannelNumber_t type;
	_ZUnoDevTypeDef_t info;
} __ZUnoDevTypeDef_t;


const _ZUNOChannelCCS_t __cc_types[] =
{
#if defined(WITH_CC_SWITCH_BINARY)
	{
		.type = ZUNO_SWITCH_BINARY_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE | CHANNEL_TYPE_FLAGS_BASIC_MAPPER,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_SWITCH_BINARY,
				.version = SWITCH_BINARY_VERSION,
			}
		}
	}
#endif
#if defined(WITH_CC_SWITCH_MULTILEVEL)
	{
		.type = ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE | CHANNEL_TYPE_FLAGS_BASIC_MAPPER,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_SWITCH_MULTILEVEL,
				.version = SWITCH_MULTILEVEL_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_NOTIFICATION)
	{
		.type = ZUNO_SENSOR_BINARY_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_NOTIFICATION,
				.version = NOTIFICATION_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_SENSOR_MULTILEVEL)
	{
		.type = ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_SENSOR_MULTILEVEL,
				.version = SENSOR_MULTILEVEL_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_METER)
	{
		.type = ZUNO_METER_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_METER,
				.version = METER_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_DOORLOCK)
	{
		.type = ZUNO_DOORLOCK_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_BASIC_MAPPER,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_DOOR_LOCK,
				.version = DOOR_LOCK_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT) || defined(WITH_CC_THERMOSTAT_OPERATING_STATE) || defined(WITH_CC_THERMOSTAT_FAN_MODE) || defined(WITH_CC_THERMOSTAT_FAN_STATE)
	{
		.type = ZUNO_THERMOSTAT_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE,
		.num_ccs = 0
#if defined(WITH_CC_THERMOSTAT_MODE)
		+ 1
#endif
#if defined(WITH_CC_THERMOSTAT_SETPOINT)
		+ 1
#endif
#if defined(WITH_CC_THERMOSTAT_OPERATING_STATE)
		+ 1
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_MODE)
		+ 1
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_STATE)
		+ 1
#endif
		,
		.ccs =
		{
#if defined(WITH_CC_THERMOSTAT_MODE)
			{
				.cc = COMMAND_CLASS_THERMOSTAT_MODE,
				.version = THERMOSTAT_MODE_VERSION_RELEASED,
			},
#endif
#if defined(WITH_CC_THERMOSTAT_SETPOINT)
			{
				.cc = COMMAND_CLASS_THERMOSTAT_SETPOINT,
				.version = THERMOSTAT_SETPOINT_VERSION_RELEASED,
			},
#endif
#if defined(WITH_CC_THERMOSTAT_OPERATING_STATE)
			{
				.cc = COMMAND_CLASS_THERMOSTAT_OPERATING_STATE,
				.version = THERMOSTAT_OPERATING_STATE_VERSION_RELEASED,
			},
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_MODE)
			{
				.cc = COMMAND_CLASS_THERMOSTAT_FAN_MODE,
				.version = THERMOSTAT_FAN_MODE_VERSION_RELEASED,
			},
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_STATE)
			{
				.cc = COMMAND_CLASS_THERMOSTAT_FAN_STATE,
				.version = THERMOSTAT_FAN_STATE_VERSION_RELEASED,
			},
#endif
		}
	},
#endif
#if defined(WITH_CC_SWITCH_COLOR)
	{
		.type = ZUNO_SWITCH_COLOR_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE | CHANNEL_TYPE_FLAGS_BASIC_MAPPER,
		.num_ccs = 2,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_SWITCH_COLOR,
				.version = SWITCH_COLOR_VERSION,
			},
			{
				.cc = COMMAND_CLASS_SWITCH_MULTILEVEL,
				.version = SWITCH_MULTILEVEL_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_SOUND_SWITCH)
	{
		.type = ZUNO_SOUND_SWITCH_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE,
		.num_ccs = 1,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_SOUND_SWITCH,
				.version = SOUND_SWITCH_VERSION,
			}
		}
	},
#endif
#if defined(WITH_CC_WINDOW_COVERING)
	{
		.type = ZUNO_WINDOW_COVERING_CHANNEL_NUMBER,
		.flags = CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE | CHANNEL_TYPE_FLAGS_BASIC_MAPPER,
		.num_ccs = 2,
		.ccs =
		{
			{
				.cc = COMMAND_CLASS_WINDOW_COVERING,
				.version = WINDOW_COVERING_VERSION,
			},
			{
				.cc = COMMAND_CLASS_SWITCH_MULTILEVEL,
				.version = SWITCH_MULTILEVEL_VERSION,
			}
		}
	},
#endif
};

static const __ZUnoDevTypeDef_t __dev_types[] =
{
#if defined(WITH_CC_NOTIFICATION)
	{
		.type = ZUNO_SENSOR_BINARY_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_SENSOR_NOTIFICATION, SPECIFIC_TYPE_NOTIFICATION_SENSOR, ICON_TYPE_UNASSIGNED, ICON_TYPE_UNASSIGNED},
	},
#endif
#if defined(WITH_CC_SENSOR_MULTILEVEL)
	{
		.type = ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_SENSOR_MULTILEVEL, SPECIFIC_TYPE_ROUTING_SENSOR_MULTILEVEL, ICON_TYPE_UNASSIGNED, ICON_TYPE_UNASSIGNED},
	},
#endif
#if defined(WITH_CC_METER)
	{
		.type = ZUNO_METER_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_METER, SPECIFIC_TYPE_NOT_USED, ICON_TYPE_GENERIC_SENSOR_MULTILEVEL, ICON_TYPE_GENERIC_SENSOR_MULTILEVEL},
	},
#endif
#if defined(WITH_CC_DOORLOCK)
	{
		.type = ZUNO_DOORLOCK_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_ENTRY_CONTROL, SPECIFIC_TYPE_DOOR_LOCK, ICON_TYPE_GENERIC_ENTRY_CONTROL, ICON_TYPE_GENERIC_ENTRY_CONTROL},
	},
#endif
#if defined(WITH_CC_THERMOSTAT_MODE)
	{
		.type = ZUNO_THERMOSTAT_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_THERMOSTAT, SPECIFIC_TYPE_THERMOSTAT_GENERAL_V2, ICON_TYPE_GENERIC_THERMOSTAT, ICON_TYPE_GENERIC_THERMOSTAT},
	},
#endif
#if defined(WITH_CC_SWITCH_COLOR)
	{
		.type = ZUNO_SWITCH_COLOR_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_SWITCH_MULTILEVEL, SPECIFIC_TYPE_COLOR_TUNABLE_MULTILEVEL, ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH, ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH},
	},
#endif
#if defined(WITH_CC_SOUND_SWITCH)
	{
		.type = ZUNO_SOUND_SWITCH_CHANNEL_NUMBER,
		.info = {GENERIC_TYPE_AV_CONTROL_POINT, SPECIFIC_TYPE_SOUND_SWITCH, ICON_TYPE_UNASSIGNED, ICON_TYPE_UNASSIGNED}
	},
#endif
};

const _ZUnoDevTypeDef_t *_zunoGetDevTypes(_ZunoChannelNumber_t type) {
	static const _ZUnoDevTypeDef_t default_value = {SPECIFIC_TYPE_NOT_USED, SPECIFIC_TYPE_NOT_USED, ICON_TYPE_UNASSIGNED, ICON_TYPE_UNASSIGNED};
	size_t i;

	i = 0;
	while (i < (sizeof(__dev_types) / sizeof(__dev_types[0]))) {
		if (__dev_types[i].type == type)
			return (&__dev_types[i].info);
		i++;
	}
	return (&default_value);
}

const _ZUNOChannelCCS_t *_zunoGetCCTypes(_ZunoChannelNumber_t type) {
	size_t i;

	i = 0;
	while (i < (sizeof(__cc_types) / sizeof(__cc_types[0]))) {
		if (__cc_types[i].type == type)
			return (&__cc_types[i]);
		i++;
	}
	return (NULL);
}