#include "Arduino.h"
#include "SPI.h"

/*
	usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits16;
	USART_SpiTransfer16
	usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits8;
*/
static uint16_t USART_SpiTransfer16(USART_TypeDef *usart, uint16_t data)
{
	while (!(usart->STATUS & USART_STATUS_TXBL))
		;
	usart->TXDOUBLE = (uint32_t)data;
	while (!(usart->STATUS & USART_STATUS_TXC))
		;
	return (uint16_t)usart->RXDOUBLE;
}

/* Public Constructors */
SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode): clock(clock), bitOrder(bitOrder), dataMode(dataMode) {
//baudrate - specified as zero in order to apply settings to USART at least once
}

SPISettings::SPISettings(void) {
	SPISettings(4000000, MSBFIRST, SPI_MODE0);
}

#define SPI_MIN_WRITE_ZDMA			2


/* Constants */
const USART_InitSync_TypeDef SPIClass::_initSpi = SPI_INIT_DEFAULT;//USART_INITSYNC_DEFAULT;


/* Public Constructors */
SPIClass::SPIClass(ZunoSpiNumConfig_t numberConfig): _baudrate(0), _slave(0x0), _lpKey(false) {
	const ZunoSpiConfig_t				*config;

	switch (numberConfig) {
		#if USART_COUNT >= 1
		case ZunoSpiUsart0:
			static const ZunoSpiConfig_t					_configTableUsart0 = 
			{
				.usart = USART0,
				.lpLock = &gSyncUSART0,
				.IRQHandler = SPIClass::_USART0_IRQHandler,
				.dmaSignalWrite = ldmaPeripheralSignal_USART0_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART0_RXDATAV,
				.bus_clock = cmuClock_USART0,
				.sck = SCK,
				.miso = MISO,
				.mosi = MOSI,
				.subType = ZUNO_IRQVEC_USART0_RX,
				.irqType = USART0_RX_IRQn,
				.fd = 0x0,
				.type = ZunoSpiTypeUsart,
			};

			config = &_configTableUsart0;
			break ;
		#endif
		#if USART_COUNT >= 2
		case ZunoSpiUsart1:
			static const ZunoSpiConfig_t					_configTableUsart1 = 
			{
				.usart = USART1,
				.lpLock = &gSyncUSART1,
				.IRQHandler = SPIClass::_USART1_IRQHandler,
				.dmaSignalWrite = ldmaPeripheralSignal_USART1_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART1_RXDATAV,
				.bus_clock = cmuClock_USART1,
				.sck = SCK,
				.miso = MISO,
				.mosi = MOSI,
				.subType = ZUNO_IRQVEC_USART1_RX,
				.irqType = USART1_RX_IRQn,
				.fd = 0x1,
				.type = ZunoSpiTypeUsart,
			};
			config = &_configTableUsart1;
			break ;
		#endif
		#if USART_COUNT >= 3
		case ZunoSpiUsart2:
			static const ZunoSpiConfig_t					_configTableUsart2 = 
			{
				.usart = USART2,
				.lpLock = &gSyncUSART2,
				.IRQHandler = SPIClass::_USART2_IRQHandler,
				.dmaSignalWrite = ldmaPeripheralSignal_USART2_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART2_RXDATAV,
				.bus_clock = cmuClock_USART2,
				.sck = SCK2,
				.miso = MISO2,
				.mosi = MOSI2,
				.subType = ZUNO_IRQVEC_USART2_RX,
				.irqType = USART2_RX_IRQn,
				.fd = 0x2,
				.type = ZunoSpiTypeUsart,
			};
			config = &_configTableUsart2;
			break ;
		#endif
		case ZunoSpiLast:
			while (true)
				__NOP();
			break ;
	}
	this->_config = config;
}

/* Public Methods */
void SPIClass::begin(void) {
	const ZunoSpiConfig_t				*config;

	config = this->_config;
	this->begin(config->sck, config->miso, config->mosi, UNKNOWN_PIN);
}

