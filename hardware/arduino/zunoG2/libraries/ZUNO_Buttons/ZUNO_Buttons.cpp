#include <Arduino.h>
#include "stdlib.h"
#include "GpioInterrupt.h"
#include "CrtxCSEN.h"
#include "ZDma.h"
#include "ZUNO_Buttons_private.h"

static const ZunoBtnButtonInit_t		gInitBtnButton = BTN_BUTTON_INIT_DEFAULT;
static const ZunoBtnTouchInit_t			gInitBtnTouch = BTN_TOUCH_INIT_DEFAULT;
static const btn_touch_value			gBaseLineTouch[ZUNO_PIN_LAST_INDEX + 1] = {0};


/* Public Constructors */
PinBtn::PinBtn(): _list(0), _bSysTimerInit(0), _bCsenInit(0), _touchFullClick(0), _toushAutoScanBufferLp(0) {

}

/* Public Methods */
ZunoError_t PinBtn::addButton(uint8_t pin) {
	return (this->addButton(pin, BtnTypeButton));
}

ZunoError_t PinBtn::addButton(uint8_t pin, ZunoBtnType_t type) {
	void				*init;

	switch (type) {
		case BtnTypeTouch:
			init = (void *)&gInitBtnTouch;
			break ;
		case BtnTypeButton:
			init = (void *)&gInitBtnButton;
			break ;
		default:
			return (ZunoErrorBtnInvalidType);
			break ;
	}
	return (this->_addButton(pin, type, init));
}

ZunoError_t PinBtn::addButton(uint8_t pin, ZunoBtnButtonInit_t *init) {
	return (this->_addButton(pin, BtnTypeButton, (void *)init));
}

ZunoError_t PinBtn::addButton(uint8_t pin, ZunoBtnTouchInit_t *init) {
	return (this->_addButton(pin, BtnTypeTouch, (void *)init));
}

void PinBtn::deleteButton(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) != 0) {
		this->_deleteButton(list);
	}
}

uint8_t PinBtn::isSingleClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		return (false);
	if ((list->event_map & BTN_EVENT_SINGLE_CLICK) != 0) {
		list->event_map ^= BTN_EVENT_SINGLE_CLICK;
		return (true);
	}
	switch (list->type) {
		case BtnTypeButton:
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_DOUBLECLICK_WAIT && (millis() / BTN_DELAY_DIVIDED - list->lastTransition) >= (list->delayDebounce + list->delaySingleClick)) {
				list->state = BTN_STATE_IDLE;
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
	if ((list->event_map & BTN_EVENT_DOUBLE_CLICK) != 0) {
		list->event_map ^= BTN_EVENT_DOUBLE_CLICK;
		return (true);
	}
	switch (list->type) {
		case BtnTypeButton:
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_TRIPLECLICK_WAIT && (millis() / BTN_DELAY_DIVIDED - list->lastTransition) >= (list->delayDebounce + list->delaySingleClick)) {
				list->state = BTN_STATE_IDLE;
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
	if ((list->event_map & BTN_EVENT_TRIPLE_CLICK) == 0 )
		return (false);
	list->event_map ^= BTN_EVENT_TRIPLE_CLICK;
	return (true);
}

uint8_t PinBtn::isLongClick(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0)
		return (false);
	if ((list->event_map & BTN_EVENT_LONG_CLICK) != 0) {
		list->event_map ^= BTN_EVENT_LONG_CLICK;
		return (true);
	}
	switch (list->type) {
		case BtnTypeButton:
			if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_PRESSED && (millis() / BTN_DELAY_DIVIDED - list->lastTransition) >= (list->delayDebounce + list->delayLongClick)) {
				list->state = BTN_STATE_RELEASE;
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
	if ((list->event_map & BTN_EVENT_RELEASE) == 0 )
		return (false);
	list->event_map ^= BTN_EVENT_RELEASE;
	return (true);
}

uint8_t PinBtn::isFree(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) == 0 || list->type != BtnTypeButton)
		return (false);
	if (list->state == BTN_STATE_IDLE && (millis() / BTN_DELAY_DIVIDED - list->lastTransition) > list->delayFree)
		return (true);
	return (false);
}

