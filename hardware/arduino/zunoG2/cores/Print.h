#ifndef _ZUNO_PRINT_H
#define _ZUNO_PRINT_H

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#include "ArduinoTypes.h"
#include <math.h>
#include <string.h>

class Print{
	public:
		inline size_t print(const char s[]) {return (this->write(s));};
		inline size_t print(char c) {return (this->write(c));};
		inline size_t print(unsigned char n, int base = DEC) {return (this->print((unsigned long)n, base));};
		inline size_t print(int n, int base = DEC) {return (this->print((long) n, base));};
		inline size_t print(unsigned int n, int base = DEC) {return (this->print((unsigned long) n, base));};
		size_t print(long n, int base = DEC);
		size_t print(unsigned long n, int base = DEC);
		inline size_t print(float n, int digits = 2) {return (this->printFloat(n, digits));};

		size_t println(const char[]);
		size_t println(char);
		size_t println(unsigned char, int = DEC);
		size_t println(int, int = DEC);
		size_t println(unsigned int, int = DEC);
		size_t println(long, int = DEC);
		size_t println(unsigned long, int = DEC);
		size_t println(float, int = 2);
		inline size_t println(void) {return (this->write("\r\n"));};

		inline size_t printNumber(unsigned long n, uint8_t base) {return (this->print(n, base));};
		size_t printFloat(float, uint8_t digits); 

		uint8_t fixPrint(long, uint8_t  = 2);
		size_t dumpPrint(uint8_t *b, size_t count, size_t line_size = 10);
		uint8_t formatPrint(int n, uint8_t format);

		virtual uint8_t write(uint8_t) = 0;
		virtual size_t write(const uint8_t *buffer, size_t size) = 0;

		size_t write(const char *str);
		inline size_t write(const char *buffer, size_t size) {return (this->write((const uint8_t *)buffer, size));}

	private:
		inline size_t _digit2hexchar(size_t d) {return ((d > 9) ? d - 10 + 'A' : d + '0');};
};

#endif // _ZUNO_PRINT_H