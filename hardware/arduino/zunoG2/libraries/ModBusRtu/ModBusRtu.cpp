#include "Arduino.h"
#include "ModBusRtu.h"
#include "CrcClass.h"
#include "Status.h"

#define MOD_BUS_RTU_MAX_PACKET										0x100

#define MOD_BUS_RTU_FN_ERROR										0x80
#define MOD_BUS_RTU_FN_WRITE_SINGLE_COILS							0x5
#define MOD_BUS_RTU_FN_WRITE_SINGLE_REGISTERS						0x6
#define MOD_BUS_RTU_FN_WRITE_MULTIPLE_COILS							0xF
#define MOD_BUS_RTU_FN_WRITE_MULTIPLE_REGISTERS						0x10


typedef struct								ModBusRtuStart_s
{
	uint8_t									addr;//slave
	uint8_t									fn;//Function code
}											ModBusRtuStart_t;

typedef struct								ModBusRtuFnReaderHoldingInputRegisters_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											ModBusRtuFnReaderHoldingInputRegisters_t;

typedef struct								receiveModBusRtuFn_s
{
	ModBusRtuStart_t						start;
	uint8_t									len;
	uint8_t									data[];
}											receiveModBusRtuFn_t;

typedef struct								sendModBusRtuFnWriteSingleRegisters_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									value[2];/* MSB  to LSB */
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											sendModBusRtuFnWriteSingleRegisters_t;

typedef struct								sendModBusRtuFnWriteMultipleRegisters_t
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									len;
	uint8_t									data[];/* MSB  to LSB */
}											sendModBusRtuFnWriteMultipleRegisters_t;

typedef struct								receiveModBusRtuFnWriteMultipleRegisters_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											receiveModBusRtuFnWriteMultipleRegisters_t;

typedef struct								sendModBusRtuFnReaderCoilsDiscreteInputs_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											sendModBusRtuFnReaderCoilsDiscreteInputs_t;

typedef struct								sendModBusRtuFnWriteSingleCoils_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									value[2];/* MSB  to LSB */
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											sendModBusRtuFnWriteSingleCoils_t;

typedef struct								sendModBusRtuFnWriteMultipleCoils_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									len;
	uint8_t									data[];/* MSB  to LSB */
}											sendModBusRtuFnWriteMultipleCoils_t;

typedef struct								receiveModBusRtuFnWriteMultipleCoil_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											receiveModBusRtuFnWriteMultipleCoil_t;

