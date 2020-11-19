#include "Arduino.h"
#include "ZGecko.h"
#include "ZDma.h"
#include "Wire.h"

/* Layout details, A = address bit, X = don't care bit (set to 0):
	7 bit address - use format AAAA AAAX.
	10 bit address - use format XXXX XAAX AAAA AAAA */
#define WIRE_ADDRESS_7BIT(x)					((uint8_t)(x << 1))
#define WIRE_ADDRESS_10BIT(x)					((uint16_t)((x & 0xFF) | (x >> 7) & 0x6))

#define WIRE_IEN_FLAGS_WRITE					(I2C_IEN_BUSERR | I2C_IEN_ARBLOST | I2C_IEN_SSTOP | I2C_IEN_CLTO | I2C_IEN_NACK | I2C_IEN_CLERR | I2C_IEN_TXC)
#define WIRE_IF_FLAGS_WRITE						(I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_SSTOP | I2C_IF_CLTO | I2C_IF_NACK | I2C_IF_CLERR | I2C_IF_TXC)

#define WIRE_IEN_FLAGS_READ						(I2C_IEN_BUSERR | I2C_IEN_ARBLOST | I2C_IEN_SSTOP | I2C_IEN_CLTO | I2C_IEN_NACK | I2C_IEN_CLERR | I2C_IEN_RXFULL)
#define WIRE_IF_FLAGS_READ						(I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_SSTOP | I2C_IF_CLTO | I2C_IF_NACK | I2C_IF_CLERR | I2C_IF_RXFULL)

/* Variables */
wire_buffer_len TwoWire::_i2c0_aviable = 0;
wire_buffer_len TwoWire::_i2c1_aviable = 0;

/* Constants */
const ZunoWireI2CTypeConfig_t	TwoWire::_configTable0 =
{
	.i2c = I2C0,
	.lpLock = &gSyncIC0,
	.IRQHandler = (void *)TwoWire::_I2C0_IRQHandler,
	.aviable = &TwoWire::_i2c0_aviable,
	.dmaSignalRead = zdmaPeripheralSignal_I2C0_RXDATAV,
	.dmaSignalWrite = zdmaPeripheralSignal_I2C0_TXBL,
	.bus_clock = cmuClock_I2C0,
	.irqType = I2C0_IRQn,
	.subType = ZUNO_IRQVEC_I2C0,
	.scl = SCL,
	.sda = SDA
};

const ZunoWireI2CTypeConfig_t	TwoWire::_configTable1 =
{
	.i2c = I2C1,
	.lpLock = &gSyncIC1,
	.IRQHandler = (void *)TwoWire::_I2C1_IRQHandler,
	.aviable = &TwoWire::_i2c1_aviable,
	.dmaSignalRead = zdmaPeripheralSignal_I2C1_RXDATAV,
	.dmaSignalWrite = zdmaPeripheralSignal_I2C1_TXBL,
	.bus_clock = cmuClock_I2C1,
	.irqType = I2C1_IRQn,
	.subType = ZUNO_IRQVEC_I2C1,
	.scl = SCL1,
	.sda = SDA1
};

/* Public Constructors */
TwoWire::TwoWire(uint8_t numberConfig)
#if (ZUNO_ZERO_BSS != true || false != 0)
	: _freqScl(0), _buffer(0), _buffer_count(0), _buffer_max(0), _address(0), _flags(0), _bFree(false), _lpKey(0)
#endif
{
	const ZunoWireI2CTypeConfig_t				*config;

	switch (numberConfig) {
		case 1:
			config = &this->_configTable1;
			break ;
		default:
			config = &this->_configTable0;
			break ;
	}
	this->_i2c_config = config;
}

