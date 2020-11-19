#include "Arduino.h"
#include "ZDma.h"
#include "Spi.h"

/* Public Constructors */
SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode): clock(clock), bitOrder(bitOrder), dataMode(dataMode) {
//baudrate - specified as zero in order to apply settings to USART at least once
}

SPISettings::SPISettings(void) {
	SPISettings(1000000, MSBFIRST, SPI_MODE0);
}

#define SPI_MIN_WRITE_ZDMA			2
#define SPI_UNIQ_ZDMA_WRITE			((size_t)&this->_baudrate)
#define SPI_UNIQ_ZDMA_READ			((size_t)&this->_ss_pin)


/* Constants */
const ZunoSpiUsartTypeConfig_t SPIClass::_configTable0 = 
{
	.usart = USART0,
	.lpLock = &gSyncUSART0,
	.dmaSignalWrite = zdmaPeripheralSignal_USART0_TXBL,
	.dmaSignalRead = zdmaPeripheralSignal_USART0_RXDATAV,
	.bus_clock = cmuClock_USART0,
	.sck = SCK,
	.miso = MISO,
	.mosi = MOSI,
	.ss = SS
};

const ZunoSpiUsartTypeConfig_t SPIClass::_configTable1 = 
{
	.usart = USART1,
	.lpLock = &gSyncUSART1,
	.dmaSignalWrite = zdmaPeripheralSignal_USART1_TXBL,
	.dmaSignalRead = zdmaPeripheralSignal_USART1_RXDATAV,
	.bus_clock = cmuClock_USART1,
	.sck = SCK,
	.miso = MISO,
	.mosi = MOSI,
	.ss = SS
};

const ZunoSpiUsartTypeConfig_t SPIClass::_configTable2 = 
{
	.usart = USART2,
	.lpLock = &gSyncUSART2,
	.dmaSignalWrite = zdmaPeripheralSignal_USART2_TXBL,
	.dmaSignalRead = zdmaPeripheralSignal_USART2_RXDATAV,
	.bus_clock = cmuClock_USART2,
	.sck = SCK2,
	.miso = MISO2,
	.mosi = MOSI2,
	.ss = SS2
};

const USART_InitSync_TypeDef SPIClass::_initSpi = SPI_INIT_DEFAULT;//USART_INITSYNC_DEFAULT;


/* Public Constructors */
SPIClass::SPIClass(uint8_t numberConfig){
#if (ZUNO_ZERO_BSS != true)
	:_baudrate(0), _lpKey(0)
#endif
	const ZunoSpiUsartTypeConfig_t				*config;

	switch (numberConfig) {
		case 0:
			config = &this->_configTable0;
			break ;
		case 2:
			config = &this->_configTable2;
			break ;
		default:
			config = &this->_configTable1;
			break ;
	}
	this->_config = config;
}

/* Public Methods */
ZunoError_t SPIClass::begin(void) {
	const ZunoSpiUsartTypeConfig_t				*config;

	config = this->_config;
	return (begin(config->sck, config->miso, config->mosi, config->ss));
}

ZunoError_t SPIClass::begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss) {
	const ZunoSpiUsartTypeConfig_t		*config;
	ZunoError_t							ret;
	const uint8_t						*location;
	USART_TypeDef						*usart;
	size_t								routeLocation;

	if (sck > ZUNO_PIN_LAST_INDEX || miso > ZUNO_PIN_LAST_INDEX || mosi > ZUNO_PIN_LAST_INDEX || ss > ZUNO_PIN_LAST_INDEX )
		return (ZunoErrorInvalidPin);
	config = this->_config;
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterSpi, this->_init, (size_t)this, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	pinMode(sck, OUTPUT);//_GPIO_P_MODEL_MODE0_PUSHPULL
	pinMode(miso, INPUT);//_GPIO_P_MODEL_MODE0_INPUT
	pinMode(mosi, OUTPUT);
	pinMode(ss, OUTPUT);
	usart = config->usart;
	this->_ss_pin = ss;
	if (usart == USART2) {
		location = &g_loc_pf0_pf1_pf3_pf7[0];
		routeLocation = 
		(((((getRealPort(mosi) << 4) | getRealPin(mosi)) == 5) ? 0 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), mosi) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT)
		| (((((getRealPort(miso) << 4) | getRealPin(miso)) == 5) ? 31 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), miso) + 13) << _USART_ROUTELOC0_RXLOC_SHIFT)
		| (((((getRealPort(sck) << 4) | getRealPin(sck)) == 5) ? 30 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), sck) + 12) << _USART_ROUTELOC0_CLKLOC_SHIFT);
	}
	else {
		location = &g_loc_pa0_pf7_all[0];
		routeLocation = 
		((getLocation(location, sizeof(g_loc_pa0_pf7_all), mosi)) << _USART_ROUTELOC0_TXLOC_SHIFT)
		| (((getLocation(location, sizeof(g_loc_pa0_pf7_all), miso) - 1) % sizeof(g_loc_pa0_pf7_all)) << _USART_ROUTELOC0_RXLOC_SHIFT)
		| ((getLocation(location, sizeof(g_loc_pa0_pf7_all), sck) - 2) % sizeof(g_loc_pa0_pf7_all) << _USART_ROUTELOC0_CLKLOC_SHIFT);
	}
	usart->ROUTELOC0 = routeLocation;
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ZunoErrorOk);
}