/* Private Methods */
ZunoError_t PinBtn::_addButton(uint8_t pin, ZunoBtnType_t type, void *init) {
	ZunoBtnHeader_t		*list;
	ZunoError_t			ret;

	if (pin > ZUNO_PIN_LAST_INDEX)
		return(ZunoErrorInvalidPin);
	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) != 0 && type == list->type)
		ret = this->_initList(list, pin, type, init, false);
	else {
		if (list != 0)
			this->_deleteButton(list);
		ret = this->_addNewButton(pin, type, init);
	}
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
		case BtnTypeTouch:
			len = sizeof(ZunoBtnTouch_t);
			break ;
	}
	if ((list = (ZunoBtnHeader_t *)malloc(len)) == 0)
		return (ZunoErrorMemory);
	list->pin = pin;
	list->next = 0;
	list->type = type;
	if ((ret = this->_initList(list, pin, type, init, true)) != ZunoErrorOk)
		return (ret);
	if ((list_next = this->_list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_list = list;
	return (ZunoErrorOk);
}

ZunoError_t PinBtn::_initList(ZunoBtnHeader_t *list, uint8_t pin, ZunoBtnType_t type, void *init, uint8_t bNew) {
	ZunoButtonMode_t		mode;
	ZunoError_t				ret;
	ZunoBtnDelayInit_t		*delay;
	uint8_t					clickPower;

	pinMode(pin, INPUT_PULLUP_FILTER);
	switch (type) {
		case BtnTypeButton:
			mode = ((ZunoBtnButtonInit_t *)init)->mode;
			if (mode == BtnButtonModeAuto)
				mode = (zunoGetSleepingMode() == false) ? BtnButtonModeTimer : BtnButtonModeExtInt;
			if (bNew == false) {
				if (((ZunoBtnButton_t *)list)->mode != mode) {
					this->_deactiveButton((ZunoBtnButton_t *)list);
					if (this->_activeButton(mode, pin) != ZunoErrorOk) {
						if ((ret = this->_activeButton(((ZunoBtnButton_t *)list)->mode, pin)) != ZunoErrorOk) {
							free(list);
							return (ret);
						}
						else
							return (ZunoErrorBtnChangeMode);
					}
				}
			}
			else if ((ret = this->_activeButton(mode, pin)) != ZunoErrorOk) {
				free(list);
				return (ret);
			}
			((ZunoBtnButton_t *)list)->mode = mode;
			((ZunoBtnButton_t *)list)->bInvert = ((ZunoBtnButtonInit_t *)init)->bInvert;
			break ;
		case BtnTypeTouch:
			if (bNew == true && (ret = this->_activeTouch(pin, (ZunoBtnTouch_t *)list)) != ZunoErrorOk) {
				free(list);
				return (ret);
			}
			if ((clickPower = ((ZunoBtnTouchInit_t *)init)->clickPower) > 100)
				clickPower = 100;
			((ZunoBtnTouch_t *)list)->clickPower = clickPower;
			break ;
	}
	list->lastTransition = 0;
	list->event_map = 0;
	list->state = BTN_STATE_IDLE;
	delay = &((ZunoBtnButtonInit_t *)init)->delay;
	list->delayDebounce = delay->delayDebounce;
	list->delaySingleClick = delay->delaySingleClick;
	list->delayLongClick = delay->delayLongClick;
	list->delayFree = delay->delayFree;
	return (ZunoErrorOk);
}

static void _setPeriodCsen(CSEN_Init_TypeDef *csenInit, size_t ms) {
	CSEN_PCPrescale_TypeDef				pcPrescale;
	size_t								pcReload;
	size_t								freq;

	freq = CMU_ClockFreqGet(cmuClock_CSEN_LF);
	pcPrescale = csenPCPrescaleDiv1;
	while (pcPrescale <= csenPCPrescaleDiv128) {
		pcReload = ms * freq / 1000 / (1 << pcPrescale);
		if (pcReload <= 0xFF) {
			csenInit->pcReload = pcReload;
			csenInit->pcPrescale = pcPrescale;
			return ;
		}
		pcPrescale = (CSEN_PCPrescale_TypeDef)((size_t)pcPrescale + 1);
	}
	csenInit->pcReload = 0xFF;
	csenInit->pcPrescale = csenPCPrescaleDiv128;
}

ZunoError_t PinBtn::_activeTouch(uint8_t pin, ZunoBtnTouch_t *list) {
	ZunoError_t					ret;
	CSEN_Init_TypeDef			csenInit;
	CSEN_InitMode_TypeDef		csenInitMode;
	ZunoZDmaExt_t				lpExt;
	uint8_t						aport;
	uint8_t						block;
	uint8_t						blockMax;
	btn_touch_value				*blockBuffer;

	aport = g_aport_pa0_pf7_all[getLocation(g_loc_pa0_pf7_all, sizeof(g_loc_pa0_pf7_all), pin)] - 0x20;
	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.loop = ZDMA_EXT_LOOP_INFINITY;
	if ((block = this->_bCsenInit + 1) == 1) {
		if ((blockBuffer = (btn_touch_value *)malloc(BTN_TOUCH_BLOCK_PERIOD * sizeof(btn_touch_value))) == 0)
			return (ZunoErrorMemory);
		if ((ret = ZDMA.toPeripheralMemory(BTN_TOUCH_UNIQ_DMA_DATA, zdmaPeripheralSignal_CSEN_DATA, (void *)blockBuffer, (void *)&CSEN->DATA, block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt)) != ZunoErrorOk) {
			free(blockBuffer);
			return (ret);
		}
		if ((ret = ZDMA.toMemoryPeripheral(BTN_TOUCH_UNIQ_DMA_BASELINE, zdmaPeripheralSignal_CSEN_BSLN, (void *)&CSEN->DMBASELINE, (void *)&gBaseLineTouch[0], block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt)) != ZunoErrorOk) {
			ZDMA.stopTransfer(BTN_TOUCH_UNIQ_DMA_DATA, true);
			free(blockBuffer);
			return (ret);
		}
		if (this->_bSysTimerInit == 0) {
			if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) != ZunoErrorOk) {
				ZDMA.stopTransfer(BTN_TOUCH_UNIQ_DMA_BASELINE, true);
				ZDMA.stopTransfer(BTN_TOUCH_UNIQ_DMA_DATA, true);
				free(blockBuffer);
				return (ret);
			}
		}
		memset(blockBuffer, 0, BTN_TOUCH_BLOCK_PERIOD * sizeof(btn_touch_value));
		this->_toushAutoScanBufferLp = blockBuffer;
		this->_toushAutoScanBufferBlockMax = BTN_TOUCH_BLOCK_PERIOD;
		CMU_ClockEnable(cmuClock_CSEN_HF, true);
		CMU_ClockEnable(cmuClock_CSEN_LF, true);
		csenInit =  CSEN_INIT_DEFAULT;
		_setPeriodCsen(&csenInit, BTN_DELAY_DIVIDED / 2);
		CSEN_Init(CSEN, &csenInit);
		csenInitMode = CSEN_INITMODE_DEFAULT;
		csenInitMode.accMode = csenAccMode1;
		csenInitMode.enableDma = true;
		csenInitMode.trigSel = csenTrigSelStart;
		csenInitMode.singleSel = (CSEN_SingleSel_TypeDef)aport;
		csenInitMode.sampleMode = csenSampleModeScan;
		csenInitMode.dmIterPerCycle = 4;
		csenInitMode.dmCycles = 0xFF;
		csenInitMode.dmDelta = 0xFF;
		csenInitMode.dmFixedDelta = true;
		csenInitMode.convSel = csenConvSelDM;
		csenInitMode.dmRes = csenDMRes16;
		CSEN_InitMode(CSEN, &csenInitMode);
		CSEN_Enable(CSEN);
		CSEN_Start(CSEN);
		pinMode(pin, OUTPUT_UP);
		while (CSEN_IsBusy(CSEN) == true)
			__NOP();
		this->_touchFullClick = CSEN_DataGet(CSEN) / 100;
		pinMode(pin, INPUT_PULLUP_FILTER);
		CSEN->CTRL = CSEN->CTRL ^ (csenTrigSelStart << _CSEN_CTRL_STM_SHIFT) | (csenTrigSelTimer << _CSEN_CTRL_STM_SHIFT);
		this->_bSysTimerInit++;
	}
	else {
		lpExt.flags = ZDMA_EXT_FLAGS_RECONFIG;
		if (block > (blockMax = this->_toushAutoScanBufferBlockMax)) {
			blockMax = blockMax + BTN_TOUCH_BLOCK_PERIOD;
			if ((blockBuffer = (btn_touch_value *)malloc(blockMax * sizeof(btn_touch_value))) == 0)
				return (ZunoErrorMemory);
			this->_toushAutoScanBufferBlockMax = blockMax;
			memset(blockBuffer, 0, blockMax * sizeof(btn_touch_value));
			ZDMA.toPeripheralMemory(BTN_TOUCH_UNIQ_DMA_DATA, zdmaPeripheralSignal_CSEN_DATA, (void *)blockBuffer, (void *)&CSEN->DATA, block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
			ZDMA.toMemoryPeripheral(BTN_TOUCH_UNIQ_DMA_BASELINE, zdmaPeripheralSignal_CSEN_BSLN, (void *)&CSEN->DMBASELINE, (void *)&gBaseLineTouch[0], block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
			free(this->_toushAutoScanBufferLp);
			this->_toushAutoScanBufferLp = blockBuffer;
		}
		else {
			ZDMA.toPeripheralMemory(BTN_TOUCH_UNIQ_DMA_DATA, zdmaPeripheralSignal_CSEN_DATA, (void *)this->_toushAutoScanBufferLp, (void *)&CSEN->DATA, block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
			ZDMA.toMemoryPeripheral(BTN_TOUCH_UNIQ_DMA_BASELINE, zdmaPeripheralSignal_CSEN_BSLN, (void *)&CSEN->DMBASELINE, (void *)&gBaseLineTouch[0], block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
		}
	}
	this->_bCsenInit++;
	if (aport < 0x20) {
		CSEN->SCANMASK0 |= (1 << aport);
		list->index = aport;
	}
	else {
		CSEN->SCANMASK1 |= (1 << (aport - 0x40));
		list->index = aport - 0x20;
	}
	return (ZunoErrorOk);
}

ZunoError_t PinBtn::_activeButton(ZunoButtonMode_t mode, uint8_t pin) {
	ZunoError_t				ret;

	switch (mode) {
		case BtnButtonModeTimer:
			if (this->_bSysTimerInit++ != 0)
				break ;
			if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer)) != ZunoErrorOk) {
				this->_bSysTimerInit--;
				return (ret);
			}
			break ;
		case BtnButtonModeExtInt:
			if ((ret = attachInterrupt(pin, this->_updateExtIntButton, CHANGE)) != ZunoErrorOk)
				return (ret);
			break ;
	}
	return (ZunoErrorOk);
}

