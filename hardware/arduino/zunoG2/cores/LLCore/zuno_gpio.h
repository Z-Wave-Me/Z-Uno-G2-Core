#ifndef ZUNO_GPIO_H
#define ZUNO_GPIO_H

#include "em_gpio.h"

#ifndef ZUNO_PIN_V
	#define ZUNO_PIN_V			6//default
#endif

#define PWM1				13
#define PWM2				14
#define PWM3				15
#define PWM4				16

#define A0					3
#define A1					4
#define A2					5
#define A3					6

#ifndef RX0 
	#define RX0 25
#endif
#ifndef TX0 
	#define TX0 24
#endif
#ifndef RX1 
	#define RX1 8
#endif
#ifndef TX1 
	#define TX1 7
#endif
#ifndef RX2 
	#define RX2 27
#endif
#ifndef TX2 
	#define TX2 26
#endif

#define SCK					0
#define MISO				1
#define MOSI				2
#define SS					8
#define SCK2				3
#define MISO2				4
#define MOSI2				7
#define SS2					8
#define BATTERY				0xFF
#define HIGH				1
#define LOW					0
#if ZUNO_PIN_V == 0
	#ifndef SCL1
	#define SCL1 23
	#endif
	#ifndef SDA1 
	#define SDA1 25
	#endif
#elif ZUNO_PIN_V == 6 || ZUNO_PIN_V == 0x704 || ZUNO_PIN_V == 0x707 || ZUNO_PIN_V == 0x708
	#define SCL1                23
	#define SDA1                25
#elif ZUNO_PIN_V == 0x701
	#define SCL                 0
	#define SDA                 1
	#define SCL1                23
	#define SDA1                25
#elif ZUNO_PIN_V == 0x802 || ZUNO_PIN_V == 0x803  || ZUNO_PIN_V == 0x800 || ZUNO_PIN_V == 0x801 || ZUNO_PIN_V == 0x804  || ZUNO_PIN_V == 0x805 || ZUNO_PIN_V == 0x810 || ZUNO_PIN_V == 0x811 
	#define SCL1                23
	#define SDA1                25
#else
	#error ZUNO_PIN_V
#endif
#ifndef BUTTON_PIN 
#define BUTTON_PIN          23
#endif
#ifndef ZUNO_PIN_LAST_INDEX 
#define ZUNO_PIN_LAST_INDEX 29
#endif
#ifndef LED_BUILTIN 
#define LED_BUILTIN      13
#endif
#ifndef SCL 
#define SCL 9
#endif
#ifndef SDA 
#define SDA 10
#endif

#if ZUNO_PIN_V == 0x804 || ZUNO_PIN_V == 0x810 || ZUNO_PIN_V == 0x811
	#define SYS_LED_INVERT						true
#else
	#define SYS_LED_INVERT						false
#endif

// Universal aport index
const uint8_t g_aport_pa0_pf7_all[] = {//APORT3Y APORT3X APORT1Y APORT1X
		0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,//PA0-PA5 - CH8-CH13 - APORT3
		0x7B, 0x7C, 0x7D, 0x7E, 0x7F,//PB11-PB15 - CH27-CH31 - APORT3
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, //PC6-PC11 - CH6-CH11 - APORT1
		0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, //PD9-PD15 - CH1-CH7 - APORT3
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37//PF0-PF7 - CH16-CH23 - APORT1
	};

// Universal pin location index
const uint8_t g_loc_pa0_pf7_all[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
		0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
		0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
	};
const uint8_t g_loc_pa0_pf7_all_size = sizeof(g_loc_pa0_pf7_all);

// Usable for USART2
const uint8_t g_loc_pa5_pf0_pf1_pf3_pf7[] = {
	    0x05,                                	   // LOC0
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // LOC1-13 is deprecated
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
		0x50, 0x51, 0x53, 0x54, 0x55, 0x56, 0x57	//PF0=LOC14,PF1=LOC15,PF3-PF7 (LOC16-LOC20)
};
#define MAX_VALID_PINLOCATION 31
#define INVALID_PIN_INDEX 0xFF
typedef struct	PinDef_s
{
	uint8_t		port;
	uint8_t		pin;
}				PinDef_t;

