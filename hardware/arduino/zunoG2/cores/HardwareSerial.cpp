#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "HardwareSerial.h"
#include "zwaveme_libft.h"

#define HARDWARE_SERIAL_MIN_WRITE_ZDMA			2
#define HARDWARE_SERIAL_BUFFER_LENGTH			128

#define HARDWARE_SERIAL_STATUS_TXC				(0x1UL << 5)
#define HARDWARE_SERIAL_FRAME_DATABITS_MASK		0xFUL
#define HARDWARE_SERIAL_FRAME_DATABITS_SHIFT	0
#define HARDWARE_SERIAL_FRAME_STOPBITS_MASK		0x3000UL
#define HARDWARE_SERIAL_FRAME_STOPBITS_TWO		(0x00000003UL << 12)
#define HARDWARE_SERIAL_FRAME_PARITY_MASK		0x300UL
#define HARDWARE_SERIAL_FRAME_PARITY_EVEN		(0x00000002UL << 8)

#if USART_COUNT >= 1
	#if HARDWARE_SERIAL_STATUS_TXC != USART_STATUS_TXC
		#error "USART_STATUS_TXC"
	#endif
	#if HARDWARE_SERIAL_FRAME_DATABITS_MASK != _USART_FRAME_DATABITS_MASK
		#error "_USART_FRAME_DATABITS_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_DATABITS_SHIFT != _USART_FRAME_DATABITS_SHIFT
		#error "_USART_FRAME_DATABITS_SHIFT"
	#endif
	#if HARDWARE_SERIAL_FRAME_STOPBITS_MASK != _USART_FRAME_STOPBITS_MASK
		#error "_USART_FRAME_STOPBITS_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_STOPBITS_TWO != USART_FRAME_STOPBITS_TWO
		#error "USART_FRAME_STOPBITS_TWO"
	#endif
	#if HARDWARE_SERIAL_FRAME_PARITY_MASK != _USART_FRAME_PARITY_MASK
		#error "_USART_FRAME_PARITY_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_PARITY_EVEN != USART_FRAME_PARITY_EVEN
		#error "USART_FRAME_PARITY_EVEN"
	#endif
	#if HARDWARE_SERIAL_STOP_BITS_1 != USART_FRAME_STOPBITS_ONE
		#error "USART_FRAME_STOPBITS_ONE"
	#endif
	#if HARDWARE_SERIAL_STOP_BITS_2 != USART_FRAME_STOPBITS_TWO
		#error "USART_FRAME_STOPBITS_TWO"
	#endif
	#if HARDWARE_SERIAL_NO_PARIRY != USART_FRAME_PARITY_NONE
		#error "USART_FRAME_PARITY_NONE"
	#endif
	#if HARDWARE_SERIAL_EVEN_PARIRY != USART_FRAME_PARITY_EVEN
		#error "USART_FRAME_PARITY_EVEN"
	#endif
	#if HARDWARE_SERIAL_ODD_PARIRY != USART_FRAME_PARITY_ODD
		#error "USART_FRAME_PARITY_ODD"
	#endif
	#if HARDWARE_SERIAL_DATA_BITS_8 != USART_FRAME_DATABITS_EIGHT
		#error "USART_FRAME_DATABITS_EIGHT"
	#endif
	#if HARDWARE_SERIAL_DATA_BITS_9 != USART_FRAME_DATABITS_NINE
		#error "USART_FRAME_DATABITS_NINE"
	#endif
#endif

