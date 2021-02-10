#ifndef NEW_H
#define NEW_H

#include <stdlib.h>


inline void *operator new(size_t size) {return (malloc(size));};
inline void *operator new[](size_t size) {return (malloc(size));};
inline void operator delete(void *ptr) {free(ptr);};
inline void operator delete[](void *ptr) {free(ptr);};
inline void operator delete(void *ptr, size_t size) {free(ptr); (void)size;};
inline void operator delete[](void *ptr, size_t size) {free(ptr); (void)size;};

#endif//NEW_H