void SPIClass::beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode) {
	USART_TypeDef						*usart;
	const ZunoSpiUsartTypeConfig_t		*config;

	config = this->_config;
	if (zunoSyncLockRead(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	usart = config->usart;
	usart->CTRL = (usart->CTRL & ~(USART_CTRL_MSBF | usartClockMode0 | usartClockMode1 | usartClockMode2 | usartClockMode3)) | (bitOrder ? USART_CTRL_MSBF : 0) | dataMode;
	if (clock != this->_baudrate) {
		this->_baudrate = clock;
		USART_BaudrateSyncSet(usart, 0, clock);
	}
	digitalWrite(this->_ss_pin, LOW);//We inform slave about receiving data
	zunoSyncReleseRead(config->lpLock, SyncMasterSpi, &this->_lpKey);
}
void SPIClass::endTransaction(void) {
	const ZunoSpiUsartTypeConfig_t		*config;

	config = this->_config;
	if (zunoSyncLockRead(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	digitalWrite(this->_ss_pin, HIGH);//We inform slave to terminate data acquisition
	zunoSyncReleseRead(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

/* Private Methods */
size_t SPIClass::_transferDate(size_t data, size_t bFlags) {
	size_t								out;
	const ZunoSpiUsartTypeConfig_t		*config;
	USART_TypeDef						*usart;

	config = this->_config;
	if (zunoSyncLockRead(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return (0);
	usart = config->usart;
	out = USART_SpiTransfer(usart, (uint8_t)data);
	if ((bFlags & SPI_FLAGS_16BIT) != 0)
		out = out | (USART_SpiTransfer(usart, (uint8_t)(data >> 8)) << 8);
	zunoSyncReleseRead(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (out);
}

ZunoError_t SPIClass::_transferStrlen(void *b, size_t bFlags) {
	return (this->_transfer(b, strlen((char *)b), bFlags));
}

ZunoError_t SPIClass::_transfer(void *b, size_t count, size_t bFlags) {
	const ZunoSpiUsartTypeConfig_t		*config;
	USART_TypeDef						*usart;
	void								*e;
	ZunoError_t							ret;
	size_t								out;

	config = this->_config;
	if ((ret = zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	usart = config->usart;
	if (count <= SPI_MIN_WRITE_ZDMA)
	{
		e = (char *)b + count;
		while (b < e) {
			out = USART_SpiTransfer(usart, ((uint8_t *)b)[0]);
			if ((bFlags & SPI_FLAGS_CONST) == 0)
				((uint8_t *)b)[0] = (uint8_t)out;
			b = (char *)b + 1;
		}
	}
	else {
		usart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
		if ((bFlags & SPI_FLAGS_CONST) != 0 || ((ret = ZDMA.toPeripheralMemory(SPI_UNIQ_ZDMA_READ, config->dmaSignalRead, b, (void*)&(usart->RXDATA), count, zdmaData8)) == ZunoErrorOk)) {
			if ((ret = ZDMA.toMemoryPeripheral(SPI_UNIQ_ZDMA_WRITE, config->dmaSignalWrite, (void*)&(usart->TXDATA), b, count, zdmaData8)) == ZunoErrorOk) {
				ZDMA.waitTransfer(SPI_UNIQ_ZDMA_WRITE);
				while (!(usart->STATUS & USART_STATUS_TXC))//Waiting for the last byte to go before we finish the transfer protocol
					__NOP();
			}
			ZDMA.stopTransfer(SPI_UNIQ_ZDMA_READ, true);
		}
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ret);
}

ZunoError_t SPIClass::_init(size_t param) {
	SPIClass							*spi;
	const ZunoSpiUsartTypeConfig_t		*config;
	USART_TypeDef						*usart;
	

	spi = (SPIClass *)param;
	config = spi->_config;
	CMU_ClockEnable(config->bus_clock, true);
	usart = config->usart;
	USART_InitSync(usart, &spi->_initSpi);
	usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
	return (ZunoErrorOk);
}

void SPIClass::_deInit(size_t param) {
	SPIClass							*spi;
	
	spi = (SPIClass *)param;
	USART_Reset(spi->_config->usart);
}


/* Preinstantiate Objects */
SPIClass SPI = SPIClass(1);