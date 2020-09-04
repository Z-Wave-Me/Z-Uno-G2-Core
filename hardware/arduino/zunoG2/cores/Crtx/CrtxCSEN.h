#ifndef CORTEXCSEN_H
#define CORTEXCSEN_H
#include "ZGecko.h"

/**************************************************************************//**
 * @addtogroup EFR32FG13P_CSEN
 * @{
 * @defgroup EFR32FG13P_CSEN_BitFields  CSEN Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CSEN CTRL */
#define _CSEN_CTRL_RESETVALUE                                0x00030000UL                               /**< Default value for CSEN_CTRL */
#define _CSEN_CTRL_MASK                                      0x1FFFF336UL                               /**< Mask for CSEN_CTRL */
#define CSEN_CTRL_EN                                         (0x1UL << 1)                               /**< CSEN Enable */
#define _CSEN_CTRL_EN_SHIFT                                  1                                          /**< Shift value for CSEN_EN */
#define _CSEN_CTRL_EN_MASK                                   0x2UL                                      /**< Bit mask for CSEN_EN */
#define _CSEN_CTRL_EN_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_EN_DISABLE                                0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_EN_ENABLE                                 0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_EN_DEFAULT                                 (_CSEN_CTRL_EN_DEFAULT << 1)               /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_EN_DISABLE                                 (_CSEN_CTRL_EN_DISABLE << 1)               /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_EN_ENABLE                                  (_CSEN_CTRL_EN_ENABLE << 1)                /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_CMPPOL                                     (0x1UL << 2)                               /**< CSEN Digital Comparator Polarity Select */
#define _CSEN_CTRL_CMPPOL_SHIFT                              2                                          /**< Shift value for CSEN_CMPPOL */
#define _CSEN_CTRL_CMPPOL_MASK                               0x4UL                                      /**< Bit mask for CSEN_CMPPOL */
#define _CSEN_CTRL_CMPPOL_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CMPPOL_GT                                 0x00000000UL                               /**< Mode GT for CSEN_CTRL */
#define _CSEN_CTRL_CMPPOL_LTE                                0x00000001UL                               /**< Mode LTE for CSEN_CTRL */
#define CSEN_CTRL_CMPPOL_DEFAULT                             (_CSEN_CTRL_CMPPOL_DEFAULT << 2)           /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CMPPOL_GT                                  (_CSEN_CTRL_CMPPOL_GT << 2)                /**< Shifted mode GT for CSEN_CTRL */
#define CSEN_CTRL_CMPPOL_LTE                                 (_CSEN_CTRL_CMPPOL_LTE << 2)               /**< Shifted mode LTE for CSEN_CTRL */
#define _CSEN_CTRL_CM_SHIFT                                  4                                          /**< Shift value for CSEN_CM */
#define _CSEN_CTRL_CM_MASK                                   0x30UL                                     /**< Bit mask for CSEN_CM */
#define _CSEN_CTRL_CM_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CM_SGL                                    0x00000000UL                               /**< Mode SGL for CSEN_CTRL */
#define _CSEN_CTRL_CM_SCAN                                   0x00000001UL                               /**< Mode SCAN for CSEN_CTRL */
#define _CSEN_CTRL_CM_CONTSGL                                0x00000002UL                               /**< Mode CONTSGL for CSEN_CTRL */
#define _CSEN_CTRL_CM_CONTSCAN                               0x00000003UL                               /**< Mode CONTSCAN for CSEN_CTRL */
#define CSEN_CTRL_CM_DEFAULT                                 (_CSEN_CTRL_CM_DEFAULT << 4)               /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CM_SGL                                     (_CSEN_CTRL_CM_SGL << 4)                   /**< Shifted mode SGL for CSEN_CTRL */
#define CSEN_CTRL_CM_SCAN                                    (_CSEN_CTRL_CM_SCAN << 4)                  /**< Shifted mode SCAN for CSEN_CTRL */
#define CSEN_CTRL_CM_CONTSGL                                 (_CSEN_CTRL_CM_CONTSGL << 4)               /**< Shifted mode CONTSGL for CSEN_CTRL */
#define CSEN_CTRL_CM_CONTSCAN                                (_CSEN_CTRL_CM_CONTSCAN << 4)              /**< Shifted mode CONTSCAN for CSEN_CTRL */
#define _CSEN_CTRL_SARCR_SHIFT                               8                                          /**< Shift value for CSEN_SARCR */
#define _CSEN_CTRL_SARCR_MASK                                0x300UL                                    /**< Bit mask for CSEN_SARCR */
#define _CSEN_CTRL_SARCR_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_SARCR_CLK10                               0x00000000UL                               /**< Mode CLK10 for CSEN_CTRL */
#define _CSEN_CTRL_SARCR_CLK12                               0x00000001UL                               /**< Mode CLK12 for CSEN_CTRL */
#define _CSEN_CTRL_SARCR_CLK14                               0x00000002UL                               /**< Mode CLK14 for CSEN_CTRL */
#define _CSEN_CTRL_SARCR_CLK16                               0x00000003UL                               /**< Mode CLK16 for CSEN_CTRL */
#define CSEN_CTRL_SARCR_DEFAULT                              (_CSEN_CTRL_SARCR_DEFAULT << 8)            /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_SARCR_CLK10                                (_CSEN_CTRL_SARCR_CLK10 << 8)              /**< Shifted mode CLK10 for CSEN_CTRL */
#define CSEN_CTRL_SARCR_CLK12                                (_CSEN_CTRL_SARCR_CLK12 << 8)              /**< Shifted mode CLK12 for CSEN_CTRL */
#define CSEN_CTRL_SARCR_CLK14                                (_CSEN_CTRL_SARCR_CLK14 << 8)              /**< Shifted mode CLK14 for CSEN_CTRL */
#define CSEN_CTRL_SARCR_CLK16                                (_CSEN_CTRL_SARCR_CLK16 << 8)              /**< Shifted mode CLK16 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_SHIFT                                 12                                         /**< Shift value for CSEN_ACU */
#define _CSEN_CTRL_ACU_MASK                                  0x7000UL                                   /**< Bit mask for CSEN_ACU */
#define _CSEN_CTRL_ACU_DEFAULT                               0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC1                                  0x00000000UL                               /**< Mode ACC1 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC2                                  0x00000001UL                               /**< Mode ACC2 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC4                                  0x00000002UL                               /**< Mode ACC4 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC8                                  0x00000003UL                               /**< Mode ACC8 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC16                                 0x00000004UL                               /**< Mode ACC16 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC32                                 0x00000005UL                               /**< Mode ACC32 for CSEN_CTRL */
#define _CSEN_CTRL_ACU_ACC64                                 0x00000006UL                               /**< Mode ACC64 for CSEN_CTRL */
#define CSEN_CTRL_ACU_DEFAULT                                (_CSEN_CTRL_ACU_DEFAULT << 12)             /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC1                                   (_CSEN_CTRL_ACU_ACC1 << 12)                /**< Shifted mode ACC1 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC2                                   (_CSEN_CTRL_ACU_ACC2 << 12)                /**< Shifted mode ACC2 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC4                                   (_CSEN_CTRL_ACU_ACC4 << 12)                /**< Shifted mode ACC4 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC8                                   (_CSEN_CTRL_ACU_ACC8 << 12)                /**< Shifted mode ACC8 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC16                                  (_CSEN_CTRL_ACU_ACC16 << 12)               /**< Shifted mode ACC16 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC32                                  (_CSEN_CTRL_ACU_ACC32 << 12)               /**< Shifted mode ACC32 for CSEN_CTRL */
#define CSEN_CTRL_ACU_ACC64                                  (_CSEN_CTRL_ACU_ACC64 << 12)               /**< Shifted mode ACC64 for CSEN_CTRL */
#define CSEN_CTRL_MCEN                                       (0x1UL << 15)                              /**< CSEN Multiple Channel Enable */
#define _CSEN_CTRL_MCEN_SHIFT                                15                                         /**< Shift value for CSEN_MCEN */
#define _CSEN_CTRL_MCEN_MASK                                 0x8000UL                                   /**< Bit mask for CSEN_MCEN */
#define _CSEN_CTRL_MCEN_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_MCEN_DISABLE                              0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_MCEN_ENABLE                               0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_MCEN_DEFAULT                               (_CSEN_CTRL_MCEN_DEFAULT << 15)            /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_MCEN_DISABLE                               (_CSEN_CTRL_MCEN_DISABLE << 15)            /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_MCEN_ENABLE                                (_CSEN_CTRL_MCEN_ENABLE << 15)             /**< Shifted mode ENABLE for CSEN_CTRL */
#define _CSEN_CTRL_STM_SHIFT                                 16                                         /**< Shift value for CSEN_STM */
#define _CSEN_CTRL_STM_MASK                                  0x30000UL                                  /**< Bit mask for CSEN_STM */
#define _CSEN_CTRL_STM_PRS                                   0x00000000UL                               /**< Mode PRS for CSEN_CTRL */
#define _CSEN_CTRL_STM_TIMER                                 0x00000001UL                               /**< Mode TIMER for CSEN_CTRL */
#define _CSEN_CTRL_STM_START                                 0x00000002UL                               /**< Mode START for CSEN_CTRL */
#define _CSEN_CTRL_STM_DEFAULT                               0x00000003UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_STM_DEFAULT                               0x00000003UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_STM_PRS                                    (_CSEN_CTRL_STM_PRS << 16)                 /**< Shifted mode PRS for CSEN_CTRL */
#define CSEN_CTRL_STM_TIMER                                  (_CSEN_CTRL_STM_TIMER << 16)               /**< Shifted mode TIMER for CSEN_CTRL */
#define CSEN_CTRL_STM_START                                  (_CSEN_CTRL_STM_START << 16)               /**< Shifted mode START for CSEN_CTRL */
#define CSEN_CTRL_STM_DEFAULT                                (_CSEN_CTRL_STM_DEFAULT << 16)             /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_STM_DEFAULT                                (_CSEN_CTRL_STM_DEFAULT << 16)             /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CMPEN                                      (0x1UL << 18)                              /**< CSEN Digital Comparator Enable */
#define _CSEN_CTRL_CMPEN_SHIFT                               18                                         /**< Shift value for CSEN_CMPEN */
#define _CSEN_CTRL_CMPEN_MASK                                0x40000UL                                  /**< Bit mask for CSEN_CMPEN */
#define _CSEN_CTRL_CMPEN_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CMPEN_DISABLE                             0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_CMPEN_ENABLE                              0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_CMPEN_DEFAULT                              (_CSEN_CTRL_CMPEN_DEFAULT << 18)           /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CMPEN_DISABLE                              (_CSEN_CTRL_CMPEN_DISABLE << 18)           /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_CMPEN_ENABLE                               (_CSEN_CTRL_CMPEN_ENABLE << 18)            /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_DRSF                                       (0x1UL << 19)                              /**< CSEN Disable Right-Shift */
#define _CSEN_CTRL_DRSF_SHIFT                                19                                         /**< Shift value for CSEN_DRSF */
#define _CSEN_CTRL_DRSF_MASK                                 0x80000UL                                  /**< Bit mask for CSEN_DRSF */
#define _CSEN_CTRL_DRSF_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_DRSF_DISABLE                              0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_DRSF_ENABLE                               0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_DRSF_DEFAULT                               (_CSEN_CTRL_DRSF_DEFAULT << 19)            /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_DRSF_DISABLE                               (_CSEN_CTRL_DRSF_DISABLE << 19)            /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_DRSF_ENABLE                                (_CSEN_CTRL_DRSF_ENABLE << 19)             /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_DMAEN                                      (0x1UL << 20)                              /**< CSEN DMA Enable Bit */
#define _CSEN_CTRL_DMAEN_SHIFT                               20                                         /**< Shift value for CSEN_DMAEN */
#define _CSEN_CTRL_DMAEN_MASK                                0x100000UL                                 /**< Bit mask for CSEN_DMAEN */
#define _CSEN_CTRL_DMAEN_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_DMAEN_DISABLE                             0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_DMAEN_ENABLE                              0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_DMAEN_DEFAULT                              (_CSEN_CTRL_DMAEN_DEFAULT << 20)           /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_DMAEN_DISABLE                              (_CSEN_CTRL_DMAEN_DISABLE << 20)           /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_DMAEN_ENABLE                               (_CSEN_CTRL_DMAEN_ENABLE << 20)            /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_CONVSEL                                    (0x1UL << 21)                              /**< CSEN Converter Select */
#define _CSEN_CTRL_CONVSEL_SHIFT                             21                                         /**< Shift value for CSEN_CONVSEL */
#define _CSEN_CTRL_CONVSEL_MASK                              0x200000UL                                 /**< Bit mask for CSEN_CONVSEL */
#define _CSEN_CTRL_CONVSEL_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CONVSEL_SAR                               0x00000000UL                               /**< Mode SAR for CSEN_CTRL */
#define _CSEN_CTRL_CONVSEL_DM                                0x00000001UL                               /**< Mode DM for CSEN_CTRL */
#define CSEN_CTRL_CONVSEL_DEFAULT                            (_CSEN_CTRL_CONVSEL_DEFAULT << 21)         /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CONVSEL_SAR                                (_CSEN_CTRL_CONVSEL_SAR << 21)             /**< Shifted mode SAR for CSEN_CTRL */
#define CSEN_CTRL_CONVSEL_DM                                 (_CSEN_CTRL_CONVSEL_DM << 21)              /**< Shifted mode DM for CSEN_CTRL */
#define CSEN_CTRL_CHOPEN                                     (0x1UL << 22)                              /**< CSEN Chop Enable */
#define _CSEN_CTRL_CHOPEN_SHIFT                              22                                         /**< Shift value for CSEN_CHOPEN */
#define _CSEN_CTRL_CHOPEN_MASK                               0x400000UL                                 /**< Bit mask for CSEN_CHOPEN */
#define _CSEN_CTRL_CHOPEN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CHOPEN_DISABLE                            0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_CHOPEN_ENABLE                             0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_CHOPEN_DEFAULT                             (_CSEN_CTRL_CHOPEN_DEFAULT << 22)          /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CHOPEN_DISABLE                             (_CSEN_CTRL_CHOPEN_DISABLE << 22)          /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_CHOPEN_ENABLE                              (_CSEN_CTRL_CHOPEN_ENABLE << 22)           /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_AUTOGND                                    (0x1UL << 23)                              /**< CSEN Automatic Ground Enable */
#define _CSEN_CTRL_AUTOGND_SHIFT                             23                                         /**< Shift value for CSEN_AUTOGND */
#define _CSEN_CTRL_AUTOGND_MASK                              0x800000UL                                 /**< Bit mask for CSEN_AUTOGND */
#define _CSEN_CTRL_AUTOGND_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_AUTOGND_DISABLE                           0x00000000UL                               /**< Mode DISABLE for CSEN_CTRL */
#define _CSEN_CTRL_AUTOGND_ENABLE                            0x00000001UL                               /**< Mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_AUTOGND_DEFAULT                            (_CSEN_CTRL_AUTOGND_DEFAULT << 23)         /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_AUTOGND_DISABLE                            (_CSEN_CTRL_AUTOGND_DISABLE << 23)         /**< Shifted mode DISABLE for CSEN_CTRL */
#define CSEN_CTRL_AUTOGND_ENABLE                             (_CSEN_CTRL_AUTOGND_ENABLE << 23)          /**< Shifted mode ENABLE for CSEN_CTRL */
#define CSEN_CTRL_MXUC                                       (0x1UL << 24)                              /**< CSEN Mux Disconnect */
#define _CSEN_CTRL_MXUC_SHIFT                                24                                         /**< Shift value for CSEN_MXUC */
#define _CSEN_CTRL_MXUC_MASK                                 0x1000000UL                                /**< Bit mask for CSEN_MXUC */
#define _CSEN_CTRL_MXUC_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_MXUC_CONN                                 0x00000000UL                               /**< Mode CONN for CSEN_CTRL */
#define _CSEN_CTRL_MXUC_UNC                                  0x00000001UL                               /**< Mode UNC for CSEN_CTRL */
#define CSEN_CTRL_MXUC_DEFAULT                               (_CSEN_CTRL_MXUC_DEFAULT << 24)            /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_MXUC_CONN                                  (_CSEN_CTRL_MXUC_CONN << 24)               /**< Shifted mode CONN for CSEN_CTRL */
#define CSEN_CTRL_MXUC_UNC                                   (_CSEN_CTRL_MXUC_UNC << 24)                /**< Shifted mode UNC for CSEN_CTRL */
#define CSEN_CTRL_EMACMPEN                                   (0x1UL << 25)                              /**< Greater and Less Than Comparison Using the Exponential Moving Average (EMA) is Enabled */
#define _CSEN_CTRL_EMACMPEN_SHIFT                            25                                         /**< Shift value for CSEN_EMACMPEN */
#define _CSEN_CTRL_EMACMPEN_MASK                             0x2000000UL                                /**< Bit mask for CSEN_EMACMPEN */
#define _CSEN_CTRL_EMACMPEN_DEFAULT                          0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_EMACMPEN_DEFAULT                           (_CSEN_CTRL_EMACMPEN_DEFAULT << 25)        /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_WARMUPMODE                                 (0x1UL << 26)                              /**< Select Warmup Mode for CSEN */
#define _CSEN_CTRL_WARMUPMODE_SHIFT                          26                                         /**< Shift value for CSEN_WARMUPMODE */
#define _CSEN_CTRL_WARMUPMODE_MASK                           0x4000000UL                                /**< Bit mask for CSEN_WARMUPMODE */
#define _CSEN_CTRL_WARMUPMODE_DEFAULT                        0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_WARMUPMODE_NORMAL                         0x00000000UL                               /**< Mode NORMAL for CSEN_CTRL */
#define _CSEN_CTRL_WARMUPMODE_KEEPCSENWARM                   0x00000001UL                               /**< Mode KEEPCSENWARM for CSEN_CTRL */
#define CSEN_CTRL_WARMUPMODE_DEFAULT                         (_CSEN_CTRL_WARMUPMODE_DEFAULT << 26)      /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_WARMUPMODE_NORMAL                          (_CSEN_CTRL_WARMUPMODE_NORMAL << 26)       /**< Shifted mode NORMAL for CSEN_CTRL */
#define CSEN_CTRL_WARMUPMODE_KEEPCSENWARM                    (_CSEN_CTRL_WARMUPMODE_KEEPCSENWARM << 26) /**< Shifted mode KEEPCSENWARM for CSEN_CTRL */
#define CSEN_CTRL_LOCALSENS                                  (0x1UL << 27)                              /**< Local Sensing Enable */
#define _CSEN_CTRL_LOCALSENS_SHIFT                           27                                         /**< Shift value for CSEN_LOCALSENS */
#define _CSEN_CTRL_LOCALSENS_MASK                            0x8000000UL                                /**< Bit mask for CSEN_LOCALSENS */
#define _CSEN_CTRL_LOCALSENS_DEFAULT                         0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_LOCALSENS_DEFAULT                          (_CSEN_CTRL_LOCALSENS_DEFAULT << 27)       /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CPACCURACY                                 (0x1UL << 28)                              /**< Charge Pump Accuracy */
#define _CSEN_CTRL_CPACCURACY_SHIFT                          28                                         /**< Shift value for CSEN_CPACCURACY */
#define _CSEN_CTRL_CPACCURACY_MASK                           0x10000000UL                               /**< Bit mask for CSEN_CPACCURACY */
#define _CSEN_CTRL_CPACCURACY_DEFAULT                        0x00000000UL                               /**< Mode DEFAULT for CSEN_CTRL */
#define _CSEN_CTRL_CPACCURACY_LO                             0x00000000UL                               /**< Mode LO for CSEN_CTRL */
#define _CSEN_CTRL_CPACCURACY_HI                             0x00000001UL                               /**< Mode HI for CSEN_CTRL */
#define CSEN_CTRL_CPACCURACY_DEFAULT                         (_CSEN_CTRL_CPACCURACY_DEFAULT << 28)      /**< Shifted mode DEFAULT for CSEN_CTRL */
#define CSEN_CTRL_CPACCURACY_LO                              (_CSEN_CTRL_CPACCURACY_LO << 28)           /**< Shifted mode LO for CSEN_CTRL */
#define CSEN_CTRL_CPACCURACY_HI                              (_CSEN_CTRL_CPACCURACY_HI << 28)           /**< Shifted mode HI for CSEN_CTRL */

