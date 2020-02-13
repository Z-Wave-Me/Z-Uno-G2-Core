// Arduino.h
#ifndef ZUNO_ARDUINOH
#define ZUNO_ARDUINOH
#include "ZUNO_Definitions.h"
#include "ArduinoTypes.h"
#include <string.h>
#include "binary.h" // to make somebody which doesn't use hexadecimal values happy
#include "CrtxGPIO.h"
#include "HardwareSerial.h"
// #include "Print.h"  // <- Здесь должен быть HardwareSerial

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
    INPUT_PULLDOWN  = GPIOMODE_INPUTPULL
};

#define A0                  14
#define A1                  15
#define A2                  16
#define A3                  17
#define BATTERY             0xFF

// Additional libraries with "pluses"

void * zunoSysCall(int vec, int num, ...);

// prototypes
void delay(dword ms);
dword millis();
void pinMode(uint8_t pin, int mode);
void digitalWrite(uint8_t pin, uint8_t val);
int  digitalRead(uint8_t pin);
int  analogRead(uint8_t pin);
bool analogWrite(uint8_t pin, word value);
void WDOG_Feed();
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
void delayMicroseconds(word tdelay);
uint8_t pin2HWPin(uint8_t pin);
#endif // ZUNO_ARDUINOH