#ifndef WIRE_H
#define WIRE_H

typedef uint16_t wire_buffer_len;

class TwoWire {
	public:
		ZunoError_t		begin(void);
		ZunoError_t		begin(uint8_t scl, uint8_t sda);
		ZunoError_t		begin(uint8_t address);
		ZunoError_t		begin(uint8_t address, uint8_t scl, uint8_t sda);
		ZunoError_t		begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len);
		void			beginTransmission(uint8_t address);
		void			beginTransmission(uint8_t address, uint8_t forced_start);
		uint8_t			transfer(uint8_t address, void *b, wire_buffer_len count);
		uint8_t			transfer(uint8_t address, void *b);
		uint8_t			transfer(uint8_t address, const char *b);
		size_t			write(int data){write((uint8_t)data);};
		size_t			write(uint8_t data);
		size_t			write(const char *data);
		size_t			write(const uint8_t *data, wire_buffer_len quantity);
		uint8_t			endTransmission(void);
		uint8_t			endTransmission(uint8_t sendStop);
		wire_buffer_len	requestFrom(uint8_t address, wire_buffer_len quantity);
		wire_buffer_len	requestFrom(uint8_t address, wire_buffer_len quantity, uint8_t sendStop);
		uint8_t			requestFromAsync(uint8_t address, wire_buffer_len quantity);
		uint8_t			requestFromAsync(uint8_t address, wire_buffer_len quantity, uint8_t sendStop);
		wire_buffer_len	available(void);
		uint8_t			read(void);
		void			enableTS(uint8_t on_off);
		void			setClock(uint32_t clock);
		void			end(void);
};

extern TwoWire Wire;

#endif// WIRE_H