void PinBtn::_deleteButton(ZunoBtnHeader_t *list) {
	ZunoBtnHeader_t		*list_prev;
	ZunoBtnHeader_t		*list_tmp;

	list_prev = this->_list;
	if (list == list_prev)
		this->_list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
	switch (list->type) {
		case BtnTypeButton:
			this->_deactiveButton((ZunoBtnButton_t *)list);
			break ;
		case BtnTypeTouch:
			this->_deactiveTouch((ZunoBtnTouch_t *)list);
			break ;
	}
	free(list);
}

inline void PinBtn::_deactiveTouch(ZunoBtnTouch_t *list) {
	uint8_t						block;
	btn_touch_value				*blockBuffer;
	ZunoZDmaExt_t				lpExt;
	uint8_t						index;

	index = list->index;

	if (index <= 0x1F)
		CSEN->SCANMASK0 ^= (1 << index);
	else
		CSEN->SCANMASK1 ^= (1 << (index - 0x20));
	blockBuffer = this->_toushAutoScanBufferLp;
	if ((block = --this->_bCsenInit) == 0) {
		ZDMA.stopTransfer(BTN_TOUCH_UNIQ_DMA_DATA, true);
		ZDMA.stopTransfer(BTN_TOUCH_UNIQ_DMA_BASELINE, true);
		free(blockBuffer);
		if (--this->_bSysTimerInit == 0)
			zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer);
		CSEN_Disable(CSEN);
		return ;
	}
	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.loop = ZDMA_EXT_LOOP_INFINITY;
	lpExt.flags = ZDMA_EXT_FLAGS_RECONFIG;
	ZDMA.toPeripheralMemory(BTN_TOUCH_UNIQ_DMA_DATA, zdmaPeripheralSignal_CSEN_DATA, (void *)blockBuffer, (void *)&CSEN->DATA, block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
	ZDMA.toMemoryPeripheral(BTN_TOUCH_UNIQ_DMA_BASELINE, zdmaPeripheralSignal_CSEN_BSLN, (void *)&CSEN->DMBASELINE, (void *)&gBaseLineTouch[0], block, BTN_TOUCH_BLOCK_DMA_SIZE, &lpExt);
}

