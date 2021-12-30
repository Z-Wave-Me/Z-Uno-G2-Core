#ifndef ZWAVEME_GPCRC_ADD_H
#define ZWAVEME_GPCRC_ADD_H

#include "em_gpcrc.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t crc8_sapi(const void *data, size_t len);
uint16_t crc16_ccitt(const void *data, size_t len);
uint16_t crc16_bypass(const void *data, size_t len);
uint16_t crc16_xmodem(const void *data, size_t len);
uint16_t crc16_teledisk(const void *data, size_t len);
uint16_t crc16_augccitt(const void *data, size_t len);
uint16_t crc16_cdma2000(const void *data, size_t len);
uint16_t crc16_dds110(const void *data, size_t len);
uint16_t crc16_dect_x(const void *data, size_t len);
uint16_t crc16_dect_r(const void *data, size_t len);
uint16_t crc16_en13757(const void *data, size_t len);
uint16_t crc16_t10dif(const void *data, size_t len);
uint16_t crc16_modbus(const void *data, size_t len);
uint32_t crc32_posix(const void *data, size_t len);
uint32_t crc32_mpeg2(const void *data, size_t len);
uint32_t crc32_jamcrc(const void *data, size_t len);
uint32_t crc32_bzip2(const void *data, size_t len);
uint32_t crc32_zlib(const void *data, size_t len);
uint32_t crc32_zlibStream(uint32_t initValue, const void *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_GPCRC_ADD_H