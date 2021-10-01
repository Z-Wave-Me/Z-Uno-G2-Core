#ifndef ZWAVEME_LIBFT_H
#define ZWAVEME_LIBFT_H

#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>
#include "zwaveme_printf.h"

#ifdef __cplusplus
extern "C" {
#endif

char *ultoa(unsigned long value, char *str, int base);
char *utoa(unsigned int value, char *str, int base);

char *ltoa(long value, char *str, int base);
char *itoa(int value, char *str, int base);


char *dtostrff(float value, unsigned long width, unsigned long prec, char *s);

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_LIBFT_H