#if EUSART_COUNT >= 1
	#if HARDWARE_SERIAL_STATUS_TXC != EUSART_STATUS_TXC
		#error "EUSART_STATUS_TXC"
	#endif
	#if HARDWARE_SERIAL_FRAME_DATABITS_MASK != _EUSART_FRAMECFG_DATABITS_MASK
		#error "_EUSART_FRAMECFG_DATABITS_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_DATABITS_SHIFT != _EUSART_FRAMECFG_DATABITS_SHIFT
		#error "_EUSART_FRAMECFG_DATABITS_SHIFT"
	#endif
	#if HARDWARE_SERIAL_FRAME_STOPBITS_MASK != _EUSART_FRAMECFG_STOPBITS_MASK
		#error "_EUSART_FRAMECFG_STOPBITS_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_STOPBITS_TWO != EUSART_FRAMECFG_STOPBITS_TWO
		#error "EUSART_FRAMECFG_STOPBITS_TWO"
	#endif
	#if HARDWARE_SERIAL_FRAME_PARITY_MASK != _EUSART_FRAMECFG_PARITY_MASK
		#error "_EUSART_FRAMECFG_PARITY_MASK"
	#endif
	#if HARDWARE_SERIAL_FRAME_PARITY_EVEN != EUSART_FRAMECFG_PARITY_EVEN
		#error "EUSART_FRAMECFG_PARITY_EVEN"
	#endif
	#if HARDWARE_SERIAL_STOP_BITS_1 != EUSART_FRAMECFG_STOPBITS_ONE
		#error "EUSART_FRAMECFG_STOPBITS_ONE"
	#endif
	#if HARDWARE_SERIAL_STOP_BITS_2 != EUSART_FRAMECFG_STOPBITS_TWO
		#error "EUSART_FRAMECFG_STOPBITS_TWO"
	#endif
	#if HARDWARE_SERIAL_NO_PARIRY != EUSART_FRAMECFG_PARITY_NONE
		#error "EUSART_FRAMECFG_PARITY_NONE"
	#endif
	#if HARDWARE_SERIAL_EVEN_PARIRY != EUSART_FRAMECFG_PARITY_EVEN
		#error "EUSART_FRAMECFG_PARITY_EVEN"
	#endif
	#if HARDWARE_SERIAL_ODD_PARIRY != EUSART_FRAMECFG_PARITY_ODD
		#error "EUSART_FRAMECFG_PARITY_ODD"
	#endif
#endif


typedef enum							ZunoHardwareSerialNumConfig_s
{
	#if EUSART_COUNT >= 2
	ZunoHardwareSerialEusart1,
	#endif
	#if EUSART_COUNT >= 1
	ZunoHardwareSerialEusart0,
	#endif
	#if EUSART_COUNT >= 3
	ZunoHardwareSerialEusart2,
	#endif
	#if USART_COUNT >= 1
	ZunoHardwareSerialUsart0,
	#endif
	#if USART_COUNT >= 2
	ZunoHardwareSerialUsart1,
	#endif
	#if USART_COUNT >= 3
	ZunoHardwareSerialUsart2,
	#endif
	ZunoHardwareSerialLast
}										ZunoHardwareSerialNumConfig_t;


