#ifndef WIRE_H
#define WIRE_H

#include "CrtxI2C.h"

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

typedef uint16_t wire_buffer_len;

#define WIRE_FLAG_WRITE							0x1
#define WIRE_FLAG_READ							0x2
#define WIRE_FLAG_STOP							0x4
#define WIRE_FLAG_ASYNC							0x8
#define WIRE_FLAG_FAILL_LONG					0x80

typedef struct							ZunoWireI2CTypeConfig_s
{
	I2C_TypeDef							*i2c;
	ZunoSync_t							*lpLock;
	void								*IRQHandler;
	wire_buffer_len						*aviable;
	ZDMA_PeripheralSignal_t				dmaSignalRead;
	ZDMA_PeripheralSignal_t				dmaSignalWrite;
	CMU_Clock_TypeDef					bus_clock;
	IRQn_Type							irqType;
	uint8_t								subType;
	uint8_t								scl;
	uint8_t								sda;
}										ZunoWireI2CTypeConfig_t;

class TwoWire {
	public:
		TwoWire(uint8_t numberConfig);
		inline ZunoError_t						begin(void) {return (this->begin(0));};//0 - master
		inline ZunoError_t						begin(uint8_t scl, uint8_t sda) {return (this->begin(0, scl, sda));};//0 - master
		inline ZunoError_t						begin(uint8_t address) {return (this->begin(address, this->_i2c_config->scl, this->_i2c_config->sda));};
		ZunoError_t								begin(uint8_t address, uint8_t scl, uint8_t sda);
		inline ZunoError_t						begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len) {return (this->_begin(address, scl, sda, b, len, false));};
		inline void								beginTransmission(uint8_t address) {this->beginTransmission(address, false);};
		void									beginTransmission(uint8_t address, uint8_t forced_start);
		inline size_t							write(uint8_t data) {return (this->write(&data, 1));};
		size_t									write(const char *data);
		size_t									write(const uint8_t *data, wire_buffer_len quantity);
		inline uint8_t							transfer(uint8_t address, void *b, wire_buffer_len count) {return (this->_transferMasterToSlaveLock(address, b, count, WIRE_FLAG_STOP | WIRE_FLAG_WRITE));};
		uint8_t									transfer(uint8_t address, void *b);
		inline uint8_t							transfer(uint8_t address, const char *b) {return (this->transfer(address, (void *)b));};
		inline uint8_t							endTransmission(void) {return (this->endTransmission(WIRE_FLAG_STOP));};
		uint8_t									endTransmission(uint8_t sendStop) {return (_transferMasterToSlaveLock(this->_address, this->_buffer, this->_buffer_count, ((sendStop == true) ? WIRE_FLAG_STOP : 0)));};
		inline wire_buffer_len					requestFrom(uint8_t address, wire_buffer_len quantity) {return (this->requestFrom(address, quantity, true));};
		inline wire_buffer_len					requestFrom(uint8_t address, wire_buffer_len quantity, uint8_t sendStop) {return (this->_requestFromLock(address, quantity, ((sendStop == true) ? WIRE_FLAG_STOP : 0)));};
		inline uint8_t							requestFromAsync(uint8_t address, wire_buffer_len quantity) {return (this->requestFrom(address, quantity, true));};
		inline uint8_t							requestFromAsync(uint8_t address, wire_buffer_len quantity, uint8_t sendStop) {return (this->_requestFromLock(address, quantity, ((sendStop == true) ? WIRE_FLAG_STOP : 0) | WIRE_FLAG_ASYNC));};
		wire_buffer_len							available(void);
		uint8_t									read(void);
		inline void								enableTS(uint8_t on_off) {};
		void									setClock(uint32_t clock);
		inline void								end(void) {zunoSyncClose(this->_i2c_config->lpLock, SyncMasterI2c, this->_deInit, (size_t)this, &this->_lpKey);};

	private:
		inline wire_buffer_len					_available(const ZunoWireI2CTypeConfig_t *i2c_config);
		inline uint8_t							_read(const ZunoWireI2CTypeConfig_t *i2c_config);
		inline size_t							_write(const uint8_t *data, wire_buffer_len quantity);
		inline void								_beginTransmission(uint8_t address, uint8_t forced_start, const ZunoWireI2CTypeConfig_t *config);
		inline void								_setBusFreq(I2C_TypeDef *i2c, uint32_t freqScl);
		wire_buffer_len							_requestFromLock(uint8_t address, wire_buffer_len quantity, size_t bFlags);
		inline wire_buffer_len					_requestFrom(uint8_t address, wire_buffer_len quantity, size_t bFlags, const ZunoWireI2CTypeConfig_t *i2c_config);
		ZunoError_t								_begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len, uint8_t bFree);
		uint8_t									_transferMasterToSlaveLock(uint16_t address, void *b, size_t len, size_t bFlags);
		inline uint8_t							_transferMasterToSlave(uint16_t address, void *b, size_t len, size_t bFlags, const ZunoWireI2CTypeConfig_t *i2c_config);
		static void								_I2C0_IRQHandler(size_t flags);
		static void								_I2C1_IRQHandler(size_t flags);
		static void								_I2C_IRQHandler(const ZunoWireI2CTypeConfig_t *i2c_config, size_t flags);
		static size_t							_getUniqZDma(const ZunoWireI2CTypeConfig_t *config) {return ((size_t)config->i2c); };
		static ZunoError_t						_init(size_t param);
		static void								_deInit(size_t param);
		static const ZunoWireI2CTypeConfig_t	_configTable0;
		static const ZunoWireI2CTypeConfig_t	_configTable1;
		static wire_buffer_len					_i2c0_aviable;
		static wire_buffer_len					_i2c1_aviable;
		const ZunoWireI2CTypeConfig_t			*_i2c_config;
		size_t									_freqScl;//To set the bus frequency, only valid in master mode - setClock
		uint8_t									*_buffer;
		wire_buffer_len							_buffer_max;
		wire_buffer_len							_buffer_count;
		uint8_t									_address;
		uint8_t									_flags;
		uint8_t									_bFree;
		volatile uint8_t						_lpKey;
};

extern TwoWire Wire;

#endif// WIRE_H