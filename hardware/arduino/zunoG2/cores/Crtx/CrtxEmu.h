#ifndef CRTX_EMU_H
#define CRTX_EMU_H

#include "ZGecko.h"

/***************************************************************************//**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @defgroup ZGM13_EMU EMU
 * @{
 * @brief ZGM13_EMU Register Declaration
 ******************************************************************************/
/** EMU Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;                  /**< Control Register  */
  __IM uint32_t  STATUS;                /**< Status Register  */
  __IOM uint32_t LOCK;                  /**< Configuration Lock Register  */
  __IOM uint32_t RAM0CTRL;              /**< Memory Control Register  */
  __IOM uint32_t CMD;                   /**< Command Register  */

  uint32_t       RESERVED0[1U];         /**< Reserved for future use **/
  __IOM uint32_t EM4CTRL;               /**< EM4 Control Register  */
  __IOM uint32_t TEMPLIMITS;            /**< Temperature Limits for Interrupt Generation  */
  __IM uint32_t  TEMP;                  /**< Value of Last Temperature Measurement  */
  __IM uint32_t  IF;                    /**< Interrupt Flag Register  */
  __IOM uint32_t IFS;                   /**< Interrupt Flag Set Register  */
  __IOM uint32_t IFC;                   /**< Interrupt Flag Clear Register  */
  __IOM uint32_t IEN;                   /**< Interrupt Enable Register  */
  __IOM uint32_t PWRLOCK;               /**< Regulator and Supply Lock Register  */

  uint32_t       RESERVED1[1U];         /**< Reserved for future use **/
  __IOM uint32_t PWRCTRL;               /**< Power Control Register  */
  __IOM uint32_t DCDCCTRL;              /**< DCDC Control  */

  uint32_t       RESERVED2[2U];         /**< Reserved for future use **/
  __IOM uint32_t DCDCMISCCTRL;          /**< DCDC Miscellaneous Control Register  */
  __IOM uint32_t DCDCZDETCTRL;          /**< DCDC Power Train NFET Zero Current Detector Control Register  */
  __IOM uint32_t DCDCCLIMCTRL;          /**< DCDC Power Train PFET Current Limiter Control Register  */
  __IOM uint32_t DCDCLNCOMPCTRL;        /**< DCDC Low Noise Compensator Control Register  */
  __IOM uint32_t DCDCLNVCTRL;           /**< DCDC Low Noise Voltage Register  */

  uint32_t       RESERVED3[1U];         /**< Reserved for future use **/
  __IOM uint32_t DCDCLPVCTRL;           /**< DCDC Low Power Voltage Register  */

  uint32_t       RESERVED4[1U];         /**< Reserved for future use **/
  __IOM uint32_t DCDCLPCTRL;            /**< DCDC Low Power Control Register  */
  __IOM uint32_t DCDCLNFREQCTRL;        /**< DCDC Low Noise Controller Frequency Control  */

  uint32_t       RESERVED5[1U];         /**< Reserved for future use **/
  __IM uint32_t  DCDCSYNC;              /**< DCDC Read Status Register  */

  uint32_t       RESERVED6[5U];         /**< Reserved for future use **/
  __IOM uint32_t VMONAVDDCTRL;          /**< VMON AVDD Channel Control  */
  __IOM uint32_t VMONALTAVDDCTRL;       /**< Alternate VMON AVDD Channel Control  */
  __IOM uint32_t VMONDVDDCTRL;          /**< VMON DVDD Channel Control  */
  __IOM uint32_t VMONIO0CTRL;           /**< VMON IOVDD0 Channel Control  */

  uint32_t       RESERVED7[4U];         /**< Reserved for future use **/
  __IOM uint32_t RAM1CTRL;              /**< Memory Control Register  */
  __IOM uint32_t RAM2CTRL;              /**< Memory Control Register  */

  uint32_t       RESERVED8[10U];        /**< Reserved for future use **/
  __IOM uint32_t DCDCLPEM01CFG;         /**< Configuration Bits for Low Power Mode to Be Applied During EM01, This Field is Only Relevant If LP Mode is Used in EM01  */

  uint32_t       RESERVED9[4U];         /**< Reserved for future use **/
  __IOM uint32_t EM23PERNORETAINCMD;    /**< Clears Corresponding Bits in EM23PERNORETAINSTATUS Unlocking Access to Peripheral  */
  __IM uint32_t  EM23PERNORETAINSTATUS; /**< Status Indicating If Peripherals Were Powered Down in EM23, Subsequently Locking Access to It  */
  __IOM uint32_t EM23PERNORETAINCTRL;   /**< When Set Corresponding Peripherals May Get Powered Down in EM23  */
} EMU_TypeDef;                          /** @} */

/***************************************************************************//**
 * @addtogroup ZGM13_EMU
 * @{
 * @defgroup ZGM13_EMU_BitFields  EMU Bit Fields
 * @{
 ******************************************************************************/

/* Bit fields for EMU CTRL */
#define _EMU_CTRL_RESETVALUE                                 0x00000000UL                                /**< Default value for EMU_CTRL */
#define _EMU_CTRL_MASK                                       0x0003031EUL                                /**< Mask for EMU_CTRL */
#define EMU_CTRL_EM2BLOCK                                    (0x1UL << 1)                                /**< Energy Mode 2 Block */
#define _EMU_CTRL_EM2BLOCK_SHIFT                             1                                           /**< Shift value for EMU_EM2BLOCK */
#define _EMU_CTRL_EM2BLOCK_MASK                              0x2UL                                       /**< Bit mask for EMU_EM2BLOCK */
#define _EMU_CTRL_EM2BLOCK_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM2BLOCK_DEFAULT                            (_EMU_CTRL_EM2BLOCK_DEFAULT << 1)           /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM2BODDIS                                   (0x1UL << 2)                                /**< Disable BOD in EM2 */
#define _EMU_CTRL_EM2BODDIS_SHIFT                            2                                           /**< Shift value for EMU_EM2BODDIS */
#define _EMU_CTRL_EM2BODDIS_MASK                             0x4UL                                       /**< Bit mask for EMU_EM2BODDIS */
#define _EMU_CTRL_EM2BODDIS_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM2BODDIS_DEFAULT                           (_EMU_CTRL_EM2BODDIS_DEFAULT << 2)          /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM01LD                                      (0x1UL << 3)                                /**< Reserved for internal use. Do not change. */
#define _EMU_CTRL_EM01LD_SHIFT                               3                                           /**< Shift value for EMU_EM01LD */
#define _EMU_CTRL_EM01LD_MASK                                0x8UL                                       /**< Bit mask for EMU_EM01LD */
#define _EMU_CTRL_EM01LD_DEFAULT                             0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM01LD_DEFAULT                              (_EMU_CTRL_EM01LD_DEFAULT << 3)             /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM23VSCALEAUTOWSEN                          (0x1UL << 4)                                /**< Automatically Configures Flash and Frequency to Wakeup From EM2 or EM3 at Low Voltage */
#define _EMU_CTRL_EM23VSCALEAUTOWSEN_SHIFT                   4                                           /**< Shift value for EMU_EM23VSCALEAUTOWSEN */
#define _EMU_CTRL_EM23VSCALEAUTOWSEN_MASK                    0x10UL                                      /**< Bit mask for EMU_EM23VSCALEAUTOWSEN */
#define _EMU_CTRL_EM23VSCALEAUTOWSEN_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM23VSCALEAUTOWSEN_DEFAULT                  (_EMU_CTRL_EM23VSCALEAUTOWSEN_DEFAULT << 4) /**< Shifted mode DEFAULT for EMU_CTRL */
#define _EMU_CTRL_EM23VSCALE_SHIFT                           8                                           /**< Shift value for EMU_EM23VSCALE */
#define _EMU_CTRL_EM23VSCALE_MASK                            0x300UL                                     /**< Bit mask for EMU_EM23VSCALE */
#define _EMU_CTRL_EM23VSCALE_DEFAULT                         0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define _EMU_CTRL_EM23VSCALE_VSCALE2                         0x00000000UL                                /**< Mode VSCALE2 for EMU_CTRL */
#define _EMU_CTRL_EM23VSCALE_VSCALE0                         0x00000002UL                                /**< Mode VSCALE0 for EMU_CTRL */
#define _EMU_CTRL_EM23VSCALE_RESV                            0x00000003UL                                /**< Mode RESV for EMU_CTRL */
#define EMU_CTRL_EM23VSCALE_DEFAULT                          (_EMU_CTRL_EM23VSCALE_DEFAULT << 8)         /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM23VSCALE_VSCALE2                          (_EMU_CTRL_EM23VSCALE_VSCALE2 << 8)         /**< Shifted mode VSCALE2 for EMU_CTRL */
#define EMU_CTRL_EM23VSCALE_VSCALE0                          (_EMU_CTRL_EM23VSCALE_VSCALE0 << 8)         /**< Shifted mode VSCALE0 for EMU_CTRL */
#define EMU_CTRL_EM23VSCALE_RESV                             (_EMU_CTRL_EM23VSCALE_RESV << 8)            /**< Shifted mode RESV for EMU_CTRL */
#define _EMU_CTRL_EM4HVSCALE_SHIFT                           16                                          /**< Shift value for EMU_EM4HVSCALE */
#define _EMU_CTRL_EM4HVSCALE_MASK                            0x30000UL                                   /**< Bit mask for EMU_EM4HVSCALE */
#define _EMU_CTRL_EM4HVSCALE_DEFAULT                         0x00000000UL                                /**< Mode DEFAULT for EMU_CTRL */
#define _EMU_CTRL_EM4HVSCALE_VSCALE2                         0x00000000UL                                /**< Mode VSCALE2 for EMU_CTRL */
#define _EMU_CTRL_EM4HVSCALE_VSCALE0                         0x00000002UL                                /**< Mode VSCALE0 for EMU_CTRL */
#define _EMU_CTRL_EM4HVSCALE_RESV                            0x00000003UL                                /**< Mode RESV for EMU_CTRL */
#define EMU_CTRL_EM4HVSCALE_DEFAULT                          (_EMU_CTRL_EM4HVSCALE_DEFAULT << 16)        /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM4HVSCALE_VSCALE2                          (_EMU_CTRL_EM4HVSCALE_VSCALE2 << 16)        /**< Shifted mode VSCALE2 for EMU_CTRL */
#define EMU_CTRL_EM4HVSCALE_VSCALE0                          (_EMU_CTRL_EM4HVSCALE_VSCALE0 << 16)        /**< Shifted mode VSCALE0 for EMU_CTRL */
#define EMU_CTRL_EM4HVSCALE_RESV                             (_EMU_CTRL_EM4HVSCALE_RESV << 16)           /**< Shifted mode RESV for EMU_CTRL */

/* Bit fields for EMU STATUS */
#define _EMU_STATUS_RESETVALUE                               0x00000000UL                           /**< Default value for EMU_STATUS */
#define _EMU_STATUS_MASK                                     0x0417011FUL                           /**< Mask for EMU_STATUS */
#define EMU_STATUS_VMONRDY                                   (0x1UL << 0)                           /**< VMON Ready */
#define _EMU_STATUS_VMONRDY_SHIFT                            0                                      /**< Shift value for EMU_VMONRDY */
#define _EMU_STATUS_VMONRDY_MASK                             0x1UL                                  /**< Bit mask for EMU_VMONRDY */
#define _EMU_STATUS_VMONRDY_DEFAULT                          0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONRDY_DEFAULT                           (_EMU_STATUS_VMONRDY_DEFAULT << 0)     /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONAVDD                                  (0x1UL << 1)                           /**< VMON AVDD Channel */
#define _EMU_STATUS_VMONAVDD_SHIFT                           1                                      /**< Shift value for EMU_VMONAVDD */
#define _EMU_STATUS_VMONAVDD_MASK                            0x2UL                                  /**< Bit mask for EMU_VMONAVDD */
#define _EMU_STATUS_VMONAVDD_DEFAULT                         0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONAVDD_DEFAULT                          (_EMU_STATUS_VMONAVDD_DEFAULT << 1)    /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONALTAVDD                               (0x1UL << 2)                           /**< Alternate VMON AVDD Channel */
#define _EMU_STATUS_VMONALTAVDD_SHIFT                        2                                      /**< Shift value for EMU_VMONALTAVDD */
#define _EMU_STATUS_VMONALTAVDD_MASK                         0x4UL                                  /**< Bit mask for EMU_VMONALTAVDD */
#define _EMU_STATUS_VMONALTAVDD_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONALTAVDD_DEFAULT                       (_EMU_STATUS_VMONALTAVDD_DEFAULT << 2) /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONDVDD                                  (0x1UL << 3)                           /**< VMON DVDD Channel */
#define _EMU_STATUS_VMONDVDD_SHIFT                           3                                      /**< Shift value for EMU_VMONDVDD */
#define _EMU_STATUS_VMONDVDD_MASK                            0x8UL                                  /**< Bit mask for EMU_VMONDVDD */
#define _EMU_STATUS_VMONDVDD_DEFAULT                         0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONDVDD_DEFAULT                          (_EMU_STATUS_VMONDVDD_DEFAULT << 3)    /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONIO0                                   (0x1UL << 4)                           /**< VMON IOVDD0 Channel */
#define _EMU_STATUS_VMONIO0_SHIFT                            4                                      /**< Shift value for EMU_VMONIO0 */
#define _EMU_STATUS_VMONIO0_MASK                             0x10UL                                 /**< Bit mask for EMU_VMONIO0 */
#define _EMU_STATUS_VMONIO0_DEFAULT                          0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONIO0_DEFAULT                           (_EMU_STATUS_VMONIO0_DEFAULT << 4)     /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONFVDD                                  (0x1UL << 8)                           /**< VMON VDDFLASH Channel */
#define _EMU_STATUS_VMONFVDD_SHIFT                           8                                      /**< Shift value for EMU_VMONFVDD */
#define _EMU_STATUS_VMONFVDD_MASK                            0x100UL                                /**< Bit mask for EMU_VMONFVDD */
#define _EMU_STATUS_VMONFVDD_DEFAULT                         0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VMONFVDD_DEFAULT                          (_EMU_STATUS_VMONFVDD_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_STATUS */
#define _EMU_STATUS_VSCALE_SHIFT                             16                                     /**< Shift value for EMU_VSCALE */
#define _EMU_STATUS_VSCALE_MASK                              0x30000UL                              /**< Bit mask for EMU_VSCALE */
#define _EMU_STATUS_VSCALE_DEFAULT                           0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define _EMU_STATUS_VSCALE_VSCALE2                           0x00000000UL                           /**< Mode VSCALE2 for EMU_STATUS */
#define _EMU_STATUS_VSCALE_VSCALE0                           0x00000002UL                           /**< Mode VSCALE0 for EMU_STATUS */
#define _EMU_STATUS_VSCALE_RESV                              0x00000003UL                           /**< Mode RESV for EMU_STATUS */
#define EMU_STATUS_VSCALE_DEFAULT                            (_EMU_STATUS_VSCALE_DEFAULT << 16)     /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VSCALE_VSCALE2                            (_EMU_STATUS_VSCALE_VSCALE2 << 16)     /**< Shifted mode VSCALE2 for EMU_STATUS */
#define EMU_STATUS_VSCALE_VSCALE0                            (_EMU_STATUS_VSCALE_VSCALE0 << 16)     /**< Shifted mode VSCALE0 for EMU_STATUS */
#define EMU_STATUS_VSCALE_RESV                               (_EMU_STATUS_VSCALE_RESV << 16)        /**< Shifted mode RESV for EMU_STATUS */
#define EMU_STATUS_VSCALEBUSY                                (0x1UL << 18)                          /**< System is Busy Scaling Voltage */
#define _EMU_STATUS_VSCALEBUSY_SHIFT                         18                                     /**< Shift value for EMU_VSCALEBUSY */
#define _EMU_STATUS_VSCALEBUSY_MASK                          0x40000UL                              /**< Bit mask for EMU_VSCALEBUSY */
#define _EMU_STATUS_VSCALEBUSY_DEFAULT                       0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_VSCALEBUSY_DEFAULT                        (_EMU_STATUS_VSCALEBUSY_DEFAULT << 18) /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_EM4IORET                                  (0x1UL << 20)                          /**< IO Retention Status */
#define _EMU_STATUS_EM4IORET_SHIFT                           20                                     /**< Shift value for EMU_EM4IORET */
#define _EMU_STATUS_EM4IORET_MASK                            0x100000UL                             /**< Bit mask for EMU_EM4IORET */
#define _EMU_STATUS_EM4IORET_DEFAULT                         0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define _EMU_STATUS_EM4IORET_DISABLED                        0x00000000UL                           /**< Mode DISABLED for EMU_STATUS */
#define _EMU_STATUS_EM4IORET_ENABLED                         0x00000001UL                           /**< Mode ENABLED for EMU_STATUS */
#define EMU_STATUS_EM4IORET_DEFAULT                          (_EMU_STATUS_EM4IORET_DEFAULT << 20)   /**< Shifted mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_EM4IORET_DISABLED                         (_EMU_STATUS_EM4IORET_DISABLED << 20)  /**< Shifted mode DISABLED for EMU_STATUS */
#define EMU_STATUS_EM4IORET_ENABLED                          (_EMU_STATUS_EM4IORET_ENABLED << 20)   /**< Shifted mode ENABLED for EMU_STATUS */
#define EMU_STATUS_TEMPACTIVE                                (0x1UL << 26)                          /**< Temperature Measurement Active */
#define _EMU_STATUS_TEMPACTIVE_SHIFT                         26                                     /**< Shift value for EMU_TEMPACTIVE */
#define _EMU_STATUS_TEMPACTIVE_MASK                          0x4000000UL                            /**< Bit mask for EMU_TEMPACTIVE */
#define _EMU_STATUS_TEMPACTIVE_DEFAULT                       0x00000000UL                           /**< Mode DEFAULT for EMU_STATUS */
#define EMU_STATUS_TEMPACTIVE_DEFAULT                        (_EMU_STATUS_TEMPACTIVE_DEFAULT << 26) /**< Shifted mode DEFAULT for EMU_STATUS */

/* Bit fields for EMU LOCK */
#define _EMU_LOCK_RESETVALUE                                 0x00000000UL                      /**< Default value for EMU_LOCK */
#define _EMU_LOCK_MASK                                       0x0000FFFFUL                      /**< Mask for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_SHIFT                              0                                 /**< Shift value for EMU_LOCKKEY */
#define _EMU_LOCK_LOCKKEY_MASK                               0xFFFFUL                          /**< Bit mask for EMU_LOCKKEY */
#define _EMU_LOCK_LOCKKEY_DEFAULT                            0x00000000UL                      /**< Mode DEFAULT for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_LOCK                               0x00000000UL                      /**< Mode LOCK for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_UNLOCKED                           0x00000000UL                      /**< Mode UNLOCKED for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_LOCKED                             0x00000001UL                      /**< Mode LOCKED for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_UNLOCK                             0x0000ADE8UL                      /**< Mode UNLOCK for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_DEFAULT                             (_EMU_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_LOCK                                (_EMU_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_UNLOCKED                            (_EMU_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_LOCKED                              (_EMU_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_UNLOCK                              (_EMU_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for EMU_LOCK */

/* Bit fields for EMU RAM0CTRL */
#define _EMU_RAM0CTRL_RESETVALUE                             0x00000000UL                              /**< Default value for EMU_RAM0CTRL */
#define _EMU_RAM0CTRL_MASK                                   0x00000001UL                              /**< Mask for EMU_RAM0CTRL */
#define _EMU_RAM0CTRL_RAMPOWERDOWN_SHIFT                     0                                         /**< Shift value for EMU_RAMPOWERDOWN */
#define _EMU_RAM0CTRL_RAMPOWERDOWN_MASK                      0x1UL                                     /**< Bit mask for EMU_RAMPOWERDOWN */
#define _EMU_RAM0CTRL_RAMPOWERDOWN_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for EMU_RAM0CTRL */
#define _EMU_RAM0CTRL_RAMPOWERDOWN_NONE                      0x00000000UL                              /**< Mode NONE for EMU_RAM0CTRL */
#define _EMU_RAM0CTRL_RAMPOWERDOWN_BLK1                      0x00000001UL                              /**< Mode BLK1 for EMU_RAM0CTRL */
#define EMU_RAM0CTRL_RAMPOWERDOWN_DEFAULT                    (_EMU_RAM0CTRL_RAMPOWERDOWN_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_RAM0CTRL */
#define EMU_RAM0CTRL_RAMPOWERDOWN_NONE                       (_EMU_RAM0CTRL_RAMPOWERDOWN_NONE << 0)    /**< Shifted mode NONE for EMU_RAM0CTRL */
#define EMU_RAM0CTRL_RAMPOWERDOWN_BLK1                       (_EMU_RAM0CTRL_RAMPOWERDOWN_BLK1 << 0)    /**< Shifted mode BLK1 for EMU_RAM0CTRL */

/* Bit fields for EMU CMD */
#define _EMU_CMD_RESETVALUE                                  0x00000000UL                        /**< Default value for EMU_CMD */
#define _EMU_CMD_MASK                                        0x00000051UL                        /**< Mask for EMU_CMD */
#define EMU_CMD_EM4UNLATCH                                   (0x1UL << 0)                        /**< EM4 Unlatch */
#define _EMU_CMD_EM4UNLATCH_SHIFT                            0                                   /**< Shift value for EMU_EM4UNLATCH */
#define _EMU_CMD_EM4UNLATCH_MASK                             0x1UL                               /**< Bit mask for EMU_EM4UNLATCH */
#define _EMU_CMD_EM4UNLATCH_DEFAULT                          0x00000000UL                        /**< Mode DEFAULT for EMU_CMD */
#define EMU_CMD_EM4UNLATCH_DEFAULT                           (_EMU_CMD_EM4UNLATCH_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_CMD */
#define EMU_CMD_EM01VSCALE0                                  (0x1UL << 4)                        /**< EM01 Voltage Scale Command to Scale to Voltage Scale Level 0 */
#define _EMU_CMD_EM01VSCALE0_SHIFT                           4                                   /**< Shift value for EMU_EM01VSCALE0 */
#define _EMU_CMD_EM01VSCALE0_MASK                            0x10UL                              /**< Bit mask for EMU_EM01VSCALE0 */
#define _EMU_CMD_EM01VSCALE0_DEFAULT                         0x00000000UL                        /**< Mode DEFAULT for EMU_CMD */
#define EMU_CMD_EM01VSCALE0_DEFAULT                          (_EMU_CMD_EM01VSCALE0_DEFAULT << 4) /**< Shifted mode DEFAULT for EMU_CMD */
#define EMU_CMD_EM01VSCALE2                                  (0x1UL << 6)                        /**< EM01 Voltage Scale Command to Scale to Voltage Scale Level 2 */
#define _EMU_CMD_EM01VSCALE2_SHIFT                           6                                   /**< Shift value for EMU_EM01VSCALE2 */
#define _EMU_CMD_EM01VSCALE2_MASK                            0x40UL                              /**< Bit mask for EMU_EM01VSCALE2 */
#define _EMU_CMD_EM01VSCALE2_DEFAULT                         0x00000000UL                        /**< Mode DEFAULT for EMU_CMD */
#define EMU_CMD_EM01VSCALE2_DEFAULT                          (_EMU_CMD_EM01VSCALE2_DEFAULT << 6) /**< Shifted mode DEFAULT for EMU_CMD */

/* Bit fields for EMU EM4CTRL */
#define _EMU_EM4CTRL_RESETVALUE                              0x00000000UL                               /**< Default value for EMU_EM4CTRL */
#define _EMU_EM4CTRL_MASK                                    0x0003003FUL                               /**< Mask for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4STATE                                 (0x1UL << 0)                               /**< Energy Mode 4 State */
#define _EMU_EM4CTRL_EM4STATE_SHIFT                          0                                          /**< Shift value for EMU_EM4STATE */
#define _EMU_EM4CTRL_EM4STATE_MASK                           0x1UL                                      /**< Bit mask for EMU_EM4STATE */
#define _EMU_EM4CTRL_EM4STATE_DEFAULT                        0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4STATE_EM4S                           0x00000000UL                               /**< Mode EM4S for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4STATE_EM4H                           0x00000001UL                               /**< Mode EM4H for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4STATE_DEFAULT                         (_EMU_EM4CTRL_EM4STATE_DEFAULT << 0)       /**< Shifted mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4STATE_EM4S                            (_EMU_EM4CTRL_EM4STATE_EM4S << 0)          /**< Shifted mode EM4S for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4STATE_EM4H                            (_EMU_EM4CTRL_EM4STATE_EM4H << 0)          /**< Shifted mode EM4H for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINLFRCO                              (0x1UL << 1)                               /**< LFRCO Retain During EM4 */
#define _EMU_EM4CTRL_RETAINLFRCO_SHIFT                       1                                          /**< Shift value for EMU_RETAINLFRCO */
#define _EMU_EM4CTRL_RETAINLFRCO_MASK                        0x2UL                                      /**< Bit mask for EMU_RETAINLFRCO */
#define _EMU_EM4CTRL_RETAINLFRCO_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINLFRCO_DEFAULT                      (_EMU_EM4CTRL_RETAINLFRCO_DEFAULT << 1)    /**< Shifted mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINLFXO                               (0x1UL << 2)                               /**< LFXO Retain During EM4 */
#define _EMU_EM4CTRL_RETAINLFXO_SHIFT                        2                                          /**< Shift value for EMU_RETAINLFXO */
#define _EMU_EM4CTRL_RETAINLFXO_MASK                         0x4UL                                      /**< Bit mask for EMU_RETAINLFXO */
#define _EMU_EM4CTRL_RETAINLFXO_DEFAULT                      0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINLFXO_DEFAULT                       (_EMU_EM4CTRL_RETAINLFXO_DEFAULT << 2)     /**< Shifted mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINULFRCO                             (0x1UL << 3)                               /**< ULFRCO Retain During EM4S */
#define _EMU_EM4CTRL_RETAINULFRCO_SHIFT                      3                                          /**< Shift value for EMU_RETAINULFRCO */
#define _EMU_EM4CTRL_RETAINULFRCO_MASK                       0x8UL                                      /**< Bit mask for EMU_RETAINULFRCO */
#define _EMU_EM4CTRL_RETAINULFRCO_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_RETAINULFRCO_DEFAULT                     (_EMU_EM4CTRL_RETAINULFRCO_DEFAULT << 3)   /**< Shifted mode DEFAULT for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4IORETMODE_SHIFT                      4                                          /**< Shift value for EMU_EM4IORETMODE */
#define _EMU_EM4CTRL_EM4IORETMODE_MASK                       0x30UL                                     /**< Bit mask for EMU_EM4IORETMODE */
#define _EMU_EM4CTRL_EM4IORETMODE_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4IORETMODE_DISABLE                    0x00000000UL                               /**< Mode DISABLE for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4IORETMODE_EM4EXIT                    0x00000001UL                               /**< Mode EM4EXIT for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4IORETMODE_SWUNLATCH                  0x00000002UL                               /**< Mode SWUNLATCH for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4IORETMODE_DEFAULT                     (_EMU_EM4CTRL_EM4IORETMODE_DEFAULT << 4)   /**< Shifted mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4IORETMODE_DISABLE                     (_EMU_EM4CTRL_EM4IORETMODE_DISABLE << 4)   /**< Shifted mode DISABLE for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4IORETMODE_EM4EXIT                     (_EMU_EM4CTRL_EM4IORETMODE_EM4EXIT << 4)   /**< Shifted mode EM4EXIT for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4IORETMODE_SWUNLATCH                   (_EMU_EM4CTRL_EM4IORETMODE_SWUNLATCH << 4) /**< Shifted mode SWUNLATCH for EMU_EM4CTRL */
#define _EMU_EM4CTRL_EM4ENTRY_SHIFT                          16                                         /**< Shift value for EMU_EM4ENTRY */
#define _EMU_EM4CTRL_EM4ENTRY_MASK                           0x30000UL                                  /**< Bit mask for EMU_EM4ENTRY */
#define _EMU_EM4CTRL_EM4ENTRY_DEFAULT                        0x00000000UL                               /**< Mode DEFAULT for EMU_EM4CTRL */
#define EMU_EM4CTRL_EM4ENTRY_DEFAULT                         (_EMU_EM4CTRL_EM4ENTRY_DEFAULT << 16)      /**< Shifted mode DEFAULT for EMU_EM4CTRL */

