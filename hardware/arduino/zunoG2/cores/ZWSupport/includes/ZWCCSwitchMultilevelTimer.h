#ifndef ZWCC_SWITCH_MULTILEVEL_TIMER_H
#define ZWCC_SWITCH_MULTILEVEL_TIMER_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_INC					0x1
# define ZUNO_TIMER_SWITCH_DEC					0x2
# define ZUNO_TIMER_SWITCH_ON					0x70
# define ZUNO_TIMER_SWITCH_ONLY_DEC				0x80

# define ZUNO_TIMER_SWITCH_MAX_VALUE			0x63
# define ZUNO_TIMER_SWITCH_MIN_VALUE			0x0

# define ZUNO_TIMER_SWITCH_DEFAULT_DURATION		0x63

typedef struct					s_ZW_SWITCH_MULTILEVEL_SET_V1_FRAME
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						value;/**/
}								t_ZW_SWITCH_MULTILEVEL_SET_V1_FRAME;

typedef struct					s_ZW_SWITCH_MULTILEVEL_SET_V2_FRAME
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						value;/**/
	uint8_t						dimmingDuration;/**/
}								t_ZW_SWITCH_MULTILEVEL_SET_V2_FRAME;

typedef union
{
	t_ZW_SWITCH_MULTILEVEL_SET_V1_FRAME					v1;
	t_ZW_SWITCH_MULTILEVEL_SET_V2_FRAME					v2;
}								u_ZW_SWITCH_MULTILEVEL_SET_FRAME;

typedef struct					s_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
}								t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME;

typedef struct					s_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
}								t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME;

typedef struct					s_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
	uint8_t						stepSize;/**/
}								t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME;

typedef union
{
	t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME	v1;
	t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME	v2;
	t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME	v3;
}								u_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME;

#endif// ZWCC_SWITCH_MULTILEVEL_TIMER_H