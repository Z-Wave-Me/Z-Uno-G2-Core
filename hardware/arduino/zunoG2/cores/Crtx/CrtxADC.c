#include "Arduino.h"
#include "ZGecko.h"
#include "CrtxADC.h"

/** Validation of ADC register block pointer reference for assert statements. */
#define ADC_REF_VALID(ref)    ((ref) == ADC0)

/** Max ADC clock */
#define ADC_MAX_CLOCK    16000000UL
/** Min ADC clock */
#define ADC_MIN_CLOCK    32000UL

/** Helper defines for selecting ADC calibration and DEVINFO register fields. */
#if defined(_DEVINFO_ADC0CAL0_1V25_GAIN_MASK)
#define DEVINFO_ADC0_GAIN1V25_MASK _DEVINFO_ADC0CAL0_1V25_GAIN_MASK
#elif defined(_DEVINFO_ADC0CAL0_GAIN1V25_MASK)
#define DEVINFO_ADC0_GAIN1V25_MASK _DEVINFO_ADC0CAL0_GAIN1V25_MASK
#endif

#if defined(_DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT)
#define DEVINFO_ADC0_GAIN1V25_SHIFT _DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT
#elif defined(_DEVINFO_ADC0CAL0_GAIN1V25_SHIFT)
#define DEVINFO_ADC0_GAIN1V25_SHIFT _DEVINFO_ADC0CAL0_GAIN1V25_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL0_1V25_OFFSET_MASK)
#define DEVINFO_ADC0_OFFSET1V25_MASK _DEVINFO_ADC0CAL0_1V25_OFFSET_MASK
#elif defined(_DEVINFO_ADC0CAL0_OFFSET1V25_MASK)
#define DEVINFO_ADC0_OFFSET1V25_MASK _DEVINFO_ADC0CAL0_OFFSET1V25_MASK
#endif

#if defined(_DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT)
#define DEVINFO_ADC0_OFFSET1V25_SHIFT _DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT
#elif defined(_DEVINFO_ADC0CAL0_OFFSET1V25_SHIFT)
#define DEVINFO_ADC0_OFFSET1V25_SHIFT _DEVINFO_ADC0CAL0_OFFSET1V25_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL0_2V5_GAIN_MASK)
#define DEVINFO_ADC0_GAIN2V5_MASK _DEVINFO_ADC0CAL0_2V5_GAIN_MASK
#elif defined(_DEVINFO_ADC0CAL0_GAIN2V5_MASK)
#define DEVINFO_ADC0_GAIN2V5_MASK _DEVINFO_ADC0CAL0_GAIN2V5_MASK
#endif

#if defined(_DEVINFO_ADC0CAL0_2V5_GAIN_SHIFT)
#define DEVINFO_ADC0_GAIN2V5_SHIFT _DEVINFO_ADC0CAL0_2V5_GAIN_SHIFT
#elif defined(_DEVINFO_ADC0CAL0_GAIN2V5_SHIFT)
#define DEVINFO_ADC0_GAIN2V5_SHIFT _DEVINFO_ADC0CAL0_GAIN2V5_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL0_2V5_OFFSET_MASK)
#define DEVINFO_ADC0_OFFSET2V5_MASK _DEVINFO_ADC0CAL0_2V5_OFFSET_MASK
#elif defined(_DEVINFO_ADC0CAL0_OFFSET2V5_MASK)
#define DEVINFO_ADC0_OFFSET2V5_MASK _DEVINFO_ADC0CAL0_OFFSET2V5_MASK
#endif

#if defined(_DEVINFO_ADC0CAL0_2V5_OFFSET_SHIFT)
#define DEVINFO_ADC0_OFFSET2V5_SHIFT _DEVINFO_ADC0CAL0_2V5_OFFSET_SHIFT
#elif defined(_DEVINFO_ADC0CAL0_OFFSET2V5_SHIFT)
#define DEVINFO_ADC0_OFFSET2V5_SHIFT _DEVINFO_ADC0CAL0_OFFSET2V5_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL1_VDD_GAIN_MASK)
#define DEVINFO_ADC0_GAINVDD_MASK _DEVINFO_ADC0CAL1_VDD_GAIN_MASK
#elif defined(_DEVINFO_ADC0CAL1_GAINVDD_MASK)
#define DEVINFO_ADC0_GAINVDD_MASK _DEVINFO_ADC0CAL1_GAINVDD_MASK
#endif