/* Bit fields for EMU TEMPLIMITS */
#define _EMU_TEMPLIMITS_RESETVALUE                           0x0000FF00UL                            /**< Default value for EMU_TEMPLIMITS */
#define _EMU_TEMPLIMITS_MASK                                 0x0001FFFFUL                            /**< Mask for EMU_TEMPLIMITS */
#define _EMU_TEMPLIMITS_TEMPLOW_SHIFT                        0                                       /**< Shift value for EMU_TEMPLOW */
#define _EMU_TEMPLIMITS_TEMPLOW_MASK                         0xFFUL                                  /**< Bit mask for EMU_TEMPLOW */
#define _EMU_TEMPLIMITS_TEMPLOW_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for EMU_TEMPLIMITS */
#define EMU_TEMPLIMITS_TEMPLOW_DEFAULT                       (_EMU_TEMPLIMITS_TEMPLOW_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_TEMPLIMITS */
#define _EMU_TEMPLIMITS_TEMPHIGH_SHIFT                       8                                       /**< Shift value for EMU_TEMPHIGH */
#define _EMU_TEMPLIMITS_TEMPHIGH_MASK                        0xFF00UL                                /**< Bit mask for EMU_TEMPHIGH */
#define _EMU_TEMPLIMITS_TEMPHIGH_DEFAULT                     0x000000FFUL                            /**< Mode DEFAULT for EMU_TEMPLIMITS */
#define EMU_TEMPLIMITS_TEMPHIGH_DEFAULT                      (_EMU_TEMPLIMITS_TEMPHIGH_DEFAULT << 8) /**< Shifted mode DEFAULT for EMU_TEMPLIMITS */
#define EMU_TEMPLIMITS_EM4WUEN                               (0x1UL << 16)                           /**< Enable EM4 Wakeup Due to Low/high Temperature */
#define _EMU_TEMPLIMITS_EM4WUEN_SHIFT                        16                                      /**< Shift value for EMU_EM4WUEN */
#define _EMU_TEMPLIMITS_EM4WUEN_MASK                         0x10000UL                               /**< Bit mask for EMU_EM4WUEN */
#define _EMU_TEMPLIMITS_EM4WUEN_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for EMU_TEMPLIMITS */
#define EMU_TEMPLIMITS_EM4WUEN_DEFAULT                       (_EMU_TEMPLIMITS_EM4WUEN_DEFAULT << 16) /**< Shifted mode DEFAULT for EMU_TEMPLIMITS */

/* Bit fields for EMU TEMP */
#define _EMU_TEMP_RESETVALUE                                 0x00000000UL                  /**< Default value for EMU_TEMP */
#define _EMU_TEMP_MASK                                       0x000000FFUL                  /**< Mask for EMU_TEMP */
#define _EMU_TEMP_TEMP_SHIFT                                 0                             /**< Shift value for EMU_TEMP */
#define _EMU_TEMP_TEMP_MASK                                  0xFFUL                        /**< Bit mask for EMU_TEMP */
#define _EMU_TEMP_TEMP_DEFAULT                               0x00000000UL                  /**< Mode DEFAULT for EMU_TEMP */
#define EMU_TEMP_TEMP_DEFAULT                                (_EMU_TEMP_TEMP_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_TEMP */

/* Bit fields for EMU IF */
#define _EMU_IF_RESETVALUE                                   0x00000000UL                                 /**< Default value for EMU_IF */
#define _EMU_IF_MASK                                         0xE31FC0FFUL                                 /**< Mask for EMU_IF */
#define EMU_IF_VMONAVDDFALL                                  (0x1UL << 0)                                 /**< VMON AVDD Channel Fall */
#define _EMU_IF_VMONAVDDFALL_SHIFT                           0                                            /**< Shift value for EMU_VMONAVDDFALL */
#define _EMU_IF_VMONAVDDFALL_MASK                            0x1UL                                        /**< Bit mask for EMU_VMONAVDDFALL */
#define _EMU_IF_VMONAVDDFALL_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONAVDDFALL_DEFAULT                          (_EMU_IF_VMONAVDDFALL_DEFAULT << 0)          /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONAVDDRISE                                  (0x1UL << 1)                                 /**< VMON AVDD Channel Rise */
#define _EMU_IF_VMONAVDDRISE_SHIFT                           1                                            /**< Shift value for EMU_VMONAVDDRISE */
#define _EMU_IF_VMONAVDDRISE_MASK                            0x2UL                                        /**< Bit mask for EMU_VMONAVDDRISE */
#define _EMU_IF_VMONAVDDRISE_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONAVDDRISE_DEFAULT                          (_EMU_IF_VMONAVDDRISE_DEFAULT << 1)          /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONALTAVDDFALL                               (0x1UL << 2)                                 /**< Alternate VMON AVDD Channel Fall */
#define _EMU_IF_VMONALTAVDDFALL_SHIFT                        2                                            /**< Shift value for EMU_VMONALTAVDDFALL */
#define _EMU_IF_VMONALTAVDDFALL_MASK                         0x4UL                                        /**< Bit mask for EMU_VMONALTAVDDFALL */
#define _EMU_IF_VMONALTAVDDFALL_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONALTAVDDFALL_DEFAULT                       (_EMU_IF_VMONALTAVDDFALL_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONALTAVDDRISE                               (0x1UL << 3)                                 /**< Alternate VMON AVDD Channel Rise */
#define _EMU_IF_VMONALTAVDDRISE_SHIFT                        3                                            /**< Shift value for EMU_VMONALTAVDDRISE */
#define _EMU_IF_VMONALTAVDDRISE_MASK                         0x8UL                                        /**< Bit mask for EMU_VMONALTAVDDRISE */
#define _EMU_IF_VMONALTAVDDRISE_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONALTAVDDRISE_DEFAULT                       (_EMU_IF_VMONALTAVDDRISE_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONDVDDFALL                                  (0x1UL << 4)                                 /**< VMON DVDD Channel Fall */
#define _EMU_IF_VMONDVDDFALL_SHIFT                           4                                            /**< Shift value for EMU_VMONDVDDFALL */
#define _EMU_IF_VMONDVDDFALL_MASK                            0x10UL                                       /**< Bit mask for EMU_VMONDVDDFALL */
#define _EMU_IF_VMONDVDDFALL_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONDVDDFALL_DEFAULT                          (_EMU_IF_VMONDVDDFALL_DEFAULT << 4)          /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONDVDDRISE                                  (0x1UL << 5)                                 /**< VMON DVDD Channel Rise */
#define _EMU_IF_VMONDVDDRISE_SHIFT                           5                                            /**< Shift value for EMU_VMONDVDDRISE */
#define _EMU_IF_VMONDVDDRISE_MASK                            0x20UL                                       /**< Bit mask for EMU_VMONDVDDRISE */
#define _EMU_IF_VMONDVDDRISE_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONDVDDRISE_DEFAULT                          (_EMU_IF_VMONDVDDRISE_DEFAULT << 5)          /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONIO0FALL                                   (0x1UL << 6)                                 /**< VMON IOVDD0 Channel Fall */
#define _EMU_IF_VMONIO0FALL_SHIFT                            6                                            /**< Shift value for EMU_VMONIO0FALL */
#define _EMU_IF_VMONIO0FALL_MASK                             0x40UL                                       /**< Bit mask for EMU_VMONIO0FALL */
#define _EMU_IF_VMONIO0FALL_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONIO0FALL_DEFAULT                           (_EMU_IF_VMONIO0FALL_DEFAULT << 6)           /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONIO0RISE                                   (0x1UL << 7)                                 /**< VMON IOVDD0 Channel Rise */
#define _EMU_IF_VMONIO0RISE_SHIFT                            7                                            /**< Shift value for EMU_VMONIO0RISE */
#define _EMU_IF_VMONIO0RISE_MASK                             0x80UL                                       /**< Bit mask for EMU_VMONIO0RISE */
#define _EMU_IF_VMONIO0RISE_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONIO0RISE_DEFAULT                           (_EMU_IF_VMONIO0RISE_DEFAULT << 7)           /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONFVDDFALL                                  (0x1UL << 14)                                /**< VMON VDDFLASH Channel Fall */
#define _EMU_IF_VMONFVDDFALL_SHIFT                           14                                           /**< Shift value for EMU_VMONFVDDFALL */
#define _EMU_IF_VMONFVDDFALL_MASK                            0x4000UL                                     /**< Bit mask for EMU_VMONFVDDFALL */
#define _EMU_IF_VMONFVDDFALL_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONFVDDFALL_DEFAULT                          (_EMU_IF_VMONFVDDFALL_DEFAULT << 14)         /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VMONFVDDRISE                                  (0x1UL << 15)                                /**< VMON VDDFLASH Channel Rise */
#define _EMU_IF_VMONFVDDRISE_SHIFT                           15                                           /**< Shift value for EMU_VMONFVDDRISE */
#define _EMU_IF_VMONFVDDRISE_MASK                            0x8000UL                                     /**< Bit mask for EMU_VMONFVDDRISE */
#define _EMU_IF_VMONFVDDRISE_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VMONFVDDRISE_DEFAULT                          (_EMU_IF_VMONFVDDRISE_DEFAULT << 15)         /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_PFETOVERCURRENTLIMIT                          (0x1UL << 16)                                /**< PFET Current Limit Hit */
#define _EMU_IF_PFETOVERCURRENTLIMIT_SHIFT                   16                                           /**< Shift value for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IF_PFETOVERCURRENTLIMIT_MASK                    0x10000UL                                    /**< Bit mask for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IF_PFETOVERCURRENTLIMIT_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_PFETOVERCURRENTLIMIT_DEFAULT                  (_EMU_IF_PFETOVERCURRENTLIMIT_DEFAULT << 16) /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_NFETOVERCURRENTLIMIT                          (0x1UL << 17)                                /**< NFET Current Limit Hit */
#define _EMU_IF_NFETOVERCURRENTLIMIT_SHIFT                   17                                           /**< Shift value for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IF_NFETOVERCURRENTLIMIT_MASK                    0x20000UL                                    /**< Bit mask for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IF_NFETOVERCURRENTLIMIT_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_NFETOVERCURRENTLIMIT_DEFAULT                  (_EMU_IF_NFETOVERCURRENTLIMIT_DEFAULT << 17) /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCLPRUNNING                                 (0x1UL << 18)                                /**< LP Mode is Running */
#define _EMU_IF_DCDCLPRUNNING_SHIFT                          18                                           /**< Shift value for EMU_DCDCLPRUNNING */
#define _EMU_IF_DCDCLPRUNNING_MASK                           0x40000UL                                    /**< Bit mask for EMU_DCDCLPRUNNING */
#define _EMU_IF_DCDCLPRUNNING_DEFAULT                        0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCLPRUNNING_DEFAULT                         (_EMU_IF_DCDCLPRUNNING_DEFAULT << 18)        /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCLNRUNNING                                 (0x1UL << 19)                                /**< LN Mode is Running */
#define _EMU_IF_DCDCLNRUNNING_SHIFT                          19                                           /**< Shift value for EMU_DCDCLNRUNNING */
#define _EMU_IF_DCDCLNRUNNING_MASK                           0x80000UL                                    /**< Bit mask for EMU_DCDCLNRUNNING */
#define _EMU_IF_DCDCLNRUNNING_DEFAULT                        0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCLNRUNNING_DEFAULT                         (_EMU_IF_DCDCLNRUNNING_DEFAULT << 19)        /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCINBYPASS                                  (0x1UL << 20)                                /**< DCDC is in Bypass */
#define _EMU_IF_DCDCINBYPASS_SHIFT                           20                                           /**< Shift value for EMU_DCDCINBYPASS */
#define _EMU_IF_DCDCINBYPASS_MASK                            0x100000UL                                   /**< Bit mask for EMU_DCDCINBYPASS */
#define _EMU_IF_DCDCINBYPASS_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_DCDCINBYPASS_DEFAULT                          (_EMU_IF_DCDCINBYPASS_DEFAULT << 20)         /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_EM23WAKEUP                                    (0x1UL << 24)                                /**< Wakeup IRQ From EM2 and EM3 */
#define _EMU_IF_EM23WAKEUP_SHIFT                             24                                           /**< Shift value for EMU_EM23WAKEUP */
#define _EMU_IF_EM23WAKEUP_MASK                              0x1000000UL                                  /**< Bit mask for EMU_EM23WAKEUP */
#define _EMU_IF_EM23WAKEUP_DEFAULT                           0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_EM23WAKEUP_DEFAULT                            (_EMU_IF_EM23WAKEUP_DEFAULT << 24)           /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_VSCALEDONE                                    (0x1UL << 25)                                /**< Voltage Scale Steps Done IRQ */
#define _EMU_IF_VSCALEDONE_SHIFT                             25                                           /**< Shift value for EMU_VSCALEDONE */
#define _EMU_IF_VSCALEDONE_MASK                              0x2000000UL                                  /**< Bit mask for EMU_VSCALEDONE */
#define _EMU_IF_VSCALEDONE_DEFAULT                           0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_VSCALEDONE_DEFAULT                            (_EMU_IF_VSCALEDONE_DEFAULT << 25)           /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_TEMP                                          (0x1UL << 29)                                /**< New Temperature Measurement Valid */
#define _EMU_IF_TEMP_SHIFT                                   29                                           /**< Shift value for EMU_TEMP */
#define _EMU_IF_TEMP_MASK                                    0x20000000UL                                 /**< Bit mask for EMU_TEMP */
#define _EMU_IF_TEMP_DEFAULT                                 0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_TEMP_DEFAULT                                  (_EMU_IF_TEMP_DEFAULT << 29)                 /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_TEMPLOW                                       (0x1UL << 30)                                /**< Temperature Low Limit Reached */
#define _EMU_IF_TEMPLOW_SHIFT                                30                                           /**< Shift value for EMU_TEMPLOW */
#define _EMU_IF_TEMPLOW_MASK                                 0x40000000UL                                 /**< Bit mask for EMU_TEMPLOW */
#define _EMU_IF_TEMPLOW_DEFAULT                              0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_TEMPLOW_DEFAULT                               (_EMU_IF_TEMPLOW_DEFAULT << 30)              /**< Shifted mode DEFAULT for EMU_IF */
#define EMU_IF_TEMPHIGH                                      (0x1UL << 31)                                /**< Temperature High Limit Reached */
#define _EMU_IF_TEMPHIGH_SHIFT                               31                                           /**< Shift value for EMU_TEMPHIGH */
#define _EMU_IF_TEMPHIGH_MASK                                0x80000000UL                                 /**< Bit mask for EMU_TEMPHIGH */
#define _EMU_IF_TEMPHIGH_DEFAULT                             0x00000000UL                                 /**< Mode DEFAULT for EMU_IF */
#define EMU_IF_TEMPHIGH_DEFAULT                              (_EMU_IF_TEMPHIGH_DEFAULT << 31)             /**< Shifted mode DEFAULT for EMU_IF */

/* Bit fields for EMU IFS */
#define _EMU_IFS_RESETVALUE                                  0x00000000UL                                  /**< Default value for EMU_IFS */
#define _EMU_IFS_MASK                                        0xE31FC0FFUL                                  /**< Mask for EMU_IFS */
#define EMU_IFS_VMONAVDDFALL                                 (0x1UL << 0)                                  /**< Set VMONAVDDFALL Interrupt Flag */
#define _EMU_IFS_VMONAVDDFALL_SHIFT                          0                                             /**< Shift value for EMU_VMONAVDDFALL */
#define _EMU_IFS_VMONAVDDFALL_MASK                           0x1UL                                         /**< Bit mask for EMU_VMONAVDDFALL */
#define _EMU_IFS_VMONAVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONAVDDFALL_DEFAULT                         (_EMU_IFS_VMONAVDDFALL_DEFAULT << 0)          /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONAVDDRISE                                 (0x1UL << 1)                                  /**< Set VMONAVDDRISE Interrupt Flag */
#define _EMU_IFS_VMONAVDDRISE_SHIFT                          1                                             /**< Shift value for EMU_VMONAVDDRISE */
#define _EMU_IFS_VMONAVDDRISE_MASK                           0x2UL                                         /**< Bit mask for EMU_VMONAVDDRISE */
#define _EMU_IFS_VMONAVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONAVDDRISE_DEFAULT                         (_EMU_IFS_VMONAVDDRISE_DEFAULT << 1)          /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONALTAVDDFALL                              (0x1UL << 2)                                  /**< Set VMONALTAVDDFALL Interrupt Flag */
#define _EMU_IFS_VMONALTAVDDFALL_SHIFT                       2                                             /**< Shift value for EMU_VMONALTAVDDFALL */
#define _EMU_IFS_VMONALTAVDDFALL_MASK                        0x4UL                                         /**< Bit mask for EMU_VMONALTAVDDFALL */
#define _EMU_IFS_VMONALTAVDDFALL_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONALTAVDDFALL_DEFAULT                      (_EMU_IFS_VMONALTAVDDFALL_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONALTAVDDRISE                              (0x1UL << 3)                                  /**< Set VMONALTAVDDRISE Interrupt Flag */
#define _EMU_IFS_VMONALTAVDDRISE_SHIFT                       3                                             /**< Shift value for EMU_VMONALTAVDDRISE */
#define _EMU_IFS_VMONALTAVDDRISE_MASK                        0x8UL                                         /**< Bit mask for EMU_VMONALTAVDDRISE */
#define _EMU_IFS_VMONALTAVDDRISE_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONALTAVDDRISE_DEFAULT                      (_EMU_IFS_VMONALTAVDDRISE_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONDVDDFALL                                 (0x1UL << 4)                                  /**< Set VMONDVDDFALL Interrupt Flag */
#define _EMU_IFS_VMONDVDDFALL_SHIFT                          4                                             /**< Shift value for EMU_VMONDVDDFALL */
#define _EMU_IFS_VMONDVDDFALL_MASK                           0x10UL                                        /**< Bit mask for EMU_VMONDVDDFALL */
#define _EMU_IFS_VMONDVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONDVDDFALL_DEFAULT                         (_EMU_IFS_VMONDVDDFALL_DEFAULT << 4)          /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONDVDDRISE                                 (0x1UL << 5)                                  /**< Set VMONDVDDRISE Interrupt Flag */
#define _EMU_IFS_VMONDVDDRISE_SHIFT                          5                                             /**< Shift value for EMU_VMONDVDDRISE */
#define _EMU_IFS_VMONDVDDRISE_MASK                           0x20UL                                        /**< Bit mask for EMU_VMONDVDDRISE */
#define _EMU_IFS_VMONDVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONDVDDRISE_DEFAULT                         (_EMU_IFS_VMONDVDDRISE_DEFAULT << 5)          /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONIO0FALL                                  (0x1UL << 6)                                  /**< Set VMONIO0FALL Interrupt Flag */
#define _EMU_IFS_VMONIO0FALL_SHIFT                           6                                             /**< Shift value for EMU_VMONIO0FALL */
#define _EMU_IFS_VMONIO0FALL_MASK                            0x40UL                                        /**< Bit mask for EMU_VMONIO0FALL */
#define _EMU_IFS_VMONIO0FALL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONIO0FALL_DEFAULT                          (_EMU_IFS_VMONIO0FALL_DEFAULT << 6)           /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONIO0RISE                                  (0x1UL << 7)                                  /**< Set VMONIO0RISE Interrupt Flag */
#define _EMU_IFS_VMONIO0RISE_SHIFT                           7                                             /**< Shift value for EMU_VMONIO0RISE */
#define _EMU_IFS_VMONIO0RISE_MASK                            0x80UL                                        /**< Bit mask for EMU_VMONIO0RISE */
#define _EMU_IFS_VMONIO0RISE_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONIO0RISE_DEFAULT                          (_EMU_IFS_VMONIO0RISE_DEFAULT << 7)           /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONFVDDFALL                                 (0x1UL << 14)                                 /**< Set VMONFVDDFALL Interrupt Flag */
#define _EMU_IFS_VMONFVDDFALL_SHIFT                          14                                            /**< Shift value for EMU_VMONFVDDFALL */
#define _EMU_IFS_VMONFVDDFALL_MASK                           0x4000UL                                      /**< Bit mask for EMU_VMONFVDDFALL */
#define _EMU_IFS_VMONFVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONFVDDFALL_DEFAULT                         (_EMU_IFS_VMONFVDDFALL_DEFAULT << 14)         /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONFVDDRISE                                 (0x1UL << 15)                                 /**< Set VMONFVDDRISE Interrupt Flag */
#define _EMU_IFS_VMONFVDDRISE_SHIFT                          15                                            /**< Shift value for EMU_VMONFVDDRISE */
#define _EMU_IFS_VMONFVDDRISE_MASK                           0x8000UL                                      /**< Bit mask for EMU_VMONFVDDRISE */
#define _EMU_IFS_VMONFVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VMONFVDDRISE_DEFAULT                         (_EMU_IFS_VMONFVDDRISE_DEFAULT << 15)         /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_PFETOVERCURRENTLIMIT                         (0x1UL << 16)                                 /**< Set PFETOVERCURRENTLIMIT Interrupt Flag */
#define _EMU_IFS_PFETOVERCURRENTLIMIT_SHIFT                  16                                            /**< Shift value for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IFS_PFETOVERCURRENTLIMIT_MASK                   0x10000UL                                     /**< Bit mask for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IFS_PFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_PFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IFS_PFETOVERCURRENTLIMIT_DEFAULT << 16) /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_NFETOVERCURRENTLIMIT                         (0x1UL << 17)                                 /**< Set NFETOVERCURRENTLIMIT Interrupt Flag */
#define _EMU_IFS_NFETOVERCURRENTLIMIT_SHIFT                  17                                            /**< Shift value for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IFS_NFETOVERCURRENTLIMIT_MASK                   0x20000UL                                     /**< Bit mask for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IFS_NFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_NFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IFS_NFETOVERCURRENTLIMIT_DEFAULT << 17) /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCLPRUNNING                                (0x1UL << 18)                                 /**< Set DCDCLPRUNNING Interrupt Flag */
#define _EMU_IFS_DCDCLPRUNNING_SHIFT                         18                                            /**< Shift value for EMU_DCDCLPRUNNING */
#define _EMU_IFS_DCDCLPRUNNING_MASK                          0x40000UL                                     /**< Bit mask for EMU_DCDCLPRUNNING */
#define _EMU_IFS_DCDCLPRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCLPRUNNING_DEFAULT                        (_EMU_IFS_DCDCLPRUNNING_DEFAULT << 18)        /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCLNRUNNING                                (0x1UL << 19)                                 /**< Set DCDCLNRUNNING Interrupt Flag */
#define _EMU_IFS_DCDCLNRUNNING_SHIFT                         19                                            /**< Shift value for EMU_DCDCLNRUNNING */
#define _EMU_IFS_DCDCLNRUNNING_MASK                          0x80000UL                                     /**< Bit mask for EMU_DCDCLNRUNNING */
#define _EMU_IFS_DCDCLNRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCLNRUNNING_DEFAULT                        (_EMU_IFS_DCDCLNRUNNING_DEFAULT << 19)        /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCINBYPASS                                 (0x1UL << 20)                                 /**< Set DCDCINBYPASS Interrupt Flag */
#define _EMU_IFS_DCDCINBYPASS_SHIFT                          20                                            /**< Shift value for EMU_DCDCINBYPASS */
#define _EMU_IFS_DCDCINBYPASS_MASK                           0x100000UL                                    /**< Bit mask for EMU_DCDCINBYPASS */
#define _EMU_IFS_DCDCINBYPASS_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_DCDCINBYPASS_DEFAULT                         (_EMU_IFS_DCDCINBYPASS_DEFAULT << 20)         /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_EM23WAKEUP                                   (0x1UL << 24)                                 /**< Set EM23WAKEUP Interrupt Flag */
#define _EMU_IFS_EM23WAKEUP_SHIFT                            24                                            /**< Shift value for EMU_EM23WAKEUP */
#define _EMU_IFS_EM23WAKEUP_MASK                             0x1000000UL                                   /**< Bit mask for EMU_EM23WAKEUP */
#define _EMU_IFS_EM23WAKEUP_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_EM23WAKEUP_DEFAULT                           (_EMU_IFS_EM23WAKEUP_DEFAULT << 24)           /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_VSCALEDONE                                   (0x1UL << 25)                                 /**< Set VSCALEDONE Interrupt Flag */
#define _EMU_IFS_VSCALEDONE_SHIFT                            25                                            /**< Shift value for EMU_VSCALEDONE */
#define _EMU_IFS_VSCALEDONE_MASK                             0x2000000UL                                   /**< Bit mask for EMU_VSCALEDONE */
#define _EMU_IFS_VSCALEDONE_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_VSCALEDONE_DEFAULT                           (_EMU_IFS_VSCALEDONE_DEFAULT << 25)           /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMP                                         (0x1UL << 29)                                 /**< Set TEMP Interrupt Flag */
#define _EMU_IFS_TEMP_SHIFT                                  29                                            /**< Shift value for EMU_TEMP */
#define _EMU_IFS_TEMP_MASK                                   0x20000000UL                                  /**< Bit mask for EMU_TEMP */
#define _EMU_IFS_TEMP_DEFAULT                                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMP_DEFAULT                                 (_EMU_IFS_TEMP_DEFAULT << 29)                 /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMPLOW                                      (0x1UL << 30)                                 /**< Set TEMPLOW Interrupt Flag */
#define _EMU_IFS_TEMPLOW_SHIFT                               30                                            /**< Shift value for EMU_TEMPLOW */
#define _EMU_IFS_TEMPLOW_MASK                                0x40000000UL                                  /**< Bit mask for EMU_TEMPLOW */
#define _EMU_IFS_TEMPLOW_DEFAULT                             0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMPLOW_DEFAULT                              (_EMU_IFS_TEMPLOW_DEFAULT << 30)              /**< Shifted mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMPHIGH                                     (0x1UL << 31)                                 /**< Set TEMPHIGH Interrupt Flag */
#define _EMU_IFS_TEMPHIGH_SHIFT                              31                                            /**< Shift value for EMU_TEMPHIGH */
#define _EMU_IFS_TEMPHIGH_MASK                               0x80000000UL                                  /**< Bit mask for EMU_TEMPHIGH */
#define _EMU_IFS_TEMPHIGH_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for EMU_IFS */
#define EMU_IFS_TEMPHIGH_DEFAULT                             (_EMU_IFS_TEMPHIGH_DEFAULT << 31)             /**< Shifted mode DEFAULT for EMU_IFS */

