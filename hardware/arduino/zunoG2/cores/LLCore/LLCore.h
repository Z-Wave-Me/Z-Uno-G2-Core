#ifndef ZUNO_LLCORE
#define ZUNO_LLCORE

#include <stdint.h>
#include <stdbool.h>
#include "ZUNO_SysTypes.h"

#define MAX_SKETCH_NAME  48
#define INVALID_VALUE    0xFF

#ifndef DBG_CONSOLE_BAUDRATE
#define DBG_CONSOLE_BAUDRATE 230400
#endif // DBG_CONSOLE_BAUDRATE

typedef struct ZUNOCodeHeader_s{
    char        sign[8];
    uint8_t     version_major;
    uint8_t     version_minor;
    uint16_t    code_size;
    uint16_t    crc16;
    uint32_t    flags;
    uint16_t    fwId;
	uint32_t    jumptable_offset;
	uint32_t    build_timestamp;
	uint8_t     console_pin;
	uint32_t 	console_baud;	
	uint16_t    sketch_version;
	uint8_t     ota_firmwares_count;
	ZUNOOTAFWDescr_t * ota_firmwares_descriptions;
	uint32_t    ota_pincode;
	uint32_t    ota_custom_offset;
	char        name[MAX_SKETCH_NAME];
	uint16_t    hw_id;
} ZUNOCodeHeader_t;

void WDOG_Feed();

extern ZUNOSetupSysState_t * g_zuno_sys;

#endif