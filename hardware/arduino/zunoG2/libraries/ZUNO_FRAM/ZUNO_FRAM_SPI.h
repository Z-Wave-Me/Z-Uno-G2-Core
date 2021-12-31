//ZUNO_FRAM_SPI.h

#ifndef ZUNO_FRAM_SPI_h
#define ZUNO_FRAM_SPI_h

#include "Arduino.h"

#define FRAM_CMD_WREN  0x06		// Write Enable Latch
#define FRAM_CMD_WRDI  0x04		// Reset Write Enable Latch
#define FRAM_CMD_RDSR  0x05		// Read Status Register
#define FRAM_CMD_RDCR  0x15		// Read Configuration Register
#define FRAM_CMD_WRSR  0x01		// Write Status Register
#define FRAM_CMD_DP    0xB9		// Write Deep Power Down
#define FRAM_CMD_WRITE 0x02		// Write Memory
#define FRAM_CMD_READ  0x03		// Read Memory
#define FRAM_CMD_FREAD 0x0B		// Fast Read Memory 
#define FRAM_CMD_CE    0xC7		// Chip Erase
#define FRAM_CMD_RDID  0x9F		// Read Device Manufacturer ID 

#define SPI_CLOCK 8000000
#define SPI_MODE SPI_MODE0
#define SPI_BITORDER MSBFIRST

#define FRAM FRAM1

class ZUNO_FRAM_SPI
{
  public:
	ZUNO_FRAM_SPI();
	ZUNO_FRAM_SPI(uint32_t);			// predefined size (bytes)
	void init(byte);					// CS pin
	byte read(uint32_t);				// address , read one byte
	void get(uint32_t, byte*, uint16_t);	// address, buffer, number of bytes to read
	void write(uint32_t, byte);			// address , write one byte
	void put(uint32_t, byte*, uint16_t);	// address, buffer, number of bytes to write
	void update(uint32_t, byte);		// address, bytes to update
	void clearFRAM();					// clear all FRAM
	void clear(uint32_t, byte, uint16_t);	// address, byte to write, number of bytes 
	void setWriteEnableBit(bool);		// set bit for write enable
	bool getWriteEnableBit(void);		// get bit for write enable
	
	uint32_t _fram_Size; //Speichergroesse in Byte
	uint32_t& Size=_fram_Size;

  private:
	void readSize();
	void setWriteEnableLatch(bool);
	
	byte _cs;
	bool _writeEnableBit = true;
	byte _addressSize=2;
};

extern ZUNO_FRAM_SPI FRAM1;

#endif
