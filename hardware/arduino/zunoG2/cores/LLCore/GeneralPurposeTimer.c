#include "Arduino.h"
#include "Sync.h"
#include "GeneralPurposeTimer.h"
#include "em_device.h"
#include "em_timer.h"

// MULTI_CHIP
#if defined(WTIMER0)
#define GPT_TOP_SET_FREQ(interval)		(size_t)((((gFlags & ZUNO_GPT_SCALE1024) != 0) ? (32 * 4) : 1) * gTopSetPrescale * interval)//32 ps / 0.25ps
#define GPT_DEFAULT_INTERVAL			0xFFFFF

#define GPT_TIMER						WTIMER0// onli 32 bit or modifed
#define GPT_TIMER_LOCK					gSyncWTIMER0
#define GPT_TIMER_LOCK_KEY				g_zuno_odhw_cfg.keyGPT
#define GPT_TIMER_CLOCK					cmuClock_WTIMER0
#define GPT_TIMER_IRQ					WTIMER0_IRQn
#define GPT_TIMER_HANDLER_ID			ZUNO_IRQVEC_WTIMER0

static volatile uint16_t		gInterval = 0;
static volatile uint8_t			gTopSetPrescale = 0;
static volatile uint8_t			gFlags = 0;


static void _timer_handler(void *p) {
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
	(void)p;
}

static ZunoError_t _deInit(size_t param) {
	NVIC_DisableIRQ(GPT_TIMER_IRQ);
	TIMER_Enable(GPT_TIMER, false);
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler);
	return (ZunoErrorOk);
	(void)param;
}

void zunoGPTDeInit(void) {
	zunoSyncClose(&GPT_TIMER_LOCK, SyncMasterGPT, _deInit, 0, &GPT_TIMER_LOCK_KEY);
}

static ZunoError_t _init(size_t param) {
	TIMER_Init_TypeDef			timerInit;
	if(!zunoAttachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler))
		return ZunoErrorAttachSysHandler;
	CMU_ClockEnable(GPT_TIMER_CLOCK, true);
	gTopSetPrescale = CMU_ClockFreqGet(GPT_TIMER_CLOCK) / 4000000;//4MHz
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(GPT_TIMER, &timerInit);
	TIMER_IntEnable(GPT_TIMER, TIMER_IF_OF);/* Enable TIMER0 IRQ on Overflow */
	NVIC_EnableIRQ(GPT_TIMER_IRQ);/* Enable TIMER0 interrupt in NVIC */
	return (ZunoErrorOk);
	(void)param;
}

ZunoError_t zunoGPTInit(uint8_t flags) {
	ZunoError_t					ret;

	if ((ret = zunoSyncOpen(&GPT_TIMER_LOCK, SyncMasterGPT, _init, 0, &GPT_TIMER_LOCK_KEY)) != ZunoErrorOk)
		return (ret);
	gFlags = flags;
	zunoSyncReleseWrite(&GPT_TIMER_LOCK, SyncMasterGPT, &GPT_TIMER_LOCK_KEY);
	return (ZunoErrorOk);
}

void zunoGPTEnable(uint8_t bEnable) {
	size_t						interval;

	if (zunoSyncLockRead(&GPT_TIMER_LOCK, SyncMasterGPT, &GPT_TIMER_LOCK_KEY) != ZunoErrorOk)
		return ;
	if (bEnable == true) {
		interval = gInterval;
		TIMER_TopSet(GPT_TIMER, GPT_TOP_SET_FREQ(((interval != 0) ? interval : GPT_DEFAULT_INTERVAL)));
	}
	TIMER_Enable(GPT_TIMER, bEnable);
	zunoSyncReleseRead(&GPT_TIMER_LOCK, SyncMasterGPT, &GPT_TIMER_LOCK_KEY);
}
void zunoGPTSet(uint16_t interval) {
	if (zunoSyncLockRead(&GPT_TIMER_LOCK, SyncMasterGPT, &GPT_TIMER_LOCK_KEY) != ZunoErrorOk)
		return ;
	if ((gFlags & ZUNO_GPT_IMWRITE) == 0)
		TIMER_TopSet(GPT_TIMER, GPT_TOP_SET_FREQ(interval));
	gInterval = interval;
	zunoSyncReleseRead(&GPT_TIMER_LOCK, SyncMasterGPT, &GPT_TIMER_LOCK_KEY);
}
#endif