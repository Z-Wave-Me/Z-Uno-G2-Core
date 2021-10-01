#include "stdint.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <math.h>
#include <float.h>
#include "zwaveme_float_private.h"
#include "zwaveme_libft.h"
#include "Zauxiliary.h"

ssize_t write(int fd, const void *buf, size_t count);

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ZPRINTF_BUFFER
	#define ZPRINTF_BUFFER			0x100
#endif

// #define ZPRINTF_FUNCTIONAL_N
// #define ZPRINTF_FUNCTIONAL_C
// #define ZPRINTF_FUNCTIONAL_S

#define ZPRINTF_FORMAT			"sScCn"

#define ZPRINTF_FLAGS_PREFIX			0x1// #
#define ZPRINTF_FLAGS_NULL				0x2// 0
#define ZPRINTF_FLAGS_SPACE				0x4// пробел
#define ZPRINTF_FLAGS_PLUS				0x8// +
#define ZPRINTF_FLAGS_LEFT				0x10// -
#define ZPRINTF_FLAGS_GRUP				0x20// '
#define ZPRINTF_FLAGS_MAX				0x40//указывает установлена ли точность
#define ZPRINTF_FLAGS_SHORT				0x80//h
#define ZPRINTF_FLAGS_LONG				0x100//l
#define ZPRINTF_FLAGS_UINTMAX			0x200//j
#define ZPRINTF_FLAGS_PTRDIFF			0x400//t
#define ZPRINTF_FLAGS_SIZE				0x800//z
#define ZPRINTF_FLAGS_LONG_LONG			0x1000//ll
#define ZPRINTF_FLAGS_CHAR				0x2000//hh
#define ZPRINTF_FLAGS_MAX_OVER			0x4000// когда max отрицательный влияет ноль или пробел использовать
#define ZPRINTF_FLAGS_MAX_OVER_STR		0x8000// когда max отрицательный влияет используеться вся строка
#define ZPRINTF_FLAGS_FLOAT_E			0x10000// научная форма используеться
#define ZPRINTF_FLAGS_UP				0x20000// буква большая использовалась

typedef struct				FtPrintfOption_s
{
	size_t					max;//Точность
	size_t					min;//Ширина
}							FtPrintfOption_t;

typedef struct				FtPrintf_s
{
	FtPrintfOption_t		opt;
	uint8_t					*buffer;
	ssize_t					(*write)(int, const void *, size_t);
	size_t					buffer_len;
	ssize_t					fd;
	size_t					count;
	va_list 				ap;//Образец где хранить начало аргументов
	va_list 				ap_line;//копия для неприрывного в случае когда начинаетья новая группа $ с начала - сбрасываеться на начало аргументов
	va_list 				ap_n;//копия для того случая когда не нужно прерывать непрерывность
	uint8_t					sp;//символ заполнения
	uint8_t					b_in_str;
	uint8_t					format;
}							FtPrintf_t;

static uint8_t *_writeDup(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint8_t dup, size_t count) {
	size_t					len;
	ssize_t					fd;

	if (count == 0 || b == 0)
		return (b);
	len = e - b;
	if (len > count)
		len = count;
	memset(b, dup, len);
	b = b + len;
	if (b < e)
		return (b);
	count -= len;
	b = array->buffer;
	len = e - b;
	array->count += len;
	if (array->b_in_str == true)
		return (0);
	fd = array->fd;
	if (array->write(fd, b, len) !=  (ssize_t)len)
		return (0);
	memset(b, dup, count);
	while (count >= len) {
		if (array->write(fd, b, len) !=  (ssize_t)len)
			return (0);
		count -= len;
		array->count += len;
	}
	return (b + count);
}

