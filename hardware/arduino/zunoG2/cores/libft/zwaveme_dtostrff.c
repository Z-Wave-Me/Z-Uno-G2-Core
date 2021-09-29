#include <stdint.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "zwaveme_libft.h"
#include "zwaveme_float_private.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t zwaveme_utoa_base(size_t value, void *str, size_t base);

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
				b[1] = 'O';
				b[2] = 'v';
				break ;
			case LibftFloatTypeInf:
				b[1] = 'I';
				b[2] = 'n';
				break ;
		}
		b[3] = 'F';
		b = b + 4;
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
	e = e + zwaveme_utoa_base(number, e, 10);
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
	lp->lenFractionNull = exp10;
	return (LibftFloatTypeNumber);
}

char *dtostrff(float value, unsigned long width, unsigned long prec, char *s) {
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
			if (prec >= lenFractionNull)
				prec = prec - lenFractionNull;
			else {
				lenFractionNull = prec;
				prec = 0;
			}
			s = (char *)((uint8_t *)memset(s, '0', lenFractionNull) + lenFractionNull);
			offset = floatEngine.lenFraction;
			if (prec >= offset)
				prec = prec - offset;
			else {
				offset = prec;
				prec = 0;
			}
			s = (char *)((uint8_t *)memcpy(s, &floatEngine.number[floatEngine.lenSingle], offset) + offset);
			s = (char *)((uint8_t *)memset(s, '0', prec) + prec);
		}
	}
	s[0] = 0;
	memset(save, ' ', width);
	return (save);
}

#ifdef __cplusplus
}
#endif