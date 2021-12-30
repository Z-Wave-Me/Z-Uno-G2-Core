#include "Arduino.h"
#include "ZUNO_ModBus.h"
#include "zwaveme_gpcrc.h"


#define MOD_BUS_RTU_FN_ERROR				0x80
#define MOD_BUS_RTU_FN_READ_HR				0x3
#define MOD_BUS_RTU_FN_WRITE_SR				0x6

#define MOD_BUS_RTU_TIMEOUT_STEP			10

typedef enum								ModBusRtuStatus_e
{
	ModBusRtuIllegalFunction = 1,
	ModBusRtuIllegalDataAdress,
	ModBusRtuIllegalDataValue,
	ModBusRtuSlaveDeviceFalture,
	ModBusRtuAcknowledge,
	ModBusRtuSlaveDeviceBusy,
	ModBusRtuMemoryParityError = 0x8,
	ModBusRtuGatewayPathUnavailable = 0xA,
	ModBusRtuGatewayTargetDeviceFailedRespond
}											ModBusRtuStatus_t;

typedef struct								ModBusRtuStatusTable_s
{
	ZunoError_t								Default;
	ZunoError_t								IllegalFunction;
	ZunoError_t								IllegalDataAdress;
	ZunoError_t								IllegalDataValue;
	ZunoError_t								SlaveDeviceFalture;
	ZunoError_t								Acknowledge;
	ZunoError_t								SlaveDeviceBusy;
	ZunoError_t								Reserved1;
	ZunoError_t								MemoryParityError;
	ZunoError_t								Reserved2;
	ZunoError_t								GatewayPathUnavailable;
	ZunoError_t								GatewayTargetDeviceFailedRespond;
}											ModBusRtuStatusTable_t;

typedef struct								ModBusRtuStart_s
{
	uint8_t									adress;//slave
	uint8_t									fn;//Function code
}											ModBusRtuStart_t;

