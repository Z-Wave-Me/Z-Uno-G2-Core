#include "Arduino.h"
#include "CrtxGpcrc.h"
#include "HardwareSerial.h"
#include "ModBus.h"

uint8_t modbusSend(HardwareSerial *hardwareSerial, uint8_t *b, size_t len) {
	uint8_t					*e;
	uint16_t				crc16;

	e = &b[len];
	crc16 = crc16_modbus(b, e - b);
	e[0] = crc16 & 0xFF;
	e[1] = crc16 >> 8;
	len = len + 2;
	if (hardwareSerial->write(b, len) != len)
		return (false);
	return (true);
}

size_t modbusReceive(HardwareSerial *hardwareSerial, uint8_t *b, size_t len) {
	size_t					i;
	uint8_t					*e;
	uint16_t				crc16;

	i = 0;
	while (hardwareSerial->available() != 0) {
		if (i > len)
			return (0);//overflow
		b[i++] = hardwareSerial->read();
	}
	if (i < 2)//crc - 2
		return (0);
	i = i - 2;
	e = &b[i];
	crc16 = crc16_modbus(b, e - b);
	if (e[0] != (crc16 & 0xFF) || e[1] != (crc16 >> 8))
		return (0);
	return (i);
}