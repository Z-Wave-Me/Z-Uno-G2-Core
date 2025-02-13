#ifndef ZUNO_DEPENDENCINES_CC_H
#define ZUNO_DEPENDENCINES_CC_H

#include <stddef.h>
#include <stdint.h>
#include "Custom_decl.h"
#include "Custom_defs.h"

#define ZUNO_CORE_VERSION_MAJOR 0x03
#define ZUNO_CORE_VERSION_MINOR 0x0d

#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
#ifndef WITH_CC_TIME
#define WITH_CC_TIME
#endif
#endif

#ifdef WITH_CC_THERMOSTAT_MODE
	#ifndef WITH_CC_THERMOSTAT_SETPOINT
	#define WITH_CC_THERMOSTAT_SETPOINT
	#endif
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

#ifdef WITH_CC_SWITCH_COLOR
	#ifndef WITH_CC_SWITCH_MULTILEVEL
	#define WITH_CC_SWITCH_MULTILEVEL
	#endif
#endif

#ifdef WITH_CC_WINDOW_COVERING
	#ifndef WITH_CC_SWITCH_MULTILEVEL
	#define WITH_CC_SWITCH_MULTILEVEL
	#endif
#endif

#ifdef WITH_CC_SWITCH_BINARY
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

#ifdef WITH_CC_SWITCH_MULTILEVEL
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

#ifdef WITH_CC_SOUND_SWITCH
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

typedef enum _ZunoChannelNumber_e
{
	ZUNO_SWITCH_BINARY_CHANNEL_NUMBER = 1,
	ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER,
	ZUNO_SENSOR_BINARY_CHANNEL_NUMBER,
	ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER,
	ZUNO_METER_CHANNEL_NUMBER,
	ZUNO_DOORLOCK_CHANNEL_NUMBER,
	ZUNO_METER_TBL_MONITOR_CHANNEL_NUMBER,
	ZUNO_THERMOSTAT_CHANNEL_NUMBER,
	ZUNO_SWITCH_COLOR_CHANNEL_NUMBER,
	ZUNO_SOUND_SWITCH_CHANNEL_NUMBER,
	ZUNO_WINDOW_COVERING_CHANNEL_NUMBER,
} _ZunoChannelNumber_t;

typedef struct _ZUnoDevTypeDef_s
{
	uint8_t gen_type;
	uint8_t spec_type;
	uint16_t icon;
	uint16_t app_icon;
} _ZUnoDevTypeDef_t;

typedef struct _ZUNOCCSVersion_s
{
	uint8_t cc;
	uint8_t version;
} _ZUNOCCSVersion_t;

typedef struct _ZUNOChannelCCS_s
{
	_ZunoChannelNumber_t type;
	uint8_t flags;
	uint8_t num_ccs;
	_ZUNOCCSVersion_t ccs[5];
} _ZUNOChannelCCS_t;

const _ZUnoDevTypeDef_t *_zunoGetDevTypes(_ZunoChannelNumber_t type);
const _ZUNOChannelCCS_t *_zunoGetCCTypes(_ZunoChannelNumber_t type);

#endif // ZUNO_DEPENDENCINES_CC_H