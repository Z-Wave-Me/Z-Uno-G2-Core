#ifndef ZUNO_NEOPIXEL_PRIVATE_H
#define ZUNO_NEOPIXEL_PRIVATE_H

#define NEO_W_OFFSET(type)				((type >> 6) & 0x3)
#define NEO_R_OFFSET(type)				((type >> 4) & 0x3)
#define NEO_G_OFFSET(type)				((type >> 2) & 0x3)
#define NEO_B_OFFSET(type)				(type & 0x3)

#define NEO_RESET_MICROSECONDS			50

#define NEO_FULL_PERIOD					125
#define NEO_ZERO_HIGH_PERIOD			40
#define NEO_ONE_HIGH_PERIOD				80
#define NEO_ZERO_LOW_PERIOD				(NEO_FULL_PERIOD - NEO_ZERO_HIGH_PERIOD)
#define NEO_ONE_LOW_PERIOD				(NEO_FULL_PERIOD - NEO_ONE_HIGH_PERIOD)

#define NEO_TIMER						WTIMER0
#define NEO_TIMER_CLOCK					cmuClock_WTIMER0
#define NEO_TIMER_IRQ					WTIMER0_IRQn
#define NEO_TIMER_HANDLER_ID			ZUNO_IRQVEC_WTIMER0

typedef union							ZunoNeoType_u
{
	uint16_t							type;
	struct
	{
		uint16_t						blueOffset: 2;
		uint16_t						greenOffset: 2;
		uint16_t						redOffset : 2;
		uint16_t						whiteOffset : 2;
	};
}										ZunoNeoType_t;

typedef struct							ZunoNeoList_s
{
	struct ZunoNeoList_s				*next;
	ZunoNeoCountLed						count_led;
	ZunoNeoType_t						flag;
	uint8_t								neo_pin;
	uint8_t								array[];
}										ZunoNeoList_t;

typedef struct							ZunoNeoSaveTimer_s
{
	uint8_t								*b;
	uint8_t								*e;
	uint8_t								bit_count;
	uint8_t								bState;
	uint8_t								neo_pin;
}										ZunoNeoSaveTimer_t;

typedef union							ZunoNeoSave_u
{
	ZunoNeoSaveTimer_t					timer;
}										ZunoNeoSave_t;

#endif //ZUNO_NEOPIXEL_PRIVATE_H