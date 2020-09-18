#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"
#include "GeneralPurposeTimer.h"

#ifndef size_t
	#define size_t		uint32_t
#endif

#define GPT_TOP_SET_FREQ(interval)		(size_t)((((gFlags & ZUNO_GPT_SCALE1024) != 0) ? (32 * 4) : 1) * gTopSetPrescale * interval)//32 ps / 0.25ps
#define GPT_DEFAULT_INTERVAL			0xFFFFF

#define GPT_TIMER						WTIMER0// onli 32 bit or modifed
#define GPT_TIMER_CLOCK					cmuClock_WTIMER0
#define GPT_TIMER_IRQ					WTIMER0_IRQn
#define GPT_TIMER_HANDLER_ID			ZUNO_IRQVEC_WTIMER0

static volatile uint16_t		gInterval = 0;
static volatile uint8_t			gTopSetPrescale = 0;
static volatile uint8_t			gFlags = 0;


static void _timer_handler(void) {
	TIMER_TypeDef				*timer;
	size_t						interval;

	timer = GPT_TIMER;
	if ((gFlags & ZUNO_GPT_CYCLIC) == 0) {
		TIMER_Enable(timer, false);
	} else {
		interval = gInterval;
		if (TIMER_TopGet(timer) != interval)
			TIMER_TopSet(GPT_TIMER, GPT_TOP_SET_FREQ(interval));
	}
	zunoSysHandlerCall(ZUNO_HANDLER_GPT, ZUNO_GPT_BASIC);
	TIMER_IntClear(timer, TIMER_IF_OF);/* Clear the interrupt flag in the beginning */
}

void zunoGPTInit(uint8_t flags) {
	gFlags = flags;
}
void zunoGPTEnable(uint8_t bEnable) {
	TIMER_Init_TypeDef			timerInit;
	TIMER_TypeDef				*timer;
	size_t						freq;

	timer = GPT_TIMER;
	if (g_bit_field.bGPTInit == false) {
		zunoAttachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler);
		CMU_ClockEnable(GPT_TIMER_CLOCK, true);
		gTopSetPrescale = CMU_ClockFreqGet(GPT_TIMER_CLOCK) / 4000000;//4MHz
		timerInit = TIMER_INIT_DEFAULT;
		timerInit.enable = false;
		TIMER_Init(timer, &timerInit);
		NVIC_EnableIRQ(GPT_TIMER_IRQ);/* Enable TIMER0 interrupt in NVIC */
		TIMER_IntEnable(timer, TIMER_IF_OF);/* Enable TIMER0 IRQ on Overflow */
		g_bit_field.bGPTInit = true;
	}
	if (bEnable == true)
		TIMER_TopSet(GPT_TIMER, GPT_TOP_SET_FREQ(((gInterval != 0) ? gInterval : GPT_DEFAULT_INTERVAL)));
	TIMER_Enable(timer, bEnable);
}
void zunoGPTSet(uint16_t interval) {
	size_t					freq;

	if ((gFlags & ZUNO_GPT_IMWRITE) == 0)
		TIMER_TopSet(GPT_TIMER, GPT_TOP_SET_FREQ(interval));
	gInterval = interval;
}