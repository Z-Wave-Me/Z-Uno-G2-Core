#include "Arduino.h"
#include "ZGecko.h"
#include "Wire.h"
#include "stdlib.h"
#include "LdmaClass.h"

/* Layout details, A = address bit, X = don't care bit (set to 0):
	7 bit address - use format AAAA AAAX.
	10 bit address - use format XXXX XAAX AAAA AAAA */
#define WIRE_ADDRESS_7BIT(x)					((uint8_t)(x << _I2C_SADDR_ADDR_SHIFT))
#define WIRE_ADDRESS_10BIT(x)					((uint16_t)((x & 0xFF) | (x >> 7) & 0x6))

#define WIRE_LOCATION			g_loc_pa0_pf7_all
#define WIRE_LOCATION_SIZE		sizeof(g_loc_pa0_pf7_all)

/* Constants */
const ZunoWireI2CTypeConfig_t	TwoWire::_configTable0 =
{
	.i2c = I2C0,
	.lpLock = &gSyncIC0,
	.IRQHandler = (void *)TwoWire::_I2C0_IRQHandler,
	.dmaSignalRead = LdmaClassSignal_I2C0_RXDATAV,
	.dmaSignalWrite = LdmaClassSignal_I2C0_TXBL,
	.bus_clock = cmuClock_I2C0,
	.irq = I2C0_IRQn,
	.subType = ZUNO_IRQVEC_I2C0,
	.scl = SCL,
	.sda = SDA
};

const ZunoWireI2CTypeConfig_t	TwoWire::_configTable1 =
{
	.i2c = I2C1,
	.lpLock = &gSyncIC1,
	.IRQHandler = (void *)TwoWire::_I2C1_IRQHandler,
	.dmaSignalRead = LdmaClassSignal_I2C1_RXDATAV,
	.dmaSignalWrite = LdmaClassSignal_I2C1_TXBL,
	.bus_clock = cmuClock_I2C1,
	.irq = I2C1_IRQn,
	.subType = ZUNO_IRQVEC_I2C1,
	.scl = SCL1,
	.sda = SDA1
};

typedef struct							ZunoWireI2CInit_s
{
	TwoWire								*wire;
	void								*buffer;
	int									address;
	uint16_t							len;
}										ZunoWireI2CInit_t;


/* Public Constructors */
TwoWire::TwoWire(uint8_t numberConfig): _user_onRequest(0x0), _user_onReceive(0x0), _adress(0x0), _timout_ms(0x19), _flagErrorLong(false), _bFree(false), _lpKey(false), _address(0x0) {
	const ZunoWireI2CTypeConfig_t				*config;

	switch (numberConfig) {
		case 0x1:
			config = &this->_configTable1;
			break ;
		default:
			config = &this->_configTable0;
			break ;
	}
	this->_i2c_config = config;
}

/* Public Methods */
ZunoError_t TwoWire::begin(int address, uint8_t scl, uint8_t sda) {
	void				*b;
	size_t				len;

	len = (address == 0x0) ? WIRE_BUFFER_LENGTH : (WIRE_BUFFER_LENGTH * 0x2);
	if ((b = malloc(len)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(address, scl, sda, b, len, true));
}

void TwoWire::beginTransmission(int address) {
	const ZunoWireI2CTypeConfig_t			*config;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return ;
	this->_adress = address;
	this->_buffer_count = 0x0;
	this->_flagErrorLong = false;
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	const ZunoWireI2CTypeConfig_t			*config;
	uint8_t									out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_endTransmission(sendStop);
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
	const ZunoWireI2CTypeConfig_t			*config;
	uint8_t									out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (0x0);
	out = this->_requestFrom(address, quantity, sendStop);
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

int TwoWire::available(void) {
	const ZunoWireI2CTypeConfig_t			*config;
	int										out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_available();
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

int TwoWire::read(void) {
	const ZunoWireI2CTypeConfig_t			*config;
	int										out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_read();
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}


int TwoWire::peek(void) {
	const ZunoWireI2CTypeConfig_t			*config;
	int										out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_peek();
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	const ZunoWireI2CTypeConfig_t			*config;
	size_t										out;

	config = this->_i2c_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	out = this->_write(data, quantity);
	zunoSyncReleseWrite(config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (out);
}

void TwoWire::setClock(uint32_t clock) {
	uint32_t								freqScl;
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	
	if (clock == 0)
		return ;
	i2c_config = this->_i2c_config;
	if (zunoSyncLockWrite(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey) != ZunoErrorOk)
		return ;
	freqScl = this->_freqScl;
	this->_freqScl = clock;
	if (freqScl != clock && freqScl != 0)
		this->_setBusFreq(this->_i2c_config->i2c, clock);
	zunoSyncReleseWrite(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
}

/* Private Methods */
ZunoError_t TwoWire::_deInit(size_t param) {
	TwoWire								*twoWire;
	const ZunoWireI2CTypeConfig_t		*config;

	twoWire = (TwoWire *)param;
	config = twoWire->_i2c_config;
	LdmaClass::transferStop(twoWire->_channel);
	I2C_Reset(config->i2c);
	if (twoWire->_bFree == true) {
		free(twoWire->_buffer);
		twoWire->_bFree = false;
	}
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, config->subType, config->IRQHandler);
	return (ZunoErrorOk);
}

ZunoError_t TwoWire::_init(size_t param) {
	const ZunoWireI2CInit_t				*init;
	ZunoError_t							ret;
	TwoWire								*wire;
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	size_t								len;
	ssize_t								channel;

	init = (const ZunoWireI2CInit_t *)param;
	if (init->address == 0x0)
		return (ZunoErrorOk);
	wire = init->wire;
	i2c_config = wire->_i2c_config;
	if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, i2c_config->subType, i2c_config->IRQHandler)) != ZunoErrorOk)
		return (ret);
	len = init->len / 0x2;
	if ((channel = LdmaClass::receivedCyclical((void *)&i2c_config->i2c->RXDATA, (uint8_t *)init->buffer + len, len, i2c_config->dmaSignalRead, ldmaCtrlSizeByte, &wire->_arrayCyclical)) >= 0x0) {
		wire->_channel = channel;
		return (ZunoErrorOk);
	}
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, i2c_config->subType, i2c_config->IRQHandler);
	return (ZunoErrorDmaLimitChannel);
}

