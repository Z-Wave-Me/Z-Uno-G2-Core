#ifndef ZUNO_LLCORE
#define ZUNO_LLCORE

#include <stdint.h>
#include <stdbool.h>


typedef struct ZUNOCodeHeader_s{
    char        sign[8];
    uint8_t     version_major;
    uint8_t     version_minor;
    uint16_t    code_size;
    uint16_t    crc16;
    uint32_t    flags;
    uint16_t    fwId;
} ZUNOCodeHeader_t;

// Universal pin location index
extern const uint8_t g_loc_pa0_pf7_all[];
extern const uint8_t g_loc_pa0_pf7_all_size;

#define INVALID_PIN_INDEX 0xFF
#endif