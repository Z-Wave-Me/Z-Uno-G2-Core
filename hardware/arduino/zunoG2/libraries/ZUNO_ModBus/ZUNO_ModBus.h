#ifndef ZUNO_MOD_BUS_H
#define ZUNO_MOD_BUS_H

#include "Arduino.h"

#define MOD_BUS_WORD_COUNT					8

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

			out = (((MOD_BUS_WORD_COUNT * 11) * 1000) / baudrate);//3.5 * 11 = 40
			if (out < 2)
				return (2);
			return (out);
		};
		static size_t						send(HardwareSerial *hardwareSerial, void *src, size_t len);
		static ZunoError_t					receive(HardwareSerial *hardwareSerial, void *dest, size_t len, size_t *count, void *stat_bit, size_t len_start_bit);

	private:
		inline ZunoError_t					_sendRtu(void *src, size_t src_len, void *dest, size_t dest_len);
		HardwareSerial						*_hardwareSerial;
		uint8_t								_time_between;
		uint8_t								_dir_pin;
};

#endif//ZUNO_MOD_BUS_H