#include "stdint.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "errno.h"
#include "limits.h"
#include "Libft.h"
#include "float.h"

/* Convert a string to a long integer. */
long strtol(const char *__restrict s, char **__restrict nptr, int base)
{
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	if (base < 0 || base == 1 || base > 36) {
		errno = EINVAL;
		return 0;
	}

	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'Z')
			c -= 'A' - 10;
		else if (c >= 'a' && c <= 'z')
			c -= 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim)) {
			any = -1;
		} else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (nptr != 0)
		*nptr = (char *) (any ? (char *)s - 1 : s);
	return (acc);
}

static uint8_t _alphabet(uint8_t value) {
	if (value > 9)
		return (value - 10 + 'A');
	return (value + 0x30);
}

static size_t _utoa_base(size_t value, void *str, size_t base) {
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
	
	if (_utoa_base(uvalue, &str[i], base) == 0)
		return (0);
	return (str - i);
}

char *ultoa(unsigned long value, char *str, int base) {
	if (_utoa_base(value, str, base) == 0)
		return (0);
	return (str);
}


/* Float */
typedef struct					LibftFloatValue_s
{
	union
	{
		float					value;
		uint32_t				uvalue;
	};
}								LibftFloatValue_t;

#define LIBFT_FLOAT_ENGINE_PRESC				(FLT_DIG + 1)//7

typedef enum			LibftFloatType_s
{
	LibftFloatTypeInf,
	LibftFloatTypeNan,
	LibftFloatTypeNull,
	LibftFloatTypeNumber
}						LibftFloatType_t;

typedef struct			LibftFloatEngine_s
{
	size_t				lenSingle;
	size_t				lenSingleNull;
	size_t				lenFraction;
	size_t				lenFractionNull;
	size_t				neg;
	uint8_t				number[LIBFT_FLOAT_ENGINE_PRESC + 1];//+1 - null
}						LibftFloatEngine_t;

size_t _floatEngineNotNumber(size_t neg, LibftFloatType_t type, uint8_t *b) {
	uint8_t							*save;

	save = b;
	if (type == LibftFloatTypeNan) {
		b[0] = 'N';
		b[1] = 'a';
		b[2] = 'N';
		b = b + 3;
	}
	else {
		if(neg != 0)
			b[0] = '-';
		else
			b[0] = '+';
		switch ((size_t)type) {
			case LibftFloatTypeNull:
				b[1] = '0';
				b = b + 2;
				break ;
			case LibftFloatTypeInf:
				b[1] = 'I';
				b[2] = 'n';
				b[3] = 'F';
				b = b + 4;
				break ;
		}
	}
	b[0] = 0;
	return (b - save);
}

