#ifndef _ZUNO_HARDWARE_SERIAL_H
#define _ZUNO_HARDWARE_SERIAL_H

#include "Stream.h"
#include "stdio.h"
#include "LdmaClass.h"
#include "Sync.h"
#include "CrtxUSART.h"

#define HARDWARE_SERIAL_SPEED_DEFAULT							115200
#define HARDWARE_SERIAL_CONFIG(databits, parity, stopbits)		(databits | parity | stopbits)

#define SERIAL_8N1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_NONE, USART_FRAME_STOPBITS_ONE)
#define SERIAL_9N1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_NONE, USART_FRAME_STOPBITS_ONE)
#define SERIAL_8N2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_NONE, USART_FRAME_STOPBITS_TWO)
#define SERIAL_9N2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_NONE, USART_FRAME_STOPBITS_TWO)
#define SERIAL_8E1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_EVEN, USART_FRAME_STOPBITS_ONE)
#define SERIAL_9E1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_EVEN, USART_FRAME_STOPBITS_ONE)
#define SERIAL_8E2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_EVEN, USART_FRAME_STOPBITS_TWO)
#define SERIAL_9E2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_EVEN, USART_FRAME_STOPBITS_TWO)
#define SERIAL_8O1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_ODD, USART_FRAME_STOPBITS_ONE)
#define SERIAL_9O1								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_ODD, USART_FRAME_STOPBITS_ONE)
#define SERIAL_8O2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_EIGHT, USART_FRAME_PARITY_ODD, USART_FRAME_STOPBITS_TWO)
#define SERIAL_9O2								HARDWARE_SERIAL_CONFIG(USART_FRAME_DATABITS_NINE, USART_FRAME_PARITY_ODD, USART_FRAME_STOPBITS_TWO)

typedef struct							ZunoHardwareSerialConfig_s
{
	USART_TypeDef						*usart;
	ZunoSync_t							*lpLock;
	LdmaClassSignal_t					dmaSignalWrite;
	LdmaClassSignal_t					dmaSignalRead;
	CMU_Clock_TypeDef					bus_clock;
	uint8_t								rx;
	uint8_t								tx;
}										ZunoHardwareSerialConfig_t;

class HardwareSerial : public Stream {
	public:
		HardwareSerial(uint8_t numberConfig);
		void									begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
		void									begin(unsigned long baud, uint32_t config);
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
		void									begin(void) {return (this->begin(HARDWARE_SERIAL_SPEED_DEFAULT));};
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx);
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx, void *buffer, uint16_t len);
		virtual size_t							write(const uint8_t *b, size_t count);

	private:
		inline int								_readLock(uint8_t bOffset);
		inline ZunoError_t						_begin(size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx, void *b, size_t len, uint8_t bFree);
		inline ZunoError_t						_beginFaill(ZunoError_t ret, uint8_t bFree, void *b);
		static ZunoError_t						_deInit(size_t param);
		static const ZunoHardwareSerialConfig_t	_configTable[];
		uint8_t									*_buffer;
		uint32_t								_baudrate;
		ssize_t									_channel;
		LdmaClassReceivedCyclical_t				_arrayReceivedCyclical;
		uint16_t								_buffer_len;
		uint8_t									_lpKey;
		uint8_t									_numberConfig;
		uint8_t									_bFree;
};

extern HardwareSerial Serial;
extern HardwareSerial Serial0;
extern HardwareSerial Serial1;

#endif // _ZUNO_HARDWARE_SERIAL_H