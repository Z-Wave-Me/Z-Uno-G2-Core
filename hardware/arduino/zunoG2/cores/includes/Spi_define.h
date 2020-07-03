#ifndef SPI_DEFINE_H
#define SPI_DEFINE_H

#include "CrtxUSART.h"

#define SPI_MODE0		usartClockMode0
#define SPI_MODE1		usartClockMode1
#define SPI_MODE2		usartClockMode2
#define SPI_MODE3		usartClockMode3

#define MSBFIRST		true
#define LSBFIRST		false

#if SPI_BUS_NOMBER == 0 || SPI_BUS_NOMBER == 1 // Select the necessary location scheme

// As long as nothing

#elif SPI_BUS_NOMBER == 2
	#ifndef LOC_PF0_PF1_PF3_PF7
		#define LOC_PF0_PF1_PF3_PF7
		const uint8_t g_loc_pf0_pf1_pf3_pf7[] = {
			0x50, 0x51, 0x53, 0x54, 0x55, 0x56, 0x57//PF0,PF1,PF3-PF7
		};
	#endif
#else
	#define SPI_BUS_NOMBER		Incorrectly defined!
#endif

#endif// SPI_DEFINE_H