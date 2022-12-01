#include "SpiFlash.h"
#include "Status.h"

#define SPI_FLASH_CLASS_CLOCK_MULTIPLIER										1000000

#define SPI_FLASH_CLASS_STATUS_WIP												0x01
#define SPI_FLASH_CLASS_STATUS_WEL												0x02

typedef struct						SpiFlashClassCmd_s
{
	uint8_t							command;
	uint8_t							buff[];
}									SpiFlashClassCmd_t;

typedef struct						SpiFlashClassCmdReadStatus_s
{
	uint8_t							command;
	uint8_t							status[0x1];
}									SpiFlashClassCmdReadStatus_t;

/* Constants */
static const SpiFlashClassDevice_t					_device_all[] =
{
	SPI_FLASH_CLASS_M25PE40
};

/* Public Constructors */
SpiFlashClass::SpiFlashClass(void): _device(0x0), _spi(&SPI), _clock(4000000), _sck(SCK), _miso(MISO), _mosi(MOSI), _ss(9), _addr_byte(0x2) {
}

SpiFlashClass::SpiFlashClass(SPIClass *spi, uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss): _device(0x0), _spi(spi), _clock(4000000), _sck(sck), _miso(miso), _mosi(mosi), _ss(ss), _addr_byte(0x2) {
}

/* Public Methods */
bool SpiFlashClass::getJEDECID(uint32_t *JEDEC_ID) {
	const SpiFlashClassDevice_t						*device;

	if ((device = this->_device) == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_NOT_INITILIZATION), false));
	JEDEC_ID[0X0] = (device->manufacturer_id << 16) | (device->memory_type << 8) | device->capacity;
	return (true);
}

bool SpiFlashClass::begin(void) {
	SpiFlashClassCmdJedec_t					cmd_jedec;
	size_t									manufacturer_id;
	size_t									memory_type;
	size_t									capacity;
	const SpiFlashClassDevice_t				*b;
	const SpiFlashClassDevice_t				*e;
	if (this->_init(&cmd_jedec) != true)
		return (false);
	manufacturer_id = cmd_jedec.ids[0x0];
	memory_type = cmd_jedec.ids[0x1];
	capacity = cmd_jedec.ids[0x2];
	b = &_device_all[0x0];
	e = &_device_all[(sizeof(_device_all) / sizeof(_device_all[0x0]))];
	while (b < e) {
		if (manufacturer_id == b->manufacturer_id && memory_type == b->memory_type && capacity == b->capacity)
			return (this->_init_end(b, &cmd_jedec));
		b++;
	}
	return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_DEVICE_NOT_FOUND), false));
}

bool SpiFlashClass::begin(uint32_t *JEDEC_ID) {
	SpiFlashClassCmdJedec_t					cmd_jedec;
	size_t									manufacturer_id;
	size_t									memory_type;
	size_t									capacity;

	if (this->_init(&cmd_jedec) != true)
		return (false);
	manufacturer_id = cmd_jedec.ids[0x0];
	memory_type = cmd_jedec.ids[0x1];
	capacity = cmd_jedec.ids[0x2];
	JEDEC_ID[0X0] = (manufacturer_id << 16) | (memory_type << 8) | capacity;
	return (true);
}

bool SpiFlashClass::begin(const SpiFlashClassDevice_t *device) {
	SpiFlashClassCmdJedec_t					cmd_jedec;

	if (this->_init(&cmd_jedec) != true)
		return (false);
	return (this->_init_end(device, &cmd_jedec));
}

bool SpiFlashClass::waitBusy(void) {
	uint32_t										status;
	bool											ret;

	while (true) {
		if ((ret = this->readStatus(&status)) != true)
			break ;
		if ((status & (SPI_FLASH_CLASS_STATUS_WIP | SPI_FLASH_CLASS_STATUS_WEL)) == 0x0)
			break ;
		delay(0x1);
	}
	return (ret);
}

bool SpiFlashClass::eraseChip(void) {
	bool									ret;

	if (this->writeEnable() != true)
		return (false);
	if (this->_sendCommand(SPI_FLASH_CLASS_CMD_ERASE_CHIP, 0x0, 0x0) != true)
		return (false);
	ret = this->waitBusy();
	if (ret != true)
		this->writeDisable();
	return (ret);
}

