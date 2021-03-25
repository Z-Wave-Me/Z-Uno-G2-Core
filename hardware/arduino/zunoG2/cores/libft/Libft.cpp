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
#include "math.h"
#include "time.h"

int *__errno(void) {
	static int						tempos = 0;

	return (&tempos);
}

/* Convert a string to a long integer. */
long strtol(const char *s, char **nptr, int base)
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

#define LIBFT_FLOAT_NAN				(0x7F820000)
#define LIBFT_FLOAT_OVF(neg)		(neg << 31)
#define LIBFT_FLOAT_INF(neg)		(neg << 31 | 0x7F800000)

static float _numberToFloat(size_t number) {
	LibftFloatValue_t				v;

	v.uvalue = number;
	return (v.value);
}

/* Самый медленный, само больше места занимает */
/*
static float _packFloat(size_t neg, size_t single, size_t lenSingleNull, size_t fraction, size_t lenFraction, size_t lenFractionNull) {
	LibftFloatValue_t				v;

	v.value = ((float)single * powf((float)10.0, (float)lenSingleNull)) + ((float)fraction * powf((float)0.1, (float)(lenFractionNull + lenFraction)));
	v.uvalue = v.uvalue | (neg << 31);
	return (v.value);
}
*/

/* Чуть медленней и чуть больше места занимает чем на железных флотах, но искажение в флотах наступает позже гораздо, чем на хардверных флотах */
/*
static inline uint64_t __UMULL32 (uint32_t op1, uint32_t op2) {
	uint32_t				result0;
	uint32_t				result1;
	union					llreg_u
	{
		uint32_t			w32[2];
		uint64_t			w64;
	}						llr;

	__ASM volatile ("umull %0, %1, %2, %3" : "=r" (result0), "=r" (result1): "r" (op1), "r" (op2) );
	llr.w32[0] = result0;
	llr.w32[1] = result1;
	return(llr.w64);
}

static inline uint32_t __ADD32S (uint32_t op1, uint32_t op2) {
	uint32_t				result0;

	__ASM volatile ("adds %0, %1, %2" : "=r" (result0): "r" (op1), "r" (op2) );
	return(result0);
}

static inline uint32_t __ADC32S (uint32_t op1, uint32_t op2) {
	uint32_t				result0;

	__ASM volatile ("adcs %0, %1, %2" : "=r" (result0): "r" (op1), "r" (op2) );
	return(result0);
}

static inline uint32_t __ADC32SImmet (uint32_t op1) {
	uint32_t				result0;

	__ASM volatile ("adcs %0, %1, #0" : "=r" (result0): "r" (op1) );
	return(result0);
}
extern uint64_t gTest;

static float _packFloat(size_t neg, size_t single, size_t lenSingleNull, size_t fraction, size_t lenFraction, size_t lenFractionNull) {
	LibftFloatValue_t				v;
	uint32_t						mantissa;
	size_t							exponent;
	size_t							offset;
	float							vf;
	uint32_t						result0;
	uint32_t						result1;
	uint32_t						result2;
	uint32_t						result3;
	uint32_t						tempos;
	size_t							i;
	uint32_t						result[4];
	union							llreg_u
	{
		uint32_t					w32[2];
		uint64_t					w64;
	}								llr;

	vf = fraction;
	lenFraction = lenFraction + lenFractionNull;
	while (lenFraction-- != 0)
		vf = vf * (float)0.1;
	if ((mantissa = single) != 0) {
		if (lenSingleNull == 0) {
			exponent = 23;
			while (0xFF) {
				if ((mantissa & 0x800000) != 0)
					break ;
				mantissa = mantissa << 1;
				exponent--;
			}
		}
		else {
			result0 = mantissa;
			result1 = 0;
			result2 = 0;
			result3 = 0;
			while (lenSingleNull-- != 0) {
				llr.w64 = __UMULL32(result0, 10);
				result0 = llr.w32[0];
				tempos = llr.w32[1];
				llr.w64 = __UMULL32(result1, 10);
				result1 = __ADD32S(llr.w32[0], tempos);
				tempos = __ADC32SImmet(llr.w32[1]);
				llr.w64 = __UMULL32(result2, 10);
				result2 = __ADC32S(llr.w32[0], tempos);
				tempos = __ADC32SImmet(llr.w32[1]);
				llr.w64 = __UMULL32(result3, 10);
				result3 = __ADC32S(llr.w32[0], tempos);
			}
			result[0] = result0;
			result[1] = result1;
			result[2] = result2;
			result[3] = result3;
			i = 3;
			while (result[i] == 0)
				i--;
			tempos = result[i];
			if (i == 0) {
				i++;
				offset = 0;
			}
			else
				offset = 32;
			llr.w32[1] = result[i];
			llr.w32[0] = result[i - 1];
			while (tempos != 0) {
				tempos = tempos >> 1;
				offset++;
			}
			exponent = (i - 1) * 32 + offset - 1;
			llr.w64 = llr.w64 >> (offset - 24);
			mantissa = llr.w32[0];
		}
		mantissa = (mantissa ^ 0x800000) | ((((uint8_t)exponent + 0x7F) & 0xFF) << 23);
	}
	v.uvalue = mantissa;
	v.value = v.value + vf;
	v.uvalue = v.uvalue | (neg << 31);
	return (v.value);
}
*/

