#ifndef LIBFT_H
#define LIBFT_H

#include "Zprintf.h"

inline int isspace(int c) {
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
};

inline int isupper(int c) {
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
};

inline int tolower(int c) { return (isupper(c) ? (c) - 'A' + 'a' : c); };

inline int islower(int c) {
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
};

inline int toupper(int c) { return (islower(c) ? c - 'a' + 'A' : c); };

char *ultoa(unsigned long value, char *str, int base);
inline char *utoa(unsigned int value, char *str, int base) {return(ultoa((unsigned long)value, str, base));};

char *ltoa(long value, char *str, int base);
inline char *itoa(int value, char *str, int base) {return (ltoa((long)value, str, base));};

long strtol (const char *__restrict s, char **__restrict ptr, int base);
inline int atoi(const char *s) {return ((int)strtol(s, NULL, 10));};
inline long atol(const char *s) {return ((long)strtol(s, NULL, 10));};

char *dtostrf(float value, unsigned long width, unsigned long prec, char *s);

#endif//LIBFT_H