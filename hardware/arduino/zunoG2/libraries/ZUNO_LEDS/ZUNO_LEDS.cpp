#include "Arduino.h"
#include "stdlib.h"
#include "ZUNO_LEDS.h"
#include "Threading.h"

/* Values */
ZunoLedListGroups_t *ZunoLed::_list = 0;
volatile uint8_t ZunoLed::bSysTimerInit = 0;

/* Public Constructors */
ZunoLed::ZunoLed(void) {

}

/* Public Methods */
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
	static uint32_t				patt_index = 0;
	uint8_t						current_mode;
	uint8_t						i;
	uint8_t						divider;

	list = ZunoLed::_list;
	while (list != 0) {
		if ((current_mode = list->current_mode) >= LED_MODE_OFFSET) {
			b = &list->array[0];
			e = &b[list->num_groups];
			current_mode = current_mode - LED_MODE_OFFSET;
			//patt_index = list->patt_index;
			while (b < e) {
				divider = b->led_modes[current_mode].divider;
				uint32_t pat = b->led_modes[current_mode].pattern;
				if (patt_index % divider == 0) {
					i = (patt_index / divider) & 0x1F;
					i = (pat & (1 << i)) != 0;
					if(b->bInverted)
						i = !i;
					digitalWrite(b->led_pin, i);
				}
				b++;
			}
			//list->patt_index++;
		}
		list = list->next;
	}
	patt_index++;
}

void ZunoLed::_deleteLed(size_t name) {
	ZunoLedListGroups_t		*list;
	ZunoLedListGroups_t		*list_prev;
	ZunoLedListGroups_t		*list_tmp;

	zunoEnterCritical();
	if ((list = this->_findList(name)) != 0) {
		list_prev = this->_list;
		if (list == list_prev)
			this->_list = list->next;
		else {
			while ((list_tmp = list_prev->next) != list)
				list_prev = list_tmp;
			list_prev->next = list->next;
		}
		if (--this->bSysTimerInit == 0)
			zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer);
		free(list);
	}
	zunoExitCritical();
}

ZunoLedListGroups_t *ZunoLed::_addLedPre(size_t name, uint8_t num_groups, ZunoError_t *ret) {
	ZunoLedListGroups_t			*list;
	zunoEnterCritical();
	if (this->bSysTimerInit++ == 0) {
		if (!zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) {
			this->bSysTimerInit--;
			*ret = ZunoErrorAttachSysHandler;
			zunoExitCritical();
			return (0);
		}
	}
	if (this->_findList(name) != 0) {
		zunoExitCritical();
		return (0);
	}
	zunoExitCritical();
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
	zunoEnterCritical();
	if ((list_next = this->_list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_list = list;
	zunoExitCritical();
}

ZunoLedListGroups_t *ZunoLed::_findList(size_t name) {
	ZunoLedListGroups_t			*list;

	list = this->_list;
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

	zunoEnterCritical();
	if ((list = this->_findList(name)) != 0) {
		b = &list->array[0];
		e = &b[list->num_groups];
		while (b < e) {
			list->current_mode = mode;
			digitalWrite(b->led_pin, ((b->bInverted) ? !mode : mode));
			b++;
		}
	}
	zunoExitCritical();
}

void ZunoLed::_setMode(size_t name, uint8_t mode) {
	ZunoLedListGroups_t			*list;

	zunoEnterCritical();
	if ((list = this->_findList(name)) == 0 || mode >= list->num_modes){
		zunoExitCritical();
		return ;
	}
	if((mode + LED_MODE_OFFSET) == list->current_mode) {
		zunoExitCritical();
		return;
	}
	list->current_mode = mode + LED_MODE_OFFSET;
	list->patt_index = 0; // Always start from first stick in case of the new pattern
	zunoExitCritical();
}


/* Preinstantiate Objects */
ZunoLed Led = ZunoLed();