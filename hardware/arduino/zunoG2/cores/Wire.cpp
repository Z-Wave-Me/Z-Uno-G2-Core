#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxI2C.h"
#include "ZDma.h"
#include "Wire_private.h"

static wire_buffer_len i2c0_aviable;
static wire_buffer_len i2c1_aviable;

static const ZunoWireI2CTypeConfig_t	i2c0_config = {
	.i2c = I2C0,
	.aviable = &i2c0_aviable,
	.dmaSignalRead = zdmaPeripheralSignal_I2C0_RXDATAV,
	.dmaSignalWrite = zdmaPeripheralSignal_I2C0_TXBL,
	.bus_clock = cmuClock_I2C0,
	.irqType = I2C0_IRQn,
	.scl = SCL,
	.sda = SDA
};

static const ZunoWireI2CTypeConfig_t	i2c1_config = {
	.i2c = I2C1,
	.aviable = &i2c1_aviable,
	.dmaSignalRead = zdmaPeripheralSignal_I2C1_RXDATAV,
	.dmaSignalWrite = zdmaPeripheralSignal_I2C1_TXBL,
	.bus_clock = cmuClock_I2C1,
	.irqType = I2C1_IRQn,
	.scl = SCL1,
	.sda = SDA1
};

static void _setBusFreq(I2C_TypeDef *i2c, uint32_t freqScl) {
	I2C_ClockHLR_TypeDef		clhr;

	if (freqScl <= I2C_FREQ_STANDARD_MAX)
		clhr = i2cClockHLRStandard;
	else if (freqScl <= I2C_FREQ_FAST_MAX)
		clhr = i2cClockHLRAsymetric;
	else
		clhr = i2cClockHLRFast;
	I2C_BusFreqSet(i2c, 0, freqScl, clhr);
}

static inline size_t _getUniqZDma(const ZunoWireI2CTypeConfig_t *config) {
	return ((size_t)config->i2c);
}

static void _I2C_IRQHandler(const ZunoWireI2CTypeConfig_t *i2c_config, size_t flags) {
	I2C_TypeDef						*i2c;
	size_t							uniqId;

	i2c = i2c_config->i2c;
	uniqId = _getUniqZDma(i2c_config);
	if ((i2c->IEN & I2C_IF_RXFULL) != 0)
		i2c_config->aviable[0] -= ZDMA.transferRemainingCount(uniqId);
	i2c->IEN = _I2C_IEN_RESETVALUE;
	i2c->CMD = I2C_CMD_STOP;
	ZDMA.stopTransfer(uniqId, true);
}

void _I2C1_IRQHandler(size_t flags) {
	_I2C_IRQHandler(&i2c1_config, flags);
}

void _I2C0_IRQHandler(size_t flags) {
	_I2C_IRQHandler(&i2c0_config, flags);
}

/* Public Constructors */
TwoWire::TwoWire(uint8_t one): _freqScl(0), _buffer(0), _buffer_count(0), _buffer_max(0), _address(0), _flags(0), _bufferFree(false), _i2c_config(&i2c1_config) {
	zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_I2C1, (void *)_I2C1_IRQHandler);
}

TwoWire::TwoWire(): _freqScl(0), _buffer(0), _buffer_count(0), _buffer_max(0), _address(0), _flags(0), _bufferFree(false), _i2c_config(&i2c0_config) {
	zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_I2C0, (void *)_I2C0_IRQHandler);
}

/* Public Methods */
ZunoError_t TwoWire::begin(void) {
	return (this->begin(0));//0 - master
}

ZunoError_t TwoWire::begin(uint8_t scl, uint8_t sda) {
	return (this->begin(0, scl, sda));//0 - master
}

ZunoError_t TwoWire::begin(uint8_t address) {
	return (this->begin(address, this->_i2c_config->scl, this->_i2c_config->sda));
}

ZunoError_t TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda) {
	void				*b;
	size_t				len;

	if ((b = malloc(WIRE_BUFFER_LENGTH)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(address, scl, sda, b, WIRE_BUFFER_LENGTH, true));
}

ZunoError_t TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len) {
	return (this->_begin(address, scl, sda, b, len, false));
}

void TwoWire::beginTransmission(uint8_t address) {
	this->beginTransmission(address, false);
}

