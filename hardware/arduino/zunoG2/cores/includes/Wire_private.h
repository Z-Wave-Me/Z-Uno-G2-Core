#ifndef WIRE_PRIVATE_H
#define WIRE_PRIVATE_H

#include "Arduino.h"
#include "CrtxI2C.h"


#define WIRE_PIN_SCL					24//by default PA1/RX - SCL
#define WIRE_PIN_SDA					23//by default and PA0/TX - SDA

#define BUFFER_LENGTH					(uint16_t)32
#define WIRE_BUFFER_LENGTH				BUFFER_LENGTH

#define WIRE_ERORR_TRANSMISSION_SUCCESS			0
#define WIRE_ERORR_TRANSMISSION_LONG			1
#define WIRE_ERORR_TRANSMISSION_LONG_I2C		(I2C_TransferReturn_TypeDef)-127//that would not conflict with I2C_TransferReturn_TypeDef
#define WIRE_ERORR_TRANSMISSION_NACK_ADDRESS	2
#define WIRE_ERORR_TRANSMISSION_NACK_DATA		3
#define WIRE_ERORR_TRANSMISSION_OTHER			4


#define WIRE_STATUS_BEGIN						0x1//Indicates that initialization was performed - Wire.begin


/* Layout details, A = address bit, X = don't care bit (set to 0):
	7 bit address - use format AAAA AAAX.
	10 bit address - use format XXXX XAAX AAAA AAAA */
#define WIRE_ADDRESS(x)							x << _I2C_SADDR_ADDR_SHIFT//7 bit address

class TwoWire 
{
	public:
		TwoWire();
		void		begin(void);
		void		begin(uint8_t scl, uint8_t sda);
		void		begin(uint8_t adress);
		void		begin(uint8_t adress, uint8_t scl, uint8_t sda);
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
		void		enableTS(uint8_t on_off);//Не сделанно еще
		void		setClock(uint32_t clock);

	private:
		static const uint8_t				wire_location[];//Based on SDA_0
		uint8_t								scl_pin;
		uint8_t								sda_pin;
		uint32_t							init_freq;//To set the bus frequency, only valid in master mode - setClock
		I2C_TransferReturn_TypeDef			seq_return;//Status after reading and writing data
		uint8_t								status;//
		uint8_t								available_bytes;//How many bytes read  - requestFrom
		uint8_t								seq_buffer[WIRE_BUFFER_LENGTH];//The buffer for reading and writing the size depends on BUFFER_LENGTH
		I2C_TransferSeq_TypeDef				seq;
		uint8_t		_get_location(uint8_t pin);
};

extern TwoWire Wire;

#endif// WIRE_PRIVATE_H