/* Public Constructors */
HardwareSerial::HardwareSerial(uint8_t numberConfig): _channel(-1), _lpKey(false), _bFree(false) {
	const ZunoHardwareSerialConfig_t				*configTable;

	if (numberConfig >= ZunoHardwareSerialLast)
		numberConfig = 0;
	switch (numberConfig) {
		#if EUSART_COUNT >= 2
		case ZunoHardwareSerialEusart1:
			static const ZunoHardwareSerialConfig_t configTable_eusart1 =
			{
				.eusart = EUSART1,
				.TXDATA = &EUSART1->TXDATA,
				.FRAME = &EUSART1->FRAMECFG,
				.RXDATA = &EUSART1->RXDATA,
				.STATUS = &EUSART1->STATUS,
				.lpLock = &gSyncEUSART1,
				.dmaSignalWrite = ldmaPeripheralSignal_EUSART1_TXFL,
				.dmaSignalRead = ldmaPeripheralSignal_EUSART1_RXFL,
				.bus_clock = cmuClock_EUSART1,
				.rx = RX0,
				.tx = TX0,
				.fd = 0x1,
				.type = ZunoHardwareSerialTypeEusart
			};
			configTable = &configTable_eusart1;
			break ;
		#endif
		#if EUSART_COUNT >= 1
		case ZunoHardwareSerialEusart0:
			static const ZunoHardwareSerialConfig_t configTable_eusart0 =
			{
				.eusart = EUSART0,
				.TXDATA = &EUSART0->TXDATA,
				.FRAME = &EUSART0->FRAMECFG,
				.RXDATA = &EUSART0->RXDATA,
				.STATUS = &EUSART0->STATUS,
				.lpLock = &gSyncEUSART0,
				.dmaSignalWrite = ldmaPeripheralSignal_EUSART0_TXFL,
				.dmaSignalRead = ldmaPeripheralSignal_EUSART0_RXFL,
				.bus_clock = cmuClock_EUSART0,
				.rx = RX2,
				.tx = TX2,
				.fd = 0x0,
				.type = ZunoHardwareSerialTypeEusart
			};
			configTable = &configTable_eusart0;
			break ;
		#endif
		#if EUSART_COUNT >= 3
		case ZunoHardwareSerialEusart2:
			static const ZunoHardwareSerialConfig_t configTable_eusart2 =
			{
				.eusart = EUSART2,
				.TXDATA = &EUSART2->TXDATA,
				.FRAME = &EUSART2->FRAMECFG,
				.RXDATA = &EUSART2->RXDATA,
				.STATUS = &EUSART2->STATUS,
				.lpLock = &gSyncEUSART2,
				.dmaSignalWrite = ldmaPeripheralSignal_EUSART2_TXFL,
				.dmaSignalRead = ldmaPeripheralSignal_EUSART2_RXFL,
				.bus_clock = cmuClock_EUSART2,
				.rx = RX1,
				.tx = TX1,
				.fd = 0x2,
				.type = ZunoHardwareSerialTypeEusart
			};
			configTable = &configTable_eusart2;
			break ;
		#endif
		#if USART_COUNT >= 1
		default:
		case ZunoHardwareSerialUsart0:
			static const ZunoHardwareSerialConfig_t configTable_usart0 =
			{
				.usart = USART0,
				.TXDATA = &USART0->TXDATA,
				.FRAME = &USART0->FRAME,
				.RXDATA = &USART0->RXDATA,
				.STATUS = &USART0->STATUS,
				.lpLock = &gSyncUSART0,
				.dmaSignalWrite = ldmaPeripheralSignal_USART0_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART0_RXDATAV,
				.bus_clock = cmuClock_USART0,
				.rx = RX0,
				.tx = TX0,
				.fd = 0x0,
				.type = ZunoHardwareSerialTypeUsart
			};
			configTable = &configTable_usart0;
			break ;
		#endif
		#if USART_COUNT >= 2
		case ZunoHardwareSerialUsart1:
			static const ZunoHardwareSerialConfig_t configTable_usart1 =
			{
				.usart = USART1,
				.TXDATA = &USART1->TXDATA,
				.FRAME = &USART1->FRAME,
				.RXDATA = &USART1->RXDATA,
				.STATUS = &USART1->STATUS,
				.lpLock = &gSyncUSART1,
				.dmaSignalWrite = ldmaPeripheralSignal_USART1_TXBL,
				.dmaSignalRead = ldmaPeripheralSignal_USART1_RXDATAV,
				.bus_clock = cmuClock_USART1,
				.rx = RX1,
				.tx = TX1,
				.fd = 0x1,
				.type = ZunoHardwareSerialTypeUsart
			};
			configTable = &configTable_usart1;
			break ;
		#endif
		#if USART_COUNT >= 3
		case ZunoHardwareSerialUsart2:
			#if ZUNO_PIN_V == 3
				static const ZunoHardwareSerialConfig_t configTable_usart1 =
				{
					.usart = USART1,
					.TXDATA = &USART1->TXDATA,
					.FRAME = &USART1->FRAME,
					.RXDATA = &USART1->RXDATA,
					.STATUS = &USART1->STATUS,
					.lpLock = &gSyncUSART1,
					.dmaSignalWrite = ldmaPeripheralSignal_USART1_TXBL,
					.dmaSignalRead = ldmaPeripheralSignal_USART1_RXDATAV,
					.bus_clock = cmuClock_USART1,
					.rx = RX1,
					.tx = TX1,
					.fd = 0x1,
					.type = ZunoHardwareSerialTypeUsart
				};
				configTable = &configTable_usart1;
			#else
				static const ZunoHardwareSerialConfig_t configTable_usart2 =
				{
					.usart = USART2,
					.TXDATA = &USART2->TXDATA,
					.FRAME = &USART2->FRAME,
					.RXDATA = &USART2->RXDATA,
					.STATUS = &USART2->STATUS,
					.lpLock = &gSyncUSART2,
					.dmaSignalWrite = ldmaPeripheralSignal_USART2_TXBL,
					.dmaSignalRead = ldmaPeripheralSignal_USART2_RXDATAV,
					.bus_clock = cmuClock_USART2,
					.rx = RX2,
					.tx = TX2,
					.fd = 0x2,
					.type = ZunoHardwareSerialTypeUsart
				};
				configTable = &configTable_usart2;
			#endif
			break ;
		#endif
	}
	this->_configTable = configTable;
}