/* Bit fields for CSEN TIMCTRL */
#define _CSEN_TIMCTRL_RESETVALUE                             0x00000000UL                            /**< Default value for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_MASK                                   0x0003FF07UL                            /**< Mask for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_SHIFT                          0                                       /**< Shift value for CSEN_PCPRESC */
#define _CSEN_TIMCTRL_PCPRESC_MASK                           0x7UL                                   /**< Bit mask for CSEN_PCPRESC */
#define _CSEN_TIMCTRL_PCPRESC_DEFAULT                        0x00000000UL                            /**< Mode DEFAULT for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV1                           0x00000000UL                            /**< Mode DIV1 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV2                           0x00000001UL                            /**< Mode DIV2 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV4                           0x00000002UL                            /**< Mode DIV4 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV8                           0x00000003UL                            /**< Mode DIV8 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV16                          0x00000004UL                            /**< Mode DIV16 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV32                          0x00000005UL                            /**< Mode DIV32 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV64                          0x00000006UL                            /**< Mode DIV64 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCPRESC_DIV128                         0x00000007UL                            /**< Mode DIV128 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DEFAULT                         (_CSEN_TIMCTRL_PCPRESC_DEFAULT << 0)    /**< Shifted mode DEFAULT for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV1                            (_CSEN_TIMCTRL_PCPRESC_DIV1 << 0)       /**< Shifted mode DIV1 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV2                            (_CSEN_TIMCTRL_PCPRESC_DIV2 << 0)       /**< Shifted mode DIV2 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV4                            (_CSEN_TIMCTRL_PCPRESC_DIV4 << 0)       /**< Shifted mode DIV4 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV8                            (_CSEN_TIMCTRL_PCPRESC_DIV8 << 0)       /**< Shifted mode DIV8 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV16                           (_CSEN_TIMCTRL_PCPRESC_DIV16 << 0)      /**< Shifted mode DIV16 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV32                           (_CSEN_TIMCTRL_PCPRESC_DIV32 << 0)      /**< Shifted mode DIV32 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV64                           (_CSEN_TIMCTRL_PCPRESC_DIV64 << 0)      /**< Shifted mode DIV64 for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCPRESC_DIV128                          (_CSEN_TIMCTRL_PCPRESC_DIV128 << 0)     /**< Shifted mode DIV128 for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_PCTOP_SHIFT                            8                                       /**< Shift value for CSEN_PCTOP */
#define _CSEN_TIMCTRL_PCTOP_MASK                             0xFF00UL                                /**< Bit mask for CSEN_PCTOP */
#define _CSEN_TIMCTRL_PCTOP_DEFAULT                          0x00000000UL                            /**< Mode DEFAULT for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_PCTOP_DEFAULT                           (_CSEN_TIMCTRL_PCTOP_DEFAULT << 8)      /**< Shifted mode DEFAULT for CSEN_TIMCTRL */
#define _CSEN_TIMCTRL_WARMUPCNT_SHIFT                        16                                      /**< Shift value for CSEN_WARMUPCNT */
#define _CSEN_TIMCTRL_WARMUPCNT_MASK                         0x30000UL                               /**< Bit mask for CSEN_WARMUPCNT */
#define _CSEN_TIMCTRL_WARMUPCNT_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for CSEN_TIMCTRL */
#define CSEN_TIMCTRL_WARMUPCNT_DEFAULT                       (_CSEN_TIMCTRL_WARMUPCNT_DEFAULT << 16) /**< Shifted mode DEFAULT for CSEN_TIMCTRL */

/* Bit fields for CSEN CMD */
#define _CSEN_CMD_RESETVALUE                                 0x00000000UL                   /**< Default value for CSEN_CMD */
#define _CSEN_CMD_MASK                                       0x00000001UL                   /**< Mask for CSEN_CMD */
#define CSEN_CMD_START                                       (0x1UL << 0)                   /**< Start Software-Triggered Conversions */
#define _CSEN_CMD_START_SHIFT                                0                              /**< Shift value for CSEN_START */
#define _CSEN_CMD_START_MASK                                 0x1UL                          /**< Bit mask for CSEN_START */
#define _CSEN_CMD_START_DEFAULT                              0x00000000UL                   /**< Mode DEFAULT for CSEN_CMD */
#define CSEN_CMD_START_DEFAULT                               (_CSEN_CMD_START_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_CMD */

/* Bit fields for CSEN STATUS */
#define _CSEN_STATUS_RESETVALUE                              0x00000000UL                         /**< Default value for CSEN_STATUS */
#define _CSEN_STATUS_MASK                                    0x00000001UL                         /**< Mask for CSEN_STATUS */
#define CSEN_STATUS_CSENBUSY                                 (0x1UL << 0)                         /**< Busy Flag */
#define _CSEN_STATUS_CSENBUSY_SHIFT                          0                                    /**< Shift value for CSEN_CSENBUSY */
#define _CSEN_STATUS_CSENBUSY_MASK                           0x1UL                                /**< Bit mask for CSEN_CSENBUSY */
#define _CSEN_STATUS_CSENBUSY_DEFAULT                        0x00000000UL                         /**< Mode DEFAULT for CSEN_STATUS */
#define _CSEN_STATUS_CSENBUSY_IDLE                           0x00000000UL                         /**< Mode IDLE for CSEN_STATUS */
#define _CSEN_STATUS_CSENBUSY_BUSY                           0x00000001UL                         /**< Mode BUSY for CSEN_STATUS */
#define CSEN_STATUS_CSENBUSY_DEFAULT                         (_CSEN_STATUS_CSENBUSY_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_STATUS */
#define CSEN_STATUS_CSENBUSY_IDLE                            (_CSEN_STATUS_CSENBUSY_IDLE << 0)    /**< Shifted mode IDLE for CSEN_STATUS */
#define CSEN_STATUS_CSENBUSY_BUSY                            (_CSEN_STATUS_CSENBUSY_BUSY << 0)    /**< Shifted mode BUSY for CSEN_STATUS */

