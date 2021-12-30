#ifndef EM_CORE_H
#define EM_CORE_H

#include "ZUNO_CoreDefs.h"

#define CORE_DECLARE_IRQ_STATE

/** CRITICAL style interrupt disable. */
#define CORE_CRITICAL_IRQ_DISABLE() zunoSysCall(ZUNO_SYSFUNC_ENTER_CRITICAL, 0);

/** CRITICAL style interrupt enable. */
#define CORE_CRITICAL_IRQ_ENABLE()  zunoSysCall(ZUNO_SYSFUNC_EXIT_CRITICAL, 0);

/** Convenience macro for implementing a CRITICAL section. */
#define CORE_CRITICAL_SECTION(yourcode) \
  {                                     \
    CORE_DECLARE_IRQ_STATE;             \
    CORE_ENTER_CRITICAL();              \
    {                                   \
      yourcode                          \
    }                                   \
    CORE_EXIT_CRITICAL();               \
  }

#define CORE_ENTER_CRITICAL()   zunoSysCall(ZUNO_SYSFUNC_ENTER_CRITICAL, 0);

/** Exit CRITICAL section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_EXIT_CRITICAL()     zunoSysCall(ZUNO_SYSFUNC_EXIT_CRITICAL, 0);

/** ATOMIC style interrupt disable. */
#define CORE_ATOMIC_IRQ_DISABLE()   zunoSysCall(ZUNO_SYSFUNC_ENTER_CRITICAL, 0);

/** ATOMIC style interrupt enable. */
#define CORE_ATOMIC_IRQ_ENABLE()    zunoSysCall(ZUNO_SYSFUNC_EXIT_CRITICAL, 0);

/** Convenience macro for implementing an ATOMIC section. */
#define CORE_ATOMIC_SECTION(yourcode) \
  {                                   \
    CORE_DECLARE_IRQ_STATE;           \
    CORE_ENTER_ATOMIC();              \
    {                                 \
      yourcode                        \
    }                                 \
    CORE_EXIT_ATOMIC();               \
  }

/** Enter ATOMIC section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_ENTER_ATOMIC()   zunoSysCall(ZUNO_SYSFUNC_ENTER_CRITICAL, 0);

/** Exit ATOMIC section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_EXIT_ATOMIC()    zunoSysCall(ZUNO_SYSFUNC_EXIT_CRITICAL, 0);
/** @} (end addtogroup core) */

#endif /* EM_CORE_H */