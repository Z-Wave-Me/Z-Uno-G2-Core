#include "Arduino.h"
#include "CrtxUSART.h"

#if defined(_USART_CLKDIV_DIVEXT_MASK)
  #define CLKDIV_MASK  (_USART_CLKDIV_DIV_MASK | _USART_CLKDIV_DIVEXT_MASK)
#else
  #define CLKDIV_MASK  _USART_CLKDIV_DIV_MASK
#endif

#if !defined(_EFM32_GECKO_FAMILY)
/***************************************************************************//**
 * @brief
 *   Configure a PRS channel as USART Rx input
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] ch
 *   PRS channel.
 ******************************************************************************/
static void prsRxInput(USART_TypeDef *usart, USART_PRS_Channel_t ch)
{
#if defined(_USART_INPUT_MASK)
  usart->INPUT = ((uint32_t)ch << _USART_INPUT_RXPRSSEL_SHIFT)
                 | USART_INPUT_RXPRS;
#elif defined(USART_CTRLX_RXPRSEN)
  if (usart == USART0) {
    PRS->CONSUMER_USART0_RX = ch;
  } else if (usart == USART1) {
    PRS->CONSUMER_USART1_RX = ch;
  }
#if USART_COUNT > 2
  else if (usart == USART2) {
    PRS->CONSUMER_USART2_RX = ch;
  }
#endif
  usart->CTRLX |= USART_CTRLX_RXPRSEN;
#endif
}
#endif

/***************************************************************************//**
 * @brief
 *   Configure a PRS channel as USART Ir input
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] ch
 *   PRS channel.
 ******************************************************************************/
static void prsIrInput(USART_TypeDef *usart, USART_PRS_Channel_t ch)
{
#if defined(_USART_IRCTRL_IRPRSSEL_MASK)
  usart->IRCTRL |= ((uint32_t)ch << _USART_IRCTRL_IRPRSSEL_SHIFT)
                   | USART_IRCTRL_IRPRSEN;
#else
  if (usart == USART0) {
    PRS->CONSUMER_USART0_IR = ch;
  } else if (usart == USART1) {
    PRS->CONSUMER_USART1_IR = ch;
  }
#if USART_COUNT > 2
  else if (usart == USART2) {
    PRS->CONSUMER_USART2_IR = ch;
  }
#endif
  usart->IRCTRL |= USART_IRCTRL_IRPRSEN;
#endif
}

/***************************************************************************//**
 * @brief
 *   Configure a PRS channel as USART Trigger input
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] ch
 *   PRS channel.
 ******************************************************************************/
static void prsTriggerInput(USART_TypeDef *usart, USART_PRS_Channel_t ch)
{
#if defined(_USART_IRCTRL_IRPRSSEL_MASK)
  usart->TRIGCTRL = (usart->TRIGCTRL & ~_USART_TRIGCTRL_TSEL_MASK)
                    | (ch << _USART_TRIGCTRL_TSEL_SHIFT);
#else
  if (usart == USART0) {
    PRS->CONSUMER_USART0_TRIGGER = ch;
  } else if (usart == USART1) {
    PRS->CONSUMER_USART1_TRIGGER = ch;
  }
#if USART_COUNT > 2
  else if (usart == USART2) {
    PRS->CONSUMER_USART2_TRIGGER = ch;
  }
#endif
#endif
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Configure USART/UART operating in asynchronous mode to use a given
 *   baudrate (or as close as possible to a specified baudrate).
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] refFreq
 *   USART/UART reference clock frequency in Hz. If set to 0,
 *   the currently configured reference clock is assumed.
 *
 * @param[in] baudrate
 *   Baudrate to try to achieve for USART/UART.
 *
 * @param[in] ovs
 *   Oversampling to be used. Normal is 16x oversampling but lower oversampling
 *   may be used to achieve higher rates or better baudrate accuracy in some
 *   cases. Notice that lower oversampling frequency makes the channel more
 *   vulnerable to bit faults during reception due to clock inaccuracies
 *   compared to the link partner.
 ******************************************************************************/
