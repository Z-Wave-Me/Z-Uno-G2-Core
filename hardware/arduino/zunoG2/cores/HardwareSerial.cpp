#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "ZDma.h"
#include "CrtxUSART.h"
#include "HardwareSerial.h"

#define HARDWARE_SERIAL_MIN_WRITE_ZDMA			2

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	#if ZUNO_PIN_V == 1
		#define HARDWARE_SERIAL0_RX				11
		#define HARDWARE_SERIAL0_TX				7

		#define HARDWARE_SERIAL1_RX				13
		#define HARDWARE_SERIAL1_TX				12

		#define HARDWARE_SERIAL2_RX				20
		#define HARDWARE_SERIAL2_TX				10
	#elif ZUNO_PIN_V == 2
		#define HARDWARE_SERIAL0_RX				25
		#define HARDWARE_SERIAL0_TX				24

		#define HARDWARE_SERIAL1_RX				8
		#define HARDWARE_SERIAL1_TX				7

		#define HARDWARE_SERIAL2_RX				26
		#define HARDWARE_SERIAL2_TX				27
	#elif ZUNO_PIN_V == 3
		#define HARDWARE_SERIAL0_RX				25
		#define HARDWARE_SERIAL0_TX				24

		#define HARDWARE_SERIAL1_RX				8
		#define HARDWARE_SERIAL1_TX				7

		#define HARDWARE_SERIAL2_RX				27
		#define HARDWARE_SERIAL2_TX				26
	#elif ZUNO_PIN_V == 4
		#define HARDWARE_SERIAL0_RX				25
		#define HARDWARE_SERIAL0_TX				24

		#define HARDWARE_SERIAL1_RX				8
		#define HARDWARE_SERIAL1_TX				7

		#define HARDWARE_SERIAL2_RX				27
		#define HARDWARE_SERIAL2_TX				26
	#else
		#error ZUNO_PIN_V
	#endif
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI
#else
	#error Set ZUNO_ASSEMBLY_TYPE
#endif

#define HARDWARE_SERIAL_UNIQ_ZDMA_WRITE			((size_t)&this->_numberConfig)
#define HARDWARE_SERIAL_UNIQ_ZDMA_READ			((size_t)&this->_baudrate)

typedef struct							ZunoHardwareSerialConfig_s
{
	USART_TypeDef						*usart;
	size_t								baudrate;
	ZDMA_PeripheralSignal_t				dmaSignalRead;
	ZDMA_PeripheralSignal_t				dmaSignalWrite;
	CMU_Clock_TypeDef					bus_clock;
	uint8_t								rx;
	uint8_t								tx;
}										ZunoHardwareSerialConfig_t;

static const ZunoHardwareSerialConfig_t		gConfig[3] = {
	{
		.usart = USART0,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART0_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART0_TXBL,
		.bus_clock = cmuClock_USART0,
		.rx = HARDWARE_SERIAL0_RX,
		.tx = HARDWARE_SERIAL0_TX
	},
	{
		.usart = USART1,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART1_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART1_TXBL,
		.bus_clock = cmuClock_USART1,
		.rx = HARDWARE_SERIAL1_RX,
		.tx = HARDWARE_SERIAL1_TX
	},
	{
		.usart = USART2,
		.baudrate = 115200,
		.dmaSignalRead = zdmaPeripheralSignal_USART2_RXDATAV,
		.dmaSignalWrite = zdmaPeripheralSignal_USART2_TXBL,
		.bus_clock = cmuClock_USART2,
		.rx = HARDWARE_SERIAL2_RX,
		.tx = HARDWARE_SERIAL2_TX
	}
};

HardwareSerial::HardwareSerial(uint8_t numberConfig): _numberConfig(0), _bLockUsart(false) {
	this->_numberConfig = numberConfig;
}

ZunoError_t HardwareSerial::begin(void) {
	return (this->begin(gConfig[this->_numberConfig].baudrate));
}

ZunoError_t HardwareSerial::begin(size_t baudrate) {
	const ZunoHardwareSerialConfig_t			*config;

	config = &gConfig[this->_numberConfig];
	return (this->begin(baudrate, config->rx, config->tx));
}

