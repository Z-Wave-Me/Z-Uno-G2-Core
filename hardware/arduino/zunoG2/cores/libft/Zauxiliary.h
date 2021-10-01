#ifndef ZAUXILIARY_H
#define ZAUXILIARY_H

#ifdef __cplusplus
extern "C" {
#endif

//ft_itoa define;
# define ITOA_LOWER				0x0//строчные буквы
# define ITOA_UPPER				0x1//прописные буквы
# define ITOA_SIGNED			0x2//считает что получает базу с  отрицательными числами, если отрицательно ставит перед -
# define ITOA_GROUPED			0x4//групирует по три символа и разделяет пробелом
# define ITOA_PLUS				0x8//если установлен ITOA_SIGNED но число положительное то перед ним ставит +
# define ITOA_NOT_ONE			0x10//если установлен то к одному числу добавляеться ноль: 01

int wctomb(char *s, wchar_t wchar);
size_t wcslen(const wchar_t *s);
uint8_t itoa_base(char *buffer, uintmax_t value, size_t base, size_t option);

#ifdef __cplusplus
}
#endif

#endif//ZAUXILIARY_H