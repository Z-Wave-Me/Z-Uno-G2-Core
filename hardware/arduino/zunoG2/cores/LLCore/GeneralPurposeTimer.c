#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"
#include "GeneralPurposeTimer.h"

#define GPT_TIMER						TIMER0
#define GPT_TIMER_CLOCK					cmuClock_TIMER0
#define GPT_TIMER_HANDLER_ID			ZUNO_IRQVEC_TIMER0


void zunoGPTInit(uint8_t flags) {
	//zunoAttachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, &timer0_irq_handler);
}
void zunoGPTEnable(uint8_t bEnable) {

}
void zunoGPTSet(uint16_t interval) {

}