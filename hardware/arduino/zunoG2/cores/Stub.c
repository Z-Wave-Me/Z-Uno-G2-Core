#include "Arduino.h"
#include "LLCore.h"
/*
// Is not needed anymore
void * zunoSysCall(int vec, int num, ...)  __attribute__((section(".sketch_syscall")));
void * zunoSysCall(int vec, int num, ...) {
    vec++;
    return (void*) (num*vec);
}
*/

void *zunoSysCall(uint8_t ct, uint8_t n, ...) __attribute__((section(".sketch_syscall")));
void *zunoSysCall(uint8_t ct, uint8_t n, ...) {
	(void)ct;
	(void)n;
	return (0);
}