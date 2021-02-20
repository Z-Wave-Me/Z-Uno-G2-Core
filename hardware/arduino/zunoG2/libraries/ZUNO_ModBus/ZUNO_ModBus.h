#ifndef ZUNO_MOD_BUS_H
#define ZUNO_MOD_BUS_H

#include "Arduino.h"

typedef enum								ModBusRtuStatus_e
{
	ModBusRtuStatusSuccess = 0,
	ModBusRtuStatusNotSupportFunction,
	ModBusRtuStatusNotSupportRegister,
	ModBusRtuStatusNotSupportCountRegister,
	ModBusRtuStatusUnknown
}											ModBusRtuStatus_t;

class ModBusRtuClass {
	public:
		ModBusRtuClass(HardwareSerial *hardwareSerial);
		ZunoError_t							begin(size_t baudrate, size_t rx, size_t tx, size_t dir_pin);
		ZunoError_t							readHR(uint8_t adress, uint16_t reg, uint8_t count, void *dest);
		ZunoError_t							writeSR(uint8_t adress, uint16_t reg, uint16_t value);
		inline void							end(void) {this->_hardwareSerial->end();};
		static inline size_t				getBetween(size_t baudrate) {
			size_t			out;

			out = ((80 * 1000) / baudrate) + 1;//3.5 * 11 = 40
			if (out < 2)
				return (2);
			return (out);
		};
		static size_t						send(HardwareSerial *hardwareSerial, void *src, size_t len);
		static size_t						receive(HardwareSerial *hardwareSerial, void *dest, size_t len);

	private:
		static inline ZunoError_t			_receive(HardwareSerial *hardwareSerial, void *dest, size_t len, size_t *count);
		inline ZunoError_t					_sendRtu(void *src, size_t src_len, void *dest, size_t dest_len);
		HardwareSerial						*_hardwareSerial;
		uint8_t								_time_between;
		uint8_t								_dir_pin;
};

#endif//ZUNO_MOD_BUS_H