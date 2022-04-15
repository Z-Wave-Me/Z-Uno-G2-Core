#ifndef CRC_CLASS_H
#define CRC_CLASS_H


class CrcClass {
	public:
		CrcClass(void) {};
		static uint8_t					crc8_sapi(const void *data, size_t len) {return (CrcClass::crc8_sapi(0xFF, data, len));};
		static uint8_t					crc8_sapi(uint8_t initValue, const void *data, size_t len);

		static uint16_t					crc16_arc(const void *data, size_t len) {return (CrcClass::crc16_arc(0x0, data, len));};
		static uint16_t					crc16_arc(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len));};

		static uint16_t					crc16_ccitt_aug(const void *data, size_t len) {return (CrcClass::crc16_ccitt_aug(0x1D0F, data, len));};
		static uint16_t					crc16_ccitt_aug(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x1021, (__RBIT(initValue) >> 0x10), data, len));};

		static uint16_t					crc16_ccitt_false(const void *data, size_t len) {return (CrcClass::crc16_ccitt_false(0xFFFF, data, len));};
		static uint16_t					crc16_ccitt_false(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len));};

		static uint16_t					crc16_bypass(const void *data, size_t len) {return (CrcClass::crc16_bypass(0x0, data, len));};
		static uint16_t					crc16_bypass(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x8005, initValue, data, len));};

		static uint16_t					crc16_cdma2000(const void *data, size_t len) {return (CrcClass::crc16_cdma2000(0xFFFF, data, len));};
		static uint16_t					crc16_cdma2000(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0xC867, initValue, data, len));};

		static uint16_t					crc16_dds_110(const void *data, size_t len) {return (CrcClass::crc16_dds_110(0x800d, data, len));};
		static uint16_t					crc16_dds_110(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x8005, (__RBIT(initValue) >> 0x10), data, len));};

		static uint16_t					crc16_dect_r(const void *data, size_t len) {return (CrcClass::crc16_dect_r(0x0, data, len));};
		static uint16_t					crc16_dect_r(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x589, initValue, data, len) ^ 0x1);};

		static uint16_t					crc16_dect_x(const void *data, size_t len) {return (CrcClass::crc16_dect_x(0x0, data, len));};
		static uint16_t					crc16_dect_x(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x0589, initValue, data, len));};

		static uint16_t					crc16_dnp(const void *data, size_t len) {return (CrcClass::crc16_dnp(0x0, data, len));};
		static uint16_t					crc16_dnp(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x3D65, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_en13757(const void *data, size_t len) {return (CrcClass::crc16_en13757(0x0, data, len));};
		static uint16_t					crc16_en13757(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x3D65, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_genibus(const void *data, size_t len) {return (CrcClass::crc16_genibus(0xFFFF, data, len));};
		static uint16_t					crc16_genibus(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_maxim(const void *data, size_t len) {return (CrcClass::crc16_maxim(0x0, data, len));};
		static uint16_t					crc16_maxim(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_mcrf4xx(const void *data, size_t len) {return (CrcClass::crc16_mcrf4xx(0xFFFF, data, len));};
		static uint16_t					crc16_mcrf4xx(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		static uint16_t					crc16_riello(const void *data, size_t len) {return (CrcClass::crc16_riello(0xB2AA, data, len));};
		static uint16_t					crc16_riello(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, (__RBIT(initValue) >> 0x10), data, len));};

		static uint16_t					crc16_t10_dif(const void *data, size_t len) {return (CrcClass::crc16_t10_dif(0x0, data, len));};
		static uint16_t					crc16_t10_dif(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x8BB7, initValue, data, len));};

		static uint16_t					crc16_teledisk(const void *data, size_t len) {return (CrcClass::crc16_teledisk(0x0, data, len));};
		static uint16_t					crc16_teledisk(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0xA097, initValue, data, len));};

		static uint16_t					crc16_tms37157(const void *data, size_t len) {return (CrcClass::crc16_tms37157(0x89EC, data, len));};
		static uint16_t					crc16_tms37157(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, (__RBIT(initValue) >> 0x10), data, len));};

		static uint16_t					crc16_usb(const void *data, size_t len) {return (CrcClass::crc16_usb(0xFFFF, data, len));};
		static uint16_t					crc16_usb(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_a(const void *data, size_t len) {return (CrcClass::crc16_a(0xC6C6, data, len));};
		static uint16_t					crc16_a(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, (__RBIT(initValue) >> 0x10), data, len));};

		static uint16_t					crc16_kermit(const void *data, size_t len) {return (CrcClass::crc16_kermit(0x0, data, len));};
		static uint16_t					crc16_kermit(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		static uint16_t					crc16_modbus(const void *data, size_t len) {return (CrcClass::crc16_modbus(0xFFFF, data, len));};
		static uint16_t					crc16_modbus(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len));};

		static uint16_t					crc16_x_25(const void *data, size_t len) {return (CrcClass::crc16_x_25(0xFFFF, data, len));};
		static uint16_t					crc16_x_25(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len) ^ 0xFFFF);};

		static uint16_t					crc16_xmodem(const void *data, size_t len) {return (CrcClass::crc16_xmodem(0x0, data, len));};
		static uint16_t					crc16_xmodem(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len));};

		static uint32_t					crc32_zlib(const void *data, size_t len) {return (CrcClass::crc32_zlib(0xFFFFFFFF, data, len));};
		static uint32_t					crc32_zlib(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		static uint32_t					crc32_bzip2(const void *data, size_t len) {return (CrcClass::crc32_bzip2(0xFFFFFFFF, data, len));};
		static uint32_t					crc32_bzip2(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		static uint32_t					crc32_mpeg_2(const void *data, size_t len) {return (CrcClass::crc32_mpeg_2(0xFFFFFFFF, data, len));};
		static uint32_t					crc32_mpeg_2(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len));};

		static uint32_t					crc32_posix(const void *data, size_t len) {return (CrcClass::crc32_posix(0x0, data, len));};
		static uint32_t					crc32_posix(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		static uint32_t					crc32_jamcrc(const void *data, size_t len) {return (CrcClass::crc32_jamcrc(0xFFFFFFFF, data, len));};
		static uint32_t					crc32_jamcrc(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_crc_RefInTrue_RefOutTrue(0x04C11DB7, initValue, data, len));};

		// static uint16_t					DMA_crc16_arc(const void *data, size_t len) {return (CrcClass::DMA_crc16_arc(0x0, data, len));};
		// static uint16_t					DMA_crc16_arc(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len));};

		// static uint16_t					DMA_crc16_ccitt_aug(const void *data, size_t len) {return (CrcClass::DMA_crc16_ccitt_aug(0xF0B8, data, len));};//reverse 0x1D0F
		// static uint16_t					DMA_crc16_ccitt_aug(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_ccitt_false(const void *data, size_t len) {return (CrcClass::DMA_crc16_ccitt_false(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_ccitt_false(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_bypass(const void *data, size_t len) {return (CrcClass::DMA_crc16_bypass(0x0, data, len));};
		// static uint16_t					DMA_crc16_bypass(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x8005, initValue, data, len));};

		// static uint16_t					DMA_crc16_cdma2000(const void *data, size_t len) {return (CrcClass::DMA_crc16_cdma2000(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_cdma2000(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0xC867, initValue, data, len));};

		// static uint16_t					DMA_crc16_dds_110(const void *data, size_t len) {return (CrcClass::DMA_crc16_dds_110(0xB001, data, len));};//reverse 0x800d
		// static uint16_t					DMA_crc16_dds_110(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x8005, initValue, data, len));};

		// static uint16_t					DMA_crc16_dect_r(const void *data, size_t len) {return (CrcClass::DMA_crc16_dect_r(0x0, data, len));};
		// static uint16_t					DMA_crc16_dect_r(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x589, initValue, data, len) ^ 0x1);};

		// static uint16_t					DMA_crc16_dect_x(const void *data, size_t len) {return (CrcClass::DMA_crc16_dect_x(0x0, data, len));};
		// static uint16_t					DMA_crc16_dect_x(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x0589, initValue, data, len));};

		// static uint16_t					DMA_crc16_dnp(const void *data, size_t len) {return (CrcClass::DMA_crc16_dnp(0x0, data, len));};
		// static uint16_t					DMA_crc16_dnp(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x3D65, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_en13757(const void *data, size_t len) {return (CrcClass::DMA_crc16_en13757(0x0, data, len));};
		// static uint16_t					DMA_crc16_en13757(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x3D65, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_genibus(const void *data, size_t len) {return (CrcClass::DMA_crc16_genibus(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_genibus(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_maxim(const void *data, size_t len) {return (CrcClass::DMA_crc16_maxim(0x0, data, len));};
		// static uint16_t					DMA_crc16_maxim(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_mcrf4xx(const void *data, size_t len) {return (CrcClass::DMA_crc16_mcrf4xx(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_mcrf4xx(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_riello(const void *data, size_t len) {return (CrcClass::DMA_crc16_riello(0x554D, data, len));};//reverse 0xB2AA
		// static uint16_t					DMA_crc16_riello(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_t10_dif(const void *data, size_t len) {return (CrcClass::DMA_crc16_t10_dif(0x0, data, len));};
		// static uint16_t					DMA_crc16_t10_dif(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x8BB7, initValue, data, len));};

		// static uint16_t					DMA_crc16_teledisk(const void *data, size_t len) {return (CrcClass::DMA_crc16_teledisk(0x0, data, len));};
		// static uint16_t					DMA_crc16_teledisk(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0xA097, initValue, data, len));};

		// static uint16_t					DMA_crc16_tms37157(const void *data, size_t len) {return (CrcClass::DMA_crc16_tms37157(0x3791, data, len));};//reverse 0x89EC
		// static uint16_t					DMA_crc16_tms37157(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_usb(const void *data, size_t len) {return (CrcClass::DMA_crc16_usb(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_usb(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_a(const void *data, size_t len) {return (CrcClass::DMA_crc16_a(0x6363, data, len));};//reverse 0xC6C6
		// static uint16_t					DMA_crc16_a(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_kermit(const void *data, size_t len) {return (CrcClass::DMA_crc16_kermit(0x0, data, len));};
		// static uint16_t					DMA_crc16_kermit(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len));};

		// static uint16_t					DMA_crc16_modbus(const void *data, size_t len) {return (CrcClass::DMA_crc16_modbus(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_modbus(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x8005, initValue, data, len));};

		// static uint16_t					DMA_crc16_x_25(const void *data, size_t len) {return (CrcClass::DMA_crc16_x_25(0xFFFF, data, len));};
		// static uint16_t					DMA_crc16_x_25(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x1021, initValue, data, len) ^ 0xFFFF);};

		// static uint16_t					DMA_crc16_xmodem(const void *data, size_t len) {return (CrcClass::DMA_crc16_xmodem(0x0, data, len));};
		// static uint16_t					DMA_crc16_xmodem(uint16_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x1021, initValue, data, len));};

		// static uint32_t					DMA_crc32_zlib(const void *data, size_t len) {return (CrcClass::DMA_crc32_zlib(0xFFFFFFFF, data, len));};
		// static uint32_t					DMA_crc32_zlib(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		// static uint32_t					DMA_crc32_bzip2(const void *data, size_t len) {return (CrcClass::DMA_crc32_bzip2(0xFFFFFFFF, data, len));};
		// static uint32_t					DMA_crc32_bzip2(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		// static uint32_t					DMA_crc32_mpeg_2(const void *data, size_t len) {return (CrcClass::DMA_crc32_mpeg_2(0xFFFFFFFF, data, len));};
		// static uint32_t					DMA_crc32_mpeg_2(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len));};

		// static uint32_t					DMA_crc32_posix(const void *data, size_t len) {return (CrcClass::DMA_crc32_posix(0x0, data, len));};
		// static uint32_t					DMA_crc32_posix(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInFalse_RefOutFalse(0x04C11DB7, initValue, data, len) ^ 0xFFFFFFFF);};

		// static uint32_t					DMA_crc32_jamcrc(const void *data, size_t len) {return (CrcClass::DMA_crc32_jamcrc(0xFFFFFFFF, data, len));};
		// static uint32_t					DMA_crc32_jamcrc(uint32_t initValue, const void *data, size_t len) {return (CrcClass::_dma_crc_RefInTrue_RefOutTrue(0x04C11DB7, initValue, data, len));};


	private:
		static uint32_t					_crc_RefInFalse_RefOutFalse(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len);
		static uint32_t					_crc_RefInTrue_RefOutTrue(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len);
		// static uint32_t					_dma_crc_RefInFalse_RefOutFalse(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len);
		// static uint32_t					_dma_crc_RefInTrue_RefOutTrue(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len);

};

#endif//CRC_CLASS_H