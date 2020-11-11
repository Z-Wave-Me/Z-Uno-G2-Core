#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "ZDma.h"
#include "HardwareSerial.h"

#define HARDWARE_SERIAL_MIN_WRITE_ZDMA			2
#define HARDWARE_SERIAL_BUFFER_LENGTH			128

#define HARDWARE_SERIAL_UNIQ_ZDMA_WRITE			((size_t)&this->_numberConfig)

typedef struct							ZunoHardwareSerialInit_s
{
	const ZunoHardwareSerialConfig_t	*config;
	size_t								baudrate;
}										ZunoHardwareSerialInit_t;

const ZunoHardwareSerialConfig_t HardwareSerial::_configTable[3] = {
	{
		.usart = USART0,
		.IRQHandler = (void *)&Serial0._USART0_IRQHandler,
		.lpLock = &gSyncUSART0,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART0_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART0_TXBL,
		.bus_clock = cmuClock_USART0,
		.irqType = USART0_RX_IRQn,
		.subType = ZUNO_IRQVEC_USART0_RX,
		.rx = RX0,
		.tx = TX0
	},
	{
		.usart = USART1,
		.IRQHandler = (void *)&Serial1._USART1_IRQHandler,
		.lpLock = &gSyncUSART1,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART1_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART1_TXBL,
		.bus_clock = cmuClock_USART1,
		.irqType = USART1_RX_IRQn,
		.subType = ZUNO_IRQVEC_USART1_RX,
		.rx = RX1,
		.tx = TX1
	},
	{
		.usart = USART2,
		.IRQHandler = (void *)&Serial._USART2_IRQHandler,
		.lpLock = &gSyncUSART2,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART2_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART2_TXBL,
		.bus_clock = cmuClock_USART2,
		.irqType = USART2_RX_IRQn,
		.subType = ZUNO_IRQVEC_USART2_RX,
		.rx = RX2,
		.tx = TX2
	}
};

/* Public Constructors */
HardwareSerial::HardwareSerial(uint8_t numberConfig): _numberConfig(numberConfig), _bFree(false), _buffer(0), _buffer_len(0), _buffer_count(0) {

}

/* Public Methods */
ZunoError_t HardwareSerial::begin(void) {
	return (this->begin(this->_configTable[this->_numberConfig].baudrate));
}

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
	zunoSyncClose(config->lpLock, SyncMasterHadwareSerial, this->_deInit, (size_t)config);
}

size_t HardwareSerial::available(void) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	size_t											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial) != ZunoErrorOk)
		return (0);
	out = this->_available();
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial);
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
	if (zunoSyncLockRead(config->lpLock, SyncMasterHadwareSerial) != ZunoErrorOk)
		return (0);
	usart = config->usart;
	if (count > HARDWARE_SERIAL_MIN_WRITE_ZDMA && ZDMA.toMemoryPeripheral(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE, config->dmaSignalWrite, (void*)&(usart->TXDATA), (void *)b, count, zdmaData8) == ZunoErrorOk) {
		ZDMA.waitTransfer(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE);
		while (!(usart->STATUS & USART_STATUS_TXBL))/* Check that transmit buffer is empty */
			__NOP();
	}
	else {
		e = b + count;
		while (b < e)
			USART_Tx(usart, b++[0]);
	}
	zunoSyncReleseRead(config->lpLock, SyncMasterHadwareSerial);
	return (count);
}

/* Private Methods */
inline size_t HardwareSerial::_available(void) {
	size_t				count;
	size_t				count_read;

	count_read = this->_buffer_count_read;
	count = this->_buffer_count;
	if (count_read >= count)
		return (0);
	return (count - count_read);
}

inline int HardwareSerial::_readLock(uint8_t bOffset) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	int											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial) != ZunoErrorOk)
		return (-1);
	out = this->_read(bOffset);
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial);
	return (out);
}

inline int HardwareSerial::_read(uint8_t bOffset) {
	size_t										count_read;

	count_read = this->_buffer_count_read;
	if (count_read >= this->_buffer_count)
		return (-1);
	if (bOffset == true)
		this->_buffer_count_read = count_read + 1;
	return (this->_buffer[count_read]);
}

void HardwareSerial::_deInit(size_t param) {
	const ZunoHardwareSerialConfig_t			*config;

	config = (const ZunoHardwareSerialConfig_t *)param;
	NVIC_DisableIRQ(config->irqType);
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, config->subType, config->IRQHandler);
	USART_Reset(config->usart);
}