ZunoError_t HardwareSerial::begin(size_t baudrate, uint8_t rx, uint8_t tx) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	USART_InitAsync_TypeDef						usartInit;
	const uint8_t								*location;
	size_t										routeLocation;

	config = &gConfig[this->_numberConfig];
	usart = config->usart;
	switch ((size_t)usart) {
		case USART0_BASE:
			if (g_bit_field.bLockUsart0 == true && this->_bLockUsart == false)
				return (ZunoErrorResourceAlready);
			g_bit_field.bLockUsart0 = true;
			break ;
		case USART1_BASE:
			if (g_bit_field.bLockUsart1 == true && this->_bLockUsart == false)
				return (ZunoErrorResourceAlready);
			g_bit_field.bLockUsart1 = true;
			break ;
		case USART2_BASE:
			if (g_bit_field.bLockUsart2 == true && this->_bLockUsart == false)
				return (ZunoErrorResourceAlready);
			g_bit_field.bLockUsart2 = true;
			break ;
		default:
			return (ZunoErrorResourceAlready);
			break ;
	}
	this->_bLockUsart = true;
	CMU_ClockEnable(config->bus_clock, true);
	pinMode(tx, OUTPUT_UP);
	pinMode(rx, INPUT_DOWN);
	usartInit = USART_INITASYNC_DEFAULT;
	usartInit.baudrate = baudrate;
	this->_baudrate = baudrate;
	USART_InitAsync(usart, &usartInit);
	if (usart == USART2) {
		location = &g_loc_pf0_pf1_pf3_pf7[0];
		routeLocation = (((((getRealPort(tx) << 4) | getRealPin(tx)) == 5) ? 0 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), tx) + 14) << _USART_ROUTELOC0_TXLOC_SHIFT) | (((((getRealPort(rx) << 4) | getRealPin(rx)) == 5) ? 31 : getLocation(location, sizeof(g_loc_pf0_pf1_pf3_pf7), rx) + 13) << _USART_ROUTELOC0_RXLOC_SHIFT);
	}
	else {
		location = &g_loc_pa0_pf7_all[0];
		routeLocation = ((getLocation(location, sizeof(g_loc_pa0_pf7_all), tx)) << _USART_ROUTELOC0_TXLOC_SHIFT) | (((getLocation(location, sizeof(g_loc_pa0_pf7_all), rx) - 1) % sizeof(g_loc_pa0_pf7_all)) << _USART_ROUTELOC0_RXLOC_SHIFT);
	}
	usart->ROUTELOC0 = routeLocation;
	usart->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
	return (ZunoErrorOk);
}

void HardwareSerial::end() {
	if (this->_bLockUsart == false)
		return ;
	USART_Reset(gConfig[this->_numberConfig].usart);
}

size_t HardwareSerial::available(void) {
	return (size_t) zunoSysCall(ZUNO_FUNC_SERIAL_AVAILABLE, 1, serial_num);
}

int HardwareSerial::peek(void) {
	int peekval;
	if(!zunoSysCall(ZUNO_FUNC_SERIAL_AVAILABLE, serial_num)) 
		return -1;
	zunoSysCall(ZUNO_FUNC_SERIAL_READ, 4, serial_num, false, &peekval, 1);
	return peekval;
}
uint8_t HardwareSerial::read(void) {
	uint8_t readval;
	zunoSysCall(ZUNO_FUNC_SERIAL_READ, 4, serial_num, true, &readval, 1);
	return readval;
}

size_t HardwareSerial::printf(const char *format, ...) {
	va_list				args;

	va_start (args, format);
	vdprintf(this->_numberConfig, format, args);
	va_end (args);
	return (0);
}

uint8_t HardwareSerial::write(uint8_t value) {
	if (this->_bLockUsart == false)
		return (0);
	USART_Tx(gConfig[this->_numberConfig].usart, value);
	return (1);
}

uint8_t HardwareSerial::write(unsigned long value) {
	return (this->write((uint8_t)value));
}

uint8_t HardwareSerial::write(long value) {
	return (this->write((uint8_t)value));
}

uint8_t HardwareSerial::write(unsigned int value) {
	return (this->write((uint8_t)value));
}

uint8_t HardwareSerial::write(int value) { 
	return (this->write((uint8_t)value));
}

size_t HardwareSerial::write(const uint8_t *b, size_t count) {
	const ZunoHardwareSerialConfig_t			*config;
	USART_TypeDef								*usart;
	const uint8_t								*e;
	size_t										baudrate;

	if (this->_bLockUsart == false)
		return (0);
	config = &gConfig[this->_numberConfig];
	usart = config->usart;
	if (count > HARDWARE_SERIAL_MIN_WRITE_ZDMA && ZDMA.toMemoryPeripheral(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE, config->dmaSignalWrite, (void*)&(usart->TXDATA), (void *)b, count, zdmaData8) == ZunoErrorOk) {
		baudrate = this->_baudrate / 1000;
		if (baudrate != 0)
			baudrate = baudrate * 8 / baudrate;
		delay((baudrate == 0)? 1 : baudrate);
		while (ZDMA.isProcessing(HARDWARE_SERIAL_UNIQ_ZDMA_WRITE) == true)
			__NOP();
		while (!(usart->STATUS & USART_STATUS_TXBL))/* Check that transmit buffer is empty */
			__NOP();
	}
	else {
		e = b + count;
		while (b < e)
			this->write(b++[0]);
	}
	return (count);
}

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