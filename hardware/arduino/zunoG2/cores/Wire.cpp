#include "Wire_private.h"


/* Public Constructors */
TwoWire::TwoWire()
{
	init_freq = I2C_FREQ_STANDARD_MAX;
	seq_return = i2cTransferDone;
	status = 0;
	available_bytes = 0;
	seq = {0, 0, TwoWire::seq_buffer, 0, 0, 0};
}

/* Public Methods */
void		TwoWire::begin(void)
{
	begin(0);
}

void		TwoWire::begin(uint8_t address)
{
	I2C_Init_TypeDef			init_i2c;

	if ((status & WIRE_STATUS_BEGIN) != 0)// Check it may have already initializedи
		return ;
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_I2C0, true);
	/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(WIRE_PIN_SCL, GPIOMODE_OUTPUT_OPENDRAINPUP);
	pinMode(WIRE_PIN_SDA, GPIOMODE_OUTPUT_OPENDRAINPUP);
	digitalWrite(WIRE_PIN_SCL, HIGH);
	digitalWrite(WIRE_PIN_SDA, HIGH);
	I2C0->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	I2C0->ROUTELOC0 = (0 << _I2C_ROUTELOC0_SDALOC_SHIFT) | (0 << _I2C_ROUTELOC0_SCLLOC_SHIFT);//до ремапинга с помощью локаций
	I2C0->SADDR =  WIRE_ADDRESS(address);
	I2C0->SADDRMASK = _I2C_SADDRMASK_MASK_DEFAULT;
	init_i2c.enable = true;// Set emlib init parameters
	init_i2c.master = (address == 0) ? true : false;
	init_i2c.freq = init_freq;
	init_i2c.refFreq = 0;
	init_i2c.clhr = i2cClockHLRStandard;
	I2C_Init(I2C0, &init_i2c);
	status = WIRE_STATUS_BEGIN;
}

void		TwoWire::beginTransmission(uint8_t address)
{
	beginTransmission(address, false);
}

void		TwoWire::beginTransmission(uint8_t address, uint8_t forced_start)
{
	seq.addr = WIRE_ADDRESS(address);
	seq.flags = I2C_FLAG_WRITE;
	seq.buf->len = 0;
	seq_return = i2cTransferInProgress;
}

size_t TwoWire::write(uint8_t data)
{
	return (write(&data, 1));
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	size_t			len;
	uint8_t			*b;

	if (seq.flags != I2C_FLAG_WRITE)
	{
		seq_return = i2cTransferDone;
		return (0);
	}
	if ((len = seq.buf->len) + quantity > WIRE_BUFFER_LENGTH)
	{
		seq_return = WIRE_ERORR_TRANSMISSION_LONG_I2C;
		return (0);
	}
	seq.buf->len = len + quantity;
	b = &seq_buffer[len];
	len = 0;
	while (len < quantity)
	{
		b[len] = data[len];
		len++;
	}
	return (quantity);
}

size_t TwoWire::write(const char *data)
{
	return (write((const uint8_t *)data, strlen(data)));
}

uint8_t		TwoWire::endTransmission(uint8_t sendStop)
{
	I2C_TransferReturn_TypeDef			tempos;
	uint32_t							timeout;

	if ((tempos = seq_return) == WIRE_ERORR_TRANSMISSION_LONG_I2C)
		return (WIRE_ERORR_TRANSMISSION_LONG);
	if (tempos != i2cTransferInProgress || seq.flags != I2C_FLAG_WRITE || (status & WIRE_STATUS_BEGIN) == 0)
		return (WIRE_ERORR_TRANSMISSION_OTHER);
	timeout = 0x1FFFF;
	tempos = I2C_TransferInit(&seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer();
	if ((seq_return = tempos) == i2cTransferDone)
		return (WIRE_ERORR_TRANSMISSION_SUCCESS);
	return (WIRE_ERORR_TRANSMISSION_OTHER);
}

uint8_t		TwoWire::endTransmission(void)
{
	return (endTransmission(true));
}

uint8_t		TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	return (requestFrom(address, quantity, true));
}

uint8_t		TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
	uint32_t							timeout;
	I2C_TransferReturn_TypeDef			tempos;

	if (quantity > WIRE_BUFFER_LENGTH)
		quantity = WIRE_BUFFER_LENGTH;
	seq.addr = WIRE_ADDRESS(address);
	seq.flags = I2C_FLAG_READ;
	seq.buf->len = quantity;
	if ((status & WIRE_STATUS_BEGIN) == 0)
	{
		available_bytes = 0;
		return (0);
	}
	timeout = 0x1FFFF;
	tempos = I2C_TransferInit(&seq);
	while (tempos == i2cTransferInProgress && timeout-- != 0)
		tempos = I2C_Transfer();
	if (tempos != i2cTransferDone)
	{
		available_bytes = 0;
		return (0);
	}
	available_bytes = seq.buf->len;
	return (seq.buf->len);
}

uint8_t		TwoWire::available(void)
{
	if (seq.flags != I2C_FLAG_READ)
		return (0);
	return (available_bytes);
}

uint8_t		TwoWire::read(void)
{
	uint8_t			len;

	if (seq.flags != I2C_FLAG_READ || (len = available_bytes) == 0)
		return (0);
	len = seq.buf->len - len;
	available_bytes--;
	return (seq_buffer[len]);
}

void		TwoWire::enableTS(uint8_t on_off)
{
}

void		TwoWire::setClock(uint32_t clock)
{
	init_freq = clock;
}

/* Preinstantiate Objects */
TwoWire Wire = TwoWire();
