#include "Status.h"
#include "Threading.h"

uint32_t GetLastStatus(void) {
	uint32_t					*data;

	data = (uint32_t *)zunoThreadDataPtr(zunoGetCurrentThreadHandle());
	return (data[0x0]);
}

void SetLastStatus (uint32_t status) {
	uint32_t					*data;

	data = (uint32_t *)zunoThreadDataPtr(zunoGetCurrentThreadHandle());
	data[0x0] = status;
}