#include <stdint.h>
#include <stdlib.h>
#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif


static uint8_t _alphabet(uint8_t value) {
	if (value > 9)
		return (value - 10 + 'A');
	return (value + 0x30);
}

size_t zwaveme_utoa_base(size_t value, void *str, size_t base) {
	uint8_t				*b;
	uint8_t				*e;
	size_t				count;
	size_t				tempos;
	
	e = (uint8_t *)str;
	if (base >= 2 && base <= 36) {
		while (0xFF) {
			e++[0] = _alphabet(value % base);
			value = value / base;
			if (value == 0)
				break ;
		}
	}
	b = (uint8_t *)str;
	count = e - b;
	e[0] = 0;
	e--;
	while (b < e) {
		tempos = e[0];
		e[0] = b[0];
		b[0] = tempos;
		b++;
		e--;
	}
	return (count);
}

char *ltoa(long value, char *str, int base) {
	size_t						uvalue;
	size_t							i;
	
	i = 0;
	if (base == 10 && value < 0) {
		str[i++] = '-';
		uvalue = (size_t)-value;
	}
	else
		uvalue = (size_t)value;
	
	if (zwaveme_utoa_base(uvalue, &str[i], base) == 0)
		return (0);
	return (str - i);
}

char *ultoa(unsigned long value, char *str, int base) {
	if (zwaveme_utoa_base(value, str, base) == 0)
		return (0);
	return (str);
}


char *utoa(unsigned int value, char *str, int base) {
	return(ultoa((unsigned long)value, str, base));
}

char *itoa(int value, char *str, int base) {
	return (ltoa((long)value, str, base));
}

int atoi(const char *s) {
	return ((int)strtol(s, NULL, 10));
};

long atol(const char *s) {
	return ((long)strtol(s, NULL, 10));
};

#ifdef __cplusplus
}
#endif