void USART_BaudrateAsyncSet(USART_TypeDef *usart,
                            uint32_t refFreq,
                            uint32_t baudrate,
                            USART_OVS_TypeDef ovs)
{
  uint32_t clkdiv;
  uint32_t oversample;

  /* Inhibit divide by 0 */
  //EFM_ASSERT(baudrate);

  /*
   * Use integer division to avoid forcing in float division
   * utils and yet keep rounding effect errors to a minimum.
   *
   * CLKDIV in asynchronous mode is given by:
   *
   * CLKDIV = 256 * (fHFPERCLK/(oversample * br) - 1)
   * or
   * CLKDIV = (256 * fHFPERCLK)/(oversample * br) - 256
   *
   * The basic problem with integer division in the above formula is that
   * the dividend (256 * fHFPERCLK) may become higher than max 32 bit
   * integer. Yet, we want to evaluate the dividend first before dividing
   * to get as small rounding effects as possible.
   * Too harsh restrictions on maximum fHFPERCLK value should not be made.
   *
   * It is possible to factorize 256 and oversample/br. However,
   * since the last 6 or 3 bits of CLKDIV are don't care, base the
   * integer arithmetic on the below formula
   *
   * CLKDIV / 64 = (4 * fHFPERCLK)/(oversample * br) - 4 (3 bits dont care)
   * or
   * CLKDIV / 8  = (32 * fHFPERCLK)/(oversample * br) - 32 (6 bits dont care)
   *
   * and calculate 1/64 of CLKDIV first. This allows for fHFPERCLK
   * up to 1 GHz without overflowing a 32 bit value.
   */

  /* HFPERCLK/HFPERBCLK used to clock all USART/UART peripheral modules. */
  if (!refFreq) {
#if defined(_SILICON_LABS_32B_SERIES_2)
    refFreq = CMU_ClockFreqGet(cmuClock_PCLK);
#else
#if defined(_CMU_HFPERPRESCB_MASK)
    if (usart == USART2) {
      refFreq = CMU_ClockFreqGet(cmuClock_HFPERB);
    } else {
      refFreq = CMU_ClockFreqGet(cmuClock_HFPER);
    }
#else
    refFreq = CMU_ClockFreqGet(cmuClock_HFPER);
#endif
#endif
  }

  /* Map oversampling. */
  switch (ovs) {
    case usartOVS16:
      //EFM_ASSERT(baudrate <= (refFreq / 16));
      oversample = 16;
      break;

    case usartOVS8:
      //EFM_ASSERT(baudrate <= (refFreq / 8));
      oversample = 8;
      break;

    case usartOVS6:
      //EFM_ASSERT(baudrate <= (refFreq / 6));
      oversample = 6;
      break;

    case usartOVS4:
      //EFM_ASSERT(baudrate <= (refFreq / 4));
      oversample = 4;
      break;

    default:
      /* Invalid input */
      //EFM_ASSERT(0);
      return;
  }

  /* Calculate and set CLKDIV with fractional bits.
   * The added (oversample*baudrate)/2 in the first line is to round the
   * divisor to the nearest fractional divisor. */
#if defined(_SILICON_LABS_32B_SERIES_0) && !defined(_EFM32_HAPPY_FAMILY)
  /* Devices with 2 fractional bits. CLKDIV[7:6] */
  clkdiv  = 4 * refFreq + (oversample * baudrate) / 2;
  clkdiv /= oversample * baudrate;
  clkdiv -= 4;
  clkdiv *= 64;
#else
  /* Devices with 5 fractional bits. CLKDIV[7:3] */
  clkdiv  = 32 * refFreq + (oversample * baudrate) / 2;
  clkdiv /= oversample * baudrate;
  clkdiv -= 32;
  clkdiv *= 8;
#endif

  /* Verify that the resulting clock divider is within limits. */
  //EFM_ASSERT(clkdiv <= CLKDIV_MASK);

  /* Make sure that reserved bits are not written to. */
  clkdiv &= CLKDIV_MASK;

  usart->CTRL  &= ~_USART_CTRL_OVS_MASK;
  usart->CTRL  |= ovs;
  usart->CLKDIV = clkdiv;
}

/***************************************************************************//**
 * @brief
 *   Calculate baudrate for USART/UART given reference frequency, clock division,
 *   and oversampling rate (if async mode).
 *
 * @details
 *   This function returns the baudrate that a USART/UART module will use if
 *   configured with the given frequency, clock divisor, and mode. Notice that
 *   this function will not use the hardware configuration. It can be used
 *   to determine if a given configuration is sufficiently accurate for the
 *   application.
 *
 * @param[in] refFreq
 *   USART/UART HF peripheral frequency used.
 *
 * @param[in] clkdiv
 *   A clock division factor to be used.
 *
 * @param[in] syncmode
 *   @li True - synchronous mode operation.
 *   @li False - asynchronous mode operation.
 *
 * @param[in] ovs
 *   Oversampling used if in asynchronous mode. Not used if @p syncmode is true.
 *
 * @return
 *   Baudrate with given settings.
 ******************************************************************************/
