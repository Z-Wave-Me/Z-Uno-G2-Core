#ifndef ZW_SUPPORT_TIMER_H
#define ZW_SUPPORT_TIMER_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL	0x3//How many channels at the same time support for dimming
# define ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL	0x3//How many channels at the same time support for dimming

typedef struct					ZunoTimerSwitchChannel_s {
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
	uint8_t						current_level;//Current Dimming Level
	uint8_t						b_mode;//Stores modes
	uint8_t						channel;//Tracked Channel Number + 1
}								ZunoTimerSwitchChannel_t;

typedef struct					ZunoTimerColorChannel_s {
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
	uint8_t						current_level;//Current Dimming Level
	uint8_t						b_mode;//Stores modes
	uint8_t						channel;//Tracked Channel Number + 1
	uint8_t						colorComponentId;
}								ZunoTimerColorChannel_t;

typedef struct					ZunoTimer_s {
	ZunoTimerSwitchChannel_t	s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	ZunoTimerColorChannel_t		s_color[ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL];
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10
}								ZunoTimer_t;

extern volatile ZunoTimer_t		g_zuno_timer;

#endif// ZW_SUPPORT_TIMER_H