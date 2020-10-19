#ifndef WIRE_H
#define WIRE_H

#include "CrtxI2C.h"

class TwoWire {
	public:
		TwoWire(I2C_TypeDef *i2c);
		TwoWire(void);
		ZunoError_t		begin(void);
		ZunoError_t		begin(uint8_t scl, uint8_t sda);
		ZunoError_t		begin(uint8_t adress);
		ZunoError_t		begin(uint8_t adress, uint8_t scl, uint8_t sda);
		ZunoError_t		begin(uint8_t adress, uint8_t scl, uint8_t sda, void *b, uint16_t len);
		void			beginTransmission(uint8_t adress);
		void			beginTransmission(uint8_t adress, uint8_t forced_start);
		uint8_t			transfer(uint8_t adress, void *b, uint16_t count);
		uint8_t			transfer(uint8_t adress, void *b);
		uint8_t			transfer(uint8_t adress, const char *b);
		size_t			write(int data){write((uint8_t)data);};
		size_t			write(uint8_t data);
		size_t			write(const char *data);
		size_t			write(const uint8_t *data, size_t quantity);
		uint8_t			endTransmission(void);
		uint8_t			endTransmission(uint8_t sendStop);
		uint8_t			requestFrom(uint8_t address, uint8_t quantity);
		uint8_t			requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
		uint8_t			available(void);
		uint8_t			read(void);
		void			enableTS(uint8_t on_off);
		void			setClock(uint32_t clock);
		void			end(void);
};

extern TwoWire Wire;

#endif// WIRE_H