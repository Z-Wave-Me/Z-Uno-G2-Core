#ifndef ARDUINO_LIKE_TYPES__
#define ARDUINO_LIKE_TYPES__
#include "ZUNO_Definitions.h"
#include <stdint.h>
#include "ZUNO_SysTypes.h"



typedef unsigned char 	boolean;
typedef unsigned char 	s_pin;

typedef unsigned int 	size_t;
typedef unsigned char   BYTE;
typedef uint16_t      	WORD;
typedef uint32_t        DWORD;
typedef unsigned char   XBYTE;
typedef unsigned char   CCBYTE;

typedef uint8_t         byte;
typedef uint16_t        word;
typedef uint32_t        dword;



#define TRUE    1
#define FALSE   0

//typedef unsigned long   time_t;

struct tmElements_s {
uint8_t Second;
uint8_t Minute;
uint8_t Hour;
uint8_t Wday; // day of week, sunday is day 1
uint8_t Day;
uint8_t Month;
uint8_t Year; // offset from 1970;
};


typedef struct tmElements_s tmElements_t;
typedef enum tmElementsFields{
    tmSecond, tmMinute, tmHour, tmWday, tmDay,tmMonth, tmYear, tmNbrFields
}tmElementsFields_t;	 

#include "string.h"




#endif // ARDUINO_LIKE_TYPES__