#if defined(_DEVINFO_ADC0CAL1_VDD_GAIN_SHIFT)
#define DEVINFO_ADC0_GAINVDD_SHIFT _DEVINFO_ADC0CAL1_VDD_GAIN_SHIFT
#elif defined(_DEVINFO_ADC0CAL1_GAINVDD_SHIFT)
#define DEVINFO_ADC0_GAINVDD_SHIFT _DEVINFO_ADC0CAL1_GAINVDD_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL1_VDD_OFFSET_MASK)
#define DEVINFO_ADC0_OFFSETVDD_MASK _DEVINFO_ADC0CAL1_VDD_OFFSET_MASK
#elif defined(_DEVINFO_ADC0CAL1_OFFSETVDD_MASK)
#define DEVINFO_ADC0_OFFSETVDD_MASK _DEVINFO_ADC0CAL1_OFFSETVDD_MASK
#endif

#if defined(_DEVINFO_ADC0CAL1_VDD_OFFSET_SHIFT)
#define DEVINFO_ADC0_OFFSETVDD_SHIFT _DEVINFO_ADC0CAL1_VDD_OFFSET_SHIFT
#elif defined(_DEVINFO_ADC0CAL1_OFFSETVDD_SHIFT)
#define DEVINFO_ADC0_OFFSETVDD_SHIFT _DEVINFO_ADC0CAL1_OFFSETVDD_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL1_5VDIFF_GAIN_MASK)
#define DEVINFO_ADC0_GAIN5VDIFF_MASK _DEVINFO_ADC0CAL1_5VDIFF_GAIN_MASK
#elif defined(_DEVINFO_ADC0CAL1_GAIN5VDIFF_MASK)
#define DEVINFO_ADC0_GAIN5VDIFF_MASK _DEVINFO_ADC0CAL1_GAIN5VDIFF_MASK
#endif

#if defined(_DEVINFO_ADC0CAL1_5VDIFF_GAIN_SHIFT)
#define DEVINFO_ADC0_GAIN5VDIFF_SHIFT _DEVINFO_ADC0CAL1_5VDIFF_GAIN_SHIFT
#elif defined(_DEVINFO_ADC0CAL1_GAIN5VDIFF_SHIFT)
#define DEVINFO_ADC0_GAIN5VDIFF_SHIFT _DEVINFO_ADC0CAL1_GAIN5VDIFF_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL1_5VDIFF_OFFSET_MASK)
#define DEVINFO_ADC0_OFFSET5VDIFF_MASK _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_MASK
#elif defined(_DEVINFO_ADC0CAL1_OFFSET5VDIFF_MASK)
#define DEVINFO_ADC0_OFFSET5VDIFF_MASK _DEVINFO_ADC0CAL1_OFFSET5VDIFF_MASK
#endif

#if defined(_DEVINFO_ADC0CAL1_5VDIFF_OFFSET_SHIFT)
#define DEVINFO_ADC0_OFFSET5VDIFF_SHIFT _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_SHIFT
#elif defined(_DEVINFO_ADC0CAL1_OFFSET5VDIFF_SHIFT)
#define DEVINFO_ADC0_OFFSET5VDIFF_SHIFT _DEVINFO_ADC0CAL1_OFFSET5VDIFF_SHIFT
#endif

#if defined(_DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_MASK)
#define DEVINFO_ADC0_OFFSET2XVDD_MASK _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_MASK
#elif defined(_DEVINFO_ADC0CAL2_OFFSET2XVDD_MASK)
#define DEVINFO_ADC0_OFFSET2XVDD_MASK _DEVINFO_ADC0CAL2_OFFSET2XVDD_MASK
#endif

#if defined(_DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_SHIFT)
#define DEVINFO_ADC0_OFFSET2XVDD_SHIFT _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_SHIFT
#elif defined(_DEVINFO_ADC0CAL2_OFFSET2XVDD_SHIFT)
#define DEVINFO_ADC0_OFFSET2XVDD_SHIFT _DEVINFO_ADC0CAL2_OFFSET2XVDD_SHIFT
#endif

#if defined(_SILICON_LABS_32B_SERIES_1)
#define FIX_ADC_TEMP_BIAS_EN
#endif

// Нужные куски EMLIB:
/*
    ADC_TimebaseCalc:
          CMU_ClockFreqGet
    ADC_PrescaleCalc:
          CMU_ClockFreqGet
    ADC_Init:
          BUS_RegMaskedWrite


*/

