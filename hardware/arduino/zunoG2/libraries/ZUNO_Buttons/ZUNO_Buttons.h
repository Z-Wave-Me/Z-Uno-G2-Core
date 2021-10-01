#ifndef ZUNO_BUTTONS_H
#define ZUNO_BUTTONS_H

#include "LdmaClass.h"

typedef enum
{
	BtnTypeButton,
	BtnTypeTouch
} ZunoBtnType_t;

typedef enum
{
	BtnButtonModeAuto,
	BtnButtonModeTimer,
	BtnButtonModeExtInt
} ZunoButtonMode_t;

#define BTN_DELAY_DEBOUNCE_MILLIS_DEFAULT				(50)
#define BTN_DELAY_SINGLECLICK_MILLIS_DEFAULT			(500)
#define BTN_DELAY_LONGCLICK_MILLIS_DEFAULT				(1000)
#define BTN_DELAY_FREE_MILLIS_DEFAULT					(1200)

#define BTN_BUTTON_INIT_DEFAULT\
	{\
		{\
			BTN_DELAY_DEBOUNCE_MILLIS_DEFAULT,\
			BTN_DELAY_SINGLECLICK_MILLIS_DEFAULT,\
			BTN_DELAY_LONGCLICK_MILLIS_DEFAULT,\
			BTN_DELAY_FREE_MILLIS_DEFAULT\
		},\
		BtnButtonModeAuto,\
		true\
	}

typedef struct							ZunoBtnDelayInit_s
{
	uint16_t							delayDebounce;
	uint16_t							delaySingleClick;
	uint16_t							delayLongClick;
	uint16_t							delayFree;
}										ZunoBtnDelayInit_t;

typedef struct							ZunoBtnButtonInit_s
{
	ZunoBtnDelayInit_t					delay;//first always must be
	ZunoButtonMode_t					mode;
	uint8_t								bInvert;
}										ZunoBtnButtonInit_t;


#define BTN_TOUCH_INIT_DEFAULT\
	{\
		{\
			BTN_DELAY_DEBOUNCE_MILLIS_DEFAULT,\
			BTN_DELAY_SINGLECLICK_MILLIS_DEFAULT,\
			BTN_DELAY_LONGCLICK_MILLIS_DEFAULT,\
			BTN_DELAY_FREE_MILLIS_DEFAULT\
		},\
		1\
	}

typedef struct							ZunoBtnTouchInit_s
{
	ZunoBtnDelayInit_t					delay;//first always must be
	uint8_t								clickPower;//%
}										ZunoBtnTouchInit_t;

#define BTN_DELAY_DIVIDED					ZUNO_SYSTIMER_PERIOD_MC

#define BTN_TOUCH_UNIQ_DMA_DATA				((size_t)(&ButtonsClass::_values.toushAutoScanBufferLp))
#define BTN_TOUCH_UNIQ_DMA_BASELINE			((size_t)(&ButtonsClass::_values.toushAutoScanBufferBlockMax))

#define BTN_TOUCH_BLOCK_DMA_SIZE	ldmaCtrlSizeHalf
typedef uint16_t btn_touch_value;

#define BTN_TOUCH_BLOCK_MAX				ZUNO_PIN_LAST_INDEX + 1
#define BTN_TOUCH_BLOCK_PERIOD			10
#define BTN_TOUCH_MAX_CLICK_POWER		100

#define BTN_EVENT_SINGLE_CLICK		0x01
#define BTN_EVENT_LONG_CLICK		0x02
#define BTN_EVENT_DOUBLE_CLICK		0x04
#define BTN_EVENT_TRIPLE_CLICK		0x08
#define BTN_EVENT_RELEASE			0x80

typedef enum							ZunoBtnStateButton_e
{
	BTN_STATE_IDLE,
	BTN_STATE_SINGLECLICK,
	BTN_STATE_DEBOUNCE,
	BTN_STATE_PRESSED,
	BTN_STATE_DOUBLECLICKDEBOUNCE,
	BTN_STATE_DOUBLECLICK,
	BTN_STATE_TRIPLECLICKDEBOUNCE,
	BTN_STATE_TRIPLECLICK,
	BTN_STATE_RELEASE,
	BTN_STATE_DOUBLECLICK_WAIT,
	BTN_STATE_TRIPLECLICK_WAIT
}										ZunoBtnStateButton_t;

typedef enum							ZunoBtnCommonClick_e
{
	BTN_COMMON_SINGLE,
	BTN_COMMON_DOUBLE,
	BTN_COMMON_TRIPLE,
	BTN_COMMON_LONG,
	BTN_COMMON_RELEASED,
	BTN_COMMON_FREE
}										ZunoBtnCommonClick_t;

typedef struct							ZunoBtnHeader_s
{
	struct ZunoBtnHeader_s				*next;
	size_t								lastTransition;
	uint8_t								pin;
	ZunoBtnType_t						type;
	ZunoBtnStateButton_t				state;
	uint8_t								event_map;
	uint8_t								delayDebounce;
	uint8_t								delaySingleClick;
	uint8_t								delayLongClick;
	uint8_t								delayFree;
}										ZunoBtnHeader_t;

