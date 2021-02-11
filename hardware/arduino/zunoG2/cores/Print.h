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
    Print(){dump_line_size = 10;};

    void setDumpLine(uint8_t line_size) {dump_line_size = line_size;};

    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(float, int = 2);

    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(float, int = 2);
    size_t println(void);

    size_t printNumber(unsigned long, uint8_t base);
    size_t printFloat(float, uint8_t digits); 

    uint8_t fixPrint(long, uint8_t  = 2);
    word    dumpPrint(uint8_t *, uint8_t);
    uint8_t formatPrint(int n, uint8_t format);

    virtual uint8_t write(uint8_t) = 0;
    virtual size_t write(const uint8_t *buffer, size_t size) = 0;

    size_t write(const char *str);
    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }
private:
    uint8_t dump_line_size;
    uint8_t _buffer[32];
    uint8_t _n;
    uint8_t _len;
    void printLNumber(long number, uint8_t base, uint8_t precision);
    void addLeadingZeros(uint8_t precision);
    void writeChars();
};

#endif // _ZUNO_PRINT_H