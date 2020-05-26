#ifndef ZWCC_SWITCH_MULTILEVEL_PRIVATE_H
#define ZWCC_SWITCH_MULTILEVEL_PRIVATE_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_INC					0x1//Indicates what should be up
# define ZUNO_TIMER_SWITCH_DEC					0x2//Indicates what should be down
# define ZUNO_TIMER_SWITCH_ON					0x70//Indicates that dimming is in progress.

# define ZUNO_TIMER_SWITCH_MAX_VALUE			0x63//Maximum value when dimming
# define ZUNO_TIMER_SWITCH_MIN_VALUE			0x0//The minimum value when dimming

# define ZUNO_TIMER_SWITCH_DEFAULT_DURATION		0x63//The default dimming period is seconds.


typedef struct					ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
}								ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME_t;

typedef struct					ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
}								ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME_t;

typedef struct					ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
	uint8_t						stepSize;/**/
}								ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME_t;

typedef union {//For more convenient support, several versions of commands
	ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME_t	v1;
	ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME_t	v2;
	ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME_t	v3;
}								ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME_u;

#endif// ZWCC_SWITCH_MULTILEVEL_PRIVATE_H