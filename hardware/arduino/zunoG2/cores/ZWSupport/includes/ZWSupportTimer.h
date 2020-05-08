#ifndef ZW_SUPPORT_TIMER_H
#define ZW_SUPPORT_TIMER_H

#include "stdint.h"

# define ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL	0x3

typedef struct					s_ZUNO_TIMER_SWITCH_CHANNEL
{
	uint32_t					ticks;
	uint32_t					step;
	uint8_t						current_level;
	uint8_t						b_mode;
	uint8_t						duration_dec;
	uint8_t						channel;
}								t_ZUNO_TIMER_SWITCH_CHANNEL;


typedef struct					s_ZUNO_TIMER
{
	t_ZUNO_TIMER_SWITCH_CHANNEL	s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	uint32_t					ticks;
}								t_ZUNO_TIMER;

extern volatile t_ZUNO_TIMER		g_zuno_timer;

#endif// ZW_SUPPORT_TIMER_H