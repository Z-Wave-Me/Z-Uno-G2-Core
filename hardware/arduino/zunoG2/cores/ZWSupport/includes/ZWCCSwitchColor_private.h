#ifndef ZWCC_SWITCH_COLOR_PRIVATE_H
#define ZWCC_SWITCH_COLOR_PRIVATE_H

#include "Arduino.h"

# define ZUNO_TIMER_COLOR_MAX_VALUE			0xFF//Maximum value when dimming
# define ZUNO_TIMER_COLOR_MIN_VALUE			0x0//The minimum value when dimming

# define ZUNO_TIMER_COLOR_INC					0x1//Indicates what should be up
# define ZUNO_TIMER_COLOR_DEC					0x2//Indicates what should be down
# define ZUNO_TIMER_COLOR_ON					0x70//Indicates that dimming is in progress.

# define ZUNO_TIMER_COLOR_DEFAULT_DURATION	0xFF//The default dimming period is seconds.

typedef struct					ZW_SWITCH_COLOR_SUPPORTED_REPORT_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentMask1;/* MSB */
	uint8_t						colorComponentMask2;/* LSB */
}								ZW_SWITCH_COLOR_SUPPORTED_REPORT_FRAME_t;//ZW_SWITCH_COLOR_SUPPORTED_REPORT_V3_FRAME

typedef struct					ZW_SWITCH_COLOR_GET_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZW_SWITCH_COLOR_GET_FRAME_t;//ZW_SWITCH_COLOR_GET_V3_FRAME

typedef struct					ZW_SWITCH_COLOR_REPORT_V2_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								ZW_SWITCH_COLOR_REPORT_V2_FRAME_t;

typedef struct					ZW_SWITCH_COLOR_REPORT_V3_FRAME_s{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						currentValue;/**/
	uint8_t						targetValue;/**/
	uint8_t						duration;/**/
}								ZW_SWITCH_COLOR_REPORT_V3_FRAME_t;

typedef union {//For more convenient support, several versions of commands
	ZW_SWITCH_COLOR_REPORT_V2_FRAME_t					v2;
	ZW_SWITCH_COLOR_REPORT_V3_FRAME_t					v3;
}								ZW_SWITCH_COLOR_REPORT_FRAME_u;

/************************************************************/
/* Switch Color Set variant group structs */                
/************************************************************/
typedef struct					VG_SWITCH_COLOR_SET_VG_s {
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								VG_SWITCH_COLOR_SET_VG_t;//VG_SWITCH_COLOR_SET_V3_VG

typedef struct					ZW_SWITCH_COLOR_SET_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	VG_SWITCH_COLOR_SET_VG_t	variantgroup[4];/**/
}								ZW_SWITCH_COLOR_SET_FRAME_t;//ZW_SWITCH_COLOR_SET_4BYTE_FRAME

typedef struct					ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V2_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
}								ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V2_FRAME_t;


typedef struct					ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V3_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
	uint8_t						duration;/**/
}								ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V3_FRAME_t;

typedef union {//For more convenient support, several versions of commands
	ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V2_FRAME_t		v2;
	ZW_SWITCH_COLOR_START_LEVEL_CHANGE_V3_FRAME_t		v3;
}								ZW_SWITCH_COLOR_START_LEVEL_CHANGE_FRAME_u;


typedef struct					ZW_SWITCH_COLOR_STOP_LEVEL_CHANGE_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZW_SWITCH_COLOR_STOP_LEVEL_CHANGE_FRAME_t;//ZW_SWITCH_COLOR_STOP_LEVEL_CHANGE_V3_FRAME

#endif // ZWCC_SWITCH_COLOR_PRIVATE_H