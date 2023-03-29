#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "HardwareSerial.h"
#include "zwaveme_libft.h"

#define HARDWARE_SERIAL_MIN_WRITE_ZDMA			2
#define HARDWARE_SERIAL_BUFFER_LENGTH			128

typedef struct							ZunoHardwareSerialDeInit_s
{
	const ZunoHardwareSerialConfig_t	*config;
	size_t								uniqIdRead;
}										ZunoHardwareSerialDeInit_t;

const ZunoHardwareSerialConfig_t HardwareSerial::_configTable[] = {
	{
		.usart = USART0,
		.lpLock = &gSyncUSART0,
		.dmaSignalWrite = ldmaPeripheralSignal_USART0_TXBL,
		.dmaSignalRead = ldmaPeripheralSignal_USART0_RXDATAV,
		.bus_clock = cmuClock_USART0,
		.rx = RX0,
		.tx = TX0
	},
	{
		.usart = USART1,
		.lpLock = &gSyncUSART1,
		.dmaSignalWrite = ldmaPeripheralSignal_USART1_TXBL,
		.dmaSignalRead = ldmaPeripheralSignal_USART1_RXDATAV,
		.bus_clock = cmuClock_USART1,
		.rx = RX1,
		.tx = TX1
	},
		#if ZUNO_PIN_V <= 3
			{
				.usart = USART1,
				.lpLock = &gSyncUSART2,
				.dmaSignalWrite = ldmaPeripheralSignal_USART1_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART1_RXDATAV,
				.bus_clock = cmuClock_USART1,
				.rx = RX2,
				.tx = TX2
			}
		#else
			{
				.usart = USART2,
				.lpLock = &gSyncUSART2,
				.dmaSignalWrite = ldmaPeripheralSignal_USART2_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART2_RXDATAV,
				.bus_clock = cmuClock_USART2,
				.rx = RX2,
				.tx = TX2
			}
		#endif
};

/* Public Constructors */
HardwareSerial::HardwareSerial(uint8_t numberConfig): _channel(-1), _lpKey(false), _bFree(false) {
	if (numberConfig >= (sizeof(HardwareSerial::_configTable) / sizeof(ZunoHardwareSerialConfig_t)))
		numberConfig = 0;
	this->_numberConfig = numberConfig;
}

/* Public Methods */
void HardwareSerial::begin(unsigned long baud, uint32_t config) {
	const ZunoHardwareSerialConfig_t			*config_serial;

	config_serial = &this->_configTable[this->_numberConfig];
	this->begin(baud, config, config_serial->rx, config_serial->tx);
}

ZunoError_t HardwareSerial::begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx) {
	void				*b;

	if ((b = malloc(HARDWARE_SERIAL_BUFFER_LENGTH)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(speed, config, rx, tx, b, HARDWARE_SERIAL_BUFFER_LENGTH, true));
}

ZunoError_t HardwareSerial::begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx, void *buffer, uint16_t len) {
	return (this->_begin(speed, config, rx, tx, buffer, len, false));
}

void HardwareSerial::end() {
	const ZunoHardwareSerialConfig_t			*config;

	config = &this->_configTable[this->_numberConfig];
	zunoSyncClose(config->lpLock, SyncMasterHadwareSerial, HardwareSerial::_deInit, (size_t)this, &this->_lpKey);
}

int HardwareSerial::available(void) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	int											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = LdmaClass::receivedAvailable(this->_channel);
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (out);
}

int HardwareSerial::peek(void) {
	return (this->_readLock(false));
}
int HardwareSerial::read(void) {
	return (this->_readLock(true));
}