/* Bit fields for EMU IFC */
#define _EMU_IFC_RESETVALUE                                  0x00000000UL                                  /**< Default value for EMU_IFC */
#define _EMU_IFC_MASK                                        0xE31FC0FFUL                                  /**< Mask for EMU_IFC */
#define EMU_IFC_VMONAVDDFALL                                 (0x1UL << 0)                                  /**< Clear VMONAVDDFALL Interrupt Flag */
#define _EMU_IFC_VMONAVDDFALL_SHIFT                          0                                             /**< Shift value for EMU_VMONAVDDFALL */
#define _EMU_IFC_VMONAVDDFALL_MASK                           0x1UL                                         /**< Bit mask for EMU_VMONAVDDFALL */
#define _EMU_IFC_VMONAVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONAVDDFALL_DEFAULT                         (_EMU_IFC_VMONAVDDFALL_DEFAULT << 0)          /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONAVDDRISE                                 (0x1UL << 1)                                  /**< Clear VMONAVDDRISE Interrupt Flag */
#define _EMU_IFC_VMONAVDDRISE_SHIFT                          1                                             /**< Shift value for EMU_VMONAVDDRISE */
#define _EMU_IFC_VMONAVDDRISE_MASK                           0x2UL                                         /**< Bit mask for EMU_VMONAVDDRISE */
#define _EMU_IFC_VMONAVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONAVDDRISE_DEFAULT                         (_EMU_IFC_VMONAVDDRISE_DEFAULT << 1)          /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONALTAVDDFALL                              (0x1UL << 2)                                  /**< Clear VMONALTAVDDFALL Interrupt Flag */
#define _EMU_IFC_VMONALTAVDDFALL_SHIFT                       2                                             /**< Shift value for EMU_VMONALTAVDDFALL */
#define _EMU_IFC_VMONALTAVDDFALL_MASK                        0x4UL                                         /**< Bit mask for EMU_VMONALTAVDDFALL */
#define _EMU_IFC_VMONALTAVDDFALL_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONALTAVDDFALL_DEFAULT                      (_EMU_IFC_VMONALTAVDDFALL_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONALTAVDDRISE                              (0x1UL << 3)                                  /**< Clear VMONALTAVDDRISE Interrupt Flag */
#define _EMU_IFC_VMONALTAVDDRISE_SHIFT                       3                                             /**< Shift value for EMU_VMONALTAVDDRISE */
#define _EMU_IFC_VMONALTAVDDRISE_MASK                        0x8UL                                         /**< Bit mask for EMU_VMONALTAVDDRISE */
#define _EMU_IFC_VMONALTAVDDRISE_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONALTAVDDRISE_DEFAULT                      (_EMU_IFC_VMONALTAVDDRISE_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONDVDDFALL                                 (0x1UL << 4)                                  /**< Clear VMONDVDDFALL Interrupt Flag */
#define _EMU_IFC_VMONDVDDFALL_SHIFT                          4                                             /**< Shift value for EMU_VMONDVDDFALL */
#define _EMU_IFC_VMONDVDDFALL_MASK                           0x10UL                                        /**< Bit mask for EMU_VMONDVDDFALL */
#define _EMU_IFC_VMONDVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONDVDDFALL_DEFAULT                         (_EMU_IFC_VMONDVDDFALL_DEFAULT << 4)          /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONDVDDRISE                                 (0x1UL << 5)                                  /**< Clear VMONDVDDRISE Interrupt Flag */
#define _EMU_IFC_VMONDVDDRISE_SHIFT                          5                                             /**< Shift value for EMU_VMONDVDDRISE */
#define _EMU_IFC_VMONDVDDRISE_MASK                           0x20UL                                        /**< Bit mask for EMU_VMONDVDDRISE */
#define _EMU_IFC_VMONDVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONDVDDRISE_DEFAULT                         (_EMU_IFC_VMONDVDDRISE_DEFAULT << 5)          /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONIO0FALL                                  (0x1UL << 6)                                  /**< Clear VMONIO0FALL Interrupt Flag */
#define _EMU_IFC_VMONIO0FALL_SHIFT                           6                                             /**< Shift value for EMU_VMONIO0FALL */
#define _EMU_IFC_VMONIO0FALL_MASK                            0x40UL                                        /**< Bit mask for EMU_VMONIO0FALL */
#define _EMU_IFC_VMONIO0FALL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONIO0FALL_DEFAULT                          (_EMU_IFC_VMONIO0FALL_DEFAULT << 6)           /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONIO0RISE                                  (0x1UL << 7)                                  /**< Clear VMONIO0RISE Interrupt Flag */
#define _EMU_IFC_VMONIO0RISE_SHIFT                           7                                             /**< Shift value for EMU_VMONIO0RISE */
#define _EMU_IFC_VMONIO0RISE_MASK                            0x80UL                                        /**< Bit mask for EMU_VMONIO0RISE */
#define _EMU_IFC_VMONIO0RISE_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONIO0RISE_DEFAULT                          (_EMU_IFC_VMONIO0RISE_DEFAULT << 7)           /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONFVDDFALL                                 (0x1UL << 14)                                 /**< Clear VMONFVDDFALL Interrupt Flag */
#define _EMU_IFC_VMONFVDDFALL_SHIFT                          14                                            /**< Shift value for EMU_VMONFVDDFALL */
#define _EMU_IFC_VMONFVDDFALL_MASK                           0x4000UL                                      /**< Bit mask for EMU_VMONFVDDFALL */
#define _EMU_IFC_VMONFVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONFVDDFALL_DEFAULT                         (_EMU_IFC_VMONFVDDFALL_DEFAULT << 14)         /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONFVDDRISE                                 (0x1UL << 15)                                 /**< Clear VMONFVDDRISE Interrupt Flag */
#define _EMU_IFC_VMONFVDDRISE_SHIFT                          15                                            /**< Shift value for EMU_VMONFVDDRISE */
#define _EMU_IFC_VMONFVDDRISE_MASK                           0x8000UL                                      /**< Bit mask for EMU_VMONFVDDRISE */
#define _EMU_IFC_VMONFVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VMONFVDDRISE_DEFAULT                         (_EMU_IFC_VMONFVDDRISE_DEFAULT << 15)         /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_PFETOVERCURRENTLIMIT                         (0x1UL << 16)                                 /**< Clear PFETOVERCURRENTLIMIT Interrupt Flag */
#define _EMU_IFC_PFETOVERCURRENTLIMIT_SHIFT                  16                                            /**< Shift value for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IFC_PFETOVERCURRENTLIMIT_MASK                   0x10000UL                                     /**< Bit mask for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IFC_PFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_PFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IFC_PFETOVERCURRENTLIMIT_DEFAULT << 16) /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_NFETOVERCURRENTLIMIT                         (0x1UL << 17)                                 /**< Clear NFETOVERCURRENTLIMIT Interrupt Flag */
#define _EMU_IFC_NFETOVERCURRENTLIMIT_SHIFT                  17                                            /**< Shift value for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IFC_NFETOVERCURRENTLIMIT_MASK                   0x20000UL                                     /**< Bit mask for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IFC_NFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_NFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IFC_NFETOVERCURRENTLIMIT_DEFAULT << 17) /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCLPRUNNING                                (0x1UL << 18)                                 /**< Clear DCDCLPRUNNING Interrupt Flag */
#define _EMU_IFC_DCDCLPRUNNING_SHIFT                         18                                            /**< Shift value for EMU_DCDCLPRUNNING */
#define _EMU_IFC_DCDCLPRUNNING_MASK                          0x40000UL                                     /**< Bit mask for EMU_DCDCLPRUNNING */
#define _EMU_IFC_DCDCLPRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCLPRUNNING_DEFAULT                        (_EMU_IFC_DCDCLPRUNNING_DEFAULT << 18)        /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCLNRUNNING                                (0x1UL << 19)                                 /**< Clear DCDCLNRUNNING Interrupt Flag */
#define _EMU_IFC_DCDCLNRUNNING_SHIFT                         19                                            /**< Shift value for EMU_DCDCLNRUNNING */
#define _EMU_IFC_DCDCLNRUNNING_MASK                          0x80000UL                                     /**< Bit mask for EMU_DCDCLNRUNNING */
#define _EMU_IFC_DCDCLNRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCLNRUNNING_DEFAULT                        (_EMU_IFC_DCDCLNRUNNING_DEFAULT << 19)        /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCINBYPASS                                 (0x1UL << 20)                                 /**< Clear DCDCINBYPASS Interrupt Flag */
#define _EMU_IFC_DCDCINBYPASS_SHIFT                          20                                            /**< Shift value for EMU_DCDCINBYPASS */
#define _EMU_IFC_DCDCINBYPASS_MASK                           0x100000UL                                    /**< Bit mask for EMU_DCDCINBYPASS */
#define _EMU_IFC_DCDCINBYPASS_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_DCDCINBYPASS_DEFAULT                         (_EMU_IFC_DCDCINBYPASS_DEFAULT << 20)         /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_EM23WAKEUP                                   (0x1UL << 24)                                 /**< Clear EM23WAKEUP Interrupt Flag */
#define _EMU_IFC_EM23WAKEUP_SHIFT                            24                                            /**< Shift value for EMU_EM23WAKEUP */
#define _EMU_IFC_EM23WAKEUP_MASK                             0x1000000UL                                   /**< Bit mask for EMU_EM23WAKEUP */
#define _EMU_IFC_EM23WAKEUP_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_EM23WAKEUP_DEFAULT                           (_EMU_IFC_EM23WAKEUP_DEFAULT << 24)           /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_VSCALEDONE                                   (0x1UL << 25)                                 /**< Clear VSCALEDONE Interrupt Flag */
#define _EMU_IFC_VSCALEDONE_SHIFT                            25                                            /**< Shift value for EMU_VSCALEDONE */
#define _EMU_IFC_VSCALEDONE_MASK                             0x2000000UL                                   /**< Bit mask for EMU_VSCALEDONE */
#define _EMU_IFC_VSCALEDONE_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_VSCALEDONE_DEFAULT                           (_EMU_IFC_VSCALEDONE_DEFAULT << 25)           /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMP                                         (0x1UL << 29)                                 /**< Clear TEMP Interrupt Flag */
#define _EMU_IFC_TEMP_SHIFT                                  29                                            /**< Shift value for EMU_TEMP */
#define _EMU_IFC_TEMP_MASK                                   0x20000000UL                                  /**< Bit mask for EMU_TEMP */
#define _EMU_IFC_TEMP_DEFAULT                                0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMP_DEFAULT                                 (_EMU_IFC_TEMP_DEFAULT << 29)                 /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMPLOW                                      (0x1UL << 30)                                 /**< Clear TEMPLOW Interrupt Flag */
#define _EMU_IFC_TEMPLOW_SHIFT                               30                                            /**< Shift value for EMU_TEMPLOW */
#define _EMU_IFC_TEMPLOW_MASK                                0x40000000UL                                  /**< Bit mask for EMU_TEMPLOW */
#define _EMU_IFC_TEMPLOW_DEFAULT                             0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMPLOW_DEFAULT                              (_EMU_IFC_TEMPLOW_DEFAULT << 30)              /**< Shifted mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMPHIGH                                     (0x1UL << 31)                                 /**< Clear TEMPHIGH Interrupt Flag */
#define _EMU_IFC_TEMPHIGH_SHIFT                              31                                            /**< Shift value for EMU_TEMPHIGH */
#define _EMU_IFC_TEMPHIGH_MASK                               0x80000000UL                                  /**< Bit mask for EMU_TEMPHIGH */
#define _EMU_IFC_TEMPHIGH_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for EMU_IFC */
#define EMU_IFC_TEMPHIGH_DEFAULT                             (_EMU_IFC_TEMPHIGH_DEFAULT << 31)             /**< Shifted mode DEFAULT for EMU_IFC */

/* Bit fields for EMU IEN */
#define _EMU_IEN_RESETVALUE                                  0x00000000UL                                  /**< Default value for EMU_IEN */
#define _EMU_IEN_MASK                                        0xE31FC0FFUL                                  /**< Mask for EMU_IEN */
#define EMU_IEN_VMONAVDDFALL                                 (0x1UL << 0)                                  /**< VMONAVDDFALL Interrupt Enable */
#define _EMU_IEN_VMONAVDDFALL_SHIFT                          0                                             /**< Shift value for EMU_VMONAVDDFALL */
#define _EMU_IEN_VMONAVDDFALL_MASK                           0x1UL                                         /**< Bit mask for EMU_VMONAVDDFALL */
#define _EMU_IEN_VMONAVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONAVDDFALL_DEFAULT                         (_EMU_IEN_VMONAVDDFALL_DEFAULT << 0)          /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONAVDDRISE                                 (0x1UL << 1)                                  /**< VMONAVDDRISE Interrupt Enable */
#define _EMU_IEN_VMONAVDDRISE_SHIFT                          1                                             /**< Shift value for EMU_VMONAVDDRISE */
#define _EMU_IEN_VMONAVDDRISE_MASK                           0x2UL                                         /**< Bit mask for EMU_VMONAVDDRISE */
#define _EMU_IEN_VMONAVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONAVDDRISE_DEFAULT                         (_EMU_IEN_VMONAVDDRISE_DEFAULT << 1)          /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONALTAVDDFALL                              (0x1UL << 2)                                  /**< VMONALTAVDDFALL Interrupt Enable */
#define _EMU_IEN_VMONALTAVDDFALL_SHIFT                       2                                             /**< Shift value for EMU_VMONALTAVDDFALL */
#define _EMU_IEN_VMONALTAVDDFALL_MASK                        0x4UL                                         /**< Bit mask for EMU_VMONALTAVDDFALL */
#define _EMU_IEN_VMONALTAVDDFALL_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONALTAVDDFALL_DEFAULT                      (_EMU_IEN_VMONALTAVDDFALL_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONALTAVDDRISE                              (0x1UL << 3)                                  /**< VMONALTAVDDRISE Interrupt Enable */
#define _EMU_IEN_VMONALTAVDDRISE_SHIFT                       3                                             /**< Shift value for EMU_VMONALTAVDDRISE */
#define _EMU_IEN_VMONALTAVDDRISE_MASK                        0x8UL                                         /**< Bit mask for EMU_VMONALTAVDDRISE */
#define _EMU_IEN_VMONALTAVDDRISE_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONALTAVDDRISE_DEFAULT                      (_EMU_IEN_VMONALTAVDDRISE_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONDVDDFALL                                 (0x1UL << 4)                                  /**< VMONDVDDFALL Interrupt Enable */
#define _EMU_IEN_VMONDVDDFALL_SHIFT                          4                                             /**< Shift value for EMU_VMONDVDDFALL */
#define _EMU_IEN_VMONDVDDFALL_MASK                           0x10UL                                        /**< Bit mask for EMU_VMONDVDDFALL */
#define _EMU_IEN_VMONDVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONDVDDFALL_DEFAULT                         (_EMU_IEN_VMONDVDDFALL_DEFAULT << 4)          /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONDVDDRISE                                 (0x1UL << 5)                                  /**< VMONDVDDRISE Interrupt Enable */
#define _EMU_IEN_VMONDVDDRISE_SHIFT                          5                                             /**< Shift value for EMU_VMONDVDDRISE */
#define _EMU_IEN_VMONDVDDRISE_MASK                           0x20UL                                        /**< Bit mask for EMU_VMONDVDDRISE */
#define _EMU_IEN_VMONDVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONDVDDRISE_DEFAULT                         (_EMU_IEN_VMONDVDDRISE_DEFAULT << 5)          /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONIO0FALL                                  (0x1UL << 6)                                  /**< VMONIO0FALL Interrupt Enable */
#define _EMU_IEN_VMONIO0FALL_SHIFT                           6                                             /**< Shift value for EMU_VMONIO0FALL */
#define _EMU_IEN_VMONIO0FALL_MASK                            0x40UL                                        /**< Bit mask for EMU_VMONIO0FALL */
#define _EMU_IEN_VMONIO0FALL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONIO0FALL_DEFAULT                          (_EMU_IEN_VMONIO0FALL_DEFAULT << 6)           /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONIO0RISE                                  (0x1UL << 7)                                  /**< VMONIO0RISE Interrupt Enable */
#define _EMU_IEN_VMONIO0RISE_SHIFT                           7                                             /**< Shift value for EMU_VMONIO0RISE */
#define _EMU_IEN_VMONIO0RISE_MASK                            0x80UL                                        /**< Bit mask for EMU_VMONIO0RISE */
#define _EMU_IEN_VMONIO0RISE_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONIO0RISE_DEFAULT                          (_EMU_IEN_VMONIO0RISE_DEFAULT << 7)           /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONFVDDFALL                                 (0x1UL << 14)                                 /**< VMONFVDDFALL Interrupt Enable */
#define _EMU_IEN_VMONFVDDFALL_SHIFT                          14                                            /**< Shift value for EMU_VMONFVDDFALL */
#define _EMU_IEN_VMONFVDDFALL_MASK                           0x4000UL                                      /**< Bit mask for EMU_VMONFVDDFALL */
#define _EMU_IEN_VMONFVDDFALL_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONFVDDFALL_DEFAULT                         (_EMU_IEN_VMONFVDDFALL_DEFAULT << 14)         /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONFVDDRISE                                 (0x1UL << 15)                                 /**< VMONFVDDRISE Interrupt Enable */
#define _EMU_IEN_VMONFVDDRISE_SHIFT                          15                                            /**< Shift value for EMU_VMONFVDDRISE */
#define _EMU_IEN_VMONFVDDRISE_MASK                           0x8000UL                                      /**< Bit mask for EMU_VMONFVDDRISE */
#define _EMU_IEN_VMONFVDDRISE_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VMONFVDDRISE_DEFAULT                         (_EMU_IEN_VMONFVDDRISE_DEFAULT << 15)         /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_PFETOVERCURRENTLIMIT                         (0x1UL << 16)                                 /**< PFETOVERCURRENTLIMIT Interrupt Enable */
#define _EMU_IEN_PFETOVERCURRENTLIMIT_SHIFT                  16                                            /**< Shift value for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IEN_PFETOVERCURRENTLIMIT_MASK                   0x10000UL                                     /**< Bit mask for EMU_PFETOVERCURRENTLIMIT */
#define _EMU_IEN_PFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_PFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IEN_PFETOVERCURRENTLIMIT_DEFAULT << 16) /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_NFETOVERCURRENTLIMIT                         (0x1UL << 17)                                 /**< NFETOVERCURRENTLIMIT Interrupt Enable */
#define _EMU_IEN_NFETOVERCURRENTLIMIT_SHIFT                  17                                            /**< Shift value for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IEN_NFETOVERCURRENTLIMIT_MASK                   0x20000UL                                     /**< Bit mask for EMU_NFETOVERCURRENTLIMIT */
#define _EMU_IEN_NFETOVERCURRENTLIMIT_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_NFETOVERCURRENTLIMIT_DEFAULT                 (_EMU_IEN_NFETOVERCURRENTLIMIT_DEFAULT << 17) /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCLPRUNNING                                (0x1UL << 18)                                 /**< DCDCLPRUNNING Interrupt Enable */
#define _EMU_IEN_DCDCLPRUNNING_SHIFT                         18                                            /**< Shift value for EMU_DCDCLPRUNNING */
#define _EMU_IEN_DCDCLPRUNNING_MASK                          0x40000UL                                     /**< Bit mask for EMU_DCDCLPRUNNING */
#define _EMU_IEN_DCDCLPRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCLPRUNNING_DEFAULT                        (_EMU_IEN_DCDCLPRUNNING_DEFAULT << 18)        /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCLNRUNNING                                (0x1UL << 19)                                 /**< DCDCLNRUNNING Interrupt Enable */
#define _EMU_IEN_DCDCLNRUNNING_SHIFT                         19                                            /**< Shift value for EMU_DCDCLNRUNNING */
#define _EMU_IEN_DCDCLNRUNNING_MASK                          0x80000UL                                     /**< Bit mask for EMU_DCDCLNRUNNING */
#define _EMU_IEN_DCDCLNRUNNING_DEFAULT                       0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCLNRUNNING_DEFAULT                        (_EMU_IEN_DCDCLNRUNNING_DEFAULT << 19)        /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCINBYPASS                                 (0x1UL << 20)                                 /**< DCDCINBYPASS Interrupt Enable */
#define _EMU_IEN_DCDCINBYPASS_SHIFT                          20                                            /**< Shift value for EMU_DCDCINBYPASS */
#define _EMU_IEN_DCDCINBYPASS_MASK                           0x100000UL                                    /**< Bit mask for EMU_DCDCINBYPASS */
#define _EMU_IEN_DCDCINBYPASS_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_DCDCINBYPASS_DEFAULT                         (_EMU_IEN_DCDCINBYPASS_DEFAULT << 20)         /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_EM23WAKEUP                                   (0x1UL << 24)                                 /**< EM23WAKEUP Interrupt Enable */
#define _EMU_IEN_EM23WAKEUP_SHIFT                            24                                            /**< Shift value for EMU_EM23WAKEUP */
#define _EMU_IEN_EM23WAKEUP_MASK                             0x1000000UL                                   /**< Bit mask for EMU_EM23WAKEUP */
#define _EMU_IEN_EM23WAKEUP_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_EM23WAKEUP_DEFAULT                           (_EMU_IEN_EM23WAKEUP_DEFAULT << 24)           /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_VSCALEDONE                                   (0x1UL << 25)                                 /**< VSCALEDONE Interrupt Enable */
#define _EMU_IEN_VSCALEDONE_SHIFT                            25                                            /**< Shift value for EMU_VSCALEDONE */
#define _EMU_IEN_VSCALEDONE_MASK                             0x2000000UL                                   /**< Bit mask for EMU_VSCALEDONE */
#define _EMU_IEN_VSCALEDONE_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_VSCALEDONE_DEFAULT                           (_EMU_IEN_VSCALEDONE_DEFAULT << 25)           /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMP                                         (0x1UL << 29)                                 /**< TEMP Interrupt Enable */
#define _EMU_IEN_TEMP_SHIFT                                  29                                            /**< Shift value for EMU_TEMP */
#define _EMU_IEN_TEMP_MASK                                   0x20000000UL                                  /**< Bit mask for EMU_TEMP */
#define _EMU_IEN_TEMP_DEFAULT                                0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMP_DEFAULT                                 (_EMU_IEN_TEMP_DEFAULT << 29)                 /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMPLOW                                      (0x1UL << 30)                                 /**< TEMPLOW Interrupt Enable */
#define _EMU_IEN_TEMPLOW_SHIFT                               30                                            /**< Shift value for EMU_TEMPLOW */
#define _EMU_IEN_TEMPLOW_MASK                                0x40000000UL                                  /**< Bit mask for EMU_TEMPLOW */
#define _EMU_IEN_TEMPLOW_DEFAULT                             0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMPLOW_DEFAULT                              (_EMU_IEN_TEMPLOW_DEFAULT << 30)              /**< Shifted mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMPHIGH                                     (0x1UL << 31)                                 /**< TEMPHIGH Interrupt Enable */
#define _EMU_IEN_TEMPHIGH_SHIFT                              31                                            /**< Shift value for EMU_TEMPHIGH */
#define _EMU_IEN_TEMPHIGH_MASK                               0x80000000UL                                  /**< Bit mask for EMU_TEMPHIGH */
#define _EMU_IEN_TEMPHIGH_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for EMU_IEN */
#define EMU_IEN_TEMPHIGH_DEFAULT                             (_EMU_IEN_TEMPHIGH_DEFAULT << 31)             /**< Shifted mode DEFAULT for EMU_IEN */

/* Bit fields for EMU PWRLOCK */
#define _EMU_PWRLOCK_RESETVALUE                              0x00000000UL                         /**< Default value for EMU_PWRLOCK */
#define _EMU_PWRLOCK_MASK                                    0x0000FFFFUL                         /**< Mask for EMU_PWRLOCK */
#define _EMU_PWRLOCK_LOCKKEY_SHIFT                           0                                    /**< Shift value for EMU_LOCKKEY */
#define _EMU_PWRLOCK_LOCKKEY_MASK                            0xFFFFUL                             /**< Bit mask for EMU_LOCKKEY */
#define _EMU_PWRLOCK_LOCKKEY_DEFAULT                         0x00000000UL                         /**< Mode DEFAULT for EMU_PWRLOCK */
#define _EMU_PWRLOCK_LOCKKEY_LOCK                            0x00000000UL                         /**< Mode LOCK for EMU_PWRLOCK */
#define _EMU_PWRLOCK_LOCKKEY_UNLOCKED                        0x00000000UL                         /**< Mode UNLOCKED for EMU_PWRLOCK */
#define _EMU_PWRLOCK_LOCKKEY_LOCKED                          0x00000001UL                         /**< Mode LOCKED for EMU_PWRLOCK */
#define _EMU_PWRLOCK_LOCKKEY_UNLOCK                          0x0000ADE8UL                         /**< Mode UNLOCK for EMU_PWRLOCK */
#define EMU_PWRLOCK_LOCKKEY_DEFAULT                          (_EMU_PWRLOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_PWRLOCK */
#define EMU_PWRLOCK_LOCKKEY_LOCK                             (_EMU_PWRLOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for EMU_PWRLOCK */
#define EMU_PWRLOCK_LOCKKEY_UNLOCKED                         (_EMU_PWRLOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for EMU_PWRLOCK */
#define EMU_PWRLOCK_LOCKKEY_LOCKED                           (_EMU_PWRLOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for EMU_PWRLOCK */
#define EMU_PWRLOCK_LOCKKEY_UNLOCK                           (_EMU_PWRLOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for EMU_PWRLOCK */

