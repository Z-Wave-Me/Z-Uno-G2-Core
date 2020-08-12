#include "Arduino.h"
#include "CrtxTimer.h"


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initialize TIMER.
 *
 * @details
 *   Notice that the counter top must be configured separately with, for instance
 *   TIMER_TopSet(). In addition, compare/capture and dead-time insertion
 *   initialization must be initialized separately if used, which should probably
 *   be done prior to using this function if configuring the TIMER to
 *   start when initialization is completed.
 *
 * @param[in] timer
 *   A pointer to the TIMER peripheral register block.
 *
 * @param[in] init
 *   A pointer to the TIMER initialization structure.
 ******************************************************************************/
void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));
  uint32_t ctrlRegVal = 0;

#if defined (_TIMER_CFG_PRESC_SHIFT)
  TIMER_SyncWait(timer);
  timer->EN_CLR = TIMER_EN_EN;
  timer->CFG = ((uint32_t)init->prescale << _TIMER_CFG_PRESC_SHIFT)
               | ((uint32_t)init->clkSel << _TIMER_CFG_CLKSEL_SHIFT)
               | ((uint32_t)init->mode   << _TIMER_CFG_MODE_SHIFT)
               | (init->debugRun         ?   TIMER_CFG_DEBUGRUN  : 0)
               | (init->dmaClrAct        ?   TIMER_CFG_DMACLRACT : 0)
               | (init->quadModeX4       ?   TIMER_CFG_QDM_X4    : 0)
               | (init->oneShot          ?   TIMER_CFG_OSMEN     : 0)
               | (init->sync             ?   TIMER_CFG_SYNC      : 0)
               | (init->ati              ?   TIMER_CFG_ATI       : 0);
  timer->EN_SET = TIMER_EN_EN;
#endif

  /* Stop the timer if specified to be disabled (doesn't hurt if already stopped). */
  if (!(init->enable)) {
    timer->CMD = TIMER_CMD_STOP;
  }

  /* Reset the counter. */
  timer->CNT = _TIMER_CNT_RESETVALUE;

#if defined(_SILICON_LABS_32B_SERIES_2)
  ctrlRegVal = ((uint32_t)init->fallAction   << _TIMER_CTRL_FALLA_SHIFT)
               | ((uint32_t)init->riseAction << _TIMER_CTRL_RISEA_SHIFT)
               | (init->count2x              ?   TIMER_CTRL_X2CNT     : 0);
#else
  ctrlRegVal = ((uint32_t)init->prescale     << _TIMER_CTRL_PRESC_SHIFT)
               | ((uint32_t)init->clkSel     << _TIMER_CTRL_CLKSEL_SHIFT)
               | ((uint32_t)init->fallAction << _TIMER_CTRL_FALLA_SHIFT)
               | ((uint32_t)init->riseAction << _TIMER_CTRL_RISEA_SHIFT)
               | ((uint32_t)init->mode       << _TIMER_CTRL_MODE_SHIFT)
               | (init->debugRun             ?   TIMER_CTRL_DEBUGRUN  : 0)
               | (init->dmaClrAct            ?   TIMER_CTRL_DMACLRACT : 0)
               | (init->quadModeX4           ?   TIMER_CTRL_QDM_X4    : 0)
               | (init->oneShot              ?   TIMER_CTRL_OSMEN     : 0)
               | (init->sync                 ?   TIMER_CTRL_SYNC      : 0);
#if defined(TIMER_CTRL_X2CNT) && defined(TIMER_CTRL_ATI)
  ctrlRegVal |= (init->count2x              ?   TIMER_CTRL_X2CNT     : 0)
                | (init->ati                ?   TIMER_CTRL_ATI       : 0);
#endif
#endif

  timer->CTRL = ctrlRegVal;

  /* Start the timer if specified to be enabled (doesn't hurt if already started). */
  if (init->enable) {
    timer->CMD = TIMER_CMD_START;
  }
}

/***************************************************************************//**
 * @brief
 *   Initialize the TIMER compare/capture channel.
 *
 * @details
 *   Notice that if operating the channel in compare mode, the CCV and CCVB register
 *   must be set separately, as required.
 *
 * @param[in] timer
 *   A pointer to the TIMER peripheral register block.
 *
 * @param[in] ch
 *   A compare/capture channel to initialize for.
 *
 * @param[in] init
 *   A pointer to the TIMER initialization structure.
 ******************************************************************************/
