#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

uint32_t GetLastStatus(void);
void SetLastStatus (uint32_t status);

// |3 3|2 2 2|2 2 2 2 2 2 2 1 1 1 1 1 1|1 1 1 1 0 0 0 0 0 0 0 0 0 0|
// |1 0|9 8 7|6 5 4 3 2 1 0 9 8 7 6 5 4|3 2 1 0 9 8 7 6 5 4 3 2 1 0|
// +---+-----+-------------------------+---------------------------+
// |Sev|  R  |   Facility              |           Code            |
// +---+-----+-------------------------+---------------------------+
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      R - is a reserved
//
//      Facility - is the facility code
//
//      Code - is the facility's status code

#define STATUS_SEV_SUCESS											0x0
#define STATUS_SEV_INFORMATIONAL									0x1
#define STATUS_SEV_WARNING											0x2
#define STATUS_SEV_ERROR											0x3

#define STATUS_SEV_MASK												0xC0000000
#define STATUS_SEV_SHIFT											0x1E

#define STATUS_FACILITY_MASK										0x7FFC000
#define STATUS_FACILITY_SHIFT										0xE

#define STATUS_CODE_MASK											0x3FFF
#define STATUS_CODE_SHIFT											0x0
#define STATUS_CODE_EXTENDED										0x2000

#define STATUS_CONSTRUCTOR(SEV, FACILITY, CODE)						((uint32_t)(((SEV << STATUS_SEV_SHIFT) & STATUS_SEV_MASK) | ((FACILITY << STATUS_FACILITY_SHIFT) & STATUS_FACILITY_MASK) | ((CODE << STATUS_CODE_SHIFT) & STATUS_CODE_MASK)))
#define STATUS_CONSTRUCTOR_EXTENDED(SEV, FACILITY, CODE)			((uint32_t)(((SEV << STATUS_SEV_SHIFT) & STATUS_SEV_MASK) | ((FACILITY << STATUS_FACILITY_SHIFT) & STATUS_FACILITY_MASK) | (((CODE << STATUS_CODE_SHIFT) | STATUS_CODE_EXTENDED) & STATUS_CODE_MASK)))

#define STATUS_FACILITY_NULL										0x0
#define STATUS_FACILITY_DS_1307_RTC									0x1
#define STATUS_FACILITY_SPI_FLASH									0x2
#define STATUS_FACILITY_MOD_BUS										0x3
#define STATUS_FACILITY_PN160										0x4


/* The operation completed successfully. */
#define STATUS_SUCCESS												((uint32_t)0x0)

/* One or more arguments are not correct. */
#define STATUS_BAD_ARGUMENTS										((uint32_t)0x1)

/* There was no initialization. */
#define STATUS_NOT_INITILIZATION									((uint32_t)0x2)

/* ID doesn't match. */
#define STATUS_ID_NOT_MATCH											((uint32_t)0x3)

/* Can't find a suitable device. */
#define STATUS_DEVICE_NOT_FOUND										((uint32_t)0x4)

/* The wait operation timed out. */
#define STATUS_WAIT_TIMEOUT											((uint32_t)0x5)

/* Crc doesn't match. */
#define STATUS_CRC_NOT_MATCH										((uint32_t)0x6)

/* Buffer overlow. */
#define STATUS_BUFFER_OVERFLOW										((uint32_t)0x7)

/* Not enough data */
#define STATUS_NOT_ENOUGH_DATA										((uint32_t)0x8)

/* Not enough memory */
#define STATUS_NOT_ENOUGH_MEMORY									((uint32_t)0x9)

#define STATUS_TMP_FOR_REPLACE										((uint32_t)0xFFFFFFFF)

#endif//STATUS_H