bool SpiFlashClass::_eraseBlock(uint32_t addr, size_t command) {
	const SpiFlashClassDevice_t						*device;
	bool											ret;
	SpiFlashClassCmdRead_t							cmd_addr;
	size_t											cmd_addr_len;

	if ((device = this->_device) == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_NOT_INITILIZATION), false));
	if (device->total_size < addr)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_BAD_ARGUMENTS), false));
	cmd_addr_len = this->_fillAddress(&cmd_addr.addr[0x0], addr) + sizeof(cmd_addr.command);
	if (this->writeEnable() != true)
		return (false);
	if ((ret = this->_sendCommand(command, &cmd_addr, sizeof(cmd_addr_len))) == true)
		ret = this->waitBusy();
	if (ret != true)
		this->writeDisable();
	return (ret);
}

bool SpiFlashClass::writeBuffer(uint32_t addr, const void *data, size_t len) {
	const SpiFlashClassDevice_t						*device;
	bool											ret;
	size_t											page_size;
	SpiFlashClassCmdRead_t							cmd_addr;
	size_t											cmd_addr_len;
	size_t											step;

	if ((device = this->_device) == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_NOT_INITILIZATION), false));
	if (device->total_size < (addr + len))
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_BAD_ARGUMENTS), false));
	ret = true;
	page_size = device->page_size;
	step = page_size - (addr & (page_size - 0x1));
	cmd_addr.command = SPI_FLASH_CLASS_CMD_PAGE_PROGRAM;
	while (len != 0x0) {
		if ((ret = this->writeEnable()) != true)
			break ;
		cmd_addr_len = this->_fillAddress(&cmd_addr.addr[0x0], addr) + sizeof(cmd_addr.command);
		if (step > len)
			step = len;
		digitalWrite(this->_ss, LOW);//We inform slave about receiving data
		ret = this->_writeBuffer_add(&cmd_addr, cmd_addr_len, data, len);
		digitalWrite(this->_ss, HIGH);//We inform slave about receiving data
		if (ret != true)
			break ;
		delay(0x3);//Почему то M25PE40 статус записи сразу сбрасываеться и тем самым не закончив запись начинаем новую, что нельзя делать;Причем только при использовании DMA возможно из-за этого слишком ыстро работает или еще что
		if ((ret = this->waitBusy()) != true)
			break ;
		data = (uint8_t *)data + step;
		len = len - step;
		addr = addr + step;
		step = page_size;
	}
	if (ret != true)
		this->writeDisable();
	return (ret);

}

bool SpiFlashClass::read(uint32_t addr, void *data, size_t len) {
	const SpiFlashClassDevice_t						*device;
	SpiFlashClassCmdRead_t							cmd_read;
	size_t											cmd_read_len;
	size_t											command;
	bool											ret;

	if ((device = this->_device) == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_NOT_INITILIZATION), false));
	if (device->total_size < (addr + len))
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_BAD_ARGUMENTS), false));
	if (len == 0x0)
		return (this->_last_status(STATUS_SUCCESS, true));
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

