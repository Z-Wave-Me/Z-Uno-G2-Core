#include "Wire_private.h"

/* Public Constructors */
TwoWire::TwoWire(): init_freq(I2C_FREQ_STANDARD_MAX), seq_return(i2cTransferDone), available_bytes(0), seq( {0, 0, &this->seq_buffer[0], 0, 0, 0}), scl_pin(SCL), sda_pin(SDA) {

}

/* Public Methods */
void TwoWire::begin(void) {
	begin(0, this->scl_pin, this->sda_pin);//0 - master
}

void TwoWire::begin(uint8_t scl, uint8_t sda) {
	this->scl_pin = scl;
	this->sda_pin = sda;
	begin(0, scl, sda);//0 - master
}

void TwoWire::begin(uint8_t address) {
	begin(address, this->scl_pin, this->sda_pin);
}

void TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda) {
	I2C_Init_TypeDef			init_i2c;

	end();
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_I2C0, true);
	/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(scl, GPIOMODE_OUTPUT_OPENDRAINPUP);
	pinMode(sda, GPIOMODE_OUTPUT_OPENDRAINPUP);
	digitalWrite(scl, HIGH);
	digitalWrite(sda, HIGH);
	init_i2c.enable = true;// Set emlib init parameters
	init_i2c.master = (address == 0) ? true : false;
	init_i2c.freq = this->init_freq;
	init_i2c.refFreq = 0;
	init_i2c.clhr = i2cClockHLRStandard;
	I2C0->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	scl = getLocation(WIRE_LOCATION, WIRE_LOCATION_SIZE, scl);
	scl = (scl == 0 ) ? WIRE_LOCATION_SIZE - 1 : scl - 1;
	I2C0->ROUTELOC0 = (getLocation(&WIRE_LOCATION[0], WIRE_LOCATION_SIZE, sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (scl << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	I2C0->SADDR =  WIRE_ADDRESS(address);
	I2C0->SADDRMASK = _I2C_SADDRMASK_MASK_DEFAULT;
	I2C_Init(I2C0, &init_i2c);
}

void TwoWire::beginTransmission(uint8_t address) {
	beginTransmission(address, false);
}

void TwoWire::beginTransmission(uint8_t address, uint8_t forced_start) {
	this->seq.addr = WIRE_ADDRESS(address);
	this->seq.flags = I2C_FLAG_WRITE;
	this->seq.buf->len = 0;
	this->seq_return = i2cTransferInProgress;
}

size_t TwoWire::write(uint8_t data) {
	return (write(&data, 1));
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	size_t			len;
	uint8_t			*b;

	if (this->seq.flags != I2C_FLAG_WRITE) {
		this->seq_return = i2cTransferDone;
		return (0);
	}
	if ((len = this->seq.buf->len) + quantity > WIRE_BUFFER_LENGTH) {
		this->seq_return = WIRE_ERORR_TRANSMISSION_LONG_I2C;
		return (0);
	}
	this->seq.buf->len = len + quantity;
	b = &this->seq_buffer[len];
	len = 0;
	while (len < quantity) {
		b[len] = data[len];
		len++;
	}
	return (quantity);
}

size_t TwoWire::write(const char *data) {
	return (write((const uint8_t *)data, strlen(data)));
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	I2C_TransferReturn_TypeDef			tempos;
	uint32_t							timeout;

	if ((tempos = this->seq_return) == WIRE_ERORR_TRANSMISSION_LONG_I2C)
		return (WIRE_ERORR_TRANSMISSION_LONG);
	if (tempos != i2cTransferInProgress || this->seq.flags != I2C_FLAG_WRITE)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	timeout = 0x1FFFF;
	tempos = I2C_TransferInit(I2C0, &this->seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer(I2C0);
	if ((this->seq_return = tempos) == i2cTransferDone)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

uint8_t TwoWire::endTransmission(void) {
	return (endTransmission(true));
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
	return (requestFrom(address, quantity, true));
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
	uint32_t							timeout;
	I2C_TransferReturn_TypeDef			tempos;

	if (quantity > WIRE_BUFFER_LENGTH_)
		quantity = WIRE_BUFFER_LENGTH_;
	this->seq.addr = WIRE_ADDRESS(address);
	this->seq.flags = I2C_FLAG_READ;
	this->seq.buf->len = quantity;
	timeout = 0x1FFFF;
	tempos = I2C_TransferInit(I2C0, &this->seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer(I2C0);
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
	return (this->seq_buffer[len]);
}

void TwoWire::enableTS(uint8_t on_off) {
// FIXME: не знаю как менять и надо ли менять
}

void TwoWire::setClock(uint32_t clock) {
	this->init_freq = clock;
}

void TwoWire::end(void) {
	I2C_Reset(I2C0);
}

/* Private Methods */

/* Preinstantiate Objects */
TwoWire Wire = TwoWire();
