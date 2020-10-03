#ifndef ZUNO_LEDS_PRIVATE_H
#define ZUNO_LEDS_PRIVATE_H

#include "ZUNO_LEDS_define.h"

#define LED_MODE_ALWAYS_OFF				0
#define LED_MODE_ALWAYS_ON				1
#define LED_MODE_OFFSET					2

typedef struct							ZunoLedList_s
{
	const ZunoLedMode_t					*led_modes;
	uint8_t								led_pin;
	uint8_t								bInverted;
}										ZunoLedList_t;

typedef struct							ZunoLedListGroups_s
{
	struct ZunoLedListGroups_s			*next;
	size_t								name;//pin or lp ZunoLedModeGroups_t
	uint8_t								num_groups;
	uint8_t								num_modes;
	uint8_t								current_mode;
	uint8_t								patt_index;
	ZunoLedList_t						array[];
}										ZunoLedListGroups_t;

class ZunoLed {
	public:
		ZunoLed(void);
		ZunoError_t				addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes);
		ZunoError_t				addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes, uint8_t bInverted);
		ZunoError_t				addLed(const ZunoLedModeGroups_t *led_groups, uint8_t num_groups, uint8_t num_modes);
		void					deleteLed(uint8_t led_pins);
		void					deleteLed(const ZunoLedModeGroups_t *led_groups);
		void					setMode(uint8_t led_pin, uint8_t mode);
		void					setMode(const ZunoLedModeGroups_t *led_groups, uint8_t mode);
		void					off(uint8_t led_pin);
		void					off(const ZunoLedModeGroups_t *led_groups);
		void					on(uint8_t led_pin);
		void					on(const ZunoLedModeGroups_t *led_groups);

	private:
		void					_deleteLed(size_t name);
		void					_setMode(size_t name, uint8_t mode);
		void					_setLed(size_t name, uint8_t mode);
		ZunoLedListGroups_t		*_addLedPre(size_t name, uint8_t num_groups, ZunoError_t *ret);
		ZunoLedListGroups_t		*_findList(size_t name);
		void					_addList(ZunoLedListGroups_t *list);
		static void				_updateTimer(void);
		ZunoLedListGroups_t		*list;
		volatile uint8_t		bSysTimerInit;
};


extern ZunoLed Led;

#endif //ZUNO_LEDS_PRIVATE_H