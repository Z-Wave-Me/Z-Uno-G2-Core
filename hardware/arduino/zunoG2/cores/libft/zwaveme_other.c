#include <stdint.h>
#include <stdlib.h>
#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif

int *__errno(void) {
	static int						tempos = 0;

	return (&tempos);
}

static uint64_t _rand_number = 1;

void srand(unsigned int seed) {
	_rand_number = seed;
}

int rand(void) {
	uint64_t				tempos;

	// This multiplier was obtained from Knuth, D.E., "The Art of Computer Programming," Vol 2, Seminumerical Algorithms, Third Edition, Addison-Wesley, 1998, p. 106 (line 26) & p. 108 
	tempos = _rand_number * 6364136223846793005 + 1;
	_rand_number = tempos;
	return (int)((tempos >> 32) & RAND_MAX);
}

#ifdef __cplusplus
}
#endif