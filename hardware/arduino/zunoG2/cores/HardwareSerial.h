#ifndef _ZUNO_HARDWARE_SERIAL_H
#define _ZUNO_HARDWARE_SERIAL_H

#include "Stream.h"
#include "stdio.h"
#include "ZDma_define.h"
#include "Sync.h"
#include "CrtxUSART.h"

typedef uint16_t hardware_serial_buffer_len;

typedef struct							ZunoHardwareSerialConfig_s
{
	USART_TypeDef						*usart;
	void								*IRQHandler;
	ZunoSync_t							*lpLock;
	size_t								baudrate;
	ZDMA_PeripheralSignal_t				dmaSignalRead;
	ZDMA_PeripheralSignal_t				dmaSignalWrite;
	CMU_Clock_TypeDef					bus_clock;
	IRQn_Type							irqType;
	uint8_t								subType;
	uint8_t								rx;
	uint8_t								tx;
}										ZunoHardwareSerialConfig_t;

class HardwareSerial : public Stream {
	public:
		HardwareSerial(uint8_t numberConfig);
		ZunoError_t								begin(void);
		ZunoError_t								begin(size_t baudrate);
		ZunoError_t								begin(size_t baudrate, uint8_t rx, uint8_t tx);
		ZunoError_t								begin(size_t baudrate, uint8_t rx, uint8_t tx, void *b, hardware_serial_buffer_len len);
		void									end();
		ssize_t									printf(const char *format, ...);
		uint8_t									write(unsigned long value);
		uint8_t									write(long value);
		uint8_t									write(unsigned int value);
		uint8_t									write(int value);
		virtual uint8_t							write(uint8_t value);
		virtual size_t							write(const uint8_t *b, size_t count);
		virtual size_t							available(void);
		virtual int								peek(void);
		virtual int								read(void);
	private:
		inline size_t							_available(void);
		inline int								_readLock(uint8_t bOffset);
		inline int								_read(uint8_t bOffset);
		inline ZunoError_t						_begin(size_t baudrate, uint8_t rx, uint8_t tx, void *b, hardware_serial_buffer_len len, uint8_t bFree);
		static ZunoError_t						_init(size_t param);
		static void								_deInit(size_t param);
		static void								_USART0_IRQHandler(size_t flags);
		static void								_USART1_IRQHandler(size_t flags);
		static void								_USART2_IRQHandler(size_t flags);
		inline void								_USART_IRQHandler(size_t flags);
		static const ZunoHardwareSerialConfig_t	_configTable[3];
		uint8_t									*_buffer;
		hardware_serial_buffer_len				_buffer_len;
		hardware_serial_buffer_len				_buffer_count;
		hardware_serial_buffer_len				_buffer_count_read;
		uint8_t									_numberConfig;
		uint8_t									_bFree;
};

extern HardwareSerial Serial;
extern HardwareSerial Serial0;
extern HardwareSerial Serial1;

#endif // _ZUNO_HARDWARE_SERIAL_H