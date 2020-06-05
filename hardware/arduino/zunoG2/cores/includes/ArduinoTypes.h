#ifndef ARDUINO_LIKE_TYPES__
#define ARDUINO_LIKE_TYPES__
#include "ZUNO_Definitions.h"
#include <stdint.h>
#include "ZUNO_SysTypes.h"



typedef unsigned char 	boolean;
typedef unsigned char 	s_pin;

typedef unsigned int 	size_t;
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned char   XBYTE;
typedef unsigned char   CCBYTE;

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned long   dword;



#define TRUE    1
#define FALSE   0

//typedef unsigned long   time_t;

struct tmElements_s {
    byte Second;
    byte Minute;
    byte Hour;
    byte Wday; // day of week, sunday is day 1
    byte Day;
    byte Month;
    byte Year; // offset from 1970;
};


typedef struct tmElements_s tmElements_t;

typedef enum tmElementsFields{
    tmSecond, tmMinute, tmHour, tmWday, tmDay,tmMonth, tmYear, tmNbrFields
}tmElementsFields_t;	 

#include "string.h"




#endif // ARDUINO_LIKE_TYPES__