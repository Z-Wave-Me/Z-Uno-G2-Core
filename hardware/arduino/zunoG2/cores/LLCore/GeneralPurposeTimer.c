#include "Arduino.h"
#include "Sync.h"
#include "GeneralPurposeTimer.h"
#include "em_device.h"
#include "em_timer.h"

#define GPT_DEFAULT_INTERVAL			0xFFFF

#define GPT_PWM_ENTER()					zunoSyncLockWrite(&_sync, SyncMasterGPT, &_key)
#define GPT_PWM_EXIT()					zunoSyncReleseWrite(&_sync, SyncMasterGPT, &_key)

#if TIMER_COUNT == 0x2
#define GPT_TIMER						WTIMER0
#define GPT_TIMER_CLOCK					cmuClock_WTIMER0
#define GPT_TIMER_IRQ					WTIMER0_IRQn
#define GPT_TIMER_HANDLER_ID			ZUNO_IRQVEC_WTIMER0
#define GPT_TIMER_32_BIT
#endif
#if TIMER_COUNT == 0x5
#define GPT_TIMER						TIMER4
#define GPT_TIMER_CLOCK					cmuClock_TIMER4
#define GPT_TIMER_IRQ					TIMER4_IRQn
#define GPT_TIMER_HANDLER_ID			ZUNO_IRQVEC_TIMER4
#define GPT_TIMER_16_BIT
#endif

static ZunoSync_t _sync = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterGPT);
static volatile uint8_t _key = true;
static uint32_t _freq_timer_clock = 0x0;
static uint16_t _interval = 0x0;
static uint8_t _flags = 0x0;
#if defined(GPT_TIMER_16_BIT)
static uint8_t _count_rep = 0x0;
static uint8_t _count_rep_max = 0x0;
#endif

static uint32_t _get_top_freq(uint16_t interval) {
	uint64_t							out;

	if ((_flags & ZUNO_GPT_SCALE1024) != 0x0)
		out = (32 * 4);//32 ps
	else
		out = 1;//0.25ps
	out = out * _freq_timer_clock * interval;
	return (out / 4000000);//4MHz
}

#if defined(GPT_TIMER_16_BIT)
static TIMER_Prescale_TypeDef _getPrescale(size_t freq) {
	uint8_t					i;

	i = 0x0;
	while (true) {
		if ((freq / (0x1 << i)) <= 0xFFFF)
			break ;
		i++;
		#if defined (_TIMER_CTRL_PRESC_MASK)
		if (i >= timerPrescale1024)
			break ;
		#endif
		#if defined (_TIMER_CFG_PRESC_MASK)
		if (((0x1 << i) - 0x1) >= timerPrescale1024)
			break ;
		#endif
	}
	#if defined (_TIMER_CTRL_PRESC_MASK)
	return ((TIMER_Prescale_TypeDef)i);
	#endif
	#if defined (_TIMER_CFG_PRESC_MASK)
	return ((TIMER_Prescale_TypeDef)((0x1 << i) - 0x1));
	#endif
}
#endif

static void _set_top_timer(uint16_t interval) {
	#if defined(GPT_TIMER_16_BIT)
	static TIMER_Prescale_TypeDef			timer_prescale_old = (TIMER_Prescale_TypeDef)0x0;
	TIMER_Prescale_TypeDef					timer_prescale;
	uint8_t									count;
	TIMER_Init_TypeDef						timerInit;
	#endif
	uint32_t								freq;

	freq = _get_top_freq(interval);
	#if defined(GPT_TIMER_16_BIT)
	timer_prescale = _getPrescale(freq);
	#if defined (_TIMER_CFG_PRESC_MASK)
	freq = freq / (timer_prescale + 0x1);
	#endif
	#if defined (_TIMER_CTRL_PRESC_MASK)
	freq = freq / (0x1 << timer_prescale);
	#endif
	if (TIMER_TopGet(GPT_TIMER) == freq && timer_prescale_old == timer_prescale)
		return ;
	#endif
	#if defined(GPT_TIMER_32_BIT)
	if (TIMER_TopGet(GPT_TIMER) == freq)
		return ;
	#endif
	#if defined(GPT_TIMER_16_BIT)
	count = 0x1;
	while (true) {
		if (freq / count <= 0xFFFF)
			break ;
		count++;
	}
	freq = freq / count;
	_count_rep_max = count - 0x1;
	_count_rep = 0x0;
	timer_prescale_old = timer_prescale;
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = timer_prescale;
	TIMER_Init(GPT_TIMER, &timerInit);
	#endif
	#if defined(GPT_TIMER_32_BIT)
	TIMER_Enable(GPT_TIMER, false);
	#endif
	TIMER_TopSet(GPT_TIMER, freq);
	TIMER_Enable(GPT_TIMER, true);
}

