#include "SpiFlash.h"

#define SPI_FLASH_CLASS_CLOCK_MULTIPLIER										1000000

#define SPI_FLASH_CLASS_STATUS_WIP												0x01
#define SPI_FLASH_CLASS_STATUS_WEL												0x02

typedef struct						SpiFlashClassCmd_s
{
	uint8_t							command;
	uint8_t							buff[];
}									SpiFlashClassCmd_t;

typedef struct						SpiFlashClassCmdJedec_s
{
	uint8_t							command;
	uint8_t							ids[4];
}									SpiFlashClassCmdJedec_t;

typedef struct						SpiFlashClassCmdReadStatus_s
{
	uint8_t							command;
	uint8_t							status[0x1];
}									SpiFlashClassCmdReadStatus_t;

/* Constants */


/* Public Constructors */
SpiFlashClass::SpiFlashClass(SPIClass *spi, uint8_t ss): _device(0x0), _spi(spi), _clock(4000000), _ss(ss), _addr_byte(0x2) {
}

/* Public Methods */
ZUNO_ERROR_TYPE SpiFlashClass::begin(const SpiFlashClassDevice_t *device, uint32_t *JEDEC_ID) {
	SpiFlashClassCmdJedec_t					cmd_jedec;
	ZUNO_ERROR_TYPE							ret;
	size_t									manufacturer_id;
	size_t									memory_type;
	size_t									capacity;
	size_t									offset;
	uint32_t								refFreq;
	uint32_t								clock;

	pinMode(this->_ss, OUTPUT_UP);
	if ((ret = this->wakeUp()) != ZUNO_ERROR_SUCCESS)
		return (ret);
	if ((ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_READ_JEDEC_ID, &cmd_jedec, sizeof(cmd_jedec))) != ZUNO_ERROR_SUCCESS)
		return (ret);
	// For simplicity with commonly used device, we only check for continuation code at 2nd byte (e.g Fujitsu FRAM devices)
	if (cmd_jedec.ids[0x1] == 0x7F)
		offset = 0x2;
	else
		offset = 0x1;
	manufacturer_id = cmd_jedec.ids[0x0];
	memory_type = cmd_jedec.ids[offset + 0x0];
	capacity = cmd_jedec.ids[offset + 0x1];
	if (JEDEC_ID != 0x0)
		JEDEC_ID[0X0] = (manufacturer_id << 16) | (memory_type << 8) | capacity;
	if (device == 0x0)
		return (ZUNO_ERROR_SUCCESS);
	if (manufacturer_id != device->manufacturer_id || memory_type != device->memory_type || capacity != device->capacity)
		return (ZUNO_ERROR_SPI_FLASH_CLASS_NOT_MATCH_JEDEC_ID);
	this->_device = device;
	refFreq = 8 * SPI_FLASH_CLASS_CLOCK_MULTIPLIER;//CMU_ClockFreqGet(cmuClock_HFPER) - 0x1 / 0x2;
	clock = device->max_clock_speed_mhz * SPI_FLASH_CLASS_CLOCK_MULTIPLIER;
	if (clock > refFreq)
		clock = refFreq;
	this->_clock = clock;
	if (device->total_size > (64 * 1024))
		this->_addr_byte = 0x3;
	return (ZUNO_ERROR_SUCCESS);
}

