#ifndef ZUNO_DEPENDENCINES_CC_H
#define ZUNO_DEPENDENCINES_CC_H

#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
#ifndef WITH_CC_TIME
#define WITH_CC_TIME
#endif
#endif

#ifdef WITH_CC_SWITCH_BINARY
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

#ifdef WITH_CC_SWITCH_MULTILEVEL
	#ifndef WITH_CC_BASIC
	#define WITH_CC_BASIC
	#endif
#endif

#endif // ZUNO_DEPENDENCINES_CC_H