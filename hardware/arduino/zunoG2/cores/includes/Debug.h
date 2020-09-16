#ifndef DEBUG_H
#define DEBUG_H

#ifndef LOGGING_UART 
	#define LOGGING_UART Serial0
#endif

#ifndef ASSERT_DBG
	#define EFM_ASSERT(expr)		((void)(expr))
#else
	#define EFM_ASSERT(expr)		if (expr == true) {(void)0;}else{LOGGING_UART.print("Error!!!: "); LOGGING_UART.print(__FILE__); LOGGING_UART.print(" "); LOGGING_UART.println(__LINE__);}
#endif

#endif //DEBUG_H