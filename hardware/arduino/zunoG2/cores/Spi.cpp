#include "Spi_private.h"


/* Public Constructors */
SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode): clock(clock), bitOrder(bitOrder), dataMode(dataMode) {
//baudrate - specified as zero in order to apply settings to USART at least once
}

SPISettings::SPISettings(void) {
	SPISettings(1000000, MSBFIRST, SPI_MODE0);
}

//----------------------------------------------------------------
/* Public Constructors */
SPIClass::SPIClass(void): sck_pin(SCK), miso_pin(MISO), mosi_pin(MOSI), ss_pin(SS), init_spi({usartEnable, 0, 0, usartDatabits8, true, MSBFIRST, SPI_MODE0, false, usartPrsRxCh0, false, false, 0, 0}) {

}

/* Public Methods */
void SPIClass::begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss) {
	this->sck_pin = sck;
	this->miso_pin = miso;
	this->mosi_pin = mosi;
	this->ss_pin = ss;
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(SPI_BUS_CLOCK, true);
	pinMode(sck, _GPIO_P_MODEL_MODE0_PUSHPULL);
	pinMode(miso, _GPIO_P_MODEL_MODE0_INPUT);
	pinMode(mosi, _GPIO_P_MODEL_MODE0_PUSHPULL);
	pinMode(ss, _GPIO_P_MODEL_MODE0_PUSHPULL);
}

void SPIClass::begin(void) {
	begin(this->sck_pin, this->miso_pin, this->mosi_pin, this->ss_pin);
}

void SPIClass::beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode) {
	if (clock != this->init_spi.baudrate || bitOrder != this->init_spi.msbf || dataMode != this->init_spi.clockMode)
	{//If the settings have not changed, why update them for USART
		this->init_spi.msbf = bitOrder;
		this->init_spi.baudrate = clock;
		this->init_spi.clockMode = dataMode;
		USART_InitSync(SPI_BUS, &(this->init_spi));
		SPI_BUS->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
		SPI_BUS->ROUTELOC0 &= ~(_USART_ROUTELOC0_TXLOC_MASK | _USART_ROUTELOC0_RXLOC_MASK | _USART_ROUTELOC0_CLKLOC_MASK);
		#if SPI_BUS_NOMBER == 0 || SPI_BUS_NOMBER == 1
			uint32_t                    lmosi;
			uint32_t					lmiso;
			uint32_t					lsck;
			lmosi = getLocation(SPI_LOCATION, SPI_LOCATION_SIZE, this->mosi_pin);
			lmiso = (getLocation(SPI_LOCATION, SPI_LOCATION_SIZE, this->miso_pin) + 1)%SPI_LOCATION_SIZE;
			lsck =  (getLocation(SPI_LOCATION, SPI_LOCATION_SIZE, this->sck_pin) + 2)%SPI_LOCATION_SIZE;
			SPI_BUS->ROUTELOC0 |= (lmosi << _USART_ROUTELOC0_TXLOC_SHIFT) | (lmiso << _USART_ROUTELOC0_RXLOC_SHIFT) | (lsck << _USART_ROUTELOC0_CLKLOC_SHIFT);
		#elif SPI_BUS_NOMBER == 2
			//PA5 = 5 real
			SPI_BUS->ROUTELOC0 |= 
			 (((((getRealPort(this->mosi_pin) << 4) | getRealPin(this->mosi_pin)) == 5) ? 0 : getLocation(&SPI_LOCATION[0], SPI_LOCATION_SIZE, this->mosi_pin) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT)
			| (((((getRealPort(this->miso_pin) << 4) | getRealPin(this->miso_pin)) == 5) ? 31 : getLocation(&SPI_LOCATION[0], SPI_LOCATION_SIZE, this->miso_pin) + 13) << _USART_ROUTELOC0_RXLOC_SHIFT)
			| (((((getRealPort(this->sck_pin) << 4) | getRealPin(this->sck_pin)) == 5) ? 30 : getLocation(&SPI_LOCATION[0], SPI_LOCATION_SIZE, this->sck_pin) + 12) << _USART_ROUTELOC0_CLKLOC_SHIFT);
		#else
			#define SPI_BUS_NOMBER		Incorrectly defined!
		#endif
	}
	digitalWrite(ss_pin, LOW);//We inform slave about receiving data
}

void SPIClass::beginTransaction(SPISettings *spi_setings) {
	beginTransaction(spi_setings->clock, spi_setings->bitOrder, spi_setings->dataMode);
}

void SPIClass::beginTransaction(void) {
	beginTransaction(1000000, MSBFIRST, SPI_MODE0);
}

uint8_t SPIClass::transfer(uint8_t data) {
	return (USART_SpiTransfer(SPI_BUS, data));
}

uint16_t SPIClass::transfer16(uint16_t data) {
	return((transfer(data >> 8) << 8) | transfer((uint8_t)data));
}

void SPIClass::transfer(void *b, size_t count) {
	void			*e;

	e = (char *)b + count;
	while (b < e)
	{
		transfer(((uint8_t *)b)[0]);
		b = (char *)b + 1;
	}
}

void SPIClass::transfer(void *b) {
	transfer(b, strlen((char *)b));
}

void SPIClass::transfer(const char *b) {
	transfer((void *)b, strlen(b));
}


void SPIClass::endTransaction(void) {
	digitalWrite(ss_pin, HIGH);//We inform slave to terminate data acquisition
}

void SPIClass::end(void) {
	USART_Reset(SPI_BUS);
}


/* Private Methods */


/* Preinstantiate Objects */
SPIClass SPI = SPIClass();