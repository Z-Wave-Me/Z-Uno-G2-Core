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
	#ifndef LOC_PA0_PF7_ALL
		#define LOC_PA0_PF7_ALL
		const uint8_t g_loc_pa0_pf7_all[] = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
			0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
			0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
			0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
			0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
		};
	#endif
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