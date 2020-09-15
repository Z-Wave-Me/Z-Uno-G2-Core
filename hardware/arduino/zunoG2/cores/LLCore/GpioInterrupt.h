#ifndef GPIO_INTERRPUT_H
#define GPIO_INTERRPUT_H

/*******************************************************************************
 *******************************   TYPEDEFS   **********************************
 ******************************************************************************/

/**
 * @brief
 *  GPIO interrupt callback function pointer.
 * @details
 *   Parameters:
 *   @li intNo - The pin interrupt number the callback function is invoked for.
 */
typedef void (*GPIOINT_IrqCallbackPtr_t)(uint8_t intNo);

/*******************************************************************************
 ******************************   PROTOTYPES   *********************************
 ******************************************************************************/
void GPIOINT_Init(void);
void GPIOINT_CallbackRegister(uint8_t intNo, GPIOINT_IrqCallbackPtr_t callbackPtr);

/***************************************************************************//**
 * @brief
 *   Unregisters user callback for given pin interrupt number.
 *
 * @details
 *   Use this function to unregister a callback.
 *
 * @param[in] intNo
 *   Pin interrupt number for the callback.
 *
 ******************************************************************************/
__STATIC_INLINE void GPIOINT_CallbackUnRegister(uint8_t intNo)
{
  GPIOINT_CallbackRegister(intNo, 0);
}

#endif // GPIO_INTERRPUT_H