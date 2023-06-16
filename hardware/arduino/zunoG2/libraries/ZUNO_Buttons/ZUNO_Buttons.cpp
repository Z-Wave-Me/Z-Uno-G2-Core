#include <Arduino.h>
#include "stdlib.h"
#include "GpioInterrupt.h"
#include "Threading.h"
#include "Sync.h"
#include "ZUNO_Buttons.h"
#include "em_csen.h"

/* Constants */
const ZunoBtnButtonInit_t ButtonsClass::_initBtnButton = BTN_BUTTON_INIT_DEFAULT;
const ZunoBtnTouchInit_t ButtonsClass::_initBtnTouch = BTN_TOUCH_INIT_DEFAULT;
const btn_touch_value ButtonsClass::_baseLineTouch[1] = {0};


/* Values */
 ZunoBtnValues_t ButtonsClass::_values = {0, 0, 0, 0, 0, 0, 0, 0};

/* Public Constructors */
ButtonsClass::ButtonsClass() {
}

/* Public Methods */
ZunoError_t ButtonsClass::addButton(uint8_t pin, ZunoBtnType_t type) {
	void				*init;

	switch (type) {
		// MULTI_CHIP
		#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
		case BtnTypeTouch:
			init = (void *)&this->_initBtnTouch;
			break ;
		#endif
		case BtnTypeButton:
			init = (void *)&this->_initBtnButton;
			break ;
		default:
			return (ZunoErrorBtnInvalidType);
			break ;
	}
	return (this->_addButton(pin, type, init));
}

void ButtonsClass::deleteButton(uint8_t pin) {
	ZunoBtnHeader_t		*list;

	if (zunoIsIOThread() == true)
		return ;
	zunoEnterCritical();
	if ((list = this->_findList(pin)) != 0)
		this->_cutList(list);
	zunoExitCritical();
	if (list != 0)
		this->_deactive(list);
}

/* Private Methods */
size_t ButtonsClass::_isCommonClick(uint8_t pin, ZunoBtnCommonClick_t typeClick) {
	size_t					out;
	ZunoBtnHeader_t			*list;
	size_t					event_map;
	ZunoBtnType_t			type;
	size_t					delayTime;

	zunoEnterCritical();
	if ((list = (ZunoBtnHeader_t *)this->_findList(pin)) != 0) {
		delayTime = (millis() / BTN_DELAY_DIVIDED - list->lastTransition);
		event_map = list->event_map;
		type = list->type;
		switch (typeClick) {
			case BTN_COMMON_SINGLE:
				if ((event_map & BTN_EVENT_SINGLE_CLICK) != 0) {
					list->event_map = event_map ^ BTN_EVENT_SINGLE_CLICK;
					out = true;
					break ;
				}
				switch (type) {
					case BtnTypeButton:
						if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_DOUBLECLICK_WAIT && delayTime >= (list->delayDebounce + list->delaySingleClick)) {
							list->state = BTN_STATE_IDLE;
							out = true;
							break ;
						}
						out = false;
						break ;
					default:
						out = false;
						break ;
				}
				break ;
			case BTN_COMMON_DOUBLE:
				if ((event_map & BTN_EVENT_DOUBLE_CLICK) != 0) {
					list->event_map = event_map ^ BTN_EVENT_DOUBLE_CLICK;
					out = true;
					break ;
				}
				switch (type) {
					case BtnTypeButton:
						if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_TRIPLECLICK_WAIT && delayTime >= (list->delayDebounce + list->delaySingleClick)) {
							list->state = BTN_STATE_IDLE;
							out = true;
							break ;
						}
						out = false;
						break ;
					default:
						out = false;
						break ;
				}
				break ;
			case BTN_COMMON_TRIPLE:
				if ((event_map & BTN_EVENT_TRIPLE_CLICK) != 0) {
					list->event_map = event_map ^ BTN_EVENT_TRIPLE_CLICK;
					out = true;
					break ;
				}
				out = false;
				break ;
			case BTN_COMMON_LONG:
				if ((event_map & BTN_EVENT_LONG_CLICK) != 0) {
					list->event_map = event_map ^ BTN_EVENT_LONG_CLICK;
					out = true;
					break ;
				}
				switch (type) {
					case BtnTypeButton:
						if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeExtInt && list->state == BTN_STATE_PRESSED && delayTime >= (list->delayDebounce + list->delayLongClick)) {
							list->state = BTN_STATE_RELEASE;
							out = true;
							break ;
						}
						out = false;
						break ;
					default:
						out = false;
						break ;
				}
				break ;
			case BTN_COMMON_RELEASED:
				if ((event_map & BTN_EVENT_RELEASE) != 0) {
					list->event_map = event_map ^ BTN_EVENT_RELEASE;
					out = true;
					break ;
				}
				out = false;
				break ;
			case BTN_COMMON_FREE:
				if (list->state == BTN_STATE_IDLE && delayTime >= list->delayFree) {
					out = true;
					break ;
				}
				out = false;
				break ;
			default:
				out = false;
				break ;
		}
	}
	else
		out = false;
	zunoExitCritical();
	return (out);
}

