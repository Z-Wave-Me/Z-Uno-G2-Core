#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#include "Arduino.h"
#include "Spi_define.h"

#if SPI_BUS_NOMBER == 0 || SPI_BUS_NOMBER == 1 //We select the necessary settings depending on the bus USART
	#define SPI_LOCATION		g_loc_pa0_pf7_all
	#if SPI_BUS_NOMBER == 0
		#define SPI_BUS_CLOCK	cmuClock_USART0
		#define SPI_BUS			USART0
	#else
		#define SPI_BUS_CLOCK	cmuClock_USART1
		#define SPI_BUS			USART1
	#endif
#elif SPI_BUS_NOMBER == 2
	#define SPI_LOCATION		g_loc_pf0_pf1_pf3_pf7
	#define SPI_BUS_CLOCK		cmuClock_USART2
	#define SPI_BUS				USART2
#else
	#define SPI_BUS_NOMBER		Incorrectly defined!
#endif

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
		USART_InitSync_TypeDef				init_spi;
		uint8_t								sck_pin;
		uint8_t								miso_pin;
		uint8_t								mosi_pin;
		uint8_t								ss_pin;
};

extern SPIClass SPI;

#endif// SPI_PRIVATE_H