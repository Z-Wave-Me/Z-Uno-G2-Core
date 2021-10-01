#include <stdint.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include "zwaveme_libft.h"
#include "zwaveme_float_private.h"

#ifdef __cplusplus
extern "C" {
#endif


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


#ifdef __cplusplus
}
#endif