/* Bit fields for CSEN PRSSEL */
#define _CSEN_PRSSEL_RESETVALUE                              0x00000000UL                       /**< Default value for CSEN_PRSSEL */
#define _CSEN_PRSSEL_MASK                                    0x0000000FUL                       /**< Mask for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_SHIFT                            0                                  /**< Shift value for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_MASK                             0xFUL                              /**< Bit mask for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_DEFAULT                          0x00000000UL                       /**< Mode DEFAULT for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH0                           0x00000000UL                       /**< Mode PRSCH0 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH1                           0x00000001UL                       /**< Mode PRSCH1 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH2                           0x00000002UL                       /**< Mode PRSCH2 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH3                           0x00000003UL                       /**< Mode PRSCH3 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH4                           0x00000004UL                       /**< Mode PRSCH4 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH5                           0x00000005UL                       /**< Mode PRSCH5 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH6                           0x00000006UL                       /**< Mode PRSCH6 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH7                           0x00000007UL                       /**< Mode PRSCH7 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH8                           0x00000008UL                       /**< Mode PRSCH8 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH9                           0x00000009UL                       /**< Mode PRSCH9 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH10                          0x0000000AUL                       /**< Mode PRSCH10 for CSEN_PRSSEL */
#define _CSEN_PRSSEL_PRSSEL_PRSCH11                          0x0000000BUL                       /**< Mode PRSCH11 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_DEFAULT                           (_CSEN_PRSSEL_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH0                            (_CSEN_PRSSEL_PRSSEL_PRSCH0 << 0)  /**< Shifted mode PRSCH0 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH1                            (_CSEN_PRSSEL_PRSSEL_PRSCH1 << 0)  /**< Shifted mode PRSCH1 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH2                            (_CSEN_PRSSEL_PRSSEL_PRSCH2 << 0)  /**< Shifted mode PRSCH2 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH3                            (_CSEN_PRSSEL_PRSSEL_PRSCH3 << 0)  /**< Shifted mode PRSCH3 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH4                            (_CSEN_PRSSEL_PRSSEL_PRSCH4 << 0)  /**< Shifted mode PRSCH4 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH5                            (_CSEN_PRSSEL_PRSSEL_PRSCH5 << 0)  /**< Shifted mode PRSCH5 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH6                            (_CSEN_PRSSEL_PRSSEL_PRSCH6 << 0)  /**< Shifted mode PRSCH6 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH7                            (_CSEN_PRSSEL_PRSSEL_PRSCH7 << 0)  /**< Shifted mode PRSCH7 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH8                            (_CSEN_PRSSEL_PRSSEL_PRSCH8 << 0)  /**< Shifted mode PRSCH8 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH9                            (_CSEN_PRSSEL_PRSSEL_PRSCH9 << 0)  /**< Shifted mode PRSCH9 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH10                           (_CSEN_PRSSEL_PRSSEL_PRSCH10 << 0) /**< Shifted mode PRSCH10 for CSEN_PRSSEL */
#define CSEN_PRSSEL_PRSSEL_PRSCH11                           (_CSEN_PRSSEL_PRSSEL_PRSCH11 << 0) /**< Shifted mode PRSCH11 for CSEN_PRSSEL */

/* Bit fields for CSEN DATA */
#define _CSEN_DATA_RESETVALUE                                0x00000000UL                   /**< Default value for CSEN_DATA */
#define _CSEN_DATA_MASK                                      0xFFFFFFFFUL                   /**< Mask for CSEN_DATA */
#define _CSEN_DATA_DATA_SHIFT                                0                              /**< Shift value for CSEN_DATA */
#define _CSEN_DATA_DATA_MASK                                 0xFFFFFFFFUL                   /**< Bit mask for CSEN_DATA */
#define _CSEN_DATA_DATA_DEFAULT                              0x00000000UL                   /**< Mode DEFAULT for CSEN_DATA */
#define CSEN_DATA_DATA_DEFAULT                               (_CSEN_DATA_DATA_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_DATA */

/* Bit fields for CSEN SCANMASK0 */
#define _CSEN_SCANMASK0_RESETVALUE                           0x00000000UL                               /**< Default value for CSEN_SCANMASK0 */
#define _CSEN_SCANMASK0_MASK                                 0xFFFFFFFFUL                               /**< Mask for CSEN_SCANMASK0 */
#define _CSEN_SCANMASK0_SCANINPUTEN_SHIFT                    0                                          /**< Shift value for CSEN_SCANINPUTEN */
#define _CSEN_SCANMASK0_SCANINPUTEN_MASK                     0xFFFFFFFFUL                               /**< Bit mask for CSEN_SCANINPUTEN */
#define _CSEN_SCANMASK0_SCANINPUTEN_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for CSEN_SCANMASK0 */
#define CSEN_SCANMASK0_SCANINPUTEN_DEFAULT                   (_CSEN_SCANMASK0_SCANINPUTEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_SCANMASK0 */

/* Bit fields for CSEN SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_RESETVALUE                       0x00000000UL                                              /**< Default value for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_MASK                             0x0F0F0F0FUL                                              /**< Mask for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_SHIFT               0                                                         /**< Shift value for CSEN_INPUT0TO7SEL */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_MASK                0xFUL                                                     /**< Bit mask for CSEN_INPUT0TO7SEL */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_DEFAULT             0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH0TO7        0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH8TO15       0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH16TO23      0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH24TO31      0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH0TO7        0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH8TO15       0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH16TO23      0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH24TO31      0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_DEFAULT              (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_DEFAULT << 0)           /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH0TO7         (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH0TO7 << 0)      /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH8TO15        (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH8TO15 << 0)     /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH16TO23       (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH16TO23 << 0)    /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH24TO31       (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH24TO31 << 0)    /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH0TO7         (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH0TO7 << 0)      /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH8TO15        (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH8TO15 << 0)     /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH16TO23       (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH16TO23 << 0)    /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH24TO31       (_CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH24TO31 << 0)    /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_SHIFT              8                                                         /**< Shift value for CSEN_INPUT8TO15SEL */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_MASK               0xF00UL                                                   /**< Bit mask for CSEN_INPUT8TO15SEL */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_DEFAULT            0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH0TO7       0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH8TO15      0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH16TO23     0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH24TO31     0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH0TO7       0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH8TO15      0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH16TO23     0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH24TO31     0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_DEFAULT             (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_DEFAULT << 8)          /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH0TO7        (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH0TO7 << 8)     /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH8TO15       (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH8TO15 << 8)    /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH16TO23      (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH16TO23 << 8)   /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH24TO31      (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT1CH24TO31 << 8)   /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH0TO7        (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH0TO7 << 8)     /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH8TO15       (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH8TO15 << 8)    /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH16TO23      (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH16TO23 << 8)   /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH24TO31      (_CSEN_SCANINPUTSEL0_INPUT8TO15SEL_APORT3CH24TO31 << 8)   /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_SHIFT             16                                                        /**< Shift value for CSEN_INPUT16TO23SEL */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_MASK              0xF0000UL                                                 /**< Bit mask for CSEN_INPUT16TO23SEL */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_DEFAULT            (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_DEFAULT << 16)        /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH0TO7 << 16)   /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH8TO15 << 16)  /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH16TO23 << 16) /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT1CH24TO31 << 16) /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH0TO7 << 16)   /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH8TO15 << 16)  /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH16TO23 << 16) /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL0_INPUT16TO23SEL_APORT3CH24TO31 << 16) /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_SHIFT             24                                                        /**< Shift value for CSEN_INPUT24TO31SEL */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_MASK              0xF000000UL                                               /**< Bit mask for CSEN_INPUT24TO31SEL */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define _CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_DEFAULT            (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_DEFAULT << 24)        /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH0TO7 << 24)   /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH8TO15 << 24)  /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH16TO23 << 24) /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT1CH24TO31 << 24) /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH0TO7 << 24)   /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH8TO15 << 24)  /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH16TO23 << 24) /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL0 */
#define CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL0_INPUT24TO31SEL_APORT3CH24TO31 << 24) /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL0 */

/* Bit fields for CSEN SCANMASK1 */
#define _CSEN_SCANMASK1_RESETVALUE                           0x00000000UL                               /**< Default value for CSEN_SCANMASK1 */
#define _CSEN_SCANMASK1_MASK                                 0xFFFFFFFFUL                               /**< Mask for CSEN_SCANMASK1 */
#define _CSEN_SCANMASK1_SCANINPUTEN_SHIFT                    0                                          /**< Shift value for CSEN_SCANINPUTEN */
#define _CSEN_SCANMASK1_SCANINPUTEN_MASK                     0xFFFFFFFFUL                               /**< Bit mask for CSEN_SCANINPUTEN */
#define _CSEN_SCANMASK1_SCANINPUTEN_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for CSEN_SCANMASK1 */
#define CSEN_SCANMASK1_SCANINPUTEN_DEFAULT                   (_CSEN_SCANMASK1_SCANINPUTEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_SCANMASK1 */

/* Bit fields for CSEN SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_RESETVALUE                       0x00000000UL                                              /**< Default value for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_MASK                             0x0F0F0F0FUL                                              /**< Mask for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_SHIFT             0                                                         /**< Shift value for CSEN_INPUT32TO39SEL */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_MASK              0xFUL                                                     /**< Bit mask for CSEN_INPUT32TO39SEL */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_DEFAULT            (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_DEFAULT << 0)         /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH0TO7 << 0)    /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH8TO15 << 0)   /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH16TO23 << 0)  /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT1CH24TO31 << 0)  /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH0TO7 << 0)    /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH8TO15 << 0)   /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH16TO23 << 0)  /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT32TO39SEL_APORT3CH24TO31 << 0)  /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_SHIFT             8                                                         /**< Shift value for CSEN_INPUT40TO47SEL */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_MASK              0xF00UL                                                   /**< Bit mask for CSEN_INPUT40TO47SEL */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_DEFAULT            (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_DEFAULT << 8)         /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH0TO7 << 8)    /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH8TO15 << 8)   /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH16TO23 << 8)  /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT1CH24TO31 << 8)  /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH0TO7 << 8)    /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH8TO15 << 8)   /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH16TO23 << 8)  /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT40TO47SEL_APORT3CH24TO31 << 8)  /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_SHIFT             16                                                        /**< Shift value for CSEN_INPUT48TO55SEL */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_MASK              0xF0000UL                                                 /**< Bit mask for CSEN_INPUT48TO55SEL */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_DEFAULT            (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_DEFAULT << 16)        /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH0TO7 << 16)   /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH8TO15 << 16)  /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH16TO23 << 16) /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT1CH24TO31 << 16) /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH0TO7 << 16)   /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH8TO15 << 16)  /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH16TO23 << 16) /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT48TO55SEL_APORT3CH24TO31 << 16) /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_SHIFT             24                                                        /**< Shift value for CSEN_INPUT56TO63SEL */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_MASK              0xF000000UL                                               /**< Bit mask for CSEN_INPUT56TO63SEL */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_DEFAULT           0x00000000UL                                              /**< Mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH0TO7      0x00000004UL                                              /**< Mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH8TO15     0x00000005UL                                              /**< Mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH16TO23    0x00000006UL                                              /**< Mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH24TO31    0x00000007UL                                              /**< Mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH0TO7      0x0000000CUL                                              /**< Mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH8TO15     0x0000000DUL                                              /**< Mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH16TO23    0x0000000EUL                                              /**< Mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define _CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH24TO31    0x0000000FUL                                              /**< Mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_DEFAULT            (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_DEFAULT << 24)        /**< Shifted mode DEFAULT for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH0TO7 << 24)   /**< Shifted mode APORT1CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH8TO15 << 24)  /**< Shifted mode APORT1CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH16TO23 << 24) /**< Shifted mode APORT1CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT1CH24TO31 << 24) /**< Shifted mode APORT1CH24TO31 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH0TO7       (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH0TO7 << 24)   /**< Shifted mode APORT3CH0TO7 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH8TO15      (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH8TO15 << 24)  /**< Shifted mode APORT3CH8TO15 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH16TO23     (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH16TO23 << 24) /**< Shifted mode APORT3CH16TO23 for CSEN_SCANINPUTSEL1 */
#define CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH24TO31     (_CSEN_SCANINPUTSEL1_INPUT56TO63SEL_APORT3CH24TO31 << 24) /**< Shifted mode APORT3CH24TO31 for CSEN_SCANINPUTSEL1 */

/* Bit fields for CSEN APORTREQ */
#define _CSEN_APORTREQ_RESETVALUE                            0x00000000UL                             /**< Default value for CSEN_APORTREQ */
#define _CSEN_APORTREQ_MASK                                  0x000003FCUL                             /**< Mask for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT1XREQ                             (0x1UL << 2)                             /**< 1 If the Bus Connected to APORT2X is Requested */
#define _CSEN_APORTREQ_APORT1XREQ_SHIFT                      2                                        /**< Shift value for CSEN_APORT1XREQ */
#define _CSEN_APORTREQ_APORT1XREQ_MASK                       0x4UL                                    /**< Bit mask for CSEN_APORT1XREQ */
#define _CSEN_APORTREQ_APORT1XREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT1XREQ_DEFAULT                     (_CSEN_APORTREQ_APORT1XREQ_DEFAULT << 2) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT1YREQ                             (0x1UL << 3)                             /**< 1 If the Bus Connected to APORT1X is Requested */
#define _CSEN_APORTREQ_APORT1YREQ_SHIFT                      3                                        /**< Shift value for CSEN_APORT1YREQ */
#define _CSEN_APORTREQ_APORT1YREQ_MASK                       0x8UL                                    /**< Bit mask for CSEN_APORT1YREQ */
#define _CSEN_APORTREQ_APORT1YREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT1YREQ_DEFAULT                     (_CSEN_APORTREQ_APORT1YREQ_DEFAULT << 3) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT2XREQ                             (0x1UL << 4)                             /**< 1 If the Bus Connected to APORT2X is Requested */
#define _CSEN_APORTREQ_APORT2XREQ_SHIFT                      4                                        /**< Shift value for CSEN_APORT2XREQ */
#define _CSEN_APORTREQ_APORT2XREQ_MASK                       0x10UL                                   /**< Bit mask for CSEN_APORT2XREQ */
#define _CSEN_APORTREQ_APORT2XREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT2XREQ_DEFAULT                     (_CSEN_APORTREQ_APORT2XREQ_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT2YREQ                             (0x1UL << 5)                             /**< 1 If the Bus Connected to APORT2Y is Requested */
#define _CSEN_APORTREQ_APORT2YREQ_SHIFT                      5                                        /**< Shift value for CSEN_APORT2YREQ */
#define _CSEN_APORTREQ_APORT2YREQ_MASK                       0x20UL                                   /**< Bit mask for CSEN_APORT2YREQ */
#define _CSEN_APORTREQ_APORT2YREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT2YREQ_DEFAULT                     (_CSEN_APORTREQ_APORT2YREQ_DEFAULT << 5) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT3XREQ                             (0x1UL << 6)                             /**< 1 If the Bus Connected to APORT3X is Requested */
#define _CSEN_APORTREQ_APORT3XREQ_SHIFT                      6                                        /**< Shift value for CSEN_APORT3XREQ */
#define _CSEN_APORTREQ_APORT3XREQ_MASK                       0x40UL                                   /**< Bit mask for CSEN_APORT3XREQ */
#define _CSEN_APORTREQ_APORT3XREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT3XREQ_DEFAULT                     (_CSEN_APORTREQ_APORT3XREQ_DEFAULT << 6) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT3YREQ                             (0x1UL << 7)                             /**< 1 If the Bus Connected to APORT3Y is Requested */
#define _CSEN_APORTREQ_APORT3YREQ_SHIFT                      7                                        /**< Shift value for CSEN_APORT3YREQ */
#define _CSEN_APORTREQ_APORT3YREQ_MASK                       0x80UL                                   /**< Bit mask for CSEN_APORT3YREQ */
#define _CSEN_APORTREQ_APORT3YREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT3YREQ_DEFAULT                     (_CSEN_APORTREQ_APORT3YREQ_DEFAULT << 7) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT4XREQ                             (0x1UL << 8)                             /**< 1 If the Bus Connected to APORT4X is Requested */
#define _CSEN_APORTREQ_APORT4XREQ_SHIFT                      8                                        /**< Shift value for CSEN_APORT4XREQ */
#define _CSEN_APORTREQ_APORT4XREQ_MASK                       0x100UL                                  /**< Bit mask for CSEN_APORT4XREQ */
#define _CSEN_APORTREQ_APORT4XREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT4XREQ_DEFAULT                     (_CSEN_APORTREQ_APORT4XREQ_DEFAULT << 8) /**< Shifted mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT4YREQ                             (0x1UL << 9)                             /**< 1 If the Bus Connected to APORT4Y is Requested */
#define _CSEN_APORTREQ_APORT4YREQ_SHIFT                      9                                        /**< Shift value for CSEN_APORT4YREQ */
#define _CSEN_APORTREQ_APORT4YREQ_MASK                       0x200UL                                  /**< Bit mask for CSEN_APORT4YREQ */
#define _CSEN_APORTREQ_APORT4YREQ_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CSEN_APORTREQ */
#define CSEN_APORTREQ_APORT4YREQ_DEFAULT                     (_CSEN_APORTREQ_APORT4YREQ_DEFAULT << 9) /**< Shifted mode DEFAULT for CSEN_APORTREQ */

