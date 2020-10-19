#include "Arduino.h"
#include "stdlib.h"
#include "CrtxI2C.h"
#include "Wire_private.h"

static const ZunoWireI2CTypeConfig_t	i2c0_config = {
	.i2c = I2C0,
	.bus_clock = cmuClock_I2C0,
	.scl = SCL,
	.sda = SDA
};

static const ZunoWireI2CTypeConfig_t	i2c1_config = {
	.i2c = I2C1,
	.bus_clock = cmuClock_I2C1,
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

/* Public Constructors */
TwoWire::TwoWire(I2C_TypeDef *i2c): _freqScl(0), seq_return(i2cTransferDone), available_bytes(0), seq( {0, 0, 0, 0, 0, 0}) {
	if (i2c == I2C1)
		this->_i2c_config = &i2c1_config;
	else
		this->_i2c_config = &i2c0_config;
}

TwoWire::TwoWire(): _freqScl(0), seq_return(i2cTransferDone), available_bytes(0), seq( {0, 0, 0, 0, 0, 0}) {
	this->_i2c_config = &i2c0_config;
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
	return (this->begin(address, scl, sda, b, WIRE_BUFFER_LENGTH));
}

ZunoError_t TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda, void *b, uint16_t len) {
	I2C_TypeDef					*i2c;
	void						*data;

	data = (void *)this->seq.buf->data;
	if (zunoIsMalloc(data) == true)
		free(data);
	this->seq.buf->data = (uint8_t *)b;
	this->_doubleBuffer_len = len;
	this->end();
	CMU_ClockEnable(this->_i2c_config->bus_clock, true);
	pinMode(scl, GPIOMODE_OUTPUT_OPENDRAINPUP);/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(sda, GPIOMODE_OUTPUT_OPENDRAINPUP);
	i2c = this->_i2c_config->i2c;
	i2c->IEN = 0;
	I2C_IntClear(i2c, _I2C_IF_MASK);
	BUS_RegBitWrite(&(i2c->CTRL), _I2C_CTRL_SLAVE_SHIFT, (address == 0) ? 0 : 1);// Set SLAVE select mode. 0 == master
	if (this->_freqScl == 0)
		this->_freqScl = I2C_FREQ_STANDARD_MAX;
	_setBusFreq(i2c, this->_freqScl);
	I2C_Enable(i2c, true);
	if (i2c == I2C0)
		i2c->ROUTELOC0 = (getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (((getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, scl) -1) % WIRE_LOCATION_SIZE) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	else
		i2c->ROUTELOC0 = ((sda == SDA1 ? 20 : 19) << _I2C_ROUTELOC0_SDALOC_SHIFT) | ((scl == SCL1 ? 18 : 19) << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	i2c->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	return (ZunoErrorOk);
}



void TwoWire::beginTransmission(uint8_t address) {
	this->beginTransmission(address, false);
}

void TwoWire::beginTransmission(uint8_t address, uint8_t forced_start) {
	this->seq.addr = WIRE_ADDRESS(address);
	this->seq.flags = I2C_FLAG_WRITE;
	this->seq.buf->len = 0;
	this->seq_return = i2cTransferInProgress;
}

size_t TwoWire::write(uint8_t data) {
	return (this->write(&data, 1));
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	size_t			len;
	uint8_t			*b;

	if (this->seq.flags != I2C_FLAG_WRITE) {
		this->seq_return = i2cTransferDone;
		return (0);
	}
	if ((len = this->seq.buf->len) + quantity > this->_doubleBuffer_len) {
		this->seq_return = WIRE_ERORR_TRANSMISSION_LONG_I2C;
		return (0);
	}
	this->seq.buf->len = len + quantity;
	b = &this->seq.buf->data[len];
	len = 0;
	while (len < quantity) {
		b[len] = data[len];
		len++;
	}
	return (quantity);
}

size_t TwoWire::write(const char *data) {
	return (this->write((const uint8_t *)data, strlen(data)));
}

uint8_t TwoWire::transfer(uint8_t adress, void *b) {
	this->transfer(adress, b, strlen((char *)b));
}

uint8_t TwoWire::transfer(uint8_t adress, const char *b) {
	this->transfer(adress, (void *)b);
}

uint8_t TwoWire::transfer(uint8_t adress, void *b, uint16_t count) {
	I2C_TypeDef							*i2c;
	I2C_TransferReturn_TypeDef			tempos;
	uint32_t							timeout;
	I2C_TransferSeq_TypeDef				seq;

	seq = this->seq;
	this->seq.addr = WIRE_ADDRESS(adress);
	this->seq.flags = I2C_FLAG_WRITE;
	this->seq.buf->len = count;
	this->seq.buf->data = (uint8_t *)b;
	timeout = 0x1FFFF;
	i2c = this->_i2c_config->i2c;
	tempos = I2C_TransferInit(i2c, &this->seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer(i2c);
	this->seq = seq;
	if (tempos == i2cTransferDone)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	I2C_TypeDef							*i2c;
	I2C_TransferReturn_TypeDef			tempos;
	uint32_t							timeout;

	if ((tempos = this->seq_return) == WIRE_ERORR_TRANSMISSION_LONG_I2C)
		return (WIRE_ERORR_TRANSMISSION_LONG);
	if (tempos != i2cTransferInProgress || this->seq.flags != I2C_FLAG_WRITE)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	timeout = 0x1FFFF;
	i2c = this->_i2c_config->i2c;
	tempos = I2C_TransferInit(i2c, &this->seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer(i2c);
	if ((this->seq_return = tempos) == i2cTransferDone)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

uint8_t TwoWire::endTransmission(void) {
	return (this->endTransmission(true));
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
	return (this->requestFrom(address, quantity, true));
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
	I2C_TypeDef							*i2c;
	uint32_t							timeout;
	I2C_TransferReturn_TypeDef			tempos;

	if (quantity > WIRE_BUFFER_LENGTH_)
		quantity = WIRE_BUFFER_LENGTH_;
	this->seq.addr = WIRE_ADDRESS(address);
	this->seq.flags = I2C_FLAG_READ;
	this->seq.buf->len = quantity;
	timeout = 0x1FFFF;
	i2c = this->_i2c_config->i2c;
	tempos = I2C_TransferInit(i2c, &this->seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer(i2c);
	if (tempos != i2cTransferDone) {
		this->available_bytes = 0;
		return (0);
	}
	this->available_bytes = this->seq.buf->len;
	return (this->seq.buf->len);
}

uint8_t		TwoWire::available(void) {
	if (this->seq.flags != I2C_FLAG_READ)
		return (0);
	return (this->available_bytes);
}

uint8_t TwoWire::read(void) {
	uint8_t			len;

	if (this->seq.flags != I2C_FLAG_READ || (len = this->available_bytes) == 0)
		return (0);
	len = this->seq.buf->len - len;
	this->available_bytes--;
	return (this->seq.buf->data[len]);
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

/* Preinstantiate Objects */
TwoWire Wire = TwoWire();