/* Public Methods */
void HardwareSerial::begin(unsigned long baud, uint32_t config) {
	const ZunoHardwareSerialConfig_t			*config_serial;

	config_serial = this->_configTable;
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

	config = this->_configTable;
	zunoSyncClose(config->lpLock, SyncMasterHadwareSerial, HardwareSerial::_deInit, (size_t)this, &this->_lpKey);
}

int HardwareSerial::available(void) {
	const ZunoHardwareSerialConfig_t			*config;
	ZunoSync_t									*lpLock;
	int											out;

	config = this->_configTable;
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
	const uint8_t								*e;
	ssize_t										channel;
	LdmaClassTransferSingle_t					array;
	uint32_t									ms;

	config = this->_configTable;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return (0);
	ms = this->countWaitingMs(count);
	if (count <= HARDWARE_SERIAL_MIN_WRITE_ZDMA) {
		e = b + count;
		ms = ms / count;
		while (b < e) {
			config->TXDATA[0x0] = (uint32_t)b++[0];
			delay(ms);
			while (!(config->STATUS[0x0] & HARDWARE_SERIAL_STATUS_TXC))/* Check that transmit buffer is empty */
				__NOP();
		}
	}
	else if ((channel = LdmaClass::transferSingle(b, (void*)(config->TXDATA), count, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) >= 0x0) {
		delay(ms);
		while (!(config->STATUS[0x0] & HARDWARE_SERIAL_STATUS_TXC))/* Check that transmit buffer is empty */
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

	config = this->_configTable;
	frame = config->FRAME[0x0];
	ms = 1000 * 0x8 * n * ((((frame & HARDWARE_SERIAL_FRAME_DATABITS_MASK) >> HARDWARE_SERIAL_FRAME_DATABITS_SHIFT) + 0x3) + 0x1 +
	((frame & HARDWARE_SERIAL_FRAME_STOPBITS_MASK) == HARDWARE_SERIAL_FRAME_STOPBITS_TWO ? 0x2 : 0x1) +
	((frame & HARDWARE_SERIAL_FRAME_PARITY_MASK) == HARDWARE_SERIAL_FRAME_PARITY_EVEN ? 0x1 : 0x0)) /
	((((frame & HARDWARE_SERIAL_FRAME_DATABITS_MASK) >> HARDWARE_SERIAL_FRAME_DATABITS_SHIFT) + 0x3) * this->_baudrate);
	ms = ms + ms / 100;//intercharacter spacing takes into account, or rather its absence
	return (ms);
}

void HardwareSerial::memset(uint8_t c, size_t n) {
	const ZunoHardwareSerialConfig_t			*config;
	ssize_t										channel;
	LdmaClassTransferSingle_t					array;

	config = this->_configTable;
	if (zunoSyncLockWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey) != ZunoErrorOk)
		return ;
	if ((channel = LdmaClass::transferSingle(&c, (void*)(config->TXDATA), n, config->dmaSignalWrite, ldmaCtrlSizeByte, ldmaCtrlSrcIncNone, ldmaCtrlDstIncNone, &array)) >= 0x0) {
		delay(this->countWaitingMs(n));
		while (!(config->STATUS[0x0] & HARDWARE_SERIAL_STATUS_TXC))/* Check that transmit buffer is empty */
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

	config = this->_configTable;
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
	config = serial->_configTable;
	if ((channel = serial->_channel) > 0x0) {
		LdmaClass::transferStop(channel);
		serial->_channel = -1;
	}
	#if EUSART_COUNT >= 1
	if (config->type == ZunoHardwareSerialTypeEusart)
		EUSART_Reset(config->eusart);
	#endif
	#if USART_COUNT >= 1
	if (config->type == ZunoHardwareSerialTypeUsart)
		USART_Reset(config->usart);
	#endif
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
	ZunoError_t									ret;
	ssize_t										channel;

	config = this->_configTable;
	if ((ret = zunoSyncOpen(config->lpLock, SyncMasterHadwareSerial, 0x0, 0x0, &this->_lpKey)) != ZunoErrorOk)
		return (this->_beginFaill(ret, bFree, b));
	CMU_ClockEnable(config->bus_clock, true);
	pinMode(tx, OUTPUT_UP);
	pinMode(rx, INPUT_PULLUP);
	if (this->_bFree == true)
		free(this->_buffer);
	this->_buffer = (uint8_t *)b;
	this->_buffer_len = len;
	this->_bFree = bFree;
	#if EUSART_COUNT >= 1
	if (config->type == ZunoHardwareSerialTypeEusart)
		this->_baudrate = this->_begin_eusart(config, baudrate, option, rx, tx);
	#endif
	#if USART_COUNT >= 1
	if (config->type == ZunoHardwareSerialTypeUsart)
		this->_baudrate = this->_begin_usart(config, baudrate, option, rx, tx);
	#endif
	#if USART_COUNT >= 1
	if (config->type == ZunoHardwareSerialTypeUsart)
		this->_baudrate = this->_begin_usart(config, baudrate, option, rx, tx);
	#endif
	if ((channel = this->_channel) > 0x0)
		LdmaClass::transferStop(channel);
	if (len != 0x0) {
		channel = LdmaClass::receivedCyclical((void *)config->RXDATA, b, len, config->dmaSignalRead, ldmaCtrlSizeByte, &this->_arrayReceivedCyclical);
		this->_channel = channel;
	}
	else
		this->_channel = -1;
	zunoSyncReleseWrite(config->lpLock, SyncMasterHadwareSerial, &this->_lpKey);
	if (len != 0x0 && channel < 0x0) {
		this->end();
		return (ZunoErrorDmaLimitChannel);
	}
	return (ZunoErrorOk);
}

#if EUSART_COUNT >= 1
uint32_t HardwareSerial::_begin_eusart(const ZunoHardwareSerialConfig_t *config, size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx) {
	uint32_t									databits;
	EUSART_UartInit_TypeDef						eusartInit;

	eusartInit = EUSART_UART_INIT_DEFAULT_HF;
	eusartInit.baudrate = baudrate;
	databits = (option & HARDWARE_SERIAL_FRAME_DATABITS_MASK);
	if (databits == HARDWARE_SERIAL_DATA_BITS_8)
		databits = EUSART_FRAMECFG_DATABITS_EIGHT;
	else
		databits = EUSART_FRAMECFG_DATABITS_NINE;
	eusartInit.databits = (EUSART_Databits_TypeDef)(databits);
	eusartInit.parity = (EUSART_Parity_TypeDef)(option & HARDWARE_SERIAL_FRAME_PARITY_MASK);
	eusartInit.stopbits = (EUSART_Stopbits_TypeDef)(option & HARDWARE_SERIAL_FRAME_STOPBITS_MASK);
	EUSART_UartInitHf(config->eusart, &eusartInit);
	GPIO->EUSARTROUTE[config->fd].TXROUTE = (getRealPort(tx) << _GPIO_EUSART_TXROUTE_PORT_SHIFT) | (getRealPin(tx) << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
	GPIO->EUSARTROUTE[config->fd].RXROUTE = (getRealPort(rx) << _GPIO_EUSART_RXROUTE_PORT_SHIFT) | (getRealPin(rx) << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
	GPIO->EUSARTROUTE[config->fd].ROUTEEN = GPIO_EUSART_ROUTEEN_RXPEN | GPIO_EUSART_ROUTEEN_TXPEN;
	return (EUSART_BaudrateGet(config->eusart));
}
#endif

#if USART_COUNT >= 1
uint32_t HardwareSerial::_begin_usart(const ZunoHardwareSerialConfig_t *config, size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx) {
	USART_InitAsync_TypeDef						usartInit;
	#if defined(USART_ROUTEPEN_TXPEN) && defined(USART_ROUTEPEN_RXPEN)
	const uint8_t								*location_ptr;
	size_t										location_sz;
	size_t 										rx_loc;
	size_t 										tx_loc;
	#endif

	usartInit = USART_INITASYNC_DEFAULT;
	usartInit.baudrate = baudrate;
	usartInit.databits = (USART_Databits_TypeDef)((option & HARDWARE_SERIAL_FRAME_DATABITS_MASK));
	usartInit.parity = (USART_Parity_TypeDef)(option & HARDWARE_SERIAL_FRAME_PARITY_MASK);
	usartInit.stopbits = (USART_Stopbits_TypeDef)(option & HARDWARE_SERIAL_FRAME_STOPBITS_MASK);
	USART_InitAsync(config->usart, &usartInit);
	#if defined(USART_ROUTEPEN_TXPEN) && defined(USART_ROUTEPEN_RXPEN)
	if (config->usart == USART2) {
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
	rx_loc = rx_loc ? rx_loc - 1 : MAX_VALID_PINLOCATION;// Now we have to shift rx location back, it always stands before tx location
	config->usart->ROUTELOC0 = tx_loc << _USART_ROUTELOC0_TXLOC_SHIFT | rx_loc << _USART_ROUTELOC0_RXLOC_SHIFT;
	config->usart->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
	#else
	GPIO->USARTROUTE[config->fd].TXROUTE = (getRealPort(tx) << _GPIO_USART_TXROUTE_PORT_SHIFT) | (getRealPin(tx) << _GPIO_USART_TXROUTE_PIN_SHIFT);
	GPIO->USARTROUTE[config->fd].RXROUTE = (getRealPort(rx) << _GPIO_USART_RXROUTE_PORT_SHIFT) | (getRealPin(rx) << _GPIO_USART_RXROUTE_PIN_SHIFT);
	GPIO->USARTROUTE[config->fd].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;
	#endif
	return (USART_BaudrateGet(config->usart));
}
#endif

/* Preinstantiate Objects */
	#if ZUNO_PIN_V == 802
	HardwareSerial Serial(ZunoHardwareSerialEusart0);
	HardwareSerial Serial1(ZunoHardwareSerialEusart2);
	HardwareSerial Serial0(ZunoHardwareSerialEusart1);
	#else
	HardwareSerial Serial(ZunoHardwareSerialUsart2);
	HardwareSerial Serial1(ZunoHardwareSerialUsart1);
	HardwareSerial Serial0(ZunoHardwareSerialUsart0);
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