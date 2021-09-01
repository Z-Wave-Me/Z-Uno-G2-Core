#ifndef SPI_H
#define SPI_H

#include "CrtxUSART.h"
#include "Sync.h"
#include "LdmaClass.h"

#define SPI				SPI1

#define SPI_MODE0		usartClockMode0
#define SPI_MODE1		usartClockMode1
#define SPI_MODE2		usartClockMode2
#define SPI_MODE3		usartClockMode3

#define MSBFIRST		true
#define LSBFIRST		false

#define SPI_INIT_DEFAULT					{usartEnable, 0, 1000000, usartDatabits8, true, MSBFIRST, SPI_MODE0, false, usartPrsRxCh0, false, false, 0, 0}

#define SPI_FLAGS_CONST				0x1
#define SPI_FLAGS_16BIT				0x2

typedef struct								ZunoSpiUsartTypeConfig_s
{
	USART_TypeDef							*usart;
	ZunoSync_t								*lpLock;
	LdmaClassSignal_t						dmaSignalWrite;
	LdmaClassSignal_t						dmaSignalRead;
	CMU_Clock_TypeDef						bus_clock;
	uint8_t									sck;
	uint8_t									miso;
	uint8_t									mosi;
	uint8_t									ss;
}											ZunoSpiUsartTypeConfig_t;

class SPISettings {
	public:
		SPISettings(void);
		SPISettings(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode);

	private:
		uint32_t							clock;
		uint8_t								bitOrder;
		USART_ClockMode_TypeDef				dataMode;

	friend class SPIClass;
};

class SPIClass {
	public:
		SPIClass(uint8_t numberConfig);
		void												begin(void);
		void												beginTransaction(SPISettings spi_setings) {this->beginTransaction(spi_setings.clock, spi_setings.bitOrder, spi_setings.dataMode);};
		inline void											end(void) {zunoSyncClose(this->_config->lpLock, SyncMasterSpi, this->_deInit, (size_t)this, &this->_lpKey);};
		void												endTransaction(void);
		inline uint8_t										transfer(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline ZunoError_t									transfer(void *buffer) {return(this->transfer((char *)buffer));};
		inline uint16_t										transfer16(uint16_t data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};
		void												setBitOrder(uint8_t order);
		inline void											setDataMode(USART_ClockMode_TypeDef mode) {this->setDataMode(mode, this->_ss_pin);};
		void												setDataMode(USART_ClockMode_TypeDef mode, uint8_t slaveSelectPin);

		ZunoError_t											begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);
		inline void											beginTransaction(SPISettings *spi_setings) {this->beginTransaction(spi_setings->clock, spi_setings->bitOrder, spi_setings->dataMode);};
		inline void											beginTransaction(void) {this->beginTransaction(1000000, MSBFIRST, SPI_MODE0);};
		void												beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode);
		inline ZunoError_t									transfer(const void *buffer, size_t count) { return(this->_transfer((void *)buffer, count, SPI_FLAGS_CONST));};
		inline ZunoError_t									transfer(const void *buffer) {return(this->transfer((char *)buffer));};
		inline ZunoError_t									transfer(const char *buffer) {return(this->_transferStrlen((void *)buffer, SPI_FLAGS_CONST));};
		inline ZunoError_t									transfer(void *buffer, size_t count) {return(this->_transfer((void *)buffer, count, 0));};
		inline ZunoError_t									transfer(char *buffer) {return(this->_transferStrlen((void *)buffer, 0));};
		inline uint8_t										transfer8(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint8_t										transfer8(int data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint16_t										transfer16(int data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};

	private:
		size_t												_transferDate(size_t data, size_t bFlags);
		ZunoError_t											_transferStrlen(void *b, size_t bFlags);
		ZunoError_t											_transfer(void *b, size_t count, size_t bFlags);
		static ZunoError_t									_init(size_t param);
		static ZunoError_t									_deInit(size_t param);
		static const ZunoSpiUsartTypeConfig_t				_configTable0;
		static const ZunoSpiUsartTypeConfig_t				_configTable1;
		static const ZunoSpiUsartTypeConfig_t				_configTable2;
		static const USART_InitSync_TypeDef					_initSpi;
		const ZunoSpiUsartTypeConfig_t						*_config;
		size_t												_baudrate;
		uint8_t												_ss_pin;
		volatile uint8_t									_lpKey;
};

extern SPIClass SPI0;
extern SPIClass SPI1;
extern SPIClass SPI2;

#endif// SPI_H