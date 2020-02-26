#ifndef _ZUNO_HARDWARE_SERIAL_H
#define _ZUNO_HARDWARE_SERIAL_H

#include "Stream.h"

class HardwareSerial : public Stream {
	
	private:
		
		byte serial_num;
		ZUNOUARTOptions_t uart_conf;

	public:

		HardwareSerial(byte number, byte rx, byte tx);  // bfn = like ZUNO_FUNC_SERIAL1_BEGIN

		void begin(DWORD baudrate = 115200);
    	void begin(DWORD baudrate, byte, byte);
    	void end();
    	virtual size_t available(void);
    	virtual int peek(void);
    	virtual uint8_t read(void);
   		//virtual void flush(void);

    	virtual size_t write(uint8_t);

    	uint8_t write(unsigned long n) {  write((uint8_t)n); return 1; }
    	uint8_t write(long n) { write((uint8_t)n); return 1; }
    	uint8_t write(unsigned int n) { write((uint8_t)n); return 1; }
    	uint8_t write(int n) { write((uint8_t)n); return 1; }


};

extern HardwareSerial Serial;
extern HardwareSerial Serial0;
extern HardwareSerial Serial1;

#endif // _ZUNO_HARDWARE_SERIAL_H