static uint8_t *_writeStr(FtPrintf_t *array, uint8_t *b, uint8_t *e, void *d, size_t count) {
	uint8_t					*date;
	size_t					len;
	ssize_t					fd;

	if (count == 0 || b == 0)
		return (b);
	date = (uint8_t *)d;
	len = e - b;
	if (len > count)
		len = count;
	memcpy(b, date, len);
	b = b + len;
	date = date + len;
	if (b < e)
		return (b);
	count -= len;
	b = array->buffer;
	len = e - b;
	array->count += len;
	if (array->b_in_str == true)
		return (0);
	fd = array->fd;
	if (array->write(fd, b, len) !=  (ssize_t)len)
		return (0);
	while (count >= len) {
		memcpy(b, date, len);
		date += len;
		if (array->write(fd, b, len) !=  (ssize_t)len)
			return (0);
		count -= len;
		array->count += len;
	}
	memcpy(b, date, count);
	return (b + count);
}

uint8_t *Zprintf_display_unknown(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t				min;
	uint8_t				sp;

	if ((min = array->opt.min) != 0)
		min--;
	sp = array->sp;
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0) {
		b = _writeDup(array, b, e, sp, min);
		min = 0;
	}
	b = _writeStr(array, b, e, &array->format, 1);
	return (_writeDup(array, b, e, sp, min));
}

uint8_t *Zprintf_display_c(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	char					str[5];// 4 байта максимум размер вывадимой многайтной строки которую можно получить
	wint_t					arg;
	ssize_t					len;
	size_t					min;

	arg = (wint_t)va_arg(array->ap_line, size_t);
	#ifdef ZPRINTF_FUNCTIONAL_C
	if ((flags & ZPRINTF_FLAGS_LONG) == 0 && array->format != 'C') {
	#endif
		array->format = (uint8_t)arg;
		return (Zprintf_display_unknown(array, b, e, flags));
	#ifdef ZPRINTF_FUNCTIONAL_C
	}
	#endif
	if ((len = wctomb(&str[0], arg)) == -1)
		return (0);
	if ((flags & ZPRINTF_FLAGS_LEFT) != 0)
		b = _writeStr(array, b, e, &str[0], len);
	if ((min = array->opt.min) >= 2)
		b = _writeDup(array, b, e, array->sp, --min);
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0)
		b = _writeStr(array, b, e, &str[0], len);
	return (b);
}

static const uint8_t gNull[] = "null";

uint8_t *Zprintf_display_s(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t					arg;
	size_t					len;
	size_t					max;
	size_t					min;
	uint8_t					sp;
	#ifdef ZPRINTF_FUNCTIONAL_S
	uint8_t					bS;
	char					str[5];// 4 байта максимум размер вывадимой многайтной строки которую можно получить
	wchar_t					*ws;
	wchar_t					*ws_end;
	ssize_t					tmp;
	#endif

	arg = va_arg(array->ap_line, size_t);
	#ifdef ZPRINTF_FUNCTIONAL_S
	if (((flags & ZPRINTF_FLAGS_LONG) == 0 && array->format != 'S') || arg == 0) {
	#endif
		if (arg == 0)
			arg = (size_t)&gNull[0];
		len = strlen((char *)arg);
	#ifdef ZPRINTF_FUNCTIONAL_S
		bS = false;
	}
	else {
		len = wcslen((wchar_t *)arg);
		bS = true;
	}
	#endif
	max = array->opt.max;
	if ((flags & ZPRINTF_FLAGS_MAX) == 0 || max > len || (flags & ZPRINTF_FLAGS_MAX_OVER_STR) != 0)
		max = len;
	min = array->opt.min;
	min = (min > max) ? min - max : 0;
	sp = array->sp;
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0) {
		b = _writeDup(array, b, e, sp, min);
		min = 0;
	}
	#ifdef ZPRINTF_FUNCTIONAL_S
	if (bS == false)
	#endif
		b = _writeStr(array, b, e, (void *)arg, max);
	#ifdef ZPRINTF_FUNCTIONAL_S
	else {
		ws = (wchar_t *)arg;
		ws_end = &ws[max];
		while (ws < ws_end) {
			if ((tmp = wctomb(str, ws++[0])) == -1)
				return (0);
			if ((b = _writeStr(array, b, e, &str[0], tmp)) == 0)
				return (0);
		}
	}
	#endif
	return (_writeDup(array, b, e, sp, min));
}