uint8_t ADC_TimebaseCalc(uint32_t hfperFreq)
{
  if (hfperFreq == 0UL) {
    hfperFreq = CMU_ClockFreqGet(cmuClock_HFPER);

    /* Just in case, make sure we get non-zero freq for below calculation */
    if (hfperFreq == 0UL) {
      hfperFreq = 1UL;
    }
  }
  /* Determine number of HFPERCLK cycle >= 1us */
  hfperFreq += 999999UL;
  hfperFreq /= 1000000UL;

  /* Return timebase value (N+1 format) */
  return (uint8_t)(hfperFreq - 1UL);
}
/***************************************************************************//**
 * @brief
 *   Calculate prescaler value used to determine ADC clock.
 *
 * @details
 *   The ADC clock is given by: HFPERCLK / (prescale + 1).
 *
 * @note
 *   The return value is clamped to the max prescaler value hardware supports.
 *
 * @param[in] adcFreq ADC frequency wanted. The frequency will automatically
 *   be adjusted to be within valid range according to reference manual.
 *
 * @param[in] hfperFreq Frequency in Hz of reference HFPER clock. Set to 0 to
 *   use currently defined HFPER clock setting.
 *
 * @return
 *   Prescaler value to use for ADC in order to achieve a clock value
 *   <= @p adcFreq.
 ******************************************************************************/


uint8_t ADC_PrescaleCalc(uint32_t adcFreq, uint32_t hfperFreq)
{
  uint32_t ret;

  /* Make sure selected ADC clock is within valid range */
  if (adcFreq > ADC_MAX_CLOCK) {
    adcFreq = ADC_MAX_CLOCK;
  } else if (adcFreq < ADC_MIN_CLOCK) {
    adcFreq = ADC_MIN_CLOCK;
  } else {
    /* Valid frequency */
  }

  /* Use current HFPER frequency? */
  if (hfperFreq == 0UL) {
    hfperFreq = CMU_ClockFreqGet(cmuClock_HFPER);
  }

  ret = (hfperFreq + adcFreq - 1U) / adcFreq;
  if (ret > 0U) {
    ret--;
  }

  if (ret > (_ADC_CTRL_PRESC_MASK >> _ADC_CTRL_PRESC_SHIFT)) {
    ret = _ADC_CTRL_PRESC_MASK >> _ADC_CTRL_PRESC_SHIFT;
  }

  return (uint8_t)ret;
}

void ADC_Init(ADC_TypeDef *adc, const ADC_Init_TypeDef *init)
{
  uint32_t tmp;
  uint8_t presc = init->prescale;
  if (presc == 0U) {
    /* Assume maximum ADC clock for prescaler 0 */
    presc = ADC_PrescaleCalc(ADC_MAX_CLOCK, 0);
  } else {
    /* Check prescaler bounds against ADC_MAX_CLOCK and ADC_MIN_CLOCK */
    /*
    if ((ADC0->CTRL & _ADC_CTRL_ADCCLKMODE_MASK) == ADC_CTRL_ADCCLKMODE_SYNC)
    {
      EFM_ASSERT(presc >= ADC_PrescaleCalc(ADC_MAX_CLOCK, 0));
      EFM_ASSERT(presc <= ADC_PrescaleCalc(ADC_MIN_CLOCK, 0));
    }*/
  }

  /* Make sure conversion is not in progress */
  adc->CMD = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;

  tmp = ((uint32_t)(init->ovsRateSel) << _ADC_CTRL_OVSRSEL_SHIFT)
        | (((uint32_t)(init->timebase) << _ADC_CTRL_TIMEBASE_SHIFT)
           & _ADC_CTRL_TIMEBASE_MASK)
        | (((uint32_t)(presc) << _ADC_CTRL_PRESC_SHIFT)
           & _ADC_CTRL_PRESC_MASK)
        | ((uint32_t)(init->warmUpMode) << _ADC_CTRL_WARMUPMODE_SHIFT);

  if (init->tailgate) {
    tmp |= ADC_CTRL_TAILGATE;
  }
  adc->CTRL = tmp;

  /* Set ADC EM2 clock configuration */
  BUS_RegMaskedWrite(&ADC0->CTRL,
                     _ADC_CTRL_ADCCLKMODE_MASK | _ADC_CTRL_ASYNCCLKEN_MASK,
                     (uint32_t)init->em2ClockConfig);

}

