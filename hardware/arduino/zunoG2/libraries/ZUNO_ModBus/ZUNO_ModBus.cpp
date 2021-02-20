#include "Arduino.h"
#include "CrtxGpcrc.h"
#include "ZUNO_ModBus.h"


#define MOD_BUS_RTU_FN_ERROR				0x80
#define MOD_BUS_RTU_FN_READ_HR				0x3
#define MOD_BUS_RTU_FN_WRITE_SR				0x6

#define MOD_BUS_RTU_TIMEOUT					50

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
ModBusRtuClass::ModBusRtuClass(HardwareSerial *hardwareSerial): _hardwareSerial(hardwareSerial), _time_between(0), _dir_pin(0xFF) {
}

/* Public Methods */
ZunoError_t ModBusRtuClass::begin(size_t baudrate, size_t rx, size_t tx, size_t dir_pin) {
	ZunoError_t						ret;

	this->_time_between = this->getBetween(baudrate);
	if ((ret = this->_hardwareSerial->begin(baudrate, rx, tx)) != ZunoErrorOk)
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

size_t ModBusRtuClass::receive(HardwareSerial *hardwareSerial, void *dest, size_t len) {
	size_t					count;

	if (ModBusRtuClass::_receive(hardwareSerial, dest, len, &count) != ZunoErrorOk)
		return (0);
	return (count);
}


/* Private Methods */
inline ZunoError_t ModBusRtuClass::_receive(HardwareSerial *hardwareSerial, void *dest, size_t len, size_t *count) {
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

inline ZunoError_t ModBusRtuClass::_sendRtu(void *src, size_t src_len, void *dest, size_t dest_len) {
	ModBusRtuFnError_t					*status;
	ModBusRtuStart_t					*start;
	size_t								fn_receive;
	size_t								fn_send;
	size_t								count;
	ZunoError_t							ret;

	if (ModBusRtuClass::send(this->_hardwareSerial, src, src_len) == false)
		return (ZunoErrorModBusRtuOther);
	delay(this->_time_between);
	if (dest == 0)
		return (ZunoErrorOk);
	digitalWrite(this->_dir_pin, LOW);
	delay(MOD_BUS_RTU_TIMEOUT);
	digitalWrite(this->_dir_pin, HIGH);
	if ((ret = ModBusRtuClass::_receive(this->_hardwareSerial, dest, dest_len, &count)) != ZunoErrorOk)
		return (ret);
	start = (ModBusRtuStart_t *)src;
	status = (ModBusRtuFnError_t *)dest;
	fn_send = start->fn;
	fn_receive = status->start.fn;
	if (fn_receive == (fn_send | MOD_BUS_RTU_FN_ERROR)) {
		switch (status->status) {
			case 0x1:
				return (ZunoErrorModBusRtuNotSupportFunction);
				break ;
			case 0x2:
				return (ZunoErrorModBusRtuNotSupportRegister);
				break ;
			case 0x3:
				return (ZunoErrorModBusRtuNotSupportCountRegister);
				break ;
			default:
				return (ZunoErrorModBusRtuUnknown);
				break;
		}
	}
	if (fn_receive != fn_send)
		return (ZunoErrorModBusRtuNoises);
	return (ZunoErrorOk);
}