uint8_t *Zprintf_display_n(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t					arg;
	size_t					count;
	
	arg = va_arg(array->ap_line, size_t);
	count = array->count;
	if ((flags & ZPRINTF_FLAGS_UINTMAX) != 0)
		*(intmax_t *)arg = (signed)count;
	else if ((flags & ZPRINTF_FLAGS_PTRDIFF) != 0 || (flags & ZPRINTF_FLAGS_SIZE) != 0)
		*(ptrdiff_t *)arg = (signed)count;
	else if ((flags & ZPRINTF_FLAGS_LONG_LONG) != 0)
		*(long long *)arg = (signed)count;
	else if ((flags & ZPRINTF_FLAGS_LONG) != 0)
		*(long *)arg = (signed)count;
	else if ((flags & ZPRINTF_FLAGS_SHORT) != 0)
		*(short *)arg = (signed)count;
	else if ((flags & ZPRINTF_FLAGS_CHAR) != 0)
		*(signed char *)arg = (signed)count;
	else
		*(int *)arg = (signed)count;
	return (b);
	(void)e;
}

static uintmax_t _getArgs(FtPrintf_t *array, uint32_t flags, size_t option) {
	uintmax_t					args;

	if ((flags & ZPRINTF_FLAGS_UINTMAX) != 0)
		args = va_arg(array->ap_line, uintmax_t);
	else {
		args = va_arg(array->ap_line, size_t);
		if ((option & ITOA_SIGNED) != 0) {//проверяем имеем дело с системой работающей с отрицательными числами(d i) или нет
			if ((flags & ZPRINTF_FLAGS_PTRDIFF) != 0 || (flags & ZPRINTF_FLAGS_SIZE) != 0)
				args = (ssize_t)args;
			else if ((flags & ZPRINTF_FLAGS_LONG_LONG) != 0)
				args = (long long)args;
			else if ((flags & ZPRINTF_FLAGS_LONG) != 0)
				args = (long)args;
			else if ((flags & ZPRINTF_FLAGS_SHORT) != 0)
				args = (short)args;
			else if ((flags & ZPRINTF_FLAGS_CHAR) != 0)
				args = (signed char)args;
			else
				args = (signed int)args;
		}
		else {
			if ((flags & ZPRINTF_FLAGS_PTRDIFF) != 0 || (flags & ZPRINTF_FLAGS_SIZE) != 0)
				args = (size_t)args;
			else if ((flags & ZPRINTF_FLAGS_LONG_LONG) != 0)
				args = (unsigned long long)args;
			else if ((flags & ZPRINTF_FLAGS_LONG) != 0)
				args = (unsigned long)args;
			else if ((flags & ZPRINTF_FLAGS_SHORT) != 0)
				args = (unsigned short)args;
			else if ((flags & ZPRINTF_FLAGS_CHAR) != 0)
				args = (unsigned char)args;
			else
				args = (unsigned int)args;
		}
	}
	return (args);
}

