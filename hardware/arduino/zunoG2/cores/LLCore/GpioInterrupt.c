#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"
#include "GpioInterrupt.h"

#define INT_SLEEPING			24// FIXME пин указать реальный для пробуждения

static uint8_t _getPort(uint8_t pin) {
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
	return (port);
}

static void _IRQDispatcher(void * p) {
	uint32_t						irqIdx;
	uint32_t iflags = (uint32_t)p;
	while (iflags != 0U) {/* check for all flags set in IF register */
		irqIdx = SL_CTZ(iflags);
		iflags &= ~(1 << irqIdx);/* clear flag*/
		zunoSysHandlerCall(ZUNO_HANDLER_EXTINT, irqIdx, getPin(_getPort(irqIdx), irqIdx));
	}
}
static inline ZunoError_t _CallbackRegister(uint8_t intNo, void (*userFunc)(void)) {
	return (zunoAttachSysHandler(ZUNO_HANDLER_EXTINT, intNo, (void *)userFunc));
}

void zunoExtIntCallbackRegister(uint8_t interruptPin, void (*userFunc)(void)) {
	zunoEnterCritical();
	_CallbackRegister(getRealPin(interruptPin), userFunc);
	zunoExitCritical();
}

static inline ZunoError_t _attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode) {
	ZunoError_t					ret;
	uint8_t						risingEdge;
	uint8_t						fallingEdge;
	uint8_t						port;
	uint8_t						pin;

	if (interruptPin == INT_SLEEPING)
		return (ZunoErrorExtInt);
	if (g_zuno_odhw_cfg.bExtInit == false) {
		if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_ODD, (void *)_IRQDispatcher)) != ZunoErrorOk) {
			return (ret);
		}
		if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_EVEN, (void *)_IRQDispatcher)) != ZunoErrorOk) {
			zunoDetachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_GPIO_ODD, (void *)_IRQDispatcher);
			return (ret);
		}
		NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
		NVIC_EnableIRQ(GPIO_ODD_IRQn);
		NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
		NVIC_EnableIRQ(GPIO_EVEN_IRQn);
		g_zuno_odhw_cfg.bExtInit = true;
	}
	zunoExitCritical();
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
	zunoEnterCritical();
	if ((GPIO->IEN & (1 << pin)) != 0 && port != _getPort(pin)){//Check whether this interrupt is busy or not
		return (ZunoErrorExtInt);
	}
	if (userFunc != 0) {
		if ((ret = _CallbackRegister(pin, userFunc)) != ZunoErrorOk) {
			return (ret);
		}
	}
	GPIO_ExtIntConfig(port, pin, pin, risingEdge, fallingEdge, true);
	return (ZunoErrorOk);
}

ZunoError_t attachInterrupt(uint8_t interruptPin, void (*userFunc)(void), uint8_t mode) {
	ZunoError_t					ret;

	zunoEnterCritical();
	ret = _attachInterrupt(interruptPin, userFunc, mode);
	zunoExitCritical();
	return (ret);
}

void zunoExtIntMode(uint8_t interruptPin, uint8_t mode) {
	if (interruptPin == ZUNO_EXT_ZEROX || interruptPin == ZUNO_EXT_INT0 || interruptPin == ZUNO_EXT_INT1) {
		pinMode(interruptPin, INPUT_PULLUP);
		attachInterrupt(interruptPin, 0, mode);
	}
}

void detachInterrupt(uint8_t interruptPin) {
	uint8_t						pin;

	if (interruptPin == INT_SLEEPING)
		return ;
	pin = getRealPin(interruptPin);
	zunoEnterCritical();
	GPIO_IntDisable(pin);
	zunoDetachSysHandlerAllSubType(ZUNO_HANDLER_EXTINT, pin);
	zunoExitCritical();
}