ZunoError_t TwoWire::_begin(int address, uint8_t scl, uint8_t sda, void *buffer, uint16_t len, uint8_t bFree) {
	I2C_TypeDef							*i2c;
	ZunoWireI2CInit_t					init;
	ZunoError_t							ret;
	const ZunoWireI2CTypeConfig_t		*i2c_config;

	if (scl > ZUNO_PIN_LAST_INDEX || sda > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	if (len == 0)
		return (ZunoErrorMemory);
	this->end();
	init.buffer = buffer;
	init.len = len;
	init.wire = this;
	init.address = address;
	i2c_config = this->_i2c_config;
	if ((ret = zunoSyncOpen(i2c_config->lpLock, SyncMasterI2c, TwoWire::_init, (size_t)&init, &this->_lpKey)) != ZunoErrorOk) {
		if (bFree == true)
			free(buffer);
		return (ret);
	}
	if (this->_bFree == true)
		free(this->_buffer);
	this->_bFree = bFree;
	this->_buffer = (uint8_t *)buffer;
	CMU_ClockEnable(i2c_config->bus_clock, true);
	pinMode(scl, gpioModeWiredAndPullUpFilter);/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(sda, gpioModeWiredAndPullUpFilter);
	i2c = i2c_config->i2c;
	if (i2c == I2C0)
		i2c->ROUTELOC0 = (getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (((getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, scl) -1) % WIRE_LOCATION_SIZE) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	else
		i2c->ROUTELOC0 = ((sda == SDA1 ? 20 : 19) << _I2C_ROUTELOC0_SDALOC_SHIFT) | ((scl == SCL1 ? 18 : 19) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	i2c->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	i2c->IEN = _I2C_IEN_RESETVALUE;
	I2C_IntClear(i2c, _I2C_IF_MASK);
	i2c->CTRL = I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;
	if (this->_freqScl == 0)
		this->_freqScl = I2C_FREQ_STANDARD_MAX;
	this->_setBusFreq(i2c, this->_freqScl);
	if (address != 0x0) {
		I2C_SlaveAddressSet(i2c, WIRE_ADDRESS_7BIT(address));
		I2C_SlaveAddressMaskSet(i2c, 0xFE); // must match exact address
		i2c->CTRL |= I2C_CTRL_SLAVE;
		I2C_IntEnable(i2c, (I2C_IEN_ADDR));
		NVIC_EnableIRQ(i2c_config->irq);
		len = len / 0x2;
	}
	this->_buffer_max = len;
	I2C_Enable(i2c, true);
	zunoSyncReleseWrite(i2c_config->lpLock, SyncMasterI2c, &this->_lpKey);
	return (ZunoErrorOk);
	(void)bFree;
}

inline uint8_t TwoWire::_transferMasterToSlaveInit(I2C_TypeDef *i2c, int adress, size_t bType) {
	uint32_t							timeout;
	uint32_t							pending;
	uint32_t							state;
	uint32_t							ms;


	i2c->CTRL &= ~(I2C_CTRL_AUTOSE);
	if ((((state = i2c->STATE) & I2C_STATE_BUSHOLD) == 0x0 && (state & I2C_STATE_BUSY) != 0x0) || this->_address != adress)
		i2c->CMD = I2C_CMD_ABORT;
	this->_address = adress;
	i2c->CMD = I2C_CMD_CLEARPC | I2C_CMD_CLEARTX;
	while ((i2c->STATUS & I2C_STATUS_RXDATAV) != 0x0)//Empty received data buffer
		i2c->RXDATA;
	if ((i2c->STATE & I2C_STATE_BUSHOLD) == 0x0) {
		I2C_IntClear(i2c, _I2C_IF_MASK);/* Clear all pending interrupts prior to starting a transfer. */
		i2c->TXDATA = WIRE_ADDRESS_7BIT((uint8_t)adress) | bType;
		i2c->CMD = I2C_CMD_START;
		timeout = 0;
		while (0xFF) {
			pending = i2c->IF;
			if ((pending & (I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_CLERR)) != 0x0) {
				i2c->CMD = I2C_CMD_ABORT;
				return (WIRE_ERORR_TRANSMISSION_OTHER);
			}
			if ((pending & (I2C_IF_NACK)) != 0x0)
				return (WIRE_ERORR_TRANSMISSION_NACK_ADDRESS);
			if ((pending & (I2C_IF_ACK)) != 0x0)
				break ;
			timeout++;
			if (timeout > (I2C_ADDR_TIMEOUT_US / I2C_ADDR_TIMEOUT_US_DIV)){
				i2c->CMD = I2C_CMD_ABORT;
				return (WIRE_ERORR_TRANSMISSION_TIMOUT);
			}
			delayMicroseconds(I2C_ADDR_TIMEOUT_US_DIV);
		}
	} 
	/*else {
		i2c->CMD = I2C_CMD_ABORT;
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	}*/
	return (WIRE_ERORR_TRANSMISSION_SUCCESS);
}

inline uint8_t TwoWire::_transferMasterToSlave(int adress, void *b, uint16_t count, uint8_t sendStop) {
	I2C_TypeDef							*i2c;
	uint32_t							pending;
	LdmaClassTransferSingle_t			array;
	ssize_t								channel;
	uint32_t							out;
	size_t								ms;
	size_t								dst;
	size_t								tempos;

	i2c = this->_i2c_config->i2c;
	if ((out = this->_transferMasterToSlaveInit(i2c, adress, 0x0)) != WIRE_ERORR_TRANSMISSION_SUCCESS){
		return (out);
	}
	if (count == 0x0)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	I2C_IntClear(i2c, _I2C_IF_MASK);/* Clear all pending interrupts prior to starting a transfer. */
	if ((channel = LdmaClass::transferSingle(b, (void *)&i2c->TXDATA, count, this->_i2c_config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) < 0)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	if (sendStop == true)
		i2c->CTRL |= I2C_CTRL_AUTOSE;
	dst = 0x0;
	ms = millis() + this->_timout_ms;
	while ((i2c->IF & (I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_CLERR | I2C_IF_TXC)) == 0){
		if(ms < millis()){
			ms = 0;
			break;
		}
		delay(1);
	}
	LdmaClass::transferStop(channel);
	pending = i2c->IF;
	if (sendStop == true)
		i2c->CTRL ^= I2C_CTRL_AUTOSE;
	if (ms == 0x0) {
		i2c->CMD = I2C_CMD_ABORT;
		return (WIRE_ERORR_TRANSMISSION_TIMOUT);
	}
	if ((pending & (I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_CLERR)) != 0x0) {
		i2c->CMD = I2C_CMD_ABORT;
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	}
	if ((pending & (I2C_IF_NACK)) != 0x0)
		return (WIRE_ERORR_TRANSMISSION_NACK_DATA);
	return (WIRE_ERORR_TRANSMISSION_SUCCESS);
}

inline size_t TwoWire::_transferSlaveToMaster(I2C_TypeDef *i2c, const uint8_t *b, size_t quantity) {
	LdmaClassTransferSingle_t			array;
	ssize_t								channel;

	if (quantity == 0x0)
		return (0x0);
	I2C_IntClear(i2c, I2C_IF_NACK);
	if ((channel = LdmaClass::transferSingle(b, (void *)&i2c->TXDATA, quantity, this->_i2c_config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) == -1)
		return (0x0);
	while (LdmaClass::transferDone(channel) == false && (i2c->IF & I2C_IF_NACK) == 0x0)
		delay(0x1);
	LdmaClass::transferStop(channel);
	i2c->CMD = I2C_CMD_CLEARTX;
	return (quantity);
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

void TwoWire::_I2C_IRQHandler(size_t flags, size_t value) {
	if ((flags & I2C_IF_ADDR) != 0) {
		LdmaClass::i2cFixReceived(this->_channel);
		if ((value & 0x1) != 0x0 && this->_user_onRequest != 0x0)
			this->_user_onRequest();
	}
}

void TwoWire::_I2C1_IRQHandler(size_t flags, size_t value) {
	Wire1._I2C_IRQHandler(flags, value);
}

void TwoWire::_I2C0_IRQHandler(size_t flags, size_t value) {
	Wire._I2C_IRQHandler(flags, value);
}

uint8_t TwoWire::_endTransmission(uint8_t sendStop) {

	if (this->_flagErrorLong == true)
		return (WIRE_ERORR_TRANSMISSION_LONG);
	return (this->_transferMasterToSlave(this->_adress, this->_buffer, this->_buffer_count, sendStop));
}

uint8_t TwoWire::_requestFrom(int address, int quantity, int sendStop) {
	I2C_TypeDef									*i2c;
	uint32_t									pending;
	LdmaClassTransferI2cRequestFromMaster_t		array;
	ssize_t										channel;
	size_t										ms;
	size_t										src;
	size_t										tempos;

	i2c = this->_i2c_config->i2c;
	this->_buffer_count = 0x0;
	this->_buffer_count_read = 0x0;
	if (quantity > this->_buffer_max)
		quantity = this->_buffer_max;
	if (quantity == 0x0)
		return (0x0);
	if (this->_transferMasterToSlaveInit(i2c, address, 0x1) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (0x0);
	I2C_IntClear(i2c, _I2C_IF_MASK);/* Clear all pending interrupts prior to starting a transfer. */
	if ((channel = LdmaClass::i2cRequestFrom(i2c, &this->_buffer[0], quantity, this->_i2c_config->dmaSignalRead, &array)) < 0x0)
		return (0x0);
	if (sendStop == true)
		i2c->CTRL |= I2C_CTRL_AUTOSE;
	src = 0x0;
	ms = 0x1;
	while ((i2c->STATE & _I2C_STATE_STATE_MASK) != I2C_STATE_STATE_IDLE && (i2c->IF & (I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_CLERR)) == 0x0) {
		if ((tempos = LdmaClass::ldmaGetSrc(channel)) != src) {
			src = tempos;
			ms = millis() + this->_timout_ms;
		}
		if (millis() > ms) {
			ms = 0x0;
			break ;
		}
		delay(0x1);
	}
	LdmaClass::transferStop(channel);
	pending = i2c->IF;
	i2c->CTRL |= I2C_CTRL_AUTOACK;//Включаем назад
	if (sendStop == true)
		i2c->CTRL ^= I2C_CTRL_AUTOSE;
	if (ms == 0x0) {
		i2c->CMD = I2C_CMD_ABORT;
		return (0x0);
	}
	if ((pending & (I2C_IF_BUSERR | I2C_IF_ARBLOST | I2C_IF_CLERR)) != 0x0) {
		i2c->CMD = I2C_CMD_ABORT;
		return (0x0);
	}
	this->_buffer_count = quantity;
	return (quantity);
}

int TwoWire::_available(void) {
	I2C_TypeDef							*i2c;

	i2c = this->_i2c_config->i2c;
	if ((i2c->CTRL & I2C_CTRL_SLAVE) != 0x0)
		return (LdmaClass::receivedAvailable(this->_channel));
	return (this->_buffer_count - this->_buffer_count_read);
}

int TwoWire::_read(void) {
	size_t			buffer_count_read;
	I2C_TypeDef		*i2c;

	i2c = this->_i2c_config->i2c;
	if ((i2c->CTRL & I2C_CTRL_SLAVE) != 0x0)
		return (LdmaClass::receivedReadPeek(this->_channel, true));
	buffer_count_read = this->_buffer_count_read;
	if (buffer_count_read >= this->_buffer_count)
		return (0x0);
	this->_buffer_count_read++;
	return (this->_buffer[buffer_count_read]);
}


int TwoWire::_peek(void) {
	size_t			buffer_count_read;
	I2C_TypeDef		*i2c;

	i2c = this->_i2c_config->i2c;
	if ((i2c->CTRL & I2C_CTRL_SLAVE) != 0x0)
		return (LdmaClass::receivedReadPeek(this->_channel, false));
	buffer_count_read = this->_buffer_count_read;
	if (buffer_count_read >= this->_buffer_count)
		return (0x0);
	return (this->_buffer[buffer_count_read]);
}

size_t TwoWire::_write(const uint8_t *data, size_t quantity) {
	size_t						len;
	uint8_t						*b;

	if (this->_adress == 0x0)
		return (0);
	if ((len = this->_buffer_count) + quantity > this->_buffer_max) {
		this->_flagErrorLong = true;
		return (0);
	}
	this->_buffer_count = len + quantity;
	b = &this->_buffer[len];
	len = 0;
	while (len < quantity) {
		b[len] = data[len];
		len++;
	}
	return (quantity);
}

/* Preinstantiate Objects */
TwoWire Wire0 = TwoWire(0);
TwoWire Wire1 = TwoWire(1);