uint32_t USART_BaudrateCalc(uint32_t refFreq,
                            uint32_t clkdiv,
                            bool syncmode,
                            USART_OVS_TypeDef ovs)
{
  uint32_t oversample;
  uint64_t divisor;
  uint64_t factor;
  uint64_t remainder;
  uint64_t quotient;
  uint32_t br;

  /* Out of bound clkdiv. */
  //EFM_ASSERT(clkdiv <= CLKDIV_MASK);

  /* Mask out unused bits */
  clkdiv &= CLKDIV_MASK;

  /* Use integer division to avoid forcing in float division */
  /* utils and yet keep rounding effect errors to a minimum. */

  /* Baudrate calculation depends on if synchronous or asynchronous mode. */
  if (syncmode) {
    /*
     * Baudrate is given by:
     *
     * br = fHFPERCLK/(2 * (1 + (CLKDIV / 256)))
     *
     * which can be rewritten to
     *
     * br = (128 * fHFPERCLK)/(256 + CLKDIV)
     */
    oversample = 1; /* Not used in sync mode, i.e., 1 */
    factor     = 128;
  } else {
    /*
     * Baudrate in asynchronous mode is given by:
     *
     * br = fHFPERCLK/(oversample * (1 + (CLKDIV / 256)))
     *
     * which can be rewritten to
     *
     * br = (256 * fHFPERCLK)/(oversample * (256 + CLKDIV))
     *
     * 256 factor of the dividend is reduced with a
     * (part of) oversample part of the divisor.
     */

    switch (ovs) {
      case usartOVS16:
        oversample = 1;
        factor     = 256 / 16;
        break;

      case usartOVS8:
        oversample = 1;
        factor     = 256 / 8;
        break;

      case usartOVS6:
        oversample = 3;
        factor     = 256 / 2;
        break;

      default:
        oversample = 1;
        factor     = 256 / 4;
        break;
    }
  }

  /*
   * The basic problem with integer division in the above formula is that
   * the dividend (factor * fHFPERCLK) may become larger than a 32 bit
   * integer. Yet we want to evaluate the dividend first before dividing
   * to get as small rounding effects as possible. Too harsh restrictions
   * should not be made on the maximum fHFPERCLK value either.
   *
   * For division a/b,
   *
   * a = qb + r
   *
   * where q is the quotient and r is the remainder, both integers.
   *
   * The original baudrate formula can be rewritten as
   *
   * br = xa / b = x(qb + r)/b = xq + xr/b
   *
   * where x is 'factor', a is 'refFreq' and b is 'divisor', referring to
   * variable names.
   */

  /*
   * The divisor will never exceed max 32 bit value since
   * clkdiv <= _USART_CLKDIV_DIV_MASK (currently 0x1FFFC0 or 0x7FFFF8)
   * and 'oversample' has been reduced to <= 3.
   */
  divisor = oversample * (256 + clkdiv);

  quotient  = refFreq / divisor;
  remainder = refFreq % divisor;

  /* The factor <= 128 and since divisor >= 256, the below cannot exceed the maximum */
  /* 32 bit value. However, factor * remainder can become larger than 32-bit */
  /* because of the size of _USART_CLKDIV_DIV_MASK on some families. */
  br = (uint32_t)(factor * quotient);

  /*
   * The factor <= 128 and remainder < (oversample*(256 + clkdiv)), which
   * means dividend (factor * remainder) worst case is
   * 128 * (3 * (256 + _USART_CLKDIV_DIV_MASK)) = 0x1_8001_7400.
   */
  br += (uint32_t)((factor * remainder) / divisor);

  return br;
}

/***************************************************************************//**
 * @brief
 *   Get the current baudrate for USART/UART.
 *
 * @details
 *   This function returns the actual baudrate (not considering oscillator
 *   inaccuracies) used by a USART/UART peripheral.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @return
 *   The current baudrate.
 ******************************************************************************/
uint32_t USART_BaudrateGet(USART_TypeDef *usart)
{
  uint32_t          freq;
  USART_OVS_TypeDef ovs;
  bool              syncmode;

  if (usart->CTRL & USART_CTRL_SYNC) {
    syncmode = true;
  } else {
    syncmode = false;
  }

  /* HFPERCLK/HFPERBCLK used to clock all USART/UART peripheral modules. */
#if defined(_SILICON_LABS_32B_SERIES_2)
  freq = CMU_ClockFreqGet(cmuClock_PCLK);
#else
#if defined(_CMU_HFPERPRESCB_MASK)
  if (usart == USART2) {
    freq = CMU_ClockFreqGet(cmuClock_HFPERB);
  } else {
    freq = CMU_ClockFreqGet(cmuClock_HFPER);
  }
#else
  freq = CMU_ClockFreqGet(cmuClock_HFPER);
#endif
#endif
  ovs  = (USART_OVS_TypeDef)(usart->CTRL & _USART_CTRL_OVS_MASK);
  return USART_BaudrateCalc(freq, usart->CLKDIV, syncmode, ovs);
}

/***************************************************************************//**
 * @brief
 *   Configure the USART operating in synchronous mode to use a given baudrate
 *   (or as close as possible to a specified baudrate).
 *
 * @details
 *   The configuration will be set to use a baudrate <= the specified baudrate
 *   to ensure that the baudrate does not exceed the specified value.
 *
 *   The fractional clock division is suppressed, although the hardware design allows it.
 *   It could cause half clock cycles to exceed a specified limit and thus
 *   potentially violate specifications for the slave device. In some special
 *   situations, a fractional clock division may be useful even in synchronous
 *   mode, but in those cases it must be directly adjusted, possibly assisted
 *   by USART_BaudrateCalc():
 *
 * @param[in] usart
 *   A pointer to the USART peripheral register block. (Cannot be used on UART
 *   modules.)
 *
 * @param[in] refFreq
 *   A USART reference clock frequency in Hz that will be used. If set to 0,
 *   the currently-configured reference clock is assumed.
 *
 * @param[in] baudrate
 *   Baudrate to try to achieve for USART.
 ******************************************************************************/
