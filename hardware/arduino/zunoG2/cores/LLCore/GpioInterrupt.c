#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"
#include "CrtxCore.h"
#include "GpioInterrupt.h"

#define INT_SLEEPING			24// FIXME пин указать реальный для пробуждения

static uint8_t _getPin(uint8_t pin) {
	uint8_t				port;

	if (pin < 8)
		port = (GPIO->EXTIPSELL >> (_GPIO_EXTIPSELL_EXTIPSEL1_SHIFT * pin)) & _GPIO_EXTIPSELL_EXTIPSEL0_MASK;
	else {
	#if defined(_GPIO_EXTIPSELH_MASK)
		port = pin - 8;
		#if defined(_GPIO_EXTIPSELH_EXTIPSEL0_MASK)
			port = (GPIO->EXTIPSELH >> (_GPIO_EXTIPSELH_EXTIPSEL1_SHIFT * port) & _GPIO_EXTIPSELH_EXTIPSEL0_MASK);
		#elif defined(_GPIO_EXTIPSELH_EXTIPSEL8_MASK)
			port = (GPIO->EXTIPSELH >> (_GPIO_EXTIPSELH_EXTIPSEL9_SHIFT * port) & _GPIO_EXTIPSELH_EXTIPSEL8_MASK);
		#else
			#error Invalid GPIO_EXTIPINSELH bit fields
		#endif
	#endif /* #if defined(_GPIO_EXTIPSELH_MASK) */
	}
	return (getPin(port, pin));
}

static void _IRQDispatcher(uint32_t iflags) {
	uint32_t						irqIdx;
	uint32_t						intFlags;

	intFlags = iflags;
	while (iflags != 0U) {/* check for all flags set in IF register */
		irqIdx = SL_CTZ(iflags);
		iflags &= ~(1 << irqIdx);/* clear flag*/
		g_zuno_odhw_cfg.ExtPin = _getPin(irqIdx);
		zunoSysHandlerCall(ZUNO_HANDLER_EXTINT, irqIdx);
	}
	GPIO_IntClear(intFlags);/* Clean interrupts. */
}

static void _IRQHandlerOdd(void) {
	uint32_t				iflags;

	iflags = GPIO_IntGetEnabled() & 0x0000AAAA;/* Get all odd interrupts. */
	_IRQDispatcher(iflags);
}

static void _IRQHandlerEven(void) {
	uint32_t				iflags;

	iflags = GPIO_IntGetEnabled() & 0x00005555;/* Get all even interrupts. */
	_IRQDispatcher(iflags);
}

static inline void _CallbackRegister(uint8_t intNo, void (*userFunc)(void)) {
	zunoAttachSysHandler(ZUNO_HANDLER_EXTINT, intNo, (void *)userFunc);
}

void zunoExtIntCallbackRegister(uint8_t interruptPin, void (*userFunc)(void)) {
	_CallbackRegister(getRealPin(interruptPin), userFunc);
}

void attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode) {
	uint8_t						risingEdge;
	uint8_t						fallingEdge;
	uint8_t						port;
	uint8_t						pin;

	if (interruptPin == INT_SLEEPING)
		return ;
	if (g_bit_field.bExtInit == false) {
		zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_ODD, (void *)_IRQHandlerOdd);
		zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_EVEN, (void *)_IRQHandlerEven);
		NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
		NVIC_EnableIRQ(GPIO_ODD_IRQn);
		NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
		NVIC_EnableIRQ(GPIO_EVEN_IRQn);
		g_bit_field.bExtInit = true;
	}
	switch (mode) {
		case LOW:
			risingEdge = false;
			fallingEdge = false;
			break ;
		case FALLING:
			risingEdge = false;
			fallingEdge = true;
			break ;
		case RISING:
			risingEdge = true;
			fallingEdge = false;
			break ;
		default:
			risingEdge = true;
			fallingEdge = true;
			break ;
	}
	port = getRealPort(interruptPin);
	pin = getRealPin(interruptPin);
	if (userFunc != 0)
		_CallbackRegister(pin, userFunc);
	GPIO_ExtIntConfig(port, pin, pin, risingEdge, fallingEdge, true);
}

void zunoExtIntMode(uint8_t interruptPin, uint8_t mode) {
	if (interruptPin == INT_SLEEPING)
		return ;
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(interruptPin, 0, mode);
}

void detachInterrupt(uint8_t interruptPin) {
	uint8_t						pin;

	pin = getRealPin(interruptPin);
	GPIO_IntDisable(pin);
	zunoDetachSysHandlerAllSubType(ZUNO_HANDLER_EXTINT, pin);
}