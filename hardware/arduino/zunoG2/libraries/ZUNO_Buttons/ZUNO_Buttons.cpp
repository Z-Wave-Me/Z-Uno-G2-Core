#include <Arduino.h>
#include "stdlib.h"
#include "ZUNO_Buttons_private.h"
#include "GpioInterrupt.h"

static const ZunoBtnButtonInit_t		gInitBtn = BTN_BUTTON_INIT_DEFAULT;

/* Public Constructors */
PinBtn::PinBtn(): list(0), bSysTimerInit(0) {

}

/* Public Methods */
ZunoError_t PinBtn::addButton(uint8_t pin, ZunoBtnType_t type, ZunoBtnButtonInit_t *init) {
	return (this->_addButton(pin, type, (void *)init));
}

ZunoError_t PinBtn::addButton(uint8_t pin, ZunoBtnType_t type) {
	return (this->_addButton(pin, type, (void *)&gInitBtn));
}

ZunoError_t PinBtn::addButton(uint8_t pin) {
	return (this->_addButton(pin, BtnTypeButton, (void *)&gInitBtn));
}

void PinBtn::deleteButton(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	noInterrupts();
	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) != 0)
		this->_deleteButton(list);
	interrupts();
}

uint8_t PinBtn::isSingleClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		return (false);
	switch (list->type) {
		case BtnTypeButton:
			if ((((ZunoBtnButton_t *)list)->event_map & BTN_EVENT_SINGLE_CLICK) != 0) {
				((ZunoBtnButton_t *)list)->event_map ^= BTN_EVENT_SINGLE_CLICK;
				return (true);
			}
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && ((ZunoBtnButton_t *)list)->state == BTN_STATE_DOUBLECLICK_WAIT && (millis() / BTN_BUTTON_DIVIDED - ((ZunoBtnButton_t *)list)->lastTransition) >= (((ZunoBtnButton_t *)list)->delayDebounce + ((ZunoBtnButton_t *)list)->delaySingleClick)) {
				((ZunoBtnButton_t *)list)->state = BTN_STATE_IDLE;
				return (true);
			}
			break ;
		default:
			break ;
	}
	return (false);
}

uint8_t PinBtn::isDoubleClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		return (false);
	switch (list->type) {
		case BtnTypeButton:
			if ((((ZunoBtnButton_t *)list)->event_map & BTN_EVENT_DOUBLE_CLICK) != 0) {
				((ZunoBtnButton_t *)list)->event_map ^= BTN_EVENT_DOUBLE_CLICK;
				return (true);
			}
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && ((ZunoBtnButton_t *)list)->state == BTN_STATE_TRIPLECLICK_WAIT && (millis() / BTN_BUTTON_DIVIDED - ((ZunoBtnButton_t *)list)->lastTransition) >= (((ZunoBtnButton_t *)list)->delayDebounce + ((ZunoBtnButton_t *)list)->delaySingleClick)) {
				((ZunoBtnButton_t *)list)->state = BTN_STATE_IDLE;
				return (true);
			}
			break ;
		default:
			break ;
	}
	return (false);
}

uint8_t PinBtn::isTripleClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0 || list->type != BtnTypeButton)
		return (false);
	if ((((ZunoBtnButton_t *)list)->event_map & BTN_EVENT_TRIPLE_CLICK) == 0 )
		return (false);
	((ZunoBtnButton_t *)list)->event_map ^= BTN_EVENT_TRIPLE_CLICK;
	return (true);
}

uint8_t PinBtn::isLongClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		return (false);
	switch (list->type) {
		case BtnTypeButton:
			if ((((ZunoBtnButton_t *)list)->event_map & BTN_EVENT_LONG_CLICK) != 0) {
				((ZunoBtnButton_t *)list)->event_map ^= BTN_EVENT_LONG_CLICK;
				return (true);
			}
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && ((ZunoBtnButton_t *)list)->state == BTN_STATE_PRESSED && (millis() / BTN_BUTTON_DIVIDED - ((ZunoBtnButton_t *)list)->lastTransition) >= (((ZunoBtnButton_t *)list)->delayDebounce + ((ZunoBtnButton_t *)list)->delayLongClick)) {
				((ZunoBtnButton_t *)list)->state = BTN_STATE_RELEASE;
				return (true);
			}
			break ;
		default:
			break ;
	}
	return (false);
}