static uint8_t *_display_number(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags, size_t base, size_t option) {
	uintmax_t					args;
	char						str[sizeof(uintmax_t) * 10 + 2 + 2];
	char						*buffer;
	size_t						count;
	size_t						letter;
	size_t						max;
	size_t						min;
	size_t						tmp;
	size_t						format;

	buffer = str + 2;//что бы не было лишник операций поэтому добавляем перед числом где вазможно и каректируем
	option = (base != 16 && (flags & ZPRINTF_FLAGS_GRUP) != 0) ? option | ITOA_GROUPED : option;
	args = _getArgs(array, flags, option);
	format = array->format;
	if (args == 0 && (flags & ZPRINTF_FLAGS_PREFIX) != 0 && format != 'p' && base != 0x8)
		flags = flags ^ ZPRINTF_FLAGS_PREFIX;
	count = itoa_base(buffer, args, base, option);
	if ((letter = buffer[0]) < 0x30) {
		buffer++;
		count--;
	}
	else
		letter = 0;
	max = array->opt.max;
	if ((flags & ZPRINTF_FLAGS_MAX) != 0) {
		if (max == 0 && args == 0) {
			if (base == 10)
				count = 0;
			else if (base != 8) {
				letter = 0;
				count = 0;
			}
			else if ((flags & ZPRINTF_FLAGS_PREFIX) != 0 && base == 8) {
				letter = 0;
				count = 0;
			}
		}
		max = (max > count)? max - count : 0;
	}
	if ((option & ITOA_SIGNED) != 0 && (flags & ZPRINTF_FLAGS_SPACE) != 0 && letter == 0)
		letter = ' ';//если с системой работающей с отрицательными числами и перед числом нет + или - и есть b_space ставим пробел
	tmp = letter ? 1 : 0;
	if ((flags & ZPRINTF_FLAGS_PREFIX) != 0) {
		if (base == 16)
			tmp += 2;
		else if (base == 8 && args != 0) {//если 8 система исчисления и префик то ставим перед 0 и если есть групировка и длинна числа = 3 то ставим пробел 
			buffer--;//символ групировке printf должен получаться с помощью localeconv но не уверен что можно ее использовать - зашиваем как пробел, тоже и в itoa
			count++;
			if (count == 4 && (flags & ZPRINTF_FLAGS_GRUP) != 0) {
				buffer[0] = ' ';
				buffer--;
				count++;
			}
			buffer[0] = 0x30;
			max -= (max > 0) ? 1 : 0;
		}
	}
	tmp += count + max;
	min = array->opt.min;
	min = (min > tmp) ? min - tmp : 0;
	tmp += min;
	if (letter != 0 && min != 0 && (flags & ZPRINTF_FLAGS_NULL) != 0 && (flags & ZPRINTF_FLAGS_MAX) == 0) {
		b = _writeStr(array, b, e, (void *)&letter, 1);
		letter = 0;
	}
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0 && (flags & ZPRINTF_FLAGS_MAX) != 0) {
		b = _writeDup(array, b, e, ' ', min);
		min = 0;
	}
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0 && format == 'x' && (flags & ZPRINTF_FLAGS_NULL) == 0) {
		b = _writeDup(array, b, e, array->sp, min);
		min = 0;
	}
	if ((flags & ZPRINTF_FLAGS_PREFIX) != 0 && base == 16 && format != 'p') {
		b = _writeStr(array, b, e, (format < 'a') ? (void *)&"0X" : (void *)&"0x", 2);
		flags = flags ^ ZPRINTF_FLAGS_PREFIX;
	}
	if ((flags & ZPRINTF_FLAGS_LEFT) == 0) {
		b = _writeDup(array, b, e, array->sp, min);
		min = 0;
	}
	if ((flags & ZPRINTF_FLAGS_PREFIX) != 0 && base == 16)
		b = _writeStr(array, b, e, (format < 'a') ? (void *)&"0X" : (void *)&"0x", 2);
	if (letter != 0)
		b = _writeStr(array, b, e, (void *)&letter, 1);
	b = _writeDup(array, b, e, ((flags & ZPRINTF_FLAGS_MAX_OVER) != 0)?  0x20 : 0x30, max);
	b = _writeStr(array, b, e, (void *)buffer, count);
	b = _writeDup(array, b, e, ' ', min);
	return (b);
}

static uint8_t *Zprintf_display_x(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t						option;

	if (array->format == 'X')
		option = ITOA_UPPER;
	else
		option = ITOA_LOWER;
	return (_display_number(array, b, e, flags, 0x10, option));
}

static uint8_t *Zprintf_display_p(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags | ZPRINTF_FLAGS_PREFIX | ZPRINTF_FLAGS_PTRDIFF, 0x10, ITOA_LOWER));
}

static uint8_t *Zprintf_display_o(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags, 0x8, ITOA_LOWER));
}