/* Самый быстрый, само меньше места занимает, но раньше чем на длиннай арифметики наступает искажение целай части  */
static float _packFloat(size_t neg, size_t single, size_t lenSingleNull, size_t fraction, size_t lenFraction, size_t lenFractionNull) {
	LibftFloatValue_t				v;
	float							vs;
	float							vf;

	vs = single;
	while (lenSingleNull-- != 0)
		vs = vs * (float)10.0;
	vf = fraction;
	lenFraction = lenFraction + lenFractionNull;
	while (lenFraction-- != 0)
		vf = vf * (float)0.1;
	v.value = vs + vf;
	v.uvalue = v.uvalue | (neg << 31);
	return (v.value);
}

static float _finishFloat(float value, const uint8_t *s, char **endptr) {
	if (endptr != NULL)
		endptr[0] = (char *)s;
	return (value);
}

static float _scientificFloat(char **endptr, const uint8_t *s, size_t neg, size_t single, size_t lenSingleNull, size_t fraction, size_t lenFraction, size_t lenFractionNull) {
	size_t					litter;
	size_t					negScientific;
	size_t					scientific;
	float					multiplier;
	float					value;
	
	negScientific = s[0];
	if (negScientific == '+' || negScientific == '-')
		s++;
	while (s[0] == '0')
		s++;
	scientific = 0;
	while (0xFF) {
		litter = s[0] - '0';
		if (litter > 9 || scientific > FLT_MAX_10_EXP)
			break ;
		scientific = scientific * 10 + litter;
		s++;
	}
	litter = s[0];
	if ((litter - '0') <= 9)//overlow
		return (_numberToFloat(LIBFT_FLOAT_NAN));
	if (negScientific != '-')
		multiplier = 10.0;
	else
		multiplier = 0.1;
	value = _packFloat(neg, single, lenSingleNull, fraction, lenFraction, lenFractionNull);
	while (scientific-- != 0)
		value = value * multiplier;
	return (_finishFloat(value, s, endptr));
}

static uint32_t _hexadecimalFloatMantissa(uint32_t mantissa, const uint8_t **str) {
	size_t						litter;
	const uint8_t				*s;

	s = str[0];
	while (0xFF) {
		litter = tolower(s[0]);
		if (litter >= '0' && litter <= '9')
			litter = litter - '0';
		else if (litter >= 'a' && litter <= 'f')
			litter = litter - 'a';
		else
			break ;
		s++;
		mantissa = mantissa * 0x10 + litter;
		if ((mantissa & 0x800000) != 0)
			break ;
	}
	str[0] = s;
	return (mantissa);
}

