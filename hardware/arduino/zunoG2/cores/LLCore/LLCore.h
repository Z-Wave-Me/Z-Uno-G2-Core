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
	uint32_t    jumptable_offset;
	uint32_t    build_timestamp;
	uint8_t     console_pin;
	uint16_t    sketch_version;
	uint8_t     ota_firmwares_count;
	ZUNOOTAFWDescr_t * ota_firmwares_descriptions;
	uint32_t    ota_pincode;
} ZUNOCodeHeader_t;

// Universal apport index
const uint8_t g_aport_pa0_pf7_all[] = {//APORT3Y APORT3X APORT1Y APORT1X
		0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,//PA0-PA5 - CH8-CH13 - APORT3
		0x7B, 0x7C, 0x7D, 0x7E, 0x7F,//PB11-PB15 - CH27-CH31 - APORT3
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, //PC6-PC11 - CH6-CH11 - APORT1
		0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, //PD9-PD15 - CH1-CH7 - APORT3
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37//PF0-PF7 - CH16-CH23 - APORT1
	};

// Universal pin location index
const uint8_t g_loc_pa0_pf7_all[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
		0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
		0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
	};
const uint8_t g_loc_pa0_pf7_all_size = sizeof(g_loc_pa0_pf7_all);

// Usable for USART2
const uint8_t g_loc_pa5_pf0_pf1_pf3_pf7[] = {
	    0x05,                                	   // LOC0
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // LOC1-13 is deprecated
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
		0x50, 0x51, 0x53, 0x54, 0x55, 0x56, 0x57	//PF0=LOC14,PF1=LOC15,PF3-PF7 (LOC16-LOC20)
};
#define MAX_VALID_PINLOCATION 31
#define INVALID_PIN_INDEX 0xFF
typedef struct	PinDef_s
{
	uint8_t		port;
	uint8_t		pin;
}				PinDef_t;

extern const PinDef_t ZUNO_PIN_DEFS[];

#endif