/* Bit fields for EMU PWRCTRL */
#define _EMU_PWRCTRL_RESETVALUE                              0x00000000UL                                    /**< Default value for EMU_PWRCTRL */
#define _EMU_PWRCTRL_MASK                                    0x00002420UL                                    /**< Mask for EMU_PWRCTRL */
#define EMU_PWRCTRL_ANASW                                    (0x1UL << 5)                                    /**< Analog Switch Selection */
#define _EMU_PWRCTRL_ANASW_SHIFT                             5                                               /**< Shift value for EMU_ANASW */
#define _EMU_PWRCTRL_ANASW_MASK                              0x20UL                                          /**< Bit mask for EMU_ANASW */
#define _EMU_PWRCTRL_ANASW_DEFAULT                           0x00000000UL                                    /**< Mode DEFAULT for EMU_PWRCTRL */
#define _EMU_PWRCTRL_ANASW_AVDD                              0x00000000UL                                    /**< Mode AVDD for EMU_PWRCTRL */
#define _EMU_PWRCTRL_ANASW_DVDD                              0x00000001UL                                    /**< Mode DVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_ANASW_DEFAULT                            (_EMU_PWRCTRL_ANASW_DEFAULT << 5)               /**< Shifted mode DEFAULT for EMU_PWRCTRL */
#define EMU_PWRCTRL_ANASW_AVDD                               (_EMU_PWRCTRL_ANASW_AVDD << 5)                  /**< Shifted mode AVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_ANASW_DVDD                               (_EMU_PWRCTRL_ANASW_DVDD << 5)                  /**< Shifted mode DVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_REGPWRSEL                                (0x1UL << 10)                                   /**< This Field Selects the Input Supply Pin for the Digital LDO */
#define _EMU_PWRCTRL_REGPWRSEL_SHIFT                         10                                              /**< Shift value for EMU_REGPWRSEL */
#define _EMU_PWRCTRL_REGPWRSEL_MASK                          0x400UL                                         /**< Bit mask for EMU_REGPWRSEL */
#define _EMU_PWRCTRL_REGPWRSEL_DEFAULT                       0x00000000UL                                    /**< Mode DEFAULT for EMU_PWRCTRL */
#define _EMU_PWRCTRL_REGPWRSEL_AVDD                          0x00000000UL                                    /**< Mode AVDD for EMU_PWRCTRL */
#define _EMU_PWRCTRL_REGPWRSEL_DVDD                          0x00000001UL                                    /**< Mode DVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_REGPWRSEL_DEFAULT                        (_EMU_PWRCTRL_REGPWRSEL_DEFAULT << 10)          /**< Shifted mode DEFAULT for EMU_PWRCTRL */
#define EMU_PWRCTRL_REGPWRSEL_AVDD                           (_EMU_PWRCTRL_REGPWRSEL_AVDD << 10)             /**< Shifted mode AVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_REGPWRSEL_DVDD                           (_EMU_PWRCTRL_REGPWRSEL_DVDD << 10)             /**< Shifted mode DVDD for EMU_PWRCTRL */
#define EMU_PWRCTRL_IMMEDIATEPWRSWITCH                       (0x1UL << 13)                                   /**< Allows Immediate Switching of ANASW and REGPWRSEL Bitfields */
#define _EMU_PWRCTRL_IMMEDIATEPWRSWITCH_SHIFT                13                                              /**< Shift value for EMU_IMMEDIATEPWRSWITCH */
#define _EMU_PWRCTRL_IMMEDIATEPWRSWITCH_MASK                 0x2000UL                                        /**< Bit mask for EMU_IMMEDIATEPWRSWITCH */
#define _EMU_PWRCTRL_IMMEDIATEPWRSWITCH_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for EMU_PWRCTRL */
#define EMU_PWRCTRL_IMMEDIATEPWRSWITCH_DEFAULT               (_EMU_PWRCTRL_IMMEDIATEPWRSWITCH_DEFAULT << 13) /**< Shifted mode DEFAULT for EMU_PWRCTRL */

/* Bit fields for EMU DCDCCTRL */
#define _EMU_DCDCCTRL_RESETVALUE                             0x00000033UL                                   /**< Default value for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_MASK                                   0x00000033UL                                   /**< Mask for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODE_SHIFT                         0                                              /**< Shift value for EMU_DCDCMODE */
#define _EMU_DCDCCTRL_DCDCMODE_MASK                          0x3UL                                          /**< Bit mask for EMU_DCDCMODE */
#define _EMU_DCDCCTRL_DCDCMODE_BYPASS                        0x00000000UL                                   /**< Mode BYPASS for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODE_LOWNOISE                      0x00000001UL                                   /**< Mode LOWNOISE for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODE_LOWPOWER                      0x00000002UL                                   /**< Mode LOWPOWER for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODE_DEFAULT                       0x00000003UL                                   /**< Mode DEFAULT for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODE_OFF                           0x00000003UL                                   /**< Mode OFF for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODE_BYPASS                         (_EMU_DCDCCTRL_DCDCMODE_BYPASS << 0)           /**< Shifted mode BYPASS for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODE_LOWNOISE                       (_EMU_DCDCCTRL_DCDCMODE_LOWNOISE << 0)         /**< Shifted mode LOWNOISE for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODE_LOWPOWER                       (_EMU_DCDCCTRL_DCDCMODE_LOWPOWER << 0)         /**< Shifted mode LOWPOWER for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODE_DEFAULT                        (_EMU_DCDCCTRL_DCDCMODE_DEFAULT << 0)          /**< Shifted mode DEFAULT for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODE_OFF                            (_EMU_DCDCCTRL_DCDCMODE_OFF << 0)              /**< Shifted mode OFF for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM23                            (0x1UL << 4)                                   /**< DCDC Mode EM23 */
#define _EMU_DCDCCTRL_DCDCMODEEM23_SHIFT                     4                                              /**< Shift value for EMU_DCDCMODEEM23 */
#define _EMU_DCDCCTRL_DCDCMODEEM23_MASK                      0x10UL                                         /**< Bit mask for EMU_DCDCMODEEM23 */
#define _EMU_DCDCCTRL_DCDCMODEEM23_EM23SW                    0x00000000UL                                   /**< Mode EM23SW for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODEEM23_DEFAULT                   0x00000001UL                                   /**< Mode DEFAULT for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODEEM23_EM23LOWPOWER              0x00000001UL                                   /**< Mode EM23LOWPOWER for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM23_EM23SW                     (_EMU_DCDCCTRL_DCDCMODEEM23_EM23SW << 4)       /**< Shifted mode EM23SW for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM23_DEFAULT                    (_EMU_DCDCCTRL_DCDCMODEEM23_DEFAULT << 4)      /**< Shifted mode DEFAULT for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM23_EM23LOWPOWER               (_EMU_DCDCCTRL_DCDCMODEEM23_EM23LOWPOWER << 4) /**< Shifted mode EM23LOWPOWER for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM4                             (0x1UL << 5)                                   /**< DCDC Mode EM4H */
#define _EMU_DCDCCTRL_DCDCMODEEM4_SHIFT                      5                                              /**< Shift value for EMU_DCDCMODEEM4 */
#define _EMU_DCDCCTRL_DCDCMODEEM4_MASK                       0x20UL                                         /**< Bit mask for EMU_DCDCMODEEM4 */
#define _EMU_DCDCCTRL_DCDCMODEEM4_EM4SW                      0x00000000UL                                   /**< Mode EM4SW for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODEEM4_DEFAULT                    0x00000001UL                                   /**< Mode DEFAULT for EMU_DCDCCTRL */
#define _EMU_DCDCCTRL_DCDCMODEEM4_EM4LOWPOWER                0x00000001UL                                   /**< Mode EM4LOWPOWER for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM4_EM4SW                       (_EMU_DCDCCTRL_DCDCMODEEM4_EM4SW << 5)         /**< Shifted mode EM4SW for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM4_DEFAULT                     (_EMU_DCDCCTRL_DCDCMODEEM4_DEFAULT << 5)       /**< Shifted mode DEFAULT for EMU_DCDCCTRL */
#define EMU_DCDCCTRL_DCDCMODEEM4_EM4LOWPOWER                 (_EMU_DCDCCTRL_DCDCMODEEM4_EM4LOWPOWER << 5)   /**< Shifted mode EM4LOWPOWER for EMU_DCDCCTRL */

/* Bit fields for EMU DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_RESETVALUE                         0x03107706UL                                      /**< Default value for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_MASK                               0x377FFF27UL                                      /**< Mask for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LNFORCECCM                          (0x1UL << 0)                                      /**< Force DCDC Into CCM Mode in Low Noise Operation */
#define _EMU_DCDCMISCCTRL_LNFORCECCM_SHIFT                   0                                                 /**< Shift value for EMU_LNFORCECCM */
#define _EMU_DCDCMISCCTRL_LNFORCECCM_MASK                    0x1UL                                             /**< Bit mask for EMU_LNFORCECCM */
#define _EMU_DCDCMISCCTRL_LNFORCECCM_DEFAULT                 0x00000000UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LNFORCECCM_DEFAULT                  (_EMU_DCDCMISCCTRL_LNFORCECCM_DEFAULT << 0)       /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPHYSDIS                         (0x1UL << 1)                                      /**< Disable LP Mode Hysteresis in the State Machine Control */
#define _EMU_DCDCMISCCTRL_LPCMPHYSDIS_SHIFT                  1                                                 /**< Shift value for EMU_LPCMPHYSDIS */
#define _EMU_DCDCMISCCTRL_LPCMPHYSDIS_MASK                   0x2UL                                             /**< Bit mask for EMU_LPCMPHYSDIS */
#define _EMU_DCDCMISCCTRL_LPCMPHYSDIS_DEFAULT                0x00000001UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPHYSDIS_DEFAULT                 (_EMU_DCDCMISCCTRL_LPCMPHYSDIS_DEFAULT << 1)      /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPHYSHI                          (0x1UL << 2)                                      /**< Comparator Threshold on the High Side */
#define _EMU_DCDCMISCCTRL_LPCMPHYSHI_SHIFT                   2                                                 /**< Shift value for EMU_LPCMPHYSHI */
#define _EMU_DCDCMISCCTRL_LPCMPHYSHI_MASK                    0x4UL                                             /**< Bit mask for EMU_LPCMPHYSHI */
#define _EMU_DCDCMISCCTRL_LPCMPHYSHI_DEFAULT                 0x00000001UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPHYSHI_DEFAULT                  (_EMU_DCDCMISCCTRL_LPCMPHYSHI_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LNFORCECCMIMM                       (0x1UL << 5)                                      /**< Force DCDC Into CCM Mode Immediately, Based on LNFORCECCM */
#define _EMU_DCDCMISCCTRL_LNFORCECCMIMM_SHIFT                5                                                 /**< Shift value for EMU_LNFORCECCMIMM */
#define _EMU_DCDCMISCCTRL_LNFORCECCMIMM_MASK                 0x20UL                                            /**< Bit mask for EMU_LNFORCECCMIMM */
#define _EMU_DCDCMISCCTRL_LNFORCECCMIMM_DEFAULT              0x00000000UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LNFORCECCMIMM_DEFAULT               (_EMU_DCDCMISCCTRL_LNFORCECCMIMM_DEFAULT << 5)    /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_PFETCNT_SHIFT                      8                                                 /**< Shift value for EMU_PFETCNT */
#define _EMU_DCDCMISCCTRL_PFETCNT_MASK                       0xF00UL                                           /**< Bit mask for EMU_PFETCNT */
#define _EMU_DCDCMISCCTRL_PFETCNT_DEFAULT                    0x00000007UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_PFETCNT_DEFAULT                     (_EMU_DCDCMISCCTRL_PFETCNT_DEFAULT << 8)          /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_NFETCNT_SHIFT                      12                                                /**< Shift value for EMU_NFETCNT */
#define _EMU_DCDCMISCCTRL_NFETCNT_MASK                       0xF000UL                                          /**< Bit mask for EMU_NFETCNT */
#define _EMU_DCDCMISCCTRL_NFETCNT_DEFAULT                    0x00000007UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_NFETCNT_DEFAULT                     (_EMU_DCDCMISCCTRL_NFETCNT_DEFAULT << 12)         /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_BYPLIMSEL_SHIFT                    16                                                /**< Shift value for EMU_BYPLIMSEL */
#define _EMU_DCDCMISCCTRL_BYPLIMSEL_MASK                     0xF0000UL                                         /**< Bit mask for EMU_BYPLIMSEL */
#define _EMU_DCDCMISCCTRL_BYPLIMSEL_DEFAULT                  0x00000000UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_BYPLIMSEL_DEFAULT                   (_EMU_DCDCMISCCTRL_BYPLIMSEL_DEFAULT << 16)       /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCLIMILIMSEL_SHIFT                20                                                /**< Shift value for EMU_LPCLIMILIMSEL */
#define _EMU_DCDCMISCCTRL_LPCLIMILIMSEL_MASK                 0x700000UL                                        /**< Bit mask for EMU_LPCLIMILIMSEL */
#define _EMU_DCDCMISCCTRL_LPCLIMILIMSEL_DEFAULT              0x00000001UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCLIMILIMSEL_DEFAULT               (_EMU_DCDCMISCCTRL_LPCLIMILIMSEL_DEFAULT << 20)   /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_SHIFT                24                                                /**< Shift value for EMU_LNCLIMILIMSEL */
#define _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_MASK                 0x7000000UL                                       /**< Bit mask for EMU_LNCLIMILIMSEL */
#define _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_DEFAULT              0x00000003UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LNCLIMILIMSEL_DEFAULT               (_EMU_DCDCMISCCTRL_LNCLIMILIMSEL_DEFAULT << 24)   /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT              28                                                /**< Shift value for EMU_LPCMPBIASEM234H */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_MASK               0x30000000UL                                      /**< Bit mask for EMU_LPCMPBIASEM234H */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS0              0x00000000UL                                      /**< Mode BIAS0 for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS1              0x00000001UL                                      /**< Mode BIAS1 for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS2              0x00000002UL                                      /**< Mode BIAS2 for EMU_DCDCMISCCTRL */
#define _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS3              0x00000003UL                                      /**< Mode BIAS3 for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPBIASEM234H_DEFAULT             (_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_DEFAULT << 28) /**< Shifted mode DEFAULT for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS0               (_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS0 << 28)   /**< Shifted mode BIAS0 for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS1               (_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS1 << 28)   /**< Shifted mode BIAS1 for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS2               (_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS2 << 28)   /**< Shifted mode BIAS2 for EMU_DCDCMISCCTRL */
#define EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS3               (_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_BIAS3 << 28)   /**< Shifted mode BIAS3 for EMU_DCDCMISCCTRL */

/* Bit fields for EMU DCDCZDETCTRL */
#define _EMU_DCDCZDETCTRL_RESETVALUE                         0x00000150UL                                  /**< Default value for EMU_DCDCZDETCTRL */
#define _EMU_DCDCZDETCTRL_MASK                               0x00000370UL                                  /**< Mask for EMU_DCDCZDETCTRL */
#define _EMU_DCDCZDETCTRL_ZDETILIMSEL_SHIFT                  4                                             /**< Shift value for EMU_ZDETILIMSEL */
#define _EMU_DCDCZDETCTRL_ZDETILIMSEL_MASK                   0x70UL                                        /**< Bit mask for EMU_ZDETILIMSEL */
#define _EMU_DCDCZDETCTRL_ZDETILIMSEL_DEFAULT                0x00000005UL                                  /**< Mode DEFAULT for EMU_DCDCZDETCTRL */
#define EMU_DCDCZDETCTRL_ZDETILIMSEL_DEFAULT                 (_EMU_DCDCZDETCTRL_ZDETILIMSEL_DEFAULT << 4)  /**< Shifted mode DEFAULT for EMU_DCDCZDETCTRL */
#define _EMU_DCDCZDETCTRL_ZDETBLANKDLY_SHIFT                 8                                             /**< Shift value for EMU_ZDETBLANKDLY */
#define _EMU_DCDCZDETCTRL_ZDETBLANKDLY_MASK                  0x300UL                                       /**< Bit mask for EMU_ZDETBLANKDLY */
#define _EMU_DCDCZDETCTRL_ZDETBLANKDLY_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for EMU_DCDCZDETCTRL */
#define EMU_DCDCZDETCTRL_ZDETBLANKDLY_DEFAULT                (_EMU_DCDCZDETCTRL_ZDETBLANKDLY_DEFAULT << 8) /**< Shifted mode DEFAULT for EMU_DCDCZDETCTRL */

/* Bit fields for EMU DCDCCLIMCTRL */
#define _EMU_DCDCCLIMCTRL_RESETVALUE                         0x00000100UL                                  /**< Default value for EMU_DCDCCLIMCTRL */
#define _EMU_DCDCCLIMCTRL_MASK                               0x00002300UL                                  /**< Mask for EMU_DCDCCLIMCTRL */
#define _EMU_DCDCCLIMCTRL_CLIMBLANKDLY_SHIFT                 8                                             /**< Shift value for EMU_CLIMBLANKDLY */
#define _EMU_DCDCCLIMCTRL_CLIMBLANKDLY_MASK                  0x300UL                                       /**< Bit mask for EMU_CLIMBLANKDLY */
#define _EMU_DCDCCLIMCTRL_CLIMBLANKDLY_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for EMU_DCDCCLIMCTRL */
#define EMU_DCDCCLIMCTRL_CLIMBLANKDLY_DEFAULT                (_EMU_DCDCCLIMCTRL_CLIMBLANKDLY_DEFAULT << 8) /**< Shifted mode DEFAULT for EMU_DCDCCLIMCTRL */
#define EMU_DCDCCLIMCTRL_BYPLIMEN                            (0x1UL << 13)                                 /**< Bypass Current Limit Enable */
#define _EMU_DCDCCLIMCTRL_BYPLIMEN_SHIFT                     13                                            /**< Shift value for EMU_BYPLIMEN */
#define _EMU_DCDCCLIMCTRL_BYPLIMEN_MASK                      0x2000UL                                      /**< Bit mask for EMU_BYPLIMEN */
#define _EMU_DCDCCLIMCTRL_BYPLIMEN_DEFAULT                   0x00000000UL                                  /**< Mode DEFAULT for EMU_DCDCCLIMCTRL */
#define EMU_DCDCCLIMCTRL_BYPLIMEN_DEFAULT                    (_EMU_DCDCCLIMCTRL_BYPLIMEN_DEFAULT << 13)    /**< Shifted mode DEFAULT for EMU_DCDCCLIMCTRL */

/* Bit fields for EMU DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_RESETVALUE                       0x57204077UL                                 /**< Default value for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_MASK                             0xF730F1F7UL                                 /**< Mask for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENR1_SHIFT                   0                                            /**< Shift value for EMU_COMPENR1 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR1_MASK                    0x7UL                                        /**< Bit mask for EMU_COMPENR1 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR1_DEFAULT                 0x00000007UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENR1_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENR1_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENR2_SHIFT                   4                                            /**< Shift value for EMU_COMPENR2 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR2_MASK                    0x1F0UL                                      /**< Bit mask for EMU_COMPENR2 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR2_DEFAULT                 0x00000007UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENR2_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENR2_DEFAULT << 4)  /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENR3_SHIFT                   12                                           /**< Shift value for EMU_COMPENR3 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR3_MASK                    0xF000UL                                     /**< Bit mask for EMU_COMPENR3 */
#define _EMU_DCDCLNCOMPCTRL_COMPENR3_DEFAULT                 0x00000004UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENR3_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENR3_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENC1_SHIFT                   20                                           /**< Shift value for EMU_COMPENC1 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC1_MASK                    0x300000UL                                   /**< Bit mask for EMU_COMPENC1 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC1_DEFAULT                 0x00000002UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENC1_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENC1_DEFAULT << 20) /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENC2_SHIFT                   24                                           /**< Shift value for EMU_COMPENC2 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC2_MASK                    0x7000000UL                                  /**< Bit mask for EMU_COMPENC2 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC2_DEFAULT                 0x00000007UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENC2_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENC2_DEFAULT << 24) /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define _EMU_DCDCLNCOMPCTRL_COMPENC3_SHIFT                   28                                           /**< Shift value for EMU_COMPENC3 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC3_MASK                    0xF0000000UL                                 /**< Bit mask for EMU_COMPENC3 */
#define _EMU_DCDCLNCOMPCTRL_COMPENC3_DEFAULT                 0x00000005UL                                 /**< Mode DEFAULT for EMU_DCDCLNCOMPCTRL */
#define EMU_DCDCLNCOMPCTRL_COMPENC3_DEFAULT                  (_EMU_DCDCLNCOMPCTRL_COMPENC3_DEFAULT << 28) /**< Shifted mode DEFAULT for EMU_DCDCLNCOMPCTRL */

/* Bit fields for EMU DCDCLNVCTRL */
#define _EMU_DCDCLNVCTRL_RESETVALUE                          0x00007100UL                           /**< Default value for EMU_DCDCLNVCTRL */
#define _EMU_DCDCLNVCTRL_MASK                                0x00007F02UL                           /**< Mask for EMU_DCDCLNVCTRL */
#define EMU_DCDCLNVCTRL_LNATT                                (0x1UL << 1)                           /**< Low Noise Mode Feedback Attenuation */
#define _EMU_DCDCLNVCTRL_LNATT_SHIFT                         1                                      /**< Shift value for EMU_LNATT */
#define _EMU_DCDCLNVCTRL_LNATT_MASK                          0x2UL                                  /**< Bit mask for EMU_LNATT */
#define _EMU_DCDCLNVCTRL_LNATT_DEFAULT                       0x00000000UL                           /**< Mode DEFAULT for EMU_DCDCLNVCTRL */
#define _EMU_DCDCLNVCTRL_LNATT_DIV3                          0x00000000UL                           /**< Mode DIV3 for EMU_DCDCLNVCTRL */
#define _EMU_DCDCLNVCTRL_LNATT_DIV6                          0x00000001UL                           /**< Mode DIV6 for EMU_DCDCLNVCTRL */
#define EMU_DCDCLNVCTRL_LNATT_DEFAULT                        (_EMU_DCDCLNVCTRL_LNATT_DEFAULT << 1)  /**< Shifted mode DEFAULT for EMU_DCDCLNVCTRL */
#define EMU_DCDCLNVCTRL_LNATT_DIV3                           (_EMU_DCDCLNVCTRL_LNATT_DIV3 << 1)     /**< Shifted mode DIV3 for EMU_DCDCLNVCTRL */
#define EMU_DCDCLNVCTRL_LNATT_DIV6                           (_EMU_DCDCLNVCTRL_LNATT_DIV6 << 1)     /**< Shifted mode DIV6 for EMU_DCDCLNVCTRL */
#define _EMU_DCDCLNVCTRL_LNVREF_SHIFT                        8                                      /**< Shift value for EMU_LNVREF */
#define _EMU_DCDCLNVCTRL_LNVREF_MASK                         0x7F00UL                               /**< Bit mask for EMU_LNVREF */
#define _EMU_DCDCLNVCTRL_LNVREF_DEFAULT                      0x00000071UL                           /**< Mode DEFAULT for EMU_DCDCLNVCTRL */
#define EMU_DCDCLNVCTRL_LNVREF_DEFAULT                       (_EMU_DCDCLNVCTRL_LNVREF_DEFAULT << 8) /**< Shifted mode DEFAULT for EMU_DCDCLNVCTRL */

/* Bit fields for EMU DCDCLPVCTRL */
#define _EMU_DCDCLPVCTRL_RESETVALUE                          0x00000168UL                           /**< Default value for EMU_DCDCLPVCTRL */
#define _EMU_DCDCLPVCTRL_MASK                                0x000001FFUL                           /**< Mask for EMU_DCDCLPVCTRL */
#define EMU_DCDCLPVCTRL_LPATT                                (0x1UL << 0)                           /**< Low Power Feedback Attenuation */
#define _EMU_DCDCLPVCTRL_LPATT_SHIFT                         0                                      /**< Shift value for EMU_LPATT */
#define _EMU_DCDCLPVCTRL_LPATT_MASK                          0x1UL                                  /**< Bit mask for EMU_LPATT */
#define _EMU_DCDCLPVCTRL_LPATT_DEFAULT                       0x00000000UL                           /**< Mode DEFAULT for EMU_DCDCLPVCTRL */
#define _EMU_DCDCLPVCTRL_LPATT_DIV4                          0x00000000UL                           /**< Mode DIV4 for EMU_DCDCLPVCTRL */
#define _EMU_DCDCLPVCTRL_LPATT_DIV8                          0x00000001UL                           /**< Mode DIV8 for EMU_DCDCLPVCTRL */
#define EMU_DCDCLPVCTRL_LPATT_DEFAULT                        (_EMU_DCDCLPVCTRL_LPATT_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_DCDCLPVCTRL */
#define EMU_DCDCLPVCTRL_LPATT_DIV4                           (_EMU_DCDCLPVCTRL_LPATT_DIV4 << 0)     /**< Shifted mode DIV4 for EMU_DCDCLPVCTRL */
#define EMU_DCDCLPVCTRL_LPATT_DIV8                           (_EMU_DCDCLPVCTRL_LPATT_DIV8 << 0)     /**< Shifted mode DIV8 for EMU_DCDCLPVCTRL */
#define _EMU_DCDCLPVCTRL_LPVREF_SHIFT                        1                                      /**< Shift value for EMU_LPVREF */
#define _EMU_DCDCLPVCTRL_LPVREF_MASK                         0x1FEUL                                /**< Bit mask for EMU_LPVREF */
#define _EMU_DCDCLPVCTRL_LPVREF_DEFAULT                      0x000000B4UL                           /**< Mode DEFAULT for EMU_DCDCLPVCTRL */
#define EMU_DCDCLPVCTRL_LPVREF_DEFAULT                       (_EMU_DCDCLPVCTRL_LPVREF_DEFAULT << 1) /**< Shifted mode DEFAULT for EMU_DCDCLPVCTRL */

/* Bit fields for EMU DCDCLPCTRL */
#define _EMU_DCDCLPCTRL_RESETVALUE                           0x03000000UL                                      /**< Default value for EMU_DCDCLPCTRL */
#define _EMU_DCDCLPCTRL_MASK                                 0x0700F000UL                                      /**< Mask for EMU_DCDCLPCTRL */
#define _EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_SHIFT              12                                                /**< Shift value for EMU_LPCMPHYSSELEM234H */
#define _EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK               0xF000UL                                          /**< Bit mask for EMU_LPCMPHYSSELEM234H */
#define _EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for EMU_DCDCLPCTRL */
#define EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_DEFAULT             (_EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_DCDCLPCTRL */
#define EMU_DCDCLPCTRL_LPVREFDUTYEN                          (0x1UL << 24)                                     /**< LP Mode Duty Cycling Enable */
#define _EMU_DCDCLPCTRL_LPVREFDUTYEN_SHIFT                   24                                                /**< Shift value for EMU_LPVREFDUTYEN */
#define _EMU_DCDCLPCTRL_LPVREFDUTYEN_MASK                    0x1000000UL                                       /**< Bit mask for EMU_LPVREFDUTYEN */
#define _EMU_DCDCLPCTRL_LPVREFDUTYEN_DEFAULT                 0x00000001UL                                      /**< Mode DEFAULT for EMU_DCDCLPCTRL */
#define EMU_DCDCLPCTRL_LPVREFDUTYEN_DEFAULT                  (_EMU_DCDCLPCTRL_LPVREFDUTYEN_DEFAULT << 24)      /**< Shifted mode DEFAULT for EMU_DCDCLPCTRL */
#define _EMU_DCDCLPCTRL_LPBLANK_SHIFT                        25                                                /**< Shift value for EMU_LPBLANK */
#define _EMU_DCDCLPCTRL_LPBLANK_MASK                         0x6000000UL                                       /**< Bit mask for EMU_LPBLANK */
#define _EMU_DCDCLPCTRL_LPBLANK_DEFAULT                      0x00000001UL                                      /**< Mode DEFAULT for EMU_DCDCLPCTRL */
#define EMU_DCDCLPCTRL_LPBLANK_DEFAULT                       (_EMU_DCDCLPCTRL_LPBLANK_DEFAULT << 25)           /**< Shifted mode DEFAULT for EMU_DCDCLPCTRL */