void PinBtn::_deactiveButton(ZunoBtnButton_t *list) {
	switch (list->mode) {
		case BtnButtonModeTimer:
			if (--this->_bSysTimerInit != 0)
				break ;
			zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)this->_updateTimer);
			break ;
		case BtnButtonModeExtInt:
			detachInterrupt(list->header.pin);
			break ;
	}
}

static void _updateTimerCommon(size_t time_now, ZunoBtnHeader_t *list, size_t pressed) {
	size_t								time_diff;
	ZunoBtnStateButton_t				state_next;

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

void PinBtn::_updateTimer(void) {
	ZunoBtnHeader_t			*list;
	size_t					time_now;

	time_now = millis() / BTN_DELAY_DIVIDED;
	list = Btn._list;
	while (list != 0) {
		switch (list->type) {
			case BtnTypeButton:
				if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeTimer)
					Btn._updateTimerButtom(time_now, list);
				break ;
			case BtnTypeTouch:
				Btn._updateTimerTouch(time_now, list);
				break ;
		}
		list = list->next;
	}
}

inline void PinBtn::_updateTimerButtom(size_t time_now, ZunoBtnHeader_t *list) {
	size_t					pressed;

	pressed = digitalRead(list->pin);
	if (((ZunoBtnButton_t *)list)->bInvert == true)
		pressed = !pressed;
	_updateTimerCommon(time_now, list, pressed);
}