ZunoError_t ButtonsClass::_addButton(uint8_t pin, ZunoBtnType_t type, void *init) {
	ZunoBtnHeader_t			*list;
	size_t					len;
	ZunoError_t				ret;

	if (zunoIsIOThread() == true)
		return (ZunoErrorTredIo);
	if (pin > ZUNO_PIN_LAST_INDEX)
		return(ZunoErrorInvalidPin);
	zunoEnterCritical();
	list = (ZunoBtnHeader_t *)this->_findList(pin);
	if (list != 0)
		this->_cutList(list);
	zunoExitCritical();
	if (list != 0) {
		if (this->_reInitList(list, type, init) == ZunoErrorOk)
			return (ZunoErrorOk);
		this->_deactive(list);
	}
	switch (type) {
		case BtnTypeButton:
			len = sizeof(ZunoBtnButton_t);
			break ;
		// MULTI_CHIP
		#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
		case BtnTypeTouch:
			len = sizeof(ZunoBtnTouch_t);
			break ;
		#endif
	}
	if ((list = (ZunoBtnHeader_t *)malloc(len)) == 0)
		return (ZunoErrorMemory);
	list->pin = pin;
	list->next = 0;
	list->type = type;
	this->_initList(list, type, init, false);
	if ((ret = this->_active(pin, type, list)) == ZunoErrorOk) {
		zunoEnterCritical();
		this->_addList(list);
		zunoExitCritical();
	}
	else
		free(list);
	return (ret);
}

inline ZunoError_t ButtonsClass::_reInitList(ZunoBtnHeader_t *list, ZunoBtnType_t type, void *init) {
	ZunoButtonMode_t		mode;

	if (list->type != type)
		return (ZunoErrorBtnChangeMode);
	switch (type) {
		case BtnTypeButton:
			if ((mode = ((ZunoBtnButton_t *)list)->mode) == BtnButtonModeAuto)
				mode = (zunoGetSleepingMode() == false) ? BtnButtonModeTimer : BtnButtonModeExtInt;
			if (mode != ((ZunoBtnButtonInit_t *)init)->mode)
				return (ZunoErrorBtnChangeMode);
			break ;
		default:
			break ;
	}
	this->_initList(list, type, init, true);
	return (ZunoErrorOk);
}

inline void ButtonsClass::_initList(ZunoBtnHeader_t *list, ZunoBtnType_t type, void *init, uint8_t bOld) {
	ZunoButtonMode_t		mode;
	ZunoBtnDelayInit_t		*delay;
	// MULTI_CHIP
	#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
	uint8_t					clickPower;
	#endif

	switch (type) {
		case BtnTypeButton:
			mode = ((ZunoBtnButtonInit_t *)init)->mode;
			if (bOld == false) {
				if (mode == BtnButtonModeAuto)
					mode = (zunoGetSleepingMode() == false) ? BtnButtonModeTimer : BtnButtonModeExtInt;
				((ZunoBtnButton_t *)list)->mode = mode;
			}
			((ZunoBtnButton_t *)list)->bInvert = ((ZunoBtnButtonInit_t *)init)->bInvert;
			break ;
		// MULTI_CHIP
		#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
		case BtnTypeTouch:
			if ((clickPower = ((ZunoBtnTouchInit_t *)init)->clickPower) > BTN_TOUCH_MAX_CLICK_POWER)
				clickPower = BTN_TOUCH_MAX_CLICK_POWER;
			((ZunoBtnTouch_t *)list)->clickPower = clickPower;
			break ;
		#endif
	}
	list->lastTransition = 0;
	list->event_map = 0;
	list->state = BTN_STATE_IDLE;
	delay = &((ZunoBtnButtonInit_t *)init)->delay;
	list->delayDebounce = delay->delayDebounce / BTN_DELAY_DIVIDED;
	list->delaySingleClick = delay->delaySingleClick / BTN_DELAY_DIVIDED;
	list->delayLongClick = delay->delayLongClick / BTN_DELAY_DIVIDED;
	list->delayFree = delay->delayFree / BTN_DELAY_DIVIDED;
}