/* Bit fields for EMU DCDCLNFREQCTRL */
#define _EMU_DCDCLNFREQCTRL_RESETVALUE                       0x10000000UL                                /**< Default value for EMU_DCDCLNFREQCTRL */
#define _EMU_DCDCLNFREQCTRL_MASK                             0x1F000007UL                                /**< Mask for EMU_DCDCLNFREQCTRL */
#define _EMU_DCDCLNFREQCTRL_RCOBAND_SHIFT                    0                                           /**< Shift value for EMU_RCOBAND */
#define _EMU_DCDCLNFREQCTRL_RCOBAND_MASK                     0x7UL                                       /**< Bit mask for EMU_RCOBAND */
#define _EMU_DCDCLNFREQCTRL_RCOBAND_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for EMU_DCDCLNFREQCTRL */
#define EMU_DCDCLNFREQCTRL_RCOBAND_DEFAULT                   (_EMU_DCDCLNFREQCTRL_RCOBAND_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_DCDCLNFREQCTRL */
#define _EMU_DCDCLNFREQCTRL_RCOTRIM_SHIFT                    24                                          /**< Shift value for EMU_RCOTRIM */
#define _EMU_DCDCLNFREQCTRL_RCOTRIM_MASK                     0x1F000000UL                                /**< Bit mask for EMU_RCOTRIM */
#define _EMU_DCDCLNFREQCTRL_RCOTRIM_DEFAULT                  0x00000010UL                                /**< Mode DEFAULT for EMU_DCDCLNFREQCTRL */
#define EMU_DCDCLNFREQCTRL_RCOTRIM_DEFAULT                   (_EMU_DCDCLNFREQCTRL_RCOTRIM_DEFAULT << 24) /**< Shifted mode DEFAULT for EMU_DCDCLNFREQCTRL */

/* Bit fields for EMU DCDCSYNC */
#define _EMU_DCDCSYNC_RESETVALUE                             0x00000000UL                              /**< Default value for EMU_DCDCSYNC */
#define _EMU_DCDCSYNC_MASK                                   0x00000001UL                              /**< Mask for EMU_DCDCSYNC */
#define EMU_DCDCSYNC_DCDCCTRLBUSY                            (0x1UL << 0)                              /**< DCDC CTRL Register Transfer Busy */
#define _EMU_DCDCSYNC_DCDCCTRLBUSY_SHIFT                     0                                         /**< Shift value for EMU_DCDCCTRLBUSY */
#define _EMU_DCDCSYNC_DCDCCTRLBUSY_MASK                      0x1UL                                     /**< Bit mask for EMU_DCDCCTRLBUSY */
#define _EMU_DCDCSYNC_DCDCCTRLBUSY_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for EMU_DCDCSYNC */
#define EMU_DCDCSYNC_DCDCCTRLBUSY_DEFAULT                    (_EMU_DCDCSYNC_DCDCCTRLBUSY_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_DCDCSYNC */

/* Bit fields for EMU VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_RESETVALUE                         0x00000000UL                                      /**< Default value for EMU_VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_MASK                               0x00FFFF0DUL                                      /**< Mask for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_EN                                  (0x1UL << 0)                                      /**< Enable */
#define _EMU_VMONAVDDCTRL_EN_SHIFT                           0                                                 /**< Shift value for EMU_EN */
#define _EMU_VMONAVDDCTRL_EN_MASK                            0x1UL                                             /**< Bit mask for EMU_EN */
#define _EMU_VMONAVDDCTRL_EN_DEFAULT                         0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_EN_DEFAULT                          (_EMU_VMONAVDDCTRL_EN_DEFAULT << 0)               /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_RISEWU                              (0x1UL << 2)                                      /**< Rise Wakeup */
#define _EMU_VMONAVDDCTRL_RISEWU_SHIFT                       2                                                 /**< Shift value for EMU_RISEWU */
#define _EMU_VMONAVDDCTRL_RISEWU_MASK                        0x4UL                                             /**< Bit mask for EMU_RISEWU */
#define _EMU_VMONAVDDCTRL_RISEWU_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_RISEWU_DEFAULT                      (_EMU_VMONAVDDCTRL_RISEWU_DEFAULT << 2)           /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_FALLWU                              (0x1UL << 3)                                      /**< Fall Wakeup */
#define _EMU_VMONAVDDCTRL_FALLWU_SHIFT                       3                                                 /**< Shift value for EMU_FALLWU */
#define _EMU_VMONAVDDCTRL_FALLWU_MASK                        0x8UL                                             /**< Bit mask for EMU_FALLWU */
#define _EMU_VMONAVDDCTRL_FALLWU_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_FALLWU_DEFAULT                      (_EMU_VMONAVDDCTRL_FALLWU_DEFAULT << 3)           /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_FALLTHRESFINE_SHIFT                8                                                 /**< Shift value for EMU_FALLTHRESFINE */
#define _EMU_VMONAVDDCTRL_FALLTHRESFINE_MASK                 0xF00UL                                           /**< Bit mask for EMU_FALLTHRESFINE */
#define _EMU_VMONAVDDCTRL_FALLTHRESFINE_DEFAULT              0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_FALLTHRESFINE_DEFAULT               (_EMU_VMONAVDDCTRL_FALLTHRESFINE_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_FALLTHRESCOARSE_SHIFT              12                                                /**< Shift value for EMU_FALLTHRESCOARSE */
#define _EMU_VMONAVDDCTRL_FALLTHRESCOARSE_MASK               0xF000UL                                          /**< Bit mask for EMU_FALLTHRESCOARSE */
#define _EMU_VMONAVDDCTRL_FALLTHRESCOARSE_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_FALLTHRESCOARSE_DEFAULT             (_EMU_VMONAVDDCTRL_FALLTHRESCOARSE_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_RISETHRESFINE_SHIFT                16                                                /**< Shift value for EMU_RISETHRESFINE */
#define _EMU_VMONAVDDCTRL_RISETHRESFINE_MASK                 0xF0000UL                                         /**< Bit mask for EMU_RISETHRESFINE */
#define _EMU_VMONAVDDCTRL_RISETHRESFINE_DEFAULT              0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_RISETHRESFINE_DEFAULT               (_EMU_VMONAVDDCTRL_RISETHRESFINE_DEFAULT << 16)   /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */
#define _EMU_VMONAVDDCTRL_RISETHRESCOARSE_SHIFT              20                                                /**< Shift value for EMU_RISETHRESCOARSE */
#define _EMU_VMONAVDDCTRL_RISETHRESCOARSE_MASK               0xF00000UL                                        /**< Bit mask for EMU_RISETHRESCOARSE */
#define _EMU_VMONAVDDCTRL_RISETHRESCOARSE_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for EMU_VMONAVDDCTRL */
#define EMU_VMONAVDDCTRL_RISETHRESCOARSE_DEFAULT             (_EMU_VMONAVDDCTRL_RISETHRESCOARSE_DEFAULT << 20) /**< Shifted mode DEFAULT for EMU_VMONAVDDCTRL */

/* Bit fields for EMU VMONALTAVDDCTRL */
#define _EMU_VMONALTAVDDCTRL_RESETVALUE                      0x00000000UL                                     /**< Default value for EMU_VMONALTAVDDCTRL */
#define _EMU_VMONALTAVDDCTRL_MASK                            0x0000FF0DUL                                     /**< Mask for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_EN                               (0x1UL << 0)                                     /**< Enable */
#define _EMU_VMONALTAVDDCTRL_EN_SHIFT                        0                                                /**< Shift value for EMU_EN */
#define _EMU_VMONALTAVDDCTRL_EN_MASK                         0x1UL                                            /**< Bit mask for EMU_EN */
#define _EMU_VMONALTAVDDCTRL_EN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_EN_DEFAULT                       (_EMU_VMONALTAVDDCTRL_EN_DEFAULT << 0)           /**< Shifted mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_RISEWU                           (0x1UL << 2)                                     /**< Rise Wakeup */
#define _EMU_VMONALTAVDDCTRL_RISEWU_SHIFT                    2                                                /**< Shift value for EMU_RISEWU */
#define _EMU_VMONALTAVDDCTRL_RISEWU_MASK                     0x4UL                                            /**< Bit mask for EMU_RISEWU */
#define _EMU_VMONALTAVDDCTRL_RISEWU_DEFAULT                  0x00000000UL                                     /**< Mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_RISEWU_DEFAULT                   (_EMU_VMONALTAVDDCTRL_RISEWU_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_FALLWU                           (0x1UL << 3)                                     /**< Fall Wakeup */
#define _EMU_VMONALTAVDDCTRL_FALLWU_SHIFT                    3                                                /**< Shift value for EMU_FALLWU */
#define _EMU_VMONALTAVDDCTRL_FALLWU_MASK                     0x8UL                                            /**< Bit mask for EMU_FALLWU */
#define _EMU_VMONALTAVDDCTRL_FALLWU_DEFAULT                  0x00000000UL                                     /**< Mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_FALLWU_DEFAULT                   (_EMU_VMONALTAVDDCTRL_FALLWU_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define _EMU_VMONALTAVDDCTRL_THRESFINE_SHIFT                 8                                                /**< Shift value for EMU_THRESFINE */
#define _EMU_VMONALTAVDDCTRL_THRESFINE_MASK                  0xF00UL                                          /**< Bit mask for EMU_THRESFINE */
#define _EMU_VMONALTAVDDCTRL_THRESFINE_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_THRESFINE_DEFAULT                (_EMU_VMONALTAVDDCTRL_THRESFINE_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define _EMU_VMONALTAVDDCTRL_THRESCOARSE_SHIFT               12                                               /**< Shift value for EMU_THRESCOARSE */
#define _EMU_VMONALTAVDDCTRL_THRESCOARSE_MASK                0xF000UL                                         /**< Bit mask for EMU_THRESCOARSE */
#define _EMU_VMONALTAVDDCTRL_THRESCOARSE_DEFAULT             0x00000000UL                                     /**< Mode DEFAULT for EMU_VMONALTAVDDCTRL */
#define EMU_VMONALTAVDDCTRL_THRESCOARSE_DEFAULT              (_EMU_VMONALTAVDDCTRL_THRESCOARSE_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_VMONALTAVDDCTRL */

/* Bit fields for EMU VMONDVDDCTRL */
#define _EMU_VMONDVDDCTRL_RESETVALUE                         0x00000000UL                                  /**< Default value for EMU_VMONDVDDCTRL */
#define _EMU_VMONDVDDCTRL_MASK                               0x0000FF0DUL                                  /**< Mask for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_EN                                  (0x1UL << 0)                                  /**< Enable */
#define _EMU_VMONDVDDCTRL_EN_SHIFT                           0                                             /**< Shift value for EMU_EN */
#define _EMU_VMONDVDDCTRL_EN_MASK                            0x1UL                                         /**< Bit mask for EMU_EN */
#define _EMU_VMONDVDDCTRL_EN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_EN_DEFAULT                          (_EMU_VMONDVDDCTRL_EN_DEFAULT << 0)           /**< Shifted mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_RISEWU                              (0x1UL << 2)                                  /**< Rise Wakeup */
#define _EMU_VMONDVDDCTRL_RISEWU_SHIFT                       2                                             /**< Shift value for EMU_RISEWU */
#define _EMU_VMONDVDDCTRL_RISEWU_MASK                        0x4UL                                         /**< Bit mask for EMU_RISEWU */
#define _EMU_VMONDVDDCTRL_RISEWU_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_RISEWU_DEFAULT                      (_EMU_VMONDVDDCTRL_RISEWU_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_FALLWU                              (0x1UL << 3)                                  /**< Fall Wakeup */
#define _EMU_VMONDVDDCTRL_FALLWU_SHIFT                       3                                             /**< Shift value for EMU_FALLWU */
#define _EMU_VMONDVDDCTRL_FALLWU_MASK                        0x8UL                                         /**< Bit mask for EMU_FALLWU */
#define _EMU_VMONDVDDCTRL_FALLWU_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_FALLWU_DEFAULT                      (_EMU_VMONDVDDCTRL_FALLWU_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_VMONDVDDCTRL */
#define _EMU_VMONDVDDCTRL_THRESFINE_SHIFT                    8                                             /**< Shift value for EMU_THRESFINE */
#define _EMU_VMONDVDDCTRL_THRESFINE_MASK                     0xF00UL                                       /**< Bit mask for EMU_THRESFINE */
#define _EMU_VMONDVDDCTRL_THRESFINE_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_THRESFINE_DEFAULT                   (_EMU_VMONDVDDCTRL_THRESFINE_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_VMONDVDDCTRL */
#define _EMU_VMONDVDDCTRL_THRESCOARSE_SHIFT                  12                                            /**< Shift value for EMU_THRESCOARSE */
#define _EMU_VMONDVDDCTRL_THRESCOARSE_MASK                   0xF000UL                                      /**< Bit mask for EMU_THRESCOARSE */
#define _EMU_VMONDVDDCTRL_THRESCOARSE_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for EMU_VMONDVDDCTRL */
#define EMU_VMONDVDDCTRL_THRESCOARSE_DEFAULT                 (_EMU_VMONDVDDCTRL_THRESCOARSE_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_VMONDVDDCTRL */

/* Bit fields for EMU VMONIO0CTRL */
#define _EMU_VMONIO0CTRL_RESETVALUE                          0x00000000UL                                 /**< Default value for EMU_VMONIO0CTRL */
#define _EMU_VMONIO0CTRL_MASK                                0x0000FF1DUL                                 /**< Mask for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_EN                                   (0x1UL << 0)                                 /**< Enable */
#define _EMU_VMONIO0CTRL_EN_SHIFT                            0                                            /**< Shift value for EMU_EN */
#define _EMU_VMONIO0CTRL_EN_MASK                             0x1UL                                        /**< Bit mask for EMU_EN */
#define _EMU_VMONIO0CTRL_EN_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_EN_DEFAULT                           (_EMU_VMONIO0CTRL_EN_DEFAULT << 0)           /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_RISEWU                               (0x1UL << 2)                                 /**< Rise Wakeup */
#define _EMU_VMONIO0CTRL_RISEWU_SHIFT                        2                                            /**< Shift value for EMU_RISEWU */
#define _EMU_VMONIO0CTRL_RISEWU_MASK                         0x4UL                                        /**< Bit mask for EMU_RISEWU */
#define _EMU_VMONIO0CTRL_RISEWU_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_RISEWU_DEFAULT                       (_EMU_VMONIO0CTRL_RISEWU_DEFAULT << 2)       /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_FALLWU                               (0x1UL << 3)                                 /**< Fall Wakeup */
#define _EMU_VMONIO0CTRL_FALLWU_SHIFT                        3                                            /**< Shift value for EMU_FALLWU */
#define _EMU_VMONIO0CTRL_FALLWU_MASK                         0x8UL                                        /**< Bit mask for EMU_FALLWU */
#define _EMU_VMONIO0CTRL_FALLWU_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_FALLWU_DEFAULT                       (_EMU_VMONIO0CTRL_FALLWU_DEFAULT << 3)       /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_RETDIS                               (0x1UL << 4)                                 /**< EM4 IO0 Retention Disable */
#define _EMU_VMONIO0CTRL_RETDIS_SHIFT                        4                                            /**< Shift value for EMU_RETDIS */
#define _EMU_VMONIO0CTRL_RETDIS_MASK                         0x10UL                                       /**< Bit mask for EMU_RETDIS */
#define _EMU_VMONIO0CTRL_RETDIS_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_RETDIS_DEFAULT                       (_EMU_VMONIO0CTRL_RETDIS_DEFAULT << 4)       /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */
#define _EMU_VMONIO0CTRL_THRESFINE_SHIFT                     8                                            /**< Shift value for EMU_THRESFINE */
#define _EMU_VMONIO0CTRL_THRESFINE_MASK                      0xF00UL                                      /**< Bit mask for EMU_THRESFINE */
#define _EMU_VMONIO0CTRL_THRESFINE_DEFAULT                   0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_THRESFINE_DEFAULT                    (_EMU_VMONIO0CTRL_THRESFINE_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */
#define _EMU_VMONIO0CTRL_THRESCOARSE_SHIFT                   12                                           /**< Shift value for EMU_THRESCOARSE */
#define _EMU_VMONIO0CTRL_THRESCOARSE_MASK                    0xF000UL                                     /**< Bit mask for EMU_THRESCOARSE */
#define _EMU_VMONIO0CTRL_THRESCOARSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for EMU_VMONIO0CTRL */
#define EMU_VMONIO0CTRL_THRESCOARSE_DEFAULT                  (_EMU_VMONIO0CTRL_THRESCOARSE_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_VMONIO0CTRL */

/* Bit fields for EMU RAM1CTRL */
#define _EMU_RAM1CTRL_RESETVALUE                             0x00000000UL                              /**< Default value for EMU_RAM1CTRL */
#define _EMU_RAM1CTRL_MASK                                   0x00000003UL                              /**< Mask for EMU_RAM1CTRL */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_SHIFT                     0                                         /**< Shift value for EMU_RAMPOWERDOWN */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_MASK                      0x3UL                                     /**< Bit mask for EMU_RAMPOWERDOWN */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for EMU_RAM1CTRL */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_NONE                      0x00000000UL                              /**< Mode NONE for EMU_RAM1CTRL */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_BLK1                      0x00000002UL                              /**< Mode BLK1 for EMU_RAM1CTRL */
#define _EMU_RAM1CTRL_RAMPOWERDOWN_BLK0TO1                   0x00000003UL                              /**< Mode BLK0TO1 for EMU_RAM1CTRL */
#define EMU_RAM1CTRL_RAMPOWERDOWN_DEFAULT                    (_EMU_RAM1CTRL_RAMPOWERDOWN_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_RAM1CTRL */
#define EMU_RAM1CTRL_RAMPOWERDOWN_NONE                       (_EMU_RAM1CTRL_RAMPOWERDOWN_NONE << 0)    /**< Shifted mode NONE for EMU_RAM1CTRL */
#define EMU_RAM1CTRL_RAMPOWERDOWN_BLK1                       (_EMU_RAM1CTRL_RAMPOWERDOWN_BLK1 << 0)    /**< Shifted mode BLK1 for EMU_RAM1CTRL */
#define EMU_RAM1CTRL_RAMPOWERDOWN_BLK0TO1                    (_EMU_RAM1CTRL_RAMPOWERDOWN_BLK0TO1 << 0) /**< Shifted mode BLK0TO1 for EMU_RAM1CTRL */

/* Bit fields for EMU RAM2CTRL */
#define _EMU_RAM2CTRL_RESETVALUE                             0x00000000UL                              /**< Default value for EMU_RAM2CTRL */
#define _EMU_RAM2CTRL_MASK                                   0x00000001UL                              /**< Mask for EMU_RAM2CTRL */
#define _EMU_RAM2CTRL_RAMPOWERDOWN_SHIFT                     0                                         /**< Shift value for EMU_RAMPOWERDOWN */
#define _EMU_RAM2CTRL_RAMPOWERDOWN_MASK                      0x1UL                                     /**< Bit mask for EMU_RAMPOWERDOWN */
#define _EMU_RAM2CTRL_RAMPOWERDOWN_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for EMU_RAM2CTRL */
#define _EMU_RAM2CTRL_RAMPOWERDOWN_NONE                      0x00000000UL                              /**< Mode NONE for EMU_RAM2CTRL */
#define _EMU_RAM2CTRL_RAMPOWERDOWN_BLK                       0x00000001UL                              /**< Mode BLK for EMU_RAM2CTRL */
#define EMU_RAM2CTRL_RAMPOWERDOWN_DEFAULT                    (_EMU_RAM2CTRL_RAMPOWERDOWN_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_RAM2CTRL */
#define EMU_RAM2CTRL_RAMPOWERDOWN_NONE                       (_EMU_RAM2CTRL_RAMPOWERDOWN_NONE << 0)    /**< Shifted mode NONE for EMU_RAM2CTRL */
#define EMU_RAM2CTRL_RAMPOWERDOWN_BLK                        (_EMU_RAM2CTRL_RAMPOWERDOWN_BLK << 0)     /**< Shifted mode BLK for EMU_RAM2CTRL */

/* Bit fields for EMU DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_RESETVALUE                        0x00000300UL                                       /**< Default value for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_MASK                              0x0000F300UL                                       /**< Mask for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_SHIFT               8                                                  /**< Shift value for EMU_LPCMPBIASEM01 */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK                0x300UL                                            /**< Bit mask for EMU_LPCMPBIASEM01 */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS0               0x00000000UL                                       /**< Mode BIAS0 for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS1               0x00000001UL                                       /**< Mode BIAS1 for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS2               0x00000002UL                                       /**< Mode BIAS2 for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_DEFAULT             0x00000003UL                                       /**< Mode DEFAULT for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS3               0x00000003UL                                       /**< Mode BIAS3 for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS0                (_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS0 << 8)      /**< Shifted mode BIAS0 for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS1                (_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS1 << 8)      /**< Shifted mode BIAS1 for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS2                (_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS2 << 8)      /**< Shifted mode BIAS2 for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPBIASEM01_DEFAULT              (_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_DEFAULT << 8)    /**< Shifted mode DEFAULT for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS3                (_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS3 << 8)      /**< Shifted mode BIAS3 for EMU_DCDCLPEM01CFG */
#define _EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_SHIFT             12                                                 /**< Shift value for EMU_LPCMPHYSSELEM01 */
#define _EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_MASK              0xF000UL                                           /**< Bit mask for EMU_LPCMPHYSSELEM01 */
#define _EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_DEFAULT           0x00000000UL                                       /**< Mode DEFAULT for EMU_DCDCLPEM01CFG */
#define EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_DEFAULT            (_EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_DEFAULT << 12) /**< Shifted mode DEFAULT for EMU_DCDCLPEM01CFG */

/* Bit fields for EMU EM23PERNORETAINCMD */
#define _EMU_EM23PERNORETAINCMD_RESETVALUE                   0x00000000UL                                           /**< Default value for EMU_EM23PERNORETAINCMD */
#define _EMU_EM23PERNORETAINCMD_MASK                         0x0000FFE7UL                                           /**< Mask for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ACMP0UNLOCK                   (0x1UL << 0)                                           /**< Clears Status Bit of ACMP0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_ACMP0UNLOCK_SHIFT            0                                                      /**< Shift value for EMU_ACMP0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ACMP0UNLOCK_MASK             0x1UL                                                  /**< Bit mask for EMU_ACMP0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ACMP0UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ACMP0UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_ACMP0UNLOCK_DEFAULT << 0)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ACMP1UNLOCK                   (0x1UL << 1)                                           /**< Clears Status Bit of ACMP1 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_ACMP1UNLOCK_SHIFT            1                                                      /**< Shift value for EMU_ACMP1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ACMP1UNLOCK_MASK             0x2UL                                                  /**< Bit mask for EMU_ACMP1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ACMP1UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ACMP1UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_ACMP1UNLOCK_DEFAULT << 1)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_PCNT0UNLOCK                   (0x1UL << 2)                                           /**< Clears Status Bit of PCNT0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_PCNT0UNLOCK_SHIFT            2                                                      /**< Shift value for EMU_PCNT0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_PCNT0UNLOCK_MASK             0x4UL                                                  /**< Bit mask for EMU_PCNT0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_PCNT0UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_PCNT0UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_PCNT0UNLOCK_DEFAULT << 2)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_I2C0UNLOCK                    (0x1UL << 5)                                           /**< Clears Status Bit of I2C0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_I2C0UNLOCK_SHIFT             5                                                      /**< Shift value for EMU_I2C0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_I2C0UNLOCK_MASK              0x20UL                                                 /**< Bit mask for EMU_I2C0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_I2C0UNLOCK_DEFAULT           0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_I2C0UNLOCK_DEFAULT            (_EMU_EM23PERNORETAINCMD_I2C0UNLOCK_DEFAULT << 5)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_I2C1UNLOCK                    (0x1UL << 6)                                           /**< Clears Status Bit of I2C1 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_I2C1UNLOCK_SHIFT             6                                                      /**< Shift value for EMU_I2C1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_I2C1UNLOCK_MASK              0x40UL                                                 /**< Bit mask for EMU_I2C1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_I2C1UNLOCK_DEFAULT           0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_I2C1UNLOCK_DEFAULT            (_EMU_EM23PERNORETAINCMD_I2C1UNLOCK_DEFAULT << 6)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_DAC0UNLOCK                    (0x1UL << 7)                                           /**< Clears Status Bit of DAC0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_DAC0UNLOCK_SHIFT             7                                                      /**< Shift value for EMU_DAC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_DAC0UNLOCK_MASK              0x80UL                                                 /**< Bit mask for EMU_DAC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_DAC0UNLOCK_DEFAULT           0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_DAC0UNLOCK_DEFAULT            (_EMU_EM23PERNORETAINCMD_DAC0UNLOCK_DEFAULT << 7)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_IDAC0UNLOCK                   (0x1UL << 8)                                           /**< Clears Status Bit of IDAC0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_IDAC0UNLOCK_SHIFT            8                                                      /**< Shift value for EMU_IDAC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_IDAC0UNLOCK_MASK             0x100UL                                                /**< Bit mask for EMU_IDAC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_IDAC0UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_IDAC0UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_IDAC0UNLOCK_DEFAULT << 8)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ADC0UNLOCK                    (0x1UL << 9)                                           /**< Clears Status Bit of ADC0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_ADC0UNLOCK_SHIFT             9                                                      /**< Shift value for EMU_ADC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ADC0UNLOCK_MASK              0x200UL                                                /**< Bit mask for EMU_ADC0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_ADC0UNLOCK_DEFAULT           0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_ADC0UNLOCK_DEFAULT            (_EMU_EM23PERNORETAINCMD_ADC0UNLOCK_DEFAULT << 9)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK                (0x1UL << 10)                                          /**< Clears Status Bit of LETIMER0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK_SHIFT         10                                                     /**< Shift value for EMU_LETIMER0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK_MASK          0x400UL                                                /**< Bit mask for EMU_LETIMER0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK_DEFAULT       0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK_DEFAULT        (_EMU_EM23PERNORETAINCMD_LETIMER0UNLOCK_DEFAULT << 10) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_WDOG0UNLOCK                   (0x1UL << 11)                                          /**< Clears Status Bit of WDOG0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_WDOG0UNLOCK_SHIFT            11                                                     /**< Shift value for EMU_WDOG0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_WDOG0UNLOCK_MASK             0x800UL                                                /**< Bit mask for EMU_WDOG0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_WDOG0UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_WDOG0UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_WDOG0UNLOCK_DEFAULT << 11)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_WDOG1UNLOCK                   (0x1UL << 12)                                          /**< Clears Status Bit of WDOG1 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_WDOG1UNLOCK_SHIFT            12                                                     /**< Shift value for EMU_WDOG1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_WDOG1UNLOCK_MASK             0x1000UL                                               /**< Bit mask for EMU_WDOG1UNLOCK */
#define _EMU_EM23PERNORETAINCMD_WDOG1UNLOCK_DEFAULT          0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_WDOG1UNLOCK_DEFAULT           (_EMU_EM23PERNORETAINCMD_WDOG1UNLOCK_DEFAULT << 12)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK                (0x1UL << 13)                                          /**< Clears Status Bit of LESENSE0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK_SHIFT         13                                                     /**< Shift value for EMU_LESENSE0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK_MASK          0x2000UL                                               /**< Bit mask for EMU_LESENSE0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK_DEFAULT       0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK_DEFAULT        (_EMU_EM23PERNORETAINCMD_LESENSE0UNLOCK_DEFAULT << 13) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_CSENUNLOCK                    (0x1UL << 14)                                          /**< Clears Status Bit of CSEN and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_CSENUNLOCK_SHIFT             14                                                     /**< Shift value for EMU_CSENUNLOCK */
#define _EMU_EM23PERNORETAINCMD_CSENUNLOCK_MASK              0x4000UL                                               /**< Bit mask for EMU_CSENUNLOCK */
#define _EMU_EM23PERNORETAINCMD_CSENUNLOCK_DEFAULT           0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_CSENUNLOCK_DEFAULT            (_EMU_EM23PERNORETAINCMD_CSENUNLOCK_DEFAULT << 14)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LEUART0UNLOCK                 (0x1UL << 15)                                          /**< Clears Status Bit of LEUART0 and Unlocks Access to It */
#define _EMU_EM23PERNORETAINCMD_LEUART0UNLOCK_SHIFT          15                                                     /**< Shift value for EMU_LEUART0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LEUART0UNLOCK_MASK           0x8000UL                                               /**< Bit mask for EMU_LEUART0UNLOCK */
#define _EMU_EM23PERNORETAINCMD_LEUART0UNLOCK_DEFAULT        0x00000000UL                                           /**< Mode DEFAULT for EMU_EM23PERNORETAINCMD */
#define EMU_EM23PERNORETAINCMD_LEUART0UNLOCK_DEFAULT         (_EMU_EM23PERNORETAINCMD_LEUART0UNLOCK_DEFAULT << 15)  /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCMD */

