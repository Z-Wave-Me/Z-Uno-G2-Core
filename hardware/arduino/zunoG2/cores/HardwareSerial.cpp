#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "ZDma.h"
#include "HardwareSerial.h"

#define HARDWARE_SERIAL_MIN_WRITE_ZDMA			2
#define HARDWARE_SERIAL_BUFFER_LENGTH			128

#define HARDWARE_SERIAL_UNIQ_ZDMA_WRITE			((size_t)&this->_buffer_len)
#define HARDWARE_SERIAL_UNIQ_ZDMA_READ			((size_t)&this->_buffer)
#define HARDWARE_SERIAL_UNIQ_ZDMA_READ2			((size_t)&serial->_buffer)

typedef struct							ZunoHardwareSerialInit_s
{
	const ZunoHardwareSerialConfig_t	*config;
	size_t								baudrate;
}										ZunoHardwareSerialInit_t;

typedef struct							ZunoHardwareSerialDeInit_s
{
	const ZunoHardwareSerialConfig_t	*config;
	size_t								uniqIdRead;
}										ZunoHardwareSerialDeInit_t;

const ZunoHardwareSerialConfig_t HardwareSerial::_configTable[] = {
	{
		.usart = USART0,
		.lpLock = &gSyncUSART0,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART0_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART0_TXBL,
		.bus_clock = cmuClock_USART0,
		.rx = RX0,
		.tx = TX0
	},
	{
		.usart = USART1,
		.lpLock = &gSyncUSART1,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART1_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART1_TXBL,
		.bus_clock = cmuClock_USART1,
		.rx = RX1,
		.tx = TX1
	},
		#if ZUNO_PIN_V <= 3
			{
				.usart = USART1,
				.lpLock = &gSyncUSART2,
				.baudrate = 115200,
				.dmaSignalRead = zdmaPeripheralSignal_USART1_RXDATAV,
				.dmaSignalWrite = zdmaPeripheralSignal_USART1_TXBL,
				.bus_clock = cmuClock_USART1,
				.rx = RX2,
				.tx = TX2
			}
		#else
			{
				.usart = USART2,
				.lpLock = &gSyncUSART2,
				.baudrate = 115200,
				.dmaSignalRead = zdmaPeripheralSignal_USART2_RXDATAV,
				.dmaSignalWrite = zdmaPeripheralSignal_USART2_TXBL,
				.bus_clock = cmuClock_USART2,
				.rx = RX2,
				.tx = TX2
			}
		#endif
};

/* Public Constructors */
HardwareSerial::HardwareSerial(uint8_t numberConfig)
#if (ZUNO_ZERO_BSS != true || false != 0)
	:_bFree(false), _lpKey(false), _buffer(0), _buffer_len(0)
#endif
{
	if (numberConfig >= (sizeof(HardwareSerial::_configTable) / sizeof(ZunoHardwareSerialConfig_t)))
		numberConfig = 0;
	this->_numberConfig = numberConfig;
}

/* Public Methods */
ZunoError_t HardwareSerial::begin(size_t baudrate) {
	const ZunoHardwareSerialConfig_t			*config;

	config = &this->_configTable[this->_numberConfig];
	return (this->begin(baudrate, config->rx, config->tx));
}

ZunoError_t HardwareSerial::begin(size_t baudrate, uint8_t rx, uint8_t tx) {
	void				*b;

	if ((b = malloc(HARDWARE_SERIAL_BUFFER_LENGTH)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(baudrate, rx, tx, b, HARDWARE_SERIAL_BUFFER_LENGTH, true));
}

ZunoError_t HardwareSerial::begin(size_t baudrate, uint8_t rx, uint8_t tx, void *b, uint16_t len) {
	return (this->_begin(baudrate, rx, tx, b, len, false));
}

void HardwareSerial::end() {
	const ZunoHardwareSerialConfig_t			*config;

	config = &this->_configTable[this->_numberConfig];
	zunoSyncClose(config->lpLock, SyncMasterHadwareSerial, HardwareSerial::_deInit, (size_t)this, &this->_lpKey);
}

size_t HardwareSerial::available(void) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	size_t											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = this->_available(config);
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (out);
}

int HardwareSerial::peek(void) {
	return (this->_readLock(false));
}
int HardwareSerial::read(void) {
	return (this->_readLock(true));
}

ssize_t HardwareSerial::printf(const char *format, ...) {
	va_list				args;
	ssize_t				out;

	va_start (args, format);
	out = vdprintf(this->_numberConfig, format, args);
	va_end (args);
	return (out);
}

uint8_t HardwareSerial::write(uint8_t value) {
	return (this->write((const uint8_t *)&value, 1));
}

uint8_t HardwareSerial::write(unsigned long value) {
	return (this->write((const uint8_t *)&value, 1));
}

