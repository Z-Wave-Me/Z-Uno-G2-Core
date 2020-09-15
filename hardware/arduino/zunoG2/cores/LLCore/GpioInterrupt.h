#ifndef GPIO_INTERRPUT_H
#define GPIO_INTERRPUT_H

//ExtInt
void attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t interruptPin);

enum {
	CHANGE = LOW + 1,
	FALLING,
	RISING,
};

#endif // GPIO_INTERRPUT_H