static uint8_t *Zprintf_display_d(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t						option;

	option = ITOA_LOWER | ITOA_SIGNED;
	if ((flags & ZPRINTF_FLAGS_PLUS) != 0)
		option = option | ITOA_PLUS;
	return (_display_number(array, b, e, flags, 0xA, option));
}

static uint8_t *Zprintf_display_u(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags, 0xA, ITOA_LOWER));
}

static uint8_t *Zprintf_display_f(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	LibftFloatEngine_t				floatEngine;
	LibftFloatType_t				type;
	size_t							width;
	size_t							prec;
	size_t							offset;
	// size_t							e;
	size_t							lenFractionNull;
	size_t							lenSingle;
	size_t							lenSingleNull;
	uint8_t							buff[6];

	width = array->opt.min;
	if ((type = zwaveme_floatEngine(va_arg(array->ap_line, double), &floatEngine)) != LibftFloatTypeNumber) {
		prec = zwaveme_floatEngineNotNumber(floatEngine.neg, type, (uint8_t *)&buff[0], ((flags & ZPRINTF_FLAGS_UP) == 0x0) ? 0x0 : 0x1);
		width = (width >= prec) ? width - prec : 0;
		b = _writeDup(array, b, e, array->sp, width);
		b = _writeStr(array, b, e, &buff[0], prec);
		return (b);
	}
	prec = ((flags & ZPRINTF_FLAGS_MAX) == 0) ? 6 : array->opt.max;//6 - знаков после запитой по умолчанию
	lenSingle = floatEngine.lenSingle;
	lenSingleNull = floatEngine.lenSingleNull;
	// e = 0;
	// if ((flags & ZPRINTF_FLAGS_FLOAT_E) != 0x0)
	// {
	// 	if (lenSingle != 0)
	// 	{
	// 		e = lenSingle - 0x1;
	// 		floatEngine.lenFraction = floatEngine.lenFraction + e;
	// 		e = e + lenSingleNull;
	// 		lenSingleNull = 0x0;
	// 		lenSingle = 0x1;
	// 	}
		
	// }
	offset = lenSingle + lenSingleNull + floatEngine.neg;
	if (prec != 0)
		offset = offset + prec + 1;//+1 '.'
	width = (width >= offset) ? width - offset : 0;
	b = _writeDup(array, b, e, array->sp, width);
	b = _writeStr(array, b, e, &floatEngine.number[0], lenSingle);
	if (lenSingle == 0)
		lenSingleNull++;
	b = _writeDup(array, b, e, '0', lenSingleNull);
	if (prec != 0) {
		b++[0] = '.';
		lenFractionNull = floatEngine.lenFractionNull;
		if (prec >= lenFractionNull)
			prec = prec - lenFractionNull;
		else {
			lenFractionNull = prec;
			prec = 0;
		}
		b = _writeDup(array, b, e, '0', lenFractionNull);
		offset = floatEngine.lenFraction;
		if (prec >= offset)
			prec = prec - offset;
		else {
			offset = prec;
			prec = 0;
		}
		b = _writeStr(array, b, e, &floatEngine.number[floatEngine.lenSingle], offset);
		b = _writeDup(array, b, e, '0', prec);
	}
	return (b);
}

// static const uint8_t gFormat[] = ZPRINTF_FORMAT;
// static const uint16_t gFunctionTable[sizeof(ZPRINTF_FORMAT)] = {
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_unknown) - ((uint8_t *)Zprintf_display_unknown))),
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_s) - ((uint8_t *)Zprintf_display_unknown))),
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_s) - ((uint8_t *)Zprintf_display_unknown))),
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_c) - ((uint8_t *)Zprintf_display_unknown))),
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_c) - ((uint8_t *)Zprintf_display_unknown))),
// 	(uint16_t)((uint32_t)(((uint8_t *)Zprintf_display_n) - ((uint8_t *)Zprintf_display_unknown)))
// };
// 	uint8_t					*p;
// 	uint8_t					*(*fn)(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
// p = (uint8_t *)strchr((char *)&gFormat[0], litter);
// p = (p != 0) ? (uint8_t *)(p - &gFormat[0] + 1) : p;
// fn = (uint8_t *(*)(FtPrintf_t*, uint8_t*, uint8_t*, uint32_t))(uint32_t)(gFunctionTable[(size_t)p] + ((uint32_t)(((uint8_t *)Zprintf_display_unknown))));
// b = fn(array, b, e, bFlags);