/* Bit fields for EMU EM23PERNORETAINSTATUS */
#define _EMU_EM23PERNORETAINSTATUS_RESETVALUE                0x00000000UL                                              /**< Default value for EMU_EM23PERNORETAINSTATUS */
#define _EMU_EM23PERNORETAINSTATUS_MASK                      0x0000FFE7UL                                              /**< Mask for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED                (0x1UL << 0)                                              /**< Indicates If ACMP0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED_SHIFT         0                                                         /**< Shift value for EMU_ACMP0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED_MASK          0x1UL                                                     /**< Bit mask for EMU_ACMP0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_ACMP0LOCKED_DEFAULT << 0)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED                (0x1UL << 1)                                              /**< Indicates If ACMP1 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED_SHIFT         1                                                         /**< Shift value for EMU_ACMP1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED_MASK          0x2UL                                                     /**< Bit mask for EMU_ACMP1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_ACMP1LOCKED_DEFAULT << 1)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED                (0x1UL << 2)                                              /**< Indicates If PCNT0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED_SHIFT         2                                                         /**< Shift value for EMU_PCNT0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED_MASK          0x4UL                                                     /**< Bit mask for EMU_PCNT0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_PCNT0LOCKED_DEFAULT << 2)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_I2C0LOCKED                 (0x1UL << 5)                                              /**< Indicates If I2C0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_I2C0LOCKED_SHIFT          5                                                         /**< Shift value for EMU_I2C0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_I2C0LOCKED_MASK           0x20UL                                                    /**< Bit mask for EMU_I2C0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_I2C0LOCKED_DEFAULT        0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_I2C0LOCKED_DEFAULT         (_EMU_EM23PERNORETAINSTATUS_I2C0LOCKED_DEFAULT << 5)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_I2C1LOCKED                 (0x1UL << 6)                                              /**< Indicates If I2C1 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_I2C1LOCKED_SHIFT          6                                                         /**< Shift value for EMU_I2C1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_I2C1LOCKED_MASK           0x40UL                                                    /**< Bit mask for EMU_I2C1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_I2C1LOCKED_DEFAULT        0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_I2C1LOCKED_DEFAULT         (_EMU_EM23PERNORETAINSTATUS_I2C1LOCKED_DEFAULT << 6)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_DAC0LOCKED                 (0x1UL << 7)                                              /**< Indicates If DAC0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_DAC0LOCKED_SHIFT          7                                                         /**< Shift value for EMU_DAC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_DAC0LOCKED_MASK           0x80UL                                                    /**< Bit mask for EMU_DAC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_DAC0LOCKED_DEFAULT        0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_DAC0LOCKED_DEFAULT         (_EMU_EM23PERNORETAINSTATUS_DAC0LOCKED_DEFAULT << 7)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED                (0x1UL << 8)                                              /**< Indicates If IDAC0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED_SHIFT         8                                                         /**< Shift value for EMU_IDAC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED_MASK          0x100UL                                                   /**< Bit mask for EMU_IDAC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_IDAC0LOCKED_DEFAULT << 8)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ADC0LOCKED                 (0x1UL << 9)                                              /**< Indicates If ADC0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_ADC0LOCKED_SHIFT          9                                                         /**< Shift value for EMU_ADC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ADC0LOCKED_MASK           0x200UL                                                   /**< Bit mask for EMU_ADC0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_ADC0LOCKED_DEFAULT        0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_ADC0LOCKED_DEFAULT         (_EMU_EM23PERNORETAINSTATUS_ADC0LOCKED_DEFAULT << 9)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED             (0x1UL << 10)                                             /**< Indicates If LETIMER0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED_SHIFT      10                                                        /**< Shift value for EMU_LETIMER0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED_MASK       0x400UL                                                   /**< Bit mask for EMU_LETIMER0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED_DEFAULT    0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED_DEFAULT     (_EMU_EM23PERNORETAINSTATUS_LETIMER0LOCKED_DEFAULT << 10) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED                (0x1UL << 11)                                             /**< Indicates If WDOG0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED_SHIFT         11                                                        /**< Shift value for EMU_WDOG0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED_MASK          0x800UL                                                   /**< Bit mask for EMU_WDOG0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_WDOG0LOCKED_DEFAULT << 11)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED                (0x1UL << 12)                                             /**< Indicates If WDOG1 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED_SHIFT         12                                                        /**< Shift value for EMU_WDOG1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED_MASK          0x1000UL                                                  /**< Bit mask for EMU_WDOG1LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED_DEFAULT       0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED_DEFAULT        (_EMU_EM23PERNORETAINSTATUS_WDOG1LOCKED_DEFAULT << 12)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED             (0x1UL << 13)                                             /**< Indicates If LESENSE0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED_SHIFT      13                                                        /**< Shift value for EMU_LESENSE0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED_MASK       0x2000UL                                                  /**< Bit mask for EMU_LESENSE0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED_DEFAULT    0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED_DEFAULT     (_EMU_EM23PERNORETAINSTATUS_LESENSE0LOCKED_DEFAULT << 13) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_CSENLOCKED                 (0x1UL << 14)                                             /**< Indicates If CSEN Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_CSENLOCKED_SHIFT          14                                                        /**< Shift value for EMU_CSENLOCKED */
#define _EMU_EM23PERNORETAINSTATUS_CSENLOCKED_MASK           0x4000UL                                                  /**< Bit mask for EMU_CSENLOCKED */
#define _EMU_EM23PERNORETAINSTATUS_CSENLOCKED_DEFAULT        0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_CSENLOCKED_DEFAULT         (_EMU_EM23PERNORETAINSTATUS_CSENLOCKED_DEFAULT << 14)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED              (0x1UL << 15)                                             /**< Indicates If LEUART0 Powered Down During EM23 */
#define _EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED_SHIFT       15                                                        /**< Shift value for EMU_LEUART0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED_MASK        0x8000UL                                                  /**< Bit mask for EMU_LEUART0LOCKED */
#define _EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED_DEFAULT     0x00000000UL                                              /**< Mode DEFAULT for EMU_EM23PERNORETAINSTATUS */
#define EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED_DEFAULT      (_EMU_EM23PERNORETAINSTATUS_LEUART0LOCKED_DEFAULT << 15)  /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINSTATUS */

/* Bit fields for EMU EM23PERNORETAINCTRL */
#define _EMU_EM23PERNORETAINCTRL_RESETVALUE                  0x00000000UL                                         /**< Default value for EMU_EM23PERNORETAINCTRL */
#define _EMU_EM23PERNORETAINCTRL_MASK                        0x0000FFE7UL                                         /**< Mask for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ACMP0DIS                     (0x1UL << 0)                                         /**< Allow Power Down of ACMP0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_ACMP0DIS_SHIFT              0                                                    /**< Shift value for EMU_ACMP0DIS */
#define _EMU_EM23PERNORETAINCTRL_ACMP0DIS_MASK               0x1UL                                                /**< Bit mask for EMU_ACMP0DIS */
#define _EMU_EM23PERNORETAINCTRL_ACMP0DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ACMP0DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_ACMP0DIS_DEFAULT << 0)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ACMP1DIS                     (0x1UL << 1)                                         /**< Allow Power Down of ACMP1 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_ACMP1DIS_SHIFT              1                                                    /**< Shift value for EMU_ACMP1DIS */
#define _EMU_EM23PERNORETAINCTRL_ACMP1DIS_MASK               0x2UL                                                /**< Bit mask for EMU_ACMP1DIS */
#define _EMU_EM23PERNORETAINCTRL_ACMP1DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ACMP1DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_ACMP1DIS_DEFAULT << 1)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_PCNT0DIS                     (0x1UL << 2)                                         /**< Allow Power Down of PCNT0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_PCNT0DIS_SHIFT              2                                                    /**< Shift value for EMU_PCNT0DIS */
#define _EMU_EM23PERNORETAINCTRL_PCNT0DIS_MASK               0x4UL                                                /**< Bit mask for EMU_PCNT0DIS */
#define _EMU_EM23PERNORETAINCTRL_PCNT0DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_PCNT0DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_PCNT0DIS_DEFAULT << 2)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_I2C0DIS                      (0x1UL << 5)                                         /**< Allow Power Down of I2C0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_I2C0DIS_SHIFT               5                                                    /**< Shift value for EMU_I2C0DIS */
#define _EMU_EM23PERNORETAINCTRL_I2C0DIS_MASK                0x20UL                                               /**< Bit mask for EMU_I2C0DIS */
#define _EMU_EM23PERNORETAINCTRL_I2C0DIS_DEFAULT             0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_I2C0DIS_DEFAULT              (_EMU_EM23PERNORETAINCTRL_I2C0DIS_DEFAULT << 5)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_I2C1DIS                      (0x1UL << 6)                                         /**< Allow Power Down of I2C1 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_I2C1DIS_SHIFT               6                                                    /**< Shift value for EMU_I2C1DIS */
#define _EMU_EM23PERNORETAINCTRL_I2C1DIS_MASK                0x40UL                                               /**< Bit mask for EMU_I2C1DIS */
#define _EMU_EM23PERNORETAINCTRL_I2C1DIS_DEFAULT             0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_I2C1DIS_DEFAULT              (_EMU_EM23PERNORETAINCTRL_I2C1DIS_DEFAULT << 6)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_VDAC0DIS                     (0x1UL << 7)                                         /**< Allow Power Down of DAC0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_VDAC0DIS_SHIFT              7                                                    /**< Shift value for EMU_VDAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_VDAC0DIS_MASK               0x80UL                                               /**< Bit mask for EMU_VDAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_VDAC0DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_VDAC0DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_VDAC0DIS_DEFAULT << 7)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_IDAC0DIS                     (0x1UL << 8)                                         /**< Allow Power Down of IDAC0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_IDAC0DIS_SHIFT              8                                                    /**< Shift value for EMU_IDAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_IDAC0DIS_MASK               0x100UL                                              /**< Bit mask for EMU_IDAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_IDAC0DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_IDAC0DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_IDAC0DIS_DEFAULT << 8)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ADC0DIS                      (0x1UL << 9)                                         /**< Allow Power Down of ADC0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_ADC0DIS_SHIFT               9                                                    /**< Shift value for EMU_ADC0DIS */
#define _EMU_EM23PERNORETAINCTRL_ADC0DIS_MASK                0x200UL                                              /**< Bit mask for EMU_ADC0DIS */
#define _EMU_EM23PERNORETAINCTRL_ADC0DIS_DEFAULT             0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_ADC0DIS_DEFAULT              (_EMU_EM23PERNORETAINCTRL_ADC0DIS_DEFAULT << 9)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LETIMER0DIS                  (0x1UL << 10)                                        /**< Allow Power Down of LETIMER0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_LETIMER0DIS_SHIFT           10                                                   /**< Shift value for EMU_LETIMER0DIS */
#define _EMU_EM23PERNORETAINCTRL_LETIMER0DIS_MASK            0x400UL                                              /**< Bit mask for EMU_LETIMER0DIS */
#define _EMU_EM23PERNORETAINCTRL_LETIMER0DIS_DEFAULT         0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LETIMER0DIS_DEFAULT          (_EMU_EM23PERNORETAINCTRL_LETIMER0DIS_DEFAULT << 10) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_WDOG0DIS                     (0x1UL << 11)                                        /**< Allow Power Down of WDOG0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_WDOG0DIS_SHIFT              11                                                   /**< Shift value for EMU_WDOG0DIS */
#define _EMU_EM23PERNORETAINCTRL_WDOG0DIS_MASK               0x800UL                                              /**< Bit mask for EMU_WDOG0DIS */
#define _EMU_EM23PERNORETAINCTRL_WDOG0DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_WDOG0DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_WDOG0DIS_DEFAULT << 11)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_WDOG1DIS                     (0x1UL << 12)                                        /**< Allow Power Down of WDOG1 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_WDOG1DIS_SHIFT              12                                                   /**< Shift value for EMU_WDOG1DIS */
#define _EMU_EM23PERNORETAINCTRL_WDOG1DIS_MASK               0x1000UL                                             /**< Bit mask for EMU_WDOG1DIS */
#define _EMU_EM23PERNORETAINCTRL_WDOG1DIS_DEFAULT            0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_WDOG1DIS_DEFAULT             (_EMU_EM23PERNORETAINCTRL_WDOG1DIS_DEFAULT << 12)    /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LESENSE0DIS                  (0x1UL << 13)                                        /**< Allow Power Down of LESENSE0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_LESENSE0DIS_SHIFT           13                                                   /**< Shift value for EMU_LESENSE0DIS */
#define _EMU_EM23PERNORETAINCTRL_LESENSE0DIS_MASK            0x2000UL                                             /**< Bit mask for EMU_LESENSE0DIS */
#define _EMU_EM23PERNORETAINCTRL_LESENSE0DIS_DEFAULT         0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LESENSE0DIS_DEFAULT          (_EMU_EM23PERNORETAINCTRL_LESENSE0DIS_DEFAULT << 13) /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_CSENDIS                      (0x1UL << 14)                                        /**< Allow Power Down of CSEN During EM23 */
#define _EMU_EM23PERNORETAINCTRL_CSENDIS_SHIFT               14                                                   /**< Shift value for EMU_CSENDIS */
#define _EMU_EM23PERNORETAINCTRL_CSENDIS_MASK                0x4000UL                                             /**< Bit mask for EMU_CSENDIS */
#define _EMU_EM23PERNORETAINCTRL_CSENDIS_DEFAULT             0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_CSENDIS_DEFAULT              (_EMU_EM23PERNORETAINCTRL_CSENDIS_DEFAULT << 14)     /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LEUART0DIS                   (0x1UL << 15)                                        /**< Allow Power Down of LEUART0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_LEUART0DIS_SHIFT            15                                                   /**< Shift value for EMU_LEUART0DIS */
#define _EMU_EM23PERNORETAINCTRL_LEUART0DIS_MASK             0x8000UL                                             /**< Bit mask for EMU_LEUART0DIS */
#define _EMU_EM23PERNORETAINCTRL_LEUART0DIS_DEFAULT          0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_LEUART0DIS_DEFAULT           (_EMU_EM23PERNORETAINCTRL_LEUART0DIS_DEFAULT << 15)  /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */



/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#if defined(_EMU_STATUS_VSCALE_MASK) \
  && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#define EMU_VSCALE_PRESENT
#endif

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

#if defined(_EMU_EM4CONF_OSC_MASK)
/** EM4 duty oscillator. */
typedef enum {
  /** Select ULFRCO as duty oscillator in EM4. */
  emuEM4Osc_ULFRCO = EMU_EM4CONF_OSC_ULFRCO,
  /** Select LFXO as duty oscillator in EM4. */
  emuEM4Osc_LFXO = EMU_EM4CONF_OSC_LFXO,
  /** Select LFRCO as duty oscillator in EM4. */
  emuEM4Osc_LFRCO = EMU_EM4CONF_OSC_LFRCO
} EMU_EM4Osc_TypeDef;
#endif

#if defined(_EMU_BUCTRL_PROBE_MASK)
/** Backup Power Voltage Probe types. */
typedef enum {
  /** Disable voltage probe. */
  emuProbe_Disable = EMU_BUCTRL_PROBE_DISABLE,
  /** Connect probe to VDD_DREG. */
  emuProbe_VDDDReg = EMU_BUCTRL_PROBE_VDDDREG,
  /** Connect probe to BU_IN. */
  emuProbe_BUIN    = EMU_BUCTRL_PROBE_BUIN,
  /** Connect probe to BU_OUT. */
  emuProbe_BUOUT   = EMU_BUCTRL_PROBE_BUOUT
} EMU_Probe_TypeDef;
#endif

#if defined(_EMU_PWRCONF_PWRRES_MASK)
/** Backup Power Domain resistor selection. */
typedef enum {
  /** Main power and backup power connected with RES0 series resistance. */
  emuRes_Res0 = EMU_PWRCONF_PWRRES_RES0,
  /** Main power and backup power connected with RES1 series resistance. */
  emuRes_Res1 = EMU_PWRCONF_PWRRES_RES1,
  /** Main power and backup power connected with RES2 series resistance. */
  emuRes_Res2 = EMU_PWRCONF_PWRRES_RES2,
  /** Main power and backup power connected with RES3 series resistance. */
  emuRes_Res3 = EMU_PWRCONF_PWRRES_RES3,
} EMU_Resistor_TypeDef;
#endif

#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_0)
/** Backup Power Domain power connection. */
typedef enum {
  /** No connection between main and backup power. */
  emuPower_None = EMU_BUINACT_PWRCON_NONE,
  /** Main power and backup power connected through diode,
      allowing current from backup to main only. */
  emuPower_BUMain = EMU_BUINACT_PWRCON_BUMAIN,
  /** Main power and backup power connected through diode,
      allowing current from main to backup only. */
  emuPower_MainBU = EMU_BUINACT_PWRCON_MAINBU,
  /** Main power and backup power connected without diode. */
  emuPower_NoDiode = EMU_BUINACT_PWRCON_NODIODE,
} EMU_Power_TypeDef;
#endif

#if defined(_EMU_BUCTRL_BUINACTPWRCON_MASK)
/** Backup Power Domain power connection configuration when not in backup mode selection. */
typedef enum {
  /** No connection. */
  emuBuBuInactPwrCon_None    = EMU_BUCTRL_BUINACTPWRCON_NONE,
  /** Allow power from backup to main. */
  emuBuBuInactPwrCon_MainBu  = EMU_BUCTRL_BUINACTPWRCON_MAINBU,
  /** Allow power from main to backup. */
  emuBuBuInactPwrCon_BuMain  = EMU_BUCTRL_BUINACTPWRCON_BUMAIN,
  /** Backup and main power are connected. */
  emuBuBuInactPwrCon_NoDiode = EMU_BUCTRL_BUINACTPWRCON_NODIODE,
} EMU_BUBuInactPwrCon_TypeDef;
#endif

#if defined(_EMU_BUCTRL_BUACTPWRCON_MASK)
/** Backup Power Domain power connection configuration in backup mode selection. */
typedef enum {
  /** No connection. */
  emuBuBuActPwrCon_None    = EMU_BUCTRL_BUACTPWRCON_NONE,
  /** Allow power from backup to main. */
  emuBuBuActPwrCon_MainBu  = EMU_BUCTRL_BUACTPWRCON_MAINBU,
  /** Allow power from main to backup. */
  emuBuBuActPwrCon_BuMain  = EMU_BUCTRL_BUACTPWRCON_BUMAIN,
  /** Backup and main power are connected. */
  emuBuBuActPwrCon_NoDiode = EMU_BUCTRL_BUACTPWRCON_NODIODE,
} EMU_BUBuActPwrCon_TypeDef;
#endif

#if defined(_EMU_BUCTRL_PWRRES_MASK)
/** Backup Power Domain resistor selection. */
typedef enum {
  /** Main power and backup power connected with RES0 series resistance. */
  emuBuPwrRes_Res0 = EMU_BUCTRL_PWRRES_RES0,
  /** Main power and backup power connected with RES1 series resistance. */
  emuBuPwrRes_Res1 = EMU_BUCTRL_PWRRES_RES1,
  /** Main power and backup power connected with RES2 series resistance. */
  emuBuPwrRes_Res2 = EMU_BUCTRL_PWRRES_RES2,
  /** Main power and backup power connected with RES3 series resistance. */
  emuBuPwrRes_Res3 = EMU_BUCTRL_PWRRES_RES3,
} EMU_BUPwrRes_TypeDef;
#endif

#if defined(_EMU_BUCTRL_VOUTRES_MASK)
/** Resistance between backup domain power supply and BU_VOUT. */
typedef enum {
  /** BU_VOUT is not connected. */
  emuBuVoutRes_Dis = EMU_BUCTRL_VOUTRES_DIS,
  /** Enable weak switch. */
  emuBuVoutRes_Weak = EMU_BUCTRL_VOUTRES_WEAK,
  /** Enable medium switch. */
  emuBuVoutRes_Med = EMU_BUCTRL_VOUTRES_MED,
  /** Enable strong switch. */
  emuBuVoutRes_Strong = EMU_BUCTRL_VOUTRES_STRONG,
} EMU_BUVoutRes_TypeDef;
#endif

/** BOD threshold setting selector, active or inactive mode. */
typedef enum {
  /** Configure BOD threshold for active mode. */
  emuBODMode_Active,
  /** Configure BOD threshold for inactive mode. */
  emuBODMode_Inactive,
} EMU_BODMode_TypeDef;

/** EM4 modes. */
typedef enum {
  /** EM4 Shutoff. */
  emuEM4Shutoff   = 0,
  /** EM4 Hibernate. */
  emuEM4Hibernate = 1,
} EMU_EM4State_TypeDef;

#if defined(_EMU_EM4CTRL_EM4IORETMODE_MASK)
typedef enum {
  /** No Retention: Pads enter reset state when entering EM4. */
  emuPinRetentionDisable = EMU_EM4CTRL_EM4IORETMODE_DISABLE,
  /** Retention through EM4: Pads enter reset state when exiting EM4. */
  emuPinRetentionEm4Exit = EMU_EM4CTRL_EM4IORETMODE_EM4EXIT,
  /** Retention through EM4 and wakeup: call @ref EMU_UnlatchPinRetention() to
      release pins from retention after EM4 wakeup. */
  emuPinRetentionLatch   = EMU_EM4CTRL_EM4IORETMODE_SWUNLATCH,
} EMU_EM4PinRetention_TypeDef;
#endif

/** Power configurations. DCDC-to-DVDD is currently the only supported mode. */
typedef enum {
  /** DCDC is connected to DVDD. */
  emuPowerConfig_DcdcToDvdd,
} EMU_PowerConfig_TypeDef;

#if defined(_EMU_DCDCCTRL_MASK)
/** DCDC operating modes. */
typedef enum {
  /** DCDC regulator bypass. */
  emuDcdcMode_Bypass = EMU_DCDCCTRL_DCDCMODE_BYPASS,
  /** DCDC low-noise mode. */
  emuDcdcMode_LowNoise = EMU_DCDCCTRL_DCDCMODE_LOWNOISE,
#if defined(_EMU_DCDCLPEM01CFG_MASK)
  /** DCDC low-power mode. */
  emuDcdcMode_LowPower = EMU_DCDCCTRL_DCDCMODE_LOWPOWER,
#endif
} EMU_DcdcMode_TypeDef;
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/** DCDC conduction modes. */
typedef enum {
  /** DCDC Low-Noise Continuous Conduction Mode (CCM). EFR32 interference minimization
      features are available in this mode. */
  emuDcdcConductionMode_ContinuousLN,
  /** DCDC Low-Noise Discontinuous Conduction Mode (DCM). This mode should be used for EFM32 or
      for EFR32 when its radio is not enabled. */
  emuDcdcConductionMode_DiscontinuousLN,
} EMU_DcdcConductionMode_TypeDef;
#endif

#if defined(_EMU_PWRCTRL_MASK)
/** DCDC to DVDD mode analog peripheral power supply select. */
typedef enum {
  /** Select AVDD as analog power supply. Typically lower noise, but less energy efficient. */
  emuDcdcAnaPeripheralPower_AVDD = EMU_PWRCTRL_ANASW_AVDD,
  /** Select DCDC (DVDD) as analog power supply. Typically more energy efficient, but more noise. */
  emuDcdcAnaPeripheralPower_DCDC = EMU_PWRCTRL_ANASW_DVDD
} EMU_DcdcAnaPeripheralPower_TypeDef;
#endif

#if defined(_EMU_DCDCMISCCTRL_MASK)
/** DCDC Forced CCM and reverse current limiter control. Positive values have unit mA. */
typedef int16_t EMU_DcdcLnReverseCurrentControl_TypeDef;

/** High efficiency mode. EMU_DCDCZDETCTRL_ZDETILIMSEL is "don't care". */
#define emuDcdcLnHighEfficiency       -1