static LibftFloatType_t _floatEngine(float value, LibftFloatEngine_t *lp) {
	static const uint32_t			table[] =
	{
		0xF0BDC21A, 0x3DA137D5, 0x9DC5ADA8, 0x2863C1F5, 0x6765C793, 0x1A784379, 0x43C33C19, 0xAD78EBC5,
		0x2C68AF0B, 0x71AFD498, 0x1D1A94A2, 0x4A817C80, 0xBEBC2000, 0x30D40000, 0x7D000000, 0x20000000,
		0x51EB851E, 0xD1B71758, 0x35AFE535, 0x89705F41, 0x232F3302, 0x5A126E1A, 0xE69594BE, 0x3B07929F,
		0x971DA050, 0x26AF8533, 0x63090312, 0xFD87B5F2, 0x40E75996, 0xA6274BBD, 0x2A890926, 0x6CE3EE76
	};
	LibftFloatValue_t				v;
	ssize_t							exp10;
	size_t							exponent;
	size_t							digit;
	size_t							i;
	uint32_t						fraction;
	uint32_t						t;
	size_t							number;
	size_t							lenNumber;
	size_t							tempos;
	uint8_t							*e;
	size_t							lenSingleNull;
	size_t							lenSingle;
	size_t							lenFractionNull;

	v.value = value;
	lp->neg = v.uvalue >> 31;
	exponent = (v.uvalue >> 23) & 0xFF;
	fraction = (v.uvalue & 0x7FFFFF) | 0x800000;
	if(exponent == 0) // don't care about a subnormals
		return (LibftFloatTypeNull);
	if (exponent == 0xFF) {
		if((fraction & 0x7FFFFF) != 0)
			return (LibftFloatTypeNan);
		return (LibftFloatTypeInf);
	}
	exp10 = ((((exponent >> 3)) * 77 + 63) >> 5) - 38;
	t = (uint32_t)(((uint64_t)(fraction << 8) * table[exponent / 8]) >> 32) + 1;
	t = t >> (7 - (exponent & 7));
	digit = (t >> 24) >> 4;
	while(digit == 0) {
		t = (t & 0xFFFFFFF) * 10;
		digit = (t >> 28) & 0xFF;
		exp10--;
	}
	number = 0;
	i = LIBFT_FLOAT_ENGINE_PRESC + 1;
	while ( i > 0) {
		digit = (uint8_t)(t >> 28);
		number = number * 10 + digit;
		t = (t & 0xFFFFFFF) * 10;
		i--;
	}
	tempos = number % 10;
	number = number / 10;
	if (tempos > 5)
		number++;
	e = &lp->number[0];
	e = e + _utoa_base(number, e, 10);
	while (e[-1] <= '0')
		e--;
	lenNumber = e - &lp->number[0];
	if (++exp10 >= 1) {
		if (lenNumber > (size_t)exp10)
			lenSingle = exp10;
		else
			lenSingle = lenNumber;
		lenNumber = lenNumber- lenSingle;
		lenSingleNull = exp10- lenSingle;
		exp10 = 0;
	}
	else {
		lenSingleNull = 0;
		lenSingle = 0;
	}
	lp->lenSingleNull = lenSingleNull;
	lp->lenSingle = lenSingle;
	lp->lenFraction = lenNumber;
	if (exp10 < 0)
		exp10 = -exp10;
	if ((size_t)exp10 >= lenNumber)
		lenFractionNull = exp10 - lenNumber;
	else
		lenFractionNull = 0;
	lp->lenFractionNull = lenFractionNull;
	return (LibftFloatTypeNumber);
}


char *dtostrf(float value, unsigned long width, unsigned long prec, char *s) {
	char							*save;
	size_t							offset;
	size_t							lenFractionNull;
	size_t							lenSingle;
	size_t							lenSingleNull;
	LibftFloatEngine_t				floatEngine;
	LibftFloatType_t				type;
	uint8_t							buff[6];

	save = s;
	if ((type = _floatEngine(value, &floatEngine)) != LibftFloatTypeNumber) {
		offset = _floatEngineNotNumber(floatEngine.neg, type, (uint8_t *)&buff[0]);
		width = (width > offset) ? width - offset : 0;
		s = (char *)((uint8_t *)memcpy(&s[width], &buff[0], offset) + offset);
	}
	else {
		lenSingle = floatEngine.lenSingle;
		lenSingleNull = floatEngine.lenSingleNull;
		offset = lenSingle + lenSingleNull + floatEngine.neg;
		if (prec != 0)
			offset = offset + prec + 1;//+1 '.'
		width = (width > offset) ? width - offset : 0;
		s = (char *)((uint8_t *)memcpy(&s[width], &floatEngine.number[0], lenSingle) + lenSingle);
		if (lenSingle == 0)
			lenSingleNull++;
		s = (char *)((uint8_t *)memset(s, '0', lenSingleNull) + lenSingleNull);
		if (prec != 0) {
			s++[0] = '.';
			lenFractionNull = floatEngine.lenFractionNull;
			offset = floatEngine.lenFraction;
			if (prec >= (lenFractionNull + offset))
				lenFractionNull = prec - offset;
			else if (lenFractionNull >= prec) {
				lenFractionNull = prec;
				offset = 0;
			}
			else
				offset = prec - lenFractionNull;
			s = (char *)((uint8_t *)memset(s, '0', lenFractionNull) + lenFractionNull);
			s = (char *)((uint8_t *)memcpy(s, &floatEngine.number[floatEngine.lenSingle], offset) + offset);
		}
	}
	s[0] = 0;
	memset(save, ' ', width);
	return (save);
}
