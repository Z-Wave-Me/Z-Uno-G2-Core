#ifndef WIRE_H
#define WIRE_H

#include "Arduino.h"
#include "CrtxI2C.h"


#define WIRE_PIN_SCL					24// A1\RX - до ремапинга с помощью локаций
#define WIRE_PIN_SDA					23// A0\TX - до ремапинга с помощью локаций

#define BUFFER_LENGTH					(uint16_t)32
#define WIRE_BUFFER_LENGTH				BUFFER_LENGTH//не больше по размеру чем I2C_TransferSeq_TypeDef->buff->len

#define WIRE_ERORR_TRANSMISSION_SUCCESS			0
#define WIRE_ERORR_TRANSMISSION_LONG			1
#define WIRE_ERORR_TRANSMISSION_LONG_I2C		(I2C_TransferReturn_TypeDef)-127//что бы не конфликтовать с I2C_TransferReturn_TypeDef
#define WIRE_ERORR_TRANSMISSION_NACK_ADDRESS	2
#define WIRE_ERORR_TRANSMISSION_NACK_DATA		3
#define WIRE_ERORR_TRANSMISSION_OTHER			4


#define WIRE_STATUS_BEGIN						0x1
#define WIRE_STATUS_START						0x2
#define WIRE_STATUS_WRITE						0x4
#define WIRE_STATUS_READ						0x8


/* Layout details, A = address bit, X = don't care bit (set to 0):
	7 bit address - use format AAAA AAAX.
	10 bit address - use format XXXX XAAX AAAA AAAA */
#define WIRE_ADDRESS(x)							x << _I2C_SADDR_ADDR_SHIFT//7 bit address

class TwoWire 
{
	private:
		static I2C_TransferSeq_TypeDef				seq;
		static I2C_TransferReturn_TypeDef			seq_return;
		static uint8_t								status;
		static uint8_t								seq_buffer[];
		static uint8_t								available_bytes;
		static size_t	fn_start(void);
		static void		fn_stop(uint8_t sendStop);
		static void		fn_begin(uint8_t master, uint8_t address);
		static void		fn_begin_transmission(uint8_t adress, uint8_t forced_start);
		static size_t	fn_write(const uint8_t *data, size_t quantity);
		static uint8_t	fn_end_transmission(uint8_t sendStop);
		static uint8_t	fn_request_from(uint8_t address, uint8_t quantity, uint8_t sendStop);

	public:
		void		begin(void);
		void		begin(uint8_t adress);
		void		beginTransmission(uint8_t adress);
		void		beginTransmission(uint8_t adress, uint8_t forced_start);
		size_t		write(uint8_t data);
		size_t		write(const char *data);
		size_t		write(const uint8_t *data, size_t quantity);
		uint8_t		endTransmission(void);
		uint8_t		endTransmission(uint8_t sendStop);
		uint8_t		requestFrom(uint8_t address, uint8_t quantity);
		uint8_t		requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
		uint8_t		available(void);
		uint8_t		read(void);
};

extern TwoWire Wire;

#endif// WIRE_H