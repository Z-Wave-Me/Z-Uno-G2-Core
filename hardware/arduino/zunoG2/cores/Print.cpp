#include "Print.h"
#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>

inline char digit2hexchar(byte d){
    return (d > 9) ? d - 10 + 'A' : d + '0';
}
size_t  Print::write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
}

size_t Print::print(const char str[])
{
  return write(str);
}

size_t Print::print(char c)
{
  return write(c);
}

size_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t Print::print(int n, int base)
{
  return print((long) n, base);
}

size_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

size_t Print::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t Print::print(unsigned long n, int base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}

size_t Print::print(double n, int digits)
{
  return printFloat(n, digits);
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

size_t Print::println(double num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::println(void)
{
  return write("\r\n");
}

size_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) 
{ 
  size_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
}

uint8_t Print::fixPrint(long n, uint8_t precision) {
    _n = 0;
    
    if (n < 0){ // Checking sign of number
        n = -n;
        write('-');
        _n++;
    }
    printLNumber(n, 10, precision);
    addLeadingZeros(precision);
    writeChars();
    _n += _len;
    return _n;           
}

word Print::dumpPrint(uint8_t * b, uint8_t count) {
    byte ch;
    _n = 0;
    while(count--) {
        ch = *b;
        ch >>= 4;
        ch = digit2hexchar(ch);
        write(ch);
        ch = *b;
        ch &= 0x0F;
        ch = digit2hexchar(ch);
        write(ch);
        _n++;
        if((_n % dump_line_size) == 0)
          write('\n');
        else
          write(' ');
        b++;
    }
    return _n * 3;
} 

uint8_t Print::formatPrint(int n, uint8_t format) {
    _n = 0;
    if ((format % 0x1F == 10) and (n < 0)){
        n = -n;
        write('-');
        _n++;
    }
    printLNumber(n, format & 0x1F, 0xFF);
    format >>= 5;
    format++;
    while(_n < format){
      write('0');
      _n++;
    }
    writeChars();
    return _n;           
}

void Print::printLNumber(long number, uint8_t base, uint8_t precision){
    uint8_t ch;
    _len = 0;
    if (base < 2) 
        base = 10;
    do{
        if (_len == precision)
            _buffer[_len++] = '.';
        ch = number % base;
        ch = digit2hexchar(ch);
        number /= base;
        _buffer[_len++] = ch;

    }while(number);
}

void Print::addLeadingZeros(uint8_t precision){
    if ((precision == 0xFF) or (precision < _len))
        return;
    precision -= _len;
    while(precision--)
        _buffer[_len++] = '0';
    _buffer[_len++] = '.';
    _buffer[_len++] = '0';

}

void Print::writeChars(){
    while(_len--)
        write(_buffer[_len]);
}





