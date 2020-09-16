#ifndef GPIO_INTERRPUT_H
#define GPIO_INTERRPUT_H

//ExtInt
void attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t interruptPin);
void zunoExtIntMode(uint8_t interruptPin, uint8_t mode);
void zunoExtIntCallbackRegister(uint8_t interruptPin, void (*userFunc)(void));

enum {
	CHANGE = LOW + 1,
	FALLING,
	RISING,
};

#define ZUNO_EXT_ZEROX				ZEROX
#define ZUNO_EXT_INT0				INT0
#define ZUNO_EXT_INT1				INT1


#define ZUNO_SETUP_ISR_ZEROX(FUNCTION_NAME)		zunoExtIntCallbackRegister(ZUNO_EXT_ZEROX, FUNCTION_NAME)
#define ZUNO_SETUP_ISR_INT0(FUNCTION_NAME)		zunoExtIntCallbackRegister(ZUNO_EXT_INT0, FUNCTION_NAME)
#define ZUNO_SETUP_ISR_INT1(FUNCTION_NAME)		zunoExtIntCallbackRegister(ZUNO_EXT_INT1, FUNCTION_NAME)


#endif // GPIO_INTERRPUT_H