ZUNO_ERROR_TYPE SpiFlashClass::waitBusy(void) {
	uint32_t										status;
	ZUNO_ERROR_TYPE									ret;

	while (true) {
		if ((ret = this->readStatus(&status)) != ZUNO_ERROR_SUCCESS)
			break ;
		if ((status & (SPI_FLASH_CLASS_STATUS_WIP | SPI_FLASH_CLASS_STATUS_WEL)) == 0x0)
			break ;
		delay(0x1);
	}
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::eraseChip(void) {
	ZUNO_ERROR_TYPE									ret;

	if ((ret = this->writeEnable()) != ZUNO_ERROR_SUCCESS)
		return (ret);
	if ((ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_ERASE_CHIP, 0x0, 0x0)) != ZUNO_ERROR_SUCCESS)
		return (ret);
	ret = this->waitBusy();
	if (ret != ZUNO_ERROR_SUCCESS)
		this->writeDisable();
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::_eraseBlock(uint32_t addr, size_t command) {
	const SpiFlashClassDevice_t						*device;
	ZUNO_ERROR_TYPE									ret;
	SpiFlashClassCmdRead_t							cmd_addr;
	size_t											cmd_addr_len;

	if ((device = this->_device) == 0x0)
		return (ZUNO_ERROR_SPI_FLASH_CLASS_NOT_INITILIZATION);
	if (device->total_size < addr)
		return (ZUNO_ERROR_SPI_FLASH_CLASS_INVALID_ARGUMENT);
	cmd_addr_len = this->_fillAddress(&cmd_addr.addr[0x0], addr) + sizeof(cmd_addr.command);
	if ((ret = this->writeEnable()) != ZUNO_ERROR_SUCCESS)
		return (ret);
	if ((ret = this->_sendCommand(command, &cmd_addr, sizeof(cmd_addr_len))) == ZUNO_ERROR_SUCCESS)
		ret = this->waitBusy();
	if (ret != ZUNO_ERROR_SUCCESS)
		this->writeDisable();
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::writeBuffer(uint32_t addr, const void *data, size_t len) {
	const SpiFlashClassDevice_t						*device;
	ZUNO_ERROR_TYPE									ret;
	size_t											page_size;
	SpiFlashClassCmdRead_t							cmd_addr;
	size_t											cmd_addr_len;
	size_t											step;

	if ((device = this->_device) == 0x0)
		return (ZUNO_ERROR_SPI_FLASH_CLASS_NOT_INITILIZATION);
	if (device->total_size < (addr + len))
		return (ZUNO_ERROR_SPI_FLASH_CLASS_INVALID_ARGUMENT);
	ret = ZUNO_ERROR_SUCCESS;
	page_size = device->page_size;
	step = page_size - (addr & (page_size - 0x1));
	cmd_addr.command = SPI_FLASH_CLASS_CMD_PAGE_PROGRAM;
	while (len != 0x0) {
		if ((ret = this->writeEnable()) != ZUNO_ERROR_SUCCESS)
			break ;
		cmd_addr_len = this->_fillAddress(&cmd_addr.addr[0x0], addr) + sizeof(cmd_addr.command);
		if (step > len)
			step = len;
		digitalWrite(this->_ss, LOW);//We inform slave about receiving data
		ret = this->_writeBuffer_add(&cmd_addr, cmd_addr_len, data, len);
		digitalWrite(this->_ss, HIGH);//We inform slave about receiving data
		if (ret != ZUNO_ERROR_SUCCESS)
			break ;
		if ((ret = this->waitBusy()) != ZUNO_ERROR_SUCCESS)
			break ;
		len = len - step;
		addr = addr + step;
		step = page_size;
	}
	if (ret != ZUNO_ERROR_SUCCESS)
		this->writeDisable();
	return (ret);

}

ZUNO_ERROR_TYPE SpiFlashClass::read(uint32_t addr, void *data, size_t len) {
	const SpiFlashClassDevice_t						*device;
	SpiFlashClassCmdRead_t							cmd_read;
	size_t											cmd_read_len;
	size_t											command;
	ZUNO_ERROR_TYPE									ret;

	if ((device = this->_device) == 0x0)
		return (ZUNO_ERROR_SPI_FLASH_CLASS_NOT_INITILIZATION);
	if (device->total_size < (addr + len))
		return (ZUNO_ERROR_SPI_FLASH_CLASS_INVALID_ARGUMENT);
	if (len == 0x0)
		return (ZUNO_ERROR_SUCCESS);
	cmd_read_len = this->_fillAddress(&cmd_read.addr[0x0], addr) + sizeof(cmd_read.command);
	if (device->supports_fast_read == true) {
		command = SPI_FLASH_CLASS_CMD_FAST_READ;
		cmd_read_len++;
	}
	else
		command = SPI_FLASH_CLASS_CMD_READ;
	cmd_read.command = command;
	digitalWrite(this->_ss, LOW);//We inform slave about receiving data
	ret = this->_read_add(&cmd_read, cmd_read_len, data, len);
	digitalWrite(this->_ss, HIGH);//We inform slave about receiving data
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::readStatus(uint32_t *status) {
	SpiFlashClassCmdReadStatus_t					read_status;
	ZUNO_ERROR_TYPE									ret;

	if ((ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_READ_STATUS, &read_status, sizeof(read_status))) != ZUNO_ERROR_SUCCESS)
		return (ret);
	status[0x0] = read_status.status[0x0];
	return (ZUNO_ERROR_SUCCESS);
}


ZUNO_ERROR_TYPE SpiFlashClass::writeEnable(void) {
	return (this->_sendCommand(SPI_FLASH_CLASS_CMD_WRITE_ENABLE, 0x0, 0x0));
}

ZUNO_ERROR_TYPE SpiFlashClass::writeDisable(void) {
	return (this->_sendCommand(SPI_FLASH_CLASS_CMD_WRITE_DISABLE, 0x0, 0x0));
}

ZUNO_ERROR_TYPE SpiFlashClass::sleep(void) {
	ZUNO_ERROR_TYPE						ret;

	ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_SLEEP, 0x0, 0x0);
	delay(0x1);
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::wakeUp(void) {
	ZUNO_ERROR_TYPE						ret;

	ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_WAKE_UP, 0x0, 0x0);
	delay(0x1);
	return (ret);
}

/* Private Methods */
ZUNO_ERROR_TYPE SpiFlashClass::_writeBuffer_add(const SpiFlashClassCmdRead_t *cmd_addr, size_t cmd_addr_len, const void *data, size_t len) {
	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	if (this->_spi->transfer(cmd_addr, cmd_addr_len) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	if (this->_spi->transfer(data, len) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	this->_spi->endTransaction();
	return (ZUNO_ERROR_SUCCESS);
}

ZUNO_ERROR_TYPE SpiFlashClass::_read_add(const SpiFlashClassCmdRead_t *cmd_read, size_t cmd_read_len, void *data, size_t len) {
	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	if (this->_spi->transfer(cmd_read, cmd_read_len) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	if (this->_spi->transfer(data, len) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	this->_spi->endTransaction();
	return (ZUNO_ERROR_SUCCESS);
}


size_t SpiFlashClass::_fillAddress(uint8_t *buff, uint32_t addr) {
	size_t										addr_byte;

	addr_byte = this->_addr_byte;
	if (addr_byte == 0x4)
		buff++[0x0] = (addr >> 24);
	if (addr_byte >= 0x3)
		buff++[0x0] = (addr >> 16) & 0xFF;
	buff++[0x0] = (addr >> 8) & 0xFF;
	buff++[0x0] = addr & 0xFF;
	return (addr_byte);
}


ZUNO_ERROR_TYPE SpiFlashClass::_sendCommand(size_t command, void *response, size_t len) {
	ZUNO_ERROR_TYPE									ret;

	digitalWrite(this->_ss, LOW);//We inform slave about receiving data
	ret = this->_sendCommandAdd(command, response, len);
	digitalWrite(this->_ss, HIGH);//We inform slave about receiving data
	return (ret);
}

ZUNO_ERROR_TYPE SpiFlashClass::_sendCommandAdd(size_t command, void *response, size_t len) {
	SpiFlashClassCmd_t					*cmd;

	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	if (len == 0x0) {
		response = &command;
		len = 0x1;
	}
	else {
		cmd = (SpiFlashClassCmd_t *)response;
		cmd->command = command;
	}
	if (this->_spi->transfer(response, len) != ZunoErrorOk)
		return (ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE);
	this->_spi->endTransaction();
	return (ZUNO_ERROR_SUCCESS);
}