uint8_t HardwareSerial::write(long value) {
	return (this->write((const uint8_t *)&value, 1));
}

uint8_t HardwareSerial::write(unsigned int value) {
	return (this->write((const uint8_t *)&value, 1));
}

uint8_t HardwareSerial::write(int value) { 
	return (this->write((const uint8_t *)&value, 1));
}

size_t HardwareSerial::write(const uint8_t *b, size_t count) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t								*e;

	config = &this->_configTable[this->_numberConfig];
	if (zunoSyncLockWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (0);
	usart = config->usart;
	if (count <= HARDWARE_SERIAL_MIN_WRITE_ZDMA) {
		e = b + count;
		while (b < e)
			USART_Tx(usart, b++[0]);
	}
	else if (ZDMA.toMemoryPeripheral(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE, config->dmaSignalWrite, (void*)&(usart->TXDATA), (void *)b, count, zdmaData8) == ZunoErrorOk) {
		ZDMA.waitTransfer(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE);
		while (!(usart->STATUS & USART_STATUS_TXBL))/* Check that transmit buffer is empty */
			__NOP();
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (count);
}

/* Private Methods */
inline size_t HardwareSerial::_available(const ZunoHardwareSerialConfig_t *config) {
	size_t				count;
	size_t				count_read;
	size_t				count_len;
	ZunoZDmaExt_t		lpExt;

	if (ZDMA.transferReceivedCount(HARDWARE_SERIAL_UNIQ_ZDMA_READ, &count) != ZunoErrorOk) {
		lpExt = ZDMA_EXT_INIT_DEFAULT;
		lpExt.loop = ZDMA_EXT_LOOP_INFINITY;
		ZDMA.toPeripheralMemory(HARDWARE_SERIAL_UNIQ_ZDMA_READ, config->dmaSignalRead, this->_buffer, (void*)&(config->usart->RXDATA), this->_buffer_len, zdmaData8, &lpExt);
		if (ZDMA.transferReceivedCount(HARDWARE_SERIAL_UNIQ_ZDMA_READ, &count) != ZunoErrorOk)
			return (0);
	}
	if (count == (count_read = this->_buffer_count_read))
		return (0);
	if (count_read == (count_len = this->_buffer_len)) {
		this->_buffer_count_read = 0;
		count_read = 0;
	}
	if (count >= count_read)
		return (count - count_read);
	return (count_len - count_read);
}

inline int HardwareSerial::_readLock(uint8_t bOffset) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	int											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (-1);
	out = this->_read(bOffset);
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (out);
}

inline int HardwareSerial::_read(uint8_t bOffset) {
	size_t								count;
	size_t								count_read;

	if (ZDMA.transferReceivedCount(HARDWARE_SERIAL_UNIQ_ZDMA_READ, &count) != ZunoErrorOk)
		return (-1);
	if (count == (count_read = this->_buffer_count_read))
		return (-1);
	if (count_read == this->_buffer_len) {
		this->_buffer_count_read = 0;
		count_read = 0;
	}
	this->_buffer_count_read++;
	return (this->_buffer[count_read]);
}

ZunoError_t HardwareSerial::_deInit(size_t param) {
	HardwareSerial								*serial;
	const ZunoHardwareSerialConfig_t			*config;

	serial = (HardwareSerial *)param;
	config = &serial->_configTable[serial->_numberConfig];
	ZDMA.stopTransfer(HARDWARE_SERIAL_UNIQ_ZDMA_READ2, true);
	USART_Reset(config->usart);
	if (serial->_bFree == true) {
		serial->_bFree = false;
		free(serial->_buffer);
	}
	return (ZunoErrorOk);
}

ZunoError_t HardwareSerial::_init(size_t param) {
	ZunoHardwareSerialInit_t					*init;
	const ZunoHardwareSerialConfig_t			*config;
	USART_InitAsync_TypeDef						usartInit;
	USART_TypeDef								*usart;

	init = (ZunoHardwareSerialInit_t *)param;
	config = init->config;
	
	usartInit = USART_INITASYNC_DEFAULT;
	usartInit.baudrate = init->baudrate;
	usartInit.enable = usartDisable;
	usart = config->usart;
	CMU_ClockEnable(config->bus_clock, true);
	USART_InitAsync(usart, &usartInit);
	//usart->ROUTELOC0 &= ~(_USART_ROUTELOC0_TXLOC_MASK | _USART_ROUTELOC0_RXLOC_MASK);
	return (ZunoErrorOk);
}

