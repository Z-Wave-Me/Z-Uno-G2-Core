#include "Wire_private.h"

const uint8_t		TwoWire::wire_location[]={
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
	0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
	0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
	0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
};


/* Public Constructors */
TwoWire::TwoWire(): init_freq(I2C_FREQ_STANDARD_MAX), seq_return(i2cTransferDone), status(0), available_bytes(0), seq( {0, 0, TwoWire::seq_buffer, 0, 0, 0})
{
	scl_pin = WIRE_PIN_SCL;
	sda_pin = WIRE_PIN_SDA;
}

/* Public Methods */
void		TwoWire::begin(void)
{
	begin(0, scl_pin, sda_pin);//0 - master
}

void		TwoWire::begin(uint8_t scl, uint8_t sda)
{
	scl_pin = scl;
	sda_pin = sda;
	begin(0, scl, sda);//0 - master
}

void		TwoWire::begin(uint8_t address)
{
	begin(address, scl_pin, sda_pin);
}

void		TwoWire::begin(uint8_t address, uint8_t scl, uint8_t sda)
{
	I2C_Init_TypeDef			init_i2c;

	if ((status & WIRE_STATUS_BEGIN) != 0)// Check it may have already initializedи
		return ;
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_I2C0, true);
	/* Output value must be set to 1 to not drive lines low. Set SCL first, to ensure it is high before changing SDA. */
	pinMode(scl, GPIOMODE_OUTPUT_OPENDRAINPUP);
	pinMode(sda, GPIOMODE_OUTPUT_OPENDRAINPUP);
	digitalWrite(scl, HIGH);
	digitalWrite(sda, HIGH);
	init_i2c.enable = true;// Set emlib init parameters
	init_i2c.master = (address == 0) ? true : false;
	init_i2c.freq = init_freq;
	init_i2c.refFreq = 0;
	init_i2c.clhr = i2cClockHLRStandard;
	I2C0->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	scl = _get_location(scl);
	scl = (scl == 0 ) ? sizeof(wire_location) - 1 : scl - 1;
	I2C0->ROUTELOC0 = (_get_location(sda) << _I2C_ROUTELOC0_SDALOC_SHIFT) | (scl << _I2C_ROUTELOC0_SCLLOC_SHIFT);//до ремапинга с помощью локаций
	I2C0->SADDR =  WIRE_ADDRESS(address);
	I2C0->SADDRMASK = _I2C_SADDRMASK_MASK_DEFAULT;
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

/* Private Methods */
uint8_t		TwoWire::_get_location(uint8_t pin)// Get the location for the SDA, it is interconnected with the location of the SCL
{
	uint8_t				i;
	uint8_t				out;
	const uint8_t		*s_location;

	i = 0;
	out = 0;
	pin = (getRealPort(pin) << 4) | getRealPin(pin);
	s_location = &wire_location[0];
	while (i < sizeof(wire_location))
	{
		if (s_location[i] == pin)
			return (i);
		i++;
	}
	return (out);
}

/* Preinstantiate Objects */
TwoWire Wire = TwoWire();