void TIMER_InitCC(TIMER_TypeDef *timer,
                  unsigned int ch,
                  const TIMER_InitCC_TypeDef *init)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));
  EFM_ASSERT(TIMER_CH_VALID(ch));

#if defined (_TIMER_CC_CFG_MASK)
  TIMER_SyncWait(timer);
  timer->EN_CLR = TIMER_EN_EN;
  timer->CC[ch].CFG =
    ((uint32_t)init->mode        << _TIMER_CC_CFG_MODE_SHIFT)
    | (init->filter              ?   TIMER_CC_CFG_FILT_ENABLE : 0)
    | (init->coist               ?   TIMER_CC_CFG_COIST       : 0)
    | ((uint32_t)init->prsOutput << _TIMER_CC_CFG_PRSCONF_SHIFT);

  if (init->prsInput) {
    timer->CC[ch].CFG |= (uint32_t)init->prsInputType << _TIMER_CC_CFG_INSEL_SHIFT;
    bool async = (init->prsInputType != timerPrsInputSync);
    timerPrsConfig(timer, ch, init->prsSel, async);
  } else {
    timer->CC[ch].CFG |= TIMER_CC_CFG_INSEL_PIN;
  }
  timer->EN_SET = TIMER_EN_EN;

  timer->CC[ch].CTRL =
    ((uint32_t)init->eventCtrl << _TIMER_CC_CTRL_ICEVCTRL_SHIFT)
    | ((uint32_t)init->edge    << _TIMER_CC_CTRL_ICEDGE_SHIFT)
    | ((uint32_t)init->cufoa   << _TIMER_CC_CTRL_CUFOA_SHIFT)
    | ((uint32_t)init->cofoa   << _TIMER_CC_CTRL_COFOA_SHIFT)
    | ((uint32_t)init->cmoa    << _TIMER_CC_CTRL_CMOA_SHIFT)
    | (init->outInvert         ?   TIMER_CC_CTRL_OUTINV : 0);
#else
  timer->CC[ch].CTRL =
    ((uint32_t)init->eventCtrl   << _TIMER_CC_CTRL_ICEVCTRL_SHIFT)
    | ((uint32_t)init->edge      << _TIMER_CC_CTRL_ICEDGE_SHIFT)
    | ((uint32_t)init->prsSel    << _TIMER_CC_CTRL_PRSSEL_SHIFT)
    | ((uint32_t)init->cufoa     << _TIMER_CC_CTRL_CUFOA_SHIFT)
    | ((uint32_t)init->cofoa     << _TIMER_CC_CTRL_COFOA_SHIFT)
    | ((uint32_t)init->cmoa      << _TIMER_CC_CTRL_CMOA_SHIFT)
    | ((uint32_t)init->mode      << _TIMER_CC_CTRL_MODE_SHIFT)
    | (init->filter              ?   TIMER_CC_CTRL_FILT_ENABLE : 0)
    | (init->prsInput            ?   TIMER_CC_CTRL_INSEL_PRS   : 0)
    | (init->coist               ?   TIMER_CC_CTRL_COIST       : 0)
    | (init->outInvert           ?   TIMER_CC_CTRL_OUTINV      : 0)
#if defined(_TIMER_CC_CTRL_PRSCONF_MASK)
    | ((uint32_t)init->prsOutput << _TIMER_CC_CTRL_PRSCONF_SHIFT)
#endif
  ;
#endif
}

#if defined(_TIMER_DTCTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Initialize the TIMER DTI unit.
 *
 * @param[in] timer
 *   A pointer to the TIMER peripheral register block.
 *
 * @param[in] init
 *   A pointer to the TIMER DTI initialization structure.
 ******************************************************************************/
