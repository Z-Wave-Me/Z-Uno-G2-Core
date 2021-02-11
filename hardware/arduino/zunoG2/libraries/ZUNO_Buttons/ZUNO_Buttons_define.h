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

#endif //ZUNO_BUTTONS_DEFINE_H