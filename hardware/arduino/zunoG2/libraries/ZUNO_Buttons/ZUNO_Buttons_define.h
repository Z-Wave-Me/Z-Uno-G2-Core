#ifndef ZUNO_BUTTONS_DEFINE_H
#define ZUNO_BUTTONS_DEFINE_H

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

#define BTN_BUTTON_DIVIDED								0xA

#define BTN_DELAY_DEBOUNCE_MILLIS_DEFAULT				(50 / BTN_BUTTON_DIVIDED)
#define BTN_DELAY_SINGLECLICK_MILLIS_DEFAULT			(250 / BTN_BUTTON_DIVIDED)
#define BTN_DELAY_LONGCLICK_MILLIS_DEFAULT				(1000 / BTN_BUTTON_DIVIDED)
#define BTN_DELAY_FREE_MILLIS_DEFAULT					(1200 / BTN_BUTTON_DIVIDED)

#define BTN_BUTTON_INIT_DEFAULT\
	{\
		BtnButtonModeAuto,\
		true,\
		BTN_DELAY_DEBOUNCE_MILLIS_DEFAULT,\
		BTN_DELAY_SINGLECLICK_MILLIS_DEFAULT,\
		BTN_DELAY_LONGCLICK_MILLIS_DEFAULT,\
		BTN_DELAY_FREE_MILLIS_DEFAULT\
	}

typedef struct							ZunoBtnButtonInit_s
{
	ZunoButtonMode_t					mode;
	uint8_t								bInvert;
	uint8_t								delayDebounce;
	uint8_t								delaySingleClick;
	uint8_t								delayLongClick;
	uint8_t								delayFree;
}										ZunoBtnButtonInit_t;

#endif //ZUNO_BUTTONS_DEFINE_H