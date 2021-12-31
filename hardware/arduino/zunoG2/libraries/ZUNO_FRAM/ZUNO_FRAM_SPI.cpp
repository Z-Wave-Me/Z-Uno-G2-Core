#include "Arduino.h"
#include "ZUNO_FRAM_SPI.h"
#include "SPI.h"

/**************************************************************************/
/*!
		SPI-FRAM library version 1.0 for Z-UnoG2 
*/
/**************************************************************************/
/*!
		@brief  different supported types from documentation
*/
/**************************************************************************/
// 
const struct {
  uint8_t ManufID; // Manufacturer ID
  uint16_t ProdID; // Product ID
  uint32_t MemSize;   // kBytes
} supported_devices[] = {
    // Fujitsu from datasheet
    {0x04, 0x0101, 2},   // MB85RS16
    {0x04, 0x0302, 8},   // MB85RS64V
    {0x04, 0x2303, 8},   // MB85RS64T
    {0x04, 0x2503, 32},  // MB85RS256TY
    {0x04, 0x4803, 256}, // MB85RS2MTA
    {0x04, 0x4903, 512}, // MB85RS4MT
};
//
/**************************************************************************/
/*!
		@brief  Instantiates a new SPI FRAM class with
				optional definition of memory size (not needed in normal case)
		@param  memory size in kbytes
		@returns nothing
*/
/**************************************************************************/
//
ZUNO_FRAM_SPI::ZUNO_FRAM_SPI(uint32_t fram_Size_byte)
{
  _fram_Size = fram_Size_byte; 		
}

