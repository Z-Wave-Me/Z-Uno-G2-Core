#ifndef _ZUNO_HARDWARE_SERIAL_H
#define _ZUNO_HARDWARE_SERIAL_H

#include "Stream.h"

class HardwareSerial : public Stream {
	public:
		HardwareSerial(uint8_t number, uint8_t rx, uint8_t tx);
		HardwareSerial(uint8_t numberConfig);
		ZunoError_t								begin(void);
		ZunoError_t								begin(size_t baudrate);
		ZunoError_t								begin(size_t baudrate, uint8_t rx, uint8_t tx);
		void									end();
		uint8_t									write(unsigned long value);
		uint8_t									write(long value);
		uint8_t									write(unsigned int value);
		uint8_t									write(int value);
		virtual uint8_t							write(uint8_t value);
		virtual size_t							write(const uint8_t *b, size_t count);
		virtual size_t available(void);
		virtual int peek(void);
		virtual uint8_t read(void);
	private:
		size_t					_baudrate;
		uint8_t					_numberConfig;
		struct
		{
			uint8_t				_bLockUsart: 1;
		};
		byte serial_num;
};

extern HardwareSerial Serial;
extern HardwareSerial Serial0;
extern HardwareSerial Serial1;

#endif // _ZUNO_HARDWARE_SERIAL_H