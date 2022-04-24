#include "Status.h"

static uint32_t _last_status = STATUS_SUCCESS;

uint32_t GetLastStatus(void) {
	return (_last_status);
}

void SetLastStatus (uint32_t status) {
	_last_status = status;
}