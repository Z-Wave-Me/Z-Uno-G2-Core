#ifndef ZUNO_LEDS_H
#define ZUNO_LEDS_H

#include "ZUNO_LEDS_define.h"

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
};


extern ZunoLed Led;

#endif //ZUNO_LEDS_H