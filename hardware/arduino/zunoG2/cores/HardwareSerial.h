#ifndef _ZUNO_HARDWARE_SERIAL_H
#define _ZUNO_HARDWARE_SERIAL_H

#include "Arduino.h"
#include "Stream.h"
#include "stdio.h"
#include "LdmaClass.h"
#include "Sync.h"
#include "em_device.h"
#include "em_cmu.h"
#include "em_eusart.h"
#include "em_usart.h"

#define HARDWARE_SERIAL_SPEED_DEFAULT							115200
#define HARDWARE_SERIAL_CONFIG(databits, parity, stopbits)		(databits | parity | stopbits)

#define HARDWARE_SERIAL_DATA_BITS_8									(0x00000005UL << 0)
#define HARDWARE_SERIAL_DATA_BITS_9									(0x00000006UL << 0)
#define HARDWARE_SERIAL_NO_PARIRY									(0x00000000UL << 8)
#define HARDWARE_SERIAL_EVEN_PARIRY									(0x00000002UL << 8)
#define HARDWARE_SERIAL_ODD_PARIRY									(0x00000003UL << 8)
#define HARDWARE_SERIAL_STOP_BITS_1									(0x00000001UL << 12)
#define HARDWARE_SERIAL_STOP_BITS_2									(0x00000003UL << 12)

#define SERIAL_8N1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_NO_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_9N1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_NO_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_8N2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_NO_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)
#define SERIAL_9N2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_NO_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)
#define SERIAL_8E1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_EVEN_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_9E1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_EVEN_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_8E2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_EVEN_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)
#define SERIAL_9E2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_EVEN_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)
#define SERIAL_8O1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_ODD_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_9O1								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_ODD_PARIRY, HARDWARE_SERIAL_STOP_BITS_1)
#define SERIAL_8O2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_8, HARDWARE_SERIAL_ODD_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)
#define SERIAL_9O2								HARDWARE_SERIAL_CONFIG(HARDWARE_SERIAL_DATA_BITS_9, HARDWARE_SERIAL_ODD_PARIRY, HARDWARE_SERIAL_STOP_BITS_2)

typedef enum							ZunoHardwareSerialType_s
{
	#if EUSART_COUNT >= 1
	ZunoHardwareSerialTypeEusart,
	#endif
	ZunoHardwareSerialTypeUsart,
}										ZunoHardwareSerialType_t;

typedef struct							ZunoHardwareSerialConfig_s
{
	union
	{
		#if EUSART_COUNT >= 1
		EUSART_TypeDef						*eusart;
		#endif
		#if USART_COUNT >= 1
		USART_TypeDef						*usart;
		#endif
	};
	volatile uint32_t					*TXDATA;
	volatile uint32_t					*FRAME;
	volatile const uint32_t				*RXDATA;
	volatile const uint32_t				*STATUS;
	ZunoSync_t							*lpLock;
	LDMA_PeripheralSignal_t				dmaSignalWrite;
	LDMA_PeripheralSignal_t				dmaSignalRead;
	CMU_Clock_TypeDef					bus_clock;
	uint8_t								rx;
	uint8_t								tx;
	uint8_t								fd;
	ZunoHardwareSerialType_t			type;
}										ZunoHardwareSerialConfig_t;

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

class HardwareSerial : public Stream {
	public:
		HardwareSerial(ZunoHardwareSerialNumConfig_t numberConfig);
		void									begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
		void									begin(unsigned long baud, uint32_t config);
		void									begin(void) {return (this->begin(HARDWARE_SERIAL_SPEED_DEFAULT));};
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx);
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx, void *buffer, uint16_t len);
		void									end();
		virtual int								available(void);
		virtual int								peek(void);
		virtual int								read(void);
		virtual int								availableForWrite(void) {return (0x10);};
		virtual void							flush(void) {};
		virtual size_t							write(uint8_t value) {return (this->write((const uint8_t *)&value, 1));};
		inline size_t							write(unsigned long n) { return write((uint8_t)n); }
		inline size_t							write(long n) { return write((uint8_t)n); }
		inline size_t							write(unsigned int n) { return write((uint8_t)n); }
		inline size_t							write(int n) { return write((uint8_t)n); }
		
		void									memset(uint8_t c, size_t n);//max 2048 * 255
		
		virtual size_t							write(const uint8_t *b, size_t count);

		size_t									countWaitingMs(size_t n);

	private:
		#if EUSART_COUNT >= 1
		inline uint32_t							_begin_eusart(const ZunoHardwareSerialConfig_t *config, size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx);
		#endif
		#if USART_COUNT >= 1
		uint32_t								_begin_usart(const ZunoHardwareSerialConfig_t *config, size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx);
		#endif
		inline int								_readLock(uint8_t bOffset);
		inline ZunoError_t						_begin(size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx, void *b, size_t len, uint8_t bFree);
		inline ZunoError_t						_beginFaill(ZunoError_t ret, uint8_t bFree, void *b);
		static ZunoError_t						_deInit(size_t param);
		const ZunoHardwareSerialConfig_t		*_configTable;
		uint8_t									*_buffer;
		uint32_t								_baudrate;
		ssize_t									_channel;
		LdmaClassReceivedCyclical_t				_arrayReceivedCyclical;
		uint16_t								_buffer_len;
		uint8_t									_lpKey;
		uint8_t									_bFree;
};

extern HardwareSerial Serial;
extern HardwareSerial Serial0;
extern HardwareSerial Serial1;

#endif // _ZUNO_HARDWARE_SERIAL_H