/***************************************************************************//**
 * @brief
 *   Load ADC calibration register for a selected reference and conversion mode.
 *
 * @details
 *   During production, calibration values are stored in the device
 *   information page for internal references. Notice that for external references,
 *   calibration values must be determined explicitly, and this function
 *   will not modify the calibration register for external references.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] ref
 *   Reference to load calibrated values for. No values are loaded for
 *   external references.
 *
 * @param[in] setScanCal
 *   Select scan mode (true) or single mode (false) calibration load.
 ******************************************************************************/
static void ADC_LoadDevinfoCal(ADC_TypeDef *adc,
                               ADC_Ref_TypeDef ref,
                               bool setScanCal)
{
  uint32_t calReg;
  uint32_t newCal;
  uint32_t mask;
  uint32_t shift;
  __IM uint32_t * diCalReg;

  if (setScanCal) {
    shift = _ADC_CAL_SCANOFFSET_SHIFT;
    mask  = ~(_ADC_CAL_SCANOFFSET_MASK
              | _ADC_CAL_SCANOFFSETINV_MASK
              | _ADC_CAL_SCANGAIN_MASK);
  } else {
    shift = _ADC_CAL_SINGLEOFFSET_SHIFT;
    mask  = ~(_ADC_CAL_SINGLEOFFSET_MASK
              | _ADC_CAL_SINGLEOFFSETINV_MASK
              | _ADC_CAL_SINGLEGAIN_MASK);
  }

  calReg = adc->CAL & mask;
  newCal = 0;

  if (adc == ADC0) {
    diCalReg = &DEVINFO->ADC0CAL0;
  }
  else {
    return;
  }

  switch (ref) {
    case adcRef1V25:
      newCal |= ((diCalReg[0] & DEVINFO_ADC0_GAIN1V25_MASK)
                 >> DEVINFO_ADC0_GAIN1V25_SHIFT)
                << _ADC_CAL_SINGLEGAIN_SHIFT;
      newCal |= ((diCalReg[0] & DEVINFO_ADC0_OFFSET1V25_MASK)
                 >> DEVINFO_ADC0_OFFSET1V25_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[0] & _DEVINFO_ADC0CAL0_NEGSEOFFSET1V25_MASK)
                 >> _DEVINFO_ADC0CAL0_NEGSEOFFSET1V25_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    case adcRef2V5:
      newCal |= ((diCalReg[0] & DEVINFO_ADC0_GAIN2V5_MASK)
                 >> DEVINFO_ADC0_GAIN2V5_SHIFT)
                << _ADC_CAL_SINGLEGAIN_SHIFT;
      newCal |= ((diCalReg[0] & DEVINFO_ADC0_OFFSET2V5_MASK)
                 >> DEVINFO_ADC0_OFFSET2V5_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[0] & _DEVINFO_ADC0CAL0_NEGSEOFFSET2V5_MASK)
                 >> _DEVINFO_ADC0CAL0_NEGSEOFFSET2V5_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    case adcRefVDD:
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_GAINVDD_MASK)
                 >> DEVINFO_ADC0_GAINVDD_SHIFT)
                << _ADC_CAL_SINGLEGAIN_SHIFT;
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_OFFSETVDD_MASK)
                 >> DEVINFO_ADC0_OFFSETVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[1] & _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_MASK)
                 >> _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    case adcRef5VDIFF:
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_GAIN5VDIFF_MASK)
                 >> DEVINFO_ADC0_GAIN5VDIFF_SHIFT)
                << _ADC_CAL_SINGLEGAIN_SHIFT;
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_OFFSET5VDIFF_MASK)
                 >> DEVINFO_ADC0_OFFSET5VDIFF_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[1] & _DEVINFO_ADC0CAL1_NEGSEOFFSET5VDIFF_MASK)
                 >> _DEVINFO_ADC0CAL1_NEGSEOFFSET5VDIFF_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    case adcRef2xVDD:
      /* There is no gain calibration for this reference */
      newCal |= ((diCalReg[2] & DEVINFO_ADC0_OFFSET2XVDD_MASK)
                 >> DEVINFO_ADC0_OFFSET2XVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[2] & _DEVINFO_ADC0CAL2_NEGSEOFFSET2XVDD_MASK)
                 >> _DEVINFO_ADC0CAL2_NEGSEOFFSET2XVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    case adcRefVddxAtt:
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_GAINVDD_MASK)
                 >> DEVINFO_ADC0_GAINVDD_SHIFT)
                << _ADC_CAL_SINGLEGAIN_SHIFT;
      newCal |= ((diCalReg[1] & DEVINFO_ADC0_OFFSETVDD_MASK)
                 >> DEVINFO_ADC0_OFFSETVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSET_SHIFT;
      newCal |= ((diCalReg[1] & _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_MASK)
                 >> _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_SHIFT)
                << _ADC_CAL_SINGLEOFFSETINV_SHIFT;
      break;

    /* For external references, the calibration must be determined for the
       specific application and set by the user. Calibration data is also not
       available for the internal references adcRefVBGR, adcRefVEntropy and
       adcRefVBGRlow. */
    default:
      newCal = 0;
      break;
  }

  adc->CAL = calReg | (newCal << shift);
}
void ADC_InitSingle(ADC_TypeDef *adc, const ADC_InitSingle_TypeDef *init)
{
  uint32_t tmp;

  //EFM_ASSERT(ADC_REF_VALID(adc));

  /* Make sure single conversion is not in progress */
  adc->CMD = ADC_CMD_SINGLESTOP;

  /* Load calibration data for selected reference */
  ADC_LoadDevinfoCal(adc, init->reference, false);

  tmp = 0UL
        | ((uint32_t)init->acqTime << _ADC_SINGLECTRL_AT_SHIFT)
        | ((uint32_t)init->posSel << _ADC_SINGLECTRL_POSSEL_SHIFT)
        | ((uint32_t)init->negSel << _ADC_SINGLECTRL_NEGSEL_SHIFT)
        | ((uint32_t)(init->resolution) << _ADC_SINGLECTRL_RES_SHIFT);

  if (init->prsEnable) {
    tmp |= ADC_SINGLECTRL_PRSEN;
  }

  if (init->leftAdjust) {
    tmp |= ADC_SINGLECTRL_ADJ_LEFT;
  }

  if (init->diff) {
    tmp |= ADC_SINGLECTRL_DIFF;
  }

  if (init->rep) {
    tmp |= ADC_SINGLECTRL_REP;
  }

  /* Force at least 8 cycle acquisition time when reading internal temperature
   * sensor with 1.25V reference */
  if ((init->posSel == adcPosSelTEMP)
      && (init->reference == adcRef1V25)
      && (init->acqTime < adcAcqTime8)) {
    tmp = (tmp & ~_ADC_SINGLECTRL_AT_MASK)
          | ((uint32_t)adcAcqTime8 << _ADC_SINGLECTRL_AT_SHIFT);
  }
  /* Set single reference. Check if reference configuraion is extended to SINGLECTRLX. */
  if (((uint32_t)init->reference & ADC_CTRLX_VREFSEL_REG) != 0UL) {
    /* Select extension register */
    tmp |= ADC_SINGLECTRL_REF_CONF;
  } else {
    tmp |= (uint32_t)init->reference << _ADC_SINGLECTRL_REF_SHIFT;
  }

  adc->SINGLECTRL = tmp;

  /* Update SINGLECTRLX for reference select and PRS select */
  tmp = adc->SINGLECTRLX & ~(_ADC_SINGLECTRLX_VREFSEL_MASK
                             | _ADC_SINGLECTRLX_PRSSEL_MASK
                             | _ADC_SINGLECTRLX_FIFOOFACT_MASK);
  if (((uint32_t)init->reference & ADC_CTRLX_VREFSEL_REG) != 0UL) {
    tmp |= ((uint32_t)init->reference & ~ADC_CTRLX_VREFSEL_REG)
           << _ADC_SINGLECTRLX_VREFSEL_SHIFT;
  }

  tmp |= (uint32_t)init->prsSel << _ADC_SINGLECTRLX_PRSSEL_SHIFT;

  if (init->fifoOverwrite) {
    tmp |= ADC_SINGLECTRLX_FIFOOFACT_OVERWRITE;
  }

  adc->SINGLECTRLX = tmp;

  /* Set DMA availability in EM2 */
  BUS_RegBitWrite(&adc->CTRL,
                  _ADC_CTRL_SINGLEDMAWU_SHIFT,
                  (uint32_t)init->singleDmaEm2Wu);

  if (init->posSel == adcPosSelTEMP) {
    /* ADC should always use low accuracy setting when reading the internal
     * temperature sensor on Series 1 devices. Using high
     * accuracy setting can introduce a glitch. */
    BUS_RegBitWrite(&adc->BIASPROG, _ADC_BIASPROG_GPBIASACC_SHIFT, 1);
  } else {
    BUS_RegBitWrite(&adc->BIASPROG, _ADC_BIASPROG_GPBIASACC_SHIFT, 0);
  }

}
void ADC_Reset(ADC_TypeDef *adc)
{
  /* Stop conversions, before resetting other registers. */
  adc->CMD          = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;
  adc->SINGLECTRL   = _ADC_SINGLECTRL_RESETVALUE;
  adc->SINGLECTRLX  = _ADC_SINGLECTRLX_RESETVALUE;
  adc->SCANCTRL     = _ADC_SCANCTRL_RESETVALUE;
  adc->SCANCTRLX    = _ADC_SCANCTRLX_RESETVALUE;
  adc->CTRL         = _ADC_CTRL_RESETVALUE;
  adc->IEN          = _ADC_IEN_RESETVALUE;
  adc->IFC          = _ADC_IFC_MASK;
  adc->BIASPROG     = _ADC_BIASPROG_RESETVALUE;
  adc->SCANMASK     = _ADC_SCANMASK_RESETVALUE;
  adc->SCANINPUTSEL = _ADC_SCANINPUTSEL_RESETVALUE;
  adc->SCANNEGSEL   = _ADC_SCANNEGSEL_RESETVALUE;

  /* Clear data FIFOs */
  adc->SINGLEFIFOCLEAR |= ADC_SINGLEFIFOCLEAR_SINGLEFIFOCLEAR;
  adc->SCANFIFOCLEAR   |= ADC_SCANFIFOCLEAR_SCANFIFOCLEAR;

  /* Load calibration values for the 1V25 internal reference. */
  ADC_LoadDevinfoCal(adc, adcRef1V25, false);
  ADC_LoadDevinfoCal(adc, adcRef1V25, true);

}
ADC_PosSel_TypeDef zme_ADC_PIN2Channel(uint8_t pin){
  switch(pin){
      /*
      case A0:
          return adcPosSelAPORT3XCH30;
      case A1:
          return adcPosSelAPORT4XCH31;
      case A2:   
          return adcPosSelAPORT1XCH6;
      case A3:
          return adcPosSelAPORT2XCH7;
          */
#if ZUNO_PIN_V == 1
      case A0:
          return adcPosSelAPORT1XCH22;
      case A1:
          return adcPosSelAPORT2XCH23;
      case A2:   
          return adcPosSelAPORT4XCH1;
      case A3:
          return adcPosSelAPORT3XCH2;
#elif ZUNO_PIN_V == 2
      case A0:
          return adcPosSelAPORT1XCH22;
      case A1:
          return adcPosSelAPORT2XCH23;
      case A2:   
          return adcPosSelAPORT4XCH1;
      case A3:
          return adcPosSelAPORT3XCH2;
#elif ZUNO_PIN_V == 3
      case A0:
          return adcPosSelAPORT1XCH22;
      case A1:
          return adcPosSelAPORT2XCH23;
      case A2:   
          return adcPosSelAPORT4XCH1;
      case A3:
          return adcPosSelAPORT3XCH2;
#elif ZUNO_PIN_V == 4
      case A0:
          return adcPosSelAPORT1XCH22;
      case A1:
          return adcPosSelAPORT2XCH23;
      case A2:   
          return adcPosSelAPORT4XCH1;
      case A3:
          return adcPosSelAPORT3XCH2;
#elif ZUNO_PIN_V == 6
      case A0:
          return adcPosSelAPORT1XCH22;
      case A1:
          return adcPosSelAPORT2XCH23;
      case A2:   
          return adcPosSelAPORT4XCH1;
      case A3:
          return adcPosSelAPORT3XCH2;
#elif ZUNO_PIN_V == 1000

#else
	#error ZUNO_PIN_V
#endif
      case BATTERY:
          return adcPosSelAVDD;
      default:
          return adcPosSelAVDD;
  }

}
void zme_ADC_Enable(){
   ADC_Init_TypeDef adcInit = ADC_INIT_DEFAULT;
   // Enable ADC clock
   CMU_ClockEnable(cmuClock_ADC0, true);
   // Setup ADC
   adcInit.timebase = ADC_TimebaseCalc(0);
   // Set ADC clock to 7 MHz, use default HFPERCLK
   adcInit.prescale = ADC_PrescaleCalc(7000000, 0);
   ADC_Init(ADC0, &adcInit);
}
void zme_ADC_Disable(){
   ADC_Reset(ADC0);
   // Disable ADC clock
   CMU_ClockEnable(cmuClock_ADC0, false);
}