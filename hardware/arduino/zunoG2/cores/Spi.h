#ifndef SPI_H
#define SPI_H

#include "Spi_define.h"

class SPISettings {
	public:
		SPISettings(void);
		SPISettings(uint32_t clock, uint8_t bitOrder, USART_ClockMode_TypeDef dataMode);
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
		uint8_t		transfer(int data){return transfer((uint8_t)data);};
		uint8_t		transfer(uint8_t data);
		uint16_t	transfer16(uint16_t data);
		void		transfer(void *b, size_t count);
		void		transfer(void *b);
		void		transfer(const char *b);
		void		endTransaction(void);
		void		end(void);
};

extern SPIClass SPI;

#endif// SPI_H