inline void PinBtn::_updateTimerTouch(size_t time_now, ZunoBtnHeader_t *list) {
	size_t								pressed;
	size_t								input0;
	size_t								input1;
	uint8_t								index;

	index = ((ZunoBtnTouch_t *)list)->index;
	input0 = CSEN->SCANMASK0;
	input1 = CSEN->SCANMASK1;
	if (index <= 0x1F) {
		index = 0x1F - index;
		input0 = (input0 << index) >> index;
		input1 = 0;
	}
	else {
		index = 0x1F - (index - 0x20);
		input1 = (input1 << index) >> index;
	}
	index = 0xFF;
	while (input0 != 0) {
		index++;
		input0 = input0 & (input0 - 1);
	}
	while (input1 != 0) {
		index++;
		input1 = input1 & (input1 - 1);
	}
	pressed = (Btn._toushAutoScanBufferLp[index] >= this->_touchFullClick * ((ZunoBtnTouch_t *)list)->clickPower)? 1 : 0;
	_updateTimerCommon(time_now, list, pressed);
}

void PinBtn::_updateExtIntButton(uint8_t pinExtInt) {
	ZunoBtnButton_t						*list;
	size_t								time_now;
	size_t								time_diff;
	size_t								pressed;
	size_t								delayDebounce;
	ZunoBtnStateButton_t				state_next;

	list = (ZunoBtnButton_t *)Btn._findList(pinExtInt);
	pressed = digitalRead(list->header.pin);
	if (list->bInvert == true)
		pressed = !pressed;
	state_next = list->header.state;
	if (state_next == BTN_STATE_IDLE && pressed == 0)
		return ;
	time_now = millis() / BTN_DELAY_DIVIDED;
	time_diff = time_now - list->header.lastTransition;
	delayDebounce = list->header.delayDebounce;
	switch (state_next) {
		case BTN_STATE_IDLE:
			state_next = BTN_STATE_PRESSED;
			list->header.event_map = 0;
			break ;
		case BTN_STATE_PRESSED:
			if (time_diff < delayDebounce) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = 0;
			}
			else if (time_diff >= (delayDebounce + list->header.delayLongClick)) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = (BTN_EVENT_LONG_CLICK | BTN_EVENT_RELEASE);
			}
			else if (time_diff >= (delayDebounce + list->header.delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = (BTN_EVENT_SINGLE_CLICK | BTN_EVENT_RELEASE);
			}
			else {
				state_next = BTN_STATE_DOUBLECLICK_WAIT;
				list->header.event_map = BTN_EVENT_RELEASE;
			}
			break ;
		case BTN_STATE_DOUBLECLICK_WAIT:
			if (time_diff >= list->header.delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = 0;
			}
			else
				state_next = BTN_STATE_DOUBLECLICK;
			break ;
		case BTN_STATE_DOUBLECLICK:
			if (time_diff < delayDebounce)
				state_next = BTN_STATE_DOUBLECLICK_WAIT;
			else if (time_diff >= (delayDebounce + list->header.delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = 0;
			}
			else {
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
				list->header.event_map = BTN_EVENT_RELEASE;
			}
			break ;
		case BTN_STATE_TRIPLECLICK_WAIT:
			if (time_diff >= list->header.delaySingleClick) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = 0;
			}
			else
				state_next = BTN_STATE_TRIPLECLICK;
			break ;
		case BTN_STATE_TRIPLECLICK:
			if (time_diff < delayDebounce)
				state_next = BTN_STATE_TRIPLECLICK_WAIT;
			else if (time_diff >= (delayDebounce + list->header.delaySingleClick)) {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = 0;
			}
			else {
				state_next = BTN_STATE_IDLE;
				list->header.event_map = (BTN_EVENT_TRIPLE_CLICK | BTN_EVENT_RELEASE);
			}
		case BTN_STATE_RELEASE:
			state_next = BTN_STATE_IDLE;
			list->header.event_map |= BTN_EVENT_RELEASE;
			break ;
	}
	list->header.lastTransition = time_now;
	list->header.state = state_next;
}

ZunoBtnHeader_t *PinBtn::_findList(uint8_t pin) {
	ZunoBtnHeader_t	*list;

	list = this->_list;
	while (list != 0) {
		if (list->pin == pin)
			break ;
		list = list->next;
	}
	return (list);
}

/* Preinstantiate Objects */
PinBtn Btn = PinBtn();