#ifndef DEBUG_H
#define DEBUG_H

#include "Custom_defs.h"

#ifndef LOGGING_UART
	#define LOGGING_UART Serial0
#endif

#define DEBUG_MESSAGE_WARNING				"***WARN"

#endif //DEBUG_H