void USART_BaudrateSyncSet(USART_TypeDef *usart, uint32_t refFreq, uint32_t baudrate)
{
  uint32_t clkdiv;

  /* Prevent dividing by 0. */
  //EFM_ASSERT(baudrate);

  /*
   * CLKDIV in synchronous mode is given by:
   *
   * CLKDIV = 256 * (fHFPERCLK/(2 * br) - 1)
   */

  /* HFPERCLK/HFPERBCLK used to clock all USART/UART peripheral modules. */
  if (!refFreq) {
#if defined(_SILICON_LABS_32B_SERIES_2)
    refFreq = CMU_ClockFreqGet(cmuClock_PCLK);
#else
#if defined(_CMU_HFPERPRESCB_MASK)
    if (usart == USART2) {
      refFreq = CMU_ClockFreqGet(cmuClock_HFPERB);
    } else {
      refFreq = CMU_ClockFreqGet(cmuClock_HFPER);
    }
#else
    refFreq = CMU_ClockFreqGet(cmuClock_HFPER);
#endif
#endif
  }

  clkdiv = (refFreq - 1) / (2 * baudrate);
  clkdiv = clkdiv << 8;

  /* Verify that resulting clock divider is within limits. */
  //EFM_ASSERT(!(clkdiv & ~CLKDIV_MASK));

  usart->CLKDIV = clkdiv;
}

/***************************************************************************//**
 * @brief
 *   Enable/disable USART/UART receiver and/or transmitter.
 *
 * @details
 *   Notice that this function does not do any configuration. Enabling should
 *   normally be done after initialization (if not enabled as part
 *   of initialization).
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] enable
 *   Select the status for the receiver/transmitter.
 ******************************************************************************/
void USART_Enable(USART_TypeDef *usart, USART_Enable_TypeDef enable)
{
  uint32_t tmp;

  /* Make sure the module exists on the selected chip. */
  //EFM_ASSERT(USART_REF_VALID(usart) || USARTRF_REF_VALID(usart) || UART_REF_VALID(usart));

#if defined(USART_EN_EN)
  usart->EN_SET = USART_EN_EN;
#endif

  /* Disable as specified. */
  tmp        = ~((uint32_t)enable);
  tmp       &= _USART_CMD_RXEN_MASK | _USART_CMD_TXEN_MASK;
  usart->CMD = tmp << 1;

  /* Enable as specified. */
  usart->CMD = (uint32_t)enable;

#if defined(USART_EN_EN)
  if (enable == usartDisable) {
    usart->EN_CLR = USART_EN_EN;
  }
#endif
}

/***************************************************************************//**
 * @brief
 *   Initialize USART/UART for normal asynchronous mode.
 *
 * @details
 *   This function will configure basic settings to operate in normal
 *   asynchronous mode.
 *
 *   A special control setup not covered by this function must be done after
 *   using this function by direct modification of the CTRL register.
 *
 *   Notice that pins used by the USART/UART module must be properly configured
 *   by the user explicitly for the USART/UART to work as intended.
 *   (When configuring pins, remember to consider the sequence of
 *   configuration to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] init
 *   A pointer to the initialization structure used to configure the basic async setup.
 ******************************************************************************/
