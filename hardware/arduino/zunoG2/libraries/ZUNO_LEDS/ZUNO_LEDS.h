#ifndef ZUNO_LEDS_H
#define ZUNO_LEDS_H

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
		inline ZunoError_t				addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes) {return (this->addLed(led_pin, led_modes, num_modes, false));};
		ZunoError_t						addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes, uint8_t bInverted);
		ZunoError_t						addLed(const ZunoLedModeGroups_t *led_groups, uint8_t num_groups, uint8_t num_modes);
		inline void						deleteLed(uint8_t led_pins) {this->_deleteLed(led_pins);};
		inline void						deleteLed(const ZunoLedModeGroups_t *led_groups) {this->_deleteLed((size_t)led_groups);};
		inline void						setMode(uint8_t led_pin, uint8_t mode) {this->_setMode(led_pin, mode);};
		inline void						setMode(const ZunoLedModeGroups_t *led_groups, uint8_t mode) {this->_setMode((size_t)led_groups, mode);};
		inline void						off(uint8_t led_pin) {this->_setLed(led_pin, LED_MODE_ALWAYS_OFF);};
		inline void						off(const ZunoLedModeGroups_t *led_groups) {this->_setLed((size_t)led_groups, LED_MODE_ALWAYS_OFF);};
		inline void						on(uint8_t led_pin) {this->_setLed(led_pin, LED_MODE_ALWAYS_ON);};
		inline void						on(const ZunoLedModeGroups_t *led_groups) {this->_setLed((size_t)led_groups, LED_MODE_ALWAYS_ON);};

	private:
		void								_deleteLed(size_t name);
		void								_setMode(size_t name, uint8_t mode);
		void								_setLed(size_t name, uint8_t mode);
		inline ZunoLedListGroups_t			*_addLedPre(size_t name, uint8_t num_groups, ZunoError_t *ret);
		inline ZunoLedListGroups_t			*_findList(size_t name);
		inline void							_addList(ZunoLedListGroups_t *list);
		static void							_updateTimer(void);
		static ZunoLedListGroups_t			*_list;
		static volatile uint8_t				bSysTimerInit;
};


extern ZunoLed Led;

#endif //ZUNO_LEDS_H