size_t SPIClass::write(const uint8_t *data, size_t quantity) {
	const ZunoSpiConfig_t		*config;
	ZunoSpiSlave_t						*slave;
	size_t								len;
	uint8_t								*b;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return (0x0);
	if ((slave = this->_slave)!= 0x0) {
		if ((len = slave->count) + quantity > slave->len) {
			quantity = 0x0;
		}
		else {
			slave->count = len + quantity;
			b = &slave->buffer[len];
			len = 0;
			while (len < quantity) {
				b[len] = data[len];
				len++;
			}
		}
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (quantity);
}

void SPIClass::onRequest(void (*function)(void)) {
	const ZunoSpiConfig_t		*config;
	ZunoSpiSlave_t						*slave;
	USART_TypeDef						*usart;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	if ((slave = this->_slave)!= 0x0) {
		usart = config->usart;
		slave->user_onRequest = function;
		usart->TIMECMP1 = USART_TIMECMP1_TSTART_RXEOF | USART_TIMECMP1_TSTOP_RXACT | 0x7F;
		usart->IEN = USART_IEN_TCMP1;
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

ZunoError_t SPIClass::setSlave(uint8_t mode, uint16_t len) {
	ZunoError_t							ret;
	USART_TypeDef						*usart;
	const ZunoSpiConfig_t		*config;
	ZunoSpiSlave_t						*slave;

	if (len < SPI_BUFFER_LENGTH)
		len = SPI_BUFFER_LENGTH;
	config = this->_config;
	if ((ret = zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	usart = config->usart;
	if (mode == true) {
		if (this->_slave == 0x0) {
			if ((slave = (ZunoSpiSlave_t *)malloc(sizeof(ZunoSpiSlave_t) + len)) == 0)
				ret = ZunoErrorMemory;
			else {
				USART_Enable(usart, usartDisable);
				slave->len = len / 0x2;
				if ((slave->channel = LdmaClass::receivedCyclical((void *)&usart->RXDATA, &slave->buffer[len / 0x2], len / 0x2, config->dmaSignalRead, ldmaCtrlSizeByte, &slave->arrayReceivedCyclical)) >= 0x0) {
					zunoAttachSysHandler(ZUNO_HANDLER_IRQ, config->subType, (void *)config->IRQHandler);
					slave->channel_w = -1;
					slave->count = 0x0;
					slave->user_onRequest = 0x0;
					this->_slave = slave;
					usart->CMD = USART_CMD_MASTERDIS;
					pinMode(this->_sck_pin, INPUT_UP);
					pinMode((this->_ss_pin == UNKNOWN_PIN) ? SS : this->_ss_pin, INPUT_UP);
					pinMode(this->_mosi_pin, INPUT_UP);
					pinMode(this->_miso_pin, OUTPUT_UP);
					usart->ROUTELOC0 = usart->ROUTELOC0 | (this->_ss_loc << _USART_ROUTELOC0_CSLOC_SHIFT);// Set USART pin locations
					usart->ROUTEPEN = USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_CSPEN | USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;// Enable USART pins
					NVIC_ClearPendingIRQ(config->irqType);
					NVIC_EnableIRQ(config->irqType);
				}
				else {
					free(slave);
					ret = ZunoErrorDmaLimitChannel;
				}
				USART_Enable(usart, usartEnable);
			}
		}
	}
	else if ((slave = this->_slave) != 0x0) {
		USART_Enable(usart, usartDisable);
		LdmaClass::transferStop(slave->channel);
		LdmaClass::transferStop(slave->channel_w);
		free(slave);
		pinMode(this->_sck_pin, OUTPUT_UP);//_GPIO_P_MODEL_MODE0_PUSHPULL
		pinMode(this->_miso_pin, INPUT_UP);//_GPIO_P_MODEL_MODE0_INPUT
		pinMode(this->_mosi_pin, OUTPUT_UP);
		if(this->_ss_pin != UNKNOWN_PIN)
			pinMode(this->_ss_pin, OUTPUT_UP);
		this->_slave = 0x0;
		usart->CMD = USART_CMD_MASTEREN;
		usart->ROUTELOC0 = usart->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK);
		usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
		usart->IEN = _USART_IEN_RESETVALUE;
		NVIC_DisableIRQ(config->irqType);
		USART_Enable(usart, usartEnable);
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ret);
}

ZunoError_t SPIClass::begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss) {
	const ZunoSpiConfig_t		*config;
	ZunoError_t							ret;
	USART_TypeDef						*usart;
	const uint8_t						*location_ptr;
	size_t								location_sz;
	size_t 								rx_loc;
	size_t 								tx_loc;
	size_t 								clk_loc;

	config = this->_config;
	usart = config->usart;
	// The right place to check pin location is here, 'cause we haven't allocate SyncMasterHadwareSerial
	// So we can throw pin error without extra code
	if (usart == USART2) {
		location_ptr = g_loc_pa5_pf0_pf1_pf3_pf7;// USART2 has a cropped location set
		location_sz = sizeof(g_loc_pa5_pf0_pf1_pf3_pf7);
	}
	else {
		location_ptr = g_loc_pa0_pf7_all;
		location_sz = sizeof(g_loc_pa0_pf7_all);
	}
	// Extract base locations for pins 
	rx_loc = getLocation(location_ptr, location_sz, miso);
	tx_loc = getLocation(location_ptr, location_sz, mosi);
	clk_loc = getLocation(location_ptr, location_sz, sck);
	if (sck == miso || sck == mosi || sck == ss || rx_loc == INVALID_PIN_INDEX || tx_loc == INVALID_PIN_INDEX || clk_loc == INVALID_PIN_INDEX)
		return (ZunoErrorInvalidPin);
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterSpi, this->_init, (size_t)this, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	pinMode(sck, OUTPUT_UP);//_GPIO_P_MODEL_MODE0_PUSHPULL
	pinMode(miso, INPUT_UP);//_GPIO_P_MODEL_MODE0_INPUT
	pinMode(mosi, OUTPUT_UP);
	this->_ss_pin = ss;
	this->_sck_pin = sck;
	this->_miso_pin = miso;
	this->_mosi_pin = mosi;
	if(ss != UNKNOWN_PIN)
		pinMode(ss, OUTPUT_UP);
	else
		ss = SS;
	rx_loc = rx_loc ? rx_loc - 1 : MAX_VALID_PINLOCATION;// Now we have to shift rx location back, it always stands before tx location
	clk_loc = (clk_loc > 1) ? clk_loc - 2 : (clk_loc ? MAX_VALID_PINLOCATION : MAX_VALID_PINLOCATION - 1);
	usart->ROUTELOC0 = tx_loc << _USART_ROUTELOC0_TXLOC_SHIFT | rx_loc << _USART_ROUTELOC0_RXLOC_SHIFT | clk_loc << _USART_ROUTELOC0_CLKLOC_SHIFT;
	ss = getLocation(location_ptr, location_sz, ss);
	this->_ss_loc = (ss > 2) ? ss - 3 : (ss ? MAX_VALID_PINLOCATION : MAX_VALID_PINLOCATION - 2);
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ZunoErrorOk);
}

ZunoError_t SPIClass::beginTransaction(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
	USART_TypeDef						*usart;
	const ZunoSpiConfig_t		*config;
	ZunoError_t							ret;

	config = this->_config;
	if ((ret = zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	usart = config->usart;
	usart->CTRL = (usart->CTRL & ~(USART_CTRL_MSBF | usartClockMode0 | usartClockMode1 | usartClockMode2 | usartClockMode3)) | (bitOrder ? USART_CTRL_MSBF : 0) | this->_convertMode(dataMode);
	if (clock != this->_baudrate) {
		this->_baudrate = clock;
		USART_BaudrateSyncSet(usart, 0, clock);
	}
	if(_ss_pin != UNKNOWN_PIN)
		digitalWrite(this->_ss_pin, LOW);//We inform slave about receiving data
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ZunoErrorOk);
}

void SPIClass::setBitOrder(uint8_t order) {
	USART_TypeDef						*usart;
	const ZunoSpiConfig_t		*config;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	usart = config->usart;
	usart->CTRL = (usart->CTRL & ~(USART_CTRL_MSBF)) | (order ? USART_CTRL_MSBF : 0x0);
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

void SPIClass::setDataMode(uint8_t mode, uint8_t slaveSelectPin) {
	USART_TypeDef						*usart;
	const ZunoSpiConfig_t		*config;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	usart = config->usart;
	usart->CTRL = (usart->CTRL & ~(usartClockMode0 | usartClockMode1 | usartClockMode2 | usartClockMode3)) | this->_convertMode(mode);
	this->_ss_pin = slaveSelectPin;
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

void SPIClass::setClockDivider(uint8_t divider, uint8_t slaveSelectPin) {
	USART_TypeDef						*usart;
	const ZunoSpiConfig_t		*config;
	uint32_t							clock;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	usart = config->usart;
	clock = CMU_ClockFreqGet(config->bus_clock) / divider;
	if (clock != this->_baudrate) {
		this->_baudrate = clock;
		USART_BaudrateSyncSet(usart, 0, clock);
	}
	this->_ss_pin = slaveSelectPin;
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

void SPIClass::endTransaction(void) {
	const ZunoSpiConfig_t		*config;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return ;
	if(_ss_pin != UNKNOWN_PIN)
		digitalWrite(this->_ss_pin, HIGH);//We inform slave to terminate data acquisition
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
}

int SPIClass::available(void) {
	const ZunoSpiConfig_t				*config;
	int											out;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return (0);
	if (this->_slave == 0x0 || this->_slave->channel == -1)
		out = 0x0;
	else
		out = LdmaClass::receivedAvailable(this->_slave->channel);
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (out);
}

int SPIClass::peek(void) {
	return (this->_readLock(false));
}
int SPIClass::read(void) {
	return (this->_readLock(true));
}

/* Private Methods */
void SPIClass::_USART_IRQHandler(uint32_t flags) {
	ZunoSpiSlave_t						*slave;
	ssize_t								channel_w;
	size_t								len;
	const ZunoSpiConfig_t		*config;

	config = this->_config;
	slave = this->_slave;
	if (slave->user_onRequest != 0x0)
	{
		if ((channel_w = slave->channel_w) < 0x0  || LdmaClass::transferDone(channel_w) == true)
		{
			if (channel_w != -1) {
				LdmaClass::transferStop(channel_w);
				slave->channel_w = -1;
				config->usart->CMD = USART_CMD_CLEARRX;
				slave->channel = LdmaClass::receivedCyclical((void *)&config->usart->RXDATA, &slave->buffer[slave->len / 0x2], slave->len / 0x2, config->dmaSignalRead, ldmaCtrlSizeByte, &slave->arrayReceivedCyclical);
			}
			else {
				slave->count = 0x0;
				slave->user_onRequest();
				if ((len = slave->count) != 0x0) {
					if ((slave->channel_w = LdmaClass::transferSingle(&slave->buffer[0x0], (void*)&(config->usart->TXDATA), len, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &slave->array_w)) >= 0x0) {
						LdmaClass::transferStop(slave->channel);
						slave->channel = -1;
					}
				}
			}
		
		}
	}
	(void)flags;
}

USART_ClockMode_TypeDef SPIClass::_convertMode(uint8_t mode) {
	USART_ClockMode_TypeDef							out;

	switch (mode) {
		case SPI_MODE0:
		default:
			out = usartClockMode0;
			break ;
		case SPI_MODE1:
			out = usartClockMode1;
			break ;
		case SPI_MODE2:
			out = usartClockMode2;
			break ;
		case SPI_MODE3:
			out = usartClockMode3;
			break ;
	}
	return (out);
}


void SPIClass::_USART0_IRQHandler(uint32_t flags) {
	SPI0._USART_IRQHandler(flags);
}

void SPIClass::_USART1_IRQHandler(uint32_t flags) {
	SPI1._USART_IRQHandler(flags);
}

void SPIClass::_USART2_IRQHandler(uint32_t flags) {
	SPI2._USART_IRQHandler(flags);
}

inline int SPIClass::_readLock(uint8_t bOffset) {
	const ZunoSpiConfig_t				*config;
	int											out;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return (-1);
	if (this->_slave == 0x0  || this->_slave->channel == -1)
		out = -1;
	else
		out = LdmaClass::receivedReadPeek(this->_slave->channel, bOffset);
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (out);
}

size_t SPIClass::_transferDate(size_t data, size_t bFlags) {
	size_t								out;
	const ZunoSpiConfig_t		*config;
	USART_TypeDef						*usart;

	config = this->_config;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey) != ZunoErrorOk)
		return (0);
	usart = config->usart;
	if ((bFlags & SPI_FLAGS_16BIT) != 0) {
		usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits16;
		out = USART_SpiTransfer16(usart, (uint16_t)data);
		usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits8;
	}
	else
		out = USART_SpiTransfer(usart, (uint8_t)data);
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (out);
}

ZunoError_t SPIClass::_transferStrlen(void *b, size_t bFlags) {
	return (this->_transfer(b, strlen((char *)b), bFlags));
}

ZunoError_t SPIClass::_transfer(void *b, size_t count, size_t bFlags) {
	const ZunoSpiConfig_t		*config;
	USART_TypeDef						*usart;
	void								*e;
	uint8_t								*tmp;
	ZunoError_t							ret;
	size_t								out;
	ssize_t								channel_r;
	ssize_t								channel_w;
	LdmaClassTransferSingle_t			array_r;
	LdmaClassTransferSingle_t			array_w;
	uint64_t							ms;

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
		ms = count;
		ms = ms * 8 * 1000 / USART_BaudrateGet(usart);
		channel_r = -1;
		if ((bFlags & SPI_FLAGS_CONST) != 0 || ((channel_r = LdmaClass::transferSingle((const void *)&usart->RXDATA, b, count - 0x1, config->dmaSignalRead, ldmaCtrlSizeByte, ldmaCtrlSrcIncNone, ldmaCtrlDstIncOne, &array_r)) >= 0x0)) {
			if ((channel_w = LdmaClass::transferSingle(b, (void*)&(usart->TXDATA), count, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array_w)) > 0x0) {
				delay(ms);
				while (!(usart->STATUS & USART_STATUS_TXC))//Waiting for the last byte to go before we finish the transfer protocol
					__NOP();
				LdmaClass::transferStop(channel_w);
			}
			else
				ret = ZunoErrorDmaLimitChannel;
			if (channel_r >= 0x0) {
				tmp = (uint8_t *)b;
				tmp[count - 0x1] = usart->RXDATA;
				LdmaClass::transferStop(channel_r);
			}
		}
		else
			ret = ZunoErrorDmaLimitChannel;
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ret);
}

ZunoError_t SPIClass::memset(uint8_t c, size_t n) {
	const ZunoSpiConfig_t		*config;
	USART_TypeDef						*usart;
	ZunoError_t							ret;
	ssize_t								channel_w;
	LdmaClassTransferSingle_t			array_w;
	uint64_t							ms;

	config = this->_config;
	if ((ret = zunoSyncLockWrite(config->lpLock, SyncMasterSpi, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	usart = config->usart;
	usart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
	ms = n;
	ms = ms * 8 * 1000 / USART_BaudrateGet(usart);
	if ((channel_w = LdmaClass::transferSingle(&c, (void*)&(usart->TXDATA), n, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncNone, ldmaCtrlDstIncNone, &array_w)) >= 0x0) {
		delay(ms);
		while (!(usart->STATUS & USART_STATUS_TXC))//Waiting for the last byte to go before we finish the transfer protocol
			__NOP();
		LdmaClass::transferStop(channel_w);
	}
	else
		ret = ZunoErrorDmaLimitChannel;
	zunoSyncReleseWrite(config->lpLock, SyncMasterSpi, &this->_lpKey);
	return (ret);
}

ZunoError_t SPIClass::_init(size_t param) {
	SPIClass							*spi;
	const ZunoSpiConfig_t		*config;
	USART_TypeDef						*usart;
	

	spi = (SPIClass *)param;
	config = spi->_config;
	CMU_ClockEnable(config->bus_clock, true);
	usart = config->usart;
	USART_InitSync(usart, &spi->_initSpi);
	usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
	return (ZunoErrorOk);
}

ZunoError_t SPIClass::_deInit(size_t param) {
	SPIClass							*spi;
	ZunoSpiSlave_t						*slave;

	spi = (SPIClass *)param;
	USART_Reset(spi->_config->usart);
	if ((slave = spi->_slave) != 0x0) {
		LdmaClass::transferStop(slave->channel);
		NVIC_DisableIRQ(spi->_config->irqType);
		free(slave);
	}
	return (ZunoErrorOk);
}


/* Preinstantiate Objects */
SPIClass SPI0 = SPIClass(ZunoSpiUsart0);
SPIClass SPI1 = SPIClass(ZunoSpiUsart1);
SPIClass SPI2 = SPIClass(ZunoSpiUsart2);