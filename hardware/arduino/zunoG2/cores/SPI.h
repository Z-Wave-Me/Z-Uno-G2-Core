#ifndef SPI_H
#define SPI_H

#include "Sync.h"
#include "LdmaClass.h"
#include "em_cmu.h"
#include "em_usart.h"

#define SPI_BUFFER_LENGTH			(64)

#define SPI							SPI1

#define SPI_CLOCK_DIV2				0x2
#define SPI_CLOCK_DIV4				0x4
#define SPI_CLOCK_DIV8				0x8
#define SPI_CLOCK_DIV16				0x10
#define SPI_CLOCK_DIV32				0x20
#define SPI_CLOCK_DIV64				0x40
#define SPI_CLOCK_DIV128			0x80

#define SPI_MODE0		0x0
#define SPI_MODE1		0x1
#define SPI_MODE2		0x2
#define SPI_MODE3		0x3

#define MSBFIRST		true
#define LSBFIRST		false

#define SPI_INIT_DEFAULT					{usartEnable, 0, 4000000, usartDatabits8, true, MSBFIRST, usartClockMode0, false, usartPrsRxCh0, false, false, false, 0, 0}

#define SPI_FLAGS_CONST				0x1
#define SPI_FLAGS_16BIT				0x2

typedef enum								ZunoSpiType_s
{
	#if EUSART_COUNT >= 1
	ZunoSpiTypeEusart,
	#endif
	ZunoSpiTypeUsart,
}											ZunoSpiType_t;

typedef struct								ZunoSpiConfig_s
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
	ZunoSync_t								*lpLock;
	void									(*IRQHandler)(uint32_t);
	LDMA_PeripheralSignal_t					dmaSignalWrite;
	LDMA_PeripheralSignal_t					dmaSignalRead;
	CMU_Clock_TypeDef						bus_clock;
	uint8_t									sck;
	uint8_t									miso;
	uint8_t									mosi;
	uint8_t									subType;
	IRQn_Type								irqType;
	uint8_t									fd;
	ZunoSpiType_t							type;
}											ZunoSpiConfig_t;

typedef struct								ZunoSpiSlave_s
{
	LdmaClassReceivedCyclical_t				arrayReceivedCyclical;
	LdmaClassTransferSingle_t				array_w;
	ssize_t									channel;
	ssize_t									channel_w;
	void									(*user_onRequest)(void);
	uint16_t								len;
	uint16_t								count;
	uint8_t									buffer[];
}											ZunoSpiSlave_t;

class SPISettings {
	public:
		SPISettings(void);
		SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);

	private:
		uint32_t							clock;
		uint8_t								bitOrder;
		uint8_t								dataMode;

	friend class SPIClass;
};

typedef enum							ZunoSpiNumConfig_s
{
	// #if EUSART_COUNT >= 2
	// ZunoSpiEusart1,
	// #endif
	// #if EUSART_COUNT >= 1
	// ZunoSpiEusart0,
	// #endif
	// #if EUSART_COUNT >= 3
	// ZunoSpiEusart2,
	// #endif
	#if USART_COUNT >= 1
	ZunoSpiUsart0,
	#endif
	#if USART_COUNT >= 2
	ZunoSpiUsart1,
	#endif
	#if USART_COUNT >= 3
	ZunoSpiUsart2,
	#endif
	ZunoSpiLast
}										ZunoSpiNumConfig_t;

