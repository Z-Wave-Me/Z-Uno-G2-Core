#ifndef ZWCC_SWITCH_MULTILEVEL_PRIVATE_H
#define ZWCC_SWITCH_MULTILEVEL_PRIVATE_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_INC					0x1//Indicates what should be up
# define ZUNO_TIMER_SWITCH_DEC					0x2//Indicates what should be down
# define ZUNO_TIMER_SWITCH_ON					0x70//Indicates that dimming is in progress.

# define ZUNO_TIMER_SWITCH_MAX_VALUE			0x63//Maximum value when dimming
# define ZUNO_TIMER_SWITCH_MIN_VALUE			0x0//The minimum value when dimming

# define ZUNO_TIMER_SWITCH_DEFAULT_DURATION		0x63//The default dimming period is seconds.


typedef struct					ZwSwitchMultilevelStopLevelChangeV1Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
}								ZwSwitchMultilevelStopLevelChangeV1Frame_t;

typedef struct					ZwSwitchMultilevelStopLevelChangeV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
}								ZwSwitchMultilevelStopLevelChangeV2Frame_t;

typedef struct					ZwSwitchMultilevelStopLevelChangeV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
	uint8_t						stepSize;/**/
}								ZwSwitchMultilevelStopLevelChangeV3Frame_t;

typedef union					ZwSwitchMultilevelStopLevelChangeFrame_u {//For more convenient support, several versions of commands
	ZwSwitchMultilevelStopLevelChangeV1Frame_t	v1;
	ZwSwitchMultilevelStopLevelChangeV2Frame_t	v2;
	ZwSwitchMultilevelStopLevelChangeV3Frame_t	v3;
}								ZwSwitchMultilevelStopLevelChangeFrame_t;

#endif// ZWCC_SWITCH_MULTILEVEL_PRIVATE_H