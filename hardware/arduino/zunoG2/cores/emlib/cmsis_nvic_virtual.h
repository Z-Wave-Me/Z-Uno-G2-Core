#ifndef _TGGGGGGGGGGGGGGGGHJFYRDFIUJKLJughjhg_H
#define _TGGGGGGGGGGGGGGGGHJFYRDFIUJKLJughjhg_H
#include "ZUNO_CoreDefs.h"
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
#endif // _TGGGGGGGGGGGGGGGGHJFYRDFIUJKLJughjhg_H