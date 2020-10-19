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
const uint8_t g_loc_pa0_pf7_all[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
		0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
		0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
	};
const uint8_t g_loc_pa0_pf7_all_size = sizeof(g_loc_pa0_pf7_all);


const uint8_t g_loc_pf0_pf1_pf3_pf7[] = {
		0x50, 0x51, 0x53, 0x54, 0x55, 0x56, 0x57//PF0,PF1,PF3-PF7
	};

#define INVALID_PIN_INDEX 0xFF

uint8_t zunoIsMalloc(void *b);

#endif