static float _hexadecimalFloat(char **endptr, const uint8_t *s, size_t neg) {
	uint32_t					mantissa;
	uint32_t					exponent;
	size_t						offset;
	size_t						tempos;
	size_t						litter;

	while (s[0] == '0')
		s++;
	mantissa = _hexadecimalFloatMantissa(0, &s);
	offset = 0;
	tempos = mantissa;
	while (tempos != 0) {
		tempos = tempos >> 1;
		offset++;
	}
	if (s[0] != '.')
		return (_numberToFloat(LIBFT_FLOAT_NAN));
	s++;
	mantissa = _hexadecimalFloatMantissa(mantissa, &s);
	if (s[0] != 'p')
		return (_numberToFloat(LIBFT_FLOAT_NAN));
	s++;
	while (s[0] == '0')
		s++;
	exponent = 0;
	while (exponent <= FLT_MAX_EXP) {
		litter = s[0] - '0';
		if (litter > 9)
			break ;
		exponent = exponent * 10 + litter;
		s++;
	}
	exponent = exponent + offset;
	litter = s[0] - '0';
	if (litter <= 9 || exponent > FLT_MAX_EXP)
		return (_numberToFloat(LIBFT_FLOAT_NAN));
	if (mantissa == 0)
		return (_finishFloat(_numberToFloat(LIBFT_FLOAT_OVF(neg)), s, endptr));
	while (0xFF) {
		if ((mantissa & 0x800000) != 0)
			break ;
		mantissa = mantissa << 1;
	}
	return (_finishFloat(_numberToFloat((neg << 31) | (mantissa ^ 0x800000) | ((((uint8_t)exponent + (0x7F - 1)) & 0xFF) << 23)), s, endptr));
}

float strtof(const char *nptr, char **endptr) {
	const uint8_t				*s;
	size_t						litter;
	size_t						neg;
	size_t						single;
	size_t						lenSingle;
	size_t						lenSingleNull;
	size_t						fraction;
	size_t						lenFraction;
	size_t						lenFractionNull;
	size_t						max;
	size_t						tempos;

	if (endptr != NULL)
		endptr[0] = (char *)nptr;
	s = (uint8_t *)nptr;
	while (isspace(s[0]) == true)
		s++;
	neg = 0;
	while (0xFF) {
		if ((litter = s[0]) == '+')
			neg = 0;
		else if (litter == '-')
			neg = 1;
		else
			break ;
		s++;
	}
	if ((litter = tolower(s[0])) == 'i') {
		if (tolower(s[0]) == 'n' && tolower(s[1]) == 'f')
			return (_finishFloat(_numberToFloat(LIBFT_FLOAT_INF(neg)), s, endptr));
		else
			return (_numberToFloat(LIBFT_FLOAT_NAN));
	}
	else if (litter == 'o') {
		if (tolower(s[0]) == 'v' && tolower(s[1]) == 'f')
			return (_finishFloat(_numberToFloat(LIBFT_FLOAT_OVF(neg)), s, endptr));
		else
			return (_numberToFloat(LIBFT_FLOAT_NAN));
	}
	else if (litter == 'n')
		return (_finishFloat(_numberToFloat(LIBFT_FLOAT_NAN), s, endptr));
	while (s[0] == '0')
		s++;
	litter = tolower(s[0]);
	if (litter == 'x' && s != (uint8_t *)nptr && s[-1] == '0')
		return (_hexadecimalFloat(endptr, ++s, neg));
	single = 0;
	lenSingle = 0;
	while (lenSingle < LIBFT_FLOAT_ENGINE_PRESC) {
		litter = s[0] - '0';
		if (litter > 9)
			break ;
		single = single * 10 + litter;
		s++;
		lenSingle++;
	}
	lenSingleNull = 0;
	max = FLT_MAX_10_EXP - lenSingle;
	while (lenSingleNull < max) {
		litter = s[0] - '0';
		if (litter > 9)
			break ;
		s++;
		lenSingleNull++;
	}
	if ((litter = s[0]) == '.' || litter == ',') {
		s++;
		max = max - lenSingleNull;
		lenFractionNull = 0;
		while (lenFractionNull < max && s[0] == '0') {
			s++;
			lenFractionNull++;
		}
		max = max - lenFractionNull;
		if (lenSingle < LIBFT_FLOAT_ENGINE_PRESC)
			tempos = LIBFT_FLOAT_ENGINE_PRESC - lenSingle;
		else
			tempos = 0;
		if (max > tempos)
			max = tempos;
		fraction = 0;
		lenFraction = 0;
		while (lenFraction < LIBFT_FLOAT_ENGINE_PRESC) {
			litter = s[0] - '0';
			if (litter > 9)
				break ;
			fraction = fraction * 10 + litter;
			s++;
			lenFraction++;
		}
		while (0xFF) {
			litter = s[0] - '0';
			if (litter > 9)
				break ;
			s++;
		}
		if (tolower(s[0]) == 'e')
			return (_scientificFloat(endptr, ++s, neg, single, lenSingleNull, fraction, lenFraction, lenFractionNull));
	}
	else if (lenSingleNull == max)
		return (_numberToFloat(LIBFT_FLOAT_NAN));
	else {
		fraction = 0;
		lenFraction = 0;
		lenFractionNull = 0;
	}
	return (_finishFloat(_packFloat(neg, single, lenSingleNull, fraction, lenFraction, lenFractionNull), s, endptr));
}

