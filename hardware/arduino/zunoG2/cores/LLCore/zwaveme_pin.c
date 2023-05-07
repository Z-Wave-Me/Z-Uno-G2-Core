#include "zwaveme_gpio.h"

#if ZUNO_PIN_V == 3
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
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//0 - A0 (tX)
	{0, 1},//1 - A1 (rX)
	{2, 7},//2 - PC7 - green
	{2, 8},//3 - PC8 - red
};
#else
	#error ZUNO_PIN_V
#endif