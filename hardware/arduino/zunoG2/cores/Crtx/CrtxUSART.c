#include "Arduino.h"
#include "CrtxUSART.h"

void USART_Reset(USART_TypeDef *usart){
  /* Make sure disabled first, before resetting other registers */
  usart->CMD = USART_CMD_RXDIS | USART_CMD_TXDIS | USART_CMD_MASTERDIS
               | USART_CMD_RXBLOCKDIS | USART_CMD_TXTRIDIS | USART_CMD_CLEARTX
               | USART_CMD_CLEARRX;

  usart->CTRL      = _USART_CTRL_RESETVALUE;
  usart->FRAME     = _USART_FRAME_RESETVALUE;
  usart->TRIGCTRL  = _USART_TRIGCTRL_RESETVALUE;
  usart->CLKDIV    = _USART_CLKDIV_RESETVALUE;
  usart->IEN       = _USART_IEN_RESETVALUE;
  usart->IFC       = _USART_IFC_MASK;
  usart->TIMING    = _USART_TIMING_RESETVALUE;
  usart->ROUTEPEN  = _USART_ROUTEPEN_RESETVALUE;
  usart->ROUTELOC0 = _USART_ROUTELOC0_RESETVALUE;
  usart->ROUTELOC1 = _USART_ROUTELOC1_RESETVALUE;

  if (USART_IRDA_VALID(usart)) {
    usart->IRCTRL = _USART_IRCTRL_RESETVALUE;
  }
  usart->INPUT = _USART_INPUT_RESETVALUE;
  if (USART_I2S_VALID(usart)) {
    usart->I2SCTRL = _USART_I2SCTRL_RESETVALUE;
  }
}
void USART_BaudrateSyncSet(USART_TypeDef *usart, uint32_t refFreq, uint32_t baudrate) {
  uint32_t clkdiv;
  /*
   * CLKDIV in synchronous mode is given by:
   *
   * CLKDIV = 256 * (fHFPERCLK/(2 * br) - 1)
   */

  /* HFPERCLK/HFPERBCLK used to clock all USART/UART peripheral modules. */
  if (!refFreq) {
    refFreq = CMU_ClockFreqGet(cmuClock_HFPER);
  }

  clkdiv = (refFreq - 1) / (2 * baudrate);
  clkdiv = clkdiv << 8;
  usart->CLKDIV = clkdiv;
}
void USART_InitSync(USART_TypeDef *usart, const USART_InitSync_TypeDef *init){
  /* Initialize USART registers to hardware reset state. */
  USART_Reset(usart);

  /* Set bits for synchronous mode. */
  usart->CTRL |= (USART_CTRL_SYNC)
                 | (uint32_t)init->clockMode
                 | (init->msbf ? USART_CTRL_MSBF : 0);

#if defined(_USART_CTRL_AUTOTX_MASK)
  usart->CTRL |= init->autoTx ? USART_CTRL_AUTOTX : 0;
#endif


  /* Configure databits, leave stopbits and parity at reset default (not used). */
  usart->FRAME = (uint32_t)init->databits
                 | USART_FRAME_STOPBITS_DEFAULT
                 | USART_FRAME_PARITY_DEFAULT;

  /* Configure the baudrate. */
  USART_BaudrateSyncSet(usart, init->refFreq, init->baudrate);

  /* Finally, enable (as specified). */
  if (init->master) {
    usart->CMD = USART_CMD_MASTEREN;
  }

  if (init->autoCsEnable) {
    usart->CTRL |= USART_CTRL_AUTOCS;
  }
#if defined(_USART_TIMING_CSHOLD_MASK)
  usart->TIMING = ((init->autoCsHold << _USART_TIMING_CSHOLD_SHIFT)
                   & _USART_TIMING_CSHOLD_MASK)
                  | ((init->autoCsSetup << _USART_TIMING_CSSETUP_SHIFT)
                     & _USART_TIMING_CSSETUP_MASK);
#endif

  usart->CMD = (uint32_t)init->enable;
}
void SPIInit(SPICfg_t * d){
    USART_InitSync_TypeDef usartInit = USART_INITSYNC_DEFAULT;
    usartInit.msbf = d->msb_first;
    usartInit.clockMode = d->clock_mode;
    usartInit.baudrate = d->baud_rate;
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART2, true);
    USART_InitSync(USART2, &usartInit);

    USART2->ROUTEPEN = USART_ROUTEPEN_TXPEN
                               | USART_ROUTEPEN_RXPEN
                               | USART_ROUTEPEN_CLKPEN;

    USART2->ROUTELOC0 = (USART2->ROUTELOC0
                                 & ~(_USART_ROUTELOC0_TXLOC_MASK
                                     | _USART_ROUTELOC0_RXLOC_MASK
                                     | _USART_ROUTELOC0_CLKLOC_MASK))
                                | (d->mosi_loc  << _USART_ROUTELOC0_TXLOC_SHIFT)
                                | (d->miso_loc   << _USART_ROUTELOC0_RXLOC_SHIFT)
                                | (d->sck_loc << _USART_ROUTELOC0_CLKLOC_SHIFT);
    
}
uint8_t USART_SpiTransfer(USART_TypeDef *usart, uint8_t data){
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDATA = (uint32_t)data;
  while (!(usart->STATUS & USART_STATUS_TXC)) {
  }
  return (uint8_t)usart->RXDATA;
}