void USART_InitAsync(USART_TypeDef *usart, const USART_InitAsync_TypeDef *init)
{
  /* Make sure the module exists on the selected chip. */
  //EFM_ASSERT(USART_REF_VALID(usart) || USARTRF_REF_VALID(usart) || UART_REF_VALID(usart));

  /* Initialize USART registers to hardware reset state. */
  USART_Reset(usart);

#if defined(USART_EN_EN)
  usart->EN_SET = USART_EN_EN;
#endif

#if defined(USART_CTRL_MVDIS)
  /* Disable the majority vote if specified. */
  if (init->mvdis) {
    usart->CTRL |= USART_CTRL_MVDIS;
  }
#endif

#if !defined(_EFM32_GECKO_FAMILY)
  /* Configure the PRS input mode. */
  if (init->prsRxEnable) {
    prsRxInput(usart, init->prsRxCh);
  }
#endif

  /* Configure databits, stopbits, and parity. */
  usart->FRAME = (uint32_t)init->databits
                 | (uint32_t)init->stopbits
                 | (uint32_t)init->parity;

  /* Configure baudrate. */
  USART_BaudrateAsyncSet(usart, init->refFreq, init->baudrate, init->oversampling);

  if (init->autoCsEnable) {
    usart->CTRL |= USART_CTRL_AUTOCS;
  }
#if defined(_USART_TIMING_CSHOLD_MASK)
  usart->TIMING = ((init->autoCsHold << _USART_TIMING_CSHOLD_SHIFT)
                   & _USART_TIMING_CSHOLD_MASK)
                  | ((init->autoCsSetup << _USART_TIMING_CSSETUP_SHIFT)
                     & _USART_TIMING_CSSETUP_MASK);

#endif

#if defined(_USART_ROUTEPEN_RTSPEN_MASK) && defined(_USART_ROUTEPEN_CTSPEN_MASK)
  usart->ROUTEPEN &= ~(_USART_ROUTEPEN_RTSPEN_MASK | _USART_ROUTEPEN_CTSPEN_MASK);
  usart->ROUTEPEN |= init->hwFlowControl;

#elif defined(USART_CTRLX_CTSEN)
  if ((init->hwFlowControl == usartHwFlowControlRts)
      || (init->hwFlowControl == usartHwFlowControlCtsAndRts)) {
    GPIO->USARTROUTE_SET[USART_NUM(usart)].ROUTEEN = GPIO_USART_ROUTEEN_RTSPEN;
  } else {
    GPIO->USARTROUTE_CLR[USART_NUM(usart)].ROUTEEN = GPIO_USART_ROUTEEN_RTSPEN;
  }

  if ((init->hwFlowControl == usartHwFlowControlCts)
      || (init->hwFlowControl == usartHwFlowControlCtsAndRts)) {
    usart->CTRLX_SET = USART_CTRLX_CTSEN;
  } else {
    usart->CTRLX_CLR = USART_CTRLX_CTSEN;
  }
#endif

  /* Finally, enable (as specified). */
  usart->CMD = (uint32_t)init->enable;
}

/***************************************************************************//**
 * @brief
 *   Initialize USART for synchronous mode.
 *
 * @details
 *   This function will configure basic settings to operate in
 *   synchronous mode.
 *
 *   A special control setup not covered by this function must be done after
 *   using this function by direct modification of the CTRL register.
 *
 *   Notice that pins used by the USART module must be properly configured
 *   by the user explicitly for the USART to work as intended.
 *   (When configuring pins remember to consider the sequence of
 *   configuration to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] usart
 *   A pointer to the USART peripheral register block. (UART does not support this
 *   mode.)
 *
 * @param[in] init
 *   A pointer to the initialization structure used to configure basic async setup.
 ******************************************************************************/
