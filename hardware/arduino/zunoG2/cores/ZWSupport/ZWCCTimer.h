#ifndef ZW_SUPPORT_TIMER_H
#define ZW_SUPPORT_TIMER_H

#define ZUNO_TIMER_SWITCH_MAX_VALUE				0x63//Maximum value when dimming
#define ZUNO_TIMER_SWITCH_MIN_VALUE				0x0//The minimum value when dimming
#define ZUNO_TIMER_SWITCH_DEFAULT_DURATION		0x0//The default dimming period is seconds.

#define ZUNO_TIMER_SWITCH_INC					0x1//Indicates what should be up
#define ZUNO_TIMER_SWITCH_DEC					0x2//Indicates what should be down

# define ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL	0x3//How many channels at the same time support for dimming

#ifndef WITH_CC_SWITCH_COLOR
	#undef ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL
	#define ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL		0//To reduce the amount of occupied memory if this channel is not used
#endif

typedef struct					ZunoTimerBasic_s
{
	uint8_t						channel;//Tracked Channel Number + 1
	uint8_t						bMode;//Stores modes
	uint8_t						targetValue;
	uint8_t						currentValue;//Current Dimming Level
	uint32_t					ticksEnd;
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
}								ZunoTimerBasic_t;

typedef struct					ZunoTimerDimmingStart_s
{
	uint8_t						channel;//Tracked Channel Number + 1
	uint8_t						bMode;//Stores modes
}								ZunoTimerDimmingStart_t;

typedef struct					ZunoTimerColorChannel_s {
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
	uint8_t						current_level;//Current Dimming Level
	uint8_t						b_mode;//Stores modes
	uint8_t						channel;//Tracked Channel Number + 1
	uint8_t						colorComponentId;
}								ZunoTimerColorChannel_t;

typedef struct							ZunoTimer_s
{
	uint32_t							ticks;//The number of milliseconds since starting the current program divided by 10
	ZunoTimerBasic_t					s_basic[0x4];
	ZunoTimerColorChannel_t				s_color[ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL];
}										ZunoTimer_t;

extern ZunoTimer_t g_zuno_timer;

void zuno_CCTimer(uint32_t ticks);
void *zuno_CCTimerFind(size_t channel, void *b, void *e, size_t step);
size_t zuno_CCTimerTicksTable7(size_t duration);
ZunoTimerBasic_t *zuno_CCTimerBasicFind(size_t channel);

inline uint8_t zuno_CCTimerTable8(size_t ticks) {
	ticks = ticks / (1000 / ZUNO_SYSTIMER_PERIOD_MC);
	if (ticks <= 0x7F)
		return (ticks);
	ticks = ticks / 60;
	ticks = ticks | (1 << 7);
	return (ticks);
};

#endif// ZW_SUPPORT_TIMER_H