size_t HardwareSerial::write(const uint8_t *b, size_t count) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t								*e;
	ssize_t										channel;
	LdmaClassTransferSingle_t					array;
	uint32_t									ms;

	config = &this->_configTable[this->_numberConfig];
	if (zunoSyncLockWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (0);
	usart = config->usart;
	ms = this->countWaitingMs(count);
	if (count <= HARDWARE_SERIAL_MIN_WRITE_ZDMA) {
		e = b + count;
		ms = ms / count;
		while (b < e) {
			usart->TXDATA = (uint32_t)b++[0];
			delay(ms);
			while (!(usart->STATUS & USART_STATUS_TXC))/* Check that transmit buffer is empty */
				__NOP();
		}
	}
	else if ((channel = LdmaClass::transferSingle(b, (void*)&(usart->TXDATA), count, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) >= 0x0) {
		delay(ms);
		while (!(usart->STATUS & USART_STATUS_TXC))/* Check that transmit buffer is empty */
			__NOP();
		LdmaClass::transferStop(channel);
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (count);
}

// V_uart — скорость UART (например: 9600, 115200), бод;
// d — количество бит данных;
// D — количество байт всех данных;
// s — количество стоповых бит;
// p — количество бит четности, p = 1 если бит четности присутствует, или p = 0 если бит четности отсутствует;
// t = 8 * D * (d + 1 + s + p) * 1000 / (d * V_uart) - мс
size_t HardwareSerial::countWaitingMs(size_t n) {
	const ZunoHardwareSerialConfig_t			*config;
	uint32_t									ms;
	uint32_t									frame;

	config = &this->_configTable[this->_numberConfig];
	frame = config->usart->FRAME;
	ms = 1000 * 0x8 * n * ((((frame & _USART_FRAME_DATABITS_MASK) >> _USART_FRAME_DATABITS_SHIFT) + 0x3) + 0x1 + ((frame & _USART_FRAME_STOPBITS_MASK) == USART_FRAME_STOPBITS_TWO ? 0x2 : 0x1) + ((frame & _USART_FRAME_PARITY_MASK) == USART_FRAME_PARITY_EVEN ? 0x1 : 0x0)) / ((((frame & _USART_FRAME_DATABITS_MASK) >> _USART_FRAME_DATABITS_SHIFT) + 0x3) * this->_baudrate);
	ms = ms + ms / 100;//intercharacter spacing takes into account, or rather its absence
	return (ms);
}

void HardwareSerial::memset(uint8_t c, size_t n) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	ssize_t										channel;
	LdmaClassTransferSingle_t					array;

	config = &this->_configTable[this->_numberConfig];
	if (zunoSyncLockWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return ;
	usart = config->usart;
	if ((channel = LdmaClass::transferSingle(&c, (void*)&(usart->TXDATA), n, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncNone, ldmaCtrlDstIncNone, &array)) >= 0x0) {
		delay(this->countWaitingMs(n));
		while (!(usart->STATUS & USART_STATUS_TXC))/* Check that transmit buffer is empty */
			__NOP();
		LdmaClass::transferStop(channel);
	}
	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return ;
}


/* Private Methods */
inline int HardwareSerial::_readLock(uint8_t bOffset) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	int											out;

	config = &this->_configTable[this->_numberConfig];
	lpLock = config->lpLock;
	if (zunoSyncLockRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (-1);
	out = LdmaClass::receivedReadPeek(this->_channel, bOffset);
	zunoSyncReleseRead(lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	return (out);
}

ZunoError_t HardwareSerial::_deInit(size_t param) {
	HardwareSerial								*serial;
	const ZunoHardwareSerialConfig_t			*config;
	ssize_t										channel;

	serial = (HardwareSerial *)param;
	config = &serial->_configTable[serial->_numberConfig];
	if ((channel = serial->_channel) > 0x0) {
		LdmaClass::transferStop(channel);
		serial->_channel = -1;
	}
	USART_Reset(config->usart);
	if (serial->_bFree == true) {
		serial->_bFree = false;
		free(serial->_buffer);
	}
	return (ZunoErrorOk);
}

inline ZunoError_t HardwareSerial::_beginFaill(ZunoError_t ret, uint8_t bFree, void *b) {
	if (bFree == true)
		free(b);
	return (ret);
}

inline ZunoError_t HardwareSerial::_begin(size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx, void *b, size_t len, uint8_t bFree) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t								*location_ptr;
	size_t										location_sz;
	ZunoError_t									ret;
	size_t 										rx_loc;
	size_t 										tx_loc;
	USART_InitAsync_TypeDef						usartInit;
	ssize_t										channel;

	config = &HardwareSerial::_configTable[this->_numberConfig];
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
	rx_loc = getLocation(location_ptr, location_sz, rx);
	tx_loc = getLocation(location_ptr, location_sz, tx);
	if (rx == tx || rx_loc == INVALID_PIN_INDEX || tx_loc == INVALID_PIN_INDEX)
		return (this->_beginFaill(ZunoErrorInvalidPin, bFree, b));// wrong index or pin combination // The pin is valid, but it doesn't support by this USART interface
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterHadwareSerial, 0x0, 0x0, &this->_lpKey)) != ZunoErrorOk)
		return (this->_beginFaill(ret, bFree, b));
	CMU_ClockEnable(config->bus_clock, true);
	usartInit = USART_INITASYNC_DEFAULT;
	usartInit.baudrate = baudrate;
	USART_InitAsync(usart, &usartInit);
	usart->FRAME = option;
	usart->IEN = _USART_IEN_RESETVALUE;
	pinMode(tx, OUTPUT_UP);
	pinMode(rx, INPUT_PULLUP);
	if (this->_bFree == true)
		free(this->_buffer);
	this->_buffer = (uint8_t *)b;
	this->_buffer_len = len;
	this->_bFree = bFree;
	rx_loc = rx_loc ? rx_loc - 1 : MAX_VALID_PINLOCATION;// Now we have to shift rx location back, it always stands before tx location
	usart->ROUTELOC0 = tx_loc << _USART_ROUTELOC0_TXLOC_SHIFT | rx_loc << _USART_ROUTELOC0_RXLOC_SHIFT;
	usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
	if ((channel = this->_channel) > 0x0)
		LdmaClass::transferStop(channel);
	if (len != 0x0) {
		channel = LdmaClass::receivedCyclical((void *)&usart->RXDATA, b, len, config->dmaSignalRead, ldmaCtrlSizeByte, &this->_arrayReceivedCyclical);
		this->_channel = channel;
	}
	else
		this->_channel = -1;
	this->_baudrate = USART_BaudrateGet(usart);
	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	if (len != 0x0 && channel < 0x0) {
		this->end();
		return (ZunoErrorDmaLimitChannel);
	}
	return (ZunoErrorOk);
}

