#include "stdint.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "Zauxiliary.h"

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

// size_t	gTest;
// size_t	gTest2;
// size_t	gTest3;

// static uint64_t divTestTwo(ZauxiliaryDiv_t dividend, ZauxiliaryDiv_t divisor) {
// 	uint32_t					offset;
// 	ZauxiliaryDiv_t				out;
// 	ZauxiliaryDiv_t				saveDivisor;

// 	if (dividend.major == 0) {
// 		if (divisor.major != 0)
// 			dividend.minor = 0;
// 		else
// 			dividend.minor = dividend.minor / divisor.minor;
// 		return (dividend.value);
// 	}
// 	saveDivisor.value = divisor.value;
// 	out.value = 0;
// 	if (divisor.major == 0) {
// 		offset = (31 - __builtin_clz(dividend.major)) + __builtin_clz(divisor.minor) + 1;
// 		divisor.value = divisor.value << offset;
// 		while (dividend.major != 0) {
// 			out.minor = out.minor << 1;
// 			if (dividend.value >= divisor.value) {
// 				dividend.value -= divisor.value;
// 				out.minor = out.minor | 1;
// 			}
// 			divisor.value = divisor.value >> 1;
// 		}
// 		out.value = out.value << (offset - 31 + __builtin_clz(out.minor));
// 		out.minor |= dividend.minor / saveDivisor.minor;
// 	}
// 	else {
// 		offset = __builtin_clz(divisor.major) - __builtin_clz(dividend.major);
// 		divisor.value = divisor.value << offset;
// 		while (dividend.major >= saveDivisor.major) {
// 			out.value = out.value << 1;
// 			if (dividend.value >= divisor.value) {
// 				dividend.value -= divisor.value;
// 				out.minor = out.minor | 1;
// 			}
// 			offset--;
// 			divisor.value = divisor.value >> 1;
// 		}
// 		out.value = out.value << (offset + 1);
// 	}
// 	return (out.value);
// }

// static uint64_t divTest(uint64_t dividend, uint64_t divisor) {
// 	ZauxiliaryDiv_t				dividendTwo;
// 	ZauxiliaryDiv_t				divisorTwo;

// 	dividendTwo.value = dividend;
// 	divisorTwo.value = divisor;
// 	return (divTestTwo(dividendTwo, divisorTwo));
// }

// uint64_t test(uint64_t dividend, uint64_t divisor) {
// 	return (dividend / divisor);
// }

// uint64_t test2(uint64_t dividend, uint64_t divisor) {
// 	return (divTest(dividend , divisor));
// }

// #include "Zauxiliary.h"

// static uint8_t fhghjh[0x400];

// ssize_t				tt;

// ssize_t write(int fd, const void *buf, size_t count) {
// 	return (Serial0.write((const uint8_t*)buf, count));
// }

// void setup() {
// 	Serial0.begin(115200);
// 	Serial0.println("Setup");
// }

// size_t time;
// size_t count;

// extern size_t gTest;
// extern size_t gTest2;
// extern size_t gTest3;

// #define TEST_COUNT_TTT		100000
// #define TEST_COUNT_NUMBER	0x7FFFFFFFFFFF
// #define TEST_COUNT_NUMBER2	0x2

// void loop() {
// 	// Serial0.println("Gss: ");
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);