int rand(void) {
	static uint64_t			number = 1;
	uint64_t				tempos;

	/* This multiplier was obtained from Knuth, D.E., "The Art of Computer Programming," Vol 2, Seminumerical Algorithms, Third Edition, Addison-Wesley, 1998, p. 106 (line 26) & p. 108 */
	tempos = number * 6364136223846793005 + 1;
	number = tempos;
	return (int)((tempos >> 32) & RAND_MAX);
}

typedef struct					ZMallocTop_s
{
	uint16_t					alloc_prev;//Если ноль то нечего перед этим листом не выделенно
	uint16_t					alloc_size;
}								ZMallocTop_t;

typedef struct					ZMallocFreeList_s
{
	ZMallocTop_t				top;
	uint16_t					next;
	uint16_t					prev;
}								ZMallocFreeList_t;


#define MALLOC_HEAP_START				((void *)&_heap)
#define MALLOC_HEAP_END					((void *)&__heap_end__)
#define MALLOC_HEAP_SIZE				((size_t)&__heap_size__)
#define MALLOC_STATUS_BUSY				0x8000
#define MALLOC_OFFSET					((size_t)&__bss_start__)

extern unsigned long __bss_start__;
extern unsigned long __heap_start__;
extern unsigned long __heap_end__;
extern unsigned long __heap_size__;

static uint8_t _heap[sizeof(ZMallocFreeList_t)] __attribute__ ((section(".heap")));
static ZMallocFreeList_t *_malloc_free_list = 0;

static size_t _mallocFullSize(size_t size) {
	size = (size + ((sizeof(size_t) - 1) + sizeof(ZMallocTop_t))) & (0 - sizeof(size_t));
	if (size < (sizeof(ZMallocFreeList_t)))
		size = sizeof(ZMallocFreeList_t);
	return (size);
}