uint8_t PinBtn::isReleased(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0 || list->type != BtnTypeButton)
		return (false);
	if ((((ZunoBtnButton_t *)list)->event_map & BTN_EVENT_RELEASE) == 0 )
		return (false);
	((ZunoBtnButton_t *)list)->event_map ^= BTN_EVENT_RELEASE;
	return (true);
}

uint8_t PinBtn::isFree(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0 || list->type != BtnTypeButton)
		return (false);
	if (((ZunoBtnButton_t *)list)->state == BTN_STATE_IDLE && (millis() / BTN_BUTTON_DIVIDED - ((ZunoBtnButton_t *)list)->lastTransition) > ((ZunoBtnButton_t *)list)->delayFree)
		return (true);
	return (false);
}

/* Private Methods */
ZunoError_t PinBtn::_addButton(uint8_t pin, ZunoBtnType_t type, void *init) {
	ZunoBtnHeader_t		*list;
	ZunoError_t			ret;

	switch (type) {
		case BtnTypeButton:
			break ;
		default:
			return (ZunoErrorBtnInvalidType);
			break ;
	}
	noInterrupts();
	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		ret = this->_addNewButton(pin, type, init);
	else if (type != list->type) {
		this->_deleteButton(list);
		ret = this->_addNewButton(pin, type, init);
	}
	else
		ret = this->_initList(list, pin, type, init, false);
	interrupts();
	return (ret);
}

inline ZunoError_t PinBtn::_addNewButton(uint8_t pin, ZunoBtnType_t type, void *init) {
	size_t				len;
	ZunoBtnHeader_t		*list;
	ZunoBtnHeader_t		*list_next;
	ZunoBtnHeader_t		*list_tmp;
	ZunoError_t			ret;

	switch (type) {
		case BtnTypeButton:
			len = sizeof(ZunoBtnButton_t);
			break ;
	}
	if ((list = (ZunoBtnHeader_t *)malloc(len)) == 0)
		return (ZunoErrorMemory);
	list->pin = pin;
	list->next = 0;
	list->type = type;
	if ((ret = this->_initList(list, pin, type, init, true)) != ZunoErrorOk) {
		free(list);
		return (ret);
	}
	if ((list_next = this->list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->list = list;
	return (ZunoErrorOk);
}

ZunoError_t PinBtn::_initList(ZunoBtnHeader_t *list, uint8_t pin, ZunoBtnType_t type, void *init, uint8_t bNew) {
	ZunoButtonMode_t		mode;
	ZunoError_t				ret;

	switch (type) {
		case BtnTypeButton:
			mode = ((ZunoBtnButtonInit_t *)init)->mode;
			if (mode == BtnButtonModeAuto)
				mode = (zunoGetSleepingMode() == false) ? BtnButtonModeTimer : BtnButtonModeExtInt;
			pinMode(pin, INPUT_PULLUP);
			if (bNew == false) {
				if (((ZunoBtnButton_t *)list)->mode != mode) {
					this->_deactiveButton(list);
					if (this->_activeButton(mode, pin) != ZunoErrorOk) {
						if ((ret = this->_activeButton(((ZunoBtnButton_t *)list)->mode, pin)) != ZunoErrorOk)
							return (ret);
						else
							return (ZunoErrorBtnChangeMode);
					}
				}
			}
			else if ((ret = this->_activeButton(mode, pin)) != ZunoErrorOk)
				return (ret);
			((ZunoBtnButton_t *)list)->lastTransition = 0;
			((ZunoBtnButton_t *)list)->event_map = 0;
			((ZunoBtnButton_t *)list)->state = BTN_STATE_IDLE;
			((ZunoBtnButton_t *)list)->mode = mode;
			((ZunoBtnButton_t *)list)->bInvert = ((ZunoBtnButtonInit_t *)init)->bInvert;
			((ZunoBtnButton_t *)list)->delayDebounce = ((ZunoBtnButtonInit_t *)init)->delayDebounce;
			((ZunoBtnButton_t *)list)->delaySingleClick = ((ZunoBtnButtonInit_t *)init)->delaySingleClick;
			((ZunoBtnButton_t *)list)->delayLongClick = ((ZunoBtnButtonInit_t *)init)->delayLongClick;
			((ZunoBtnButton_t *)list)->delayFree = ((ZunoBtnButtonInit_t *)init)->delayFree;
			break ;
	}
	return (ZunoErrorOk);
}

void PinBtn::_deleteButton(ZunoBtnHeader_t *list) {
	ZunoBtnHeader_t		*list_prev;
	ZunoBtnHeader_t		*list_tmp;

	list_prev = this->list;
	if (list == list_prev)
		this->list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
	switch (list->type) {
		case BtnTypeButton:
			this->_deactiveButton(list);
			break ;
	}
	free(list);
}

ZunoError_t PinBtn::_activeButton(ZunoButtonMode_t mode, uint8_t pin) {
	ZunoError_t				ret;

	switch (mode) {
		case BtnButtonModeTimer:
			if (this->bSysTimerInit++ != 0)
				break ;
			if (zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer) == -1) {
				this->bSysTimerInit--;
				return (ZunoErrorAttachSysHandler);
			}
			break ;
		case BtnButtonModeExtInt:
			if ((ret = attachInterrupt(pin, this->_updateExtIntButton, CHANGE)) != ZunoErrorOk)
				return (ret);
			break ;
	}
	return (ZunoErrorOk);
}

void PinBtn::_deactiveButton(ZunoBtnHeader_t *list) {
	switch (((ZunoBtnButton_t *)list)->mode) {
		case BtnButtonModeTimer:
			if (--this->bSysTimerInit != 0)
				break ;
			zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer);
			break ;
		case BtnButtonModeExtInt:
			detachInterrupt(list->pin);
			break ;
	}
}

