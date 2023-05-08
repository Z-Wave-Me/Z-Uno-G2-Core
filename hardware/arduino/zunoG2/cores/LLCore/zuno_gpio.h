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

#define RX0					25
#define TX0					24
#define RX1					8
#define TX1					7
#define RX2					27
#define TX2					26

#define SCK					0
#define MISO				1
#define MOSI				2
#define SS					8
#define SCK2				3
#define MISO2				4
#define MOSI2				7
#define SS2					8

#define BUTTON_PIN			23

#define BATTERY				0xFF

#define HIGH				1
#define LOW					0

#if ZUNO_PIN_V == 3
	#define SCL                 9
	#define SDA                 10
	#define SCL1                2
	#define SDA1                24

	#define LED_BUILTIN         15

	#define ZUNO_PIN_LAST_INDEX	27
#elif ZUNO_PIN_V == 4
	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	27
#elif ZUNO_PIN_V == 6
	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	27
#elif ZUNO_PIN_V == 802
	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	27
#else
	#error ZUNO_PIN_V
#endif


// Universal apport index
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

extern const PinDef_t ZUNO_PIN_DEFS[];

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
inline size_t getRealPort(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].port);};
inline size_t getRealPin(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].pin);};
uint32_t zunoMapPin2EM4Bit(uint8_t em4_pin);
uint32_t zunoMapPin2EM4Int(uint8_t em4_pin);
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch);
inline int digitalRead(uint8_t pin) {return (GPIO_PinInGet((GPIO_Port_TypeDef)getRealPort(pin), getRealPin(pin)));};

#endif//ZUNO_GPIO_H