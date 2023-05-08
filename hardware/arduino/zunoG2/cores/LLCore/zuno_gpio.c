#include "Arduino.h"
#include "zuno_gpio.h"

// A = 0
// B = 1
// C = 2
// D = 3
// E = 4
// F = 5
#if ZUNO_PIN_V == 3
#pragma message "ZUNO_PIN_V==3"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {2, 10},//2 - PC10 - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1  
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3 and ARDURINO LED
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {0, 5},//18 - PA5 - 18
    {1, 11},//19 - PB11 - 19 
    {1, 12},//20 - PB12 - 20 
    {1, 13},//21 - PB13 - 21 
    {1, 14},//22 - PB14 - 22 
    {2, 7},//23 - PC7 - BTN
    {2, 11},//24 - PC11 - TX0
    {3, 13},//25 - PD13 - RX0
    // DO NOT USE !!!
    {5, 2},//26 - PF2 - USB Serial tx
    {5, 3},//27 - PF3 - USB Serial rx
    {2, 6},//28 - PC6 - green
    {1, 15}//29 - PB15 - red
};
#elif ZUNO_PIN_V == 4
#pragma message "ZUNO_PIN_V==4"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1 and ARDURINO LED
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 11},//18 - PB11 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 13},//20 - PB13 - 20 
    {2, 6},//21 - PC6 - 21
    {2, 7},//22 - PC7 - 22
    {2, 10},//23 - PC10 - BTN
    {3, 13},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 5},//26 - PA5 - USB Serial rx
    {5, 3},//27 - PF3 - USB Serial tx
    {1, 15},//28 - PB15 - green
    {1, 14}//29 - PB14 - red
};
#elif ZUNO_PIN_V == 6
#pragma message "ZUNO_PIN_V==6"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1 and ARDURINO LED
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 13},//18 - PB13 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 11},//20 - PB11 - 20 
    {2, 6},//21 - PC6 - 21
    {2, 7},//22 - PC7 - 22
    {2, 10},//23 - PC10 - BTN
    {3, 13},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 5},//26 - PA5 - USB Serial rx
    {5, 3},//27 - PF3 - USB Serial tx
    {1, 15},//28 - PB15 - green
    {1, 14}//29 - PB14 - red
};
#elif ZUNO_PIN_V == 802
#pragma message "ZUNO_PIN_V==802"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 5},//05 - PA05
	{0, 6},//06 - PA06
	{0, 7},//07 - PA07
	{0, 8},//08 - PA08
	{0, 9},//09 - PA09
	{0,10},//10 - PA10
	{1, 0},//11 - PB00
	{2, 5},//12 - PC05
	{3, 0},//13 - PD00
	{1, 3},//14 - PB03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{2, 0},//18 - PC00
	{2, 6},//19 - PC06
	{2, 2},//20 - PC02
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{1, 1},//23 - PB01 - button_pin
	{2, 1},//24 - PC01 - TX0
	{3, 2},//25 - PD02 - RX0
	{2, 8},//26 - PC08
	{2, 9},//27 - PC09
	{1, 2},//28 - PB02 - led1_pin
	{3, 3},//29 - PD03 - led2_pin
};
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