/** Default reverse current for fast transient response mode (low noise).  */
#define emuDcdcLnFastTransient         160
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/** DCDC Low-noise RCO band select. */
typedef enum {
  /** Set RCO to 3MHz. */
  emuDcdcLnRcoBand_3MHz = 0,
  /** Set RCO to 4MHz. */
  emuDcdcLnRcoBand_4MHz = 1,
  /** Set RCO to 5MHz. */
  emuDcdcLnRcoBand_5MHz = 2,
  /** Set RCO to 6MHz. */
  emuDcdcLnRcoBand_6MHz = 3,
  /** Set RCO to 7MHz. */
  emuDcdcLnRcoBand_7MHz = 4,
  /** Set RCO to 8MHz. */
  emuDcdcLnRcoBand_8MHz = 5,
  /** Set RCO to 9MHz. */
  emuDcdcLnRcoBand_9MHz = 6,
  /** Set RCO to 10MHz. */
  emuDcdcLnRcoBand_10MHz = 7,
} EMU_DcdcLnRcoBand_TypeDef;

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Deprecated. */
#define EMU_DcdcLnRcoBand_3MHz          emuDcdcLnRcoBand_3MHz
#define EMU_DcdcLnRcoBand_4MHz          emuDcdcLnRcoBand_4MHz
#define EMU_DcdcLnRcoBand_5MHz          emuDcdcLnRcoBand_5MHz
#define EMU_DcdcLnRcoBand_6MHz          emuDcdcLnRcoBand_6MHz
#define EMU_DcdcLnRcoBand_7MHz          emuDcdcLnRcoBand_7MHz
#define EMU_DcdcLnRcoBand_8MHz          emuDcdcLnRcoBand_8MHz
#define EMU_DcdcLnRcoBand_9MHz          emuDcdcLnRcoBand_9MHz
#define EMU_DcdcLnRcoBand_10MHz         emuDcdcLnRcoBand_10MHz
/** @endcond */
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/** DCDC Low Noise Compensator Control register. */
typedef enum {
  /** DCDC capacitor is 1uF. */
  emuDcdcLnCompCtrl_1u0F,
  /** DCDC capacitor is 4.7uF. */
  emuDcdcLnCompCtrl_4u7F,
} EMU_DcdcLnCompCtrl_TypeDef;
#endif

#if defined(_DCDC_CTRL_MASK)
/** DCDC mode. */
typedef enum {
  emuDcdcMode_Bypass,                     /**< DCDC regulator bypass. */
  emuDcdcMode_Regulation                  /**< DCDC regulator on.     */
} EMU_DcdcMode_TypeDef;

/** VREGIN comparator threshold. */
typedef enum {
  emuVreginCmpThreshold_2v0 = 0,          /**< Comparator threshold is 2.0V. */
  emuVreginCmpThreshold_2v1 = 1,          /**< Comparator threshold is 2.1V. */
  emuVreginCmpThreshold_2v2 = 2,          /**< Comparator threshold is 2.2V. */
  emuVreginCmpThreshold_2v3 = 3           /**< Comparator threshold is 2.3V. */
} EMU_VreginCmpThreshold_TypeDef;

/** DCDC Ton max timeout. */
typedef enum {
  emuDcdcTonMaxTimeout_Off    = _DCDC_CTRL_IPKTMAXCTRL_OFF,         /**< Ton max off.       */
  emuDcdcTonMaxTimeout_0P35us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_0P35us, /**< Ton max is 0.35us. */
  emuDcdcTonMaxTimeout_0P63us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_0P63us, /**< Ton max is 0.63us. */
  emuDcdcTonMaxTimeout_0P91us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_0P91us, /**< Ton max is 0.91us. */
  emuDcdcTonMaxTimeout_1P19us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_1P19us, /**< Ton max is 1.19us. */
  emuDcdcTonMaxTimeout_1P47us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_1P47us, /**< Ton max is 1.47us. */
  emuDcdcTonMaxTimeout_1P75us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_1P75us, /**< Ton max is 1.75us. */
  emuDcdcTonMaxTimeout_2P03us = _DCDC_CTRL_IPKTMAXCTRL_TMAX_2P03us  /**< Ton max is 2.03us. */
} EMU_DcdcTonMaxTimeout_TypeDef;

/** DCDC drive speed. */
typedef enum {
  emuDcdcDriveSpeed_BestEmi        = _DCDC_EM01CTRL0_DRVSPEED_BEST_EMI,        /**< Lowest efficiency, lowest EMI. */
  emuDcdcDriveSpeed_Default        = _DCDC_EM01CTRL0_DRVSPEED_DEFAULT_SETTING, /**< Default efficiency, acceptable EMI level. */
  emuDcdcDriveSpeed_Intermediate   = _DCDC_EM01CTRL0_DRVSPEED_INTERMEDIATE,    /**< Small increase in efficiency from the default setting. */
  emuDcdcDriveSpeed_BestEfficiency = _DCDC_EM01CTRL0_DRVSPEED_BEST_EFFICIENCY  /**< Highest efficiency, highest EMI. Small increase in efficiency from INTERMEDIATE setting. */
} EMU_DcdcDriveSpeed_TypeDef;

/** DCDC peak current setting. */
typedef enum {
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load28mA)
  emuDcdcPeakCurrent_Load28mA = _DCDC_EM01CTRL0_IPKVAL_Load28mA, /**< Load 28mA, peak current 70mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load32mA)
  emuDcdcPeakCurrent_Load32mA = _DCDC_EM01CTRL0_IPKVAL_Load32mA, /**< Load 32mA, peak current 80mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load36mA)
  emuDcdcPeakCurrent_Load36mA = _DCDC_EM01CTRL0_IPKVAL_Load36mA, /**< Load 36mA, peak current 90mA. */
#endif
  emuDcdcPeakCurrent_Load40mA = _DCDC_EM01CTRL0_IPKVAL_Load40mA, /**< Load 40mA, peak current 100mA. */
  emuDcdcPeakCurrent_Load44mA = _DCDC_EM01CTRL0_IPKVAL_Load44mA, /**< Load 44mA, peak current 110mA. */
  emuDcdcPeakCurrent_Load48mA = _DCDC_EM01CTRL0_IPKVAL_Load48mA, /**< Load 48mA, peak current 120mA. */
  emuDcdcPeakCurrent_Load52mA = _DCDC_EM01CTRL0_IPKVAL_Load52mA, /**< Load 52mA, peak current 130mA. */
  emuDcdcPeakCurrent_Load56mA = _DCDC_EM01CTRL0_IPKVAL_Load56mA, /**< Load 56mA, peak current 140mA. */
  emuDcdcPeakCurrent_Load60mA = _DCDC_EM01CTRL0_IPKVAL_Load60mA, /**< Load 60mA, peak current 150mA. */
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load64mA)
  emuDcdcPeakCurrent_Load64mA = _DCDC_EM01CTRL0_IPKVAL_Load64mA, /**< Load 64mA, peak current 160mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load68mA)
  emuDcdcPeakCurrent_Load68mA = _DCDC_EM01CTRL0_IPKVAL_Load68mA, /**< Load 68mA, peak current 170mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load72mA)
  emuDcdcPeakCurrent_Load72mA = _DCDC_EM01CTRL0_IPKVAL_Load72mA, /**< Load 72mA, peak current 180mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load76mA)
  emuDcdcPeakCurrent_Load76mA = _DCDC_EM01CTRL0_IPKVAL_Load76mA, /**< Load 76mA, peak current 190mA. */
#endif
#if defined(_DCDC_EM01CTRL0_IPKVAL_Load80mA)
  emuDcdcPeakCurrent_Load80mA = _DCDC_EM01CTRL0_IPKVAL_Load80mA  /**< Load 80mA, peak current 200mA. */
#endif
} EMU_DcdcPeakCurrent_TypeDef;
#endif

#if defined(EMU_STATUS_VMONRDY)
/** VMON channels. */
typedef enum {
  emuVmonChannel_AVDD,
  emuVmonChannel_ALTAVDD,
  emuVmonChannel_DVDD,
  emuVmonChannel_IOVDD0,
#if defined(_EMU_VMONIO1CTRL_EN_MASK)
  emuVmonChannel_IOVDD1,
#endif
#if defined(_EMU_VMONBUVDDCTRL_EN_MASK)
  emuVmonChannel_BUVDD,
#endif
} EMU_VmonChannel_TypeDef;
#endif /* EMU_STATUS_VMONRDY */

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
/** Bias mode configurations. */
typedef enum {
  emuBiasMode_1KHz,
  emuBiasMode_4KHz,
  emuBiasMode_Continuous
} EMU_BiasMode_TypeDef;
#endif

#if defined(EMU_VSCALE_PRESENT)
/** Supported EM0/1 Voltage Scaling Levels. */
typedef enum {
  /** High-performance voltage level. HF clock can be set to any frequency. */
  emuVScaleEM01_HighPerformance = _EMU_STATUS_VSCALE_VSCALE2,
  /** Low-power optimized voltage level. HF clock must be limited
      to @ref CMU_VSCALEEM01_LOWPOWER_VOLTAGE_CLOCK_MAX Hz at this voltage.
      EM0/1 voltage scaling is applied when core clock frequency is
      changed from @ref CMU or when calling @ref EMU_EM01Init() when HF
      clock is already below the limit. */
#if defined(_SILICON_LABS_32B_SERIES_2)
  /** Minimum VSCALE level in EM0/1 is VSCALE1. */
  emuVScaleEM01_LowPower        = _EMU_STATUS_VSCALE_VSCALE1,
#else
  emuVScaleEM01_LowPower        = _EMU_STATUS_VSCALE_VSCALE0,
#endif
} EMU_VScaleEM01_TypeDef;
#endif

#if defined(EMU_VSCALE_PRESENT)
/** Supported EM2/3 Voltage Scaling Levels. */
typedef enum {
  /** Fast-wakeup voltage level. */
  emuVScaleEM23_FastWakeup      = _EMU_CTRL_EM23VSCALE_VSCALE2,
  /** Low-power optimized voltage level. Using this voltage level in EM2 and 3
      adds approximately 30 us to wakeup time if EM0 and 1 voltage must be scaled
      up to @ref emuVScaleEM01_HighPerformance on EM2 or 3 exit. */
  emuVScaleEM23_LowPower        = _EMU_CTRL_EM23VSCALE_VSCALE0,
} EMU_VScaleEM23_TypeDef;
#endif

#if defined(_EMU_CTRL_EM4HVSCALE_MASK)
/** Supported EM4H Voltage Scaling Levels */
typedef enum {
  /** Fast-wakeup voltage level. */
  emuVScaleEM4H_FastWakeup      = _EMU_CTRL_EM4HVSCALE_VSCALE2,
  /** Low-power optimized voltage level. Using this voltage level in EM4H
      adds approximately 30 us to wakeup time if EM0 and 1 voltage must be scaled
      up to @ref emuVScaleEM01_HighPerformance on EM4H exit. */
  emuVScaleEM4H_LowPower        = _EMU_CTRL_EM4HVSCALE_VSCALE0,
} EMU_VScaleEM4H_TypeDef;
#endif

#if defined(_EMU_EM23PERNORETAINCTRL_MASK)
/** Peripheral EM2 and 3 retention control. */
typedef enum {
#if defined(_EMU_EM23PERNORETAINCTRL_USBDIS_MASK)
  emuPeripheralRetention_USB      = _EMU_EM23PERNORETAINCTRL_USBDIS_MASK,       /* Select USB retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_RTCDIS_MASK)
  emuPeripheralRetention_RTC      = _EMU_EM23PERNORETAINCTRL_RTCDIS_MASK,       /* Select RTC retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ACMP3DIS_MASK)
  emuPeripheralRetention_ACMP3    = _EMU_EM23PERNORETAINCTRL_ACMP3DIS_MASK,     /* Select ACMP3 retention control. */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ACMP2DIS_MASK)
  emuPeripheralRetention_ACMP2    = _EMU_EM23PERNORETAINCTRL_ACMP2DIS_MASK,     /* Select ACMP2 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ADC1DIS_MASK)
  emuPeripheralRetention_ADC1     = _EMU_EM23PERNORETAINCTRL_ADC1DIS_MASK,      /* Select ADC1 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_I2C2DIS_MASK)
  emuPeripheralRetention_I2C2     = _EMU_EM23PERNORETAINCTRL_I2C2DIS_MASK,      /* Select I2C2 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LETIMER1DIS_MASK)
  emuPeripheralRetention_LETIMER1 = _EMU_EM23PERNORETAINCTRL_LETIMER1DIS_MASK,  /* Select LETIMER1 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LCDDIS_MASK)
  emuPeripheralRetention_LCD      = _EMU_EM23PERNORETAINCTRL_LCDDIS_MASK,       /* Select LCD retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LEUART1DIS_MASK)
  emuPeripheralRetention_LEUART1  = _EMU_EM23PERNORETAINCTRL_LEUART1DIS_MASK,   /* Select LEUART1 retention control.  */
#endif
  emuPeripheralRetention_LEUART0  = _EMU_EM23PERNORETAINCTRL_LEUART0DIS_MASK,   /* Select LEUART0 retention control.  */
#if defined(_EMU_EM23PERNORETAINCTRL_CSENDIS_MASK)
  emuPeripheralRetention_CSEN     = _EMU_EM23PERNORETAINCTRL_CSENDIS_MASK,      /* Select CSEN retention control.  */
#endif
  emuPeripheralRetention_LESENSE0 = _EMU_EM23PERNORETAINCTRL_LESENSE0DIS_MASK,  /* Select LESENSE0 retention control.  */
#if defined(_EMU_EM23PERNORETAINCTRL_WDOG1DIS_MASK)
  emuPeripheralRetention_WDOG1    = _EMU_EM23PERNORETAINCTRL_WDOG1DIS_MASK,     /* Select WDOG1 retention control.  */
#endif
  emuPeripheralRetention_WDOG0    = _EMU_EM23PERNORETAINCTRL_WDOG0DIS_MASK,     /* Select WDOG0 retention control.  */
  emuPeripheralRetention_LETIMER0 = _EMU_EM23PERNORETAINCTRL_LETIMER0DIS_MASK,  /* Select LETIMER0 retention control.  */
  emuPeripheralRetention_ADC0     = _EMU_EM23PERNORETAINCTRL_ADC0DIS_MASK,      /* Select ADC0 retention control.  */
#if defined(_EMU_EM23PERNORETAINCTRL_IDAC0DIS_MASK)
  emuPeripheralRetention_IDAC0    = _EMU_EM23PERNORETAINCTRL_IDAC0DIS_MASK,     /* Select IDAC0 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_VDAC0DIS_MASK)
  emuPeripheralRetention_VDAC0    = _EMU_EM23PERNORETAINCTRL_VDAC0DIS_MASK,     /* Select VDAC0 retention control.  */
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_I2C1DIS_MASK)
  emuPeripheralRetention_I2C1     = _EMU_EM23PERNORETAINCTRL_I2C1DIS_MASK,      /* Select I2C1 retention control.  */
#endif
  emuPeripheralRetention_I2C0     = _EMU_EM23PERNORETAINCTRL_I2C0DIS_MASK,      /* Select I2C0 retention control.  */
  emuPeripheralRetention_ACMP1    = _EMU_EM23PERNORETAINCTRL_ACMP1DIS_MASK,     /* Select ACMP1 retention control.  */
  emuPeripheralRetention_ACMP0    = _EMU_EM23PERNORETAINCTRL_ACMP0DIS_MASK,     /* Select ACMP0 retention control.  */
#if defined(_EMU_EM23PERNORETAINCTRL_PCNT1DIS_MASK)
  emuPeripheralRetention_PCNT2    = _EMU_EM23PERNORETAINCTRL_PCNT2DIS_MASK,     /* Select PCNT2 retention control.  */
  emuPeripheralRetention_PCNT1    = _EMU_EM23PERNORETAINCTRL_PCNT1DIS_MASK,     /* Select PCNT1 retention control.  */
#endif
  emuPeripheralRetention_PCNT0    = _EMU_EM23PERNORETAINCTRL_PCNT0DIS_MASK,     /* Select PCNT0 retention control.  */

  emuPeripheralRetention_D1       = _EMU_EM23PERNORETAINCTRL_LETIMER0DIS_MASK
                                    | _EMU_EM23PERNORETAINCTRL_PCNT0DIS_MASK
                                    | _EMU_EM23PERNORETAINCTRL_ADC0DIS_MASK
                                    | _EMU_EM23PERNORETAINCTRL_ACMP0DIS_MASK
                                    | _EMU_EM23PERNORETAINCTRL_LESENSE0DIS_MASK,/* Select all peripherals in domain 1. */
  emuPeripheralRetention_D2       = _EMU_EM23PERNORETAINCTRL_ACMP1DIS_MASK
#if defined(_EMU_EM23PERNORETAINCTRL_IDAC0DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_IDAC0DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_VDAC0DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_VDAC0DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_CSENDIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_CSENDIS_MASK
#endif
                                    | _EMU_EM23PERNORETAINCTRL_LEUART0DIS_MASK
#if defined(_EMU_EM23PERNORETAINCTRL_USBDIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_USBDIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_RTCDIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_RTCDIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ACMP3DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_ACMP3DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ACMP2DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_ACMP2DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_ADC1DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_ADC1DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_I2C2DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_I2C2DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LETIMER1DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_LETIMER1DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LCDDIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_LCDDIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_LEUART1DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_LEUART1DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_PCNT1DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_PCNT1DIS_MASK
                                    | _EMU_EM23PERNORETAINCTRL_PCNT2DIS_MASK
#endif
#if defined(_EMU_EM23PERNORETAINCTRL_I2C1DIS_MASK)
                                    | _EMU_EM23PERNORETAINCTRL_I2C1DIS_MASK    /* Select all peripherals in domain 2. */
#endif
                                    | _EMU_EM23PERNORETAINCTRL_I2C0DIS_MASK,
  emuPeripheralRetention_ALL       = emuPeripheralRetention_D1
                                     | emuPeripheralRetention_D2
#if defined(_EMU_EM23PERNORETAINCTRL_WDOG1DIS_MASK)
                                     | emuPeripheralRetention_WDOG1
#endif
                                     | emuPeripheralRetention_WDOG0,            /* Select all peripherals with retention control.  */
} EMU_PeripheralRetention_TypeDef;
#endif

#if defined(_EMU_TEMP_TEMPAVG_MASK)
/** Number of samples to use for temperature averaging. */
typedef enum {
  /** 16 samples used for temperature averaging. */
  emuTempAvgNum_16      = _EMU_CTRL_TEMPAVGNUM_N16,
  /** 64 samples used for temperature averaging. */
  emuTempAvgNum_64      = _EMU_CTRL_TEMPAVGNUM_N64,
} EMU_TempAvgNum_TypeDef;
#endif

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

#if defined(EMU_VSCALE_PRESENT)
/** EM0 and 1 initialization structure. Voltage scaling is applied when
    the core clock frequency is changed from @ref CMU. EM0 and 1 emuVScaleEM01_HighPerformance
    is always enabled. */
typedef struct {
  bool  vScaleEM01LowPowerVoltageEnable;                 /**< EM0/1 low power voltage status. */
} EMU_EM01Init_TypeDef;
#endif

#if defined(EMU_VSCALE_PRESENT)
/** Default initialization of EM0 and 1 configuration. */
#define EMU_EM01INIT_DEFAULT                                                               \
  {                                                                                        \
    false                                                /** Do not scale down in EM0/1.*/ \
  }
#endif

/** EM2 and 3 initialization structure.  */
typedef struct {
  bool                          em23VregFullEn;         /**< Enable full VREG drive strength in EM2/3. */
#if defined(EMU_VSCALE_PRESENT)
  EMU_VScaleEM23_TypeDef        vScaleEM23Voltage;      /**< EM2/3 voltage scaling level. */
#endif
} EMU_EM23Init_TypeDef;

/** Default initialization of EM2 and 3 configuration. */
#if defined(EMU_VSCALE_PRESENT)
#define EMU_EM23INIT_DEFAULT                                                                                    \
  {                                                                                                             \
    false,                                              /* Reduced voltage regulator drive strength in EM2/3.*/ \
    emuVScaleEM23_FastWakeup,                           /* Do not scale down in EM2/3. */                       \
  }
#else
#define EMU_EM23INIT_DEFAULT                                                                                    \
  {                                                                                                             \
    false,                                              /* Reduced voltage regulator drive strength in EM2/3.*/ \
  }
#endif

#if defined(_EMU_EM4CONF_MASK) || defined(_EMU_EM4CTRL_MASK)
/** EM4 initialization structure.  */
typedef struct {
#if defined(_EMU_EM4CONF_MASK)
  /* Initialization parameters for platforms with EMU->EM4CONF register (Series 0). */
  bool                        lockConfig;       /**< Lock configuration of regulator, BOD and oscillator. */
  bool                        buBodRstDis;      /**< When set, no reset will be asserted due to Brownout when in EM4. */
  EMU_EM4Osc_TypeDef          osc;              /**< EM4 duty oscillator. */
  bool                        buRtcWakeup;      /**< Wake up on EM4 BURTC interrupt. */
  bool                        vreg;             /**< Enable EM4 voltage regulator. */
#elif defined(_EMU_EM4CTRL_MASK)
  /* Initialization parameters for platforms with EMU->EM4CTRL register (Series 1). */
  bool                        retainLfxo;       /**< Disable LFXO upon EM4 entry. */
  bool                        retainLfrco;      /**< Disable LFRCO upon EM4 entry. */
  bool                        retainUlfrco;     /**< Disable ULFRCO upon EM4 entry. */
  EMU_EM4State_TypeDef        em4State;         /**< Hibernate or shutoff EM4 state. */
  EMU_EM4PinRetention_TypeDef pinRetentionMode; /**< EM4 pin retention mode. */
#endif
#if defined(_EMU_CTRL_EM4HVSCALE_MASK)
  EMU_VScaleEM4H_TypeDef      vScaleEM4HVoltage;/**< EM4H voltage scaling level. */
#endif
} EMU_EM4Init_TypeDef;
#endif

#if defined(_EMU_EM4CONF_MASK)
/** Default initialization of EM4 configuration (Series 0). */
#define EMU_EM4INIT_DEFAULT                                                                \
  {                                                                                        \
    false,                            /* Do not lock configuration after it's been set. */ \
    false,                            /* No reset will be asserted due to BOD in EM4. */   \
    emuEM4Osc_ULFRCO,                 /* Use default ULFRCO oscillator.  */                \
    true,                             /* Wake up on EM4 BURTC interrupt. */                \
    true,                             /* Enable VREG. */                                   \
  }

#elif defined(_EMU_CTRL_EM4HVSCALE_MASK)
/** Default initialization of EM4 configuration (Series 1 with VSCALE). */
#define EMU_EM4INIT_DEFAULT                                                            \
  {                                                                                    \
    false,                           /* Retain LFXO configuration upon EM4 entry. */   \
    false,                           /* Retain LFRCO configuration upon EM4 entry. */  \
    false,                           /* Retain ULFRCO configuration upon EM4 entry. */ \
    emuEM4Shutoff,                   /* Use EM4 shutoff state. */                      \
    emuPinRetentionDisable,          /* Do not retain pins in EM4. */                  \
    emuVScaleEM4H_FastWakeup,        /* Do not scale down in EM4H. */                  \
  }

#elif defined(_EMU_EM4CTRL_MASK)
/** Default initialization of EM4 configuration (Series 1 without VSCALE). */
#define EMU_EM4INIT_DEFAULT                                                            \
  {                                                                                    \
    false,                           /* Retain LFXO configuration upon EM4 entry. */   \
    false,                           /* Retain LFRCO configuration upon EM4 entry. */  \
    false,                           /* Retain ULFRCO configuration upon EM4 entry. */ \
    emuEM4Shutoff,                   /* Use EM4 shutoff state. */                      \
    emuPinRetentionDisable,          /* Do not retain pins in EM4. */                  \
  }
#endif

#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_0)
/** Backup Power Domain Initialization structure. */
typedef struct {
  /* Backup Power Domain power configuration. */

  /** Voltage probe select, selects ADC voltage. */
  EMU_Probe_TypeDef     probe;
  /** Enable BOD calibration mode. */
  bool                  bodCal;
  /** Enable BU_STAT status pin for active BU mode. */
  bool                  statusPinEnable;

  /* Backup Power Domain connection configuration. */
  /** Power domain resistor. */
  EMU_Resistor_TypeDef  resistor;
  /** BU_VOUT strong enable. */
  bool                  voutStrong;
  /** BU_VOUT medium enable. */
  bool                  voutMed;
  /** BU_VOUT weak enable. */
  bool                  voutWeak;
  /** Power connection, when not in Backup Mode. */
  EMU_Power_TypeDef  inactivePower;
  /** Power connection, when in Backup Mode. */
  EMU_Power_TypeDef     activePower;
  /** Enable backup power domain, and release reset, enable BU_VIN pin.  */
  bool                  enable;
} EMU_BUPDInit_TypeDef;

/** Default Backup Power Domain configuration. */
#define EMU_BUPDINIT_DEFAULT                                                              \
  {                                                                                       \
    emuProbe_Disable, /* Do not enable voltage probe. */                                  \
    false,          /* Disable BOD calibration mode. */                                   \
    false,          /* Disable BU_STAT pin for backup mode indication. */                 \
                                                                                          \
    emuRes_Res0,    /* RES0 series resistance between main and backup power. */           \
    false,          /* Do not enable strong switch. */                                    \
    false,          /* Do not enable medium switch. */                                    \
    false,          /* Do not enable weak switch. */                                      \
                                                                                          \
    emuPower_None,  /* No connection between main and backup power. (inactive mode) */    \
    emuPower_None,  /* No connection between main and backup power. (active mode) */      \
    true            /* Enable BUPD enter on BOD, enable BU_VIN pin, release BU reset.  */ \
  }
#endif

#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_1)
/** Backup Power Domain Initialization structure. */
typedef struct {
  bool disMaxComp;                            /**< Disable MAIN-BU Comparator. */
  EMU_BUBuInactPwrCon_TypeDef inactivePwrCon; /**< Power connection configuration when not in backup mode. */
  EMU_BUBuActPwrCon_TypeDef activePwrCon;     /**< Power connection configuration when in backup mode. */
  EMU_BUPwrRes_TypeDef pwrRes;                /**< Power domain resistor. */
  EMU_BUVoutRes_TypeDef voutRes;              /**< BU_VOUT resistor select. */
  bool buVinProbeEn;                          /**< Enable BU_VIN probing. */
  bool staEn;                                 /**< Enable backup mode status export. */
  bool enable;                                /**< Enable backup power domain. */
} EMU_BUInit_TypeDef;

/** Default Backup Power Domain configuration. */
#define EMU_BUINIT_DEFAULT                                                                 \
  {                                                                                        \
    false,                   /**< MAIN-BU Comparator is not disabloed */                   \
    emuBuBuInactPwrCon_None, /**< No power connection wen not in backup mode */            \
    emuBuBuActPwrCon_None,   /**< No power connection when in backup mode */               \
    emuBuPwrRes_Res0,        /**< RES0 series resistance between main and backup power. */ \
    emuBuVoutRes_Dis,        /**< Vout resistor is set to not connected */                 \
    false,                   /**< BU_VIN probe is disabled */                              \
    false,                   /**< Status export is disabled */                             \
    true                     /**< Enable backup mode */                                    \
  }
