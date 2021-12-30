#ifndef WIRE_H
#define WIRE_H


#define Wire				Wire0

#define WIRE_BUFFER_LENGTH				(32)

#define I2C_ADDR_TIMEOUT_US              2000
#define I2C_ADDR_TIMEOUT_US_DIV          10

#define WIRE_ERORR_TRANSMISSION_SUCCESS			0
#define WIRE_ERORR_TRANSMISSION_LONG			1
#define WIRE_ERORR_TRANSMISSION_NACK_ADDRESS	2
#define WIRE_ERORR_TRANSMISSION_NACK_DATA		3
#define WIRE_ERORR_TRANSMISSION_OTHER			4
#define WIRE_ERORR_TRANSMISSION_TIMOUT			5

typedef struct							ZunoWireI2CTypeConfig_s
{
	I2C_TypeDef							*i2c;
	ZunoSync_t							*lpLock;
	void								*IRQHandler;
	LdmaClassSignal_t					dmaSignalRead;
	LdmaClassSignal_t					dmaSignalWrite;
	CMU_Clock_TypeDef					bus_clock;
	IRQn_Type							irq;
	uint8_t								subType;
	uint8_t								scl;
	uint8_t								sda;
}										ZunoWireI2CTypeConfig_t;

class TwoWire : public Stream {
	public:
		TwoWire(uint8_t numberConfig);
		void									begin(void) {this->begin((int)0x0);};
		void									begin(uint8_t address) {this->begin((int)address);};
		void									begin(int address) {this->begin(address, this->_i2c_config->scl, this->_i2c_config->sda);};
		void									beginTransmission(uint8_t address) {this->beginTransmission((int)address);};
		void									beginTransmission(int address);
		uint8_t									endTransmission(void) {return (this->endTransmission(true));};
		uint8_t									endTransmission(uint8_t sendStop);
		inline void								onReceive(void (*function)(int)) {this->_user_onReceive = function;};
		inline void								onRequest(void (*function)(void)) {this->_user_onRequest = function;};
		uint8_t									requestFrom(uint8_t address, uint8_t quantity) {return (this->requestFrom((int)address, (int)quantity, true));};
		uint8_t									requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {return (this->requestFrom((int)address, (int)quantity, (int)sendStop));};
		uint8_t									requestFrom(int address, int quantity) {return (this->requestFrom((int)address, (int)quantity, true));};
		uint8_t									requestFrom(int address, int quantity, int sendStop);
		virtual size_t							write(uint8_t data) { return (this->write((const uint8_t *)&data, 0x1));};
		virtual size_t							write(const uint8_t *data, size_t quantity);
		virtual int								available(void);
		virtual int								read(void);
		virtual int								peek(void);
		virtual void							flush(void) {};
		inline size_t							write(unsigned long n) { return write((uint8_t)n); }
		inline size_t							write(long n) { return write((uint8_t)n); }
		inline size_t							write(unsigned int n) { return write((uint8_t)n); }
		inline size_t							write(int n) { return write((uint8_t)n); }
		using Print::write;
		void									setClock(uint32_t clock);
		inline void								end(void) {zunoSyncClose(this->_i2c_config->lpLock, SyncMasterI2c, TwoWire::_deInit, (size_t)this, &this->_lpKey);};
		inline void								setWireTimeout(uint32_t timeout) {this->_timout_ms = timeout;};

		ZunoError_t								begin(int address, uint8_t scl, uint8_t sda);
		ZunoError_t								begin(int address, uint8_t scl, uint8_t sda, void *buffer, uint16_t len) {return (this->_begin(address, scl, sda, buffer, len, false));};
		inline void								enableTS(bool en) {(void)en;};
		uint8_t									transfer(int address, const char *buffer) {return (this->transfer(address, buffer, true));};
		uint8_t									transfer(int address, void *buffer, uint16_t count) {return (this->transfer(address, buffer, count, true));};
		uint8_t									transfer(int address, const char *buffer, uint8_t sendStop){return (this->transfer(address, (void *)buffer, strlen(buffer), sendStop));};
		uint8_t									transfer(int address, void *buffer, uint16_t count, uint8_t sendStop) {return (this->_transferMasterToSlave(address, buffer, count, sendStop));};

	private:
		ZunoError_t								_begin(int address, uint8_t scl, uint8_t sda, void *buffer, uint16_t len, uint8_t bFree);
		inline uint8_t							_transferMasterToSlaveInit(I2C_TypeDef *i2c, int adress, size_t bType);
		uint8_t									_transferMasterToSlave(int adress, void *b, uint16_t count, uint8_t sendStop);
		inline size_t							_transferSlaveToMaster(I2C_TypeDef *i2c, const uint8_t *b, size_t count);
		inline void								_setBusFreq(I2C_TypeDef *i2c, uint32_t freqScl);
		static void								_I2C0_IRQHandler(size_t flags, size_t value);
		static void								_I2C1_IRQHandler(size_t flags, size_t value);
		void									_I2C_IRQHandler(size_t flags, size_t value);
		inline uint8_t							_endTransmission(uint8_t sendStop);
		inline uint8_t							_requestFrom(int address, int quantity, int sendStop);
		inline int								_available(void);
		inline int								_read(void);
		inline int								_peek(void);
		inline size_t							_write(const uint8_t *data, size_t quantity);
		static ZunoError_t						_init(size_t param);
		static ZunoError_t						_deInit(size_t param);

		static const ZunoWireI2CTypeConfig_t			_configTable0;
		static const ZunoWireI2CTypeConfig_t			_configTable1;
		const ZunoWireI2CTypeConfig_t					*_i2c_config;
		void											(*_user_onRequest)(void);
		void											(*_user_onReceive)(int);
		LdmaClassReceivedCyclical_t						_arrayCyclical;
		uint32_t										_freqScl;//To set the bus frequency, only valid in master mode - setClock
		uint8_t											*_buffer;
		uint16_t										_buffer_max;
		uint16_t										_adress;
		uint16_t										_buffer_count;
		uint16_t										_buffer_count_read;
		uint8_t											_timout_ms;
		uint8_t											_flagErrorLong;
		uint8_t											_channel;
		uint8_t											_bFree;
		uint8_t											_lpKey;
		uint8_t											_address;
};

extern TwoWire Wire0;
extern TwoWire Wire1;

#endif// WIRE_H