void USART_InitSync(USART_TypeDef *usart, const USART_InitSync_TypeDef *init)
{
  /* Make sure the module exists on the selected chip. */
  //EFM_ASSERT(USART_REF_VALID(usart) || USARTRF_REF_VALID(usart) );

  /* Initialize USART registers to hardware reset state. */
  USART_Reset(usart);

#if defined(USART_EN_EN)
  usart->EN_SET = USART_EN_EN;
#endif

  /* Set bits for synchronous mode. */
  usart->CTRL |= (USART_CTRL_SYNC)
                 | (uint32_t)init->clockMode
                 | (init->msbf ? USART_CTRL_MSBF : 0);

#if defined(_USART_CTRL_AUTOTX_MASK)
  usart->CTRL |= init->autoTx ? USART_CTRL_AUTOTX : 0;
#endif

#if !defined(_EFM32_GECKO_FAMILY)
  if (init->prsRxEnable) {
    prsRxInput(usart, init->prsRxCh);
  }
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

/***************************************************************************//**
 * @brief
 *   Initialize USART for asynchronous IrDA mode.
 *
 * @details
 *   This function will configure basic settings to operate in
 *   asynchronous IrDA mode.
 *
 *   A special control setup not covered by this function must be done after
 *   using this function by direct modification of the CTRL and IRCTRL
 *   registers.
 *
 *   Notice that pins used by the USART/UART module must be properly configured
 *   by the user explicitly for the USART/UART to work as intended.
 *   (When configuring pins, remember to consider the sequence of
 *   configuration to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] usart
 *   A pointer to the USART peripheral register block.
 *
 * @param[in] init
 *   A pointer to the initialization structure used to configure async IrDA setup.
 *
 * @note
 *   Not all USART instances support IrDA. See the data sheet for your device.
 *
 ******************************************************************************/
void USARTn_InitIrDA(USART_TypeDef *usart, const USART_InitIrDA_TypeDef *init)
{
  //EFM_ASSERT(USART_IRDA_VALID(usart));

  /* Initialize USART as an async device. */
  USART_InitAsync(usart, &(init->async));

  /* Set IrDA modulation to RZI (return-to-zero-inverted). */
  usart->CTRL |= USART_CTRL_TXINV;

  /* Invert the Rx signal before the demodulator if enabled. */
  if (init->irRxInv) {
    usart->CTRL |= USART_CTRL_RXINV;
  }

  /* Configure IrDA. */
  usart->IRCTRL = (uint32_t)init->irPw
                  | ((init->irFilt ? 1UL : 0UL) << _USART_IRCTRL_IRFILT_SHIFT);
  if (init->irPrsEn) {
    prsIrInput(usart, init->irPrsSel);
  }

  /* Enable IrDA. */
  usart->IRCTRL |= USART_IRCTRL_IREN;
}

#if defined(_USART_I2SCTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Initialize USART for I2S mode.
 *
 * @details
 *   This function will configure basic settings to operate in I2S
 *   mode.
 *
 *   A special control setup not covered by this function must be done after
 *   using this function by direct modification of the CTRL and I2SCTRL
 *   registers.
 *
 *   Notice that pins used by the USART module must be properly configured
 *   by the user explicitly for the USART to work as intended.
 *   (When configuring pins, remember to consider the sequence of
 *   configuration to avoid unintended pulses/glitches on output
 *   pins.)
 *
 * @param[in] usart
 *   A pointer to the USART peripheral register block. (UART does not support this
 *   mode.)
 *
 * @param[in] init
 *   A pointer to the initialization structure used to configure the basic I2S setup.
 *
 * @note
 *   This function does not apply to all USART's. See the chip Reference Manual.
 *
 ******************************************************************************/
void USART_InitI2s(USART_TypeDef *usart, USART_InitI2s_TypeDef *init)
{
  USART_Enable_TypeDef enable;

  /* Make sure the module exists on the selected chip. */
  //EFM_ASSERT(USART_I2S_VALID(usart));

  /* Override the enable setting. */
  enable            = init->sync.enable;
  init->sync.enable = usartDisable;

  /* Initialize USART as a sync device. */
  USART_InitSync(usart, &init->sync);

  /* Configure and enable I2CCTRL register according to the selected mode. */
  usart->I2SCTRL = (uint32_t)init->format
                   | (uint32_t)init->justify
                   | (init->delay    ? USART_I2SCTRL_DELAY    : 0)
                   | (init->dmaSplit ? USART_I2SCTRL_DMASPLIT : 0)
                   | (init->mono     ? USART_I2SCTRL_MONO     : 0)
                   | USART_I2SCTRL_EN;

  if (enable != usartDisable) {
    USART_Enable(usart, enable);
  }
}
#endif

/***************************************************************************//**
 * @brief
 *   Initialize the automatic transmissions using PRS channel as a trigger.
 * @note
 *   Initialize USART with USART_Init() before setting up the PRS configuration.
 *
 * @param[in] usart A pointer to USART to configure.
 * @param[in] init A pointer to the initialization structure.
 ******************************************************************************/
void USART_InitPrsTrigger(USART_TypeDef *usart, const USART_PrsTriggerInit_TypeDef *init)
{
  uint32_t trigctrl;

  prsTriggerInput(usart, init->prsTriggerChannel);
  /* Clear values that will be reconfigured. */
  trigctrl = usart->TRIGCTRL & ~(_USART_TRIGCTRL_RXTEN_MASK
                                 | _USART_TRIGCTRL_TXTEN_MASK
#if defined(USART_TRIGCTRL_AUTOTXTEN)
                                 | _USART_TRIGCTRL_AUTOTXTEN_MASK
#endif
                                 );

#if defined(USART_TRIGCTRL_AUTOTXTEN)
  if (init->autoTxTriggerEnable) {
    trigctrl |= USART_TRIGCTRL_AUTOTXTEN;
  }
#endif
  if (init->txTriggerEnable) {
    trigctrl |= USART_TRIGCTRL_TXTEN;
  }
  if (init->rxTriggerEnable) {
    trigctrl |= USART_TRIGCTRL_RXTEN;
  }
  usart->TRIGCTRL = trigctrl;
}

/***************************************************************************//**
 * @brief
 *   Reset USART/UART to the same state that it was in after a hardware reset.
 *
 * @param[in] usart
 *   A pointer to USART/UART peripheral register block.
 ******************************************************************************/
void USART_Reset(USART_TypeDef *usart)
{
  /* Make sure the module exists on the selected chip. */
  //EFM_ASSERT(USART_REF_VALID(usart) || USARTRF_REF_VALID(usart) || UART_REF_VALID(usart) );

#if defined(USART_EN_EN)
  usart->EN_SET = USART_EN_EN;
  /* Make sure disabled first, before resetting other registers. */
  usart->CMD = USART_CMD_RXDIS | USART_CMD_TXDIS | USART_CMD_MASTERDIS
               | USART_CMD_RXBLOCKDIS | USART_CMD_TXTRIDIS | USART_CMD_CLEARTX
               | USART_CMD_CLEARRX;

  usart->CTRL      = _USART_CTRL_RESETVALUE;
  usart->CTRLX     = _USART_CTRLX_RESETVALUE;
  usart->FRAME     = _USART_FRAME_RESETVALUE;
  usart->TRIGCTRL  = _USART_TRIGCTRL_RESETVALUE;
  usart->CLKDIV    = _USART_CLKDIV_RESETVALUE;
  usart->IEN       = _USART_IEN_RESETVALUE;
  usart->IF_CLR    = _USART_IF_MASK;
  usart->TIMING    = _USART_TIMING_RESETVALUE;

  if (USART_IRDA_VALID(usart)) {
    usart->IRCTRL = _USART_IRCTRL_RESETVALUE;
  }

  if (USART_I2S_VALID(usart)) {
    usart->I2SCTRL = _USART_I2SCTRL_RESETVALUE;
  }
  usart->EN_CLR = USART_EN_EN;

#else
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
#if defined(_USART_TIMING_MASK)
  usart->TIMING    = _USART_TIMING_RESETVALUE;
#endif
#if defined(_USART_ROUTEPEN_MASK) || defined(_UART_ROUTEPEN_MASK)
  usart->ROUTEPEN  = _USART_ROUTEPEN_RESETVALUE;
  usart->ROUTELOC0 = _USART_ROUTELOC0_RESETVALUE;
  usart->ROUTELOC1 = _USART_ROUTELOC1_RESETVALUE;
#else
  usart->ROUTE     = _USART_ROUTE_RESETVALUE;
#endif

  if (USART_IRDA_VALID(usart)) {
    usart->IRCTRL = _USART_IRCTRL_RESETVALUE;
  }

#if defined(_USART_INPUT_RESETVALUE)
  usart->INPUT = _USART_INPUT_RESETVALUE;
#endif

#if defined(_USART_I2SCTRL_RESETVALUE)
  if (USART_I2S_VALID(usart)) {
    usart->I2SCTRL = _USART_I2SCTRL_RESETVALUE;
  }
#endif
#endif
}

/***************************************************************************//**
 * @brief
 *   Receive one 4-8 bit frame, (or part of 10-16 bit frame).
 *
 * @details
 *   This function is normally used to receive one frame when operating with
 *   frame length 4-8 bits. See @ref USART_RxExt() for reception of
 *   9 bit frames.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is empty until data is received.
 *   Alternatively, the user can explicitly check whether data is available.
 *   If data is available, call @ref USART_RxDataGet() to read the RXDATA
 *   register directly.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @return
 *   Data received.
 ******************************************************************************/
uint8_t USART_Rx(USART_TypeDef *usart)
{
  while (!(usart->STATUS & USART_STATUS_RXDATAV)) {
  }

  return (uint8_t)usart->RXDATA;
}

/***************************************************************************//**
 * @brief
 *   Receive two 4-8 bit frames or one 10-16 bit frame.
 *
 * @details
 *   This function is normally used to receive one frame when operating with
 *   frame length 10-16 bits. See @ref USART_RxDoubleExt() for
 *   reception of two 9 bit frames.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is empty until data is received.
 *   Alternatively, the user can explicitly check whether data is available.
 *   If data is available, call @ref USART_RxDoubleGet() to read the RXDOUBLE
 *   register directly.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @return
 *   Data received.
 ******************************************************************************/
uint16_t USART_RxDouble(USART_TypeDef *usart)
{
  while (!(usart->STATUS & USART_STATUS_RXFULL)) {
  }

  return (uint16_t)usart->RXDOUBLE;
}

/***************************************************************************//**
 * @brief
 *   Receive two 4-9 bit frames, or one 10-16 bit frame with extended
 *   information.
 *
 * @details
 *   This function is normally used to receive one frame when operating with
 *   frame length 10-16 bits and additional RX status information is required.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if buffer is empty until data is received.
 *   Alternatively, the user can explicitly check whether data is available.
 *   If data is available, call @ref USART_RxDoubleXGet() to read the RXDOUBLEX
 *   register directly.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @return
 *   Data received.
 ******************************************************************************/
uint32_t USART_RxDoubleExt(USART_TypeDef *usart)
{
  while (!(usart->STATUS & USART_STATUS_RXFULL)) {
  }

  return usart->RXDOUBLEX;
}

/***************************************************************************//**
 * @brief
 *   Receive one 4-9 bit frame (or part of 10-16 bit frame) with extended
 *   information.
 *
 * @details
 *   This function is normally used to receive one frame when operating with
 *   frame length 4-9 bits and additional RX status information is required.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is empty until data is received.
 *   Alternatively, the user can explicitly check whether data is available.
 *   If data is available, call @ref USART_RxDataXGet() to read the RXDATAX
 *   register directly.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @return
 *   Data received.
 ******************************************************************************/
uint16_t USART_RxExt(USART_TypeDef *usart)
{
  while (!(usart->STATUS & USART_STATUS_RXDATAV)) {
  }

  return (uint16_t)usart->RXDATAX;
}

/***************************************************************************//**
 * @brief
 *   Perform one 8 bit frame SPI transfer.
 *
 * @note
 *   This function will stall if the transmit buffer is full. When a transmit
 *   buffer becomes available, data is written and the function will wait until
 *   data is fully transmitted. The SPI return value is then read out and
 *   returned.
 *
 * @param[in] usart
 *   A pointer to the USART peripheral register block.
 *
 * @param[in] data
 *   Data to transmit.
 *
 * @return
 *   Data received.
 ******************************************************************************/
uint8_t USART_SpiTransfer(USART_TypeDef *usart, uint8_t data)
{
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDATA = (uint32_t)data;
  while (!(usart->STATUS & USART_STATUS_TXC)) {
  }
  return (uint8_t)usart->RXDATA;
}

/*
	usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits16;
	USART_SpiTransfer16
	usart->FRAME = (usart->FRAME & ~(_USART_FRAME_DATABITS_MASK)) | usartDatabits8;
*/
uint16_t USART_SpiTransfer16(USART_TypeDef *usart, uint16_t data)
{
	while (!(usart->STATUS & USART_STATUS_TXBL))
		;
	usart->TXDOUBLE = (uint32_t)data;
	while (!(usart->STATUS & USART_STATUS_TXC))
		;
	return (uint16_t)usart->RXDOUBLE;
}


/***************************************************************************//**
 * @brief
 *   Transmit one 4-9 bit frame.
 *
 * @details
 *   Depending on the frame length configuration, 4-8 (least significant) bits from
 *   @p data are transmitted. If the frame length is 9, 8 bits are transmitted from
 *   @p data and one bit as specified by CTRL register, BIT8DV field.
 *   See USART_TxExt() for transmitting 9 bit frame with full control of
 *   all 9 bits.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is full until the buffer becomes available.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] data
 *   Data to transmit. See details above for more information.
 ******************************************************************************/
void USART_Tx(USART_TypeDef *usart, uint8_t data)
{
  /* Check that transmit buffer is empty */
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDATA = (uint32_t)data;
}

/***************************************************************************//**
 * @brief
 *   Transmit two 4-9 bit frames or one 10-16 bit frame.
 *
 * @details
 *   Depending on the frame length configuration, 4-8 (least significant) bits from
 *   each byte in @p data are transmitted. If frame length is 9, 8 bits are
 *   transmitted from each byte in @p data adding one bit as specified by the CTRL
 *   register, BIT8DV field, to each byte. See USART_TxDoubleExt()
 *   for transmitting two 9 bit frames with full control of all 9 bits.
 *
 *   If the frame length is 10-16, 10-16 (least significant) bits from @p data
 *   are transmitted.
 *
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is full until the buffer becomes available.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] data
 *   Data to transmit, the least significant byte holds the frame transmitted
 *   first. See details above for more info.
 ******************************************************************************/
void USART_TxDouble(USART_TypeDef *usart, uint16_t data)
{
  /* Check that transmit buffer is empty */
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDOUBLE = (uint32_t)data;
}

/***************************************************************************//**
 * @brief
 *   Transmit two 4-9 bit frames or one 10-16 bit frame with extended control.
 *
 * @details
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is full until the buffer becomes available.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] data
 *   Data to transmit with extended control. Contains two 16 bit words
 *   concatenated. Least significant word holds the frame transmitted first. If the frame
 *   length is 4-9, two frames with 4-9 least significant bits from each 16 bit
 *   word are transmitted.
 * @par
 *   If the frame length is 10-16 bits, 8 data bits are taken from the least
 *   significant 16 bit word and the remaining bits from the other 16 bit word.
 * @par
 *   Additional control bits are available as documented in the reference
 *   manual (set to 0 if not used). For 10-16 bit frame length, these control
 *   bits are taken from the most significant 16 bit word.
 ******************************************************************************/
void USART_TxDoubleExt(USART_TypeDef *usart, uint32_t data)
{
  /* Check that transmit buffer is empty. */
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDOUBLEX = data;
}

/***************************************************************************//**
 * @brief
 *   Transmit one 4-9 bit frame with extended control.
 *
 * @details
 *   Notice that possible parity/stop bits in asynchronous mode are not
 *   considered part of a specified frame bit length.
 *
 * @note
 *   This function will stall if the buffer is full until the buffer becomes available.
 *
 * @param[in] usart
 *   A pointer to the USART/UART peripheral register block.
 *
 * @param[in] data
 *   Data to transmit with extended control. Least significant bit contains
 *   frame bits. Additional control bits are available as documented in
 *   the reference manual (set to 0 if not used).
 ******************************************************************************/
void USART_TxExt(USART_TypeDef *usart, uint16_t data)
{
  /* Check that the transmit buffer is empty. */
  while (!(usart->STATUS & USART_STATUS_TXBL)) {
  }
  usart->TXDATAX = (uint32_t)data;
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