#endif

#if defined(_DCDC_CTRL_MASK)
/** DCDC regulator initialization structure. */
typedef struct {
  EMU_DcdcMode_TypeDef            mode;             /**< DCDC mode. */
  EMU_VreginCmpThreshold_TypeDef  cmpThreshold;     /**< VREGIN comparator threshold. */
  EMU_DcdcTonMaxTimeout_TypeDef   tonMax;           /**< Ton max timeout control. */
  bool                            dcmOnlyEn;        /**< DCM only mode enable. */
  EMU_DcdcDriveSpeed_TypeDef      driveSpeedEM01;   /**< DCDC drive speed in EM0/1. */
  EMU_DcdcDriveSpeed_TypeDef      driveSpeedEM23;   /**< DCDC drive speed in EM2/3. */
  EMU_DcdcPeakCurrent_TypeDef     peakCurrentEM01;  /**< EM0/1 peak current setting. */
  EMU_DcdcPeakCurrent_TypeDef     peakCurrentEM23;  /**< EM2/3 peak current setting. */
} EMU_DCDCInit_TypeDef;

/** Default DCDC initialization. */
#define EMU_DCDCINIT_DEFAULT                                                \
  {                                                                         \
    emuDcdcMode_Regulation,        /**< DCDC regulator on. */               \
    emuVreginCmpThreshold_2v3,     /**< 2.3V VREGIN comparator treshold. */ \
    emuDcdcTonMaxTimeout_1P19us,   /**< Ton max is 1.19us. */               \
    true,                          /**< Enable DCM only mode. */            \
    emuDcdcDriveSpeed_Default,     /**< Default efficiency in EM0/1. */     \
    emuDcdcDriveSpeed_Default,     /**< Default efficiency in EM2/3. */     \
    emuDcdcPeakCurrent_Load60mA,   /**< Default peak current in EM0/1. */   \
    emuDcdcPeakCurrent_Load36mA    /**< Default peak current in EM2/3. */   \
  }
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/** DCDC initialization structure. */
typedef struct {
  EMU_PowerConfig_TypeDef powerConfig;                  /**< Device external power configuration.
                                                             @ref emuPowerConfig_DcdcToDvdd is currently the only supported mode. */
  EMU_DcdcMode_TypeDef dcdcMode;                        /**< DCDC regulator operating mode in EM0/1. */
  uint16_t mVout;                                       /**< Target output voltage (mV). */
  uint16_t em01LoadCurrent_mA;                          /**< Estimated average load current in EM0/1. (mA).
                                                             This estimate is also used for EM1 optimization;
                                                             if EM1 current is expected to be higher than EM0,
                                                             then this parameter should hold the higher EM1 current. */
  uint16_t em234LoadCurrent_uA;                         /**< Estimated average load current in EM2 (uA).
                                                             This estimate is also used for EM3 and 4 optimization;
                                                             if EM3 or 4 current is expected to be higher than EM2,
                                                             then this parameter should hold the higher EM3 or 4 current. */
  uint16_t maxCurrent_mA;                               /**< Maximum average DCDC output current (mA).
                                                             This can be set to the maximum for the power source,
                                                             for example the maximum for a battery. */
  EMU_DcdcAnaPeripheralPower_TypeDef
    anaPeripheralPower;                                 /**< Select analog peripheral power in DCDC-to-DVDD mode. */
  EMU_DcdcLnReverseCurrentControl_TypeDef
    reverseCurrentControl;                              /**< Low-noise reverse current control.
                                                             NOTE: this parameter uses special encoding:
                                                             >= 0 is forced CCM mode where the parameter is used as the
                                                                  reverse current threshold in mA.
                                                             -1   is encoded as emuDcdcLnHighEfficiencyMode (EFM32 only). */
  EMU_DcdcLnCompCtrl_TypeDef dcdcLnCompCtrl;            /**< DCDC Low-noise mode compensator control. */
} EMU_DCDCInit_TypeDef;

/** Default DCDC initialization. */
#if defined(_EFM_DEVICE)
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define EMU_DCDCINIT_DEFAULT                                                         \
  {                                                                                  \
    emuPowerConfig_DcdcToDvdd,   /* DCDC to DVDD. */                                 \
    emuDcdcMode_LowNoise,        /* Low-noise mode in EM0. */                        \
    1800,                        /* Nominal output voltage for DVDD mode, 1.8V.  */  \
    5,                           /* Nominal EM0/1 load current of less than 5mA. */  \
    10,                          /* Nominal EM2/3/4 load current less than 10uA.  */ \
    200,                         /* Maximum average current of 200mA
                                    (assume strong battery or other power source). */      \
    emuDcdcAnaPeripheralPower_DCDC,/* Select DCDC as analog power supply (lower power). */ \
    emuDcdcLnHighEfficiency,     /* Use high-efficiency mode. */                           \
    emuDcdcLnCompCtrl_1u0F,      /* 1uF DCDC capacitor. */                                 \
  }
#else
#define EMU_DCDCINIT_DEFAULT                                                         \
  {                                                                                  \
    emuPowerConfig_DcdcToDvdd,   /* DCDC to DVDD. */                                 \
    emuDcdcMode_LowPower,        /* Low-power mode in EM0. */                        \
    1800,                        /* Nominal output voltage for DVDD mode, 1.8V.  */  \
    5,                           /* Nominal EM0/1 load current of less than 5mA. */  \
    10,                          /* Nominal EM2/3/4 load current less than 10uA.  */ \
    200,                         /* Maximum average current of 200mA
                                    (assume strong battery or other power source). */ \
    emuDcdcAnaPeripheralPower_AVDD,/* Select AVDD as analog power supply). */         \
    emuDcdcLnHighEfficiency,     /* Use high-efficiency mode. */                      \
    emuDcdcLnCompCtrl_4u7F,      /* 4.7uF DCDC capacitor. */                          \
  }
#endif

#else /* EFR32 device. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define EMU_DCDCINIT_DEFAULT                                                         \
  {                                                                                  \
    emuPowerConfig_DcdcToDvdd,   /* DCDC to DVDD. */                                 \
    emuDcdcMode_LowNoise,        /* Low-noise mode in EM0. */                        \
    1800,                        /* Nominal output voltage for DVDD mode, 1.8V.  */  \
    15,                          /* Nominal EM0/1 load current of less than 15mA. */ \
    10,                          /* Nominal EM2/3/4 load current less than 10uA.  */ \
    200,                         /* Maximum average current of 200mA
                                    (assume strong battery or other power source). */      \
    emuDcdcAnaPeripheralPower_DCDC,/* Select DCDC as analog power supply (lower power). */ \
    160,                         /* Maximum reverse current of 160mA. */                   \
    emuDcdcLnCompCtrl_1u0F,      /* 1uF DCDC capacitor. */                                 \
  }
#else
#define EMU_DCDCINIT_DEFAULT                                                         \
  {                                                                                  \
    emuPowerConfig_DcdcToDvdd,   /* DCDC to DVDD. */                                 \
    emuDcdcMode_LowNoise,        /* Low-noise mode in EM0. */                        \
    1800,                        /* Nominal output voltage for DVDD mode, 1.8V.  */  \
    15,                          /* Nominal EM0/1 load current of less than 15mA. */ \
    10,                          /* Nominal EM2/3/4 load current less than 10uA.  */ \
    200,                         /* Maximum average current of 200mA
                                    (assume strong battery or other power source). */      \
    emuDcdcAnaPeripheralPower_DCDC,/* Select DCDC as analog power supply (lower power). */ \
    160,                         /* Maximum reverse current of 160mA. */                   \
    emuDcdcLnCompCtrl_4u7F,      /* 4.7uF DCDC capacitor. */                               \
  }
#endif
#endif
#endif

#if defined(EMU_STATUS_VMONRDY)
/** VMON initialization structure. */
typedef struct {
  EMU_VmonChannel_TypeDef channel;      /**< VMON channel to configure. */
  int threshold;                        /**< Trigger threshold (mV). Supported range is 1620 mV to 3400 mV. */
  bool riseWakeup;                      /**< Wake up from EM4H on rising edge. */
  bool fallWakeup;                      /**< Wake up from EM4H on falling edge. */
  bool enable;                          /**< Enable VMON channel. */
  bool retDisable;                      /**< Disable IO0 retention when voltage drops below threshold (IOVDD only). */
} EMU_VmonInit_TypeDef;

/** Default VMON initialization structure. */
#define EMU_VMONINIT_DEFAULT                                                         \
  {                                                                                  \
    emuVmonChannel_AVDD,                /* AVDD VMON channel. */                     \
    3200,                               /* 3.2 V threshold. */                       \
    false,                              /* Do not wake from EM4H on rising edge. */  \
    false,                              /* Do not wake from EM4H on falling edge. */ \
    true,                               /* Enable VMON channel. */                   \
    false                               /* Do not disable IO0 retention  */          \
  }

/** VMON Hysteresis initialization structure. */
typedef struct {
  EMU_VmonChannel_TypeDef channel;      /**< VMON channel to configure. */
  int riseThreshold;                    /**< Rising threshold (mV). */
  int fallThreshold;                    /**< Falling threshold (mV). */
  bool riseWakeup;                      /**< Wake up from EM4H on rising edge. */
  bool fallWakeup;                      /**< Wake up from EM4H on falling edge. */
  bool enable;                          /**< Enable VMON channel. */
} EMU_VmonHystInit_TypeDef;

/** Default VMON Hysteresis initialization structure. */
#define EMU_VMONHYSTINIT_DEFAULT                                                     \
  {                                                                                  \
    emuVmonChannel_AVDD,                /* AVDD VMON channel. */                     \
    3200,                               /* 3.2 V rise threshold. */                  \
    3200,                               /* 3.2 V fall threshold. */                  \
    false,                              /* Do not wake from EM4H on rising edge. */  \
    false,                              /* Do not wake from EM4H on falling edge. */ \
    true                                /* Enable VMON channel. */                   \
  }
#endif /* EMU_STATUS_VMONRDY */

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

#if defined(EMU_VSCALE_PRESENT)
void EMU_EM01Init(const EMU_EM01Init_TypeDef *em01Init);
#endif
void EMU_EM23Init(const EMU_EM23Init_TypeDef *em23Init);
void EMU_EM23PresleepHook(void);
void EMU_EM23PostsleepHook(void);
#if defined(_EMU_EM4CONF_MASK) || defined(_EMU_EM4CTRL_MASK)
void EMU_EM4Init(const EMU_EM4Init_TypeDef *em4Init);
#endif
void EMU_EnterEM2(bool restore);
void EMU_EnterEM3(bool restore);
void EMU_Save(void);
void EMU_Restore(void);
void EMU_EnterEM4(void);
#if defined(_EMU_EM4CTRL_MASK)
void EMU_EnterEM4H(void);
void EMU_EnterEM4S(void);
#endif
void EMU_MemPwrDown(uint32_t blocks);
void EMU_RamPowerDown(uint32_t start, uint32_t end);
void EMU_RamPowerUp(void);
#if defined(_EMU_EM23PERNORETAINCTRL_MASK)
void EMU_PeripheralRetention(EMU_PeripheralRetention_TypeDef periMask, bool enable);
#endif
void EMU_UpdateOscConfig(void);
#if defined(EMU_VSCALE_PRESENT)
void EMU_VScaleEM01ByClock(uint32_t clockFrequency, bool wait);
void EMU_VScaleEM01(EMU_VScaleEM01_TypeDef voltage, bool wait);
#endif
#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_0)
void EMU_BUPDInit(const EMU_BUPDInit_TypeDef *bupdInit);
void EMU_BUThresholdSet(EMU_BODMode_TypeDef mode, uint32_t value);
void EMU_BUThresRangeSet(EMU_BODMode_TypeDef mode, uint32_t value);
#endif
#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_1)
void EMU_BUInit(const EMU_BUInit_TypeDef *buInit);
#endif
#if defined(_EMU_BUCTRL_DISMAXCOMP_MASK)
void EMU_BUDisMaxCompSet(bool disableMainBuComparator);
#endif
#if defined(_EMU_BUCTRL_BUINACTPWRCON_MASK)
void EMU_BUBuInactPwrConSet(EMU_BUBuInactPwrCon_TypeDef inactPwrCon);
#endif
#if defined(_EMU_BUCTRL_BUACTPWRCON_MASK)
void EMU_BUBuActPwrConSet(EMU_BUBuActPwrCon_TypeDef actPwrCon);
#endif
#if defined(_EMU_BUCTRL_PWRRES_MASK)
void EMU_BUPwrResSet(EMU_BUPwrRes_TypeDef pwrRes);
#endif
#if defined(_EMU_BUCTRL_VOUTRES_MASK)
void EMU_BUVoutResSet(EMU_BUVoutRes_TypeDef resistorSel);
#endif
#if defined(_EMU_BUCTRL_BUVINPROBEEN_MASK)
void EMU_BUBuVinProbeEnSet(bool enable);
#endif
#if defined(_EMU_BUCTRL_STATEN_MASK)
void EMU_BUStatEnSet(bool enable);
#endif
#if defined(_EMU_BUCTRL_EN_MASK)
void EMU_BUEnableSet(bool enable);
#endif
#if defined(_EMU_DCDCCTRL_MASK) || defined(_DCDC_CTRL_MASK)
bool EMU_DCDCInit(const EMU_DCDCInit_TypeDef *dcdcInit);
void EMU_DCDCModeSet(EMU_DcdcMode_TypeDef dcdcMode);
bool EMU_DCDCPowerOff(void);
#if !defined(_DCDC_CTRL_MASK)
void EMU_DCDCConductionModeSet(EMU_DcdcConductionMode_TypeDef conductionMode, bool rcoDefaultSet);
bool EMU_DCDCOutputVoltageSet(uint32_t mV, bool setLpVoltage, bool setLnVoltage);
void EMU_DCDCOptimizeSlice(uint32_t em0LoadCurrentmA);
void EMU_DCDCLnRcoBandSet(EMU_DcdcLnRcoBand_TypeDef band);
#endif
#endif
#if defined(EMU_STATUS_VMONRDY)
void EMU_VmonInit(const EMU_VmonInit_TypeDef *vmonInit);
void EMU_VmonHystInit(const EMU_VmonHystInit_TypeDef *vmonInit);
void EMU_VmonEnable(EMU_VmonChannel_TypeDef channel, bool enable);
bool EMU_VmonChannelStatusGet(EMU_VmonChannel_TypeDef channel);
#endif
#if defined(_EMU_TEMP_TEMP_MASK)
float EMU_TemperatureGet(void);
#endif

#if ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER
#if defined(_DCDC_CTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Lock DCDC registers in order to protect them against unintended
 *   modification.
 ******************************************************************************/
__STATIC_INLINE void EMU_DCDCLock(void)
{
  DCDC->LOCK = ~DCDC_LOCK_LOCKKEY_UNLOCKKEY;
}

/***************************************************************************//**
 * @brief
 *   Unlock the DCDCU so that writing to locked registers again is possible.
 ******************************************************************************/
__STATIC_INLINE void EMU_DCDCUnlock(void)
{
  DCDC->LOCK = DCDC_LOCK_LOCKKEY_UNLOCKKEY;
}
#endif

#if defined(_SILICON_LABS_32B_SERIES_1)
/***************************************************************************//**
 * @brief
 *   Check status of the internal LDO regulator.
 *
 * @return
 *   Return true if the regulator is on, false if regulator is off.
 ******************************************************************************/
__STATIC_INLINE bool EMU_LDOStatusGet(void)
{
  if ((*(volatile uint32_t*)0x400E303C & 0x00000040UL) == 0UL) {
    return true;
  } else {
    return false;
  }
}
#endif

/***************************************************************************//**
 * @brief
 *   Enter energy mode 1 (EM1).
 ******************************************************************************/
__STATIC_INLINE void EMU_EnterEM1(void)
{
  /* Enter sleep mode. */
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}

#if defined(EMU_VSCALE_PRESENT)
/***************************************************************************//**
 * @brief
 *   Wait for voltage scaling to complete.
 ******************************************************************************/
__STATIC_INLINE void EMU_VScaleWait(void)
{
#if defined(_SILICON_LABS_32B_SERIES_1)
  if (EMU_LDOStatusGet() == false) {
    /* Skip waiting if the LDO regulator is turned off. */
    return;
  }
#endif

  while (BUS_RegBitRead(&EMU->STATUS, _EMU_STATUS_VSCALEBUSY_SHIFT) != 0U) {
  }
}
#endif

#if defined(EMU_VSCALE_PRESENT)
/***************************************************************************//**
 * @brief
 *   Get current voltage scaling level.
 *
 * @return
 *    Current voltage scaling level.
 ******************************************************************************/
__STATIC_INLINE EMU_VScaleEM01_TypeDef EMU_VScaleGet(void)
{
  EMU_VScaleWait();
  return (EMU_VScaleEM01_TypeDef)((uint32_t)
                                  ((EMU->STATUS & _EMU_STATUS_VSCALE_MASK)
                                   >> _EMU_STATUS_VSCALE_SHIFT));
}
#endif

#if defined(_EMU_STATUS_VMONRDY_MASK)
/***************************************************************************//**
 * @brief
 *   Get the status of the voltage monitor (VMON).
 *
 * @return
 *   Status of the VMON. True if all the enabled channels are ready, false if
 *   one or more of the enabled channels are not ready.
 ******************************************************************************/
__STATIC_INLINE bool EMU_VmonStatusGet(void)
{
  return BUS_RegBitRead(&EMU->STATUS, _EMU_STATUS_VMONRDY_SHIFT) != 0U;
}
#endif /* _EMU_STATUS_VMONRDY_MASK */

#if defined(_EMU_IF_MASK)
/***************************************************************************//**
 * @brief
 *   Clear one or more pending EMU interrupts.
 *
 * @param[in] flags
 *   Pending EMU interrupt sources to clear. Use one or more valid
 *   interrupt flags for the EMU module (EMU_IFC_nnn).
 ******************************************************************************/
__STATIC_INLINE void EMU_IntClear(uint32_t flags)
{
#if defined(EMU_HAS_SET_CLEAR)
  EMU->IF_CLR = flags;
#else
  EMU->IFC = flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Disable one or more EMU interrupts.
 *
 * @param[in] flags
 *   EMU interrupt sources to disable. Use one or more valid
 *   interrupt flags for the EMU module (EMU_IEN_nnn).
 ******************************************************************************/
__STATIC_INLINE void EMU_IntDisable(uint32_t flags)
{
#if defined(EMU_HAS_SET_CLEAR)
  EMU->IEN_CLR = flags;
#else
  EMU->IEN &= ~flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Enable one or more EMU interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. To ignore a pending interrupt, consider using
 *   @ref EMU_IntClear() prior to enabling the interrupt.
 *
 * @param[in] flags
 *   EMU interrupt sources to enable. Use one or more valid
 *   interrupt flags for the EMU module (EMU_IEN_nnn).
 ******************************************************************************/
__STATIC_INLINE void EMU_IntEnable(uint32_t flags)
{
#if defined(EMU_HAS_SET_CLEAR)
  EMU->IEN_SET = flags;
#else
  EMU->IEN |= flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Get pending EMU interrupt flags.
 *
 * @note
 *   Event bits are not cleared by the use of this function.
 *
 * @return
 *   EMU interrupt sources pending. Returns one or more valid
 *   interrupt flags for the EMU module (EMU_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t EMU_IntGet(void)
{
  return EMU->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending EMU interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled EMU interrupt sources
 *   Return value is the bitwise AND of
 *   - the enabled interrupt sources in EMU_IEN and
 *   - the pending interrupt flags EMU_IF.
 ******************************************************************************/
__STATIC_INLINE uint32_t EMU_IntGetEnabled(void)
{
  uint32_t ien;

  ien = EMU->IEN;
  return EMU->IF & ien;
}

/***************************************************************************//**
 * @brief
 *   Set one or more pending EMU interrupts.
 *
 * @param[in] flags
 *   EMU interrupt sources to set to pending. Use one or more valid
 *   interrupt flags for the EMU module (EMU_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void EMU_IntSet(uint32_t flags)
{
#if defined(EMU_HAS_SET_CLEAR)
  EMU->IF_SET = flags;
#else
  EMU->IFS = flags;
#endif
}
#endif /* _EMU_IF_MASK */

#if defined(_EMU_EM4CONF_LOCKCONF_MASK)
/***************************************************************************//**
 * @brief
 *   Enable or disable EM4 lock configuration.
 * @param[in] enable
 *   If true, locks down EM4 configuration.
 ******************************************************************************/
__STATIC_INLINE void EMU_EM4Lock(bool enable)
{
  BUS_RegBitWrite(&(EMU->EM4CONF), _EMU_EM4CONF_LOCKCONF_SHIFT, enable);
}
#endif

#if defined(_EMU_STATUS_BURDY_MASK)
/***************************************************************************//**
 * @brief
 *   Halts until backup power functionality is ready.
 ******************************************************************************/
__STATIC_INLINE void EMU_BUReady(void)
{
  while (!(EMU->STATUS & EMU_STATUS_BURDY))
    ;
}
#endif

#if defined(_EMU_ROUTE_BUVINPEN_MASK)
/***************************************************************************//**
 * @brief
 *   Disable BU_VIN support.
 * @param[in] enable
 *   If true, enables BU_VIN input pin support, if false disables it.
 ******************************************************************************/
__STATIC_INLINE void EMU_BUPinEnable(bool enable)
{
  BUS_RegBitWrite(&(EMU->ROUTE), _EMU_ROUTE_BUVINPEN_SHIFT, enable);
}
#endif

/***************************************************************************//**
 * @brief
 *   Lock EMU registers in order to protect them against unintended
 *   modification.
 *
 * @note
 *   If locking EMU registers, they must be unlocked prior to using any
 *   EMU API functions modifying EMU registers, excluding interrupt control
 *   and regulator control if the architecture has a EMU_PWRCTRL register.
 *   An exception to this is the energy mode entering API (EMU_EnterEMn()),
 *   which can be used when the EMU registers are locked.
 ******************************************************************************/
__STATIC_INLINE void EMU_Lock(void)
{
  EMU->LOCK = 0x0;
}

/***************************************************************************//**
 * @brief
 *   Unlock the EMU so that writing to locked registers again is possible.
 ******************************************************************************/
__STATIC_INLINE void EMU_Unlock(void)
{
  EMU->LOCK = EMU_LOCK_LOCKKEY_UNLOCK;
}

#if defined(_EMU_PWRLOCK_MASK)
/***************************************************************************//**
 * @brief
 *   Lock the EMU regulator control registers in order to protect against
 *   unintended modification.
 ******************************************************************************/
__STATIC_INLINE void EMU_PowerLock(void)
{
  EMU->PWRLOCK = EMU_PWRLOCK_LOCKKEY_LOCK;
}

/***************************************************************************//**
 * @brief
 *   Unlock the EMU power control registers so that writing to
 *   locked registers again is possible.
 ******************************************************************************/
__STATIC_INLINE void EMU_PowerUnlock(void)
{
  EMU->PWRLOCK = EMU_PWRLOCK_LOCKKEY_UNLOCK;
}
#endif

#if defined(_EMU_CTRL_EM2BLOCK_MASK)
/***************************************************************************//**
 * @brief
 *   Block entering EM2 or higher number energy modes.
 ******************************************************************************/
__STATIC_INLINE void EMU_EM2Block(void)
{
  BUS_RegBitWrite(&EMU->CTRL, _EMU_CTRL_EM2BLOCK_SHIFT, 1U);
}

/***************************************************************************//**
 * @brief
 *   Unblock entering EM2 or higher number energy modes.
 ******************************************************************************/
__STATIC_INLINE void EMU_EM2UnBlock(void)
{
  BUS_RegBitWrite(&EMU->CTRL, _EMU_CTRL_EM2BLOCK_SHIFT, 0U);
}
#endif

#if defined(_EMU_EM4CTRL_EM4IORETMODE_MASK)
/***************************************************************************//**
 * @brief
 *   When EM4 pin retention is set to emuPinRetentionLatch, then pins are retained
 *   through EM4 entry and wakeup. The pin state is released by calling this function.
 *   The feature allows peripherals or GPIO to be re-initialized after EM4 exit (reset),
 *   and when initialization is done, this function can release pins and return control
 *   to the peripherals or GPIO.
 ******************************************************************************/
__STATIC_INLINE void EMU_UnlatchPinRetention(void)
{
  EMU->CMD = EMU_CMD_EM4UNLATCH;
}
#endif

#if defined(_EMU_TEMP_TEMP_MASK)
#define EMU_TEMP_ZERO_C_IN_KELVIN (273.15f)
/***************************************************************************//**
 * @brief
 *   Returns true if a temperature measurement is ready
 ******************************************************************************/
__STATIC_INLINE bool EMU_TemperatureReady(void)
{
#if defined(EMU_STATUS_FIRSTTEMPDONE)
  return EMU->STATUS & EMU_STATUS_FIRSTTEMPDONE;
#else
  return !((EMU->TEMP & _EMU_TEMP_TEMP_MASK) == 0u);
#endif
}

#if defined(_EMU_TEMP_TEMPAVG_MASK)
/***************************************************************************//**
 * @brief
 *   Get averaged temperature in degrees Celcius
 *
 * @note
 *   An averaged temperature measurement must first be requested by calling
 *   @ref EMU_TemperatureAvgRequest() and waiting for the TEMPAVG interrupt flag
 *   to go high.
 *
 * @return
 *   Averaged temperature
 ******************************************************************************/
__STATIC_INLINE float EMU_TemperatureAvgGet(void)
{
  return ((float) ((EMU->TEMP & _EMU_TEMP_TEMPAVG_MASK)
                   >> _EMU_TEMP_TEMPAVG_SHIFT)
          ) / 4.0f - EMU_TEMP_ZERO_C_IN_KELVIN;
}

/***************************************************************************//**
 * @brief
 *   Request averaged temperature
 *
 * @note
 *   EMU must be unlocked, by calling @ref EMU_Unlock(), before this function
 *   can be called.
 *
 * @param[in] numSamples
 *   Number of temeprature samples to average
 ******************************************************************************/
__STATIC_INLINE void EMU_TemperatureAvgRequest(EMU_TempAvgNum_TypeDef numSamples)
{
  BUS_RegBitWrite(&EMU->CTRL, _EMU_CTRL_TEMPAVGNUM_SHIFT, numSamples);
  EMU->CMD = 1u << _EMU_CMD_TEMPAVGREQ_SHIFT;
}

#endif //defined(_EMU_TEMP_TEMPAVG_MASK)
#endif //defined(_EMU_TEMP_TEMP_MASK)

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
void EMU_SetBiasMode(EMU_BiasMode_TypeDef mode);
#endif

#endif//#if ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER

#endif // CRTX_EMU_H