static uint8_t _ZprintFlag(FtPrintf_t *array, const char **format, uint8_t litter, uint32_t *lpbFlags) {
	const char							*f;
	size_t								tmp;
	uint32_t							bFlags;
	uint8_t								b_point;
	uint8_t								b_star;
	uint8_t								null;

	bFlags = lpbFlags[0];
	f = format[0];
	if ((litter >= 0x31 && litter <= 0x39) || litter == '*') {
		b_point = (f[-1] == '.') ? 1 : 0;//Если точка со звездой и доларом - то вступает очередное тупое правило - учитываем его
		if (litter == '*') {
			f++;//если звезда сместим указатель
			b_star = 1;//установим обрабатываем в данный момент звезду или нет
		}
		else
			b_star = 0;//установим обрабатываем в данный момент звезду или нет
		null = f[0];//сохраним символ, что бы знать может это символ - ноль
		tmp = 0;
		if ((litter = f[0]) >= 0x30 && litter <= 0x39) {
			tmp = atoi(f);
			while ((litter = f[1]) >= 0x30 && litter <= 0x39)
				f++;
			if (litter == '$')
				f++;//если после числа есть доллар значит увеличим указатель
		}
		if (f[0] != '$') {//проверим указатель указывает на доллар или нет, если да обрабатываем как доллар все
			if (b_point != 0) {
				f--;//востановим указатель ведь в цикле потом увеличиться...
				array->opt.max = va_arg(array->ap_line, size_t);
				bFlags |= ZPRINTF_FLAGS_MAX;
			}
			else if (b_star != 0) {//если стоит что звезда значит обрабатываем просто как звезду после которой нет долаллара в притык
				f--;//востановим указатель ведь в цикле потом увеличиться...
				array->opt.min = va_arg(array->ap_line, size_t);//получим значение звезды
				if (null == 0x30)
					bFlags |= ZPRINTF_FLAGS_NULL;//раз просто звезда, то проверим, был ли сивол нуля и если надо установим это
				if (tmp != 0)
					array->opt.min = tmp;//если после звезды есть число то нужно его сохранить
			}
			else
				array->opt.min = tmp;
		}
		else {
			if (b_point != 0) {
				va_copy(array->ap_n, array->ap_line);
				array->opt.max = va_arg(array->ap_n, size_t);
				bFlags |= ZPRINTF_FLAGS_MAX;
			}
			else if (tmp == 0)
				array->opt.min = 0;//Долар после звезд без цифер принимаем за 0
			else if (b_star != 0) {//Раз перед ним есть звезда значит конец доларового выражения
				va_copy(array->ap_n, array->ap);//что бы не прерывать не прирывную линию используем другую копию
				while (tmp-- > 0)
					array->opt.min = va_arg(array->ap_n, size_t);
			}
			else {
				va_copy(array->ap_line, array->ap);//Раз нет звезды перед значит начинаем новую линию
				while (tmp-- > 1)
					va_arg(array->ap_line, size_t);//причем подгоняем аргументы на один меньше, так там все тупо сделанно
			}
		}
	}
	else {
		switch (litter) {
		case '#':
			bFlags |= ZPRINTF_FLAGS_PREFIX;
			break ;
		case 0x30:
			bFlags |= ZPRINTF_FLAGS_NULL;
			break ;
		case 0x20:
			bFlags |= ZPRINTF_FLAGS_SPACE;
			break ;
		case '+':
			bFlags |= ZPRINTF_FLAGS_PLUS;
			break ;
		case '-':
			bFlags |= ZPRINTF_FLAGS_LEFT;
			break ;
		case '\'':
			bFlags |= ZPRINTF_FLAGS_GRUP;
			break ;
		case '.':
			bFlags |= ZPRINTF_FLAGS_MAX;
			array->opt.max = atoi(f + 1);
			while ((litter = f[1]) >= 0x30 && litter <= 0x39)
				f++;
			break ;
		case 'h':
			if (f[1] == litter) {
				bFlags |= ZPRINTF_FLAGS_CHAR;
				f++;
				break ;
			}
			bFlags |= ZPRINTF_FLAGS_SHORT;
			break ;
		case 'l':
			if (f[1] == litter) {
				bFlags |= ZPRINTF_FLAGS_LONG_LONG;
				f++;
				break ;
			}
			bFlags |= ZPRINTF_FLAGS_LONG;
			break ;
		case 'j':
			bFlags |= ZPRINTF_FLAGS_UINTMAX;
			break ;
		case 't':
			bFlags |= ZPRINTF_FLAGS_PTRDIFF;
			break ;
		case 'z':
			bFlags |= ZPRINTF_FLAGS_SIZE;
			break ;
		default:
			return (false);
			break ;
		}
	}
	format[0] = f;
	lpbFlags[0] = bFlags;
	return (true);
}