void TIMER_InitDTI(TIMER_TypeDef *timer, const TIMER_InitDTI_TypeDef *init)
{
  EFM_ASSERT(TIMER0 == timer);

  /* Make sure the DTI unit is disabled while initializing. */
  TIMER_EnableDTI(timer, false);

#if defined (_TIMER_DTCFG_MASK)
  TIMER_SyncWait(timer);
  timer->EN_CLR = TIMER_EN_EN;
  timer->DTCFG = (init->autoRestart       ?   TIMER_DTCFG_DTDAS   : 0)
                 | (init->enablePrsSource ?   TIMER_DTCFG_DTPRSEN : 0);
  if (init->enablePrsSource) {
    timerPrsConfig(timer, TIMER_INPUT_CHANNEL_DTI, init->prsSel, true);
  }

  timer->DTTIMECFG =
    ((uint32_t)init->prescale   << _TIMER_DTTIMECFG_DTPRESC_SHIFT)
    | ((uint32_t)init->riseTime << _TIMER_DTTIMECFG_DTRISET_SHIFT)
    | ((uint32_t)init->fallTime << _TIMER_DTTIMECFG_DTFALLT_SHIFT);

  timer->DTFCFG =
    (init->enableFaultSourceCoreLockup ?   TIMER_DTFCFG_DTLOCKUPFEN : 0)
    | (init->enableFaultSourceDebugger ?   TIMER_DTFCFG_DTDBGFEN    : 0)
    | (init->enableFaultSourcePrsSel0  ?   TIMER_DTFCFG_DTPRS0FEN   : 0)
    | (init->enableFaultSourcePrsSel1  ?   TIMER_DTFCFG_DTPRS1FEN   : 0)
    | ((uint32_t)(init->faultAction)   << _TIMER_DTFCFG_DTFA_SHIFT);

  if (init->enableFaultSourcePrsSel0) {
    timerPrsConfig(timer, TIMER_INPUT_CHANNEL_DTIFS1, init->faultSourcePrsSel0, true);
  }
  if (init->enableFaultSourcePrsSel1) {
    timerPrsConfig(timer, TIMER_INPUT_CHANNEL_DTIFS2, init->faultSourcePrsSel1, true);
  }

  timer->EN_SET = TIMER_EN_EN;
#endif

#if defined(TIMER_DTCTRL_DTDAS)
  /* Set up the DTCTRL register.
     The enable bit will be set at the end of the function if specified. */
  timer->DTCTRL =
    (init->autoRestart              ?   TIMER_DTCTRL_DTDAS   : 0)
    | (init->activeLowOut           ?   TIMER_DTCTRL_DTIPOL  : 0)
    | (init->invertComplementaryOut ?   TIMER_DTCTRL_DTCINV  : 0)
    | (init->enablePrsSource        ?   TIMER_DTCTRL_DTPRSEN : 0)
    | ((uint32_t)(init->prsSel)     << _TIMER_DTCTRL_DTPRSSEL_SHIFT);
#endif

#if defined (TIMER_DTCFG_DTDAS)
  timer->DTCTRL = (init->activeLowOut             ? TIMER_DTCTRL_DTIPOL  : 0)
                  | (init->invertComplementaryOut ? TIMER_DTCTRL_DTCINV  : 0);
#endif

#if defined (_TIMER_DTTIME_DTPRESC_SHIFT)
  /* Set up the DTTIME register. */
  timer->DTTIME = ((uint32_t)init->prescale   << _TIMER_DTTIME_DTPRESC_SHIFT)
                  | ((uint32_t)init->riseTime << _TIMER_DTTIME_DTRISET_SHIFT)
                  | ((uint32_t)init->fallTime << _TIMER_DTTIME_DTFALLT_SHIFT);
#endif

#if defined (TIMER_DTFC_DTLOCKUPFEN)
  /* Set up the DTFC register. */
  timer->DTFC =
    (init->enableFaultSourceCoreLockup    ?   TIMER_DTFC_DTLOCKUPFEN : 0)
    | (init->enableFaultSourceDebugger    ?   TIMER_DTFC_DTDBGFEN    : 0)
    | (init->enableFaultSourcePrsSel0     ?   TIMER_DTFC_DTPRS0FEN   : 0)
    | (init->enableFaultSourcePrsSel1     ?   TIMER_DTFC_DTPRS1FEN   : 0)
    | ((uint32_t)init->faultAction        << _TIMER_DTFC_DTFA_SHIFT)
    | ((uint32_t)init->faultSourcePrsSel0 << _TIMER_DTFC_DTPRS0FSEL_SHIFT)
    | ((uint32_t)init->faultSourcePrsSel1 << _TIMER_DTFC_DTPRS1FSEL_SHIFT);
#endif

  /* Set up the DTOGEN register. */
  timer->DTOGEN = init->outputsEnableMask;

  /* Clear any previous DTI faults.  */
  TIMER_ClearDTIFault(timer, TIMER_GetDTIFault(timer));

  /* Enable/disable before returning. */
  TIMER_EnableDTI(timer, init->enable);
}
#endif

/***************************************************************************//**
 * @brief
 *   Reset the TIMER to the same state that it was in after a hardware reset.
 *
 * @note
 *   The ROUTE register is NOT reset by this function to allow for
 *   a centralized setup of this feature.
 *
 * @param[in] timer
 *   A pointer to the TIMER peripheral register block.
 ******************************************************************************/
