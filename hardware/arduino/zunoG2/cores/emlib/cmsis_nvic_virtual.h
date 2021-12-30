#ifndef CMSIS_NVIC_VIRTUAL_H

#include "ZUNO_CoreDefs.h"

// #define NVIC_SetPriorityGrouping    __NVIC_SetPriorityGrouping
// #define NVIC_GetPriorityGrouping    __NVIC_GetPriorityGrouping
// #define NVIC_EnableIRQ              __NVIC_EnableIRQ
// #define NVIC_GetEnableIRQ           __NVIC_GetEnableIRQ
// #define NVIC_DisableIRQ             __NVIC_DisableIRQ
// #define NVIC_GetPendingIRQ          __NVIC_GetPendingIRQ
// #define NVIC_SetPendingIRQ          __NVIC_SetPendingIRQ
// #define NVIC_ClearPendingIRQ        __NVIC_ClearPendingIRQ
// #define NVIC_GetActive              __NVIC_GetActive
// #define NVIC_SetPriority            __NVIC_SetPriority
#define NVIC_GetPriority            __NVIC_GetPriority
// #define NVIC_SystemReset            __NVIC_SystemReset

	void *zunoSysCall(uint8_t ct, uint8_t n, ...);
	__STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CONTROL, 2, IRQn, false);
	}
	__STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CONTROL, 2, IRQn, true);
	}
	__STATIC_INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CLEARPENDING, 1, IRQn);
	}
	__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_SETPRIORITY, 2, IRQn, priority);
	}
#endif // CMSIS_NVIC_VIRTUAL_H