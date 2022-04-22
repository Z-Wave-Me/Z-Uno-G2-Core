#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "Arduino.h"
#include "SPI.h"
#include "ZunoError.h"

#define SPI_FLASH_CLASS_CMD_PAGE_PROGRAM										0x02
#define SPI_FLASH_CLASS_CMD_READ												0x03
#define SPI_FLASH_CLASS_CMD_WRITE_DISABLE										0x04
#define SPI_FLASH_CLASS_CMD_READ_STATUS											0x05
#define SPI_FLASH_CLASS_CMD_WRITE_ENABLE										0x06
#define SPI_FLASH_CLASS_CMD_FAST_READ											0x0B
#define SPI_FLASH_CLASS_CMD_ERASE_BLOCK_4K										0x20
#define SPI_FLASH_CLASS_CMD_READ_JEDEC_ID										0x9F
#define SPI_FLASH_CLASS_CMD_WAKE_UP												0xAB// deep power wake up
#define SPI_FLASH_CLASS_CMD_SLEEP												0xB9// deep power down
#define SPI_FLASH_CLASS_CMD_ERASE_CHIP											0xC7
#define SPI_FLASH_CLASS_CMD_ERASE_BLOCK_64K										0xD8

#define SPI_FLASH_CLASS_M25PE40						\
{ \
	.total_size = (0x1 << 0x16), \
	.page_size = (0x1 << 0x8), \
	.manufacturer_id = 0x20, \
	.memory_type = 0x80, \
	.capacity = 0x13, \
	.max_clock_speed_mhz = 33, \
	.supports_fast_read = true \
} \

#define ZUNO_ERROR_SPI_FLASH_CLASS_NOT_MATCH_JEDEC_ID										(ZUNO_ERROR_CONSTRUCTOR_SYSTEM(ZUNO_ERROR_TYPE_SPI_FLASH, 0x0))
#define ZUNO_ERROR_SPI_FLASH_CLASS_NOT_INITILIZATION										(ZUNO_ERROR_CONSTRUCTOR_SYSTEM(ZUNO_ERROR_TYPE_SPI_FLASH, 0x1))
#define ZUNO_ERROR_SPI_FLASH_CLASS_INVALID_ARGUMENT											(ZUNO_ERROR_CONSTRUCTOR_SYSTEM(ZUNO_ERROR_TYPE_SPI_FLASH, 0x2))

typedef struct						SpiFlashClassDevice_s
{
	uint32_t						total_size;
	uint16_t						page_size;
	// Three response bytes to 0x9f JEDEC ID command.
	uint8_t							manufacturer_id;
	uint8_t							memory_type;
	uint8_t							capacity;
	// Max clock speed for all operations and the fastest read mode.
	uint8_t							max_clock_speed_mhz;
	// Supports the 0x0b fast read command with 8 dummy cycles.
	bool							supports_fast_read : 0x1;
}									SpiFlashClassDevice_t;

typedef struct						SpiFlashClassCmdRead_s
{
	uint8_t							command;
	uint8_t							addr[0x4];
	uint8_t							dummy;
}									SpiFlashClassCmdRead_t;

class SpiFlashClass {
	public:
		SpiFlashClass(SPIClass *spi, uint8_t ss);
		inline ZUNO_ERROR_TYPE										begin(const SpiFlashClassDevice_t *device) {return (this->begin(device, 0x0));};
		ZUNO_ERROR_TYPE												begin(const SpiFlashClassDevice_t *device, uint32_t *JEDEC_ID);
		ZUNO_ERROR_TYPE												sleep(void);
		ZUNO_ERROR_TYPE												wakeUp(void);
		ZUNO_ERROR_TYPE												eraseChip(void);
		inline ZUNO_ERROR_TYPE										eraseBlock4k(uint32_t addr) {return (this->_eraseBlock(addr, SPI_FLASH_CLASS_CMD_ERASE_BLOCK_4K));};
		inline ZUNO_ERROR_TYPE										eraseBlock64k(uint32_t addr) {return (this->_eraseBlock(addr, SPI_FLASH_CLASS_CMD_ERASE_BLOCK_64K));};
		ZUNO_ERROR_TYPE												writeEnable(void);
		ZUNO_ERROR_TYPE												writeDisable(void);
		ZUNO_ERROR_TYPE												readStatus(uint32_t *status);
		ZUNO_ERROR_TYPE												waitBusy(void);
		ZUNO_ERROR_TYPE												read(uint32_t addr, void *data, size_t len);
		ZUNO_ERROR_TYPE												writeBuffer(uint32_t addr, const void *data, size_t len);

	private:
		ZUNO_ERROR_TYPE												_eraseBlock(uint32_t addr, size_t command);
		inline ZUNO_ERROR_TYPE										_writeBuffer_add(const SpiFlashClassCmdRead_t *cmd_addr, size_t cmd_addr_len, const void *data, size_t len);
		inline ZUNO_ERROR_TYPE										_read_add(const SpiFlashClassCmdRead_t *cmd_read, size_t cmd_read_len, void *data, size_t len);
		inline size_t												_fillAddress(uint8_t *buff, uint32_t addr);
		inline ZUNO_ERROR_TYPE										_sendCommand(size_t command, void *response, size_t len);
		inline ZUNO_ERROR_TYPE										_sendCommandAdd(size_t command, void *response, size_t len);
		const SpiFlashClassDevice_t					*_device;
		SPIClass									*_spi;
		uint32_t									_clock;
		uint8_t										_ss;
		uint8_t										_addr_byte;
};

#endif// ZUNO_SPI_FLASH_H