// A = 0
// B = 1
// C = 2
// D = 3
// E = 4
// F = 5
#if ZUNO_PIN_V == 0
// User-defined pin mapping
extern const PinDef_t ZUNO_PIN_DEFS[];
#elif ZUNO_PIN_V == 6 || ZUNO_PIN_V == 0x704 || ZUNO_PIN_V == 0x707 || ZUNO_PIN_V == 0x708
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
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
#elif ZUNO_PIN_V == 0x701
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PCF2  - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 2},//7 - PF2 - 7
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
    {2, 7},//24 - PC7 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {5, 4},//26 - PF4 - USB Serial rx
    {5, 3},//27 - PF3 - USB Serial tx
    {3, 11},//28 - PD12 - green
    {3, 12}//29 - PD11 - red
};
#elif ZUNO_PIN_V == 0x800
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 5},//05 - PA05
	{2, 8},//06 - PC08
	{2, 2},//07 - PC02 - TX1
	{2, 9},//08 - PC09 - RX1
	{0, 6},//09 - PA06
	{0,10},//10 - PA10
	{1, 0},//11 - PB00
	{2, 5},//12 - PC05
	{0, 7},//13 - PB02
	{1, 3},//14 - PB03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{2, 0},//18 - PC00
	{2, 6},//19 - PC06
	{0, 8},//20 - PA08
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{1, 1},//23 - PB01 - button_pin
	{2, 1},//24 - PC01 - TX0
	{3, 2},//25 - PD02 - RX0
	{0, 8},//26 - PA08 - sapi_tx_pin
	{0, 9},//27 - PA09 - sapi_rx_pin
	{1, 2},//28 - PB02 - led1_pin
	{3, 3},//29 - PD03 - led2_pin
};
#elif ZUNO_PIN_V == 0x801
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 8},//05 - PA08
	{2, 8},//06 - PC08
	{2, 2},//07 - PC02 - TX1
	{2, 9},//08 - PC09 - RX1
	{0, 6},//09 - PA06
	{0,10},//10 - PA10
	{1, 0},//11 - PB00
	{2, 5},//12 - PC05
	{0, 7},//13 - PB02
	{1, 3},//14 - PB03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{2, 0},//18 - PC00
	{2, 6},//19 - PC06
	{0, 8},//20 - PA08
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{1, 1},//23 - PB01 - button_pin
	{2, 1},//24 - PC01 - TX0
	{3, 2},//25 - PD02 - RX0
	{0, 5},//26 - PA05 - sapi_tx_pin
	{0, 0},//27 - PA00 - sapi_rx_pin
	{1, 2},//28 - PB02 - led1_pin
	{3, 3},//29 - PD03 - led2_pin
};
#elif ZUNO_PIN_V == 0x802
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 5},//05 - PA05
	{2, 8},//06 - PC08
	{2, 2},//07 - PC02 - TX1
	{2, 9},//08 - PC09 - RX1
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
	{0, 8},//20 - PA08
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{1, 1},//23 - PB01 - button_pin
	{2, 1},//24 - PC01 - TX0
	{3, 2},//25 - PD02 - RX0
	{0, 6},//26 - PA06 - sapi_tx_pin
	{0, 7},//27 - PA07 - sapi_rx_pin
	{1, 2},//28 - PB02 - led1_pin
	{3, 3},//29 - PD03 - led2_pin
};
#elif ZUNO_PIN_V == 0x803
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 5},//05 - PA05
	{2, 8},//06 - PC08
	{0, 9},//07 - PA09 - TX1
	{0, 8},//08 - PA08 - RX1
	{2, 9},//09 - PC09
	{0,10},//10 - PA10
	{2, 1},//11 - PC01
	{2, 5},//12 - PC05
	{0, 6},//13 - PA06
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
	{1, 0},//24 - PB00 - TX0
	{3, 2},//25 - PD02 - RX0
	{3, 0},//26 - PD00 - sapi_tx_pin
	{3, 1},//27 - PD01 - sapi_rx_pin
	{1, 2},//28 - PB02 - led1_pin
	{3, 3},//29 - PD03 - led2_pin
};
#elif ZUNO_PIN_V == 0x804 // ZGM8202 board
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//00 - PA00
	{0, 1},//01 - PA01
	{0, 2},//02 - PA02
	{0, 3},//03 - PA03
	{0, 4},//04 - PA04
	{0, 5},//05 - PA05
	{2, 8},//06 - PC08
	{0, 9},//07 - PA09 - TX1
	{0, 8},//08 - PA08 - RX1
	{2, 9},//09 - PC09
	{0,10},//10 - PA10
	{2, 1},//11 - PC01
	{2, 5},//12 - PC05
	{0, 0},//13 - PA00
	{0, 3},//14 - PA03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{2, 0},//18 - PC00
	{2, 6},//19 - PC06
	{2, 2},//20 - PC02
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{0, 5},//23 - PA05 - button_pin
	{1, 1},//24 - PB01 - TX0
	{1, 2},//25 - PB02 - RX0
	{2, 0},//26 - PC00 - sapi_tx_pin
	{2, 5},//27 - PC05 - sapi_rx_pin
	{0, 4},//28 - PA04 - led1_pin
	{0, 6},//29 - PA06 - led2_pin
};
#elif ZUNO_PIN_V == 0x805 // Z-Uno based on 8th gen. chips
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{3, 2},//00 - PD02
	{3, 1},//01 - PD01
	{2, 1},//02 - PC01
	{2, 4},//03 - PC04
	{2, 5},//04 - PC05
	{2, 6},//05 - PC06
	{2, 7},//06 - PC07
	{2, 8},//07 - PC08 - TX1
	{2, 9},//08 - PC09 - RX1
	{1, 6},//09 - PB06
	{1, 3},//10 - PB03
	{1, 2},//11 - PB02
	{1, 1},//12 - PB01
	{1, 0},//13 - PB00
	{0, 0},//14 - PA00
	{0, 4},//15 - PA04
	{0, 5},//16 - PA05
	{0, 6},//17 - PA06
	{0, 7},//18 - PA07
	{3, 5},//19 - PD05
	{0, 3},//20 - PA03
	{3, 4},//21 - PD04
	{3, 3},//22 - PD03
	{3, 0},//23 - PD00 - button_pin
	{1, 4},//24 - PB04 - TX0
	{1, 5},//25 - PB05 - RX0
	{2, 2},//26 - PC02 - sapi_tx_pin
	{2, 3},//27 - PC03 - sapi_rx_pin
	{0,8},//28 - PA08 - led1_pin
	{0,10},//29 - PA10 - led2_pin
};
#elif ZUNO_PIN_V == 0x810
// Wave Plug
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{2, 0},//00 - PC00
	{2, 1},//01 - PC01
	{2, 2},//02 - PC02
	{3, 0},//03 - PD00
	{3, 3},//04 - PD03
	{0, 5},//05 - PA05
	{2, 4},//06 - PC04
	{0, 9},//07 - PA09 - TX1
	{0, 8},//08 - PA08 - RX1
	{2, 9},//09 - PC09
	{0,10},//10 - PA10
	{3, 3},//11 - PD03
	{2, 5},//12 - PC05
	{0, 0},//13 - PB01
	{1, 3},//14 - PB03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{3, 1},//18 - PD01
	{2, 6},//19 - PC06
	{2, 2},//20 - PC02
	{2, 3},//21 - PC03
	{2, 4},//22 - PC04
	{3, 2},//23 - PD02 - button_pin
	{0, 3},//24 - PA03 - TX0
	{0, 4},//25 - PA04 - RX0
	{0, 2},//26 - PA2 - sapi_tx_pin
	{0, 1},//27 - PA1 - sapi_rx_pin
	{1, 0},//28 - PB00 - led1_pin
	{1, 1},//29 - PB01 - led2_pin
};
#elif ZUNO_PIN_V == 0x811
// Wave1
constexpr PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{2, 0},//00 - PC00
	{2, 1},//01 - PC01
	{2, 2},//02 - PC02
	{3, 0},//03 - PD00
	{0, 6},//04 - PA06
	{0, 5},//05 - PA05
	{2, 4},//06 - PC04
	{0, 9},//07 - PA09 - TX1
	{0, 8},//08 - PA08 - RX1
	{2, 9},//09 - PC09
	{0,10},//10 - PA10
	{2, 1},//11 - PC01
	{2, 5},//12 - PC05
	{1, 1},//13 - PB01
	{1, 3},//14 - PB03
	{1, 4},//15 - PB04
	{1, 5},//16 - PB05
	{1, 6},//17 - PB06
	{2, 0},//18 - PC00
	{2, 6},//19 - PC06
	{2, 2},//20 - PC02
	{3, 3},//21 - PD03
	{0, 4},//22 - PA04
	{2, 3},//23 - PC03 - button_pin
	{0, 3},//24 - PA03 - TX0
	{0, 9},//25 - PA09 - RX0
	{0, 2},//26 - PA2 - sapi_tx_pin
	{0, 1},//27 - PA1 - sapi_rx_pin
	{1, 0},//28 - PB00 - led1_pin
	{0, 0},//29 - PA00 - led2_pin
};
#else
    #error ZUNO_PIN_V
