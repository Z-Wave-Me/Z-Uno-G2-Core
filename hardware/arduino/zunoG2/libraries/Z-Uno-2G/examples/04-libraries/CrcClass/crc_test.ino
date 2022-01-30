
#include "Arduino.h"
#include "CrcClass.h"


#define MY_SERIAL Serial

void setup(){
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
}

typedef struct							Crc16Test_s
{
	uint16_t 							(*function)(const void *data, size_t len);
	const char							*name;
	uint16_t							crc;
}										Crc16Test_t;

const Crc16Test_t _crc16[] = {
	{
		.function = CrcClass::crc16_arc,
		.name = "CRC-16/ARC",
		.crc = 0xBB3D
	},
	{
		.function = CrcClass::crc16_ccitt_false,
		.name = "CRC-16/AUG-CCITT",
		.crc = 0x29B1
	},
	{
		.function = CrcClass::crc16_bypass,
		.name = "CRC-16/BUYPASS",
		.crc = 0xFEE8
	},
	{
		.function = CrcClass::crc16_ccitt_aug,
		.name = "CRC-16/CCITT-FALSE",
		.crc = 0xE5CC
	},
	{
		.function = CrcClass::crc16_cdma2000,
		.name = "CRC-16/CDMA2000",
		.crc = 0x4C06
	},
	{
		.function = CrcClass::crc16_dds_110,
		.name = "CRC-16/DDS-110",
		.crc = 0x9ECF
	},
	{
		.function = CrcClass::crc16_dect_r,
		.name = "CRC-16/DECT-R",
		.crc = 0x7E
	},
	{
		.function = CrcClass::crc16_dect_x,
		.name = "CRC-16/DECT-X",
		.crc = 0x7F
	},
	{
		.function = CrcClass::crc16_dnp,
		.name = "CRC-16/DNP",
		.crc = 0xEA82
	},
	{
		.function = CrcClass::crc16_en13757,
		.name = "CRC-16/EN",
		.crc = 0xC2B7
	},
	{
		.function = CrcClass::crc16_genibus,
		.name = "CRC-16/GENIBUS",
		.crc = 0xD64E
	},
	{
		.function = CrcClass::crc16_maxim,
		.name = "CRC-16/MAXIM",
		.crc = 0x44C2
	},
	{
		.function = CrcClass::crc16_mcrf4xx,
		.name = "CRC-16/MCRF4XX",
		.crc = 0x6F91
	},
	{
		.function = CrcClass::crc16_riello,
		.name = "CRC-16/RIELLO",
		.crc = 0x63D0
	},
	{
		.function = CrcClass::crc16_t10_dif,
		.name = "CRC-16/T10-DIF",
		.crc = 0xD0DB
	},
	{
		.function = CrcClass::crc16_teledisk,
		.name = "CRC-16/TELEDISK",
		.crc = 0xFB3
	},
	{
		.function = CrcClass::crc16_tms37157,
		.name = "CRC-16/TMS37157",
		.crc = 0x26B1
	},
	{
		.function = CrcClass::crc16_usb,
		.name = "CRC-16/USB",
		.crc = 0xB4C8
	},
	{
		.function = CrcClass::crc16_a,
		.name = "CRC-A",
		.crc = 0xBF05
	},
	{
		.function = CrcClass::crc16_kermit,
		.name = "CRC-16/KERMIT",
		.crc = 0x2189
	},
	{
		.function = CrcClass::crc16_modbus,
		.name = "CRC-16/MODBUS",
		.crc = 0x4B37
	},
	{
		.function = CrcClass::crc16_x_25,
		.name = "CRC-16/X-25",
		.crc = 0x906E
	},
	{
		.function = CrcClass::crc16_xmodem,
		.name = "CRC-16/XMODEM",
		.crc = 0x31C3
	}
};

typedef struct							Crc32Test_s
{
	uint32_t 							(*function)(const void *data, size_t len);
	const char							*name;
	uint32_t							crc;
}										Crc32Test_t;

