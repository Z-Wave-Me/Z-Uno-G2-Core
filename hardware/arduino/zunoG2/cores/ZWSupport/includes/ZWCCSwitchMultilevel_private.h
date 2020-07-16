#ifndef ZWCC_SWITCH_MULTILEVEL_PRIVATE_H
#define ZWCC_SWITCH_MULTILEVEL_PRIVATE_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_INC					0x1//Indicates what should be up
# define ZUNO_TIMER_SWITCH_DEC					0x2//Indicates what should be down
# define ZUNO_TIMER_SWITCH_ON					0x70//Indicates that dimming is in progress.

# define ZUNO_TIMER_SWITCH_MAX_VALUE			0x63//Maximum value when dimming
# define ZUNO_TIMER_SWITCH_MIN_VALUE			0x0//The minimum value when dimming

# define ZUNO_TIMER_SWITCH_DEFAULT_DURATION		0x63//The default dimming period is seconds.

#endif// ZWCC_SWITCH_MULTILEVEL_PRIVATE_H