/* Bit fields for CSEN APORTCONFLICT */
#define _CSEN_APORTCONFLICT_RESETVALUE                       0x00000000UL                                       /**< Default value for CSEN_APORTCONFLICT */
#define _CSEN_APORTCONFLICT_MASK                             0x000003FCUL                                       /**< Mask for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT1XCONFLICT                   (0x1UL << 2)                                       /**< 1 If the Bus Connected to APORT1X is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT1XCONFLICT_SHIFT            2                                                  /**< Shift value for CSEN_APORT1XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT1XCONFLICT_MASK             0x4UL                                              /**< Bit mask for CSEN_APORT1XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT1XCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT1XCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT1XCONFLICT_DEFAULT << 2) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT1YCONFLICT                   (0x1UL << 3)                                       /**< 1 If the Bus Connected to APORT1Y is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT1YCONFLICT_SHIFT            3                                                  /**< Shift value for CSEN_APORT1YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT1YCONFLICT_MASK             0x8UL                                              /**< Bit mask for CSEN_APORT1YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT1YCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT1YCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT1YCONFLICT_DEFAULT << 3) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT2XCONFLICT                   (0x1UL << 4)                                       /**< 1 If the Bus Connected to APORT2X is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT2XCONFLICT_SHIFT            4                                                  /**< Shift value for CSEN_APORT2XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT2XCONFLICT_MASK             0x10UL                                             /**< Bit mask for CSEN_APORT2XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT2XCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT2XCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT2XCONFLICT_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT2YCONFLICT                   (0x1UL << 5)                                       /**< 1 If the Bus Connected to APORT2Y is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT2YCONFLICT_SHIFT            5                                                  /**< Shift value for CSEN_APORT2YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT2YCONFLICT_MASK             0x20UL                                             /**< Bit mask for CSEN_APORT2YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT2YCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT2YCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT2YCONFLICT_DEFAULT << 5) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT3XCONFLICT                   (0x1UL << 6)                                       /**< 1 If the Bus Connected to APORT3X is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT3XCONFLICT_SHIFT            6                                                  /**< Shift value for CSEN_APORT3XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT3XCONFLICT_MASK             0x40UL                                             /**< Bit mask for CSEN_APORT3XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT3XCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT3XCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT3XCONFLICT_DEFAULT << 6) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT3YCONFLICT                   (0x1UL << 7)                                       /**< 1 If the Bus Connected to APORT3Y is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT3YCONFLICT_SHIFT            7                                                  /**< Shift value for CSEN_APORT3YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT3YCONFLICT_MASK             0x80UL                                             /**< Bit mask for CSEN_APORT3YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT3YCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT3YCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT3YCONFLICT_DEFAULT << 7) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT4XCONFLICT                   (0x1UL << 8)                                       /**< 1 If the Bus Connected to APORT4X is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT4XCONFLICT_SHIFT            8                                                  /**< Shift value for CSEN_APORT4XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT4XCONFLICT_MASK             0x100UL                                            /**< Bit mask for CSEN_APORT4XCONFLICT */
#define _CSEN_APORTCONFLICT_APORT4XCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT4XCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT4XCONFLICT_DEFAULT << 8) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT4YCONFLICT                   (0x1UL << 9)                                       /**< 1 If the Bus Connected to APORT4Y is in Conflict With Another Peripheral */
#define _CSEN_APORTCONFLICT_APORT4YCONFLICT_SHIFT            9                                                  /**< Shift value for CSEN_APORT4YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT4YCONFLICT_MASK             0x200UL                                            /**< Bit mask for CSEN_APORT4YCONFLICT */
#define _CSEN_APORTCONFLICT_APORT4YCONFLICT_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for CSEN_APORTCONFLICT */
#define CSEN_APORTCONFLICT_APORT4YCONFLICT_DEFAULT           (_CSEN_APORTCONFLICT_APORT4YCONFLICT_DEFAULT << 9) /**< Shifted mode DEFAULT for CSEN_APORTCONFLICT */

/* Bit fields for CSEN CMPTHR */
#define _CSEN_CMPTHR_RESETVALUE                              0x00000000UL                       /**< Default value for CSEN_CMPTHR */
#define _CSEN_CMPTHR_MASK                                    0x0000FFFFUL                       /**< Mask for CSEN_CMPTHR */
#define _CSEN_CMPTHR_CMPTHR_SHIFT                            0                                  /**< Shift value for CSEN_CMPTHR */
#define _CSEN_CMPTHR_CMPTHR_MASK                             0xFFFFUL                           /**< Bit mask for CSEN_CMPTHR */
#define _CSEN_CMPTHR_CMPTHR_DEFAULT                          0x00000000UL                       /**< Mode DEFAULT for CSEN_CMPTHR */
#define CSEN_CMPTHR_CMPTHR_DEFAULT                           (_CSEN_CMPTHR_CMPTHR_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_CMPTHR */

/* Bit fields for CSEN EMA */
#define _CSEN_EMA_RESETVALUE                                 0x00000000UL                 /**< Default value for CSEN_EMA */
#define _CSEN_EMA_MASK                                       0x003FFFFFUL                 /**< Mask for CSEN_EMA */
#define _CSEN_EMA_EMA_SHIFT                                  0                            /**< Shift value for CSEN_EMA */
#define _CSEN_EMA_EMA_MASK                                   0x3FFFFFUL                   /**< Bit mask for CSEN_EMA */
#define _CSEN_EMA_EMA_DEFAULT                                0x00000000UL                 /**< Mode DEFAULT for CSEN_EMA */
#define CSEN_EMA_EMA_DEFAULT                                 (_CSEN_EMA_EMA_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_EMA */

/* Bit fields for CSEN EMACTRL */
#define _CSEN_EMACTRL_RESETVALUE                             0x00000000UL                           /**< Default value for CSEN_EMACTRL */
#define _CSEN_EMACTRL_MASK                                   0x00000007UL                           /**< Mask for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_SHIFT                        0                                      /**< Shift value for CSEN_EMASAMPLE */
#define _CSEN_EMACTRL_EMASAMPLE_MASK                         0x7UL                                  /**< Bit mask for CSEN_EMASAMPLE */
#define _CSEN_EMACTRL_EMASAMPLE_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W1                           0x00000000UL                           /**< Mode W1 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W2                           0x00000001UL                           /**< Mode W2 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W4                           0x00000002UL                           /**< Mode W4 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W8                           0x00000003UL                           /**< Mode W8 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W16                          0x00000004UL                           /**< Mode W16 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W32                          0x00000005UL                           /**< Mode W32 for CSEN_EMACTRL */
#define _CSEN_EMACTRL_EMASAMPLE_W64                          0x00000006UL                           /**< Mode W64 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_DEFAULT                       (_CSEN_EMACTRL_EMASAMPLE_DEFAULT << 0) /**< Shifted mode DEFAULT for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W1                            (_CSEN_EMACTRL_EMASAMPLE_W1 << 0)      /**< Shifted mode W1 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W2                            (_CSEN_EMACTRL_EMASAMPLE_W2 << 0)      /**< Shifted mode W2 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W4                            (_CSEN_EMACTRL_EMASAMPLE_W4 << 0)      /**< Shifted mode W4 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W8                            (_CSEN_EMACTRL_EMASAMPLE_W8 << 0)      /**< Shifted mode W8 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W16                           (_CSEN_EMACTRL_EMASAMPLE_W16 << 0)     /**< Shifted mode W16 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W32                           (_CSEN_EMACTRL_EMASAMPLE_W32 << 0)     /**< Shifted mode W32 for CSEN_EMACTRL */
#define CSEN_EMACTRL_EMASAMPLE_W64                           (_CSEN_EMACTRL_EMASAMPLE_W64 << 0)     /**< Shifted mode W64 for CSEN_EMACTRL */