typedef struct								ModBusRtuFnError_s
{
	ModBusRtuStart_t						start;
	ModBusRtuStatus_t						status;
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											ModBusRtuFnError_t;

typedef struct								sendModBusRtuFnReadHR_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									count[2];/* MSB  to LSB */ //Quantity of Registers
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											sendModBusRtuFnReadHR_t;

typedef struct								receiveModBusRtuFnReadHR_s
{
	ModBusRtuStart_t						start;
	uint8_t									len;
}											receiveModBusRtuFnReadHR_t;

typedef struct								sendModBusRtuFnWriteSR_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									value[2];/* MSB  to LSB */
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											sendModBusRtuFnWriteSR_t;

typedef struct								receiveModBusRtuFnWriteSR_s
{
	ModBusRtuStart_t						start;
	uint8_t									reg[2];/* MSB  to LSB */ //Starting Address
	uint8_t									value[2];/* MSB  to LSB */
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											receiveModBusRtuFnWriteSR_t;

/* Public Constructors */
ModBusRtuClass::ModBusRtuClass(HardwareSerial *hardwareSerial, uint16_t timeout): _hardwareSerial(hardwareSerial), _timeout(timeout), _dir_pin(0xFF), _time_between(0) {
}

/* Public Methods */
ZunoError_t ModBusRtuClass::begin(size_t baudrate, size_t rx, size_t tx, size_t dir_pin) {
	ZunoError_t						ret;

	this->_time_between = this->getBetween(baudrate);
	if ((ret = this->_hardwareSerial->begin(baudrate, SERIAL_8N1, rx, tx)) != ZunoErrorOk)
		return (ret);
	this->_dir_pin = dir_pin;
	pinMode(dir_pin, OUTPUT_UP);//Поднимаем и всегда RS485 держим на отправку данных
	CMU_ClockEnable(cmuClock_GPCRC, true);
	return (ZunoErrorOk);
}

ZunoError_t ModBusRtuClass::readHR(uint8_t adress, uint16_t reg, uint8_t count, void *dest) {
	sendModBusRtuFnReadHR_t				send;

	send.start.adress = adress;
	send.start.fn = MOD_BUS_RTU_FN_READ_HR;
	send.reg[0] = reg >> 8;
	send.reg[1] = reg & 0xFF;
	send.count[0] = 0;
	send.count[1] = count;
	return (this->_sendRtu(&send, sizeof(send), dest, sizeof(receiveModBusRtuFnReadHR_t) + 2 * count + 2));
}

ZunoError_t ModBusRtuClass::writeSR(uint8_t adress, uint16_t reg, uint16_t value) {
	sendModBusRtuFnWriteSR_t			send;
	receiveModBusRtuFnWriteSR_t			receive;

	send.start.adress = adress;
	send.start.fn = MOD_BUS_RTU_FN_WRITE_SR;
	send.reg[0] = reg >> 8;
	send.reg[1] = reg & 0xFF;
	send.value[0] = value >> 8;
	send.value[1] = value & 0xFF;
	return (this->_sendRtu(&send, sizeof(send), &receive, sizeof(receive)));
}

size_t ModBusRtuClass::send(HardwareSerial *hardwareSerial, void *src, size_t len) {
	uint8_t					*b;
	uint8_t					*e;
	uint16_t				crc16;

	len = len- 2;
	b = (uint8_t *)src;
	e = &b[len];
	crc16 = crc16_modbus(b, e - b);
	e[0] = crc16 & 0xFF;
	e[1] = crc16 >> 8;
	len = len + 2;
	if (hardwareSerial->write(b, len) != len)
		return (false);
	return (true);
}

ZunoError_t ModBusRtuClass::receive(HardwareSerial *hardwareSerial, void *dest, size_t len, size_t *count, void *start_bit, size_t len_start_bit) {
	size_t					i;
	uint8_t					*b;
	uint8_t					*e;
	uint16_t				crc16;

	b = (uint8_t *)dest;
	i = 0;
	while (hardwareSerial->available() != 0) {
		if (i > len)
			return (ZunoErrorOverflow);//overflow
		b[i++] = hardwareSerial->read();
		if (len_start_bit == i && memcmp(b, start_bit, i) != 0)
			i = 0;
	}
	if (i < 2)//crc - 2
		return (ZunoErrorNotData);
	i = i - 2;
	e = &b[i];
	crc16 = crc16_modbus(b, e - b);
	if (e[0] != (crc16 & 0xFF) || e[1] != (crc16 >> 8))
		return (ZunoErrorNotMatchCrc);
	count[0] = i;
	return (ZunoErrorOk);
}

/* Private Methods */
inline ZunoError_t ModBusRtuClass::_sendRtu(void *src, size_t src_len, void *dest, size_t dest_len) {
	static const ModBusRtuStatusTable_t		error =
	{
		.Default = ZunoErrorModBusRtuOther,
		.IllegalFunction = ZunoErrorModBusRtuIllegalFunction,
		.IllegalDataAdress = ZunoErrorModBusRtuIllegalDataAdress,
		.IllegalDataValue = ZunoErrorModBusRtuIllegalDataValue,
		.SlaveDeviceFalture = ZunoErrorModBusRtuSlaveDeviceFalture,
		.Acknowledge = ZunoErrorModBusRtuAcknowledge,
		.SlaveDeviceBusy = ZunoErrorModBusRtuSlaveDeviceBusy,
		.Reserved1 = ZunoErrorModBusRtuOther,
		.MemoryParityError = ZunoErrorModBusRtuMemoryParityError,
		.Reserved2 = ZunoErrorModBusRtuOther,
		.GatewayPathUnavailable = ZunoErrorModBusRtuGatewayPathUnavailable,
		.GatewayTargetDeviceFailedRespond = ZunoErrorModBusRtuGatewayTargetDeviceFailedRespond
	};
	ModBusRtuFnError_t					*status;
	ModBusRtuStart_t					*start;
	size_t								fn_receive;
	size_t								fn_send;
	size_t								count;
	ZunoError_t							ret;
	size_t								timeout;
	size_t								i;
	const ZunoError_t					*b;

	if (ModBusRtuClass::send(this->_hardwareSerial, src, src_len) == false)
		return (ZunoErrorModBusRtuOther);
	delay(this->_time_between);
	if (dest == 0)
		return (ZunoErrorOk);
	digitalWrite(this->_dir_pin, LOW);
	timeout = this->_timeout;
	i = 0;
	while (this->_hardwareSerial->available() == 0 && i < timeout) {
		i = i + MOD_BUS_RTU_TIMEOUT_STEP;
		delay(MOD_BUS_RTU_TIMEOUT_STEP);
	}
	delay(this->_time_between * (dest_len / MOD_BUS_WORD_COUNT + 1));
	digitalWrite(this->_dir_pin, HIGH);
	if (i >= timeout)
		return (ZunoErrorTimeout);
	start = (ModBusRtuStart_t *)src;
	if ((ret = ModBusRtuClass::receive(this->_hardwareSerial, dest, dest_len, &count, &start->adress, 1)) != ZunoErrorOk)
		return (ret);
	status = (ModBusRtuFnError_t *)dest;
	fn_send = start->fn;
	fn_receive = status->start.fn;
	if (fn_receive == (fn_send | MOD_BUS_RTU_FN_ERROR)) {
		i = status->status;
		if (i > (sizeof(error) - 1))
			i = 0;
		b = (ZunoError_t *)&error;
		return (b[i]);
	}
	if (fn_receive != fn_send)
		return (ZunoErrorModBusRtuNoises);
	return (ZunoErrorOk);
}
