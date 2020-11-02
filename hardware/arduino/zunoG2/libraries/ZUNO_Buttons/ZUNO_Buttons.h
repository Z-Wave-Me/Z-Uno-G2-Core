#ifndef ZUNO_BUTTONS_H
#define ZUNO_BUTTONS_H

#include "ZUNO_Buttons_define.h"

class PinBtn {
	public:
		PinBtn();
		ZunoError_t				addButton(uint8_t pin);
		ZunoError_t				addButton(uint8_t pin, ZunoBtnType_t type);
		ZunoError_t				addButton(uint8_t pin, ZunoBtnButtonInit_t *init);
		ZunoError_t				addButton(uint8_t pin, ZunoBtnTouchInit_t *init);
		void					deleteButton(uint8_t pin);
		uint8_t					isSingleClick(uint8_t pin);
		uint8_t					isDoubleClick(uint8_t pin);
		uint8_t					isTripleClick(uint8_t pin);
		uint8_t					isLongClick(uint8_t pin);
		uint8_t					isReleased(uint8_t pin);
		uint8_t					isFree(uint8_t pin);
		void					test(void);
};

extern PinBtn Btn;

#endif //ZUNO_BUTTONS_H