#endif

typedef enum {
  /** Input disabled. Pullup if DOUT is set. */
  GPIOMODE_DISABLED                  = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set */
  GPIOMODE_INPUT                     = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction */
  GPIOMODE_INPUTPULL                 = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction */
  GPIOMODE_INPUTPULLFILTER           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output */
  GPIOMODE_OUTPUT_PUSHPULL           = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Wired-or output */
  GPIOMODE_OUTPUT_WIREDOR              = _GPIO_P_MODEL_MODE0_WIREDOR,
  /** Wired-or output with pull-down */
  GPIOMODE_OUTPUT_WIREDORPD             = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output */
  GPIOMODE_OUTPUT_OPENDRAIN             = _GPIO_P_MODEL_MODE0_WIREDAND,
  /** Open-drain output with filter */
  GPIOMODE_OUTPUT_OPENDRAINFLT          = _GPIO_P_MODEL_MODE0_WIREDANDFILTER,
  /** Open-drain output with pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUP           = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output with filter and pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUPFLT        = _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER,
} GPIO_Mode_t;

enum{
    DISABLED = GPIOMODE_DISABLED,
    OUTPUT = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT = GPIOMODE_INPUT,
    INPUT_PULLUP    = 0x100 | GPIOMODE_INPUTPULL,
    INPUT_PULLDOWN  = GPIOMODE_INPUTPULL,
	INPUT_PULLUP_FILTER = 0x100 | GPIOMODE_INPUTPULLFILTER,
	INPUT_PULLDOWN_FILTER = GPIOMODE_INPUTPULLFILTER,
    OUTPUT_UP = 0x100 | GPIOMODE_OUTPUT_PUSHPULL,
    OUTPUT_DOWN = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT_UP = 0x100 | GPIOMODE_INPUT,
    INPUT_DOWN = GPIOMODE_INPUT
};

void pinMode(uint8_t pin, int mode);
uint8_t pin2HWPin(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
void digitalToggle(uint8_t pin);
uint8_t getPin(uint8_t port, uint8_t pin);
size_t getRealPort(uint8_t pin);
size_t getRealPin(uint8_t pin);
uint32_t zunoMapPin2EM4Bit(uint8_t em4_pin);
uint32_t zunoMapPin2EM4Int(uint8_t em4_pin);
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch);
int digitalRead(uint8_t pin);

#endif//ZUNO_GPIO_H