class SPIClass {
	public:
		SPIClass(ZunoSpiNumConfig_t numberConfig);
		// Base Setup
		void			begin(void);
		ZunoError_t		begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);
		void			beginTransaction(SPISettings spi_setings) {this->beginTransaction(spi_setings.clock, spi_setings.bitOrder, spi_setings.dataMode);};
		inline void		beginTransaction(SPISettings *spi_setings) {this->beginTransaction(spi_setings->clock, spi_setings->bitOrder, spi_setings->dataMode);};
		inline void		beginTransaction(void) {this->beginTransaction(4000000, MSBFIRST, SPI_MODE0);};
		ZunoError_t		beginTransaction(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);
		inline void		end(void) {zunoSyncClose(this->_config->lpLock, SyncMasterSpi, this->_deInit, (size_t)this, &this->_lpKey);};
		void			endTransaction(void);
		// Options
		void			setBitOrder(uint8_t order);
		inline void		setDataMode(uint8_t mode) {this->setDataMode(mode, this->_ss_pin);};
		void			setDataMode(uint8_t mode, uint8_t slaveSelectPin);
		inline void		setClockDivider(uint8_t divider) {this->setClockDivider(divider, this->_ss_pin);};
		void			setClockDivider(uint8_t divider, uint8_t slaveSelectPin);
		// Slave mode
		ZunoError_t		setSlave(uint8_t mode) {return (this->setSlave(mode, SPI_BUFFER_LENGTH));};
		ZunoError_t		setSlave(uint8_t mode, uint16_t len);
		// Typical Arduino interface 
		ZunoError_t		memset(uint8_t c, size_t n);//max 2048 * 255
		int				available(void);
		int				peek(void);
		int				read(void);
		size_t			write(uint8_t data) { return (this->write((const uint8_t *)&data, 0x1));};
		size_t			write(const uint8_t *data, size_t quantity);
		// Alll the ways to transfer
		inline uint8_t		transfer(int data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint8_t		transfer(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline ZunoError_t	transfer(const void *buffer, size_t count) { return(this->_transfer((void *)buffer, count, SPI_FLAGS_CONST));};
		inline ZunoError_t	transfer(const void *buffer) {return(this->transfer((char *)buffer));};
		inline ZunoError_t	transfer(const char *buffer) {return(this->_transferStrlen((void *)buffer, SPI_FLAGS_CONST));};
		inline ZunoError_t	transfer(void *buffer, size_t count) {return(this->_transfer((void *)buffer, count, 0));};
		inline ZunoError_t	transfer(char *buffer) {return(this->_transferStrlen((void *)buffer, 0));};
		inline uint8_t		transfer8(uint8_t data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint8_t		transfer8(int data) {return ((uint8_t)this->_transferDate(data, 0));};
		inline uint16_t		transfer16(int data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};
		inline uint16_t		transfer16(uint16_t data) {return ((uint16_t)this->_transferDate(data, SPI_FLAGS_16BIT));};
		// Request callback
		void onRequest(void (*function)(void));
		 
	private:
		inline USART_ClockMode_TypeDef						_convertMode(uint8_t mode);
		#if USART_COUNT >= 1
		void												_USART_IRQHandler(uint32_t flags);
		static void											_USART0_IRQHandler(uint32_t flags);
		#endif
		#if USART_COUNT >= 2
		static void											_USART1_IRQHandler(uint32_t flags);
		#endif
		#if USART_COUNT >= 3
		static void											_USART2_IRQHandler(uint32_t flags);
		#endif
		inline int											_readLock(uint8_t bOffset);
		size_t												_transferDate(size_t data, size_t bFlags);
		ZunoError_t											_transferStrlen(void *b, size_t bFlags);
		ZunoError_t											_transfer(void *b, size_t count, size_t bFlags);
		static ZunoError_t									_init(size_t param);
		static ZunoError_t									_deInit(size_t param);
		static const USART_InitSync_TypeDef					_initSpi;
		const ZunoSpiConfig_t								*_config;
		size_t												_baudrate;
		ZunoSpiSlave_t										*_slave;
		uint8_t												_ss_pin;
		#if defined(USART_ROUTEPEN_TXPEN) && defined(USART_ROUTEPEN_RXPEN)
		uint8_t												_ss_loc;
		#endif
		uint8_t												_sck_pin;
		uint8_t												_mosi_pin;
		uint8_t												_miso_pin;
		volatile uint8_t									_lpKey;
};

extern SPIClass SPI0;
extern SPIClass SPI1;
extern SPIClass SPI2;

#endif// SPI_H