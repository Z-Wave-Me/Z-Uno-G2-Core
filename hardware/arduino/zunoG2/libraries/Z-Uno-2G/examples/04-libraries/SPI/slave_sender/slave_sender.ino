#include "Arduino.h"
#include "Spi.h"



// void _USART_IRQHandler(size_t date) {
// 	USART_Tx(USART2, 'E');
// 	(void)date;
// }

void setup(){
	// Serial.begin();
	SPI.begin(SCK, MISO, MOSI, SS);
	SPI.setSlave(true);
	// zunoDetachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_USART1_RX, (void *)&_USART_IRQHandler);
	// NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	// NVIC_EnableIRQ(USART1_RX_IRQn);

	// USART1->TIMECMP1 =  USART_TIMECMP1_TSTART_RXEOF | USART_TIMECMP1_TSTOP_RXACT | 0xC;
	// USART_IntEnable(USART1, USART_IEN_TCMP1);
	// USART_Tx(USART2, 'E');
}

// Покуда так - так как TIMECMP не работает так как нужно
void loop(){
	size_t			cmd;
	size_t			i;

	if (SPI.available() >= 0x2)
	{
		cmd = (SPI.read() << 0x8 )| SPI.read();
		if (cmd == 0x3031 && SPI.available() == 0x0) {
			SPI.beginTransmissionSlave();
			SPI.write((uint8_t *)"Yes!! this I", 12);
			SPI.endTransmissionSlave();
			i = 12;
			while (i != 0)
			{
				while (SPI.available() && i != 0)
				{
					cmd = SPI.read();
					i--;
				}
				delay(0x2);
			}
		}
		else {
			while (SPI.available())
			{
				cmd = SPI.read();
			}
		}
	}
}