/* Public Methods */
ZunoError_t TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda) {
	void				*b;
	size_t				len;

	if ((b = malloc(WIRE_BUFFER_LENGTH)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(address, scl, sda, b, WIRE_BUFFER_LENGTH, true));
}

void TwoWire::beginTransmission(uint8_t address, uint8_t forced_start) {
	const ZunoWireI2CTypeConfig_t			*config;

	config = this->_i2c_config;
	if (zunoSyncLockRead(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return ;
	this->_beginTransmission(address, forced_start, config);
	zunoSyncReleseRead(config->lpLock, SyncMasterI2c, &this->_lpKey);
}

size_t TwoWire::write(const uint8_t *data, wire_buffer_len quantity) {
	const ZunoWireI2CTypeConfig_t			*config;
	size_t									out;

	config = this->_i2c_config;
	if (zunoSyncLockRead(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = this->_write(data, quantity);
	zunoSyncReleseRead(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

size_t TwoWire::write(const char *data) {
	return (this->write((const uint8_t *)data, strlen(data)));
}

uint8_t TwoWire::transfer(uint8_t address, void *b) {
	return (this->transfer(address, b, strlen((char *)b)));
}

wire_buffer_len TwoWire::available(void) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	wire_buffer_len						out;

	i2c_config = this->_i2c_config;
	if (zunoSyncLockRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = this->_available(i2c_config);
	zunoSyncReleseRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

uint8_t TwoWire::read(void) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	wire_buffer_len						out;

	i2c_config = this->_i2c_config;
	if (zunoSyncLockRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = this->_read(i2c_config);
	zunoSyncReleseRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

void TwoWire::setClock(uint32_t clock) {
	uint32_t								freqScl;
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	
	if (clock == 0)
		return ;
	i2c_config = this->_i2c_config;
	if (zunoSyncLockRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return ;
	freqScl = this->_freqScl;
	this->_freqScl = clock;
	if (freqScl != clock && freqScl != 0)
		this->_setBusFreq(this->_i2c_config->i2c, clock);
	zunoSyncReleseRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
}

/* Private Methods */
inline wire_buffer_len TwoWire::_available(const ZunoWireI2CTypeConfig_t *i2c_config) {
	wire_buffer_len						aviable_count;
	wire_buffer_len						buffer_count;

	if ((this->_flags & WIRE_FLAG_READ) == 0)
		return (0);
	aviable_count = this->_i2c_config->aviable[0];
	if ((buffer_count = this->_buffer_count) >= aviable_count)
		return (0);
	return (aviable_count - buffer_count);
}

inline uint8_t TwoWire::_read(const ZunoWireI2CTypeConfig_t *i2c_config) {
	wire_buffer_len						buffer_count;

	if ((this->_flags & WIRE_FLAG_READ) == 0)
		return (0);
	if ((buffer_count = this->_buffer_count) >= this->_i2c_config->aviable[0])
		return (0);
	this->_buffer_count++;
	return (this->_buffer[buffer_count]);
}

inline size_t TwoWire::_write(const uint8_t *data, wire_buffer_len quantity) {
	size_t									count;
	uint8_t									*b;

	if (this->_flags != WIRE_FLAG_WRITE)
		return (0);
	count = this->_buffer_count;
	b = &this->_buffer[count];
	count = count + quantity;
	if (count > this->_buffer_max) {
		this->_flags |= WIRE_FLAG_FAILL_LONG;
		return (0);
	}
	this->_buffer_count = count;
	count = 0;
	while (count < quantity) {
		b[count] = data[count];
		count++;
	}
	return (quantity);
}

void TwoWire::_beginTransmission(uint8_t address, uint8_t forced_start, const ZunoWireI2CTypeConfig_t *config) {
	size_t									uniqId;

	uniqId = this->_getUniqZDma(config);
	if (ZDMA.isProcessing(uniqId) == true) {
		if (forced_start == false)
			return ;
		config->i2c->IEN = _I2C_IEN_RESETVALUE;
		ZDMA.stopTransfer(uniqId, true);
	}
	this->_address = address;
	this->_buffer_count = 0;
	this->_flags = WIRE_FLAG_WRITE;
}

void TwoWire::_deInit(size_t param) {
	TwoWire								*twoWire;
	const ZunoWireI2CTypeConfig_t		*config;

	twoWire = (TwoWire *)param;
	config = twoWire->_i2c_config;
	I2C_Reset(config->i2c);
	if (twoWire->_bFree == true) {
		free(twoWire->_buffer);
		twoWire->_bFree = false;
	}
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, config->subType, config->IRQHandler);
}

ZunoError_t TwoWire::_init(size_t param) {
	I2C_TypeDef							*i2c;
	ZunoError_t							ret;
	TwoWire								*twoWire;
	const ZunoWireI2CTypeConfig_t		*config;

	twoWire = (TwoWire *)param;
	config = twoWire->_i2c_config;
	i2c = config->i2c;
	i2c->IEN = _I2C_IEN_RESETVALUE;//just in case
	if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, config->subType, config->IRQHandler)) != ZunoErrorOk)
		return (ret);
	CMU_ClockEnable(config->bus_clock, true);
	i2c->CTRL = I2C_CTRL_CLTO_320PCC//Enable the Clock Low Timeout counter.
	| I2C_CTRL_AUTOSE | I2C_CTRL_AUTOACK;//Auto Stop and Ack
	if (twoWire->_freqScl == 0)
		twoWire->_freqScl = I2C_FREQ_STANDARD_MAX;
	twoWire->_setBusFreq(i2c, twoWire->_freqScl);
	i2c->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	I2C_Enable(i2c, true);
	NVIC_EnableIRQ(config->irqType);/* Enable interrupts in NVIC */
	return (ZunoErrorOk);
}

ZunoError_t TwoWire::_begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len, uint8_t bFree) {
	const ZunoWireI2CTypeConfig_t		*config;
	I2C_TypeDef							*i2c;
	ZunoSync_t							*lpLock;
	ZunoError_t							ret;
	size_t								location;

	if (scl > ZUNO_PIN_LAST_INDEX || sda > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	if (len == 0)
		return (ZunoErrorMemory);
	config = this->_i2c_config;
	lpLock = config->lpLock;
	i2c = config->i2c;
	if ((ret = zunoSyncOpen(lpLock, SyncMasterI2c, this->_init, (size_t)this, &this->_lpKey)) != ZunoErrorOk) {
		if (bFree == true)
			free(b);
		return (ret);
	}
	if (this->_bFree == true)
		free(this->_buffer);
	this->_bFree = bFree;
	this->_buffer = (uint8_t *)b;
	this->_buffer_max = len;
	pinMode(scl, GPIOMODE_OUTPUT_OPENDRAINPUP);/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(sda, GPIOMODE_OUTPUT_OPENDRAINPUP);
	i2c->CTRL |= (((address == 0) ? 0 : 1) << _I2C_CTRL_SLAVE_SHIFT);// Set SLAVE select mode. 0 == master
	if (i2c == I2C0)
		location = (getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (((getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), scl) -1) % sizeof(g_loc_pa0_pf7_all)) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	else
		location = ((sda == SDA1 ? 20 : 19) << _I2C_ROUTELOC0_SDALOC_SHIFT) | ((scl == SCL1 ? 18 : 19) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	i2c->ROUTELOC0 = location;
	zunoSyncReleseWrite(lpLock, SyncMasterI2c, &this->_lpKey);
	return (ZunoErrorOk);
}

uint8_t TwoWire::_transferMasterToSlaveLock(uint16_t address, void *b, size_t len, size_t bFlags) {
	uint8_t								out;
	const ZunoWireI2CTypeConfig_t		*i2c_config;

	i2c_config = this->_i2c_config;
	if (zunoSyncLockWrite(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_transferMasterToSlave(address, b, len, bFlags | this->_flags, i2c_config);
	zunoSyncReleseWrite(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

inline uint8_t TwoWire::_transferMasterToSlave(uint16_t address, void *b, size_t len, size_t bFlags, const ZunoWireI2CTypeConfig_t *i2c_config) {
	I2C_TypeDef							*i2c;
	ZunoError_t							ret;
	size_t								uniqId;

	if ((bFlags & WIRE_FLAG_WRITE) == 0)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	this->_flags = 0;
	if ((bFlags & WIRE_FLAG_FAILL_LONG) != 0)
		return (WIRE_ERORR_TRANSMISSION_LONG);
	uniqId = this->_getUniqZDma(i2c_config);
	ZDMA.stopTransfer(uniqId, true);
	if (len == 0)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	i2c = i2c_config->i2c;
	i2c->IEN = _I2C_IEN_RESETVALUE;//just in case
	i2c->CMD = I2C_CMD_CLEARPC | I2C_CMD_CLEARTX | I2C_CMD_ABORT;//Ensure buffers are empty.
	I2C_IntClear(i2c, _I2C_IF_MASK);
	i2c->TXDATA = WIRE_ADDRESS_7BIT(address);// Data not transmitted until the START is sent.
	i2c->CMD = I2C_CMD_START;
	if ((ret = ZDMA.toMemoryPeripheral(uniqId, i2c_config->dmaSignalWrite, (void*)&(i2c->TXDATA), b, len, zdmaData8)) == ZunoErrorOk) {
		I2C_IntEnable(i2c, WIRE_IEN_FLAGS_WRITE);
		ZDMA.waitTransfer(uniqId);
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	}
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

wire_buffer_len TwoWire::_requestFromLock(uint8_t address, wire_buffer_len quantity, size_t bFlags) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	wire_buffer_len						out;

	i2c_config = this->_i2c_config;
	if (zunoSyncLockRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = this->_requestFrom(address, quantity, this->_flags | bFlags, i2c_config);
	zunoSyncReleseRead(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
}
wire_buffer_len TwoWire::_requestFrom(uint8_t address, wire_buffer_len quantity, size_t bFlags, const ZunoWireI2CTypeConfig_t *i2c_config) {
	
	I2C_TypeDef							*i2c;
	ZunoError_t							ret;
	size_t								uniqId;

	if (quantity > this->_buffer_max || (bFlags & WIRE_FLAG_WRITE) != 0)
		return (0);
	uniqId = this->_getUniqZDma(i2c_config);
	ZDMA.stopTransfer(uniqId, true);
	i2c = i2c_config->i2c;
	i2c->CMD = I2C_CMD_CLEARPC | I2C_CMD_CLEARTX | I2C_CMD_ABORT;//Ensure buffers are empty.
	while (i2c->STATUS & I2C_STATUS_RXDATAV)//Empty received data buffer
		i2c->RXDATA;
	I2C_IntClear(i2c, _I2C_IF_MASK);
	i2c->TXDATA = WIRE_ADDRESS_7BIT(address) | 1;// Data not transmitted until the START is sent. The I2C read bit is OR'ed with the address for a read operation 
	i2c->CMD = I2C_CMD_START;
	i2c_config->aviable[0] = quantity;
	this->_buffer_count = 0;
	this->_flags = WIRE_FLAG_READ;
	if ((ret = ZDMA.toPeripheralMemory(uniqId, i2c_config->dmaSignalRead, this->_buffer, (void*)&(i2c->RXDATA), quantity, zdmaData8)) == ZunoErrorOk) {
		I2C_IntEnable(i2c, WIRE_IEN_FLAGS_READ);
		if ((bFlags & WIRE_FLAG_ASYNC) != 0)
			return (true);
		ZDMA.waitTransfer(uniqId);
		return (i2c_config->aviable[0]);
	}
	return (0);
}

inline void TwoWire::_setBusFreq(I2C_TypeDef *i2c, uint32_t freqScl) {
	I2C_ClockHLR_TypeDef		clhr;

	if (freqScl <= I2C_FREQ_STANDARD_MAX)
		clhr = i2cClockHLRStandard;
	else if (freqScl <= I2C_FREQ_FAST_MAX)
		clhr = i2cClockHLRAsymetric;
	else
		clhr = i2cClockHLRFast;
	I2C_BusFreqSet(i2c, 0, freqScl, clhr);
}

void TwoWire::_I2C_IRQHandler(const ZunoWireI2CTypeConfig_t *i2c_config, size_t flags) {
	I2C_TypeDef						*i2c;
	size_t							uniqId;
	size_t							count;

	i2c = i2c_config->i2c;
	if (i2c->IEN == _I2C_IEN_RESETVALUE)
		return ;
	uniqId = TwoWire::_getUniqZDma(i2c_config);
	if ((i2c->IEN & I2C_IF_RXFULL) != 0 && ZDMA.transferReceivedCount(uniqId, &count) == ZunoErrorOk)
		i2c_config->aviable[0] = count;
	i2c->IEN = _I2C_IEN_RESETVALUE;
	i2c->CMD = I2C_CMD_STOP;
	ZDMA.stopTransfer(uniqId, true);
}

void TwoWire::_I2C1_IRQHandler(size_t flags) {
	TwoWire::_I2C_IRQHandler(&TwoWire::_configTable1, flags);
}

void TwoWire::_I2C0_IRQHandler(size_t flags) {
	TwoWire::_I2C_IRQHandler(&TwoWire::_configTable0, flags);
}

/* Preinstantiate Objects */
TwoWire Wire = TwoWire(0);