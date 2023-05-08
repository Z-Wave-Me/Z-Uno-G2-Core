#include "Arduino.h"
#include "zuno_gpio.h"

// A = 0
// B = 1
// C = 2
// D = 3
// E = 4
// F = 5
#if ZUNO_PIN_V == 0
// "SDKBOARD" map
#pragma message "ZUNO_PIN_V==0. SDK BOARD"
const PinDef_t ZUNO_PIN_DEFS[] = {
   // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 3},//3 - PF6 - A0 
    {5, 6},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {0, 0},//7 - PF4 - 7
    {0, 1},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {3, 11},//13 - PA0 - PWM1 and ARDURINO LED
    {3, 12},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 13},//18 - PB13 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 11},//20 - PB11 - 20 
    {2, 6},//21 - PC6 - 21
    {0, 5},//22 - PC7 - 22
    {5, 7},//23 - PF7 - BTN
    {2, 7},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 1},//26 - PA1 - USB Serial rx
    {0, 0},//27 - PA0 - USB Serial tx
    {5, 4},//28 - PB15 - green
    {5, 5}//29 - PB14 - red
};

#elif ZUNO_PIN_V == 1
// "NIKBOARD" map
#pragma message "ZUNO_PIN_V==1"
const PinDef_t ZUNO_PIN_DEFS[] = {
    // LEFT SIDE
    {1, 14},  //  0 - B14
    {1, 15}, //  1 - B15
    {2, 6},  //  2 - C6
    {2, 7},  //  3 - C7
    {2, 8},  //  4 - C8
    {2, 9},  //  5 - C9 (UART_USB_RX)
    {2, 10}, //  6 - C10
    {2, 11}, //  7 - C11
    {5, 0},  //  8 - F0 (SCLK)
    {5, 1},  //  9 - F1 (SDIO)
    {5, 2},  // 10 - F2 (SWO)
    {5, 3},  // 11 - F3 (UART_USB_TX)
    {5, 4},  // 12 - F4 (LED)
    {5, 5},  // 13 - F5
    {5, 6},  // 14 - F6
    {5, 7},  // 15 - F7 (BTN)
    // RIGHT SIDE
    {3, 9},  //  16 - D9
    {3, 10}, //  17 - D10
    {3, 11}, //  18 - D11
    {3, 12}, //  19 - D12
    {3, 13}, //  20 - D13
    {3, 14}, //  21 - D14
    {3, 15}, //  22 - D15
    {0, 0},  //  23 - A0 (tX)
    {0, 1},  //  24 - A1 (rX)
    {0, 2},  //  25 - A2 (ADC0)
    {0, 3},  //  26 - A3 
    {0, 4},  //  27 - A4
    {0, 5},  //  28 - A5
    {1, 11}, //  29 - B11 
    {1, 12}, //  30 - B12
    {1, 13}, //  31 - B13
    
};
#elif ZUNO_PIN_V == 2
#pragma message "ZUNO_PIN_V==2"
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
    {0, 0},//11 - PA0
    {0, 1},//12 - PA1
    {0, 2},//13 - PA2 - ARDURINO LED - blue and PWM1
    {0, 3},//14 - PA3 - PWM2
    {0, 4},//15 - PA4 - PWM3 
    {0, 5},//16 - PA5 - PWM4
    {1, 11},//17 - PB11 - 17 
    {1, 12},//18 - PB12 - 18 
    {1, 13},//19 - PB13 - 19 
    {1, 14},//20 - PB14 - 20 
    {1, 15},//21 - PB15 - 21 
    {2, 6},//22 - PC6 - 22 
    {2, 7},//23 - PC7 - BTN
    {2, 11},//24 - PC11 - TX0 
    {5, 3},//25 - PF3 - RX0 
    // DO NOT USE !!!
    {3, 13},//26 - PD13 - USB Serial rx
    {5, 2},//27 - PF2 - USB Serial tx
    {3, 15},//28 - PD15 - green
    {3, 14}//29 - PD14 - red
};
#elif ZUNO_PIN_V == 3
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
#elif ZUNO_PIN_V == 1000
// Rasberi v0
#pragma message "ZUNO_PIN_V==1000"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    {0, 0},//0 - A0 (tX)
    {0, 1},//1 - A1 (rX)
    {2, 7},//2 - PC7 - green
    {2, 8},//3 - PC8 - red
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