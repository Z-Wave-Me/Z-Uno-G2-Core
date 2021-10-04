#include "zwaveme_libft.h"
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

int isalnum(int c) {
	if (isalpha(c) == true)
		return (true);
	return (isdigit(c));
}

int isalpha(int c) {
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

int isascii (int c) {
	if ((unsigned int)c <= 0x7F)
		return (true);
	return (false);
}


int isblank(int c) {
	if (c == 0x20 || c == 0x9)
		return (true);
	return (false);
}

int iscntrl(int c) {
	if (c == 0x7F || (unsigned int)c <= 0x1F)
		return (true);
	return (false);
}

int isdigit(int c) {
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int isgraph(int c) {
	if (c == ' ')
		return (false);
	return (isprint(c));
}

int islower(int c) {
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

int isprint(int c) {
	if (c >= 0x20 && c <= 0x7E)
		return (true);
	return (false);
}

int ispunct(int c) {
	if (isprint(c) == false)
		return (false);
	if (c == ' ')
		return (false);
	if (isalnum(c) == true)
		return (false);
	return (true);
}

int isspace(int c) {
	if (c == 0x20)
		return (true);
	if (c >= 0x9 && c <= 0xD)
		return (true);
	// if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
	// 	return (true);
	return (false);
}

int isupper(int c) {
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

int isxdigit(int c) {
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'a' && c <= 'f')
		return (true);
	if (c >= 'A' && c <= 'F')
		return (true);
	return (false);
}

int toascii(int c) {
	return (c & 0x7F);
}

int tolower(int c) {
	return (isupper(c) ? (c) - 'A' + 'a' : c);
}

int toupper(int c) {
	return (islower(c) ? c - 'a' + 'A' : c);
}

#ifdef __cplusplus
}
#endif