ZUNO_FRAM_SPI::ZUNO_FRAM_SPI()
{
  _fram_Size = 0;
}
//
/**************************************************************************/
/*!
		@brief  Setup the FRAM module
		@param  CS pin connected to module
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::init(byte cs)   // CS pin
{
  _cs = cs;
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPI_CLOCK, MSBFIRST, SPI_MODE);
  if (_fram_Size == 0) readSize();
}
//
/**************************************************************************/
/*!
		@brief  Read the size from module using the device table above, define the address size
		@param  none
		@returns nothing, set the internal _fram_Size (identical with .Size property)
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::readSize()
{
  uint16_t _size_kBit ;
  uint8_t a[4]; 
  uint8_t b[2]; 
  
  digitalWrite(_cs, LOW);
  SPI.transfer(FRAM_CMD_RDID);
  SPI.transfer(a,4);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
  byte manufacturerID = (a[0]);
  word productID = (a[2] << 8) + a[3];
  int devtype_len = sizeof(supported_devices)/sizeof(supported_devices[0]);
    for (uint8_t i = 0; i< devtype_len; i++) {
		if (manufacturerID == supported_devices[i].ManufID && productID == supported_devices[i].ProdID){
        _fram_Size = supported_devices[i].MemSize * 1024;
		if(_fram_Size> 70000) _addressSize=3;
    }
   }
  digitalWrite(_cs, LOW);
  SPI.transfer(0x05);
  SPI.transfer(b,2);
  SPI.endTransaction();
}
//
/**************************************************************************/
/*!
		@brief  Read one byte from FRAM at given address
		@param  Address to be read
		@returns result (one byte)
*/
/**************************************************************************/
//
byte ZUNO_FRAM_SPI::read(uint32_t framAddress)
{ 
  byte val;
  uint8_t spibuf[6];
   
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_READ);
  if (_addressSize == 3) spibuf[1] = (uint8_t)(framAddress >> 16);
  spibuf[_addressSize-1] = (uint8_t)(framAddress >> 8);
  spibuf[_addressSize] = (uint8_t)(framAddress & 0xFF);
  SPI.transfer(spibuf,_addressSize+1);
  val= SPI.transfer(0);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
  return val;
}
//
/**************************************************************************/
/*!
		@brief  Write one byte at FRAM at given address
		@param  Adress to write
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::write(uint32_t framAddress, byte val)
{
  uint8_t spibuf[6];

  if (framAddress >= _fram_Size) return;

  setWriteEnableLatch(_writeEnableBit);
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_WRITE);
  if (_addressSize == 3) spibuf[1] = (uint8_t)(framAddress >> 16);
  spibuf[_addressSize-1] = (uint8_t)(framAddress >> 8);
  spibuf[_addressSize] = (uint8_t)(framAddress & 0xFF);
  spibuf[_addressSize+1] = val;
  SPI.transfer(spibuf,_addressSize+2);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
}
//
/**************************************************************************/
/*!
		@brief  Get an byte array from FRAM at given address
		@param  Adress to read, target buffer, number of bytes
		@returns nothing, result will be in given buffer
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::get(uint32_t framAddress, byte* buffer, uint16_t number)
{
  uint8_t spibuf[6];
   
  if (framAddress >= _fram_Size) return;
  if (framAddress + number > _fram_Size) return;

  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_READ);
  if (_addressSize == 3) spibuf[1] = (uint8_t)(framAddress >> 16);
  spibuf[_addressSize-1] = (uint8_t)(framAddress >> 8);
  spibuf[_addressSize] = (uint8_t)(framAddress & 0xFF);
  SPI.transfer(spibuf,_addressSize+1);
  SPI.transfer(buffer,number);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
}
//
/**************************************************************************/
/*!
		@brief  write an byte array at FRAM from given address on
		@param  Adress to write, buffer (pointer), number of bytes
		@returns nothing, buffer will be overwritten!
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::put(uint32_t framAddress, byte* buffer, uint16_t number)
{
  if (framAddress >= _fram_Size) return;
  if (framAddress + number > _fram_Size) return;

  uint8_t spibuf[6];
 
  setWriteEnableLatch(_writeEnableBit);
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_WRITE);
  if (_addressSize == 3) spibuf[1] = (uint8_t)(framAddress >> 16);
  spibuf[_addressSize-1] = (uint8_t)(framAddress >> 8);
  spibuf[_addressSize] = (uint8_t)(framAddress & 0xFF);
  SPI.transfer(spibuf,_addressSize+1);
  SPI.transfer(buffer,number);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
}
//
/**************************************************************************/
/*!
		@brief  Clear the full FRAM (chip erase)
		@param  nothing
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::clearFRAM(void)
{
  if (_fram_Size == 0) return;

  uint8_t spibuf[6];
  uint8_t clearbuf[200];
 
  setWriteEnableLatch(_writeEnableBit);
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_WRITE);
  if (_addressSize == 3) spibuf[1] = 0;
  spibuf[_addressSize-1] = 0;
  spibuf[_addressSize] = 0;
  SPI.transfer(spibuf,_addressSize+1);
  for(int ci=0; ci < _fram_Size; ci+=200) {
    for(int ai=0; ai<200; ai++) clearbuf[ai]= 0xFF;
    if(ci+200 < _fram_Size) SPI.transfer(clearbuf, 200);
    else SPI.transfer(clearbuf,_fram_Size-ci);
  }
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
} 

// suggested chip erase from manual did not work in my case:
/* {
  setWriteEnableLatch(_writeEnableBit);
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  SPI.transfer(FRAM_CMD_CE);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
}  */
//
/**************************************************************************/
/*!
		@brief  Clear the given size of FRAM
		@param  Start-address, byte to write, number of bytes
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::clear(uint32_t framAddress, byte cbyte, uint16_t cnumber)
{
  if (framAddress >= _fram_Size) return;
  if (framAddress + cnumber > _fram_Size) return;

  uint8_t spibuf[6];
  uint8_t clearbuf[200];
 
  setWriteEnableLatch(_writeEnableBit);
  digitalWrite(_cs, LOW);
  SPI.beginTransaction();
  spibuf[0]=(FRAM_CMD_WRITE);
  if (_addressSize == 3) spibuf[1] = (uint8_t)(framAddress >> 16);
  spibuf[_addressSize-1] = (uint8_t)(framAddress >> 8);
  spibuf[_addressSize] = (uint8_t)(framAddress & 0xFF);
  SPI.transfer(spibuf,_addressSize+1);
  for(int ci=0; ci < cnumber; ci+=200) {
    for(int ai=0; ai<200; ai++) clearbuf[ai]= cbyte;
    if(ci+200 < cnumber) SPI.transfer(clearbuf, 200);
    else SPI.transfer(clearbuf,cnumber-ci);
  }
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
} 
//
/**************************************************************************/
/*!
		@brief  (internal) Set the write enable state of the FRAM module
		@param  true - enabled / false - forbidden
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::setWriteEnableLatch(bool _writeEnableBit)
{
  digitalWrite(_cs, LOW);
  SPI.beginTransaction(SPISettings());
  if (_writeEnableBit) SPI.transfer(FRAM_CMD_WREN);
  else SPI.transfer(FRAM_CMD_WRDI);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
 
}
//
/**************************************************************************/
/*!
		@brief  Set the write enable bit for protecting FRAM
		@param  true - enabled / false - forbidden
		@returns nothing
*/
/**************************************************************************/
//
void ZUNO_FRAM_SPI::setWriteEnableBit(bool writeEnableBit)
{
  _writeEnableBit=writeEnableBit;
}
//
/**************************************************************************/
/*!
		@brief  Get the write enable bit for protecting FRAM
		@param  -
		@returns the Bit: true - enabled / false - forbidden
*/
/**************************************************************************/
//
bool ZUNO_FRAM_SPI::getWriteEnableBit()
{
  return _writeEnableBit;
}

ZUNO_FRAM_SPI FRAM = ZUNO_FRAM_SPI();
