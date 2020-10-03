#include "Arduino.h"
#include "stdlib.h"
#include "ZUNO_LEDS_private.h"

/* Public Constructors */
ZunoLed::ZunoLed(void): list(0), bSysTimerInit(0) {

}

/* Public Methods */
void ZunoLed::deleteLed(uint8_t led_pins) {
	this->_deleteLed(led_pins);
}

void ZunoLed::deleteLed(const ZunoLedModeGroups_t *led_groups) {
	this->_deleteLed((size_t)led_groups);
}

void ZunoLed::setMode(uint8_t led_pin, uint8_t mode) {
	this->_setMode(led_pin, mode);
}

void ZunoLed::setMode(const ZunoLedModeGroups_t *led_groups, uint8_t mode) {
	this->_setMode((size_t)led_groups, mode);
}

void ZunoLed::off(uint8_t led_pin) {
	this->_setLed(led_pin, LED_MODE_ALWAYS_OFF);
}

void ZunoLed::off(const ZunoLedModeGroups_t *led_groups) {
	this->_setLed((size_t)led_groups, LED_MODE_ALWAYS_OFF);
}
void ZunoLed::on(uint8_t led_pin) {
	this->_setLed(led_pin, LED_MODE_ALWAYS_ON);
}

void ZunoLed::on(const ZunoLedModeGroups_t *led_groups) {
	this->_setLed((size_t)led_groups, LED_MODE_ALWAYS_ON);
}

ZunoError_t ZunoLed::addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes) {
	return (this->addLed(led_pin, led_modes, num_modes, false));
}

ZunoError_t ZunoLed::addLed(uint8_t led_pin, const ZunoLedMode_t *led_modes, uint8_t num_modes, uint8_t bInverted) {
	ZunoLedListGroups_t			*list;
	ZunoError_t					ret;

	ret = ZunoErrorOk;
	if ((list = this->_addLedPre(led_pin, 1, &ret)) != 0) {
		list->num_modes = num_modes;
		list->array[0].led_pin = led_pin;
		list->array[0].led_modes = led_modes;
		list->array[0].bInverted = bInverted;
		pinMode(led_pin, OUTPUT);
		this->_addList(list);
	}
	return (ret);
}

ZunoError_t ZunoLed::addLed(const ZunoLedModeGroups_t *led_groups, uint8_t num_groups, uint8_t num_modes) {
	const ZunoLedModeGroups_t	*led_groups_end;
	ZunoLedList_t				*array;
	ZunoLedListGroups_t			*list;
	ZunoError_t					ret;
	uint8_t						led_pin;

	ret = ZunoErrorOk;
	if ((list = this->_addLedPre((size_t)led_groups, num_groups, &ret)) != 0) {
		list->num_modes = num_modes;
		led_groups_end = &led_groups[num_groups];
		array = &list->array[0];
		while (led_groups < led_groups_end) {
			array->led_modes = led_groups->led_modes;
			array->bInverted = led_groups->bInverted;
			led_pin = led_groups->led_pin;
			array->led_pin = led_pin;
			pinMode(led_pin, OUTPUT);
			array++;
			led_groups++;
		}
		this->_addList(list);
	}
	return (ret);
}

/* Private Methods */
void ZunoLed::_updateTimer(void) {
	ZunoLedListGroups_t			*list;
	ZunoLedList_t				*b;
	ZunoLedList_t				*e;
	uint8_t						patt_index;
	uint8_t						current_mode;
	uint8_t						i;
	uint8_t						divider;

	list = Led.list;
	while (list != 0) {
		if ((current_mode = list->current_mode) >= LED_MODE_OFFSET) {
			b = &list->array[0];
			e = &b[list->num_groups];
			current_mode = current_mode - LED_MODE_OFFSET;
			patt_index = list->patt_index;
			while (b < e) {
				divider = b->led_modes[current_mode].divider;
				if (patt_index % divider == 0) {
					i = (patt_index / divider) % 32;
					i = ((uint8_t *)&b->led_modes[current_mode].pattern)[(i >> 3)] & (1 << (i & 0x07));
					i = (i != 0);
					digitalWrite(b->led_pin, ((b->bInverted == true) ? !i : i));
				}
				b++;
			}
			list->patt_index++;
		}
		list = list->next;
	}
}

void ZunoLed::_deleteLed(size_t name) {
	ZunoLedListGroups_t		*list;
	ZunoLedListGroups_t		*list_prev;
	ZunoLedListGroups_t		*list_tmp;

	noInterrupts();
	if ((list = this->_findList(name)) != 0) {
		list_prev = this->list;
		if (list == list_prev)
			this->list = list->next;
		else {
			while ((list_tmp = list_prev->next) != list)
				list_prev = list_tmp;
			list_prev->next = list->next;
		}
		if (--this->bSysTimerInit == 0)
			zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer);
		free(list);
	}
	interrupts();
}

ZunoLedListGroups_t *ZunoLed::_addLedPre(size_t name, uint8_t num_groups, ZunoError_t *ret) {
	ZunoLedListGroups_t			*list;
	 ZunoError_t				tmp;

	if (this->bSysTimerInit++ == 0) {
		if ((tmp = zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) != ZunoErrorOk) {
			this->bSysTimerInit--;
			*ret = tmp;
			return (0);
		}
	}
	if (this->_findList(name) != 0)
		return (0);
	if ((list = (ZunoLedListGroups_t *)malloc(sizeof(ZunoLedListGroups_t) + (sizeof(ZunoLedList_t) * num_groups))) == 0) {
		*ret = ZunoErrorMemory;
		return (0);
	}
	list->name = name;
	list->next = 0;
	list->current_mode = LED_MODE_ALWAYS_OFF;
	list->patt_index = 0;
	list->num_groups = num_groups;
	return (list);
}

void ZunoLed::_addList(ZunoLedListGroups_t *list) {
	ZunoLedListGroups_t			*list_next;
	ZunoLedListGroups_t			*list_tmp;

	noInterrupts();
	if ((list_next = this->list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->list = list;
	interrupts();
}

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

void ZunoLed::_setLed(size_t name, uint8_t mode) {
	ZunoLedListGroups_t			*list;
	ZunoLedList_t				*b;
	ZunoLedList_t				*e;

	if ((list = this->_findList(name)) == 0)
		return ;
	b = &list->array[0];
	e = &b[list->num_groups];
	while (b < e) {
		list->current_mode = mode;
		digitalWrite(b->led_pin, ((b->bInverted == true) ? !mode : mode));
		b++;
	}
}

void ZunoLed::_setMode(size_t name, uint8_t mode) {
	if ((list = this->_findList(name)) == 0 || mode >= list->num_modes)
		return ;
	if((mode + LED_MODE_OFFSET) == list->current_mode)
		return;
	list->current_mode = mode + LED_MODE_OFFSET;
	list->patt_index = 0; // Always start from first stick in case of the new pattern
}


/* Preinstantiate Objects */
ZunoLed Led = ZunoLed();