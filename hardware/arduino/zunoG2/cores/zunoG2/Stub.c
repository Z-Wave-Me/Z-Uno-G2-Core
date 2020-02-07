#include "LLCore.h"
void * zunoSysCall(int vec, int num, ...)  __attribute__((section(".sketch_syscall")));
void * zunoSysCall(int vec, int num, ...) {
    vec++;
    return (void*) (num*vec);
}