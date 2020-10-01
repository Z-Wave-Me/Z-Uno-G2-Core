#ifndef ZUNO_LEDS_H
#define ZUNO_LEDS_H

#define LED_MODE_ALWAYS_OFF 0
#define LED_MODE_ALWAYS_ON  1

typedef struct							ZunoLedMode_s
{
	uint8_t								divider;
	uint32_t							pattern;
}										ZunoLedMode_t;

typedef struct							ZunoLedModeGroups_s
{
	ZunoLedMode_t						mode;
	uint8_t								pin;
}										ZunoLedModeGroups_t;

typedef struct							ZunoLedList_s
{
	ZunoLedMode_t						mode;
	uint8_t								pin;
}										ZunoLedList_t;

typedef struct							ZunoLedListGroups_s
{
	struct ZunoLedListGroups_s			*next;
	size_t								name;//pin or lp ZunoLedModeGroups_t
	uint8_t								num_groups;
	uint8_t								num_modes;
	ZunoLedList_t						array[];
}										ZunoLedListGroups_t;

class ZunoLed {
	public:
		ZunoLed(void);
		ZunoError_t				addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes);
		ZunoError_t				addLed(const ZunoLedModeGroups_t *led_groups, uint8_t num_groups, uint8_t num_modes);

	private:
		ZunoLedListGroups_t		*_findList(size_t name);
		static void				_updateTimer(void);
		ZunoLedListGroups_t		*list;
		uint8_t					bSysTimerInit;
};

#endif //ZUNO_LEDS_H