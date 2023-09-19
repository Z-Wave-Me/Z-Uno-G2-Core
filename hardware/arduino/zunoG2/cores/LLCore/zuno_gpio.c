#include "Arduino.h"
#include "zuno_gpio.h"

#if ZUNO_PIN_V == 3
#pragma message "ZUNO_PIN_V==3"
#elif ZUNO_PIN_V == 4
#pragma message "ZUNO_PIN_V==4"
#elif ZUNO_PIN_V == 6
#pragma message "ZUNO_PIN_V==6"
#elif ZUNO_PIN_V == 800
#pragma message "ZUNO_PIN_V==800 (SDK BRD4210A)"
#elif ZUNO_PIN_V == 802
#pragma message "ZUNO_PIN_V==802 (SDK BRD4205B)"
#elif ZUNO_PIN_V == 803
#pragma message "ZUNO_PIN_V==803 (RYSE BRD)"
#elif ZUNO_PIN_V == 804
#pragma message "ZUNO_PIN_V==804 (ZGM8202 BRD)"
#else
    #error ZUNO_PIN_V
#endif



/* pin */
void pinMode(uint8_t pin, int mode){
    GPIO_PinModeSet((GPIO_Port_TypeDef)getRealPort(pin), getRealPin(pin), (GPIO_Mode_TypeDef)(mode & 0x0F), ((mode & 0x100) != 0) ? true : false);
}

uint8_t pin2HWPin(uint8_t pin) {
    return ((ZUNO_PIN_DEFS[pin].port << 4) | (ZUNO_PIN_DEFS[pin].pin));
}

void digitalWrite(uint8_t pin, uint8_t mode) {
    uint8_t						real_port;
    uint8_t						real_pin;

    real_port = getRealPort(pin);
    real_pin = getRealPin(pin);
    if (mode == true)
        GPIO_PinOutSet((GPIO_Port_TypeDef)real_port, real_pin);
    else
        GPIO_PinOutClear((GPIO_Port_TypeDef)real_port, real_pin);
}
void digitalToggle(uint8_t pin) {
   uint8_t real_port;
   uint8_t real_pin;
   real_port = getRealPort(pin);
   real_pin = getRealPin(pin);
   GPIO_PinOutToggle((GPIO_Port_TypeDef)real_port, real_pin);
}
uint8_t getPin(uint8_t port, uint8_t pin) {
    const PinDef_t			*lp_b;
    const PinDef_t			*lp_e;

    lp_b = &ZUNO_PIN_DEFS[0];
    lp_e = &ZUNO_PIN_DEFS[sizeof(ZUNO_PIN_DEFS) / sizeof(PinDef_t)];
    while (lp_b < lp_e) {
        if (lp_b->port == port && lp_b->pin == pin)
            return (lp_b - &ZUNO_PIN_DEFS[0]);
        lp_b++;
    }
    return (INVALID_PIN_INDEX);
}

uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin) {
    size_t				i;

    i = 0;
    pin = (getRealPort(pin) << 4) | getRealPin(pin);
    while (i < count) {
        if (location[i] == pin)
            return (i);
        i++;
    }
    return 0xFF;
}

size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch) {
    size_t				loc;

    loc = getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), pin);
    loc = (loc + 32 - ch) & 0x1F;
    ch <<= 3;
    return (loc << ch);
}

size_t getRealPort(uint8_t pin) {
	return(ZUNO_PIN_DEFS[pin].port);
}

size_t getRealPin(uint8_t pin) {
	return(ZUNO_PIN_DEFS[pin].pin);
}

int digitalRead(uint8_t pin) {
	return (GPIO_PinInGet((GPIO_Port_TypeDef)getRealPort(pin), getRealPin(pin)));
}