#include "em_wdog.h"

void *zunoSysCall(uint8_t ct, uint8_t n, ...) __attribute__((optimize(0), section(".sketch_syscall")));
void *zunoSysCall(uint8_t ct, uint8_t n, ...) {
	(void)ct;
	(void)n;
	return (0);
}