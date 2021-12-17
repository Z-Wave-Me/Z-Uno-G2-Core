#ifndef LE_UART_H
#define LE_UART_H

#include "Stream.h"
#include "stdio.h"
#include "LdmaClass.h"
#include "Sync.h"
#include "CrtxLeuart.h"

#define LE_UART_SPEED_DEFAULT							1200
#define LE_UART_CONFIG(databits, parity, stopbits)		(databits | parity | stopbits)

#define LE_UART_SERIAL_8N1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_NONE, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_9N1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_NONE, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_8N2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_NONE, LEUART_CTRL_STOPBITS_TWO)
#define LE_UART_SERIAL_9N2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_NONE, LEUART_CTRL_STOPBITS_TWO)
#define LE_UART_SERIAL_8E1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_EVEN, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_9E1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_EVEN, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_8E2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_EVEN, LEUART_CTRL_STOPBITS_TWO)
#define LE_UART_SERIAL_9E2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_EVEN, LEUART_CTRL_STOPBITS_TWO)
#define LE_UART_SERIAL_8O1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_ODD, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_9O1								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_ODD, LEUART_CTRL_STOPBITS_ONE)
#define LE_UART_SERIAL_8O2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_EIGHT, LEUART_CTRL_PARITY_ODD, LEUART_CTRL_STOPBITS_TWO)
#define LE_UART_SERIAL_9O2								LE_UART_CONFIG(LEUART_CTRL_DATABITS_NINE, LEUART_CTRL_PARITY_ODD, LEUART_CTRL_STOPBITS_TWO)

class LeUartClass : public Stream {
	public:
		LeUartClass(void);
		void									begin(unsigned long baud) { begin(baud, LE_UART_SERIAL_8N1); }
		void									begin(unsigned long baud, uint32_t config) {this->begin(baud, config, RX0, TX0);};
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

		void									begin(void) {return (this->begin(LE_UART_SPEED_DEFAULT));};
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx);
		ZunoError_t								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx, void *buffer, uint16_t len) {return (this->_begin(speed, config, rx, tx, buffer, len, false));};
		void									wakeUp(uint16_t value) {return (this->_wakeUp(value));};
		void									wakeUp(void) {return (this->_wakeUp((size_t)-1));};
		void									wakeUpDisabled(void);
		void									startFrame(uint16_t value);
		void									startFrameDisabled(void);
		virtual size_t							write(const uint8_t *b, size_t count);

	private:
		void									_wakeUp(size_t value);
		inline int								_readLock(uint8_t bOffset);
		ZunoError_t								_begin(size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx, void *b, size_t len, uint8_t bFree);
		inline ZunoError_t						_beginFaill(ZunoError_t ret, uint8_t bFree, void *b);
		static ZunoError_t						_deInit(size_t param);
		uint8_t									*_buffer;
		uint32_t								_baudrate;
		ssize_t									_channel;
		LdmaClassReceivedCyclical_t				_arrayReceivedCyclical;
		uint16_t								_buffer_len;
		uint8_t									_lpKey;
		uint8_t									_bFree;
};

extern LeUartClass LeUart;


#endif // LE_UART_H