void TIMER_Reset(TIMER_TypeDef *timer)
{
  int i;

  EFM_ASSERT(TIMER_REF_VALID(timer));

  /* Make sure disabled first, before resetting other registers. */
  timer->CMD = TIMER_CMD_STOP;

  timer->CTRL = _TIMER_CTRL_RESETVALUE;
  timer->IEN  = _TIMER_IEN_RESETVALUE;
#if defined (TIMER_HAS_SET_CLEAR)
  timer->IF_CLR = _TIMER_IF_MASK;
#else
  timer->IFC  = _TIMER_IFC_MASK;
#endif
  timer->TOPB = _TIMER_TOPB_RESETVALUE;
  /* Write TOP after TOPB to invalidate TOPB (clear TIMER_STATUS_TOPBV). */
  timer->TOP  = _TIMER_TOP_RESETVALUE;
  timer->CNT  = _TIMER_CNT_RESETVALUE;
  /* Do not reset the route register, setting should be done independently. */
  /* Note: The ROUTE register may be locked by the DTLOCK register. */

  for (i = 0; TIMER_CH_VALID(i); i++) {
    timer->CC[i].CTRL = _TIMER_CC_CTRL_RESETVALUE;
#if defined (_TIMER_CC_CCV_RESETVALUE) && defined (_TIMER_CC_CCVB_RESETVALUE)
    timer->CC[i].CCV  = _TIMER_CC_CCV_RESETVALUE;
    timer->CC[i].CCVB = _TIMER_CC_CCVB_RESETVALUE;
#endif
#if defined (_TIMER_CC_OC_RESETVALUE) && defined (_TIMER_CC_OCB_RESETVALUE) \
    && defined (_TIMER_CC_ICF_RESETVALUE) && defined (_TIMER_CC_ICOF_RESETVALUE)
    timer->CC[i].OC     = _TIMER_CC_OC_RESETVALUE;
    timer->CC[i].OCB    = _TIMER_CC_OCB_RESETVALUE;
#endif
  }

  /* Reset dead time insertion module, which has no effect on timers without DTI. */
#if defined(_TIMER_DTCFG_MASK)
  timer->DTLOCK   = TIMER_DTLOCK_DTILOCKKEY_UNLOCK;
  timer->DTCTRL   = _TIMER_DTCTRL_RESETVALUE;
  timer->DTOGEN   = _TIMER_DTOGEN_RESETVALUE;
  timer->DTFAULTC = _TIMER_DTFAULTC_MASK;
#elif defined(TIMER_DTLOCK_LOCKKEY_UNLOCK)
  /* Unlock DTI registers first if locked. */
  timer->DTLOCK   = TIMER_DTLOCK_LOCKKEY_UNLOCK;
  timer->DTCTRL   = _TIMER_DTCTRL_RESETVALUE;
  timer->DTTIME   = _TIMER_DTTIME_RESETVALUE;
  timer->DTFC     = _TIMER_DTFC_RESETVALUE;
  timer->DTOGEN   = _TIMER_DTOGEN_RESETVALUE;
  timer->DTFAULTC = _TIMER_DTFAULTC_MASK;
#endif

#if defined(_TIMER_CFG_MASK)
  TIMER_SyncWait(timer);
  /* CFG registers must be reset after the timer is disabled */
  timer->EN_CLR = TIMER_EN_EN;
  timer->CFG = _TIMER_CFG_RESETVALUE;
  for (i = 0; TIMER_CH_VALID(i); i++) {
    timer->CC[i].CFG = _TIMER_CC_CFG_RESETVALUE;
  }
  timer->DTCFG = _TIMER_DTCFG_RESETVALUE;
  timer->DTFCFG = _TIMER_DTFCFG_RESETVALUE;
  timer->DTTIMECFG = _TIMER_DTTIMECFG_RESETVALUE;
#endif
}

#if defined(TIMER_STATUS_SYNCBUSY)
/**
 * @brief Wait for pending synchronization to finish
 *
 * @param[in] timer
 */
void TIMER_SyncWait(TIMER_TypeDef * timer)
{
  while (((timer->EN & TIMER_EN_EN) != 0U)
         && ((timer->STATUS & TIMER_STATUS_SYNCBUSY) != 0U)) {
    /* Wait for synchronization to complete */
  }
}
#endif