// 	// Serial0.println("My: ");
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test2(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test2(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);
// 	// time = millis();
// 	// count = 0;
// 	// while (count++ < TEST_COUNT_TTT)
// 	// 	test2(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2);
// 	// Serial0.println(millis() - time);

// 	Serial0.println((size_t)test(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2));
// 	Serial0.println((size_t)test2(TEST_COUNT_NUMBER, TEST_COUNT_NUMBER2));
// 	// Serial0.println(gTest);
// 	// Serial0.println(gTest2);
// 	// Serial0.println(gTest3);
// 	// tt = (int8_t)0xAA;
// 	// tt = (uint8_t)0xAA;
// 	//Serial0.println(Zdprintf(0, "12345678A%20.7s ", "ghjghjgjgh"));
// 	//Serial0.println(Serial0.printf("12345678A%20.7s ", "ghjghjgjgh"));
// 	Serial0.println("Loop");
// 	delay(1000);
// }

int		atoi(const char *str) {
	register int		tmp;
	register uintmax_t	out;
	register size_t		i;

	out = 0;
	tmp = 1;
	while (str[0] == ' ' || str[0] == '\n' || str[0] == '\t' ||
			str[0] == '\v' || str[0] == '\f' || str[0] == '\r')
		str++;
	if (str[0] == '-')
	{
		tmp = -1;
		str++;
	}
	else if (str[0] == '+')
		str++;
	i = 0;
	while (str[i] >= 0x30 && str[i] <= 0x39)
		out = out * 10 + str[i++] - 0x30;
	if (i <= 19)
		return ((int)(out * tmp));
	if (out - 9223372036854775807 >= 1)
		return ((tmp == -1) ? 0 : -1);
	return (tmp > 0 ? -1 : 0);
}

static int	fn_stub(char *s, size_t tmp)
{
	if (tmp >= 0x800)
	{
		s[0] = (char)(tmp >> 0xC) | 0xE0;
		s[1] = (char)((tmp >> 0x6) & 0x3F) | 0x80;
		s[2] = (char)((tmp & 0x3F) | 0x80);
		return (3);
	}
	s[0] = (char)(tmp >> 0x6) | 0xC0;
	s[1] = (char)((tmp & 0x3F) | 0x80);
	return (2);
}

int			wctomb(char *s, wchar_t wchar) {
	size_t	tmp;

	if (s == 0)//Фиг его знает что такое состояние сдвига - поэтому просто всегда ноль возвращаем
		return (0);
	tmp = wchar;
	if (tmp > 0x10FFFF)
		return (-1);
	else if (tmp <= 0x7F)
	{
		s[0] = (char)tmp;
		return (1);
	}
	else if (tmp >= 0x10000)
	{
		s[0] = (char)(tmp >> 0x12) | 0xF0;
		s[1] = (char)((tmp >> 0xC) & 0x3F) | 0x80;
		s[2] = (char)((tmp >> 0x6) & 0x3F) | 0x80;
		s[3] = (char)((tmp & 0x3F) | 0x80);
		return (4);
	}
	return (fn_stub(s, tmp));
}

size_t	wcslen(const wchar_t *s) {
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	fn_reverse(char *start, char *end)
{
	char tmp;

	end[1] = 0;
	while (start + 1 <= end)
	{
		tmp = end[0];
		end--[0] = start[0];
		start++[0] = tmp;
	}
}

static uint64_t _divItoa(ZauxiliaryDiv_t dividend, ZauxiliaryDiv_t divisor) {
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

static uint64_t _divItoaPre(uintmax_t dividend, uintmax_t divisor) {
	ZauxiliaryDiv_t				dividendTwo;
	ZauxiliaryDiv_t				divisorTwo;

	dividendTwo.value = dividend;
	divisorTwo.value = divisor;
	return (_divItoa(dividendTwo, divisorTwo));
}

static uint8_t _alphabet(uint8_t value, size_t option) {
	if (value > 9)
		return (value - 10 + (((option & ITOA_UPPER) != 0)? 'A' : 'a'));
	return (value + 0x30);
}

uint8_t itoa_base(char *buffer, uintmax_t value, size_t base, size_t option) {
	char					*str;
	char					*start;
	uintmax_t				tmp;
	size_t					i;
	size_t					count;
	size_t					group;

	if (base > 36 || base < 2)
		base = 10;
	str = buffer;
	start = buffer;
	if ((option & ITOA_SIGNED) != 0)
	{
		if ((intmax_t)value < 0)
		{
			value = ~value + 1;
			buffer++[0] = '-';
			start++;
		}
		else if ((option & ITOA_PLUS) != 0)
		{
			buffer++[0] = '+';
			start++;
		}
	}
	if ((option & ITOA_NOT_ONE) && value < base)
	{
		buffer++[0] = 0x30;
		buffer[0] = _alphabet(value, option);
		return (buffer + 1 - str);
	}
	if ((option & ITOA_GROUPED) != 0)
		group = (base == 2) ? 4 : 3;
	else
		group = 0xFF;
	i = 0;
	count = 1;
	while (value >= base)
	{
		if (i == group)
		{
			buffer++[0] = ' ';
			i = 0;
		}
		tmp = _divItoaPre(value, base);
		buffer++[0] = _alphabet(value - tmp * base, option);
		value = tmp;
		i++;
		count++;
	}
	if (i == group)
		buffer++[0] = ' ';
	buffer[0] = _alphabet(value, option);
	if (base == 2 || (option & ITOA_GROUPED) != 0) {
		count = ((count + 3) & -4) - count;
		while (count > 0)
		{
			count--;
			buffer++[1] = 0x30;
		}
	}
	fn_reverse(start, buffer);
	return (buffer + 1 - str);
}