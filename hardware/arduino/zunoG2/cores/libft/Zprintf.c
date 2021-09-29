#include "stdint.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "Zprintf_privat.h"
#include "Zprintf_display.h"
#include "Libft.h"
#include "Zauxiliary.h"
#include "Zprintf.h"

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
				if (write(array->fd, b, len) != len)
					return (-1);
				array->count += len;
			}
			#endif
			array->format = litter;
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
		if (write(array->fd, b, len) != (ssize_t)len)
			return (-1);
		array->count += len;
	}
	e = array->buffer;
	len = b - e;
	count = array->count + len;
	if (array->b_in_str == false) {
		if (len != 0 && write(array->fd, e, len) != (ssize_t)len)
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

ssize_t printf(const char *format, ...) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;
	va_list				ap;

	array.buffer = &b[0];
	array.fd = 0x0;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	va_start (ap, format);
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	va_end (ap);
	return (out);
}

ssize_t dprintf(ssize_t fd, const char *format, ...) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;
	va_list				ap;

	array.buffer = &b[0];
	array.fd = fd;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	va_start (ap, format);
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	va_end (ap);
	return (out);
}

ssize_t sprintf(char *str, const char *format, ...) {
	FtPrintf_t			array;
	ssize_t				out;
	va_list				ap;

	array.buffer = (uint8_t *)str;
	array.buffer_len = (size_t)(-1);
	array.b_in_str = true;
	va_start (ap, format);
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[(size_t)(-1)], ap);
	va_end (ap);
	return (out);
}

ssize_t snprintf(char *str, size_t len, const char *format, ...) {
	FtPrintf_t			array;
	ssize_t				out;
	va_list				ap;

	array.buffer = (uint8_t *)str;
	array.buffer_len = len;
	array.b_in_str = true;
	va_start (ap, format);
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[len], ap);
	va_end (ap);
	return (out);
}

ssize_t vdprintf(ssize_t fd, const char *format, va_list ap) {
	FtPrintf_t			array;
	uint8_t				b[ZPRINTF_BUFFER];
	ssize_t				out;

	array.buffer = &b[0];
	array.fd = fd;
	array.buffer_len = ZPRINTF_BUFFER;
	array.b_in_str = false;
	out = _Zprint(&array, format, &b[0], &b[ZPRINTF_BUFFER], ap);
	return (out);
}

ssize_t vsprintf(char *str, const char *format, va_list ap) {
	FtPrintf_t			array;
	ssize_t				out;
	size_t				len;

	len = strlen(str);
	array.buffer = (uint8_t *)str;
	array.buffer_len = len;
	array.b_in_str = true;
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[len], ap);
	return (out);
}

ssize_t vsnprintf(char *str, size_t len, const char *format, va_list ap) {
	FtPrintf_t			array;
	ssize_t				out;

	array.buffer = (uint8_t *)str;
	array.buffer_len = len;
	array.b_in_str = true;
	out = _Zprint(&array, format, (uint8_t *)str, (uint8_t *)&str[len], ap);
	return (out);
}