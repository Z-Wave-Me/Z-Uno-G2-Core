#include "HardwareSerial.h"
#include "Arduino.h"	
//#include "ZUNO_Channels.h"
//static const char const_text[] = "<INIT>\n";

HardwareSerial::HardwareSerial(byte number, byte rx, byte tx) {
	serial_num = number;
	uart_conf.rx_pin = pin2HWPin(rx);
	uart_conf.tx_pin = pin2HWPin(tx);

	//zunoSysCall(ZUNO_FUNC_SERIAL_WRITE, 3, 0, const_text, strlen(const_text));

}

void HardwareSerial::begin(DWORD baudrate) {
	uart_conf.baudrate = baudrate;
	zunoSysCall(ZUNO_FUNC_SERIAL_BEGIN, 2, serial_num, &uart_conf);
}

void HardwareSerial::begin(DWORD baudrate, byte rx, byte tx) {
	uart_conf.baudrate = baudrate;
	uart_conf.rx_pin = pin2HWPin(rx);
	uart_conf.tx_pin = pin2HWPin(tx);
	zunoSysCall(ZUNO_FUNC_SERIAL_BEGIN, 2, serial_num, &uart_conf);
}
void HardwareSerial::end() {
	zunoSysCall(ZUNO_FUNC_SERIAL_END, 1, serial_num);
}

size_t HardwareSerial::available(void) {
	return (size_t) zunoSysCall(ZUNO_FUNC_SERIAL_AVAILABLE, 1, serial_num);
}

int HardwareSerial::peek(void) {
	int peekval;
	if(!zunoSysCall(ZUNO_FUNC_SERIAL_AVAILABLE, serial_num)) 
		return -1;
	zunoSysCall(ZUNO_FUNC_SERIAL_READ, 4, serial_num, false, &peekval, 1);
	return peekval;
}
uint8_t HardwareSerial::read(void) {
	uint8_t readval;
	zunoSysCall(ZUNO_FUNC_SERIAL_READ, 4, serial_num, true, &readval, 1);
	return readval;
}
size_t HardwareSerial::write(uint8_t value) {
	zunoSysCall(ZUNO_FUNC_SERIAL_WRITE, 3, serial_num, &value, 1);
	return 1;
}

// Экземпляры классов - стиль как в Ардуино
// FIXME: pin numbers for unofficial board was presented. 
//     	  Correct them before the release!
#if defined ZUNO_PIN_V1
HardwareSerial Serial(1, 20, 10);// USB
HardwareSerial Serial1(1, 13, 12); // UART1  - разделяет один физический UART на разных пинах с Serial
HardwareSerial Serial0(0, 11, 7); // UART0 
#else
// FIXME: при rst отваливаеться UART1/UART0
HardwareSerial Serial(1, 26, 27);// USB
HardwareSerial Serial1(1, 7, 8); // UART1
HardwareSerial Serial0(0, 24, 25); // UART0
#endif