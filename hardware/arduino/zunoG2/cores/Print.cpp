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
	size_t				count;

	count = 0;
	if (n < 0){ // Checking sign of number
		n = -n;
		this->write('-');
		count++;
	}
	this->_printLNumber(n, 10, precision);
	this->_addLeadingZeros(precision);
	this->_writeChars();
	count += _len;
	return (count);
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
	size_t				count;

	count = 0;
	if ((format % 0x1F == 10) and (n < 0)){
		n = -n;
		this->write('-');
		count++;
	}
	this->_printLNumber(n, format & 0x1F, 0xFF);
	format >>= 5;
	format++;
	while(count < format){
		this->write('0');
		count++;
	}
	this->_writeChars();
	return (count);
}

/* Private Methods */
void Print::_printLNumber(long number, uint8_t base, uint8_t precision){
    uint8_t ch;
    _len = 0;
    if (base < 2) 
        base = 10;
    do{
        if (_len == precision)
            _buffer[_len++] = '.';
        ch = number % base;
        ch = _digit2hexchar(ch);
        number /= base;
        _buffer[_len++] = ch;

    }while(number);
}

void Print::_addLeadingZeros(uint8_t precision){
    if ((precision == 0xFF) or (precision < _len))
        return;
    precision -= _len;
    while(precision--)
        _buffer[_len++] = '0';
    _buffer[_len++] = '.';
    _buffer[_len++] = '0';

}

void Print::_writeChars(){
    while(_len--)
        write(_buffer[_len]);
}





