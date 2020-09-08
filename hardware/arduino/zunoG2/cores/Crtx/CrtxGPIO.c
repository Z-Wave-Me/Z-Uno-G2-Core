#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"

void GPIO_EM4EnablePinWakeup(uint32_t pinmask, uint32_t polaritymask) {
  GPIO->EXTILEVEL &= ~pinmask;
  GPIO->EXTILEVEL |= pinmask & polaritymask;
  GPIO->EM4WUEN  |= pinmask;                /* Enable wakeup */
  GPIO_EM4SetPinRetention(true);            /* Enable pin retention */
  GPIO_IntClear(pinmask);
}

/***************************************************************************//**
 * @brief
 *   Configure GPIO external pin interrupt.
 *
 * @details
 *   It is recommended to disable interrupts before configuring a GPIO pin interrupt.
 *   See @ref GPIO_IntDisable() for more information.
 *
 *   The actual GPIO interrupt handler must be in place before enabling the
 *   interrupt.
 *
 *   Notice that any pending interrupt for the selected interrupt is cleared
 *   by this function.
 *
 * @note
 *   On series 0 devices the pin number parameter is not used. The
 *   pin number used on these devices is hardwired to the interrupt with the
 *   same number. @n
 *   On series 1 devices, pin number can be selected freely within a group.
 *   Interrupt numbers are divided into 4 groups (intNo / 4) and valid pin
 *   number within the interrupt groups are:
 *       0: pins 0-3   (interrupt number 0-3)
 *       1: pins 4-7   (interrupt number 4-7)
 *       2: pins 8-11  (interrupt number 8-11)
 *       3: pins 12-15 (interrupt number 12-15)
 *
 * @param[in] port
 *   The port to associate with @p pin.
 *
 * @param[in] pin
 *   The pin number on the port.
 *
 * @param[in] intNo
 *   The interrupt number to trigger.
 *
 * @param[in] risingEdge
 *   Set to true if interrupts shall be enabled on rising edge, otherwise false.
 *
 * @param[in] fallingEdge
 *   Set to true if interrupts shall be enabled on falling edge, otherwise false.
 *
 * @param[in] enable
 *   Set to true if interrupt shall be enabled after configuration completed,
 *   false to leave disabled. See @ref GPIO_IntDisable() and @ref GPIO_IntEnable().
 ******************************************************************************/
void GPIO_ExtIntConfig(uint8_t port,
                       unsigned int pin,
                       unsigned int intNo,
                       bool risingEdge,
                       bool fallingEdge,
                       bool enable)
{
  uint32_t tmp = 0;

  /* There are two registers controlling the interrupt configuration:
   * The EXTIPSELL register controls pins 0-7 and EXTIPSELH controls
   * pins 8-15. */
  if (intNo < 8) {
    BUS_RegMaskedWrite(&GPIO->EXTIPSELL,
                       _GPIO_EXTIPSELL_EXTIPSEL0_MASK
                       << (_GPIO_EXTIPSELL_EXTIPSEL1_SHIFT * intNo),
                       port << (_GPIO_EXTIPSELL_EXTIPSEL1_SHIFT * intNo));
  } else {
    tmp = intNo - 8;
    BUS_RegMaskedWrite(&GPIO->EXTIPSELH,
                       _GPIO_EXTIPSELH_EXTIPSEL8_MASK
                       << (_GPIO_EXTIPSELH_EXTIPSEL9_SHIFT * tmp),
                       port << (_GPIO_EXTIPSELH_EXTIPSEL9_SHIFT * tmp));
  }
  /* There are two registers controlling the interrupt/pin number mapping:
   * The EXTIPINSELL register controls interrupt 0-7 and EXTIPINSELH controls
   * interrupt 8-15. */
  if (intNo < 8) {
    BUS_RegMaskedWrite(&GPIO->EXTIPINSELL,
                       _GPIO_EXTIPINSELL_EXTIPINSEL0_MASK
                       << (_GPIO_EXTIPINSELL_EXTIPINSEL1_SHIFT * intNo),
                       ((pin % 4) & _GPIO_EXTIPINSELL_EXTIPINSEL0_MASK)
                       << (_GPIO_EXTIPINSELL_EXTIPINSEL1_SHIFT * intNo));
  } else {
    BUS_RegMaskedWrite(&GPIO->EXTIPINSELH,
                       _GPIO_EXTIPINSELH_EXTIPINSEL8_MASK
                       << (_GPIO_EXTIPINSELH_EXTIPINSEL9_SHIFT * tmp),
                       ((pin % 4) & _GPIO_EXTIPINSELH_EXTIPINSEL8_MASK)
                       << (_GPIO_EXTIPSELH_EXTIPSEL9_SHIFT * tmp));
  }

  /* Enable/disable rising edge */
  BUS_RegBitWrite(&(GPIO->EXTIRISE), intNo, risingEdge);

  /* Enable/disable falling edge */
  BUS_RegBitWrite(&(GPIO->EXTIFALL), intNo, fallingEdge);

  /* Clear any pending interrupt */
  GPIO->IFC = 1 << intNo;

  /* Finally enable/disable interrupt */
  BUS_RegBitWrite(&(GPIO->IEN), intNo, enable);
}