/* Bit fields for CSEN SINGLECTRL */
#define _CSEN_SINGLECTRL_RESETVALUE                          0x00000000UL                                  /**< Default value for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_MASK                                0x000007F0UL                                  /**< Mask for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_SHIFT                     4                                             /**< Shift value for CSEN_SINGLESEL */
#define _CSEN_SINGLECTRL_SINGLESEL_MASK                      0x7F0UL                                       /**< Bit mask for CSEN_SINGLESEL */
#define _CSEN_SINGLECTRL_SINGLESEL_DEFAULT                   0x00000000UL                                  /**< Mode DEFAULT for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH0                0x00000020UL                                  /**< Mode APORT1XCH0 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH1                0x00000021UL                                  /**< Mode APORT1YCH1 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH2                0x00000022UL                                  /**< Mode APORT1XCH2 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH3                0x00000023UL                                  /**< Mode APORT1YCH3 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH4                0x00000024UL                                  /**< Mode APORT1XCH4 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH5                0x00000025UL                                  /**< Mode APORT1YCH5 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH6                0x00000026UL                                  /**< Mode APORT1XCH6 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH7                0x00000027UL                                  /**< Mode APORT1YCH7 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH8                0x00000028UL                                  /**< Mode APORT1XCH8 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH9                0x00000029UL                                  /**< Mode APORT1YCH9 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH10               0x0000002AUL                                  /**< Mode APORT1XCH10 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH11               0x0000002BUL                                  /**< Mode APORT1YCH11 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH12               0x0000002CUL                                  /**< Mode APORT1XCH12 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH13               0x0000002DUL                                  /**< Mode APORT1YCH13 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH14               0x0000002EUL                                  /**< Mode APORT1XCH14 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH15               0x0000002FUL                                  /**< Mode APORT1YCH15 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH16               0x00000030UL                                  /**< Mode APORT1XCH16 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH17               0x00000031UL                                  /**< Mode APORT1YCH17 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH18               0x00000032UL                                  /**< Mode APORT1XCH18 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH19               0x00000033UL                                  /**< Mode APORT1YCH19 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH20               0x00000034UL                                  /**< Mode APORT1XCH20 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH21               0x00000035UL                                  /**< Mode APORT1YCH21 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH22               0x00000036UL                                  /**< Mode APORT1XCH22 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH23               0x00000037UL                                  /**< Mode APORT1YCH23 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH24               0x00000038UL                                  /**< Mode APORT1XCH24 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH25               0x00000039UL                                  /**< Mode APORT1YCH25 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH26               0x0000003AUL                                  /**< Mode APORT1XCH26 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH27               0x0000003BUL                                  /**< Mode APORT1YCH27 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH28               0x0000003CUL                                  /**< Mode APORT1XCH28 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH29               0x0000003DUL                                  /**< Mode APORT1YCH29 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH30               0x0000003EUL                                  /**< Mode APORT1XCH30 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH31               0x0000003FUL                                  /**< Mode APORT1YCH31 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH0                0x00000060UL                                  /**< Mode APORT3XCH0 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH1                0x00000061UL                                  /**< Mode APORT3YCH1 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH2                0x00000062UL                                  /**< Mode APORT3XCH2 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH3                0x00000063UL                                  /**< Mode APORT3YCH3 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH4                0x00000064UL                                  /**< Mode APORT3XCH4 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH5                0x00000065UL                                  /**< Mode APORT3YCH5 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH6                0x00000066UL                                  /**< Mode APORT3XCH6 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH7                0x00000067UL                                  /**< Mode APORT3YCH7 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH8                0x00000068UL                                  /**< Mode APORT3XCH8 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH9                0x00000069UL                                  /**< Mode APORT3YCH9 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH10               0x0000006AUL                                  /**< Mode APORT3XCH10 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH11               0x0000006BUL                                  /**< Mode APORT3YCH11 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH12               0x0000006CUL                                  /**< Mode APORT3XCH12 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH13               0x0000006DUL                                  /**< Mode APORT3YCH13 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH14               0x0000006EUL                                  /**< Mode APORT3XCH14 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH15               0x0000006FUL                                  /**< Mode APORT3YCH15 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH16               0x00000070UL                                  /**< Mode APORT3XCH16 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH17               0x00000071UL                                  /**< Mode APORT3YCH17 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH18               0x00000072UL                                  /**< Mode APORT3XCH18 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH19               0x00000073UL                                  /**< Mode APORT3YCH19 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH20               0x00000074UL                                  /**< Mode APORT3XCH20 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH21               0x00000075UL                                  /**< Mode APORT3YCH21 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH22               0x00000076UL                                  /**< Mode APORT3XCH22 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH23               0x00000077UL                                  /**< Mode APORT3YCH23 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH24               0x00000078UL                                  /**< Mode APORT3XCH24 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH25               0x00000079UL                                  /**< Mode APORT3YCH25 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH26               0x0000007AUL                                  /**< Mode APORT3XCH26 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH27               0x0000007BUL                                  /**< Mode APORT3YCH27 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH28               0x0000007CUL                                  /**< Mode APORT3XCH28 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH29               0x0000007DUL                                  /**< Mode APORT3YCH29 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH30               0x0000007EUL                                  /**< Mode APORT3XCH30 for CSEN_SINGLECTRL */
#define _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH31               0x0000007FUL                                  /**< Mode APORT3YCH31 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_DEFAULT                    (_CSEN_SINGLECTRL_SINGLESEL_DEFAULT << 4)     /**< Shifted mode DEFAULT for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH0                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH0 << 4)  /**< Shifted mode APORT1XCH0 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH1                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH1 << 4)  /**< Shifted mode APORT1YCH1 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH2                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH2 << 4)  /**< Shifted mode APORT1XCH2 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH3                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH3 << 4)  /**< Shifted mode APORT1YCH3 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH4                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH4 << 4)  /**< Shifted mode APORT1XCH4 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH5                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH5 << 4)  /**< Shifted mode APORT1YCH5 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH6                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH6 << 4)  /**< Shifted mode APORT1XCH6 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH7                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH7 << 4)  /**< Shifted mode APORT1YCH7 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH8                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH8 << 4)  /**< Shifted mode APORT1XCH8 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH9                 (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH9 << 4)  /**< Shifted mode APORT1YCH9 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH10                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH10 << 4) /**< Shifted mode APORT1XCH10 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH11                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH11 << 4) /**< Shifted mode APORT1YCH11 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH12                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH12 << 4) /**< Shifted mode APORT1XCH12 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH13                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH13 << 4) /**< Shifted mode APORT1YCH13 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH14                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH14 << 4) /**< Shifted mode APORT1XCH14 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH15                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH15 << 4) /**< Shifted mode APORT1YCH15 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH16                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH16 << 4) /**< Shifted mode APORT1XCH16 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH17                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH17 << 4) /**< Shifted mode APORT1YCH17 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH18                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH18 << 4) /**< Shifted mode APORT1XCH18 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH19                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH19 << 4) /**< Shifted mode APORT1YCH19 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH20                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH20 << 4) /**< Shifted mode APORT1XCH20 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH21                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH21 << 4) /**< Shifted mode APORT1YCH21 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH22                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH22 << 4) /**< Shifted mode APORT1XCH22 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH23                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH23 << 4) /**< Shifted mode APORT1YCH23 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH24                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH24 << 4) /**< Shifted mode APORT1XCH24 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH25                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH25 << 4) /**< Shifted mode APORT1YCH25 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH26                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH26 << 4) /**< Shifted mode APORT1XCH26 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH27                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH27 << 4) /**< Shifted mode APORT1YCH27 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH28                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH28 << 4) /**< Shifted mode APORT1XCH28 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH29                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH29 << 4) /**< Shifted mode APORT1YCH29 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1XCH30                (_CSEN_SINGLECTRL_SINGLESEL_APORT1XCH30 << 4) /**< Shifted mode APORT1XCH30 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT1YCH31                (_CSEN_SINGLECTRL_SINGLESEL_APORT1YCH31 << 4) /**< Shifted mode APORT1YCH31 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH0                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH0 << 4)  /**< Shifted mode APORT3XCH0 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH1                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH1 << 4)  /**< Shifted mode APORT3YCH1 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH2                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH2 << 4)  /**< Shifted mode APORT3XCH2 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH3                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH3 << 4)  /**< Shifted mode APORT3YCH3 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH4                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH4 << 4)  /**< Shifted mode APORT3XCH4 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH5                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH5 << 4)  /**< Shifted mode APORT3YCH5 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH6                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH6 << 4)  /**< Shifted mode APORT3XCH6 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH7                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH7 << 4)  /**< Shifted mode APORT3YCH7 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH8                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH8 << 4)  /**< Shifted mode APORT3XCH8 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH9                 (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH9 << 4)  /**< Shifted mode APORT3YCH9 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH10                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH10 << 4) /**< Shifted mode APORT3XCH10 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH11                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH11 << 4) /**< Shifted mode APORT3YCH11 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH12                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH12 << 4) /**< Shifted mode APORT3XCH12 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH13                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH13 << 4) /**< Shifted mode APORT3YCH13 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH14                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH14 << 4) /**< Shifted mode APORT3XCH14 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH15                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH15 << 4) /**< Shifted mode APORT3YCH15 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH16                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH16 << 4) /**< Shifted mode APORT3XCH16 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH17                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH17 << 4) /**< Shifted mode APORT3YCH17 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH18                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH18 << 4) /**< Shifted mode APORT3XCH18 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH19                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH19 << 4) /**< Shifted mode APORT3YCH19 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH20                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH20 << 4) /**< Shifted mode APORT3XCH20 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH21                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH21 << 4) /**< Shifted mode APORT3YCH21 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH22                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH22 << 4) /**< Shifted mode APORT3XCH22 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH23                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH23 << 4) /**< Shifted mode APORT3YCH23 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH24                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH24 << 4) /**< Shifted mode APORT3XCH24 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH25                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH25 << 4) /**< Shifted mode APORT3YCH25 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH26                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH26 << 4) /**< Shifted mode APORT3XCH26 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH27                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH27 << 4) /**< Shifted mode APORT3YCH27 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH28                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH28 << 4) /**< Shifted mode APORT3XCH28 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH29                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH29 << 4) /**< Shifted mode APORT3YCH29 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3XCH30                (_CSEN_SINGLECTRL_SINGLESEL_APORT3XCH30 << 4) /**< Shifted mode APORT3XCH30 for CSEN_SINGLECTRL */
#define CSEN_SINGLECTRL_SINGLESEL_APORT3YCH31                (_CSEN_SINGLECTRL_SINGLESEL_APORT3YCH31 << 4) /**< Shifted mode APORT3YCH31 for CSEN_SINGLECTRL */

/* Bit fields for CSEN DMBASELINE */
#define _CSEN_DMBASELINE_RESETVALUE                          0x00000000UL                                /**< Default value for CSEN_DMBASELINE */
#define _CSEN_DMBASELINE_MASK                                0xFFFFFFFFUL                                /**< Mask for CSEN_DMBASELINE */
#define _CSEN_DMBASELINE_BASELINEUP_SHIFT                    0                                           /**< Shift value for CSEN_BASELINEUP */
#define _CSEN_DMBASELINE_BASELINEUP_MASK                     0xFFFFUL                                    /**< Bit mask for CSEN_BASELINEUP */
#define _CSEN_DMBASELINE_BASELINEUP_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for CSEN_DMBASELINE */
#define CSEN_DMBASELINE_BASELINEUP_DEFAULT                   (_CSEN_DMBASELINE_BASELINEUP_DEFAULT << 0)  /**< Shifted mode DEFAULT for CSEN_DMBASELINE */
#define _CSEN_DMBASELINE_BASELINEDN_SHIFT                    16                                          /**< Shift value for CSEN_BASELINEDN */
#define _CSEN_DMBASELINE_BASELINEDN_MASK                     0xFFFF0000UL                                /**< Bit mask for CSEN_BASELINEDN */
#define _CSEN_DMBASELINE_BASELINEDN_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for CSEN_DMBASELINE */
#define CSEN_DMBASELINE_BASELINEDN_DEFAULT                   (_CSEN_DMBASELINE_BASELINEDN_DEFAULT << 16) /**< Shifted mode DEFAULT for CSEN_DMBASELINE */

/* Bit fields for CSEN DMCFG */
#define _CSEN_DMCFG_RESETVALUE                               0x00000000UL                        /**< Default value for CSEN_DMCFG */
#define _CSEN_DMCFG_MASK                                     0x103F0FFFUL                        /**< Mask for CSEN_DMCFG */
#define _CSEN_DMCFG_DMG_SHIFT                                0                                   /**< Shift value for CSEN_DMG */
#define _CSEN_DMCFG_DMG_MASK                                 0xFFUL                              /**< Bit mask for CSEN_DMG */
#define _CSEN_DMCFG_DMG_DEFAULT                              0x00000000UL                        /**< Mode DEFAULT for CSEN_DMCFG */
#define CSEN_DMCFG_DMG_DEFAULT                               (_CSEN_DMCFG_DMG_DEFAULT << 0)      /**< Shifted mode DEFAULT for CSEN_DMCFG */
#define _CSEN_DMCFG_DMR_SHIFT                                8                                   /**< Shift value for CSEN_DMR */
#define _CSEN_DMCFG_DMR_MASK                                 0xF00UL                             /**< Bit mask for CSEN_DMR */
#define _CSEN_DMCFG_DMR_DEFAULT                              0x00000000UL                        /**< Mode DEFAULT for CSEN_DMCFG */
#define CSEN_DMCFG_DMR_DEFAULT                               (_CSEN_DMCFG_DMR_DEFAULT << 8)      /**< Shifted mode DEFAULT for CSEN_DMCFG */
#define _CSEN_DMCFG_DMCR_SHIFT                               16                                  /**< Shift value for CSEN_DMCR */
#define _CSEN_DMCFG_DMCR_MASK                                0xF0000UL                           /**< Bit mask for CSEN_DMCR */
#define _CSEN_DMCFG_DMCR_DEFAULT                             0x00000000UL                        /**< Mode DEFAULT for CSEN_DMCFG */
#define CSEN_DMCFG_DMCR_DEFAULT                              (_CSEN_DMCFG_DMCR_DEFAULT << 16)    /**< Shifted mode DEFAULT for CSEN_DMCFG */
#define _CSEN_DMCFG_CRMODE_SHIFT                             20                                  /**< Shift value for CSEN_CRMODE */
#define _CSEN_DMCFG_CRMODE_MASK                              0x300000UL                          /**< Bit mask for CSEN_CRMODE */
#define _CSEN_DMCFG_CRMODE_DEFAULT                           0x00000000UL                        /**< Mode DEFAULT for CSEN_DMCFG */
#define _CSEN_DMCFG_CRMODE_DM10                              0x00000000UL                        /**< Mode DM10 for CSEN_DMCFG */
#define _CSEN_DMCFG_CRMODE_DM12                              0x00000001UL                        /**< Mode DM12 for CSEN_DMCFG */
#define _CSEN_DMCFG_CRMODE_DM14                              0x00000002UL                        /**< Mode DM14 for CSEN_DMCFG */
#define _CSEN_DMCFG_CRMODE_DM16                              0x00000003UL                        /**< Mode DM16 for CSEN_DMCFG */
#define CSEN_DMCFG_CRMODE_DEFAULT                            (_CSEN_DMCFG_CRMODE_DEFAULT << 20)  /**< Shifted mode DEFAULT for CSEN_DMCFG */
#define CSEN_DMCFG_CRMODE_DM10                               (_CSEN_DMCFG_CRMODE_DM10 << 20)     /**< Shifted mode DM10 for CSEN_DMCFG */
#define CSEN_DMCFG_CRMODE_DM12                               (_CSEN_DMCFG_CRMODE_DM12 << 20)     /**< Shifted mode DM12 for CSEN_DMCFG */
#define CSEN_DMCFG_CRMODE_DM14                               (_CSEN_DMCFG_CRMODE_DM14 << 20)     /**< Shifted mode DM14 for CSEN_DMCFG */
#define CSEN_DMCFG_CRMODE_DM16                               (_CSEN_DMCFG_CRMODE_DM16 << 20)     /**< Shifted mode DM16 for CSEN_DMCFG */
#define CSEN_DMCFG_DMGRDIS                                   (0x1UL << 28)                       /**< Delta Modulation Gain Step Reduction Disable */
#define _CSEN_DMCFG_DMGRDIS_SHIFT                            28                                  /**< Shift value for CSEN_DMGRDIS */
#define _CSEN_DMCFG_DMGRDIS_MASK                             0x10000000UL                        /**< Bit mask for CSEN_DMGRDIS */
#define _CSEN_DMCFG_DMGRDIS_DEFAULT                          0x00000000UL                        /**< Mode DEFAULT for CSEN_DMCFG */
#define CSEN_DMCFG_DMGRDIS_DEFAULT                           (_CSEN_DMCFG_DMGRDIS_DEFAULT << 28) /**< Shifted mode DEFAULT for CSEN_DMCFG */

