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
} ZUNOCodeHeader_t;
//static const PinDef_t ZUNO_PIN_DEFS[];
#define INVALID_PIN_INDEX 0xFF
#endif