typedef struct							ZunoBtnButton_s
{
	ZunoBtnHeader_t						header;//first always must be
	ZunoButtonMode_t					mode;
	uint8_t								bInvert;
}										ZunoBtnButton_t;

typedef struct							ZunoBtnTouch_s
{
	ZunoBtnHeader_t						header;//first always must be
	uint8_t								clickPower;//%
	uint8_t								index;
}										ZunoBtnTouch_t;

typedef struct							ZunoBtnValuesDma_s
{
	ssize_t								channel_data;
	ssize_t								channel_baseline;
	LdmaClassReceivedCyclical_t			array_data;
	LdmaClassTransferCyclical_t			array_baseline;
}										ZunoBtnValuesDma_t;

typedef struct							ZunoBtnValues_s
{
	ZunoBtnHeader_t						*list;
	btn_touch_value						*toushAutoScanBufferLp;
	ZunoBtnValuesDma_t					*dma;
	btn_touch_value						touchFullClick;
	uint8_t								bSysTimerInit;
	uint8_t								touchBlock;
	uint8_t								toushAutoScanBufferBlockMax;
	uint8_t								keyCsen;
}										ZunoBtnValues_t;

typedef struct							ZunoBtnCsenInit_s
{
	size_t								aport;
	size_t								pin;
}										ZunoBtnCsenInit_t;

class ButtonsClass {
	public:
		ButtonsClass();
		inline ZunoError_t					addButton(uint8_t pin) {return (this->addButton(pin, BtnTypeButton));};
		ZunoError_t							addButton(uint8_t pin, ZunoBtnType_t type);
		inline ZunoError_t					addButton(uint8_t pin, ZunoBtnButtonInit_t *init) {return (this->_addButton(pin, BtnTypeButton, (void *)init));};
		inline ZunoError_t					addButton(uint8_t pin, ZunoBtnTouchInit_t *init) {return (this->_addButton(pin, BtnTypeTouch, (void *)init));};
		void								deleteButton(uint8_t pin);
		inline uint8_t						isSingleClick(uint8_t pin) {return (this->_isCommonClick(pin, BTN_COMMON_SINGLE));};
		inline uint8_t						isDoubleClick(uint8_t pin) {return (this->_isCommonClick(pin, BTN_COMMON_DOUBLE));};
		inline uint8_t						isTripleClick(uint8_t pin){return (this->_isCommonClick(pin, BTN_COMMON_TRIPLE));};
		inline uint8_t						isLongClick(uint8_t pin) {return (this->_isCommonClick(pin, BTN_COMMON_LONG));};
		inline uint8_t						isReleased(uint8_t pin) {return (this->_isCommonClick(pin, BTN_COMMON_RELEASED));};
		inline uint8_t						isFree(uint8_t pin) {return (this->_isCommonClick(pin, BTN_COMMON_FREE));};

	private:
		size_t								_isCommonClick(uint8_t pin, ZunoBtnCommonClick_t typeClick);
		ZunoError_t							_addButton(uint8_t pin, ZunoBtnType_t type, void *init);
		inline ZunoError_t					_active(uint8_t pin, ZunoBtnType_t type, ZunoBtnHeader_t *list);
		inline ZunoError_t					_activeTouchLock(uint8_t pin, ZunoBtnTouch_t *list);
		inline ZunoError_t					_activeTouch(ZunoBtnCsenInit_t *initBtn, ZunoBtnTouch_t *list);
		inline void							_deactive(ZunoBtnHeader_t *list);
		inline void							_deactiveTouch(ZunoBtnTouch_t *list);
		inline ZunoError_t					_reInitList(ZunoBtnHeader_t *list, ZunoBtnType_t type, void *init);
		inline void							_initList(ZunoBtnHeader_t *list, ZunoBtnType_t type, void *init, uint8_t bOld);
		inline ZunoBtnHeader_t				*_findList(uint8_t pin);
		inline void							_addList(ZunoBtnHeader_t *list);
		inline void							_cutList(ZunoBtnHeader_t *list);
		static void							_updateTimer(void);
		static void							_updateExtIntButton(uint8_t pinExtInt);
		static void							_updateTimerCommon(size_t time_now, ZunoBtnHeader_t *list, size_t pressed);
		static ZunoError_t					_initCsen(size_t param);
		static ZunoError_t					_deInitCsen(size_t param);
		static ZunoError_t					_openTimer(void);
		static void							_closeTimer(void);
		static void							_reconfigTouch(void);
		static const ZunoBtnButtonInit_t	_initBtnButton;
		static const ZunoBtnTouchInit_t		_initBtnTouch;
		static const btn_touch_value		_baseLineTouch[];
		static ZunoBtnValues_t				_values;
};

extern ButtonsClass Btn;

#endif //ZUNO_BUTTONS_H