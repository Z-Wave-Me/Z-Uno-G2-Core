#ifndef ZWCC_SWITCH_COLOR_PRIVATE_H
#define ZWCC_SWITCH_COLOR_PRIVATE_H

#include "Arduino.h"

# define ZUNO_TIMER_COLOR_MAX_VALUE			0xFF//Maximum value when dimming
# define ZUNO_TIMER_COLOR_MIN_VALUE			0x0//The minimum value when dimming

# define ZUNO_TIMER_COLOR_INC					0x1//Indicates what should be up
# define ZUNO_TIMER_COLOR_DEC					0x2//Indicates what should be down
# define ZUNO_TIMER_COLOR_ON					0x70//Indicates that dimming is in progress.

# define ZUNO_TIMER_COLOR_DEFAULT_DURATION	0xFF//The default dimming period is seconds.

typedef struct					ZwSwitchColorSupportedReporFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentMask1;/* MSB */
	uint8_t						colorComponentMask2;/* LSB */
}								ZwSwitchColorSupportedReporFrame_t;//ZW_SWITCH_COLOR_SUPPORTED_REPORTV3Frame

typedef struct					ZwSwitchColorGetFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZwSwitchColorGetFrame_t;//ZW_SWITCH_COLOR_GETV3Frame

typedef struct					ZwSwitchColorReportV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								ZwSwitchColorReportV2Frame_t;

typedef struct					ZwSwitchColorReportV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						currentValue;/**/
	uint8_t						targetValue;/**/
	uint8_t						duration;/**/
}								ZwSwitchColorReportV3Frame_t;

typedef union					ZwSwitchColorReportFrame_u {//For more convenient support, several versions of commands
	ZwSwitchColorReportV2Frame_t					v2;
	ZwSwitchColorReportV3Frame_t					v3;
}								ZwSwitchColorReportFrame_t;

/************************************************************/
/* Switch Color Set variant group structs */                
/************************************************************/
typedef struct					VgSwitchColorSetVg_s {
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								VgSwitchColorSetVg_t;//VG_SWITCH_COLOR_SET_V3_VG

typedef struct					ZwSwitchColorSetFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	VgSwitchColorSetVg_t		variantgroup[4];/**/
}								ZwSwitchColorSetFrame_t;//ZW_SWITCH_COLOR_SET_4BYTE_FRAME

typedef struct					ZwSwitchColorStartLevelChangeV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
}								ZwSwitchColorStartLevelChangeV2Frame_t;


typedef struct					ZwSwitchColorStartLevelChangeV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
	uint8_t						duration;/**/
}								ZwSwitchColorStartLevelChangeV3Frame_t;

typedef union {//For more convenient support, several versions of commands
	ZwSwitchColorStartLevelChangeV2Frame_t		v2;
	ZwSwitchColorStartLevelChangeV3Frame_t		v3;
}								ZwSwitchColorStartLevelChange_FRAME_u;


typedef struct					ZwSwitchColorStopLevelChange_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZwSwitchColorStopLevelChange_t;//ZW_SWITCH_COLOR_STOP_LEVEL_CHANGEV3Frame

#endif // ZWCC_SWITCH_COLOR_PRIVATE_H