void ButtonsClass::_closeTimer(void) {
	zunoEnterCritical();
	if (--ButtonsClass::_values.bSysTimerInit == 0)
		zunoDetachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)ButtonsClass::_updateTimer);
	zunoExitCritical();
}

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
ZunoError_t ButtonsClass::_deInitCsen(size_t param) {
	if (param <= 0x1F)
		CSEN->SCANMASK0 ^= (1 << param);
	else
		CSEN->SCANMASK1 ^= (1 << (param - 0x20));
	if (--ButtonsClass::_values.touchBlock == 0) {
		LdmaClass::transferStop(ButtonsClass::_values.dma->channel_data);
		LdmaClass::transferStop(ButtonsClass::_values.dma->channel_baseline);
		ButtonsClass::_closeTimer();
		CSEN_Disable(CSEN);
		free(ButtonsClass::_values.toushAutoScanBufferLp);
		free(ButtonsClass::_values.dma);
		return (ZunoErrorOk);
	}
	ButtonsClass::_reconfigTouch();
	return (ZunoErrorSyncDeInit);
}
#endif

inline void ButtonsClass::_deactive(ZunoBtnHeader_t *list) {
	ZunoBtnButton_t			*list_button;

	switch (list->type) {
		case BtnTypeButton:
			list_button = (ZunoBtnButton_t *)list;
			switch ((size_t)list_button->mode) {
				case BtnButtonModeTimer:
					this->_closeTimer();
					break ;
				case BtnButtonModeExtInt:
					detachInterrupt(list_button->header.pin);
					break ;
			}
			break ;
		// MULTI_CHIP
		#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
		case BtnTypeTouch:
			zunoSyncClose(&gSyncCSEN, SyncMasterBtn, this->_deInitCsen, ((ZunoBtnTouch_t *)list)->index, &this->_values.keyCsen);
			break ;
		#endif
	}
	free(list);
}

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
void ButtonsClass::_reconfigTouch(void) {

	LdmaClass::transferStop(ButtonsClass::_values.dma->channel_data);
	ButtonsClass::_values.dma->channel_data = LdmaClass::receivedCyclical((const void *)&CSEN->DATA, ButtonsClass::_values.toushAutoScanBufferLp, ButtonsClass::_values.touchBlock, ldmaPeripheralSignal_CSEN_DATA, BTN_TOUCH_BLOCK_DMA_SIZE, &ButtonsClass::_values.dma->array_data);
}
#endif

inline ZunoError_t ButtonsClass::_active(uint8_t pin, ZunoBtnType_t type, ZunoBtnHeader_t *list) {
	ZunoError_t				ret;
	ZunoBtnButton_t			*list_button;

	pinMode(pin, INPUT_PULLUP_FILTER);
	ret = ZunoErrorOk;//-Wall -Wextra -Werror
	switch (type) {
		case BtnTypeButton:
			list_button = (ZunoBtnButton_t *)list;
			switch ((size_t)list_button->mode) {
				case BtnButtonModeTimer:
					ret = this->_openTimer();
					break ;
				case BtnButtonModeExtInt:
					ret = attachInterrupt(pin, (void (*)(void))this->_updateExtIntButton, CHANGE);
					break ;
			}
			break ;
		// MULTI_CHIP
		#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
		case BtnTypeTouch:
			ret = this->_activeTouchLock(pin, (ZunoBtnTouch_t *)list);
			break ;
		#endif
	}
	return (ret);
}