bool SpiFlashClass::readStatus(uint32_t *status) {
	SpiFlashClassCmdReadStatus_t					read_status;

	if (this->_sendCommand(SPI_FLASH_CLASS_CMD_READ_STATUS, &read_status, sizeof(read_status)) != true)
		return (false);
	status[0x0] = read_status.status[0x0];
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool SpiFlashClass::writeStatus(uint32_t status) {
	SpiFlashClassCmdWriteStatus_t					write_status;

	write_status.value = status;
	if (this->_sendCommand(SPI_FLASH_CLASS_CMD_WRTE_STATUS, &write_status, sizeof(write_status)) != true)
		return (false);
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool SpiFlashClass::writeEnable(void) {
	return (this->_sendCommand(SPI_FLASH_CLASS_CMD_WRITE_ENABLE, 0x0, 0x0));
}

bool SpiFlashClass::writeDisable(void) {
	return (this->_sendCommand(SPI_FLASH_CLASS_CMD_WRITE_DISABLE, 0x0, 0x0));
}

bool SpiFlashClass::sleep(void) {
	bool						ret;

	ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_SLEEP, 0x0, 0x0);
	delay(0x1);
	return (ret);
}

bool SpiFlashClass::wakeUp(void) {
	bool						ret;

	ret = this->_sendCommand(SPI_FLASH_CLASS_CMD_WAKE_UP, 0x0, 0x0);
	delay(0x1);
	return (ret);
}

/* Private Methods */
bool SpiFlashClass::_init(SpiFlashClassCmdJedec_t *cmd_jedec) {
	if (this->_spi->begin(this->_sck, this->_miso, this->_mosi, UNKNOWN_PIN) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	pinMode(this->_ss, OUTPUT_UP);
	this->wakeUp();
	this->writeDisable();
	if (this->waitBusy() != true)
		return (false);
	if ( this->_sendCommand(SPI_FLASH_CLASS_CMD_READ_JEDEC_ID, cmd_jedec, sizeof(cmd_jedec[0x0])) != true)
		return (false);
	// For simplicity with commonly used device, we only check for continuation code at 2nd byte (e.g Fujitsu FRAM devices)
	if (cmd_jedec->ids[0x1] == 0x7F) {
		cmd_jedec->ids[0x1] = cmd_jedec->ids[0x2];
		cmd_jedec->ids[0x2] = cmd_jedec->ids[0x3];
	}
	return (true);
}

bool SpiFlashClass::_init_end(const SpiFlashClassDevice_t *device, SpiFlashClassCmdJedec_t *cmd_jedec) {
	size_t									manufacturer_id;
	size_t									memory_type;
	size_t									capacity;
	uint32_t								refFreq;
	uint32_t								clock;

	manufacturer_id = cmd_jedec->ids[0x0];
	memory_type = cmd_jedec->ids[0x1];
	capacity = cmd_jedec->ids[0x2];
	if (manufacturer_id != device->manufacturer_id || memory_type != device->memory_type || capacity != device->capacity)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_SPI_FLASH, STATUS_ID_NOT_MATCH), false));
	this->_device = device;
	// refFreq = CMU_ClockFreqGet(cmuClock_HFPER) - 0x1 / 0x2;
	refFreq = 8 * SPI_FLASH_CLASS_CLOCK_MULTIPLIER;
	clock = device->max_clock_speed_mhz * SPI_FLASH_CLASS_CLOCK_MULTIPLIER;
	if (clock > refFreq)
		clock = refFreq;
	this->_clock = clock;
	if (device->total_size > (64 * 1024))
		this->_addr_byte = 0x3;
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool SpiFlashClass::_writeBuffer_add(const SpiFlashClassCmdRead_t *cmd_addr, size_t cmd_addr_len, const void *data, size_t len) {
	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (this->_spi->transfer(cmd_addr, cmd_addr_len) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (this->_spi->transfer(data, len) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	this->_spi->endTransaction();
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool SpiFlashClass::_read_add(const SpiFlashClassCmdRead_t *cmd_read, size_t cmd_read_len, void *data, size_t len) {
	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (this->_spi->transfer(cmd_read, cmd_read_len) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (this->_spi->transfer(data, len) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	this->_spi->endTransaction();
	return (this->_last_status(STATUS_SUCCESS, true));
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

bool SpiFlashClass::_sendCommand(size_t command, void *response, size_t len) {
	bool									ret;

	digitalWrite(this->_ss, LOW);//We inform slave about receiving data
	ret = this->_sendCommandAdd(command, response, len);
	digitalWrite(this->_ss, HIGH);//We inform slave about receiving data
	return (ret);
}

bool SpiFlashClass::_sendCommandAdd(size_t command, void *response, size_t len) {
	SpiFlashClassCmd_t					*cmd;

	if (this->_spi->beginTransaction(this->_clock, MSBFIRST, SPI_MODE0) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (len == 0x0) {
		response = &command;
		len = 0x1;
	}
	else {
		cmd = (SpiFlashClassCmd_t *)response;
		cmd->command = command;
	}
	if (this->_spi->transfer(response, len) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	this->_spi->endTransaction();
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool SpiFlashClass::_last_status(uint32_t status, bool ret) {
	SetLastStatus(status);
	return (ret);
}