/* Preinstantiate Objects */
#if ZUNO_PIN_V == 3
	HardwareSerial Serial(2);// USB
	HardwareSerial Serial1(1); // UART1 // Пока не поддерживается 2
	HardwareSerial Serial0(0); // UART0
#elif ZUNO_PIN_V == 4
	HardwareSerial Serial(2);// USB
	HardwareSerial Serial1(1); // UART1
	HardwareSerial Serial0(0); // UART0
#elif ZUNO_PIN_V == 6
	HardwareSerial Serial(2);// USB
	HardwareSerial Serial1(1); // UART1
	HardwareSerial Serial0(0); // UART0
#elif ZUNO_PIN_V == 0
	HardwareSerial Serial(1);// USB
	HardwareSerial Serial1(1); // UART1
	HardwareSerial Serial0(0); // UART0
#else
	#error ZUNO_PIN_V
#endif
//For printf
ssize_t write(int fd, const void *buf, size_t count) {
	switch (fd) {
		case 0:
			return (Serial0.write((const uint8_t *)buf, count));
			break ;
		case 1:
			return (Serial1.write((const uint8_t *)buf, count));
			break ;
		case 2:
			return (Serial.write((const uint8_t *)buf, count));
			break ;
		default:
			break ;
	}
	return (-1);
}