ZunoError_t ButtonsClass::_openTimer(void) {
	ZunoError_t ret = ZunoErrorOk;
	zunoEnterCritical();
	if ( (ButtonsClass::_values.bSysTimerInit++ == 0) && 
		(!zunoAttachSysHandler(ZUNO_HANDLER_SYSTIMER, 0, (void *)ButtonsClass::_updateTimer))){ 
		ButtonsClass::_values.bSysTimerInit--;
		ret = ZunoErrorAttachSysHandler;
	}
	zunoExitCritical();
	return ret;
}

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
static inline void _setPeriodCsen(CSEN_Init_TypeDef *csenInit, size_t ms) {
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
#endif

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
ZunoError_t ButtonsClass::_initCsen(size_t param) {
	ZunoBtnCsenInit_t			*initBtn;
	ZunoError_t					ret;
	CSEN_Init_TypeDef			csenInit;
	CSEN_InitMode_TypeDef		csenInitMode;
	btn_touch_value				*blockBuffer;
	ZunoBtnValuesDma_t			*dma;

	initBtn = (ZunoBtnCsenInit_t *)param;
	if ((blockBuffer = (btn_touch_value *)malloc(BTN_TOUCH_BLOCK_PERIOD * sizeof(btn_touch_value))) == 0)
		return (ZunoErrorMemory);
	if ((dma = (ZunoBtnValuesDma_t *)malloc(sizeof(ZunoBtnValuesDma_t))) == 0) {
		free(blockBuffer);
		return (ZunoErrorMemory);
	}
	memset(blockBuffer, 0, BTN_TOUCH_BLOCK_PERIOD * sizeof(btn_touch_value));
	if ((dma->channel_data = LdmaClass::receivedCyclical((const void *)&CSEN->DATA, blockBuffer, 0x1, ldmaPeripheralSignal_CSEN_DATA, BTN_TOUCH_BLOCK_DMA_SIZE, &dma->array_data)) < 0x0)
	{
		free(dma);
		free(blockBuffer);
		return (ZunoErrorDmaLimitChannel);
	}
	if ((dma->channel_baseline = LdmaClass::transferCyclical(&ButtonsClass::_baseLineTouch[0], (void *)&CSEN->DMBASELINE, 0x1, ldmaPeripheralSignal_CSEN_BSLN, BTN_TOUCH_BLOCK_DMA_SIZE, &dma->array_baseline)) < 0x0)
	{
		LdmaClass::transferStop(dma->channel_data);
		free(dma);
		free(blockBuffer);
		return (ZunoErrorDmaLimitChannel);
	}
	if ((ret = ButtonsClass::_openTimer()) != ZunoErrorOk) {
		LdmaClass::transferStop(dma->channel_data);
		LdmaClass::transferStop(dma->channel_baseline);
		free(dma);
		free(blockBuffer);
		return (ret);
	}
	ButtonsClass::_values.dma = dma;
	ButtonsClass::_values.toushAutoScanBufferLp = blockBuffer;
	ButtonsClass::_values.toushAutoScanBufferBlockMax = BTN_TOUCH_BLOCK_PERIOD;
	CMU_ClockEnable(cmuClock_CSEN_HF, true);
	CMU_ClockEnable(cmuClock_CSEN_LF, true);
	csenInit =  CSEN_INIT_DEFAULT;
	_setPeriodCsen(&csenInit, BTN_DELAY_DIVIDED / 2);
	CSEN_Init(CSEN, &csenInit);
	csenInitMode = CSEN_INITMODE_DEFAULT;
	csenInitMode.accMode = csenAccMode1;
	csenInitMode.enableDma = true;
	csenInitMode.trigSel = csenTrigSelStart;
	csenInitMode.singleSel = (CSEN_SingleSel_TypeDef)initBtn->aport;
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
	pinMode(initBtn->pin, OUTPUT_UP);
	while (CSEN_IsBusy(CSEN) == true)
		__NOP();
	ButtonsClass::_values.touchFullClick = CSEN_DataGet(CSEN) / BTN_TOUCH_MAX_CLICK_POWER;
	pinMode(initBtn->pin, INPUT_PULLUP_FILTER);
	CSEN->CTRL = (CSEN->CTRL ^ (csenTrigSelStart << _CSEN_CTRL_STM_SHIFT)) | (csenTrigSelTimer << _CSEN_CTRL_STM_SHIFT);
	return (ZunoErrorOk);
}
#endif

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
inline ZunoError_t ButtonsClass::_activeTouchLock(uint8_t pin, ZunoBtnTouch_t *list) {
	ZunoBtnCsenInit_t			initBtn;
	ZunoError_t					ret;

	initBtn.pin = pin;
	initBtn.aport = g_aport_pa0_pf7_all[getLocation(g_loc_pa0_pf7_all, sizeof(g_loc_pa0_pf7_all), pin)] - 0x20;
	if ((ret = zunoSyncOpen(&gSyncCSEN, SyncMasterBtn, this->_initCsen, (size_t)&initBtn, &this->_values.keyCsen)) != ZunoErrorOk)
		return (ret);
	ret = this->_activeTouch(&initBtn, list);
	zunoSyncReleseWrite(&gSyncCSEN, SyncMasterBtn, &this->_values.keyCsen);
	return (ret);
}
#endif

// MULTI_CHIP
#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
inline ZunoError_t ButtonsClass::_activeTouch(ZunoBtnCsenInit_t *initBtn, ZunoBtnTouch_t *list) {
	size_t						aport;
	size_t						block;
	size_t						blockMax;
	btn_touch_value				*blockBuffer;
	btn_touch_value				*tmp;

	if ((block = ++this->_values.touchBlock) != 0) {
		if (block > (blockMax = this->_values.toushAutoScanBufferBlockMax)) {
			blockMax = blockMax + BTN_TOUCH_BLOCK_PERIOD;
			if ((blockBuffer = (btn_touch_value *)malloc(blockMax * sizeof(btn_touch_value))) == 0) {
				this->_values.touchBlock--;
				return (ZunoErrorMemory);
			}
			memset(blockBuffer, 0, blockMax * sizeof(btn_touch_value));
			tmp = this->_values.toushAutoScanBufferLp;
			this->_values.toushAutoScanBufferBlockMax = blockMax;
			this->_values.toushAutoScanBufferLp = blockBuffer;
			free(tmp);
		}
		this->_reconfigTouch();
	}
	aport = initBtn->aport;
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
#endif

inline void ButtonsClass::_addList(ZunoBtnHeader_t *list) {
	ZunoBtnHeader_t		*list_next;
	ZunoBtnHeader_t		*list_tmp;

	if ((list_next = this->_values.list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_values.list = list;
}

inline void ButtonsClass::_cutList(ZunoBtnHeader_t *list) {
	ZunoBtnHeader_t		*list_prev;
	ZunoBtnHeader_t		*list_tmp;

	list_prev = this->_values.list;
	if (list == list_prev)
		this->_values.list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
}

inline ZunoBtnHeader_t *ButtonsClass::_findList(uint8_t pin) {
	ZunoBtnHeader_t	*list;

	list = this->_values.list;
	while (list != 0) {
		if (list->pin == pin)
			break ;
		list = list->next;
	}
	return (list);
}

void ButtonsClass::_updateTimer(void) {
	ZunoBtnHeader_t			*list;
	size_t					time_now;
	size_t					pressed;
	// MULTI_CHIP
	#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
	size_t					input0;
	size_t					input1;
	size_t					index;
	#endif

	time_now = millis() / BTN_DELAY_DIVIDED;
	list = Btn._values.list;
	while (list != 0) {
		switch (list->type) {
			case BtnTypeButton:
				if (((ZunoBtnButton_t *)list)->mode == BtnButtonModeTimer) {
					pressed = digitalRead(list->pin);
					if (((ZunoBtnButton_t *)list)->bInvert == true)
						pressed = !pressed;
					ButtonsClass::_updateTimerCommon(time_now, list, pressed);
				}
				break ;
			// MULTI_CHIP
			#if defined(CSEN_COUNT) && (CSEN_COUNT > 0)
			case BtnTypeTouch:
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
				index = (size_t)(-1);
				while (input0 != 0) {
					index++;
					input0 = input0 & (input0 - 1);
				}
				while (input1 != 0) {
					index++;
					input1 = input1 & (input1 - 1);
				}
				pressed = (ButtonsClass::_values.toushAutoScanBufferLp[index] >= ButtonsClass::_values.touchFullClick * ((ZunoBtnTouch_t *)list)->clickPower)? 1 : 0;
				ButtonsClass::_updateTimerCommon(time_now, list, pressed);
				break ;
			#endif
		}
		list = list->next;
	}
}

void ButtonsClass::_updateTimerCommon(size_t time_now, ZunoBtnHeader_t *list, size_t pressed) {
	size_t								time_diff;
	ZunoBtnStateButton_t				state_next;

	state_next = list->state;
	if (state_next == BTN_STATE_IDLE && pressed == 0)
		return ;
	time_diff = time_now - list->lastTransition;
	switch ((size_t)state_next) {
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

void ButtonsClass::_updateExtIntButton(uint8_t pinExtInt) {
	ZunoBtnButton_t						*list;
	size_t								time_now;
	size_t								time_diff;
	size_t								pressed;
	size_t								delayDebounce;
	ZunoBtnStateButton_t				state_next;

	list = (ZunoBtnButton_t *)Btn._findList(pinExtInt);
	if(list == NULL)
		return;
	pressed = digitalRead(list->header.pin);
	if (list->bInvert == true)
		pressed = !pressed;
	state_next = list->header.state;
	if (state_next == BTN_STATE_IDLE && pressed == 0)
		return ;
	time_now = millis() / BTN_DELAY_DIVIDED;
	time_diff = time_now - list->header.lastTransition;
	delayDebounce = list->header.delayDebounce;
	switch ((size_t)state_next) {
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
			break ;
		case BTN_STATE_RELEASE:
			state_next = BTN_STATE_IDLE;
			list->header.event_map |= BTN_EVENT_RELEASE;
			break ;
	}
	list->header.lastTransition = time_now;
	list->header.state = state_next;
}

/* Preinstantiate Objects */
ButtonsClass Btn = ButtonsClass();