static ssize_t _ZprintWhile(FtPrintf_t *array, const char *format, uint8_t *b, uint8_t *e) {
	uint8_t					litter;
	size_t					len;
	size_t					min;
	uint32_t				bFlags;//флаги
	size_t					count;
	
	len = array->buffer_len;
	while ((litter = format++[0]) != 0) {
		if (litter == '%') {
				bFlags = 0;
				array->opt.max = 0;
				array->opt.min = 0;
				while ((litter = format[0]) != 0) {
					if (_ZprintFlag(array, &format, litter, &bFlags) == false)
						break ;
					format++;
				}
			if ((ssize_t)(min = array->opt.min) < 0) {
				bFlags |= ZPRINTF_FLAGS_LEFT;
				array->opt.min = ~(ssize_t)min + 1;// тупой printf  пришлось добавить...
			}
			if ((litter = format++[0]) == 0)
				break ;
			array->sp = ((bFlags & ZPRINTF_FLAGS_NULL) != 0 && (bFlags & ZPRINTF_FLAGS_LEFT) == 0) ? 0x30 : 0x20;
			if ((ssize_t)array->opt.max < 0) {
				if ((bFlags & ZPRINTF_FLAGS_NULL) == 0)
					bFlags |= ZPRINTF_FLAGS_MAX_OVER;
				bFlags |= ZPRINTF_FLAGS_MAX_OVER_STR;
				array->opt.max = array->opt.min;
			}
			#ifdef ZPRINTF_FUNCTIONAL_N
			if (len != 0 && array->b_in_str == false) {
				if (array->write(array->fd, b, len) != len)
					return (-1);
				array->count += len;
			}
			#endif
			array->format = litter;
			if (litter < 'a')
				bFlags = bFlags| ZPRINTF_FLAGS_UP;
			switch (litter) {
				case 'u':
					b = Zprintf_display_u(array, b, e, bFlags);
					break ;
				case 'i':
				case 'd':
					b = Zprintf_display_d(array, b, e, bFlags);
					break ;
				case 'o':
					b = Zprintf_display_o(array, b, e, bFlags);
					break ;
				// case 'E':
				// case 'e':
				// 	b = Zprintf_display_f(array, b, e, bFlags | ZPRINTF_FLAGS_FLOAT_E);
				// 	break ;
				case 'F':
				case 'f':
					b = Zprintf_display_f(array, b, e, bFlags);
					break ;
				case 'p':
					b = Zprintf_display_p(array, b, e, bFlags);
					break ;
				case 'X':
				case 'x':
					b = Zprintf_display_x(array, b, e, bFlags);
					break ;
				#ifdef ZPRINTF_FUNCTIONAL_N
				case 'n':
					b = Zprintf_display_n(array, b, e, bFlags);
					break ;
				#endif
				#ifdef ZPRINTF_FUNCTIONAL_S
				case 'S':
				#endif
				case 's':
					b = Zprintf_display_s(array, b, e, bFlags);
					break ;
				#ifdef ZPRINTF_FUNCTIONAL_C
				case 'C':
				#endif
				case 'c':
					b = Zprintf_display_c(array, b, e, bFlags);
					break ;
				default:
					b = Zprintf_display_unknown(array, b, e, bFlags);
					break ;
			}
			if (b == 0) {
				if (array->b_in_str == true)
					return (len);
				return (-1);
			}
			continue ;
		}
		b++[0] = litter;
		if (b < e)
			continue ;
		if (array->b_in_str == true)
			return (len);
		b = e - len;
		if (array->write(array->fd, b, len) != (ssize_t)len)
			return (-1);
		array->count += len;
	}
	e = array->buffer;
	len = b - e;
	count = array->count + len;
	if (array->b_in_str == false) {
		if (len != 0 && array->write(array->fd, e, len) != (ssize_t)len)
			return (-1);
	}
	else if (count < array->buffer_len)
		b[0] = 0;
	return (count);
}

