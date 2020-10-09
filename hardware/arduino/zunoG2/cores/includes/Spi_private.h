#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define SPI_INIT_DEFAULT					{usartEnable, 0, 0, usartDatabits8, true, MSBFIRST, SPI_MODE0, false, usartPrsRxCh0, false, false, 0, 0}

typedef struct								ZunoSpiUsartTypeConfig_s
{
	USART_TypeDef							*usart;
	ZDMA_PeripheralSignal_t					dmaSignal;
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
		SPIClass(USART_TypeDef *usart);
		SPIClass(void);
		void		begin(void);
		void		begin(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);
		void		beginTransaction(SPISettings *spi_setings);
		void		beginTransaction(void);
		void		beginTransaction(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode);
		uint8_t		transfer(uint8_t data);
		uint16_t	transfer16(uint16_t data);
		void		transfer(void *b, size_t count);
		void		transfer(void *b);
		void		transfer(const char *b);
		void		endTransaction(void);
		void		end(void);

	private:
		const ZunoSpiUsartTypeConfig_t		*usart_config;
		uint32_t							clock;
		USART_ClockMode_TypeDef				dataMode;
		ZunoZDmaUser_t						userLp;
		uint8_t								bitOrder;
		uint8_t								sck_pin;
		uint8_t								miso_pin;
		uint8_t								mosi_pin;
		uint8_t								ss_pin;
};

extern SPIClass SPI;

#endif// SPI_PRIVATE_H