static void *_malloc(size_t size) {
	ZMallocFreeList_t					*freeList;
	ZMallocFreeList_t					*list;
	ZMallocFreeList_t					*list_new;
	ZMallocFreeList_t					*list_tmp;
	ZMallocFreeList_t					*list_prev;
	ZMallocFreeList_t					*list_next;
	size_t								min;
	size_t								tempos;
	size_t								size_free;

	if ((freeList = _malloc_free_list) == 0) {
		freeList = (ZMallocFreeList_t *)MALLOC_HEAP_START;
		_malloc_free_list = freeList;
		freeList->top.alloc_size = MALLOC_HEAP_SIZE;
	}
	size = _mallocFullSize(size);
	list = (ZMallocFreeList_t *)MALLOC_OFFSET;
	min = (size_t)(-1);
	while (freeList != (ZMallocFreeList_t *)MALLOC_OFFSET) {
		if ((tempos = freeList->top.alloc_size) >= size && tempos <= min) {
			min = tempos;
			list = freeList;
			if (min == size)
				break ;
		}
		freeList = (ZMallocFreeList_t *)(MALLOC_OFFSET + freeList->next);
	}
	if (list == (ZMallocFreeList_t *)MALLOC_OFFSET)
		return (0);
	if (min >= (size + sizeof(ZMallocFreeList_t))) {
		size_free = min - size;
		list_new = list;
		list_new->top.alloc_size = size_free;
		list = (ZMallocFreeList_t *)((size_t)list + size_free);
		list->top.alloc_prev = size_free;
		list->top.alloc_size = size;
		list_tmp = (ZMallocFreeList_t *)((size_t)list + size);
		if (list_tmp <= (ZMallocFreeList_t *)((size_t)MALLOC_HEAP_END - sizeof(ZMallocFreeList_t)))
			list_tmp->top.alloc_prev = size;
	}
	else {
		list_next = (ZMallocFreeList_t *)(list->next + (size_t)MALLOC_OFFSET);
		list_prev = (ZMallocFreeList_t *)(list->prev + (size_t)MALLOC_OFFSET);
		list_new = (ZMallocFreeList_t *)MALLOC_OFFSET;
		if (list_next != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_next->prev = list->prev;
			list_new = list_next;
		}
		if (list_prev != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_prev->next = list->next;
			list_new = list_prev;
		}
		_malloc_free_list = list_new;
	}
	list->top.alloc_size = list->top.alloc_size | MALLOC_STATUS_BUSY;
	return ((uint8_t *)list + sizeof(ZMallocTop_t));
}

void *malloc(size_t size) {
	void			*tmp;

	tmp = _malloc(size);
	return (tmp);
}

static void _mallocListMerge(ZMallocFreeList_t *main, ZMallocFreeList_t *extra) {
	ZMallocFreeList_t					*list_next;
	ZMallocFreeList_t					*list_prev;

	main->top.alloc_size = main->top.alloc_size + extra->top.alloc_size;
	list_next = (ZMallocFreeList_t *)(extra->next + (size_t)MALLOC_OFFSET);
	list_prev = (ZMallocFreeList_t *)(extra->prev + (size_t)MALLOC_OFFSET);
	if (list_next != (ZMallocFreeList_t *)MALLOC_OFFSET)
		list_next->prev = extra->prev;
	if (list_prev != (ZMallocFreeList_t *)MALLOC_OFFSET)
		list_prev->next = extra->next;
}

static void _free(void *ptr) {
	ZMallocFreeList_t					*freeList;
	ZMallocFreeList_t					*list;
	ZMallocFreeList_t					*list_tmp;
	size_t								tempos;

	if (ptr <= MALLOC_HEAP_START || ptr >= MALLOC_HEAP_END)
		return ;
	list = (ZMallocFreeList_t *)((uint8_t *)ptr - sizeof(ZMallocTop_t));
	list->top.alloc_size = list->top.alloc_size ^ MALLOC_STATUS_BUSY;
	list->prev = 0;
	if ((freeList = _malloc_free_list) == (ZMallocFreeList_t *)MALLOC_OFFSET)
		list->next = 0;
	else {
		freeList->prev = (size_t)list - (size_t)MALLOC_OFFSET;
		list->next = (size_t)freeList - (size_t)MALLOC_OFFSET;
	}
	while ((tempos = list->top.alloc_prev) != 0) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list - tempos);
		if ((list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0)
			break ;
		_mallocListMerge(list_tmp, list);
		list = list_tmp;
	}
	while (0xFF) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list + list->top.alloc_size);
		if (list_tmp > (ZMallocFreeList_t *)((size_t)MALLOC_HEAP_END - sizeof(ZMallocFreeList_t)) || (list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0)
			break ;
		_mallocListMerge(list, list_tmp);
	}
	_malloc_free_list = list;
}

void free(void *ptr) {
	_free(ptr);
}

void *realloc(void *ptr, size_t size) {
	ZMallocFreeList_t					*list;
	size_t								sizeOld;
	size_t								sizeNew;
	void								*ptrNew;

	if (ptr == 0)
		return (malloc(size));
	if (size == 0) {
		free(ptr);
		return (0);
	}
	sizeNew = _mallocFullSize(size);
	list = (ZMallocFreeList_t *)((uint8_t *)ptr - sizeof(ZMallocTop_t));
	sizeOld = list->top.alloc_size ^ MALLOC_STATUS_BUSY;
	if (sizeOld >= sizeNew)
		return (ptr);
	if ((ptrNew = malloc(sizeNew)) == 0)
		return (0);
	memcpy(ptrNew, ptr, size);
	free(ptr);
	return (ptrNew);
}

