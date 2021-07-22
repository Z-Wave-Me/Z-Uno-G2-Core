#ifndef SPI_H
#define SPI_H
#include "Sync.h"

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
	ZDMA_PeripheralSignal_t					dmaSignalWrite;
	ZDMA_PeripheralSignal_t					dmaSignalRead;
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
		ZunoError_t											begin(void);
		ZunoError_t											begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);
		void												beginTransaction(SPISettings spi_setings) {this->beginTransaction(spi_setings.clock, spi_setings.bitOrder, spi_setings.dataMode);};
		inline void											beginTransaction(SPISettings *spi_setings) {this->beginTransaction(spi_setings->clock, spi_setings->bitOrder, spi_setings->dataMode);};
		inline void											beginTransaction(void) {this->beginTransaction(1000000, MSBFIRST, SPI_MODE0);};
		void												beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode);
		void												endTransaction(void);
		inline void											end(void) {zunoSyncClose(this->_config->lpLock, SyncMasterSpi, this->_deInit, (size_t)this, &this->_lpKey);};
		inline ZunoError_t									transfer(const void *b, size_t count) { return(this->_transfer((void *)b, count, SPI_FLAGS_CONST));};
		inline ZunoError_t									transfer(const void *b) {return(this->transfer((char *)b));};
		inline ZunoError_t									transfer(const char *b) {return(this->_transferStrlen((void *)b, SPI_FLAGS_CONST));};
		inline ZunoError_t									transfer(void *b, size_t count) {return(this->_transfer((void *)b, count, 0));};
		inline ZunoError_t									transfer(void *b) {return(this->transfer((char *)b));};
		inline ZunoError_t									transfer(char *b) {return(this->_transferStrlen((void *)b, 0));};
		inline uint8_t										transfer(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint8_t										transfer8(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint8_t										transfer8(int data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint16_t										transfer16(uint16_t data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};
		inline uint16_t										transfer16(int data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};
		ZunoError_t											transferDup(const void *b, size_t count, size_t repeat);

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

extern SPIClass SPI;

#endif// SPI_H