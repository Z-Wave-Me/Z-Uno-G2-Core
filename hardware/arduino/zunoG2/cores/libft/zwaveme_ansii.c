#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif

int isspace(int c) {
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

int isupper(int c) {
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

int tolower(int c) {
	return (isupper(c) ? (c) - 'A' + 'a' : c);
}

int islower(int c) {
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

int toupper(int c) {
	return (islower(c) ? c - 'a' + 'A' : c);
}

#ifdef __cplusplus
}
#endif