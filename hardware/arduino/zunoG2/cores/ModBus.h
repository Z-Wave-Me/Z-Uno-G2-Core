#ifndef MOD_BUS_H
#define MOD_BUS_H

#define MODBUS_DELAY		(39)//3.5 * 11

uint8_t modbusSend(HardwareSerial *hardwareSerial, uint8_t *b, size_t len);
size_t modbusReceive(HardwareSerial *hardwareSerial, uint8_t *b, size_t len);

inline uint8_t modbusDelay(size_t baudrate) {
	size_t			out;

	out = MODBUS_DELAY / (baudrate / 1000) + 1;
	if (out < 2)
		return (2);
	return (out);
}

#endif // MOD_BUS_H