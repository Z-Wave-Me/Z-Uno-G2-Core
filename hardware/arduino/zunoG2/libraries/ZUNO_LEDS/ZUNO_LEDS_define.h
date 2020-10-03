#ifndef ZUNO_LEDS_DEFINE_H
#define ZUNO_LEDS_DEFINE_H

typedef struct							ZunoLedMode_s
{
	uint8_t								divider;
	uint32_t							pattern;
}										ZunoLedMode_t;

typedef struct							ZunoLedModeGroups_s
{
	const ZunoLedMode_t					*led_modes;
	uint8_t								led_pin;
	uint8_t								bInverted;
}										ZunoLedModeGroups_t;


#endif //ZUNO_LEDS_DEFINE_H