void *reallocarray (void *ptr, size_t nmemb, size_t size) {
	size_t						tempos;

	if (__builtin_mul_overflow (nmemb, size, &tempos)) {
		errno = ENOMEM;
		return (0);
	}
	return (realloc(ptr, tempos));
}

void zcfree(void *ptr) {
	free(ptr);
}

void *calloc(size_t nmemb, size_t size) {
	size_t						tempos;
	void						*tmp;

	if (__builtin_mul_overflow (nmemb, size, &tempos)) {
		errno = ENOMEM;
		return (0);
	}
	if ((tmp = malloc(tempos)) == 0)
		return (0);
	memset(tmp, 0, tempos);
	return (tmp);
}

void malloc_stats(void) {
	ZMallocFreeList_t					*freeList;
	size_t								freeBytes;
	size_t								i;

	dprintf(0, "system bytes     = %10u\n", MALLOC_HEAP_SIZE);
	freeList = _malloc_free_list;
	freeBytes = 0;
	i = 0;
	if (freeList != 0) {
		while (freeList != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			i++;
			freeBytes = freeBytes + freeList->top.alloc_size;
			freeList = (ZMallocFreeList_t *)(MALLOC_OFFSET + freeList->next);
		}
	}
	dprintf(0, "in use bytes     = %10u\n", MALLOC_HEAP_SIZE - freeBytes);
	dprintf(0, "free blocks      = %10u\n", i);
}

typedef struct				ZauxiliaryDiv_s
{
	union
	{
		uint64_t				value;
		struct
		{
			uint32_t			minor;
			uint32_t			major;
		};
	};
}							ZauxiliaryDiv_t;

static uint64_t _div(ZauxiliaryDiv_t dividend, ZauxiliaryDiv_t divisor) {
	uint32_t					offset;
	ZauxiliaryDiv_t				out;
	ZauxiliaryDiv_t				saveDivisor;

	if (dividend.major == 0) 
		return (dividend.minor / divisor.minor);
	saveDivisor.minor = divisor.minor;
	out.value = 0;
	offset = (31 - __builtin_clz(dividend.major)) + __builtin_clz(divisor.minor) + 1;
	divisor.value = divisor.value << offset;
	while (dividend.major != 0) {
		out.minor = out.minor << 1;
		if (dividend.value >= divisor.value) {
			dividend.value -= divisor.value;
			out.minor = out.minor | 1;
		}
		divisor.value = divisor.value >> 1;
	}
	out.value = out.value << (offset - 31 + __builtin_clz(out.minor));
	out.minor |= dividend.minor / saveDivisor.minor;
	return (out.value);
}

static uint64_t zdiv(uintmax_t dividend, uintmax_t divisor) {
	ZauxiliaryDiv_t				dividendTwo;
	ZauxiliaryDiv_t				divisorTwo;

	dividendTwo.value = dividend;
	divisorTwo.value = divisor;
	return (_div(dividendTwo, divisorTwo));
}

#define SECSPERMIN	60L
#define MINSPERHOUR	60L
#define HOURSPERDAY	24L
#define SECSPERHOUR	(SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY	(SECSPERHOUR * HOURSPERDAY)
#define DAYSPERWEEK	7
#define MONSPERYEAR	12

#define YEAR_BASE	1900
#define EPOCH_YEAR      1970
#define EPOCH_WDAY      4
#define EPOCH_YEARS_SINCE_LEAP 2
#define EPOCH_YEARS_SINCE_CENTURY 70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

/* Move epoch from 01.01.1970 to 01.03.0000 (yes, Year 0) - this is the first
 * day of a 400-year long "era", right after additional day of leap year.
 * This adjustment is required only for date calculation, so instead of
 * modifying time_t value (which would require 64-bit operations to work
 * correctly) it's enough to adjust the calculated number of days since epoch.
 */