static ssize_t _Zprint(FtPrintf_t *array, const char *format, uint8_t *b, uint8_t *e, va_list ap) {
	ssize_t				out;

	array->count = 0;
	va_copy(array->ap, ap);
	va_copy(array->ap_line, array->ap);
	va_copy(array->ap_n, array->ap);
	out = _ZprintWhile(array, format, b, e);
	va_end(array->ap);
	va_end(array->ap_line);
	va_end(array->ap_n);
	return (out);
}

int vdprintf_class(ssize_t (*f)(int, const void *, size_t), int fd, const char *format, va_list ap) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;

	array.write = f;
	array.buffer = &b[0];
	array.fd = fd;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	return (out);
}

int printf(const char *format, ...) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;
	va_list				ap;

	array.write = write;
	array.buffer = &b[0];
	array.fd = 0x0;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	va_start (ap, format);
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	va_end (ap);
	return (out);
}

int dprintf(int fd, const char *format, ...) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;
	va_list				ap;

	array.write = write;
	array.buffer = &b[0];
	array.fd = fd;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	va_start (ap, format);
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	va_end (ap);
	return (out);
}

int sprintf(char *str, const char *format, ...) {
	FtPrintf_t			array;
	ssize_t				out;
	va_list				ap;

	array.write = write;
	array.buffer = (uint8_t *)str;
	array.buffer_len = (size_t)(-1);
	array.b_in_str = true;
	va_start (ap, format);
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[(size_t)(-1)], ap);
	va_end (ap);
	return (out);
}

int snprintf(char *str, size_t len, const char *format, ...) {
	FtPrintf_t			array;
	ssize_t				out;
	va_list				ap;

	array.write = write;
	array.buffer = (uint8_t *)str;
	array.buffer_len = len;
	array.b_in_str = true;
	va_start (ap, format);
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[len], ap);
	va_end (ap);
	return (out);
}

int vprintf(const char *format, va_list ap) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;

	array.write = write;
	array.buffer = &b[0];
	array.fd = 0x0;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	return (out);
}

int vdprintf(int fd, const char *format, va_list ap) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;

	array.write = write;
	array.buffer = &b[0];
	array.fd = fd;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	return (out);
}

int vsprintf(char *str, const char *format, va_list ap) {
	FtPrintf_t			array;
	ssize_t				out;

	array.write = write;
	array.buffer = (uint8_t *)str;
	array.buffer_len = (size_t)(-1);
	array.b_in_str = true;
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[(size_t)(-1)], ap);
	return (out);
}

int vsnprintf(char *str, size_t len, const char *format, va_list ap) {
	FtPrintf_t			array;
	ssize_t				out;

	array.write = write;
	array.buffer = (uint8_t *)str;
	array.buffer_len = len;
	array.b_in_str = true;
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[len], ap);
	return (out);
}

#ifdef __cplusplus
}
#endif