static void _timer_handler(void) {
	size_t						interval;

	#if defined(GPT_TIMER_16_BIT)
	uint8_t							count;
	#endif

	if (_freq_timer_clock == 0x0)
		return ;
	#if defined(GPT_TIMER_16_BIT)
	if ((count = _count_rep) < _count_rep_max) {
		_count_rep = count + 0x1;
		return ;
	}
	_count_rep = 0x0;
	#endif
	if ((_flags & ZUNO_GPT_CYCLIC) == 0) {
		TIMER_Enable(GPT_TIMER, false);
	} else {
		if ((interval = _interval) != 0x0) {
			_interval = 0x0;
			_set_top_timer(interval);
		}
	}
	zunoSysHandlerCall(ZUNO_HANDLER_GPT, ZUNO_GPT_BASIC);
}

static void _deInit(void) {
	_freq_timer_clock = 0x0;
	NVIC_DisableIRQ(GPT_TIMER_IRQ);
	TIMER_Reset(GPT_TIMER);
	CMU_ClockEnable(GPT_TIMER_CLOCK, false);
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler);
	zunoPeripheryRelese(&gSyncVirtualTimer2, SyncMasterGPT);
}

void zunoGPTDeInit(void) {
	if (GPT_PWM_ENTER() != ZunoErrorOk)
		return ;
	_deInit();
	GPT_PWM_EXIT();
}

static ZunoError_t _init(void) {
	TIMER_Init_TypeDef			timerInit;

	if (_freq_timer_clock != 0x0)
		return (ZunoErrorOk);
	if (zunoAttachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler) == false)
		return (ZunoErrorAttachSysHandler);
	if (zunoPeripheryCapture(&gSyncVirtualTimer2, SyncMasterGPT) != SyncPeripheryCaptureStatusOk) {
		zunoDetachSysHandler(ZUNO_HANDLER_IRQ, GPT_TIMER_HANDLER_ID, (void *)_timer_handler);
		return (ZunoErrorNotInit);
	}
	CMU_ClockEnable(GPT_TIMER_CLOCK, true);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.enable = false;
	TIMER_Init(GPT_TIMER, &timerInit);
	TIMER_IntEnable(GPT_TIMER, TIMER_IF_OF);/* Enable TIMER0 IRQ on Overflow */
	NVIC_EnableIRQ(GPT_TIMER_IRQ);/* Enable TIMER0 interrupt in NVIC */
	_freq_timer_clock = CMU_ClockFreqGet(GPT_TIMER_CLOCK);
	return (ZunoErrorOk);
}

ZunoError_t zunoGPTInit(uint8_t flags) {
	ZunoError_t					ret;

	if ((ret = GPT_PWM_ENTER()) != ZunoErrorOk)
		return (ret);
	if ((ret = _init()) == ZunoErrorOk)
		_flags = flags;
	GPT_PWM_EXIT();
	return (ret);
}

static void _zunoGPTEnable(uint8_t bEnable) {
	size_t						interval;

	if (_freq_timer_clock == 0x0)
		return ;
	if (bEnable == true) {
		if ((interval = _interval) == 0x0)
			interval = GPT_DEFAULT_INTERVAL;
		_interval = 0x0;
		_set_top_timer(interval);
		if ((GPT_TIMER->STATUS & TIMER_STATUS_RUNNING) == 0x0)
			TIMER_Enable(GPT_TIMER, true);
	}
	else
		TIMER_Enable(GPT_TIMER, false);
}

void zunoGPTEnable(uint8_t bEnable) {
	if (GPT_PWM_ENTER() != ZunoErrorOk)
		return ;
	_zunoGPTEnable(bEnable);
	GPT_PWM_EXIT();
}

static void _zunoGPTSet(uint16_t interval) {
	if (_freq_timer_clock == 0x0)
		return ;
	if ((_flags & ZUNO_GPT_IMWRITE) != 0x0 && interval != 0x0) {
		_set_top_timer(interval);
		return ;
	}
	_interval = interval;
}

void zunoGPTSet(uint16_t interval) {
	if (GPT_PWM_ENTER() != ZunoErrorOk)
		return ;
	_zunoGPTSet(interval);
	GPT_PWM_EXIT();
}