ZunoError_t HardwareSerial::_init(size_t param) {
	ZunoHardwareSerialInit_t					*init;
	const ZunoHardwareSerialConfig_t			*config;
	ZunoError_t									ret;
	USART_InitAsync_TypeDef						usartInit;
	USART_TypeDef								*usart;

	init = (ZunoHardwareSerialInit_t *)param;
	config = init->config;
	if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, config->subType, config->IRQHandler)) != ZunoErrorOk)
		return (ret);
	CMU_ClockEnable(config->bus_clock, true);
	usartInit = USART_INITASYNC_DEFAULT;
	usartInit.baudrate = init->baudrate;
	usart = config->usart;
	USART_InitAsync(usart, &usartInit);
	usart->IEN = USART_IEN_RXDATAV;
	NVIC_EnableIRQ(config->irqType);/* Enable interrupts in NVIC */
	return (ZunoErrorOk);
}

inline ZunoError_t HardwareSerial::_begin(size_t baudrate, uint8_t rx, uint8_t tx, void *b, hardware_serial_buffer_len len, uint8_t bFree) {
	ZunoHardwareSerialInit_t					init;
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t								*location;
	size_t										routeLocation;
	ZunoError_t									ret;
	ZunoSync_t									*lpLock;

	if (rx > ZUNO_PIN_LAST_INDEX || tx > ZUNO_PIN_LAST_INDEX)
		return (ZunoErrorInvalidPin);
	if (len == 0)
		return (ZunoErrorMemory);
	config = &this->_configTable[this->_numberConfig];
	init.config = config;
	init.baudrate = baudrate;
	lpLock = config->lpLock;
	if ((ret = zunoSyncOpen(lpLock, SyncMasterHadwareSerial, this->_init, (size_t)&init)) != ZunoErrorOk || (ret = zunoSyncLockWrite(lpLock, SyncMasterHadwareSerial)) != ZunoErrorOk) {
		if (bFree == true)
			free(b);
	}
	usart = config->usart;
	USART_BaudrateAsyncSet(usart, 0, baudrate, usartOVS16);
	if (this->_bFree == true)
		free(this->_buffer);
	this->_buffer = (uint8_t *)b;
	this->_buffer_len = len;
	this->_bFree = bFree;
	pinMode(tx, OUTPUT_UP);
	pinMode(rx, INPUT_DOWN);
	if (usart == USART2) {
		location = &g_loc_pf0_pf1_pf3_pf7[0];
		routeLocation = (((((getRealPort(tx) << 4) | getRealPin(tx)) == 5) ? 0 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), tx) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT) | (((((getRealPort(rx) << 4) | getRealPin(rx)) == 5) ? 31 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), rx) + 13) << _USART_ROUTELOC0_RXLOC_SHIFT);
	}
	else {
		location = &g_loc_pa0_pf7_all[0];
		routeLocation = ((getLocation(location, sizeof(g_loc_pa0_pf7_all), tx)) << _USART_ROUTELOC0_TXLOC_SHIFT) | (((getLocation(location, sizeof(g_loc_pa0_pf7_all), rx) - 1) % sizeof(g_loc_pa0_pf7_all)) << _USART_ROUTELOC0_RXLOC_SHIFT);
	}
	usart->ROUTELOC0 = routeLocation;
	usart->ROUTEPEN |= USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
	zunoSyncReleseWrite(lpLock, SyncMasterHadwareSerial);
	return (ZunoErrorOk);
}

inline void HardwareSerial::_USART_IRQHandler(size_t date) {
	USART_TypeDef						*usart;

	if (this->_buffer_count >= this->_buffer_len) {
		this->_buffer_count = 0;
		this->_buffer_count_read = 0;
	}
	this->_buffer[this->_buffer_count++] = (uint8_t)date;
}

void HardwareSerial::_USART0_IRQHandler(size_t flags) {
	Serial0._USART_IRQHandler(flags);
}

void HardwareSerial::_USART1_IRQHandler(size_t flags) {
	Serial1._USART_IRQHandler(flags);
}

void HardwareSerial::_USART2_IRQHandler(size_t flags) {
	Serial._USART_IRQHandler(flags);
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
		HardwareSerial Serial(1);// USB
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