/* Bit fields for CSEN ANACTRL */
#define _CSEN_ANACTRL_RESETVALUE                             0x00000070UL                           /**< Default value for CSEN_ANACTRL */
#define _CSEN_ANACTRL_MASK                                   0x00700770UL                           /**< Mask for CSEN_ANACTRL */
#define _CSEN_ANACTRL_IREFPROG_SHIFT                         4                                      /**< Shift value for CSEN_IREFPROG */
#define _CSEN_ANACTRL_IREFPROG_MASK                          0x70UL                                 /**< Bit mask for CSEN_IREFPROG */
#define _CSEN_ANACTRL_IREFPROG_DEFAULT                       0x00000007UL                           /**< Mode DEFAULT for CSEN_ANACTRL */
#define CSEN_ANACTRL_IREFPROG_DEFAULT                        (_CSEN_ANACTRL_IREFPROG_DEFAULT << 4)  /**< Shifted mode DEFAULT for CSEN_ANACTRL */
#define _CSEN_ANACTRL_IDACIREFS_SHIFT                        8                                      /**< Shift value for CSEN_IDACIREFS */
#define _CSEN_ANACTRL_IDACIREFS_MASK                         0x700UL                                /**< Bit mask for CSEN_IDACIREFS */
#define _CSEN_ANACTRL_IDACIREFS_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CSEN_ANACTRL */
#define CSEN_ANACTRL_IDACIREFS_DEFAULT                       (_CSEN_ANACTRL_IDACIREFS_DEFAULT << 8) /**< Shifted mode DEFAULT for CSEN_ANACTRL */
#define _CSEN_ANACTRL_TRSTPROG_SHIFT                         20                                     /**< Shift value for CSEN_TRSTPROG */
#define _CSEN_ANACTRL_TRSTPROG_MASK                          0x700000UL                             /**< Bit mask for CSEN_TRSTPROG */
#define _CSEN_ANACTRL_TRSTPROG_DEFAULT                       0x00000000UL                           /**< Mode DEFAULT for CSEN_ANACTRL */
#define CSEN_ANACTRL_TRSTPROG_DEFAULT                        (_CSEN_ANACTRL_TRSTPROG_DEFAULT << 20) /**< Shifted mode DEFAULT for CSEN_ANACTRL */

/* Bit fields for CSEN IF */
#define _CSEN_IF_RESETVALUE                                  0x00000000UL                          /**< Default value for CSEN_IF */
#define _CSEN_IF_MASK                                        0x0000001FUL                          /**< Mask for CSEN_IF */
#define CSEN_IF_CMP                                          (0x1UL << 0)                          /**< Digital Comparator Interrupt Flag */
#define _CSEN_IF_CMP_SHIFT                                   0                                     /**< Shift value for CSEN_CMP */
#define _CSEN_IF_CMP_MASK                                    0x1UL                                 /**< Bit mask for CSEN_CMP */
#define _CSEN_IF_CMP_DEFAULT                                 0x00000000UL                          /**< Mode DEFAULT for CSEN_IF */
#define CSEN_IF_CMP_DEFAULT                                  (_CSEN_IF_CMP_DEFAULT << 0)           /**< Shifted mode DEFAULT for CSEN_IF */
#define CSEN_IF_CONV                                         (0x1UL << 1)                          /**< Conversion Done Interrupt Flag */
#define _CSEN_IF_CONV_SHIFT                                  1                                     /**< Shift value for CSEN_CONV */
#define _CSEN_IF_CONV_MASK                                   0x2UL                                 /**< Bit mask for CSEN_CONV */
#define _CSEN_IF_CONV_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for CSEN_IF */
#define CSEN_IF_CONV_DEFAULT                                 (_CSEN_IF_CONV_DEFAULT << 1)          /**< Shifted mode DEFAULT for CSEN_IF */
#define CSEN_IF_EOS                                          (0x1UL << 2)                          /**< End of Scan Interrupt Flag. */
#define _CSEN_IF_EOS_SHIFT                                   2                                     /**< Shift value for CSEN_EOS */
#define _CSEN_IF_EOS_MASK                                    0x4UL                                 /**< Bit mask for CSEN_EOS */
#define _CSEN_IF_EOS_DEFAULT                                 0x00000000UL                          /**< Mode DEFAULT for CSEN_IF */
#define CSEN_IF_EOS_DEFAULT                                  (_CSEN_IF_EOS_DEFAULT << 2)           /**< Shifted mode DEFAULT for CSEN_IF */
#define CSEN_IF_DMAOF                                        (0x1UL << 3)                          /**< DMA Overflow Interrupt Flag. */
#define _CSEN_IF_DMAOF_SHIFT                                 3                                     /**< Shift value for CSEN_DMAOF */
#define _CSEN_IF_DMAOF_MASK                                  0x8UL                                 /**< Bit mask for CSEN_DMAOF */
#define _CSEN_IF_DMAOF_DEFAULT                               0x00000000UL                          /**< Mode DEFAULT for CSEN_IF */
#define CSEN_IF_DMAOF_DEFAULT                                (_CSEN_IF_DMAOF_DEFAULT << 3)         /**< Shifted mode DEFAULT for CSEN_IF */
#define CSEN_IF_APORTCONFLICT                                (0x1UL << 4)                          /**< APORT Conflict Interrupt Flag */
#define _CSEN_IF_APORTCONFLICT_SHIFT                         4                                     /**< Shift value for CSEN_APORTCONFLICT */
#define _CSEN_IF_APORTCONFLICT_MASK                          0x10UL                                /**< Bit mask for CSEN_APORTCONFLICT */
#define _CSEN_IF_APORTCONFLICT_DEFAULT                       0x00000000UL                          /**< Mode DEFAULT for CSEN_IF */
#define CSEN_IF_APORTCONFLICT_DEFAULT                        (_CSEN_IF_APORTCONFLICT_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_IF */

/* Bit fields for CSEN IFS */
#define _CSEN_IFS_RESETVALUE                                 0x00000000UL                           /**< Default value for CSEN_IFS */
#define _CSEN_IFS_MASK                                       0x0000001FUL                           /**< Mask for CSEN_IFS */
#define CSEN_IFS_CMP                                         (0x1UL << 0)                           /**< Set CMP Interrupt Flag */
#define _CSEN_IFS_CMP_SHIFT                                  0                                      /**< Shift value for CSEN_CMP */
#define _CSEN_IFS_CMP_MASK                                   0x1UL                                  /**< Bit mask for CSEN_CMP */
#define _CSEN_IFS_CMP_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_CMP_DEFAULT                                 (_CSEN_IFS_CMP_DEFAULT << 0)           /**< Shifted mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_CONV                                        (0x1UL << 1)                           /**< Set CONV Interrupt Flag */
#define _CSEN_IFS_CONV_SHIFT                                 1                                      /**< Shift value for CSEN_CONV */
#define _CSEN_IFS_CONV_MASK                                  0x2UL                                  /**< Bit mask for CSEN_CONV */
#define _CSEN_IFS_CONV_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_CONV_DEFAULT                                (_CSEN_IFS_CONV_DEFAULT << 1)          /**< Shifted mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_EOS                                         (0x1UL << 2)                           /**< Set EOS Interrupt Flag */
#define _CSEN_IFS_EOS_SHIFT                                  2                                      /**< Shift value for CSEN_EOS */
#define _CSEN_IFS_EOS_MASK                                   0x4UL                                  /**< Bit mask for CSEN_EOS */
#define _CSEN_IFS_EOS_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_EOS_DEFAULT                                 (_CSEN_IFS_EOS_DEFAULT << 2)           /**< Shifted mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_DMAOF                                       (0x1UL << 3)                           /**< Set DMAOF Interrupt Flag */
#define _CSEN_IFS_DMAOF_SHIFT                                3                                      /**< Shift value for CSEN_DMAOF */
#define _CSEN_IFS_DMAOF_MASK                                 0x8UL                                  /**< Bit mask for CSEN_DMAOF */
#define _CSEN_IFS_DMAOF_DEFAULT                              0x00000000UL                           /**< Mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_DMAOF_DEFAULT                               (_CSEN_IFS_DMAOF_DEFAULT << 3)         /**< Shifted mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_APORTCONFLICT                               (0x1UL << 4)                           /**< Set APORTCONFLICT Interrupt Flag */
#define _CSEN_IFS_APORTCONFLICT_SHIFT                        4                                      /**< Shift value for CSEN_APORTCONFLICT */
#define _CSEN_IFS_APORTCONFLICT_MASK                         0x10UL                                 /**< Bit mask for CSEN_APORTCONFLICT */
#define _CSEN_IFS_APORTCONFLICT_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CSEN_IFS */
#define CSEN_IFS_APORTCONFLICT_DEFAULT                       (_CSEN_IFS_APORTCONFLICT_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_IFS */

/* Bit fields for CSEN IFC */
#define _CSEN_IFC_RESETVALUE                                 0x00000000UL                           /**< Default value for CSEN_IFC */
#define _CSEN_IFC_MASK                                       0x0000001FUL                           /**< Mask for CSEN_IFC */
#define CSEN_IFC_CMP                                         (0x1UL << 0)                           /**< Clear CMP Interrupt Flag */
#define _CSEN_IFC_CMP_SHIFT                                  0                                      /**< Shift value for CSEN_CMP */
#define _CSEN_IFC_CMP_MASK                                   0x1UL                                  /**< Bit mask for CSEN_CMP */
#define _CSEN_IFC_CMP_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_CMP_DEFAULT                                 (_CSEN_IFC_CMP_DEFAULT << 0)           /**< Shifted mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_CONV                                        (0x1UL << 1)                           /**< Clear CONV Interrupt Flag */
#define _CSEN_IFC_CONV_SHIFT                                 1                                      /**< Shift value for CSEN_CONV */
#define _CSEN_IFC_CONV_MASK                                  0x2UL                                  /**< Bit mask for CSEN_CONV */
#define _CSEN_IFC_CONV_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_CONV_DEFAULT                                (_CSEN_IFC_CONV_DEFAULT << 1)          /**< Shifted mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_EOS                                         (0x1UL << 2)                           /**< Clear EOS Interrupt Flag */
#define _CSEN_IFC_EOS_SHIFT                                  2                                      /**< Shift value for CSEN_EOS */
#define _CSEN_IFC_EOS_MASK                                   0x4UL                                  /**< Bit mask for CSEN_EOS */
#define _CSEN_IFC_EOS_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_EOS_DEFAULT                                 (_CSEN_IFC_EOS_DEFAULT << 2)           /**< Shifted mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_DMAOF                                       (0x1UL << 3)                           /**< Clear DMAOF Interrupt Flag */
#define _CSEN_IFC_DMAOF_SHIFT                                3                                      /**< Shift value for CSEN_DMAOF */
#define _CSEN_IFC_DMAOF_MASK                                 0x8UL                                  /**< Bit mask for CSEN_DMAOF */
#define _CSEN_IFC_DMAOF_DEFAULT                              0x00000000UL                           /**< Mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_DMAOF_DEFAULT                               (_CSEN_IFC_DMAOF_DEFAULT << 3)         /**< Shifted mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_APORTCONFLICT                               (0x1UL << 4)                           /**< Clear APORTCONFLICT Interrupt Flag */
#define _CSEN_IFC_APORTCONFLICT_SHIFT                        4                                      /**< Shift value for CSEN_APORTCONFLICT */
#define _CSEN_IFC_APORTCONFLICT_MASK                         0x10UL                                 /**< Bit mask for CSEN_APORTCONFLICT */
#define _CSEN_IFC_APORTCONFLICT_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CSEN_IFC */
#define CSEN_IFC_APORTCONFLICT_DEFAULT                       (_CSEN_IFC_APORTCONFLICT_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_IFC */

/* Bit fields for CSEN IEN */
#define _CSEN_IEN_RESETVALUE                                 0x00000000UL                           /**< Default value for CSEN_IEN */
#define _CSEN_IEN_MASK                                       0x0000001FUL                           /**< Mask for CSEN_IEN */
#define CSEN_IEN_CMP                                         (0x1UL << 0)                           /**< CMP Interrupt Enable */
#define _CSEN_IEN_CMP_SHIFT                                  0                                      /**< Shift value for CSEN_CMP */
#define _CSEN_IEN_CMP_MASK                                   0x1UL                                  /**< Bit mask for CSEN_CMP */
#define _CSEN_IEN_CMP_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_CMP_DEFAULT                                 (_CSEN_IEN_CMP_DEFAULT << 0)           /**< Shifted mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_CONV                                        (0x1UL << 1)                           /**< CONV Interrupt Enable */
#define _CSEN_IEN_CONV_SHIFT                                 1                                      /**< Shift value for CSEN_CONV */
#define _CSEN_IEN_CONV_MASK                                  0x2UL                                  /**< Bit mask for CSEN_CONV */
#define _CSEN_IEN_CONV_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_CONV_DEFAULT                                (_CSEN_IEN_CONV_DEFAULT << 1)          /**< Shifted mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_EOS                                         (0x1UL << 2)                           /**< EOS Interrupt Enable */
#define _CSEN_IEN_EOS_SHIFT                                  2                                      /**< Shift value for CSEN_EOS */
#define _CSEN_IEN_EOS_MASK                                   0x4UL                                  /**< Bit mask for CSEN_EOS */
#define _CSEN_IEN_EOS_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_EOS_DEFAULT                                 (_CSEN_IEN_EOS_DEFAULT << 2)           /**< Shifted mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_DMAOF                                       (0x1UL << 3)                           /**< DMAOF Interrupt Enable */
#define _CSEN_IEN_DMAOF_SHIFT                                3                                      /**< Shift value for CSEN_DMAOF */
#define _CSEN_IEN_DMAOF_MASK                                 0x8UL                                  /**< Bit mask for CSEN_DMAOF */
#define _CSEN_IEN_DMAOF_DEFAULT                              0x00000000UL                           /**< Mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_DMAOF_DEFAULT                               (_CSEN_IEN_DMAOF_DEFAULT << 3)         /**< Shifted mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_APORTCONFLICT                               (0x1UL << 4)                           /**< APORTCONFLICT Interrupt Enable */
#define _CSEN_IEN_APORTCONFLICT_SHIFT                        4                                      /**< Shift value for CSEN_APORTCONFLICT */
#define _CSEN_IEN_APORTCONFLICT_MASK                         0x10UL                                 /**< Bit mask for CSEN_APORTCONFLICT */
#define _CSEN_IEN_APORTCONFLICT_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CSEN_IEN */
#define CSEN_IEN_APORTCONFLICT_DEFAULT                       (_CSEN_IEN_APORTCONFLICT_DEFAULT << 4) /**< Shifted mode DEFAULT for CSEN_IEN */

