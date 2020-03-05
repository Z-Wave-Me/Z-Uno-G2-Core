#include "Arduino.h"
#include "CrtxTimer.h"
void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init) {

  /* Stop timer if specified to be disabled (dosn't hurt if already stopped) */
  if (!(init->enable)) {
    timer->CMD = TIMER_CMD_STOP;
  }

  /* Reset counter */
  timer->CNT = _TIMER_CNT_RESETVALUE;

  timer->CTRL = ((uint32_t)(init->prescale)     << _TIMER_CTRL_PRESC_SHIFT)
                | ((uint32_t)(init->clkSel)     << _TIMER_CTRL_CLKSEL_SHIFT)
                | ((uint32_t)(init->fallAction) << _TIMER_CTRL_FALLA_SHIFT)
                | ((uint32_t)(init->riseAction) << _TIMER_CTRL_RISEA_SHIFT)
                | ((uint32_t)(init->mode)       << _TIMER_CTRL_MODE_SHIFT)
                | (init->debugRun               ?   TIMER_CTRL_DEBUGRUN  : 0)
                | (init->dmaClrAct              ?   TIMER_CTRL_DMACLRACT : 0)
                | (init->quadModeX4             ?   TIMER_CTRL_QDM_X4    : 0)
                | (init->oneShot                ?   TIMER_CTRL_OSMEN     : 0)

                | (init->count2x                ?   TIMER_CTRL_X2CNT     : 0)
                | (init->ati                    ?   TIMER_CTRL_ATI       : 0)
                | (init->sync                   ?   TIMER_CTRL_SYNC      : 0);

  /* Start timer if specified to be enabled (dosn't hurt if already started) */
  if (init->enable) {
    timer->CMD = TIMER_CMD_START;
  }
}

/***************************************************************************//**
 * @brief
 *   Initialize TIMER compare/capture channel.
 *
 * @details
 *   Notice that if operating channel in compare mode, the CCV and CCVB register
 *   must be set separately as required.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] ch
 *   Compare/capture channel to init for.
 *
 * @param[in] init
 *   Pointer to TIMER initialization structure.
 ******************************************************************************/
void TIMER_InitCC(TIMER_TypeDef *timer,
                  unsigned int ch,
                  const TIMER_InitCC_TypeDef *init) {

  timer->CC[ch].CTRL =
    ((uint32_t)(init->eventCtrl) << _TIMER_CC_CTRL_ICEVCTRL_SHIFT)
    | ((uint32_t)(init->edge)    << _TIMER_CC_CTRL_ICEDGE_SHIFT)
    | ((uint32_t)(init->prsSel)  << _TIMER_CC_CTRL_PRSSEL_SHIFT)
    | ((uint32_t)(init->cufoa)   << _TIMER_CC_CTRL_CUFOA_SHIFT)
    | ((uint32_t)(init->cofoa)   << _TIMER_CC_CTRL_COFOA_SHIFT)
    | ((uint32_t)(init->cmoa)    << _TIMER_CC_CTRL_CMOA_SHIFT)
    | ((uint32_t)(init->mode)    << _TIMER_CC_CTRL_MODE_SHIFT)
    | (init->filter              ?   TIMER_CC_CTRL_FILT_ENABLE : 0)
    | (init->prsInput            ?   TIMER_CC_CTRL_INSEL_PRS   : 0)
    | (init->coist               ?   TIMER_CC_CTRL_COIST       : 0)
    | (init->outInvert           ?   TIMER_CC_CTRL_OUTINV      : 0);
}