void TwoWire::beginTransmission(uint8_t address, uint8_t forced_start) {
	const ZunoWireI2CTypeConfig_t			*i2c_config;
	size_t									uniqId;

	i2c_config = this->_i2c_config;
	uniqId = _getUniqZDma(i2c_config);
	if (ZDMA.isProcessing(uniqId) == true) {
		if (forced_start == false)
			return ;
		i2c_config->i2c->IEN = _I2C_IEN_RESETVALUE;
		ZDMA.stopTransfer(uniqId, true);
	}
	this->_address = address;
	this->_buffer_count = 0;
	this->_flags = WIRE_FLAG_WRITE;
}

size_t TwoWire::write(uint8_t data) {
	return (this->write(&data, 1));
}

size_t TwoWire::write(const uint8_t *data, wire_buffer_len quantity) {
	size_t			count;
	uint8_t			*b;

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

size_t TwoWire::write(const char *data) {
	return (this->write((const uint8_t *)data, strlen(data)));
}

uint8_t TwoWire::transfer(uint8_t address, void *b) {
	this->transfer(address, b, strlen((char *)b));
}

uint8_t TwoWire::transfer(uint8_t address, const char *b) {
	this->transfer(address, (void *)b);
}

uint8_t TwoWire::transfer(uint8_t address, void *b, uint16_t count) {
	if (ZDMA.isProcessing(_getUniqZDma(this->_i2c_config) == true))
		return (0);
	return (_transferMasterToSlave(address, b, count));
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	I2C_TransferReturn_TypeDef			tempos;
	size_t								flags;
	uint8_t								out;

	flags = this->_flags;
	if ((flags & WIRE_FLAG_WRITE) == 0)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	if ((flags & WIRE_FLAG_FAILL_LONG) != 0) {
		this->_flags = 0;
		return (WIRE_ERORR_TRANSMISSION_LONG);
	}
	out = _transferMasterToSlave(this->_address, this->_buffer, this->_buffer_count);
	this->_flags = 0;
	return (out);
}

uint8_t TwoWire::endTransmission(void) {
	return (this->endTransmission(true));
}

wire_buffer_len TwoWire::requestFrom(uint8_t address, wire_buffer_len quantity) {
	return (this->requestFrom(address, quantity, true));
}

wire_buffer_len TwoWire::requestFrom(uint8_t address, wire_buffer_len quantity, uint8_t sendStop) {
	uint8_t						flags;

	flags = (sendStop == true) ? WIRE_FLAG_STOP : 0;
	return (this->_requestFrom(address, quantity, flags));
}

uint8_t TwoWire::requestFromAsync(uint8_t address, wire_buffer_len quantity) {
	return (this->requestFrom(address, quantity, true));
}

uint8_t TwoWire::requestFromAsync(uint8_t address, wire_buffer_len quantity, uint8_t sendStop) {
	uint8_t						flags;

	flags = (sendStop == true) ? WIRE_FLAG_STOP : 0;
	return (this->_requestFrom(address, quantity, flags | WIRE_FLAG_ASYNC));
}

wire_buffer_len TwoWire::available(void) {
	if ((this->_flags & WIRE_FLAG_READ) == 0)
		return (0);
	return (this->_i2c_config->aviable[0] - this->_buffer_count);
}

uint8_t TwoWire::read(void) {
	wire_buffer_len						buffer_count;

	if ((this->_flags & WIRE_FLAG_READ) == 0)
		return (0);
	if ((buffer_count = this->_buffer_count) == this->_i2c_config->aviable[0])
		return (0);
	this->_buffer_count++;
	return (this->_buffer[buffer_count]);
}

void TwoWire::enableTS(uint8_t on_off) {

}

void TwoWire::setClock(uint32_t clock) {
	uint32_t		freqScl;

	if (clock == 0)
		return ;
	freqScl = this->_freqScl;
	this->_freqScl = clock;
	if (freqScl != clock && freqScl != 0)
		_setBusFreq(this->_i2c_config->i2c, clock);
}

void TwoWire::end(void) {
	I2C_Reset(this->_i2c_config->i2c);
}

/* Private Methods */
ZunoError_t TwoWire::_begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, wire_buffer_len len, uint8_t bufferFree) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	I2C_TypeDef							*i2c;

	if (this->_bufferFree == true)
		free(this->_buffer);
	this->_bufferFree = bufferFree;
	this->_buffer = (uint8_t *)b;
	this->_buffer_max = len;
	this->end();
	i2c_config = this->_i2c_config;
	CMU_ClockEnable(i2c_config->bus_clock, true);
	pinMode(scl, GPIOMODE_OUTPUT_OPENDRAINPUP);/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(sda, GPIOMODE_OUTPUT_OPENDRAINPUP);
	i2c = i2c_config->i2c;
	i2c->CTRL = I2C_CTRL_CLTO_320PCC//Enable the Clock Low Timeout counter.
	| I2C_CTRL_AUTOSE | I2C_CTRL_AUTOACK//Auto Stop and Ack
	| (((address == 0) ? 0 : 1) << _I2C_CTRL_SLAVE_SHIFT);// Set SLAVE select mode. 0 == master
	if (this->_freqScl == 0)
		this->_freqScl = I2C_FREQ_STANDARD_MAX;
	_setBusFreq(i2c, this->_freqScl);
	I2C_Enable(i2c, true);
	if (i2c == I2C0)
		i2c->ROUTELOC0 = (getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (((getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, scl) -1) % WIRE_LOCATION_SIZE) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	else
		i2c->ROUTELOC0 = ((sda == SDA1 ? 20 : 19) << _I2C_ROUTELOC0_SDALOC_SHIFT) | ((scl == SCL1 ? 18 : 19) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	i2c->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	NVIC_EnableIRQ(i2c_config->irqType);/* Enable interrupts in NVIC */
	return (ZunoErrorOk);
}

uint8_t TwoWire::_transferMasterToSlave(uint16_t address, void *b, size_t len) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	I2C_TypeDef							*i2c;
	ZunoError_t							ret;
	size_t								uniq;
	size_t								freqScl;

	i2c_config = this->_i2c_config;
	i2c = i2c_config->i2c;
	i2c->IEN = _I2C_IEN_RESETVALUE;//just in case
	i2c->CMD = I2C_CMD_CLEARPC | I2C_CMD_CLEARTX | I2C_CMD_ABORT;//Ensure buffers are empty.
	I2C_IntClear(i2c, _I2C_IF_MASK);
	i2c->TXDATA = WIRE_ADDRESS_7BIT(address);// Data not transmitted until the START is sent.
	i2c->CMD = I2C_CMD_START;
	uniq = _getUniqZDma(i2c_config);
	if ((ret = ZDMA.toMemoryPeripheral(uniq, i2c_config->dmaSignalWrite, (void*)&(i2c->TXDATA), b, len, zdmaData8)) == ZunoErrorOk) {
		I2C_IntEnable(i2c, WIRE_IEN_FLAGS_WRITE);
		if ((freqScl = this->_freqScl / 1000) != 0)
			freqScl = len * 8 / freqScl;
		delay((freqScl == 0)? 1 : freqScl);
		while (ZDMA.isProcessing(uniq) == true) {
			delay(1);
			Serial0.println("Int error: ");
			Serial0.println(I2C0->IF);//Тут только если ошибка - нужно больше разных тестов дабы все ошибки отловить
		}
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	}
	else {
		Serial0.print("Code Error: ");//Ошибка из-за отсутвие синхранизации походу - в любом случае со временем считает что все каналы заняты
		Serial0.println(ret);
	}
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

wire_buffer_len TwoWire::_requestFrom(uint8_t address, wire_buffer_len quantity, uint8_t flags) {
	const ZunoWireI2CTypeConfig_t		*i2c_config;
	I2C_TypeDef							*i2c;
	ZunoError_t							ret;
	size_t								uniqId;
	size_t								freqScl;

	if (quantity > this->_buffer_max || (this->_flags & WIRE_FLAG_WRITE) != 0)
		return (0);
	i2c_config = this->_i2c_config;
	uniqId = _getUniqZDma(i2c_config);
	if (ZDMA.isProcessing(uniqId) == true)
		return (0);
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
		// if ((flags & WIRE_FLAG_ASYNC) != 0) {
		// 	this->_flags = WIRE_FLAG_READ | WIRE_FLAG_ASYNC;
		// 	return (true);
		// }
		if ((freqScl = this->_freqScl / 1000) != 0)
			freqScl = quantity * 8 / freqScl;
		delay((freqScl == 0)? 1 : freqScl);
		while (ZDMA.isProcessing(uniqId) == true) {
			delay(1);
			Serial0.println("DMA");
			Serial0.println(I2C0->IF);//Тут только если ошибка - нужно больше разных тестов дабы все ошибки отловить
		}
		return (i2c_config->aviable[0]);
	}
	Serial0.print("Code Error: ");//Ошибка из-за отсутвие синхранизации походу - в любом случае со временем считает что все каналы заняты
	Serial0.println(ret);
	return (0);
}

/* Preinstantiate Objects */
TwoWire Wire = TwoWire();