#include "Arduino.h"
#include "zuno_gpio.h"

#if ZUNO_PIN_V == 0 
#pragma message "ZUNO_PIN_V==0. Custom pinmapping. You have to define PinDef_t ZUNO_PIN_DEFS[] yourself!"
#elif ZUNO_PIN_V == 6 || ZUNO_PIN_V == 0x704
#pragma message "ZUNO_PIN_V==0x704"
#elif ZUNO_PIN_V == 0x701
#pragma message "ZUNO_PIN_V==0x701. u-fairy.com module"
#elif ZUNO_PIN_V == 0x800
#pragma message "ZUNO_PIN_V==0x800 (SDK BRD4210A)"
#elif ZUNO_PIN_V == 0x801
#pragma message "ZUNO_PIN_V==0x800 (SDK BRD4210A+EXT_NVM)"
#elif ZUNO_PIN_V == 0x802
#pragma message "ZUNO_PIN_V==0x802 (SDK BRD4205B)"
#elif ZUNO_PIN_V == 0x803
#pragma message "ZUNO_PIN_V==0x803 (RYSE BRD)"
#elif ZUNO_PIN_V == 0x804
#pragma message "ZUNO_PIN_V==0x804 (ZGM8202 BRD)"
#elif ZUNO_PIN_V == 0x805
#pragma message "ZUNO_PIN_V==0x805 (Z-Uno3 R1 )"
#elif ZUNO_PIN_V == 0x810
#pragma message "ZUNO_PIN_V==0x810 (Wave Plug )"
#elif ZUNO_PIN_V == 0x811
#pragma message "ZUNO_PIN_V==0x811 (Wave1 )"
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
    for(int i=0; i<=ZUNO_PIN_LAST_INDEX; i++){
        if((ZUNO_PIN_DEFS[i].port == port) &&
           (ZUNO_PIN_DEFS[i].pin == pin))
           return i;
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