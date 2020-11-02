#ifndef WIRE_PRIVATE_H
#define WIRE_PRIVATE_H

#define WIRE_LOCATION			g_loc_pa0_pf7_all
#define WIRE_LOCATION_SIZE		sizeof(g_loc_pa0_pf7_all)

// If you need more, please use ZUNO_ENABLE(WIRE_BUFFER_LENGTH=[NEEDED_LEN])
#ifndef WIRE_BUFFER_LENGTH 
#define WIRE_BUFFER_LENGTH				(32)
#else
#pragma message "WIRE_BUFFER_LENGTH was defined by user"
#endif

#define WIRE_ERORR_TRANSMISSION_SUCCESS			0
#define WIRE_ERORR_TRANSMISSION_LONG			1
#define WIRE_ERORR_TRANSMISSION_NACK_ADDRESS	2
#define WIRE_ERORR_TRANSMISSION_NACK_DATA		3
#define WIRE_ERORR_TRANSMISSION_OTHER			4

/* Layout details, A = address bit, X = don't care bit (set to 0):
	7 bit address - use format AAAA AAAX.
	10 bit address - use format XXXX XAAX AAAA AAAA */
#define WIRE_ADDRESS_7BIT(x)							((uint8_t)(x << 1))
#define WIRE_ADDRESS_10BIT(x)							((uint16_t)((x & 0xFF) | (x >> 7) & 0x6))

#define WIRE_IEN_FLAGS_WRITE					(I2C_IEN_BUSERR | I2C_IEN_ARBLOST | I2C_IEN_SSTOP | I2C_IEN_CLTO | I2C_IEN_NACK | I2C_IEN_CLERR | I2C_IEN_TXC)
#define WIRE_IF_FLAGS_WRITE						(I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_SSTOP | I2C_IF_CLTO | I2C_IF_NACK | I2C_IF_CLERR | I2C_IF_TXC)

#define WIRE_IEN_FLAGS_READ						(I2C_IEN_BUSERR | I2C_IEN_ARBLOST | I2C_IEN_SSTOP | I2C_IEN_CLTO | I2C_IEN_NACK | I2C_IEN_CLERR | I2C_IEN_RXFULL)
#define WIRE_IF_FLAGS_READ						(I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_SSTOP | I2C_IF_CLTO | I2C_IF_NACK | I2C_IF_CLERR | I2C_IF_RXFULL)

#define WIRE_FLAG_WRITE							0x1
#define WIRE_FLAG_READ							0x2
#define WIRE_FLAG_STOP							0x4
#define WIRE_FLAG_ASYNC							0x8
#define WIRE_FLAG_FAILL_LONG					0x80

typedef uint16_t wire_buffer_len;

typedef struct							ZunoWireI2CTypeConfig_s
{
	I2C_TypeDef							*i2c;
	wire_buffer_len						*aviable;
	ZDMA_PeripheralSignal_t				dmaSignalRead;
	ZDMA_PeripheralSignal_t				dmaSignalWrite;
	CMU_Clock_TypeDef					bus_clock;
	IRQn_Type							irqType;
	uint8_t								scl;
	uint8_t								sda;
}										ZunoWireI2CTypeConfig_t;

class TwoWire {
	public:
		TwoWire(uint8_t one);
		TwoWire(void);
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

	private:
		wire_buffer_len						_requestFrom(uint8_t address, wire_buffer_len quantity, uint8_t flags);
		ZunoError_t							_begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len, uint8_t bufferFree);
		uint8_t								_transferMasterToSlave(uint16_t address, void *b, size_t len);
		const ZunoWireI2CTypeConfig_t		*_i2c_config;
		size_t								_freqScl;//To set the bus frequency, only valid in master mode - setClock
		uint8_t								*_buffer;
		wire_buffer_len						_buffer_max;
		wire_buffer_len						_buffer_count;
		uint8_t								_address;
		uint8_t								_flags;
		uint8_t								_bufferFree;
};

extern TwoWire Wire;

#endif// WIRE_PRIVATE_H