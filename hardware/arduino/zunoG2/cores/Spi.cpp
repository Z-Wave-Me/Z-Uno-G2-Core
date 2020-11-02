#include "Arduino.h"
#include "ZDma.h"
#include "Spi_define.h"
#include "Spi_private.h"

static const ZunoSpiUsartTypeConfig_t usart0_config = {USART0, zdmaPeripheralSignal_USART0_TXBL, cmuClock_USART0, SCK, MISO, MOSI, SS};
static const ZunoSpiUsartTypeConfig_t usart1_config = {USART1, zdmaPeripheralSignal_USART1_TXBL, cmuClock_USART1, SCK, MISO, MOSI, SS};
static const ZunoSpiUsartTypeConfig_t usart2_config = {USART2, zdmaPeripheralSignal_USART2_TXBL, cmuClock_USART2, SCK2, MISO2, MOSI2, SS2};

/* Public Constructors */
SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode): clock(clock), bitOrder(bitOrder), dataMode(dataMode) {
//baudrate - specified as zero in order to apply settings to USART at least once
}

SPISettings::SPISettings(void) {
	SPISettings(1000000, MSBFIRST, SPI_MODE0);
}

//----------------------------------------------------------------
/* Public Constructors */
SPIClass::SPIClass(USART_TypeDef *usart): clock(0), bitOrder(MSBFIRST), dataMode(SPI_MODE0) {
	if (usart == USART0)
		this->usart_config = &usart0_config;
	else if (usart == USART2)
		this->usart_config = &usart2_config;
	else
		this->usart_config = &usart1_config;
}

SPIClass::SPIClass(void): clock(0), bitOrder(MSBFIRST), dataMode(SPI_MODE0) {
	this->usart_config = &usart1_config;
}

/* Public Methods */
void SPIClass::begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss) {
	this->sck_pin = sck;
	this->miso_pin = miso;
	this->mosi_pin = mosi;
	this->ss_pin = ss;
	CMU_ClockEnable(this->usart_config->bus_clock, true);
	pinMode(sck, OUTPUT);//_GPIO_P_MODEL_MODE0_PUSHPULL
	pinMode(miso, INPUT);//_GPIO_P_MODEL_MODE0_INPUT
	pinMode(mosi, OUTPUT);
	pinMode(ss, OUTPUT);
}

void SPIClass::begin(void) {
	begin(this->usart_config->sck, this->usart_config->miso, this->usart_config->mosi, this->usart_config->ss);
}

void SPIClass::beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode) {
	USART_InitSync_TypeDef				init_spi;
	const ZunoSpiUsartTypeConfig_t		*usart_config;
	USART_TypeDef						*usart;
	const uint8_t						*location;

	if (clock != this->clock || bitOrder != this->bitOrder || dataMode != this->dataMode)
	{//If the settings have not changed, why update them for USART
		this->clock = clock;
		this->bitOrder = bitOrder;
		this->dataMode = dataMode;
		init_spi = SPI_INIT_DEFAULT;
		init_spi.msbf = bitOrder;
		init_spi.baudrate = clock;
		init_spi.clockMode = dataMode;
		usart_config = this->usart_config;
		usart = usart_config->usart;
		USART_InitSync(usart, &init_spi);
		if (usart == USART2) {
			location = &g_loc_pf0_pf1_pf3_pf7[0];
			usart->ROUTELOC0 = 
			(((((getRealPort(this->mosi_pin) << 4) | getRealPin(this->mosi_pin)) == 5) ? 0 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), this->mosi_pin) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT)
			| (((((getRealPort(this->miso_pin) << 4) | getRealPin(this->miso_pin)) == 5) ? 31 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), this->miso_pin) + 13) << _USART_ROUTELOC0_RXLOC_SHIFT)
			| (((((getRealPort(this->sck_pin) << 4) | getRealPin(this->sck_pin)) == 5) ? 30 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), this->sck_pin) + 12) << _USART_ROUTELOC0_CLKLOC_SHIFT);
		}
		else {
			location = &g_loc_pa0_pf7_all[0];
			usart->ROUTELOC0 = 
			((getLocation(location, sizeof(g_loc_pa0_pf7_all), this->mosi_pin)) << _USART_ROUTELOC0_TXLOC_SHIFT)
			| (((getLocation(location, sizeof(g_loc_pa0_pf7_all), this->miso_pin) - 1) % sizeof(g_loc_pa0_pf7_all)) << _USART_ROUTELOC0_RXLOC_SHIFT)
			| ((getLocation(location, sizeof(g_loc_pa0_pf7_all), this->sck_pin) - 2) % sizeof(g_loc_pa0_pf7_all) << _USART_ROUTELOC0_CLKLOC_SHIFT);
		}
		usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
	}
	digitalWrite(this->ss_pin, LOW);//We inform slave about receiving data
}

void SPIClass::beginTransaction(SPISettings *spi_setings) {
	beginTransaction(spi_setings->clock, spi_setings->bitOrder, spi_setings->dataMode);
}

void SPIClass::beginTransaction(void) {
	beginTransaction(1000000, MSBFIRST, SPI_MODE0);
}

uint8_t SPIClass::transfer(uint8_t data) {
	return (USART_SpiTransfer(this->usart_config->usart, data));
}

uint16_t SPIClass::transfer16(uint16_t data) {
	return((transfer(data >> 8) << 8) | transfer((uint8_t)data));
}

void SPIClass::transfer(void *b, size_t count) {
	uint32_t					clock;
	USART_TypeDef				*usart;
	void						*e;
	size_t						uniqId;

	usart = this->usart_config->usart;
	uniqId = (size_t)&this->clock;
	if (ZDMA.toMemoryPeripheral(uniqId, this->usart_config->dmaSignal, (void*)&(usart->TXDATA), b, count, zdmaData8) == ZunoErrorOk) {
		clock = this->clock / 1000;
		if (clock != 0)
			clock = count * 8 / clock;
		delay((clock == 0)? 1 : clock);
		while (ZDMA.isProcessing(uniqId) == true)
			__NOP();
		while (!(usart->STATUS & USART_STATUS_TXC))//Waiting for the last byte to go before we finish the transfer protocol
			__NOP();
	}
	else {
		e = (char *)b + count;
		while (b < e) {
			transfer(((uint8_t *)b)[0]);
			b = (char *)b + 1;
		}
	}
}

void SPIClass::transfer(void *b) {
	transfer(b, strlen((char *)b));
}

void SPIClass::transfer(const char *b) {
	transfer((void *)b, strlen(b));
}


void SPIClass::endTransaction(void) {
	digitalWrite(this->ss_pin, HIGH);//We inform slave to terminate data acquisition
}

void SPIClass::end(void) {
	USART_Reset(this->usart_config->usart);
}


/* Private Methods */


/* Preinstantiate Objects */
SPIClass SPI = SPIClass();