inline ZunoError_t HardwareSerial::_begin(size_t baudrate, uint8_t rx, uint8_t tx, void *b, hardware_serial_buffer_len len, uint8_t bFree) {
	ZunoHardwareSerialInit_t					init;
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t							    *location_ptr = g_loc_pa0_pf7_all;
	uint8_t										location_sz = sizeof(g_loc_pa0_pf7_all);
	
	size_t										routeLocation;
	ZunoError_t									ret;
	uint32_t 									rx_loc, tx_loc;

	if (rx > ZUNO_PIN_LAST_INDEX || tx > ZUNO_PIN_LAST_INDEX || rx == tx){
		if (bFree == true)
			free(b); // FIXME: Do we need it? Seems we have forgot it previously  ;)
		return (ZunoErrorInvalidPin); // wrong index or pin combination
	}
	if (len == 0)
		return (ZunoErrorMemory);
	config = &HardwareSerial::_configTable[this->_numberConfig];
	init.config = config;
	usart = config->usart;
	// The right place to check pin location is here, 'cause we haven't allocate SyncMasterHadwareSerial
	// So we can throw pin error without extra code  
	if (usart == USART2) {
		// USART2 has a cropped location set
		location_ptr = g_loc_pa5_pf0_pf1_pf3_pf7;
		location_sz  = sizeof(g_loc_pa5_pf0_pf1_pf3_pf7);  
	}
	// Extract base locations for pins 
	rx_loc = getLocation(location_ptr, location_sz, rx);
    tx_loc = getLocation(location_ptr, location_sz, tx);
	if((rx_loc == INVALID_PIN_INDEX) || (tx_loc == INVALID_PIN_INDEX)){
		return (ZunoErrorInvalidPin); // The pin is valid, but it doesn't support by this USART interface
	}
	// Now we have to shift rx location back, it always stands before tx location
	rx_loc = rx_loc ? rx_loc-1 : MAX_VALID_PINLOCATION;
	init.baudrate = baudrate;
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterHadwareSerial, HardwareSerial::_init, (size_t)&init, &this->_lpKey)) != ZunoErrorOk) {
		if (bFree == true)
			free(b);
		return (ret);
	}
	pinMode(tx, OUTPUT_UP);
	usart->ROUTELOC0 &= ~(_USART_ROUTELOC0_TXLOC_MASK);
	usart->ROUTELOC0 |= tx_loc << _USART_ROUTELOC0_TXLOC_SHIFT;
	pinMode(rx, INPUT_DOWN);
	usart->ROUTELOC0 &= ~(_USART_ROUTELOC0_RXLOC_MASK);
	usart->ROUTELOC0 |= rx_loc << _USART_ROUTELOC0_RXLOC_SHIFT;
	USART_BaudrateAsyncSet(usart, 0, baudrate, usartOVS16);
	//disable rx and tx
	usart->ROUTEPEN &= ~_USART_ROUTEPEN_MASK;
	//enable tx
	usart->ROUTEPEN |= USART_ROUTEPEN_TXPEN;
	USART_Enable(usart, usartEnableTx);
	//enable rx
	usart->ROUTEPEN |= USART_ROUTEPEN_RXPEN;
	USART_Enable(usart, usartEnableRx);
	USART_Enable(usart, usartEnable);
	if (this->_bFree == true)
		free(this->_buffer);
	this->_buffer = (uint8_t *)b;
	this->_buffer_len = len;
	this->_bFree = bFree;
	this->_buffer_count_read = 0;
	ZunoZDmaExt_t lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.loop = ZDMA_EXT_LOOP_INFINITY;
	lpExt.flags = ZDMA_EXT_FLAGS_RECONFIG;
	ZDMA.toPeripheralMemory(HARDWARE_SERIAL_UNIQ_ZDMA_READ, config->dmaSignalRead, (void *)b, (void*)&(usart->RXDATA), len, zdmaData8, &lpExt);

	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (ZunoErrorOk);
}

/* Preinstantiate Objects */
#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	#if ZUNO_PIN_V == 1
		HardwareSerial Serial(1);// USB
		HardwareSerial Serial1(1); // UART1  - разделяет один физический UART на разных пинах с Serial
		HardwareSerial Serial0(0); // UART0 
	#elif ZUNO_PIN_V == 2
		HardwareSerial Serial(1);// USB
		HardwareSerial Serial1(1); // UART1
		HardwareSerial Serial0(0); // UART0
	#elif ZUNO_PIN_V == 3
		HardwareSerial Serial(2);// USB
		HardwareSerial Serial1(1); // UART1 // Пока не поддерживается 2
		HardwareSerial Serial0(0); // UART0
	#elif ZUNO_PIN_V == 4
		HardwareSerial Serial(2);// USB
		HardwareSerial Serial1(1); // UART1
		HardwareSerial Serial0(0); // UART0
	#else
		#error ZUNO_PIN_V
	#endif
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI
#else
	#error Set ZUNO_ASSEMBLY_TYPE
#endif