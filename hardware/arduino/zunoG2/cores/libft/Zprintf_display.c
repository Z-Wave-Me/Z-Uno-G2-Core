//#include "Arduino.h"
#include "stdint.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "Zprintf_privat.h"
#include "Zauxiliary.h"

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
	if (write(fd, b, len) !=  (ssize_t)len)
		return (0);
	memset(b, dup, count);
	while (count >= len) {
		if (write(fd, b, len) !=  (ssize_t)len)
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
	if (write(fd, b, len) !=  (ssize_t)len)
		return (0);
	while (count >= len) {
		memcpy(b, date, len);
		date += len;
		if (write(fd, b, len) !=  (ssize_t)len)
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

uint8_t *Zprintf_display_x(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t						option;

	if (array->format == 'X')
		option = ITOA_UPPER;
	else
		option = ITOA_LOWER;
	return (_display_number(array, b, e, flags, 0x10, option));
}

uint8_t *Zprintf_display_p(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags | ZPRINTF_FLAGS_PREFIX | ZPRINTF_FLAGS_PTRDIFF, 0x10, ITOA_LOWER));
}

uint8_t *Zprintf_display_o(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags, 0x8, ITOA_LOWER));
}

uint8_t *Zprintf_display_d(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	size_t						option;

	option = ITOA_LOWER | ITOA_SIGNED;
	if ((flags & ZPRINTF_FLAGS_PLUS) != 0)
		option = option | ITOA_PLUS;
	return (_display_number(array, b, e, flags, 0xA, option));
}

uint8_t *Zprintf_display_u(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags) {
	return (_display_number(array, b, e, flags, 0xA, ITOA_LOWER));
}