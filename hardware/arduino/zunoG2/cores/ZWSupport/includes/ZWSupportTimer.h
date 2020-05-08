#ifndef ZW_SUPPORT_TIMER_H
#define ZW_SUPPORT_TIMER_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL	0x3//How many channels at the same time support for dimming

typedef struct					s_ZUNO_TIMER_SWITCH_CHANNEL
{
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
	uint8_t						current_level;//Current Dimming Level
	uint8_t						b_mode;//Stores modes
	uint8_t						duration_dec;//
	uint8_t						channel;//Tracked Channel Number + 1
}								t_ZUNO_TIMER_SWITCH_CHANNEL;


typedef struct					s_ZUNO_TIMER
{
	t_ZUNO_TIMER_SWITCH_CHANNEL	s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10
}								t_ZUNO_TIMER;

extern volatile t_ZUNO_TIMER		g_zuno_timer;

#endif// ZW_SUPPORT_TIMER_H