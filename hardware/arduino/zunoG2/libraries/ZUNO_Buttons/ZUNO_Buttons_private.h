#ifndef ZUNO_BUTTONS_PRIVATE_H
#define ZUNO_BUTTONS_PRIVATE_H

#include "ZUNO_Buttons_define.h"

#define BTN_EVENT_SINGLE_CLICK		0x01
#define BTN_EVENT_LONG_CLICK		0x02
#define BTN_EVENT_DOUBLE_CLICK		0x04
#define BTN_EVENT_TRIPLE_CLICK		0x08
#define BTN_EVENT_RELEASE			0x80

typedef enum			ZunoBtnStateButton_e
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
}						ZunoBtnStateButton_t;

typedef struct							ZunoBtnHeader_s
{
	struct ZunoBtnHeader_s				*next;
	uint8_t								pin;
	ZunoBtnType_t						type;
}										ZunoBtnHeader_t;

typedef struct							ZunoBtnButton_s
{
	ZunoBtnHeader_t						header;
	ZunoBtnStateButton_t				state;
	uint8_t								event_map;
	size_t								lastTransition;
	ZunoButtonMode_t					mode;
	uint8_t								bInvert;
	uint8_t								delayDebounce;
	uint8_t								delaySingleClick;
	uint8_t								delayLongClick;
	uint8_t								delayFree;
}										ZunoBtnButton_t;

typedef struct							ZunoBtnTouch_s
{
	ZunoBtnHeader_t						header;
}										ZunoBtnTouch_t;

class PinBtn {
	public:
		PinBtn();
		ZunoError_t				addButton(uint8_t pin);
		ZunoError_t				addButton(uint8_t pin, ZunoBtnType_t type);
		ZunoError_t				addButton(uint8_t pin, ZunoBtnType_t type, ZunoBtnButtonInit_t *init);
		void					deleteButton(uint8_t pin);
		uint8_t					isSingleClick(uint8_t pin);
		uint8_t					isDoubleClick(uint8_t pin);
		uint8_t					isTripleClick(uint8_t pin);
		uint8_t					isLongClick(uint8_t pin);
		uint8_t					isReleased(uint8_t pin);
		uint8_t					isFree(uint8_t pin);

	private:
		inline ZunoError_t		_addNewButton(uint8_t pin, ZunoBtnType_t type, void *init);
		ZunoError_t				_addButton(uint8_t pin, ZunoBtnType_t type, void *init);
		void					_deleteButton(ZunoBtnHeader_t *list);
		ZunoError_t				_activeButton(ZunoButtonMode_t mode, uint8_t pin);
		void					_deactiveButton(ZunoBtnHeader_t *list);
		static void				_updateTimer(void);
		static void				_updateExtIntButton(void);
		inline void				_updateButton(size_t time_now, ZunoBtnButton_t *list);
		ZunoError_t				_initList(ZunoBtnHeader_t *list, uint8_t pin, ZunoBtnType_t type, void *init, uint8_t bNew);
		ZunoBtnHeader_t			*_findList(uint8_t pin);
		ZunoBtnHeader_t			*list;
		uint8_t					bSysTimerInit;
};

extern PinBtn Btn;

#endif //ZUNO_BUTTONS_PRIVATE_H