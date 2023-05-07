#ifndef ZWAVEME_GPIO_H
#define ZWAVEME_GPIO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BATTERY							0xFF
#define HIGH							1
#define LOW								0

// Universal apport index
extern const uint8_t g_aport_pa0_pf7_all[32];

// Universal pin location index
extern const uint8_t g_loc_pa0_pf7_all[32];

// Usable for USART2
extern const uint8_t g_loc_pa5_pf0_pf1_pf3_pf7[21];

typedef struct	PinDef_s
{
	uint8_t		port;
	uint8_t		pin;
}				PinDef_t;

#define DISABLED						_GPIO_P_MODEL_MODE0_DISABLED
#define OUTPUT							_GPIO_P_MODEL_MODE0_PUSHPULL
#define INPUT							_GPIO_P_MODEL_MODE0_INPUT
#define INPUT_PULLUP					0x100 | _GPIO_P_MODEL_MODE0_INPUTPULL
#define INPUT_PULLDOWN 					_GPIO_P_MODEL_MODE0_INPUTPULL
#define INPUT_PULLUP_FILTER				0x100 | _GPIO_P_MODEL_MODE0_INPUTPULLFILTER
#define INPUT_PULLDOWN_FILTER			_GPIO_P_MODEL_MODE0_INPUTPULLFILTER
#define OUTPUT_UP						0x100 | _GPIO_P_MODEL_MODE0_PUSHPULL
#define OUTPUT_DOWN						_GPIO_P_MODEL_MODE0_PUSHPULL
#define INPUT_UP						0x100 | _GPIO_P_MODEL_MODE0_INPUT
#define INPUT_DOWN						_GPIO_P_MODEL_MODE0_INPUT

#define UNKNOWN_PIN						0xFF
#define MAX_VALID_PINLOCATION			31

static inline uint8_t getRealPort(uint8_t pin) {extern const PinDef_t ZUNO_PIN_DEFS[]; return(ZUNO_PIN_DEFS[pin].port);};
static inline uint8_t getRealPin(uint8_t pin) {extern const PinDef_t ZUNO_PIN_DEFS[]; return(ZUNO_PIN_DEFS[pin].pin);};
void pinMode(uint8_t pin, int mode);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
int digitalRead(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_GPIO_H