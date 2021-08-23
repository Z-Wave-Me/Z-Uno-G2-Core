#include "Print.h"
#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>
#include "float.h"
#include "Libft.h"

/* Public Methods */
size_t  Print::write(const char *str) {
    if (str == NULL) return 0;
    return write((const uint8_t *)str, strlen(str));
}
size_t Print::write(const uint8_t *buffer, size_t size){
	size_t i;
	for(i=0;i<size;i++)
		write(buffer[i]);
}

size_t Print::print(long n, int base) {
	char								buf[8 * sizeof(long) + 1 + 1]; // Assumes 8-bit chars plus zero byte. + sign

	ltoa(n, &buf[0], base);
	return (this->write(&buf[0]));
}

size_t Print::print(unsigned long n, int base) {
	char								buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.

	ultoa(n, &buf[0], base);
	return (this->write(&buf[0]));
}

size_t Print::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(char c)
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(unsigned char b, int base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Print::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(float num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::printFloat(float number, uint8_t digits) {
	char				buff[FLT_MAX_10_EXP + FLT_MAX_10_EXP + 1 + 1 + 1];//++1 - zero; +1 '.'; +1 - neg

	if (digits > FLT_MAX_10_EXP)
		digits = FLT_MAX_10_EXP;
	dtostrff(number, 0, digits, &buff[0]);
	return (this->write(&buff[0]));
}

uint8_t Print::fixPrint(long n, uint8_t precision) {
	char				buf[4 * sizeof(long) + 1 + 1];//+1 zero byte +1 sign
	char				*f;
	char				*b;
	size_t				count;

	f = &buf[sizeof(buf)];
	b = &buf[0];
	if (n < 0) {
		n = -n;
		b++[0] = '-';
	}
	while (n != 0 && precision != 0) {
		f--;
		f[0] = this->_digit2hexchar(n % 10);
		n = n / 10;
		precision--;
	}
	ultoa((unsigned long)n, b, 10);
	b = b + strlen(b);
	if (f != &buf[sizeof(buf) - 1])
		b++[0] = '.';
	count = this->write(&buf[0], b - &buf[0]) + precision;
	while(precision-- != 0)
		this->write('0');
	return (count + this->write(f, &buf[sizeof(buf)] - f));
}

size_t Print::dumpPrint(uint8_t *b, size_t count, size_t line_size) {
	size_t					ch;
	size_t					n;

	n = 0;
	while(count--) {
		ch = b++[0];
		n++;
		this->write(this->_digit2hexchar(ch >> 4));
		this->write(this->_digit2hexchar(ch & 0x0F));
		ch = ((n % line_size) == 0) ? '\n' : ' ';
		this->write(ch);
	}
	return (n * 3);
}

uint8_t Print::formatPrint(int n, uint8_t format) {
	char				buf[4 * sizeof(long) + 1 + 1];//+1 zero byte +1 sign
	size_t				count;
	size_t				i;

	ltoa(n, &buf[0], 10);
	n = strlen(&buf[0]);
	count = format > n ? format - n : 0;
	i = count;
	while(i-- != 0)
		this->write(' ');
	this->write(&buf[0], n);
	return (count + n);
}
