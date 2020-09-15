#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"
#include "CrtxCore.h"
#include "GpioInterrupt.h"


typedef void (*GPIOINT_IrqCallbackPtr_t)(void);

static GPIOINT_IrqCallbackPtr_t		gpioCallbacks[16] = { 0 };/* Array of user callbacks. One for each pin interrupt number. */
static uint8_t						gInit = false;

static void _IRQDispatcher(uint32_t iflags) {
	uint32_t						irqIdx;
	GPIOINT_IrqCallbackPtr_t		callback;

	/* check for all flags set in IF register */
	while (iflags != 0U) {
		irqIdx = SL_CTZ(iflags);
		iflags &= ~(1 << irqIdx);/* clear flag*/
		callback = gpioCallbacks[irqIdx];
		if (callback != 0)
			callback();/* call user callback */
	}
}

static void _IRQHandlerOdd(void) {
	uint32_t				iflags;

	iflags = GPIO_IntGetEnabled() & 0x0000AAAA;/* Get all odd interrupts. */
	GPIO_IntClear(iflags);/* Clean only odd interrupts. */
	_IRQDispatcher(iflags);
}

static void _IRQHandlerEven(void) {
	uint32_t				iflags;

	iflags = GPIO_IntGetEnabled() & 0x00005555;/* Get all even interrupts. */
	GPIO_IntClear(iflags);/* Clean only odd interrupts. */
	_IRQDispatcher(iflags);
}

static void _CallbackRegister(uint8_t intNo, GPIOINT_IrqCallbackPtr_t callbackPtr) {
	CORE_ATOMIC_SECTION(
		gpioCallbacks[intNo] = callbackPtr;/* Dispatcher is used */
	)
}

void zunoExtIntCallbackRegister(uint8_t interruptPin, void (*userFunc)(void)) {
	_CallbackRegister(getRealPin(interruptPin), userFunc);
}

void attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode) {
	uint8_t						risingEdge;
	uint8_t						fallingEdge;
	uint8_t						port;
	uint8_t						pin;

	if (gInit == false) {
		zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_ODD, (void *)_IRQHandlerOdd);
		zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_EVEN, (void *)_IRQHandlerEven);
		NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
		NVIC_EnableIRQ(GPIO_ODD_IRQn);
		NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
		NVIC_EnableIRQ(GPIO_EVEN_IRQn);
		gInit = true;
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
	_CallbackRegister(pin, userFunc);
	GPIO_ExtIntConfig(port, pin, pin, risingEdge, fallingEdge, true);
}

void zunoExtIntMode(uint8_t interruptPin, uint8_t mode) {
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(interruptPin, gpioCallbacks[getRealPin(interruptPin)], mode);
}

void detachInterrupt(uint8_t interruptPin) {
	uint8_t						pin;

	pin = getRealPin(interruptPin);
	GPIO_IntDisable(pin);
	_CallbackRegister(pin, 0);
}