void PinBtn::_updateExtIntButton(void) {
	ZunoBtnButton_t						*list;
	size_t								time_now;
	size_t								time_diff;
	size_t								pressed;
	size_t								delayDebounce;
	ZunoBtnStateButton_t				state_next;

	list = (ZunoBtnButton_t *)Btn._findList(g_zuno_odhw_cfg.ExtPin);
	pressed = digitalRead(list->header.pin);
	if (list->bInvert == true)
		pressed = !pressed;
	state_next = list->state;
	if (state_next == BTN_STATE_IDLE && pressed == 0)
		return ;
	time_now = millis() / BTN_BUTTON_DIVIDED;
	time_diff = time_now - list->lastTransition;
	delayDebounce = list->delayDebounce;
	switch (state_next) {
		case BTN_STATE_IDLE:
			state_next = BTN_STATE_PRESSED;
			list->event_map = 0;
			break ;
		case BTN_STATE_PRESSED:
			if (time_diff < delayDebounce) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else if (time_diff >= (delayDebounce + list->delayLongClick)) {
				state_next = BTN_STATE_IDLE;
				list->event_map = (BTN_EVENT_LONG_CLICK | BTN_EVENT_RELEASE);
			}
			else if (time_diff >= (delayDebounce + list->delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->event_map = (BTN_EVENT_SINGLE_CLICK | BTN_EVENT_RELEASE);
			}
			else {
				state_next = BTN_STATE_DOUBLECLICK_WAIT;
				list->event_map = BTN_EVENT_RELEASE;
			}
			break ;
		case BTN_STATE_DOUBLECLICK_WAIT:
			if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else
				state_next = BTN_STATE_DOUBLECLICK;
			break ;
		case BTN_STATE_DOUBLECLICK:
			if (time_diff < delayDebounce)
				state_next = BTN_STATE_DOUBLECLICK_WAIT;
			else if (time_diff >= (delayDebounce + list->delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else {
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
				list->event_map = BTN_EVENT_RELEASE;
			}
			break ;
		case BTN_STATE_TRIPLECLICK_WAIT:
			if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else
				state_next = BTN_STATE_TRIPLECLICK;
			break ;
		case BTN_STATE_TRIPLECLICK:
			if (time_diff < delayDebounce)
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
			else if (time_diff >= (delayDebounce + list->delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else {
				state_next = BTN_STATE_IDLE;
				list->event_map = (BTN_EVENT_TRIPLE_CLICK | BTN_EVENT_RELEASE);
			}
		case BTN_STATE_RELEASE:
			state_next = BTN_STATE_IDLE;
			list->event_map |= BTN_EVENT_RELEASE;
			break ;
	}
	list->lastTransition = time_now;
	list->state = state_next;
}

void PinBtn::_updateTimer(void) {
	ZunoBtnHeader_t		*list;
	size_t				time_now;

	time_now = millis();
	list = Btn.list;
	while (list != 0) {
		switch (list->type) {
			case BtnTypeButton:
				if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeTimer)
					Btn._updateButton(time_now / BTN_BUTTON_DIVIDED, (ZunoBtnButton_t *)list);
				break ;
		}
		list = list->next;
	}
}

inline void PinBtn::_updateButton(size_t time_now, ZunoBtnButton_t *list) {
	size_t								time_diff;
	size_t								pressed;
	ZunoBtnStateButton_t				state_next;

	pressed = digitalRead(list->header.pin);
	if (list->bInvert == true)
		pressed = !pressed;
	state_next = list->state;
	if (state_next == BTN_STATE_IDLE && pressed == 0)
		return ;
	time_diff = time_now - list->lastTransition;
	switch (state_next) {
		case BTN_STATE_IDLE:
			state_next = BTN_STATE_DEBOUNCE;
			list->event_map = 0;
			break ;
		case BTN_STATE_DEBOUNCE:
			if (pressed == 0) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			else if(time_diff >= list->delayDebounce)
				state_next = BTN_STATE_PRESSED;
			break ;
		case BTN_STATE_PRESSED:
			if (pressed == 0) {
				if (time_diff >= list->delaySingleClick) {
					state_next = BTN_STATE_IDLE;
					list->event_map |= (BTN_EVENT_SINGLE_CLICK | BTN_EVENT_RELEASE);
				}
				else
					state_next = BTN_STATE_DOUBLECLICK_WAIT;
			}
			else if(time_diff >= list->delayLongClick) {
				state_next = BTN_STATE_RELEASE;
				list->event_map |= BTN_EVENT_LONG_CLICK;
			}
			break ;
		case BTN_STATE_DOUBLECLICK_WAIT:
			if (pressed != 0)
				state_next = BTN_STATE_DOUBLECLICKDEBOUNCE;
			else if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map |= (BTN_EVENT_SINGLE_CLICK | BTN_EVENT_RELEASE);
			}
			break ;
		case BTN_STATE_DOUBLECLICKDEBOUNCE:
			if (pressed == 0)
				state_next = BTN_STATE_DOUBLECLICK_WAIT;
			else if (time_diff >= list->delayDebounce)
				state_next = BTN_STATE_DOUBLECLICK;
			break ;
		case BTN_STATE_DOUBLECLICK:
			if (pressed == 0)
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
			else if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			break ;
		case BTN_STATE_TRIPLECLICK_WAIT:
			if(pressed != 0)
				state_next = BTN_STATE_TRIPLECLICKDEBOUNCE;
			else if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map = (BTN_EVENT_DOUBLE_CLICK | BTN_EVENT_RELEASE);
			}
			break ;
		case BTN_STATE_TRIPLECLICKDEBOUNCE:
			if (pressed == 0)
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
			else if (time_diff >= list->delayDebounce)
				state_next = BTN_STATE_TRIPLECLICK;
			break ;
		case BTN_STATE_TRIPLECLICK:
			if (pressed == 0) {
				state_next = BTN_STATE_IDLE;
				list->event_map = (BTN_EVENT_TRIPLE_CLICK | BTN_EVENT_RELEASE);
			}
			else if (time_diff >= list->delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->event_map = 0;
			}
			break ;
		case BTN_STATE_RELEASE:
			if (pressed == 0) {
				state_next = BTN_STATE_IDLE;
				list->event_map |= BTN_EVENT_RELEASE;
			}
			break ;
	}
	if (state_next == list->state) 
		return ;
	list->lastTransition = time_now;
	list->state = state_next;
}

ZunoBtnHeader_t *PinBtn::_findList(uint8_t pin) {
	ZunoBtnHeader_t	*list;

	list = this->list;
	while (list != 0) {
		if (list->pin == pin)
			break ;
		list = list->next;
	}
	return (list);
}

/* Preinstantiate Objects */
PinBtn Btn = PinBtn();