const Crc32Test_t _crc32[] = {
	{
		.function = CrcClass::crc32_zlib,
		.name = "CRC-32/zlib",
		.crc = 0xCBF43926
	},
	{
		.function = CrcClass::crc32_bzip2,
		.name = "CRC-32/BZIP2",
		.crc = 0xFC891918
	},
	{
		.function = CrcClass::crc32_mpeg_2,
		.name = "CRC-32/MPEG-2",
		.crc = 0x376E6E7
	},
	{
		.function = CrcClass::crc32_posix,
		.name = "CRC-32/POSIX",
		.crc = 0x765E7680
	},
	{
		.function = CrcClass::crc32_jamcrc,
		.name = "CRC-32/JAMCRC",
		.crc = 0x340BC6D9
	},
};

static uint16_t _crc16_ccitt_aug(const void *data, size_t len) {
	size_t				i;
	uint16_t			crc16;
	const uint8_t		*b;

	crc16 = 0x1D0F;
	b = (const uint8_t *)data;
	while (len--) {
		crc16 = crc16 ^ b++[0x0] << 0x8;
		i = 0x0;
		while (i++ < 0x8)
			crc16 = ((crc16 & 0x8000) != 0x0) ? (crc16 << 0x1) ^ 0x1021 : crc16 << 0x1;
	}
	return (crc16);
}


uint16_t _crc16_ccitt_aug_table(const void *data, size_t len) {
	static const uint16_t Crc16_table[256] = {
		0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
		0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
		0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
		0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
		0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
		0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
		0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
		0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
		0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
		0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
		0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
		0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
		0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
		0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
		0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
		0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
		0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
		0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
		0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
		0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
		0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
		0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
		0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
		0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
		0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
		0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
		0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
		0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
		0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
		0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
	};
	uint16_t					crc16;
	const uint8_t				*b;

	crc16 = 0x1D0F;
	b = (const uint8_t *)data;
	while (len--)
		crc16 = (crc16 << 0x8) ^ Crc16_table[(crc16 >> 0x8) ^ b++[0x0]];
	return crc16;
}

void loop(){
	size_t			i;
	size_t			date_len;
	size_t			ms;
	uint16_t		crc16;

	MY_SERIAL.print("Crc16:\n");
	i = 0x0;
	while (i < (sizeof(_crc16) / sizeof(_crc16[0x0]))) {
		MY_SERIAL.print(_crc16[i].name);
		if (_crc16[i].function("123456789", 9) != _crc16[i].crc)
			MY_SERIAL.print(": False!\n");
		else
			MY_SERIAL.print(": Good!\n");
		i++;
	}
	MY_SERIAL.print("\n\n");

	MY_SERIAL.print("Crc32:\n");
	i = 0x0;
	while (i < (sizeof(_crc32) / sizeof(_crc32[0x0]))) {
		MY_SERIAL.print(_crc32[i].name);
		if (_crc32[i].function("123456789", 9) != _crc32[i].crc)
			MY_SERIAL.print(": False!\n");
		else
			MY_SERIAL.print(": Good!\n");
		i++;
	}
	MY_SERIAL.print("\n\n");

	MY_SERIAL.print("CRC-16/AUG-CCITT speed:\n");
	i = 0x0;
	date_len = 0x8;
	while (i <= 0x8) {
		ms = millis();
		crc16 = CrcClass::crc16_ccitt_aug(&_crc16[0x0], date_len);
		ms = millis() - ms;
		MY_SERIAL.printf("%u. data len: %u crc16 hardware:     %#X  ms:%u\n", i, date_len,crc16, ms);

		ms = millis();
		crc16 = _crc16_ccitt_aug_table(&_crc16[0x0], date_len);
		ms = millis() - ms;
		MY_SERIAL.printf("%u. data len: %u crc16 software tbl: %#X  ms:%u\n", i, date_len,crc16, ms);

		ms = millis();
		crc16 = _crc16_ccitt_aug(&_crc16[0x0], date_len);
		ms = millis() - ms;
		MY_SERIAL.printf("%u. data len: %u crc16 software:     %#X  ms:%u\n\n", i, date_len,crc16, ms);
	
		i++;
		date_len = date_len + 0x400;
	}
	delay(5000);
}