/** @} */
/** @} End of group EFR32FG13P_CSEN */
/** @} End of group Parts */
/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Comparator Mode. Selects the operation of the digital comparator. */
typedef enum {
  /** Comparator is disabled. */
  csenCmpModeDisabled    = 0,

  /** Comparator trips when the result is greater than the threshold. */
  csenCmpModeGreater     = CSEN_CTRL_CMPEN | CSEN_CTRL_CMPPOL_GT,

  /** Comparator trips when the result is less or equal to the threshold. */
  csenCmpModeLessOrEqual = CSEN_CTRL_CMPEN | CSEN_CTRL_CMPPOL_LTE,

  /** Comparator trips when the EMA is within the threshold window. */
  csenCmpModeEMAWindow   = CSEN_CTRL_EMACMPEN,
} CSEN_CmpMode_TypeDef;

/** Converter Select. Determines the converter operational mode. */
typedef enum {
  /** Successive Approximation (SAR) converter. */
  csenConvSelSAR     = CSEN_CTRL_CONVSEL_SAR,

  /** Successive Approximation (SAR) converter with low freq attenuation. */
  csenConvSelSARChop = CSEN_CTRL_CONVSEL_SAR | CSEN_CTRL_CHOPEN_ENABLE,

  /** Delta Modulation (DM) converter. */
  csenConvSelDM      = CSEN_CTRL_CONVSEL_DM,

  /** Delta Modulation (DM) converter with low frequency attenuation. */
  csenConvSelDMChop  = CSEN_CTRL_CONVSEL_DM | CSEN_CTRL_CHOPEN_ENABLE,
} CSEN_ConvSel_TypeDef;

/** Sample Mode. Determines how inputs are sampled for a conversion. */
typedef enum {
  /** Convert multiple inputs shorted together and stop. */
  csenSampleModeBonded     = CSEN_CTRL_CM_SGL | CSEN_CTRL_MCEN_ENABLE,

  /** Convert one input and stop. */
  csenSampleModeSingle     = CSEN_CTRL_CM_SGL,

  /** Convert multiple inputs one at a time and stop. */
  csenSampleModeScan       = CSEN_CTRL_CM_SCAN,

  /** Continuously convert multiple inputs shorted together. */
  csenSampleModeContBonded = CSEN_CTRL_CM_CONTSGL | CSEN_CTRL_MCEN_ENABLE,

  /** Continuously convert one input. */
  csenSampleModeContSingle = CSEN_CTRL_CM_CONTSGL,

  /** Continuously convert multiple inputs one at a time. */
  csenSampleModeContScan   = CSEN_CTRL_CM_CONTSCAN,
} CSEN_SampleMode_TypeDef;

/** Start Trigger Select. */
typedef enum {
  csenTrigSelPRS   = _CSEN_CTRL_STM_PRS,   /**< PRS system. */
  csenTrigSelTimer = _CSEN_CTRL_STM_TIMER, /**< CSEN PC timer. */
  csenTrigSelStart = _CSEN_CTRL_STM_START, /**< Start bit. */
} CSEN_TrigSel_TypeDef;

/** Accumulator Mode Select. */
typedef enum {
  csenAccMode1  = _CSEN_CTRL_ACU_ACC1,  /**< Accumulate 1 sample. */
  csenAccMode2  = _CSEN_CTRL_ACU_ACC2,  /**< Accumulate 2 samples. */
  csenAccMode4  = _CSEN_CTRL_ACU_ACC4,  /**< Accumulate 4 samples. */
  csenAccMode8  = _CSEN_CTRL_ACU_ACC8,  /**< Accumulate 8 samples. */
  csenAccMode16 = _CSEN_CTRL_ACU_ACC16, /**< Accumulate 16 samples. */
  csenAccMode32 = _CSEN_CTRL_ACU_ACC32, /**< Accumulate 32 samples. */
  csenAccMode64 = _CSEN_CTRL_ACU_ACC64, /**< Accumulate 64 samples. */
} CSEN_AccMode_TypeDef;

/** Successive Approximation (SAR) Conversion Resolution. */
typedef enum {
  csenSARRes10 = _CSEN_CTRL_SARCR_CLK10, /**< 10-bit resolution. */
  csenSARRes12 = _CSEN_CTRL_SARCR_CLK12, /**< 12-bit resolution. */
  csenSARRes14 = _CSEN_CTRL_SARCR_CLK14, /**< 14-bit resolution. */
  csenSARRes16 = _CSEN_CTRL_SARCR_CLK16, /**< 16-bit resolution. */
} CSEN_SARRes_TypeDef;

/** Delta Modulator (DM) Conversion Resolution. */
typedef enum {
  csenDMRes10 = _CSEN_DMCFG_CRMODE_DM10, /**< 10-bit resolution. */
  csenDMRes12 = _CSEN_DMCFG_CRMODE_DM12, /**< 12-bit resolution. */
  csenDMRes14 = _CSEN_DMCFG_CRMODE_DM14, /**< 14-bit resolution. */
  csenDMRes16 = _CSEN_DMCFG_CRMODE_DM16, /**< 16-bit resolution. */
} CSEN_DMRes_TypeDef;

/** Period counter clock pre-scaler. See the reference manual for source clock
 *  information. */
typedef enum {
  csenPCPrescaleDiv1   = _CSEN_TIMCTRL_PCPRESC_DIV1,   /**< Divide by 1. */
  csenPCPrescaleDiv2   = _CSEN_TIMCTRL_PCPRESC_DIV2,   /**< Divide by 2. */
  csenPCPrescaleDiv4   = _CSEN_TIMCTRL_PCPRESC_DIV4,   /**< Divide by 4. */
  csenPCPrescaleDiv8   = _CSEN_TIMCTRL_PCPRESC_DIV8,   /**< Divide by 8. */
  csenPCPrescaleDiv16  = _CSEN_TIMCTRL_PCPRESC_DIV16,  /**< Divide by 16. */
  csenPCPrescaleDiv32  = _CSEN_TIMCTRL_PCPRESC_DIV32,  /**< Divide by 32. */
  csenPCPrescaleDiv64  = _CSEN_TIMCTRL_PCPRESC_DIV64,  /**< Divide by 64. */
  csenPCPrescaleDiv128 = _CSEN_TIMCTRL_PCPRESC_DIV128, /**< Divide by 128. */
} CSEN_PCPrescale_TypeDef;

/** Exponential Moving Average sample weight. */
typedef enum {
  csenEMASampleW1  = _CSEN_EMACTRL_EMASAMPLE_W1,  /**< Weight 1. */
  csenEMASampleW2  = _CSEN_EMACTRL_EMASAMPLE_W2,  /**< Weight 2. */
  csenEMASampleW4  = _CSEN_EMACTRL_EMASAMPLE_W4,  /**< Weight 4. */
  csenEMASampleW8  = _CSEN_EMACTRL_EMASAMPLE_W8,  /**< Weight 8. */
  csenEMASampleW16 = _CSEN_EMACTRL_EMASAMPLE_W16, /**< Weight 16. */
  csenEMASampleW32 = _CSEN_EMACTRL_EMASAMPLE_W32, /**< Weight 32. */
  csenEMASampleW64 = _CSEN_EMACTRL_EMASAMPLE_W64, /**< Weight 64. */
} CSEN_EMASample_TypeDef;

/** Reset Phase Timing Select (units are microseconds). */
typedef enum {
  csenResetPhaseSel0 = 0,  /**< Reset phase time = 0.75 usec. */
  csenResetPhaseSel1 = 1,  /**< Reset phase time = 1.00 usec. */
  csenResetPhaseSel2 = 2,  /**< Reset phase time = 1.20 usec. */
  csenResetPhaseSel3 = 3,  /**< Reset phase time = 1.50 usec. */
  csenResetPhaseSel4 = 4,  /**< Reset phase time = 2.00 usec. */
  csenResetPhaseSel5 = 5,  /**< Reset phase time = 3.00 usec. */
  csenResetPhaseSel6 = 6,  /**< Reset phase time = 6.00 usec. */
  csenResetPhaseSel7 = 7,  /**< Reset phase time = 12.0 usec. */
} CSEN_ResetPhaseSel_TypeDef;

/** Drive Strength Select. Scales the output current. */
typedef enum {
  csenDriveSelFull = 0,  /**< Drive strength = fully on. */
  csenDriveSel1 = 1,     /**< Drive strength = 1/8 full scale. */
  csenDriveSel2 = 2,     /**< Drive strength = 1/4 full scale. */
  csenDriveSel3 = 3,     /**< Drive strength = 3/8 full scale. */
  csenDriveSel4 = 4,     /**< Drive strength = 1/2 full scale. */
  csenDriveSel5 = 5,     /**< Drive strength = 5/8 full scale. */
  csenDriveSel6 = 6,     /**< Drive strength = 3/4 full scale. */
  csenDriveSel7 = 7,     /**< Drive strength = 7/8 full scale. */
} CSEN_DriveSel_TypeDef;

/** Gain Select. See reference manual for information on each setting. */
typedef enum {
  csenGainSel1X = 0,  /**< Gain = 1x. */
  csenGainSel2X = 1,  /**< Gain = 2x. */
  csenGainSel3X = 2,  /**< Gain = 3x. */
  csenGainSel4X = 3,  /**< Gain = 4x. */
  csenGainSel5X = 4,  /**< Gain = 5x. */
  csenGainSel6X = 5,  /**< Gain = 6x. */
  csenGainSel7X = 6,  /**< Gain = 7x. */
  csenGainSel8X = 7,  /**< Gain = 8x. */
} CSEN_GainSel_TypeDef;

/** Peripheral Reflex System signal used to trigger conversion. */
typedef enum {
  csenPRSSELCh0  = _CSEN_PRSSEL_PRSSEL_PRSCH0,  /**< PRS channel 0. */
  csenPRSSELCh1  = _CSEN_PRSSEL_PRSSEL_PRSCH1,  /**< PRS channel 1. */
  csenPRSSELCh2  = _CSEN_PRSSEL_PRSSEL_PRSCH2,  /**< PRS channel 2. */
  csenPRSSELCh3  = _CSEN_PRSSEL_PRSSEL_PRSCH3,  /**< PRS channel 3. */
  csenPRSSELCh4  = _CSEN_PRSSEL_PRSSEL_PRSCH4,  /**< PRS channel 4. */
  csenPRSSELCh5  = _CSEN_PRSSEL_PRSSEL_PRSCH5,  /**< PRS channel 5. */
  csenPRSSELCh6  = _CSEN_PRSSEL_PRSSEL_PRSCH6,  /**< PRS channel 6. */
  csenPRSSELCh7  = _CSEN_PRSSEL_PRSSEL_PRSCH7,  /**< PRS channel 7. */
#if defined(_CSEN_PRSSEL_PRSSEL_PRSCH8)
  csenPRSSELCh8  = _CSEN_PRSSEL_PRSSEL_PRSCH8,  /**< PRS channel 8. */
#endif
#if defined(_CSEN_PRSSEL_PRSSEL_PRSCH9)
  csenPRSSELCh9  = _CSEN_PRSSEL_PRSSEL_PRSCH9,  /**< PRS channel 9. */
#endif
#if defined(_CSEN_PRSSEL_PRSSEL_PRSCH10)
  csenPRSSELCh10 = _CSEN_PRSSEL_PRSSEL_PRSCH10, /**< PRS channel 10. */
#endif
#if defined(_CSEN_PRSSEL_PRSSEL_PRSCH11)
  csenPRSSELCh11 = _CSEN_PRSSEL_PRSSEL_PRSCH11, /**< PRS channel 11. */
#endif
} CSEN_PRSSel_TypeDef;

/** APORT channel to CSEN input selection. */
typedef enum {
  csenInputSelDefault        = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_DEFAULT,
  csenInputSelAPORT1CH0TO7   = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH0TO7,
  csenInputSelAPORT1CH8TO15  = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH8TO15,
  csenInputSelAPORT1CH16TO23 = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH16TO23,
  csenInputSelAPORT1CH24TO31 = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT1CH24TO31,
  csenInputSelAPORT3CH0TO7   = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH0TO7,
  csenInputSelAPORT3CH8TO15  = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH8TO15,
  csenInputSelAPORT3CH16TO23 = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH16TO23,
  csenInputSelAPORT3CH24TO31 = _CSEN_SCANINPUTSEL0_INPUT0TO7SEL_APORT3CH24TO31,
} CSEN_InputSel_TypeDef;