typedef struct								ModBusRtuFnError_s
{
	ModBusRtuStart_t						start;
	uint8_t									status;
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											ModBusRtuFnError_t;

/* Public Constructors */
ModBusRtuClass::ModBusRtuClass(HardwareSerial *hardwareSerial, uint16_t timout_ms, uint8_t dir_pin): _hardwareSerial(hardwareSerial), _timout_ms(timout_ms), _dir_pin(dir_pin) {
}

/* Public Methods */
bool ModBusRtuClass::begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx) {
	size_t											dir_pin;

	if (this->_hardwareSerial->begin(speed, config, rx, tx) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if ((dir_pin = this->_dir_pin) != UNKNOWN_PIN)
		pinMode(dir_pin, OUTPUT_UP);//Поднимаем и всегда RS485 держим на отправку данных
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool ModBusRtuClass::writeMultipleCoils(uint8_t addr, uint16_t reg, uint16_t count, const uint8_t *src) {
	union
	{
		sendModBusRtuFnWriteMultipleCoils_t				send;
		receiveModBusRtuFnWriteMultipleCoil_t			receive;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};
	size_t												len;

	len = count + 0x7;
	len = (len & (0 - 0x8) ) / 0x8;
	if (addr < 0x1 || addr > 0xF7)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	if (len > ((sizeof(buffer) - sizeof(receive))) || len == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	send.start.addr = addr;
	send.start.fn = MOD_BUS_RTU_FN_WRITE_MULTIPLE_COILS;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.count[0x0] = count >> 0x8;
	send.count[0x1] = count & 0xFF;
	send.len = len;
	memcpy(&send.data[0x0], src, len);
	return (this->_sendRtu(&buffer[0x0], sizeof(send) + sizeof(receive.crc16_modbus) + len, sizeof(receive)));
}

bool ModBusRtuClass::writeSingleCoils(uint8_t addr, uint16_t reg, bool value) {
	union
	{
		sendModBusRtuFnWriteSingleCoils_t				send;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};

	send.start.addr = addr;
	send.start.fn = MOD_BUS_RTU_FN_WRITE_SINGLE_COILS;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.value[0x0] = (value != false) ? 0xFF: 0x0;
	send.value[0x1] = 0x0;
	return (this->_sendRtu(&buffer[0x0], sizeof(send), sizeof(send)));
}

bool ModBusRtuClass::writeSingleRegisters(uint8_t addr, uint16_t reg, uint16_t value) {
	union
	{
		sendModBusRtuFnWriteSingleRegisters_t			send;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};

	send.start.addr = addr;
	send.start.fn = MOD_BUS_RTU_FN_WRITE_SINGLE_REGISTERS;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.value[0x0] = value >> 0x8;
	send.value[0x1] = value & 0xFF;
	return (this->_sendRtu(&buffer[0x0], sizeof(send), sizeof(send)));
}

/* Private Methods */
bool ModBusRtuClass::_readCoilsDiscreteInputs(uint8_t addr, uint16_t reg, uint16_t count, uint8_t *dest, uint8_t fn) {
	union
	{
		sendModBusRtuFnReaderCoilsDiscreteInputs_t		send;
		receiveModBusRtuFn_t							receive;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};
	size_t												len;

	len = count + 0x7;
	len = (len & (0 - 0x8) ) / 0x8;
	if (addr < 0x1 || addr > 0xF7)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	if (len > ((sizeof(buffer) - sizeof(receive) - sizeof(send.crc16_modbus))) || len == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	send.start.addr = addr;
	send.start.fn = fn;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.count[0x0] = count >> 0x8;
	send.count[0x1] = count & 0xFF;
	if (this->_sendRtu(&buffer[0x0], sizeof(send), sizeof(receive) + len + sizeof(send.crc16_modbus)) == false)
		return (false);
	memcpy(dest, &receive.data[0x0], receive.len);
	return (true);
}

bool ModBusRtuClass::_writeMultipleRegisters(uint8_t addr, uint16_t reg, uint8_t count, const uint16_t *src, uint8_t bMemcpy) {
	union
	{
		sendModBusRtuFnWriteMultipleRegisters_t			send;
		receiveModBusRtuFnWriteMultipleRegisters_t		receive;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};
	size_t												i;
	uint8_t												*dest;
	const uint8_t										*data;

	if (addr < 0x1 || addr > 0xF7)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	if (count > ((sizeof(buffer) - sizeof(send) - 0x2) / 0x2) || count == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	send.start.addr = addr;
	send.start.fn = MOD_BUS_RTU_FN_WRITE_MULTIPLE_REGISTERS;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.count[0x0] = 0x0;
	send.count[0x1] = count;
	send.len = 0x2 * count;
	dest = &send.data[0x0];
	data = (const uint8_t *)src;
	if (bMemcpy == false) {
		i = 0x0;
		while (i < count) {
			dest[i] = data[0x1];
			dest[i + 0x1] = data[0x0];
			i = i + 0x2;
		}
	}
	else
		memcpy(dest, data, 2 * count);
	return (this->_sendRtu(&buffer[0x0], sizeof(send) + 0x2 + send.len, sizeof(receive)));
}

bool ModBusRtuClass::_readHoldingInputRegisters(uint8_t addr, uint16_t reg, uint8_t count, uint16_t *dest, uint8_t fn, uint8_t bMemcpy) {
	union
	{
		ModBusRtuFnReaderHoldingInputRegisters_t		send;
		receiveModBusRtuFn_t							receive;
		uint8_t											buffer[MOD_BUS_RTU_MAX_PACKET];
	};
	uint8_t												*data;

	if (addr < 0x1 || addr > 0xF7)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	if (count > ((sizeof(buffer) - sizeof(receive) - sizeof(send.crc16_modbus)) / 0x2) || count == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BAD_ARGUMENTS), false));
	send.start.addr = addr;
	send.start.fn = fn;
	send.reg[0x0] = reg >> 0x8;
	send.reg[0x1] = reg & 0xFF;
	send.count[0x0] = 0x0;
	send.count[0x1] = count;
	if (this->_sendRtu(&buffer[0x0], sizeof(send), sizeof(receive) + 0x2 * count + sizeof(send.crc16_modbus)) == false)
		return (false);
	data = &receive.data[0x0];
	if (bMemcpy == false) {
		while (count-- != 0x0) {
			dest[0x0] = (data[0x0] << 0x8) | data[0x1];
			dest++;
			data = data + 0x2;
		}
	}
	else
		memcpy(dest, data, 2 * count);
	return (true);
}

bool ModBusRtuClass::_last_status(uint32_t status, bool ret) {
	SetLastStatus(status);
	return (ret);
}

bool ModBusRtuClass::_sendRtu(void *buffer, uint8_t len, uint8_t dest_len) {
	ssize_t								timout_ms;
	const ModBusRtuStart_t				*start;
	uint32_t							ms;

	if (this->_send(buffer, len) == false)
		return (false);
	ms = this->_hardwareSerial->countWaitingMs(dest_len);
	if (this->_dir_pin != UNKNOWN_PIN) {
		delay(ms / dest_len);
		digitalWrite(this->_dir_pin, LOW);
	}
	timout_ms = this->_timout_ms;
	while (this->_hardwareSerial->available() == 0x0 && timout_ms > 0x0) {
		timout_ms = timout_ms - 0xA;
		delay(0xA);
	}
	if (timout_ms < 0x0) {
		if (this->_dir_pin != UNKNOWN_PIN)
			digitalWrite(this->_dir_pin, HIGH);
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_WAIT_TIMEOUT), false));
	}
	delay(ms);
	if (this->_dir_pin != UNKNOWN_PIN)
		digitalWrite(this->_dir_pin, HIGH);
	start = (const ModBusRtuStart_t *)buffer;
	if (this->_receive(start->addr, start->fn, buffer, dest_len) == false)
		return (false);
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool ModBusRtuClass::_send(void *src, uint8_t len) {
	uint8_t					*b;
	uint8_t					*e;
	uint16_t				crc16;

	b = (uint8_t *)src;
	len = len - 2;
	e = &b[len];
	crc16 = CrcClass::crc16_modbus(b, e - b);
	e[0] = crc16 & 0xFF;
	e[1] = crc16 >> 8;
	len = len + 2;
	if (this->_hardwareSerial->write(b, len) != len)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	return (true);
}

uint8_t ModBusRtuClass::_receive(uint8_t addr, uint8_t fn, void *dest, uint8_t len) {
	int						value;
	size_t					i;
	uint8_t					*b;
	ModBusRtuStart_t		*start;
	ModBusRtuFnError_t		*error;
	uint16_t				crc16;

	i = 0;
	b = (uint8_t *)dest;
	start = (ModBusRtuStart_t *)dest;
	while ((value = this->_hardwareSerial->read()) >= 0x0) {
		if (i >= MOD_BUS_RTU_MAX_PACKET)
			return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_BUFFER_OVERFLOW), false));
		b[i] = value;
		i++;
	}
	if (i < 0x2)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_NOT_ENOUGH_DATA), false));
	crc16 = CrcClass::crc16_modbus(b, &b[i - 0x2] - b);
	if (b[i - 0x2] != (crc16 & 0xFF) || b[i - 0x1] != (crc16 >> 8))
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, STATUS_CRC_NOT_MATCH), false));
	if (start->addr != addr)
		return (this->_last_status(STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, MOD_BUS_RTU_STATUS_RESPONSE_ADDR_NOT_MATCH), false));
	if (start->fn == fn) {
		if (i != len)
			return (this->_last_status(STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, MOD_BUS_RTU_STATUS_RESPONSE_LEN_NOT_MATCH), false));
		return (true);
	}
	if (start->fn == (MOD_BUS_RTU_FN_ERROR | fn)) {
		error = (ModBusRtuFnError_t *)dest;
		return (this->_last_status(STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, error->status), false));
	}
	return (this->_last_status(STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_MOD_BUS, MOD_BUS_RTU_STATUS_UNKNOWN_FN), false));
}