#define EPOCH_ADJUSTMENT_DAYS	719468L
/* year to which the adjustment was made */
#define ADJUSTED_EPOCH_YEAR	0
/* 1st March of year 0 is Wednesday */
#define ADJUSTED_EPOCH_WDAY	3
/* there are 97 leap years in 400-year periods. ((400 - 97) * 365 + 97 * 366) */
#define DAYS_PER_ERA		146097L
/* there are 24 leap years in 100-year periods. ((100 - 24) * 365 + 24 * 366) */
#define DAYS_PER_CENTURY	36524L
/* there is one leap year every 4 years */
#define DAYS_PER_4_YEARS	(3 * 365 + 366)
/* number of days in a non-leap year */
#define DAYS_PER_YEAR		365
/* number of days in January */
#define DAYS_IN_JANUARY		31
/* number of days in non-leap February */
#define DAYS_IN_FEBRUARY	28
/* number of years per era */
#define YEARS_PER_ERA		400

struct tm *gmtime_r(const time_t *tim_p, struct tm *res) {
	long days, rem;
	const time_t lcltime = *tim_p;
	int era, weekday, year;
	unsigned erayear, yearday, month, day;
	unsigned long eraday;

	days = zdiv(lcltime, SECSPERDAY);
	rem = (lcltime - (days * SECSPERDAY));
	days = days + EPOCH_ADJUSTMENT_DAYS;
	if (rem < 0) {
		rem += SECSPERDAY;
		--days;
	}
	/* compute hour, min, and sec */
	res->tm_hour = (int) (rem / SECSPERHOUR);
	rem %= SECSPERHOUR;
	res->tm_min = (int)(rem / SECSPERMIN);
	res->tm_sec = (int)(rem % SECSPERMIN);
	/* compute day of week */
	if ((weekday = ((ADJUSTED_EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
		weekday += DAYSPERWEEK;
	res->tm_wday = weekday;
	/* compute year, month, day & day of year */
	/* for description of this algorithm see
	* http://howardhinnant.github.io/date_algorithms.html#civil_from_days */
	era = (days >= 0 ? days : days - (DAYS_PER_ERA - 1)) / DAYS_PER_ERA;
	eraday = days - era * DAYS_PER_ERA;/* [0, 146096] */
	erayear = (eraday - eraday / (DAYS_PER_4_YEARS - 1) + eraday / DAYS_PER_CENTURY - eraday / (DAYS_PER_ERA - 1)) / 365;/* [0, 399] */
	yearday = eraday - (DAYS_PER_YEAR * erayear + erayear / 4 - erayear / 100);/* [0, 365] */
	month = (5 * yearday + 2) / 153;/* [0, 11] */
	day = yearday - (153 * month + 2) / 5 + 1;	/* [1, 31] */
	month += month < 10 ? 2 : -10;
	year = ADJUSTED_EPOCH_YEAR + erayear + era * YEARS_PER_ERA + (month <= 1);
	res->tm_yday = yearday >= DAYS_PER_YEAR - DAYS_IN_JANUARY - DAYS_IN_FEBRUARY ? yearday - (DAYS_PER_YEAR - DAYS_IN_JANUARY - DAYS_IN_FEBRUARY) : yearday + DAYS_IN_JANUARY + DAYS_IN_FEBRUARY + isleap(erayear);
	res->tm_year = year - YEAR_BASE;
	res->tm_mon = month;
	res->tm_mday = day;
	res->tm_isdst = 0;
	return (res);
}

#define _SEC_IN_MINUTE 60L
#define _SEC_IN_HOUR 3600L
#define _SEC_IN_DAY 86400L

static const int DAYS_IN_MONTH[12] =
{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#define _DAYS_IN_MONTH(x) ((x == 1) ? days_in_feb : DAYS_IN_MONTH[x])

static const int _DAYS_BEFORE_MONTH[12] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

#define _ISLEAP(y) (((y) % 4) == 0 && (((y) % 100) != 0 || (((y)+1900) % 400) == 0))
#define _DAYS_IN_YEAR(year) (_ISLEAP(year) ? 366 : 365)

static void 
validate_structure (struct tm *tim_p)
{
  div_t res;
  int days_in_feb = 28;

  /* calculate time & date to account for out of range values */
  if (tim_p->tm_sec < 0 || tim_p->tm_sec > 59)
    {
      res = div (tim_p->tm_sec, 60);
      tim_p->tm_min += res.quot;
      if ((tim_p->tm_sec = res.rem) < 0)
	{
	  tim_p->tm_sec += 60;
	  --tim_p->tm_min;
	}
    }

  if (tim_p->tm_min < 0 || tim_p->tm_min > 59)
    {
      res = div (tim_p->tm_min, 60);
      tim_p->tm_hour += res.quot;
      if ((tim_p->tm_min = res.rem) < 0)
	{
	  tim_p->tm_min += 60;
	  --tim_p->tm_hour;
        }
    }

  if (tim_p->tm_hour < 0 || tim_p->tm_hour > 23)
    {
      res = div (tim_p->tm_hour, 24);
      tim_p->tm_mday += res.quot;
      if ((tim_p->tm_hour = res.rem) < 0)
	{
	  tim_p->tm_hour += 24;
	  --tim_p->tm_mday;
        }
    }

  if (tim_p->tm_mon < 0 || tim_p->tm_mon > 11)
    {
      res = div (tim_p->tm_mon, 12);
      tim_p->tm_year += res.quot;
      if ((tim_p->tm_mon = res.rem) < 0)
        {
	  tim_p->tm_mon += 12;
	  --tim_p->tm_year;
        }
    }

  if (_DAYS_IN_YEAR (tim_p->tm_year) == 366)
    days_in_feb = 29;

  if (tim_p->tm_mday <= 0)
    {
      while (tim_p->tm_mday <= 0)
	{
	  if (--tim_p->tm_mon == -1)
	    {
	      tim_p->tm_year--;
	      tim_p->tm_mon = 11;
	      days_in_feb =
		((_DAYS_IN_YEAR (tim_p->tm_year) == 366) ?
		 29 : 28);
	    }
	  tim_p->tm_mday += _DAYS_IN_MONTH (tim_p->tm_mon);
	}
    }
  else
    {
      while (tim_p->tm_mday > _DAYS_IN_MONTH (tim_p->tm_mon))
	{
	  tim_p->tm_mday -= _DAYS_IN_MONTH (tim_p->tm_mon);
	  if (++tim_p->tm_mon == 12)
	    {
	      tim_p->tm_year++;
	      tim_p->tm_mon = 0;
	      days_in_feb =
		((_DAYS_IN_YEAR (tim_p->tm_year) == 366) ?
		 29 : 28);
	    }
	}
    }
}

time_t 
mktime (struct tm *tim_p)
{
  time_t tim = 0;
  long days = 0;
  int year;

  /* validate structure */
  validate_structure (tim_p);

  /* compute hours, minutes, seconds */
  tim += tim_p->tm_sec + (tim_p->tm_min * _SEC_IN_MINUTE) +
    (tim_p->tm_hour * _SEC_IN_HOUR);

  /* compute days in year */
  days += tim_p->tm_mday - 1;
  days += _DAYS_BEFORE_MONTH[tim_p->tm_mon];
  if (tim_p->tm_mon > 1 && _DAYS_IN_YEAR (tim_p->tm_year) == 366)
    days++;

  /* compute day of the year */
  tim_p->tm_yday = days;

  if (tim_p->tm_year > 10000 || tim_p->tm_year < -10000)
      return (time_t) -1;

  /* compute days in other years */
  if ((year = tim_p->tm_year) > 70)
    {
      for (year = 70; year < tim_p->tm_year; year++)
	days += _DAYS_IN_YEAR (year);
    }
  else if (year < 70)
    {
      for (year = 69; year > tim_p->tm_year; year--)
	days -= _DAYS_IN_YEAR (year);
      days -= _DAYS_IN_YEAR (year);
    }

  /* compute total seconds */
  tim += (time_t)days * _SEC_IN_DAY;
  return tim;
}