/** APORT channel to CSEN single input selection. */
typedef enum {
  csenSingleSelDefault     = _CSEN_SINGLECTRL_SINGLESEL_DEFAULT,
  csenSingleSelAPORT1XCH0  = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH0,
  csenSingleSelAPORT1YCH1  = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH1,
  csenSingleSelAPORT1XCH2  = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH2,
  csenSingleSelAPORT1YCH3  = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH3,
  csenSingleSelAPORT1XCH4  = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH4,
  csenSingleSelAPORT1YCH5  = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH5,
  csenSingleSelAPORT1XCH6  = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH6,
  csenSingleSelAPORT1YCH7  = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH7,
  csenSingleSelAPORT1XCH8  = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH8,
  csenSingleSelAPORT1YCH9  = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH9,
  csenSingleSelAPORT1XCH10 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH10,
  csenSingleSelAPORT1YCH11 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH11,
  csenSingleSelAPORT1XCH12 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH12,
  csenSingleSelAPORT1YCH13 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH13,
  csenSingleSelAPORT1XCH14 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH14,
  csenSingleSelAPORT1YCH15 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH15,
  csenSingleSelAPORT1XCH16 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH16,
  csenSingleSelAPORT1YCH17 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH17,
  csenSingleSelAPORT1XCH18 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH18,
  csenSingleSelAPORT1YCH19 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH19,
  csenSingleSelAPORT1XCH20 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH20,
  csenSingleSelAPORT1YCH21 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH21,
  csenSingleSelAPORT1XCH22 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH22,
  csenSingleSelAPORT1YCH23 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH23,
  csenSingleSelAPORT1XCH24 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH24,
  csenSingleSelAPORT1YCH25 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH25,
  csenSingleSelAPORT1XCH26 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH26,
  csenSingleSelAPORT1YCH27 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH27,
  csenSingleSelAPORT1XCH28 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH28,
  csenSingleSelAPORT1YCH29 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH29,
  csenSingleSelAPORT1XCH30 = _CSEN_SINGLECTRL_SINGLESEL_APORT1XCH30,
  csenSingleSelAPORT1YCH31 = _CSEN_SINGLECTRL_SINGLESEL_APORT1YCH31,
  csenSingleSelAPORT3XCH0  = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH0,
  csenSingleSelAPORT3YCH1  = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH1,
  csenSingleSelAPORT3XCH2  = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH2,
  csenSingleSelAPORT3YCH3  = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH3,
  csenSingleSelAPORT3XCH4  = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH4,
  csenSingleSelAPORT3YCH5  = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH5,
  csenSingleSelAPORT3XCH6  = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH6,
  csenSingleSelAPORT3YCH7  = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH7,
  csenSingleSelAPORT3XCH8  = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH8,
  csenSingleSelAPORT3YCH9  = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH9,
  csenSingleSelAPORT3XCH10 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH10,
  csenSingleSelAPORT3YCH11 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH11,
  csenSingleSelAPORT3XCH12 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH12,
  csenSingleSelAPORT3YCH13 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH13,
  csenSingleSelAPORT3XCH14 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH14,
  csenSingleSelAPORT3YCH15 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH15,
  csenSingleSelAPORT3XCH16 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH16,
  csenSingleSelAPORT3YCH17 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH17,
  csenSingleSelAPORT3XCH18 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH18,
  csenSingleSelAPORT3YCH19 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH19,
  csenSingleSelAPORT3XCH20 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH20,
  csenSingleSelAPORT3YCH21 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH21,
  csenSingleSelAPORT3XCH22 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH22,
  csenSingleSelAPORT3YCH23 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH23,
  csenSingleSelAPORT3XCH24 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH24,
  csenSingleSelAPORT3YCH25 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH25,
  csenSingleSelAPORT3XCH26 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH26,
  csenSingleSelAPORT3YCH27 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH27,
  csenSingleSelAPORT3XCH28 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH28,
  csenSingleSelAPORT3YCH29 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH29,
  csenSingleSelAPORT3XCH30 = _CSEN_SINGLECTRL_SINGLESEL_APORT3XCH30,
  csenSingleSelAPORT3YCH31 = _CSEN_SINGLECTRL_SINGLESEL_APORT3YCH31,
} CSEN_SingleSel_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** CSEN init structure, common for all measurement modes. */
typedef struct {
  /** Requests system charge pump high accuracy mode. */
  bool                          cpAccuracyHi;

  /** Disables external kelvin connection and senses capacitor locally. */
  bool                          localSense;

  /** Keeps the converter warm allowing continuous conversions. */
  bool                          keepWarm;

  /** Converter warmup time is warmUpCount + 3 converter clock cycles. */
  uint8_t                       warmUpCount;

  /** Period counter reload value. */
  uint8_t                       pcReload;

  /** Period counter pre-scaler. */
  CSEN_PCPrescale_TypeDef       pcPrescale;

  /** Peripheral reflex system trigger selection. */
  CSEN_PRSSel_TypeDef           prsSel;

  /** CSEN input to APORT channel mapping. */
  CSEN_InputSel_TypeDef         input0To7;
  CSEN_InputSel_TypeDef         input8To15;
  CSEN_InputSel_TypeDef         input16To23;
  CSEN_InputSel_TypeDef         input24To31;
  CSEN_InputSel_TypeDef         input32To39;
  CSEN_InputSel_TypeDef         input40To47;
  CSEN_InputSel_TypeDef         input48To55;
  CSEN_InputSel_TypeDef         input56To63;
} CSEN_Init_TypeDef;

#define CSEN_INIT_DEFAULT                                             \
  {                                                                   \
    false,                      /* Charge pump low accuracy mode. */  \
    false,                      /* Use external kelvin connection. */ \
    false,                      /* Disable keep warm. */              \
    0,                          /* 0+3 cycle warmup time. */          \
    0,                          /* Period counter reload. */          \
    csenPCPrescaleDiv1,         /* Period counter prescale. */        \
    csenPRSSELCh0,              /* PRS channel 0. */                  \
    csenInputSelAPORT1CH0TO7,   /* input0To7   -> aport1ch0to7 */     \
    csenInputSelAPORT1CH8TO15,  /* input8To15  -> aport1ch8to15 */    \
    csenInputSelAPORT1CH16TO23, /* input16To23 -> aport1ch16to23 */   \
    csenInputSelAPORT1CH24TO31, /* input24To31 -> aport1ch24to31 */   \
    csenInputSelAPORT3CH0TO7,   /* input32To39 -> aport3ch0to7 */     \
    csenInputSelAPORT3CH8TO15,  /* input40To47 -> aport3ch8to15 */    \
    csenInputSelAPORT3CH16TO23, /* input48To55 -> aport3ch16to23 */   \
    csenInputSelAPORT3CH24TO31, /* input56To63 -> aport3ch24to31 */   \
  }

/** Measurement mode init structure. */
typedef struct {
  /** Selects the conversion sample mode. */
  CSEN_SampleMode_TypeDef       sampleMode;

  /** Selects the conversion trigger source. */
  CSEN_TrigSel_TypeDef          trigSel;

  /** Enables DMA operation. */
  bool                          enableDma;

  /** Disables dividing the accumulated result. */
  bool                          sumOnly;

  /** Selects the number of samples to accumulate per conversion. */
  CSEN_AccMode_TypeDef          accMode;

  /** Selects the Exponential Moving Average sample weighting. */
  CSEN_EMASample_TypeDef        emaSample;

  /** Enables the comparator and selects the comparison type. */
  CSEN_CmpMode_TypeDef          cmpMode;

  /** Comparator threshold value. Meaning depends on @p cmpMode. */
  uint16_t                      cmpThr;

  /** Selects an APORT channel for a single conversion. */
  CSEN_SingleSel_TypeDef        singleSel;

  /**
   * Mask selects inputs 0 to 31. Effect depends on @p sampleMode. If sample
   * mode is bonded, then mask selects inputs to short together. If sample
   * mode is scan, then mask selects which inputs will be scanned. If sample
   * mode is single and auto-ground is on (@p autoGnd is true), mask selects
   * which pins are grounded.
   */
  uint32_t                      inputMask0;

  /** Mask selects inputs 32 to 63. See @p inputMask0 for more information. */
  uint32_t                      inputMask1;

  /** Ground inactive inputs during a conversion. */
  bool                          autoGnd;

  /** Selects the converter type. */
  CSEN_ConvSel_TypeDef          convSel;

  /** Selects the Successive Approximation (SAR) converter resolution. */
  CSEN_SARRes_TypeDef           sarRes;

  /** Selects the Delta Modulation (DM) converter resolution. */
  CSEN_DMRes_TypeDef            dmRes;

  /** Sets the number of DM iterations (comparisons) per cycle. Only applies
   *  to the Delta Modulation converter. */
  uint8_t                       dmIterPerCycle;

  /** Sets number of DM converter cycles. Only applies to the
   *  Delta Modulation converter. */
  uint8_t                       dmCycles;

  /** Sets the DM converter initial delta value. Only applies to the
   *  Delta Modulation converter. */
  uint8_t                       dmDelta;

  /** Disable DM automatic delta size reduction per cycle. Only applies to the
   *  Delta Modulation converter. */
  bool                          dmFixedDelta;

  /** Selects the reset phase timing. Most measurements should use the default
   *  value. See reference manual for details on when to adjust. */
  CSEN_ResetPhaseSel_TypeDef    resetPhase;

  /** Selects the output drive strength.  Most measurements should use the
  *  default value. See reference manual for details on when to adjust. */
  CSEN_DriveSel_TypeDef         driveSel;

  /** Selects the converter gain. */
  CSEN_GainSel_TypeDef          gainSel;
} CSEN_InitMode_TypeDef;

#define CSEN_INITMODE_DEFAULT                                          \
  {                                                                    \
    csenSampleModeSingle,       /* Sample one input and stop. */       \
    csenTrigSelStart,           /* Use start bit to trigger. */        \
    false,                      /* Disable DMA. */                     \
    false,                      /* Average the accumulated result. */  \
    csenAccMode1,               /* Accumulate 1 sample. */             \
    csenEMASampleW1,            /* Disable the EMA. */                 \
    csenCmpModeDisabled,        /* Disable the comparator. */          \
    0,                          /* Comparator threshold not used. */   \
    csenSingleSelDefault,       /* Disconnect the single input. */     \
    0,                          /* Disable inputs 0 to 31. */          \
    0,                          /* Disable inputs 32 to 63. */         \
    false,                      /* Do not ground inactive inputs. */   \
    csenConvSelSAR,             /* Use the SAR converter. */           \
    csenSARRes10,               /* Set SAR resolution to 10 bits. */   \
    csenDMRes10,                /* Set DM resolution to 10 bits. */    \
    0,                          /* Set DM conv/cycle to default. */    \
    0,                          /* Set DM cycles to default. */        \
    0,                          /* Set DM initial delta to default. */ \
    false,                      /* Use DM auto delta reduction. */     \
    csenResetPhaseSel0,         /* Use shortest reset phase time. */   \
    csenDriveSelFull,           /* Use full output current. */         \
    csenGainSel8X,              /* Use highest converter gain. */      \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get last conversion result.
 *
 * @note
 *   Check conversion busy flag before calling this function. In addition,
 *   the result width and format depend on the parameters passed to the
 *   @ref CSEN_InitMode() function.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @return
 *   Result data from last conversion.
 ******************************************************************************/
__STATIC_INLINE uint32_t CSEN_DataGet(CSEN_TypeDef *csen)
{
  return csen->DATA;
}

/***************************************************************************//**
 * @brief
 *   Get last exponential moving average.
 *
 * @note
 *   Confirm CSEN is idle before calling this function.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @return
 *   Exponential moving average from last conversion.
 ******************************************************************************/
__STATIC_INLINE uint32_t CSEN_EMAGet(CSEN_TypeDef *csen)
{
  return (csen->EMA & _CSEN_EMA_EMA_MASK);
}

/***************************************************************************//**
 * @brief
 *   Set exponential moving average initial value.
 *
 * @note
 *   Call this function before starting a conversion.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @param[in] ema
 *   Initial value for the exponential moving average.
 ******************************************************************************/
__STATIC_INLINE void CSEN_EMASet(CSEN_TypeDef *csen, uint32_t ema)
{
  csen->EMA = ema & _CSEN_EMA_EMA_MASK;
}

/***************************************************************************//**
 * @brief
 *   Disables the CSEN.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 ******************************************************************************/
__STATIC_INLINE void CSEN_Disable(CSEN_TypeDef *csen)
{
  BUS_RegBitWrite(&csen->CTRL, _CSEN_CTRL_EN_SHIFT, 0);
}

/***************************************************************************//**
 * @brief
 *   Enables the CSEN.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 ******************************************************************************/
__STATIC_INLINE void CSEN_Enable(CSEN_TypeDef *csen)
{
  BUS_RegBitWrite(&csen->CTRL, _CSEN_CTRL_EN_SHIFT, 1);
}

void CSEN_DMBaselineSet(CSEN_TypeDef *csen, uint32_t up, uint32_t down);
void CSEN_Init(CSEN_TypeDef *csen, const CSEN_Init_TypeDef *init);
void CSEN_InitMode(CSEN_TypeDef *csen, const CSEN_InitMode_TypeDef *init);
void CSEN_Reset(CSEN_TypeDef *csen);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending CSEN interrupts.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @param[in] flags
 *   Pending CSEN interrupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the CSEN module (CSEN_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void CSEN_IntClear(CSEN_TypeDef *csen, uint32_t flags)
{
  csen->IFC = flags;
}

/***************************************************************************//**
 * @brief
 *   Disable one or more CSEN interrupts.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @param[in] flags
 *   CSEN interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the CSEN module (CSEN_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void CSEN_IntDisable(CSEN_TypeDef *csen, uint32_t flags)
{
  csen->IEN &= ~flags;
}

/***************************************************************************//**
 * @brief
 *   Enable one or more CSEN interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using CSEN_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @param[in] flags
 *   CSEN interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the CSEN module (CSEN_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void CSEN_IntEnable(CSEN_TypeDef *csen, uint32_t flags)
{
  csen->IEN |= flags;
}

/***************************************************************************//**
 * @brief
 *   Get pending CSEN interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @return
 *   CSEN interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the CSEN module (CSEN_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t CSEN_IntGet(CSEN_TypeDef *csen)
{
  return csen->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending CSEN interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled CSEN interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in CSENx_IEN_nnn
 *     register (CSENx_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the CSEN module
 *     (CSENx_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t CSEN_IntGetEnabled(CSEN_TypeDef *csen)
{
  uint32_t ien;

  /* Store CSENx->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  ien = csen->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return csen->IF & ien;
}

/***************************************************************************//**
 * @brief
 *   Set one or more pending CSEN interrupts from SW.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @param[in] flags
 *   CSEN interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the CSEN module (CSEN_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void CSEN_IntSet(CSEN_TypeDef *csen, uint32_t flags)
{
  csen->IFS = flags;
}

/***************************************************************************//**
 * @brief
 *   Return CSEN conversion busy status.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 *
 * @return
 *   True if CSEN conversion is in progress.
 ******************************************************************************/
__STATIC_INLINE bool CSEN_IsBusy(CSEN_TypeDef *csen)
{
  return (bool)(csen->STATUS & _CSEN_STATUS_CSENBUSY_MASK);
}

/***************************************************************************//**
 * @brief
 *   Start scan sequence and/or single conversion.
 *
 * @param[in] csen
 *   Pointer to CSEN peripheral register block.
 ******************************************************************************/
__STATIC_INLINE void CSEN_Start(CSEN_TypeDef *csen)
{
  csen->CMD = CSEN_CMD_START;
}
#endif // CORTEXCSEN_H