#ifndef ZPRINTF_PRIVAT_H
#define ZPRINTF_PRIVAT_H

ssize_t write(int fd, const void *buf, size_t count);

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

typedef struct				FtPrintfOption_s
{
	size_t					max;//Точность
	size_t					min;//Ширина
}							FtPrintfOption_t;

typedef struct				FtPrintf_s
{
	FtPrintfOption_t		opt;
	uint8_t					*buffer;
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

#endif//ZPRINTF_PRIVAT_H