#include "Arduino.h"
#include "stdlib.h"
#include "ZUNO_LEDS.h"

/* Public Constructors */
ZunoLed::ZunoLed(void): list(0), bSysTimerInit(0) {

}

/* Public Methods */
ZunoError_t ZunoLed::addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes) {
	ZunoLedListGroups_t			*list;
	ZunoError_t						ret;

	if (this->bSysTimerInit++ == 0) {
		if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) != ZunoErrorOk) {
			this->bSysTimerInit--;
			return (ret);
		}
	}
	noInterrupts();
	if (this->_findList(led_pin) != 0) {
		interrupts();
		return (ZunoErrorOk);
	}
	if ((list = (ZunoLedListGroups_t *)malloc(0)) == 0) {
		interrupts();
		return (ZunoErrorMemory);
	}
	interrupts();
	return (ZunoErrorOk);
}

ZunoError_t ZunoLed::addLed(const ZunoLedModeGroups_t *led_groups, uint8_t num_groups, uint8_t num_modes) {
	ZunoLedListGroups_t			*list;
	ZunoError_t					ret;

	if (this->bSysTimerInit++ == 0) {
		if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) != ZunoErrorOk) {
			this->bSysTimerInit--;
			return (ret);
		}
	}
	if (this->_findList((size_t)led_groups) != 0)
		return (ZunoErrorOk);
	noInterrupts();
	if ((list = (ZunoLedListGroups_t *)malloc(0)) == 0) {
		interrupts();
		return (ZunoErrorMemory);
	}
	
	interrupts();
	return (ZunoErrorOk);
}


/* Private Methods */
ZunoLedListGroups_t *ZunoLed::_findList(size_t name) {
	ZunoLedListGroups_t			*list;

	list = this->list;
	while (list != 0) {
		if (list->name == name)
			break ;
		list = list->next;
	}
	return (list);
}

void ZunoLed::_updateTimer(void) {
}

/* Preinstantiate Objects */
ZunoLed Led = ZunoLed();