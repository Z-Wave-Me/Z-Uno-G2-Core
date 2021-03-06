#ifndef CORTEXGPIO_H
#define CORTEXGPIO_H

#include "ZGecko.h"
#include "CrtxEmu.h"

typedef struct {
  __IOM uint32_t CTRL;         /**< Port Control Register  */
  __IOM uint32_t MODEL;        /**< Port Pin Mode Low Register  */
  __IOM uint32_t MODEH;        /**< Port Pin Mode High Register  */
  __IOM uint32_t DOUT;         /**< Port Data Out Register  */
  uint32_t       RESERVED0[2]; /**< Reserved for future use **/
  __IOM uint32_t DOUTTGL;      /**< Port Data Out Toggle Register  */
  __IM uint32_t  DIN;          /**< Port Data in Register  */
  __IOM uint32_t PINLOCKN;     /**< Port Unlocked Pins Register  */
  uint32_t       RESERVED1[1]; /**< Reserved for future use **/
  __IOM uint32_t OVTDIS;       /**< Over Voltage Disable for All Modes  */
  uint32_t       RESERVED2[1]; /**< Reserved future */
} GPIO_P_TypeDef;

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG13P_GPIO GPIO
 * @{
 * @brief EFR32FG13P_GPIO Register Declaration
 *****************************************************************************/
/** GPIO Register Declaration */
typedef struct {
  GPIO_P_TypeDef P[12];          /**< Port configuration bits */

  uint32_t       RESERVED0[112]; /**< Reserved for future use **/
  __IOM uint32_t EXTIPSELL;      /**< External Interrupt Port Select Low Register  */
  __IOM uint32_t EXTIPSELH;      /**< External Interrupt Port Select High Register  */
  __IOM uint32_t EXTIPINSELL;    /**< External Interrupt Pin Select Low Register  */
  __IOM uint32_t EXTIPINSELH;    /**< External Interrupt Pin Select High Register  */
  __IOM uint32_t EXTIRISE;       /**< External Interrupt Rising Edge Trigger Register  */
  __IOM uint32_t EXTIFALL;       /**< External Interrupt Falling Edge Trigger Register  */
  __IOM uint32_t EXTILEVEL;      /**< External Interrupt Level Register  */
  __IM uint32_t  IF;             /**< Interrupt Flag Register  */
  __IOM uint32_t IFS;            /**< Interrupt Flag Set Register  */
  __IOM uint32_t IFC;            /**< Interrupt Flag Clear Register  */
  __IOM uint32_t IEN;            /**< Interrupt Enable Register  */
  __IOM uint32_t EM4WUEN;        /**< EM4 Wake Up Enable Register  */

  uint32_t       RESERVED1[4];   /**< Reserved for future use **/
  __IOM uint32_t ROUTEPEN;       /**< I/O Routing Pin Enable Register  */
  __IOM uint32_t ROUTELOC0;      /**< I/O Routing Location Register  */
  __IOM uint32_t ROUTELOC1;      /**< I/O Routing Location Register 1  */

  uint32_t       RESERVED2[1];   /**< Reserved for future use **/
  __IOM uint32_t INSENSE;        /**< Input Sense Register  */
  __IOM uint32_t LOCK;           /**< Configuration Lock Register  */
} GPIO_TypeDef;                  /** @} */

/* Bit fields for GPIO P_CTRL */
#define _GPIO_P_CTRL_RESETVALUE                         0x00500050UL                                  /**< Default value for GPIO_P_CTRL */
#define _GPIO_P_CTRL_MASK                               0x10711071UL                                  /**< Mask for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTH                       (0x1UL << 0)                                  /**< Drive Strength for Port */
#define _GPIO_P_CTRL_DRIVESTRENGTH_SHIFT                0                                             /**< Shift value for GPIO_DRIVESTRENGTH */
#define _GPIO_P_CTRL_DRIVESTRENGTH_MASK                 0x1UL                                         /**< Bit mask for GPIO_DRIVESTRENGTH */
#define _GPIO_P_CTRL_DRIVESTRENGTH_DEFAULT              0x00000000UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define _GPIO_P_CTRL_DRIVESTRENGTH_STRONG               0x00000000UL                                  /**< Mode STRONG for GPIO_P_CTRL */
#define _GPIO_P_CTRL_DRIVESTRENGTH_WEAK                 0x00000001UL                                  /**< Mode WEAK for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTH_DEFAULT               (_GPIO_P_CTRL_DRIVESTRENGTH_DEFAULT << 0)     /**< Shifted mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTH_STRONG                (_GPIO_P_CTRL_DRIVESTRENGTH_STRONG << 0)      /**< Shifted mode STRONG for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTH_WEAK                  (_GPIO_P_CTRL_DRIVESTRENGTH_WEAK << 0)        /**< Shifted mode WEAK for GPIO_P_CTRL */
#define _GPIO_P_CTRL_SLEWRATE_SHIFT                     4                                             /**< Shift value for GPIO_SLEWRATE */
#define _GPIO_P_CTRL_SLEWRATE_MASK                      0x70UL                                        /**< Bit mask for GPIO_SLEWRATE */
#define _GPIO_P_CTRL_SLEWRATE_DEFAULT                   0x00000005UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_SLEWRATE_DEFAULT                    (_GPIO_P_CTRL_SLEWRATE_DEFAULT << 4)          /**< Shifted mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DINDIS                              (0x1UL << 12)                                 /**< Data in Disable */
#define _GPIO_P_CTRL_DINDIS_SHIFT                       12                                            /**< Shift value for GPIO_DINDIS */
#define _GPIO_P_CTRL_DINDIS_MASK                        0x1000UL                                      /**< Bit mask for GPIO_DINDIS */
#define _GPIO_P_CTRL_DINDIS_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DINDIS_DEFAULT                      (_GPIO_P_CTRL_DINDIS_DEFAULT << 12)           /**< Shifted mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTHALT                    (0x1UL << 16)                                 /**< Alternate Drive Strength for Port */
#define _GPIO_P_CTRL_DRIVESTRENGTHALT_SHIFT             16                                            /**< Shift value for GPIO_DRIVESTRENGTHALT */
#define _GPIO_P_CTRL_DRIVESTRENGTHALT_MASK              0x10000UL                                     /**< Bit mask for GPIO_DRIVESTRENGTHALT */
#define _GPIO_P_CTRL_DRIVESTRENGTHALT_DEFAULT           0x00000000UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define _GPIO_P_CTRL_DRIVESTRENGTHALT_STRONG            0x00000000UL                                  /**< Mode STRONG for GPIO_P_CTRL */
#define _GPIO_P_CTRL_DRIVESTRENGTHALT_WEAK              0x00000001UL                                  /**< Mode WEAK for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTHALT_DEFAULT            (_GPIO_P_CTRL_DRIVESTRENGTHALT_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTHALT_STRONG             (_GPIO_P_CTRL_DRIVESTRENGTHALT_STRONG << 16)  /**< Shifted mode STRONG for GPIO_P_CTRL */
#define GPIO_P_CTRL_DRIVESTRENGTHALT_WEAK               (_GPIO_P_CTRL_DRIVESTRENGTHALT_WEAK << 16)    /**< Shifted mode WEAK for GPIO_P_CTRL */
#define _GPIO_P_CTRL_SLEWRATEALT_SHIFT                  20                                            /**< Shift value for GPIO_SLEWRATEALT */
#define _GPIO_P_CTRL_SLEWRATEALT_MASK                   0x700000UL                                    /**< Bit mask for GPIO_SLEWRATEALT */
#define _GPIO_P_CTRL_SLEWRATEALT_DEFAULT                0x00000005UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_SLEWRATEALT_DEFAULT                 (_GPIO_P_CTRL_SLEWRATEALT_DEFAULT << 20)      /**< Shifted mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DINDISALT                           (0x1UL << 28)                                 /**< Alternate Data in Disable */
#define _GPIO_P_CTRL_DINDISALT_SHIFT                    28                                            /**< Shift value for GPIO_DINDISALT */
#define _GPIO_P_CTRL_DINDISALT_MASK                     0x10000000UL                                  /**< Bit mask for GPIO_DINDISALT */
#define _GPIO_P_CTRL_DINDISALT_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for GPIO_P_CTRL */
#define GPIO_P_CTRL_DINDISALT_DEFAULT                   (_GPIO_P_CTRL_DINDISALT_DEFAULT << 28)        /**< Shifted mode DEFAULT for GPIO_P_CTRL */

/* Bit fields for GPIO P_MODEL */
#define _GPIO_P_MODEL_RESETVALUE                        0x00000000UL                                        /**< Default value for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MASK                              0xFFFFFFFFUL                                        /**< Mask for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_SHIFT                       0                                                   /**< Shift value for GPIO_MODE0 */
#define _GPIO_P_MODEL_MODE0_MASK                        0xFUL                                               /**< Bit mask for GPIO_MODE0 */
#define _GPIO_P_MODEL_MODE0_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_DEFAULT                      (_GPIO_P_MODEL_MODE0_DEFAULT << 0)                  /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_DISABLED                     (_GPIO_P_MODEL_MODE0_DISABLED << 0)                 /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_INPUT                        (_GPIO_P_MODEL_MODE0_INPUT << 0)                    /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_INPUTPULL                    (_GPIO_P_MODEL_MODE0_INPUTPULL << 0)                /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE0_INPUTPULLFILTER << 0)          /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_PUSHPULL                     (_GPIO_P_MODEL_MODE0_PUSHPULL << 0)                 /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_PUSHPULLALT                  (_GPIO_P_MODEL_MODE0_PUSHPULLALT << 0)              /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDOR                      (_GPIO_P_MODEL_MODE0_WIREDOR << 0)                  /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE0_WIREDORPULLDOWN << 0)          /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDAND                     (_GPIO_P_MODEL_MODE0_WIREDAND << 0)                 /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDFILTER               (_GPIO_P_MODEL_MODE0_WIREDANDFILTER << 0)           /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE0_WIREDANDPULLUP << 0)           /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER << 0)     /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDALT                  (_GPIO_P_MODEL_MODE0_WIREDANDALT << 0)              /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE0_WIREDANDALTFILTER << 0)        /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE0_WIREDANDALTPULLUP << 0)        /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE0_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE0_WIREDANDALTPULLUPFILTER << 0)  /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_SHIFT                       4                                                   /**< Shift value for GPIO_MODE1 */
#define _GPIO_P_MODEL_MODE1_MASK                        0xF0UL                                              /**< Bit mask for GPIO_MODE1 */
#define _GPIO_P_MODEL_MODE1_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE1_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_DEFAULT                      (_GPIO_P_MODEL_MODE1_DEFAULT << 4)                  /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_DISABLED                     (_GPIO_P_MODEL_MODE1_DISABLED << 4)                 /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_INPUT                        (_GPIO_P_MODEL_MODE1_INPUT << 4)                    /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_INPUTPULL                    (_GPIO_P_MODEL_MODE1_INPUTPULL << 4)                /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE1_INPUTPULLFILTER << 4)          /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_PUSHPULL                     (_GPIO_P_MODEL_MODE1_PUSHPULL << 4)                 /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_PUSHPULLALT                  (_GPIO_P_MODEL_MODE1_PUSHPULLALT << 4)              /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDOR                      (_GPIO_P_MODEL_MODE1_WIREDOR << 4)                  /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE1_WIREDORPULLDOWN << 4)          /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDAND                     (_GPIO_P_MODEL_MODE1_WIREDAND << 4)                 /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDFILTER               (_GPIO_P_MODEL_MODE1_WIREDANDFILTER << 4)           /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE1_WIREDANDPULLUP << 4)           /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER << 4)     /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDALT                  (_GPIO_P_MODEL_MODE1_WIREDANDALT << 4)              /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE1_WIREDANDALTFILTER << 4)        /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE1_WIREDANDALTPULLUP << 4)        /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE1_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE1_WIREDANDALTPULLUPFILTER << 4)  /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_SHIFT                       8                                                   /**< Shift value for GPIO_MODE2 */
#define _GPIO_P_MODEL_MODE2_MASK                        0xF00UL                                             /**< Bit mask for GPIO_MODE2 */
#define _GPIO_P_MODEL_MODE2_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE2_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_DEFAULT                      (_GPIO_P_MODEL_MODE2_DEFAULT << 8)                  /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_DISABLED                     (_GPIO_P_MODEL_MODE2_DISABLED << 8)                 /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_INPUT                        (_GPIO_P_MODEL_MODE2_INPUT << 8)                    /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_INPUTPULL                    (_GPIO_P_MODEL_MODE2_INPUTPULL << 8)                /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE2_INPUTPULLFILTER << 8)          /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_PUSHPULL                     (_GPIO_P_MODEL_MODE2_PUSHPULL << 8)                 /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_PUSHPULLALT                  (_GPIO_P_MODEL_MODE2_PUSHPULLALT << 8)              /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDOR                      (_GPIO_P_MODEL_MODE2_WIREDOR << 8)                  /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE2_WIREDORPULLDOWN << 8)          /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDAND                     (_GPIO_P_MODEL_MODE2_WIREDAND << 8)                 /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDFILTER               (_GPIO_P_MODEL_MODE2_WIREDANDFILTER << 8)           /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE2_WIREDANDPULLUP << 8)           /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE2_WIREDANDPULLUPFILTER << 8)     /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDALT                  (_GPIO_P_MODEL_MODE2_WIREDANDALT << 8)              /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE2_WIREDANDALTFILTER << 8)        /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE2_WIREDANDALTPULLUP << 8)        /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE2_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE2_WIREDANDALTPULLUPFILTER << 8)  /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_SHIFT                       12                                                  /**< Shift value for GPIO_MODE3 */
#define _GPIO_P_MODEL_MODE3_MASK                        0xF000UL                                            /**< Bit mask for GPIO_MODE3 */
#define _GPIO_P_MODEL_MODE3_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE3_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_DEFAULT                      (_GPIO_P_MODEL_MODE3_DEFAULT << 12)                 /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_DISABLED                     (_GPIO_P_MODEL_MODE3_DISABLED << 12)                /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_INPUT                        (_GPIO_P_MODEL_MODE3_INPUT << 12)                   /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_INPUTPULL                    (_GPIO_P_MODEL_MODE3_INPUTPULL << 12)               /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE3_INPUTPULLFILTER << 12)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_PUSHPULL                     (_GPIO_P_MODEL_MODE3_PUSHPULL << 12)                /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_PUSHPULLALT                  (_GPIO_P_MODEL_MODE3_PUSHPULLALT << 12)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDOR                      (_GPIO_P_MODEL_MODE3_WIREDOR << 12)                 /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE3_WIREDORPULLDOWN << 12)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDAND                     (_GPIO_P_MODEL_MODE3_WIREDAND << 12)                /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDFILTER               (_GPIO_P_MODEL_MODE3_WIREDANDFILTER << 12)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE3_WIREDANDPULLUP << 12)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE3_WIREDANDPULLUPFILTER << 12)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDALT                  (_GPIO_P_MODEL_MODE3_WIREDANDALT << 12)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE3_WIREDANDALTFILTER << 12)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE3_WIREDANDALTPULLUP << 12)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE3_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE3_WIREDANDALTPULLUPFILTER << 12) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_SHIFT                       16                                                  /**< Shift value for GPIO_MODE4 */
#define _GPIO_P_MODEL_MODE4_MASK                        0xF0000UL                                           /**< Bit mask for GPIO_MODE4 */
#define _GPIO_P_MODEL_MODE4_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE4_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_DEFAULT                      (_GPIO_P_MODEL_MODE4_DEFAULT << 16)                 /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_DISABLED                     (_GPIO_P_MODEL_MODE4_DISABLED << 16)                /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_INPUT                        (_GPIO_P_MODEL_MODE4_INPUT << 16)                   /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_INPUTPULL                    (_GPIO_P_MODEL_MODE4_INPUTPULL << 16)               /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE4_INPUTPULLFILTER << 16)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_PUSHPULL                     (_GPIO_P_MODEL_MODE4_PUSHPULL << 16)                /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_PUSHPULLALT                  (_GPIO_P_MODEL_MODE4_PUSHPULLALT << 16)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDOR                      (_GPIO_P_MODEL_MODE4_WIREDOR << 16)                 /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE4_WIREDORPULLDOWN << 16)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDAND                     (_GPIO_P_MODEL_MODE4_WIREDAND << 16)                /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDFILTER               (_GPIO_P_MODEL_MODE4_WIREDANDFILTER << 16)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE4_WIREDANDPULLUP << 16)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER << 16)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDALT                  (_GPIO_P_MODEL_MODE4_WIREDANDALT << 16)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE4_WIREDANDALTFILTER << 16)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE4_WIREDANDALTPULLUP << 16)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE4_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE4_WIREDANDALTPULLUPFILTER << 16) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_SHIFT                       20                                                  /**< Shift value for GPIO_MODE5 */
#define _GPIO_P_MODEL_MODE5_MASK                        0xF00000UL                                          /**< Bit mask for GPIO_MODE5 */
#define _GPIO_P_MODEL_MODE5_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE5_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_DEFAULT                      (_GPIO_P_MODEL_MODE5_DEFAULT << 20)                 /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_DISABLED                     (_GPIO_P_MODEL_MODE5_DISABLED << 20)                /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_INPUT                        (_GPIO_P_MODEL_MODE5_INPUT << 20)                   /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_INPUTPULL                    (_GPIO_P_MODEL_MODE5_INPUTPULL << 20)               /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE5_INPUTPULLFILTER << 20)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_PUSHPULL                     (_GPIO_P_MODEL_MODE5_PUSHPULL << 20)                /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_PUSHPULLALT                  (_GPIO_P_MODEL_MODE5_PUSHPULLALT << 20)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDOR                      (_GPIO_P_MODEL_MODE5_WIREDOR << 20)                 /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE5_WIREDORPULLDOWN << 20)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDAND                     (_GPIO_P_MODEL_MODE5_WIREDAND << 20)                /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDFILTER               (_GPIO_P_MODEL_MODE5_WIREDANDFILTER << 20)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE5_WIREDANDPULLUP << 20)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER << 20)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDALT                  (_GPIO_P_MODEL_MODE5_WIREDANDALT << 20)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE5_WIREDANDALTFILTER << 20)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE5_WIREDANDALTPULLUP << 20)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE5_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE5_WIREDANDALTPULLUPFILTER << 20) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_SHIFT                       24                                                  /**< Shift value for GPIO_MODE6 */
#define _GPIO_P_MODEL_MODE6_MASK                        0xF000000UL                                         /**< Bit mask for GPIO_MODE6 */
#define _GPIO_P_MODEL_MODE6_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE6_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_DEFAULT                      (_GPIO_P_MODEL_MODE6_DEFAULT << 24)                 /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_DISABLED                     (_GPIO_P_MODEL_MODE6_DISABLED << 24)                /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_INPUT                        (_GPIO_P_MODEL_MODE6_INPUT << 24)                   /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_INPUTPULL                    (_GPIO_P_MODEL_MODE6_INPUTPULL << 24)               /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE6_INPUTPULLFILTER << 24)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_PUSHPULL                     (_GPIO_P_MODEL_MODE6_PUSHPULL << 24)                /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_PUSHPULLALT                  (_GPIO_P_MODEL_MODE6_PUSHPULLALT << 24)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDOR                      (_GPIO_P_MODEL_MODE6_WIREDOR << 24)                 /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE6_WIREDORPULLDOWN << 24)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDAND                     (_GPIO_P_MODEL_MODE6_WIREDAND << 24)                /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDFILTER               (_GPIO_P_MODEL_MODE6_WIREDANDFILTER << 24)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE6_WIREDANDPULLUP << 24)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE6_WIREDANDPULLUPFILTER << 24)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDALT                  (_GPIO_P_MODEL_MODE6_WIREDANDALT << 24)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE6_WIREDANDALTFILTER << 24)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE6_WIREDANDALTPULLUP << 24)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE6_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE6_WIREDANDALTPULLUPFILTER << 24) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_SHIFT                       28                                                  /**< Shift value for GPIO_MODE7 */
#define _GPIO_P_MODEL_MODE7_MASK                        0xF0000000UL                                        /**< Bit mask for GPIO_MODE7 */
#define _GPIO_P_MODEL_MODE7_DEFAULT                     0x00000000UL                                        /**< Mode DEFAULT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_INPUTPULLFILTER             0x00000003UL                                        /**< Mode INPUTPULLFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDOR                     0x00000006UL                                        /**< Mode WIREDOR for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDORPULLDOWN             0x00000007UL                                        /**< Mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDFILTER              0x00000009UL                                        /**< Mode WIREDANDFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDPULLUP              0x0000000AUL                                        /**< Mode WIREDANDPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDPULLUPFILTER        0x0000000BUL                                        /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDALT                 0x0000000CUL                                        /**< Mode WIREDANDALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDALTFILTER           0x0000000DUL                                        /**< Mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDALTPULLUP           0x0000000EUL                                        /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE7_WIREDANDALTPULLUPFILTER     0x0000000FUL                                        /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_DEFAULT                      (_GPIO_P_MODEL_MODE7_DEFAULT << 28)                 /**< Shifted mode DEFAULT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_DISABLED                     (_GPIO_P_MODEL_MODE7_DISABLED << 28)                /**< Shifted mode DISABLED for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_INPUT                        (_GPIO_P_MODEL_MODE7_INPUT << 28)                   /**< Shifted mode INPUT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_INPUTPULL                    (_GPIO_P_MODEL_MODE7_INPUTPULL << 28)               /**< Shifted mode INPUTPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_INPUTPULLFILTER              (_GPIO_P_MODEL_MODE7_INPUTPULLFILTER << 28)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_PUSHPULL                     (_GPIO_P_MODEL_MODE7_PUSHPULL << 28)                /**< Shifted mode PUSHPULL for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_PUSHPULLALT                  (_GPIO_P_MODEL_MODE7_PUSHPULLALT << 28)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDOR                      (_GPIO_P_MODEL_MODE7_WIREDOR << 28)                 /**< Shifted mode WIREDOR for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDORPULLDOWN              (_GPIO_P_MODEL_MODE7_WIREDORPULLDOWN << 28)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDAND                     (_GPIO_P_MODEL_MODE7_WIREDAND << 28)                /**< Shifted mode WIREDAND for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDFILTER               (_GPIO_P_MODEL_MODE7_WIREDANDFILTER << 28)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDPULLUP               (_GPIO_P_MODEL_MODE7_WIREDANDPULLUP << 28)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDPULLUPFILTER         (_GPIO_P_MODEL_MODE7_WIREDANDPULLUPFILTER << 28)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDALT                  (_GPIO_P_MODEL_MODE7_WIREDANDALT << 28)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDALTFILTER            (_GPIO_P_MODEL_MODE7_WIREDANDALTFILTER << 28)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDALTPULLUP            (_GPIO_P_MODEL_MODE7_WIREDANDALTPULLUP << 28)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEL */
#define GPIO_P_MODEL_MODE7_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEL_MODE7_WIREDANDALTPULLUPFILTER << 28) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEL */

/* Bit fields for GPIO P_MODEH */
#define _GPIO_P_MODEH_RESETVALUE                        0x00000000UL                                         /**< Default value for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MASK                              0xFFFFFFFFUL                                         /**< Mask for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_SHIFT                       0                                                    /**< Shift value for GPIO_MODE8 */
#define _GPIO_P_MODEH_MODE8_MASK                        0xFUL                                                /**< Bit mask for GPIO_MODE8 */
#define _GPIO_P_MODEH_MODE8_DEFAULT                     0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_DISABLED                    0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_INPUT                       0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_INPUTPULL                   0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_INPUTPULLFILTER             0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_PUSHPULL                    0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_PUSHPULLALT                 0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDOR                     0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDORPULLDOWN             0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDAND                    0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDFILTER              0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDPULLUP              0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDPULLUPFILTER        0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDALT                 0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDALTFILTER           0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDALTPULLUP           0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE8_WIREDANDALTPULLUPFILTER     0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_DEFAULT                      (_GPIO_P_MODEH_MODE8_DEFAULT << 0)                   /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_DISABLED                     (_GPIO_P_MODEH_MODE8_DISABLED << 0)                  /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_INPUT                        (_GPIO_P_MODEH_MODE8_INPUT << 0)                     /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_INPUTPULL                    (_GPIO_P_MODEH_MODE8_INPUTPULL << 0)                 /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_INPUTPULLFILTER              (_GPIO_P_MODEH_MODE8_INPUTPULLFILTER << 0)           /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_PUSHPULL                     (_GPIO_P_MODEH_MODE8_PUSHPULL << 0)                  /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_PUSHPULLALT                  (_GPIO_P_MODEH_MODE8_PUSHPULLALT << 0)               /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDOR                      (_GPIO_P_MODEH_MODE8_WIREDOR << 0)                   /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDORPULLDOWN              (_GPIO_P_MODEH_MODE8_WIREDORPULLDOWN << 0)           /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDAND                     (_GPIO_P_MODEH_MODE8_WIREDAND << 0)                  /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDFILTER               (_GPIO_P_MODEH_MODE8_WIREDANDFILTER << 0)            /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDPULLUP               (_GPIO_P_MODEH_MODE8_WIREDANDPULLUP << 0)            /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDPULLUPFILTER         (_GPIO_P_MODEH_MODE8_WIREDANDPULLUPFILTER << 0)      /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDALT                  (_GPIO_P_MODEH_MODE8_WIREDANDALT << 0)               /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDALTFILTER            (_GPIO_P_MODEH_MODE8_WIREDANDALTFILTER << 0)         /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDALTPULLUP            (_GPIO_P_MODEH_MODE8_WIREDANDALTPULLUP << 0)         /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE8_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEH_MODE8_WIREDANDALTPULLUPFILTER << 0)   /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_SHIFT                       4                                                    /**< Shift value for GPIO_MODE9 */
#define _GPIO_P_MODEH_MODE9_MASK                        0xF0UL                                               /**< Bit mask for GPIO_MODE9 */
#define _GPIO_P_MODEH_MODE9_DEFAULT                     0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_DISABLED                    0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_INPUT                       0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_INPUTPULL                   0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_INPUTPULLFILTER             0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_PUSHPULL                    0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_PUSHPULLALT                 0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDOR                     0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDORPULLDOWN             0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDAND                    0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDFILTER              0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDPULLUP              0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDPULLUPFILTER        0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDALT                 0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDALTFILTER           0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDALTPULLUP           0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE9_WIREDANDALTPULLUPFILTER     0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_DEFAULT                      (_GPIO_P_MODEH_MODE9_DEFAULT << 4)                   /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_DISABLED                     (_GPIO_P_MODEH_MODE9_DISABLED << 4)                  /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_INPUT                        (_GPIO_P_MODEH_MODE9_INPUT << 4)                     /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_INPUTPULL                    (_GPIO_P_MODEH_MODE9_INPUTPULL << 4)                 /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_INPUTPULLFILTER              (_GPIO_P_MODEH_MODE9_INPUTPULLFILTER << 4)           /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_PUSHPULL                     (_GPIO_P_MODEH_MODE9_PUSHPULL << 4)                  /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_PUSHPULLALT                  (_GPIO_P_MODEH_MODE9_PUSHPULLALT << 4)               /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDOR                      (_GPIO_P_MODEH_MODE9_WIREDOR << 4)                   /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDORPULLDOWN              (_GPIO_P_MODEH_MODE9_WIREDORPULLDOWN << 4)           /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDAND                     (_GPIO_P_MODEH_MODE9_WIREDAND << 4)                  /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDFILTER               (_GPIO_P_MODEH_MODE9_WIREDANDFILTER << 4)            /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDPULLUP               (_GPIO_P_MODEH_MODE9_WIREDANDPULLUP << 4)            /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDPULLUPFILTER         (_GPIO_P_MODEH_MODE9_WIREDANDPULLUPFILTER << 4)      /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDALT                  (_GPIO_P_MODEH_MODE9_WIREDANDALT << 4)               /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDALTFILTER            (_GPIO_P_MODEH_MODE9_WIREDANDALTFILTER << 4)         /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDALTPULLUP            (_GPIO_P_MODEH_MODE9_WIREDANDALTPULLUP << 4)         /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE9_WIREDANDALTPULLUPFILTER      (_GPIO_P_MODEH_MODE9_WIREDANDALTPULLUPFILTER << 4)   /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_SHIFT                      8                                                    /**< Shift value for GPIO_MODE10 */
#define _GPIO_P_MODEH_MODE10_MASK                       0xF00UL                                              /**< Bit mask for GPIO_MODE10 */
#define _GPIO_P_MODEH_MODE10_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE10_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_DEFAULT                     (_GPIO_P_MODEH_MODE10_DEFAULT << 8)                  /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_DISABLED                    (_GPIO_P_MODEH_MODE10_DISABLED << 8)                 /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_INPUT                       (_GPIO_P_MODEH_MODE10_INPUT << 8)                    /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_INPUTPULL                   (_GPIO_P_MODEH_MODE10_INPUTPULL << 8)                /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE10_INPUTPULLFILTER << 8)          /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_PUSHPULL                    (_GPIO_P_MODEH_MODE10_PUSHPULL << 8)                 /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_PUSHPULLALT                 (_GPIO_P_MODEH_MODE10_PUSHPULLALT << 8)              /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDOR                     (_GPIO_P_MODEH_MODE10_WIREDOR << 8)                  /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE10_WIREDORPULLDOWN << 8)          /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDAND                    (_GPIO_P_MODEH_MODE10_WIREDAND << 8)                 /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDFILTER              (_GPIO_P_MODEH_MODE10_WIREDANDFILTER << 8)           /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE10_WIREDANDPULLUP << 8)           /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE10_WIREDANDPULLUPFILTER << 8)     /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDALT                 (_GPIO_P_MODEH_MODE10_WIREDANDALT << 8)              /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE10_WIREDANDALTFILTER << 8)        /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE10_WIREDANDALTPULLUP << 8)        /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE10_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE10_WIREDANDALTPULLUPFILTER << 8)  /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_SHIFT                      12                                                   /**< Shift value for GPIO_MODE11 */
#define _GPIO_P_MODEH_MODE11_MASK                       0xF000UL                                             /**< Bit mask for GPIO_MODE11 */
#define _GPIO_P_MODEH_MODE11_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE11_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_DEFAULT                     (_GPIO_P_MODEH_MODE11_DEFAULT << 12)                 /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_DISABLED                    (_GPIO_P_MODEH_MODE11_DISABLED << 12)                /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_INPUT                       (_GPIO_P_MODEH_MODE11_INPUT << 12)                   /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_INPUTPULL                   (_GPIO_P_MODEH_MODE11_INPUTPULL << 12)               /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE11_INPUTPULLFILTER << 12)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_PUSHPULL                    (_GPIO_P_MODEH_MODE11_PUSHPULL << 12)                /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_PUSHPULLALT                 (_GPIO_P_MODEH_MODE11_PUSHPULLALT << 12)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDOR                     (_GPIO_P_MODEH_MODE11_WIREDOR << 12)                 /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE11_WIREDORPULLDOWN << 12)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDAND                    (_GPIO_P_MODEH_MODE11_WIREDAND << 12)                /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDFILTER              (_GPIO_P_MODEH_MODE11_WIREDANDFILTER << 12)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE11_WIREDANDPULLUP << 12)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE11_WIREDANDPULLUPFILTER << 12)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDALT                 (_GPIO_P_MODEH_MODE11_WIREDANDALT << 12)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE11_WIREDANDALTFILTER << 12)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE11_WIREDANDALTPULLUP << 12)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE11_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE11_WIREDANDALTPULLUPFILTER << 12) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_SHIFT                      16                                                   /**< Shift value for GPIO_MODE12 */
#define _GPIO_P_MODEH_MODE12_MASK                       0xF0000UL                                            /**< Bit mask for GPIO_MODE12 */
#define _GPIO_P_MODEH_MODE12_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE12_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_DEFAULT                     (_GPIO_P_MODEH_MODE12_DEFAULT << 16)                 /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_DISABLED                    (_GPIO_P_MODEH_MODE12_DISABLED << 16)                /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_INPUT                       (_GPIO_P_MODEH_MODE12_INPUT << 16)                   /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_INPUTPULL                   (_GPIO_P_MODEH_MODE12_INPUTPULL << 16)               /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE12_INPUTPULLFILTER << 16)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_PUSHPULL                    (_GPIO_P_MODEH_MODE12_PUSHPULL << 16)                /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_PUSHPULLALT                 (_GPIO_P_MODEH_MODE12_PUSHPULLALT << 16)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDOR                     (_GPIO_P_MODEH_MODE12_WIREDOR << 16)                 /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE12_WIREDORPULLDOWN << 16)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDAND                    (_GPIO_P_MODEH_MODE12_WIREDAND << 16)                /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDFILTER              (_GPIO_P_MODEH_MODE12_WIREDANDFILTER << 16)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE12_WIREDANDPULLUP << 16)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER << 16)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDALT                 (_GPIO_P_MODEH_MODE12_WIREDANDALT << 16)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE12_WIREDANDALTFILTER << 16)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE12_WIREDANDALTPULLUP << 16)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE12_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE12_WIREDANDALTPULLUPFILTER << 16) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_SHIFT                      20                                                   /**< Shift value for GPIO_MODE13 */
#define _GPIO_P_MODEH_MODE13_MASK                       0xF00000UL                                           /**< Bit mask for GPIO_MODE13 */
#define _GPIO_P_MODEH_MODE13_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE13_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_DEFAULT                     (_GPIO_P_MODEH_MODE13_DEFAULT << 20)                 /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_DISABLED                    (_GPIO_P_MODEH_MODE13_DISABLED << 20)                /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_INPUT                       (_GPIO_P_MODEH_MODE13_INPUT << 20)                   /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_INPUTPULL                   (_GPIO_P_MODEH_MODE13_INPUTPULL << 20)               /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE13_INPUTPULLFILTER << 20)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_PUSHPULL                    (_GPIO_P_MODEH_MODE13_PUSHPULL << 20)                /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_PUSHPULLALT                 (_GPIO_P_MODEH_MODE13_PUSHPULLALT << 20)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDOR                     (_GPIO_P_MODEH_MODE13_WIREDOR << 20)                 /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE13_WIREDORPULLDOWN << 20)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDAND                    (_GPIO_P_MODEH_MODE13_WIREDAND << 20)                /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDFILTER              (_GPIO_P_MODEH_MODE13_WIREDANDFILTER << 20)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE13_WIREDANDPULLUP << 20)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE13_WIREDANDPULLUPFILTER << 20)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDALT                 (_GPIO_P_MODEH_MODE13_WIREDANDALT << 20)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE13_WIREDANDALTFILTER << 20)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE13_WIREDANDALTPULLUP << 20)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE13_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE13_WIREDANDALTPULLUPFILTER << 20) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_SHIFT                      24                                                   /**< Shift value for GPIO_MODE14 */
#define _GPIO_P_MODEH_MODE14_MASK                       0xF000000UL                                          /**< Bit mask for GPIO_MODE14 */
#define _GPIO_P_MODEH_MODE14_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE14_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_DEFAULT                     (_GPIO_P_MODEH_MODE14_DEFAULT << 24)                 /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_DISABLED                    (_GPIO_P_MODEH_MODE14_DISABLED << 24)                /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_INPUT                       (_GPIO_P_MODEH_MODE14_INPUT << 24)                   /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_INPUTPULL                   (_GPIO_P_MODEH_MODE14_INPUTPULL << 24)               /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE14_INPUTPULLFILTER << 24)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_PUSHPULL                    (_GPIO_P_MODEH_MODE14_PUSHPULL << 24)                /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_PUSHPULLALT                 (_GPIO_P_MODEH_MODE14_PUSHPULLALT << 24)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDOR                     (_GPIO_P_MODEH_MODE14_WIREDOR << 24)                 /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE14_WIREDORPULLDOWN << 24)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDAND                    (_GPIO_P_MODEH_MODE14_WIREDAND << 24)                /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDFILTER              (_GPIO_P_MODEH_MODE14_WIREDANDFILTER << 24)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE14_WIREDANDPULLUP << 24)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE14_WIREDANDPULLUPFILTER << 24)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDALT                 (_GPIO_P_MODEH_MODE14_WIREDANDALT << 24)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE14_WIREDANDALTFILTER << 24)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE14_WIREDANDALTPULLUP << 24)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE14_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE14_WIREDANDALTPULLUPFILTER << 24) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_SHIFT                      28                                                   /**< Shift value for GPIO_MODE15 */
#define _GPIO_P_MODEH_MODE15_MASK                       0xF0000000UL                                         /**< Bit mask for GPIO_MODE15 */
#define _GPIO_P_MODEH_MODE15_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_DISABLED                   0x00000000UL                                         /**< Mode DISABLED for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_INPUT                      0x00000001UL                                         /**< Mode INPUT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_INPUTPULL                  0x00000002UL                                         /**< Mode INPUTPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_INPUTPULLFILTER            0x00000003UL                                         /**< Mode INPUTPULLFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_PUSHPULL                   0x00000004UL                                         /**< Mode PUSHPULL for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_PUSHPULLALT                0x00000005UL                                         /**< Mode PUSHPULLALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDOR                    0x00000006UL                                         /**< Mode WIREDOR for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDORPULLDOWN            0x00000007UL                                         /**< Mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDAND                   0x00000008UL                                         /**< Mode WIREDAND for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDFILTER             0x00000009UL                                         /**< Mode WIREDANDFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDPULLUP             0x0000000AUL                                         /**< Mode WIREDANDPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDPULLUPFILTER       0x0000000BUL                                         /**< Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDALT                0x0000000CUL                                         /**< Mode WIREDANDALT for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDALTFILTER          0x0000000DUL                                         /**< Mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDALTPULLUP          0x0000000EUL                                         /**< Mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define _GPIO_P_MODEH_MODE15_WIREDANDALTPULLUPFILTER    0x0000000FUL                                         /**< Mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_DEFAULT                     (_GPIO_P_MODEH_MODE15_DEFAULT << 28)                 /**< Shifted mode DEFAULT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_DISABLED                    (_GPIO_P_MODEH_MODE15_DISABLED << 28)                /**< Shifted mode DISABLED for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_INPUT                       (_GPIO_P_MODEH_MODE15_INPUT << 28)                   /**< Shifted mode INPUT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_INPUTPULL                   (_GPIO_P_MODEH_MODE15_INPUTPULL << 28)               /**< Shifted mode INPUTPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_INPUTPULLFILTER             (_GPIO_P_MODEH_MODE15_INPUTPULLFILTER << 28)         /**< Shifted mode INPUTPULLFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_PUSHPULL                    (_GPIO_P_MODEH_MODE15_PUSHPULL << 28)                /**< Shifted mode PUSHPULL for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_PUSHPULLALT                 (_GPIO_P_MODEH_MODE15_PUSHPULLALT << 28)             /**< Shifted mode PUSHPULLALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDOR                     (_GPIO_P_MODEH_MODE15_WIREDOR << 28)                 /**< Shifted mode WIREDOR for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDORPULLDOWN             (_GPIO_P_MODEH_MODE15_WIREDORPULLDOWN << 28)         /**< Shifted mode WIREDORPULLDOWN for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDAND                    (_GPIO_P_MODEH_MODE15_WIREDAND << 28)                /**< Shifted mode WIREDAND for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDFILTER              (_GPIO_P_MODEH_MODE15_WIREDANDFILTER << 28)          /**< Shifted mode WIREDANDFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDPULLUP              (_GPIO_P_MODEH_MODE15_WIREDANDPULLUP << 28)          /**< Shifted mode WIREDANDPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDPULLUPFILTER        (_GPIO_P_MODEH_MODE15_WIREDANDPULLUPFILTER << 28)    /**< Shifted mode WIREDANDPULLUPFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDALT                 (_GPIO_P_MODEH_MODE15_WIREDANDALT << 28)             /**< Shifted mode WIREDANDALT for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDALTFILTER           (_GPIO_P_MODEH_MODE15_WIREDANDALTFILTER << 28)       /**< Shifted mode WIREDANDALTFILTER for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDALTPULLUP           (_GPIO_P_MODEH_MODE15_WIREDANDALTPULLUP << 28)       /**< Shifted mode WIREDANDALTPULLUP for GPIO_P_MODEH */
#define GPIO_P_MODEH_MODE15_WIREDANDALTPULLUPFILTER     (_GPIO_P_MODEH_MODE15_WIREDANDALTPULLUPFILTER << 28) /**< Shifted mode WIREDANDALTPULLUPFILTER for GPIO_P_MODEH */

/* Bit fields for GPIO P_DOUT */
#define _GPIO_P_DOUT_RESETVALUE                         0x00000000UL                     /**< Default value for GPIO_P_DOUT */
#define _GPIO_P_DOUT_MASK                               0x0000FFFFUL                     /**< Mask for GPIO_P_DOUT */
#define _GPIO_P_DOUT_DOUT_SHIFT                         0                                /**< Shift value for GPIO_DOUT */
#define _GPIO_P_DOUT_DOUT_MASK                          0xFFFFUL                         /**< Bit mask for GPIO_DOUT */
#define _GPIO_P_DOUT_DOUT_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for GPIO_P_DOUT */
#define GPIO_P_DOUT_DOUT_DEFAULT                        (_GPIO_P_DOUT_DOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_P_DOUT */

/* Bit fields for GPIO P_DOUTTGL */
#define _GPIO_P_DOUTTGL_RESETVALUE                      0x00000000UL                           /**< Default value for GPIO_P_DOUTTGL */
#define _GPIO_P_DOUTTGL_MASK                            0x0000FFFFUL                           /**< Mask for GPIO_P_DOUTTGL */
#define _GPIO_P_DOUTTGL_DOUTTGL_SHIFT                   0                                      /**< Shift value for GPIO_DOUTTGL */
#define _GPIO_P_DOUTTGL_DOUTTGL_MASK                    0xFFFFUL                               /**< Bit mask for GPIO_DOUTTGL */
#define _GPIO_P_DOUTTGL_DOUTTGL_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for GPIO_P_DOUTTGL */
#define GPIO_P_DOUTTGL_DOUTTGL_DEFAULT                  (_GPIO_P_DOUTTGL_DOUTTGL_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_P_DOUTTGL */

/* Bit fields for GPIO P_DIN */
#define _GPIO_P_DIN_RESETVALUE                          0x00000000UL                   /**< Default value for GPIO_P_DIN */
#define _GPIO_P_DIN_MASK                                0x0000FFFFUL                   /**< Mask for GPIO_P_DIN */
#define _GPIO_P_DIN_DIN_SHIFT                           0                              /**< Shift value for GPIO_DIN */
#define _GPIO_P_DIN_DIN_MASK                            0xFFFFUL                       /**< Bit mask for GPIO_DIN */
#define _GPIO_P_DIN_DIN_DEFAULT                         0x00000000UL                   /**< Mode DEFAULT for GPIO_P_DIN */
#define GPIO_P_DIN_DIN_DEFAULT                          (_GPIO_P_DIN_DIN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_P_DIN */

/* Bit fields for GPIO P_PINLOCKN */
#define _GPIO_P_PINLOCKN_RESETVALUE                     0x0000FFFFUL                             /**< Default value for GPIO_P_PINLOCKN */
#define _GPIO_P_PINLOCKN_MASK                           0x0000FFFFUL                             /**< Mask for GPIO_P_PINLOCKN */
#define _GPIO_P_PINLOCKN_PINLOCKN_SHIFT                 0                                        /**< Shift value for GPIO_PINLOCKN */
#define _GPIO_P_PINLOCKN_PINLOCKN_MASK                  0xFFFFUL                                 /**< Bit mask for GPIO_PINLOCKN */
#define _GPIO_P_PINLOCKN_PINLOCKN_DEFAULT               0x0000FFFFUL                             /**< Mode DEFAULT for GPIO_P_PINLOCKN */
#define GPIO_P_PINLOCKN_PINLOCKN_DEFAULT                (_GPIO_P_PINLOCKN_PINLOCKN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_P_PINLOCKN */

/* Bit fields for GPIO P_OVTDIS */
#define _GPIO_P_OVTDIS_RESETVALUE                       0x00000000UL                         /**< Default value for GPIO_P_OVTDIS */
#define _GPIO_P_OVTDIS_MASK                             0x0000FFFFUL                         /**< Mask for GPIO_P_OVTDIS */
#define _GPIO_P_OVTDIS_OVTDIS_SHIFT                     0                                    /**< Shift value for GPIO_OVTDIS */
#define _GPIO_P_OVTDIS_OVTDIS_MASK                      0xFFFFUL                             /**< Bit mask for GPIO_OVTDIS */
#define _GPIO_P_OVTDIS_OVTDIS_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for GPIO_P_OVTDIS */
#define GPIO_P_OVTDIS_OVTDIS_DEFAULT                    (_GPIO_P_OVTDIS_OVTDIS_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_P_OVTDIS */

/* Bit fields for GPIO EXTIPSELL */
#define _GPIO_EXTIPSELL_RESETVALUE                      0x00000000UL                              /**< Default value for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_MASK                            0xFFFFFFFFUL                              /**< Mask for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_SHIFT                 0                                         /**< Shift value for GPIO_EXTIPSEL0 */
#define _GPIO_EXTIPSELL_EXTIPSEL0_MASK                  0xFUL                                     /**< Bit mask for GPIO_EXTIPSEL0 */
#define _GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL0_PORTA << 0)    /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL0_PORTB << 0)    /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL0_PORTC << 0)    /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL0_PORTD << 0)    /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL0_PORTF << 0)    /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_SHIFT                 4                                         /**< Shift value for GPIO_EXTIPSEL1 */
#define _GPIO_EXTIPSELL_EXTIPSEL1_MASK                  0xF0UL                                    /**< Bit mask for GPIO_EXTIPSEL1 */
#define _GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL1_PORTA << 4)    /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL1_PORTB << 4)    /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL1_PORTC << 4)    /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL1_PORTD << 4)    /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL1_PORTF << 4)    /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_SHIFT                 8                                         /**< Shift value for GPIO_EXTIPSEL2 */
#define _GPIO_EXTIPSELL_EXTIPSEL2_MASK                  0xF00UL                                   /**< Bit mask for GPIO_EXTIPSEL2 */
#define _GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL2_PORTA << 8)    /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL2_PORTB << 8)    /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL2_PORTC << 8)    /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL2_PORTD << 8)    /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL2_PORTF << 8)    /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_SHIFT                 12                                        /**< Shift value for GPIO_EXTIPSEL3 */
#define _GPIO_EXTIPSELL_EXTIPSEL3_MASK                  0xF000UL                                  /**< Bit mask for GPIO_EXTIPSEL3 */
#define _GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL3_PORTA << 12)   /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL3_PORTB << 12)   /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL3_PORTC << 12)   /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL3_PORTD << 12)   /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL3_PORTF << 12)   /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_SHIFT                 16                                        /**< Shift value for GPIO_EXTIPSEL4 */
#define _GPIO_EXTIPSELL_EXTIPSEL4_MASK                  0xF0000UL                                 /**< Bit mask for GPIO_EXTIPSEL4 */
#define _GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL4_PORTA << 16)   /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL4_PORTB << 16)   /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL4_PORTC << 16)   /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL4_PORTD << 16)   /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL4_PORTF << 16)   /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_SHIFT                 20                                        /**< Shift value for GPIO_EXTIPSEL5 */
#define _GPIO_EXTIPSELL_EXTIPSEL5_MASK                  0xF00000UL                                /**< Bit mask for GPIO_EXTIPSEL5 */
#define _GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL5_PORTA << 20)   /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL5_PORTB << 20)   /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL5_PORTC << 20)   /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL5_PORTD << 20)   /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL5_PORTF << 20)   /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_SHIFT                 24                                        /**< Shift value for GPIO_EXTIPSEL6 */
#define _GPIO_EXTIPSELL_EXTIPSEL6_MASK                  0xF000000UL                               /**< Bit mask for GPIO_EXTIPSEL6 */
#define _GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL6_PORTA << 24)   /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL6_PORTB << 24)   /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL6_PORTC << 24)   /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL6_PORTD << 24)   /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL6_PORTF << 24)   /**< Shifted mode PORTF for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_SHIFT                 28                                        /**< Shift value for GPIO_EXTIPSEL7 */
#define _GPIO_EXTIPSELL_EXTIPSEL7_MASK                  0xF0000000UL                              /**< Bit mask for GPIO_EXTIPSEL7 */
#define _GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTA                 0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTB                 0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTC                 0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTD                 0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTF                 0x00000005UL                              /**< Mode PORTF for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT                (_GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTA                  (_GPIO_EXTIPSELL_EXTIPSEL7_PORTA << 28)   /**< Shifted mode PORTA for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTB                  (_GPIO_EXTIPSELL_EXTIPSEL7_PORTB << 28)   /**< Shifted mode PORTB for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTC                  (_GPIO_EXTIPSELL_EXTIPSEL7_PORTC << 28)   /**< Shifted mode PORTC for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTD                  (_GPIO_EXTIPSELL_EXTIPSEL7_PORTD << 28)   /**< Shifted mode PORTD for GPIO_EXTIPSELL */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTF                  (_GPIO_EXTIPSELL_EXTIPSEL7_PORTF << 28)   /**< Shifted mode PORTF for GPIO_EXTIPSELL */

/* Bit fields for GPIO EXTIPSELH */
#define _GPIO_EXTIPSELH_RESETVALUE                      0x00000000UL                               /**< Default value for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_MASK                            0xFFFFFFFFUL                               /**< Mask for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_SHIFT                 0                                          /**< Shift value for GPIO_EXTIPSEL8 */
#define _GPIO_EXTIPSELH_EXTIPSEL8_MASK                  0xFUL                                      /**< Bit mask for GPIO_EXTIPSEL8 */
#define _GPIO_EXTIPSELH_EXTIPSEL8_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_PORTA                 0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_PORTB                 0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_PORTC                 0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_PORTD                 0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL8_PORTF                 0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_DEFAULT                (_GPIO_EXTIPSELH_EXTIPSEL8_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTA                  (_GPIO_EXTIPSELH_EXTIPSEL8_PORTA << 0)     /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTB                  (_GPIO_EXTIPSELH_EXTIPSEL8_PORTB << 0)     /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTC                  (_GPIO_EXTIPSELH_EXTIPSEL8_PORTC << 0)     /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTD                  (_GPIO_EXTIPSELH_EXTIPSEL8_PORTD << 0)     /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTF                  (_GPIO_EXTIPSELH_EXTIPSEL8_PORTF << 0)     /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_SHIFT                 4                                          /**< Shift value for GPIO_EXTIPSEL9 */
#define _GPIO_EXTIPSELH_EXTIPSEL9_MASK                  0xF0UL                                     /**< Bit mask for GPIO_EXTIPSEL9 */
#define _GPIO_EXTIPSELH_EXTIPSEL9_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_PORTA                 0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_PORTB                 0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_PORTC                 0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_PORTD                 0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL9_PORTF                 0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_DEFAULT                (_GPIO_EXTIPSELH_EXTIPSEL9_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTA                  (_GPIO_EXTIPSELH_EXTIPSEL9_PORTA << 4)     /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTB                  (_GPIO_EXTIPSELH_EXTIPSEL9_PORTB << 4)     /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTC                  (_GPIO_EXTIPSELH_EXTIPSEL9_PORTC << 4)     /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTD                  (_GPIO_EXTIPSELH_EXTIPSEL9_PORTD << 4)     /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTF                  (_GPIO_EXTIPSELH_EXTIPSEL9_PORTF << 4)     /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_SHIFT                8                                          /**< Shift value for GPIO_EXTIPSEL10 */
#define _GPIO_EXTIPSELH_EXTIPSEL10_MASK                 0xF00UL                                    /**< Bit mask for GPIO_EXTIPSEL10 */
#define _GPIO_EXTIPSELH_EXTIPSEL10_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL10_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL10_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL10_PORTA << 8)    /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL10_PORTB << 8)    /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL10_PORTC << 8)    /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL10_PORTD << 8)    /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL10_PORTF << 8)    /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_SHIFT                12                                         /**< Shift value for GPIO_EXTIPSEL11 */
#define _GPIO_EXTIPSELH_EXTIPSEL11_MASK                 0xF000UL                                   /**< Bit mask for GPIO_EXTIPSEL11 */
#define _GPIO_EXTIPSELH_EXTIPSEL11_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL11_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL11_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL11_PORTA << 12)   /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL11_PORTB << 12)   /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL11_PORTC << 12)   /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL11_PORTD << 12)   /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL11_PORTF << 12)   /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_SHIFT                16                                         /**< Shift value for GPIO_EXTIPSEL12 */
#define _GPIO_EXTIPSELH_EXTIPSEL12_MASK                 0xF0000UL                                  /**< Bit mask for GPIO_EXTIPSEL12 */
#define _GPIO_EXTIPSELH_EXTIPSEL12_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL12_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL12_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL12_PORTA << 16)   /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL12_PORTB << 16)   /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL12_PORTC << 16)   /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL12_PORTD << 16)   /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL12_PORTF << 16)   /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_SHIFT                20                                         /**< Shift value for GPIO_EXTIPSEL13 */
#define _GPIO_EXTIPSELH_EXTIPSEL13_MASK                 0xF00000UL                                 /**< Bit mask for GPIO_EXTIPSEL13 */
#define _GPIO_EXTIPSELH_EXTIPSEL13_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL13_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL13_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL13_PORTA << 20)   /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL13_PORTB << 20)   /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL13_PORTC << 20)   /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL13_PORTD << 20)   /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL13_PORTF << 20)   /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_SHIFT                24                                         /**< Shift value for GPIO_EXTIPSEL14 */
#define _GPIO_EXTIPSELH_EXTIPSEL14_MASK                 0xF000000UL                                /**< Bit mask for GPIO_EXTIPSEL14 */
#define _GPIO_EXTIPSELH_EXTIPSEL14_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL14_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL14_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL14_PORTA << 24)   /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL14_PORTB << 24)   /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL14_PORTC << 24)   /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL14_PORTD << 24)   /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL14_PORTF << 24)   /**< Shifted mode PORTF for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_SHIFT                28                                         /**< Shift value for GPIO_EXTIPSEL15 */
#define _GPIO_EXTIPSELH_EXTIPSEL15_MASK                 0xF0000000UL                               /**< Bit mask for GPIO_EXTIPSEL15 */
#define _GPIO_EXTIPSELH_EXTIPSEL15_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_PORTA                0x00000000UL                               /**< Mode PORTA for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_PORTB                0x00000001UL                               /**< Mode PORTB for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_PORTC                0x00000002UL                               /**< Mode PORTC for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_PORTD                0x00000003UL                               /**< Mode PORTD for GPIO_EXTIPSELH */
#define _GPIO_EXTIPSELH_EXTIPSEL15_PORTF                0x00000005UL                               /**< Mode PORTF for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_DEFAULT               (_GPIO_EXTIPSELH_EXTIPSEL15_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTA                 (_GPIO_EXTIPSELH_EXTIPSEL15_PORTA << 28)   /**< Shifted mode PORTA for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTB                 (_GPIO_EXTIPSELH_EXTIPSEL15_PORTB << 28)   /**< Shifted mode PORTB for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTC                 (_GPIO_EXTIPSELH_EXTIPSEL15_PORTC << 28)   /**< Shifted mode PORTC for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTD                 (_GPIO_EXTIPSELH_EXTIPSEL15_PORTD << 28)   /**< Shifted mode PORTD for GPIO_EXTIPSELH */
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTF                 (_GPIO_EXTIPSELH_EXTIPSEL15_PORTF << 28)   /**< Shifted mode PORTF for GPIO_EXTIPSELH */

/* Bit fields for GPIO EXTIPINSELL */
#define _GPIO_EXTIPINSELL_RESETVALUE                    0x32103210UL                                  /**< Default value for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_MASK                          0x33333333UL                                  /**< Mask for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_SHIFT             0                                             /**< Shift value for GPIO_EXTIPINSEL0 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_MASK              0x3UL                                         /**< Bit mask for GPIO_EXTIPINSEL0 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT           0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0              0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1              0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2              0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3              0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0               (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0 << 0)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1               (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1 << 0)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2               (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2 << 0)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3               (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3 << 0)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_SHIFT             4                                             /**< Shift value for GPIO_EXTIPINSEL1 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_MASK              0x30UL                                        /**< Bit mask for GPIO_EXTIPINSEL1 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0              0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT           0x00000001UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1              0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2              0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3              0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0               (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0 << 4)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1               (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1 << 4)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2               (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2 << 4)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3               (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3 << 4)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_SHIFT             8                                             /**< Shift value for GPIO_EXTIPINSEL2 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_MASK              0x300UL                                       /**< Bit mask for GPIO_EXTIPINSEL2 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0              0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1              0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT           0x00000002UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2              0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3              0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0               (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0 << 8)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1               (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1 << 8)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2               (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2 << 8)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3               (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3 << 8)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_SHIFT             12                                            /**< Shift value for GPIO_EXTIPINSEL3 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_MASK              0x3000UL                                      /**< Bit mask for GPIO_EXTIPINSEL3 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0              0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1              0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2              0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT           0x00000003UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3              0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0               (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0 << 12)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1               (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1 << 12)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2               (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2 << 12)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3               (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3 << 12)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_SHIFT             16                                            /**< Shift value for GPIO_EXTIPINSEL4 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_MASK              0x30000UL                                     /**< Bit mask for GPIO_EXTIPINSEL4 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT           0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN4              0x00000000UL                                  /**< Mode PIN4 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN5              0x00000001UL                                  /**< Mode PIN5 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN6              0x00000002UL                                  /**< Mode PIN6 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN7              0x00000003UL                                  /**< Mode PIN7 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN4               (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN4 << 16)    /**< Shifted mode PIN4 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN5               (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN5 << 16)    /**< Shifted mode PIN5 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN6               (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN6 << 16)    /**< Shifted mode PIN6 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN7               (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN7 << 16)    /**< Shifted mode PIN7 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_SHIFT             20                                            /**< Shift value for GPIO_EXTIPINSEL5 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_MASK              0x300000UL                                    /**< Bit mask for GPIO_EXTIPINSEL5 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN4              0x00000000UL                                  /**< Mode PIN4 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT           0x00000001UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN5              0x00000001UL                                  /**< Mode PIN5 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN6              0x00000002UL                                  /**< Mode PIN6 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN7              0x00000003UL                                  /**< Mode PIN7 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN4               (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN4 << 20)    /**< Shifted mode PIN4 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN5               (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN5 << 20)    /**< Shifted mode PIN5 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN6               (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN6 << 20)    /**< Shifted mode PIN6 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN7               (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN7 << 20)    /**< Shifted mode PIN7 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_SHIFT             24                                            /**< Shift value for GPIO_EXTIPINSEL6 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_MASK              0x3000000UL                                   /**< Bit mask for GPIO_EXTIPINSEL6 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN4              0x00000000UL                                  /**< Mode PIN4 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN5              0x00000001UL                                  /**< Mode PIN5 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT           0x00000002UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN6              0x00000002UL                                  /**< Mode PIN6 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN7              0x00000003UL                                  /**< Mode PIN7 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN4               (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN4 << 24)    /**< Shifted mode PIN4 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN5               (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN5 << 24)    /**< Shifted mode PIN5 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN6               (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN6 << 24)    /**< Shifted mode PIN6 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN7               (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN7 << 24)    /**< Shifted mode PIN7 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_SHIFT             28                                            /**< Shift value for GPIO_EXTIPINSEL7 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_MASK              0x30000000UL                                  /**< Bit mask for GPIO_EXTIPINSEL7 */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN4              0x00000000UL                                  /**< Mode PIN4 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN5              0x00000001UL                                  /**< Mode PIN5 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN6              0x00000002UL                                  /**< Mode PIN6 for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT           0x00000003UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN7              0x00000003UL                                  /**< Mode PIN7 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN4               (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN4 << 28)    /**< Shifted mode PIN4 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN5               (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN5 << 28)    /**< Shifted mode PIN5 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN6               (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN6 << 28)    /**< Shifted mode PIN6 for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT            (_GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN7               (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN7 << 28)    /**< Shifted mode PIN7 for GPIO_EXTIPINSELL */

/* Bit fields for GPIO EXTIPINSELH */
#define _GPIO_EXTIPINSELH_RESETVALUE                    0x32103210UL                                   /**< Default value for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_MASK                          0x33333333UL                                   /**< Mask for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_SHIFT             0                                              /**< Shift value for GPIO_EXTIPINSEL8 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_MASK              0x3UL                                          /**< Bit mask for GPIO_EXTIPINSEL8 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_PIN8              0x00000000UL                                   /**< Mode PIN8 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_PIN9              0x00000001UL                                   /**< Mode PIN9 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_PIN10             0x00000002UL                                   /**< Mode PIN10 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL8_PIN11             0x00000003UL                                   /**< Mode PIN11 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL8_DEFAULT            (_GPIO_EXTIPINSELH_EXTIPINSEL8_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL8_PIN8               (_GPIO_EXTIPINSELH_EXTIPINSEL8_PIN8 << 0)      /**< Shifted mode PIN8 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL8_PIN9               (_GPIO_EXTIPINSELH_EXTIPINSEL8_PIN9 << 0)      /**< Shifted mode PIN9 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL8_PIN10              (_GPIO_EXTIPINSELH_EXTIPINSEL8_PIN10 << 0)     /**< Shifted mode PIN10 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL8_PIN11              (_GPIO_EXTIPINSELH_EXTIPINSEL8_PIN11 << 0)     /**< Shifted mode PIN11 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_SHIFT             4                                              /**< Shift value for GPIO_EXTIPINSEL9 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_MASK              0x30UL                                         /**< Bit mask for GPIO_EXTIPINSEL9 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_PIN8              0x00000000UL                                   /**< Mode PIN8 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_DEFAULT           0x00000001UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_PIN9              0x00000001UL                                   /**< Mode PIN9 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_PIN10             0x00000002UL                                   /**< Mode PIN10 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL9_PIN11             0x00000003UL                                   /**< Mode PIN11 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL9_PIN8               (_GPIO_EXTIPINSELH_EXTIPINSEL9_PIN8 << 4)      /**< Shifted mode PIN8 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL9_DEFAULT            (_GPIO_EXTIPINSELH_EXTIPINSEL9_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL9_PIN9               (_GPIO_EXTIPINSELH_EXTIPINSEL9_PIN9 << 4)      /**< Shifted mode PIN9 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL9_PIN10              (_GPIO_EXTIPINSELH_EXTIPINSEL9_PIN10 << 4)     /**< Shifted mode PIN10 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL9_PIN11              (_GPIO_EXTIPINSELH_EXTIPINSEL9_PIN11 << 4)     /**< Shifted mode PIN11 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_SHIFT            8                                              /**< Shift value for GPIO_EXTIPINSEL10 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_MASK             0x300UL                                        /**< Bit mask for GPIO_EXTIPINSEL10 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_PIN8             0x00000000UL                                   /**< Mode PIN8 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_PIN9             0x00000001UL                                   /**< Mode PIN9 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_DEFAULT          0x00000002UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_PIN10            0x00000002UL                                   /**< Mode PIN10 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL10_PIN11            0x00000003UL                                   /**< Mode PIN11 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL10_PIN8              (_GPIO_EXTIPINSELH_EXTIPINSEL10_PIN8 << 8)     /**< Shifted mode PIN8 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL10_PIN9              (_GPIO_EXTIPINSELH_EXTIPINSEL10_PIN9 << 8)     /**< Shifted mode PIN9 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL10_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL10_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL10_PIN10             (_GPIO_EXTIPINSELH_EXTIPINSEL10_PIN10 << 8)    /**< Shifted mode PIN10 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL10_PIN11             (_GPIO_EXTIPINSELH_EXTIPINSEL10_PIN11 << 8)    /**< Shifted mode PIN11 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_SHIFT            12                                             /**< Shift value for GPIO_EXTIPINSEL11 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_MASK             0x3000UL                                       /**< Bit mask for GPIO_EXTIPINSEL11 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_PIN8             0x00000000UL                                   /**< Mode PIN8 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_PIN9             0x00000001UL                                   /**< Mode PIN9 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_PIN10            0x00000002UL                                   /**< Mode PIN10 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_DEFAULT          0x00000003UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL11_PIN11            0x00000003UL                                   /**< Mode PIN11 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL11_PIN8              (_GPIO_EXTIPINSELH_EXTIPINSEL11_PIN8 << 12)    /**< Shifted mode PIN8 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL11_PIN9              (_GPIO_EXTIPINSELH_EXTIPINSEL11_PIN9 << 12)    /**< Shifted mode PIN9 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL11_PIN10             (_GPIO_EXTIPINSELH_EXTIPINSEL11_PIN10 << 12)   /**< Shifted mode PIN10 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL11_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL11_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL11_PIN11             (_GPIO_EXTIPINSELH_EXTIPINSEL11_PIN11 << 12)   /**< Shifted mode PIN11 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_SHIFT            16                                             /**< Shift value for GPIO_EXTIPINSEL12 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_MASK             0x30000UL                                      /**< Bit mask for GPIO_EXTIPINSEL12 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_DEFAULT          0x00000000UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_PIN12            0x00000000UL                                   /**< Mode PIN12 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_PIN13            0x00000001UL                                   /**< Mode PIN13 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_PIN14            0x00000002UL                                   /**< Mode PIN14 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL12_PIN15            0x00000003UL                                   /**< Mode PIN15 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL12_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL12_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL12_PIN12             (_GPIO_EXTIPINSELH_EXTIPINSEL12_PIN12 << 16)   /**< Shifted mode PIN12 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL12_PIN13             (_GPIO_EXTIPINSELH_EXTIPINSEL12_PIN13 << 16)   /**< Shifted mode PIN13 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL12_PIN14             (_GPIO_EXTIPINSELH_EXTIPINSEL12_PIN14 << 16)   /**< Shifted mode PIN14 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL12_PIN15             (_GPIO_EXTIPINSELH_EXTIPINSEL12_PIN15 << 16)   /**< Shifted mode PIN15 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_SHIFT            20                                             /**< Shift value for GPIO_EXTIPINSEL13 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_MASK             0x300000UL                                     /**< Bit mask for GPIO_EXTIPINSEL13 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_PIN12            0x00000000UL                                   /**< Mode PIN12 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_DEFAULT          0x00000001UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_PIN13            0x00000001UL                                   /**< Mode PIN13 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_PIN14            0x00000002UL                                   /**< Mode PIN14 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL13_PIN15            0x00000003UL                                   /**< Mode PIN15 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL13_PIN12             (_GPIO_EXTIPINSELH_EXTIPINSEL13_PIN12 << 20)   /**< Shifted mode PIN12 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL13_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL13_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL13_PIN13             (_GPIO_EXTIPINSELH_EXTIPINSEL13_PIN13 << 20)   /**< Shifted mode PIN13 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL13_PIN14             (_GPIO_EXTIPINSELH_EXTIPINSEL13_PIN14 << 20)   /**< Shifted mode PIN14 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL13_PIN15             (_GPIO_EXTIPINSELH_EXTIPINSEL13_PIN15 << 20)   /**< Shifted mode PIN15 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_SHIFT            24                                             /**< Shift value for GPIO_EXTIPINSEL14 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_MASK             0x3000000UL                                    /**< Bit mask for GPIO_EXTIPINSEL14 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_PIN12            0x00000000UL                                   /**< Mode PIN12 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_PIN13            0x00000001UL                                   /**< Mode PIN13 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_DEFAULT          0x00000002UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_PIN14            0x00000002UL                                   /**< Mode PIN14 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL14_PIN15            0x00000003UL                                   /**< Mode PIN15 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL14_PIN12             (_GPIO_EXTIPINSELH_EXTIPINSEL14_PIN12 << 24)   /**< Shifted mode PIN12 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL14_PIN13             (_GPIO_EXTIPINSELH_EXTIPINSEL14_PIN13 << 24)   /**< Shifted mode PIN13 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL14_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL14_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL14_PIN14             (_GPIO_EXTIPINSELH_EXTIPINSEL14_PIN14 << 24)   /**< Shifted mode PIN14 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL14_PIN15             (_GPIO_EXTIPINSELH_EXTIPINSEL14_PIN15 << 24)   /**< Shifted mode PIN15 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_SHIFT            28                                             /**< Shift value for GPIO_EXTIPINSEL15 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_MASK             0x30000000UL                                   /**< Bit mask for GPIO_EXTIPINSEL15 */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_PIN12            0x00000000UL                                   /**< Mode PIN12 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_PIN13            0x00000001UL                                   /**< Mode PIN13 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_PIN14            0x00000002UL                                   /**< Mode PIN14 for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_DEFAULT          0x00000003UL                                   /**< Mode DEFAULT for GPIO_EXTIPINSELH */
#define _GPIO_EXTIPINSELH_EXTIPINSEL15_PIN15            0x00000003UL                                   /**< Mode PIN15 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL15_PIN12             (_GPIO_EXTIPINSELH_EXTIPINSEL15_PIN12 << 28)   /**< Shifted mode PIN12 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL15_PIN13             (_GPIO_EXTIPINSELH_EXTIPINSEL15_PIN13 << 28)   /**< Shifted mode PIN13 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL15_PIN14             (_GPIO_EXTIPINSELH_EXTIPINSEL15_PIN14 << 28)   /**< Shifted mode PIN14 for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL15_DEFAULT           (_GPIO_EXTIPINSELH_EXTIPINSEL15_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH */
#define GPIO_EXTIPINSELH_EXTIPINSEL15_PIN15             (_GPIO_EXTIPINSELH_EXTIPINSEL15_PIN15 << 28)   /**< Shifted mode PIN15 for GPIO_EXTIPINSELH */

/* Bit fields for GPIO EXTIRISE */
#define _GPIO_EXTIRISE_RESETVALUE                       0x00000000UL                           /**< Default value for GPIO_EXTIRISE */
#define _GPIO_EXTIRISE_MASK                             0x0000FFFFUL                           /**< Mask for GPIO_EXTIRISE */
#define _GPIO_EXTIRISE_EXTIRISE_SHIFT                   0                                      /**< Shift value for GPIO_EXTIRISE */
#define _GPIO_EXTIRISE_EXTIRISE_MASK                    0xFFFFUL                               /**< Bit mask for GPIO_EXTIRISE */
#define _GPIO_EXTIRISE_EXTIRISE_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for GPIO_EXTIRISE */
#define GPIO_EXTIRISE_EXTIRISE_DEFAULT                  (_GPIO_EXTIRISE_EXTIRISE_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EXTIRISE */

/* Bit fields for GPIO EXTIFALL */
#define _GPIO_EXTIFALL_RESETVALUE                       0x00000000UL                           /**< Default value for GPIO_EXTIFALL */
#define _GPIO_EXTIFALL_MASK                             0x0000FFFFUL                           /**< Mask for GPIO_EXTIFALL */
#define _GPIO_EXTIFALL_EXTIFALL_SHIFT                   0                                      /**< Shift value for GPIO_EXTIFALL */
#define _GPIO_EXTIFALL_EXTIFALL_MASK                    0xFFFFUL                               /**< Bit mask for GPIO_EXTIFALL */
#define _GPIO_EXTIFALL_EXTIFALL_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for GPIO_EXTIFALL */
#define GPIO_EXTIFALL_EXTIFALL_DEFAULT                  (_GPIO_EXTIFALL_EXTIFALL_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EXTIFALL */

/* Bit fields for GPIO EXTILEVEL */
#define _GPIO_EXTILEVEL_RESETVALUE                      0x00000000UL                            /**< Default value for GPIO_EXTILEVEL */
#define _GPIO_EXTILEVEL_MASK                            0x13130000UL                            /**< Mask for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU0                           (0x1UL << 16)                           /**< EM4 Wake Up Level for EM4WU0 Pin */
#define _GPIO_EXTILEVEL_EM4WU0_SHIFT                    16                                      /**< Shift value for GPIO_EM4WU0 */
#define _GPIO_EXTILEVEL_EM4WU0_MASK                     0x10000UL                               /**< Bit mask for GPIO_EM4WU0 */
#define _GPIO_EXTILEVEL_EM4WU0_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU0_DEFAULT                   (_GPIO_EXTILEVEL_EM4WU0_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU1                           (0x1UL << 17)                           /**< EM4 Wake Up Level for EM4WU1 Pin */
#define _GPIO_EXTILEVEL_EM4WU1_SHIFT                    17                                      /**< Shift value for GPIO_EM4WU1 */
#define _GPIO_EXTILEVEL_EM4WU1_MASK                     0x20000UL                               /**< Bit mask for GPIO_EM4WU1 */
#define _GPIO_EXTILEVEL_EM4WU1_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU1_DEFAULT                   (_GPIO_EXTILEVEL_EM4WU1_DEFAULT << 17)  /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU4                           (0x1UL << 20)                           /**< EM4 Wake Up Level for EM4WU4 Pin */
#define _GPIO_EXTILEVEL_EM4WU4_SHIFT                    20                                      /**< Shift value for GPIO_EM4WU4 */
#define _GPIO_EXTILEVEL_EM4WU4_MASK                     0x100000UL                              /**< Bit mask for GPIO_EM4WU4 */
#define _GPIO_EXTILEVEL_EM4WU4_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU4_DEFAULT                   (_GPIO_EXTILEVEL_EM4WU4_DEFAULT << 20)  /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU8                           (0x1UL << 24)                           /**< EM4 Wake Up Level for EM4WU8 Pin */
#define _GPIO_EXTILEVEL_EM4WU8_SHIFT                    24                                      /**< Shift value for GPIO_EM4WU8 */
#define _GPIO_EXTILEVEL_EM4WU8_MASK                     0x1000000UL                             /**< Bit mask for GPIO_EM4WU8 */
#define _GPIO_EXTILEVEL_EM4WU8_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU8_DEFAULT                   (_GPIO_EXTILEVEL_EM4WU8_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU9                           (0x1UL << 25)                           /**< EM4 Wake Up Level for EM4WU9 Pin */
#define _GPIO_EXTILEVEL_EM4WU9_SHIFT                    25                                      /**< Shift value for GPIO_EM4WU9 */
#define _GPIO_EXTILEVEL_EM4WU9_MASK                     0x2000000UL                             /**< Bit mask for GPIO_EM4WU9 */
#define _GPIO_EXTILEVEL_EM4WU9_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU9_DEFAULT                   (_GPIO_EXTILEVEL_EM4WU9_DEFAULT << 25)  /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU12                          (0x1UL << 28)                           /**< EM4 Wake Up Level for EM4WU12 Pin */
#define _GPIO_EXTILEVEL_EM4WU12_SHIFT                   28                                      /**< Shift value for GPIO_EM4WU12 */
#define _GPIO_EXTILEVEL_EM4WU12_MASK                    0x10000000UL                            /**< Bit mask for GPIO_EM4WU12 */
#define _GPIO_EXTILEVEL_EM4WU12_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for GPIO_EXTILEVEL */
#define GPIO_EXTILEVEL_EM4WU12_DEFAULT                  (_GPIO_EXTILEVEL_EM4WU12_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTILEVEL */

/* Bit fields for GPIO IF */
#define _GPIO_IF_RESETVALUE                             0x00000000UL                   /**< Default value for GPIO_IF */
#define _GPIO_IF_MASK                                   0xFFFFFFFFUL                   /**< Mask for GPIO_IF */
#define _GPIO_IF_EXT_SHIFT                              0                              /**< Shift value for GPIO_EXT */
#define _GPIO_IF_EXT_MASK                               0xFFFFUL                       /**< Bit mask for GPIO_EXT */
#define _GPIO_IF_EXT_DEFAULT                            0x00000000UL                   /**< Mode DEFAULT for GPIO_IF */
#define GPIO_IF_EXT_DEFAULT                             (_GPIO_IF_EXT_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_IF */
#define _GPIO_IF_EM4WU_SHIFT                            16                             /**< Shift value for GPIO_EM4WU */
#define _GPIO_IF_EM4WU_MASK                             0xFFFF0000UL                   /**< Bit mask for GPIO_EM4WU */
#define _GPIO_IF_EM4WU_DEFAULT                          0x00000000UL                   /**< Mode DEFAULT for GPIO_IF */
#define GPIO_IF_EM4WU_DEFAULT                           (_GPIO_IF_EM4WU_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_IF */

/* Bit fields for GPIO IFS */
#define _GPIO_IFS_RESETVALUE                            0x00000000UL                    /**< Default value for GPIO_IFS */
#define _GPIO_IFS_MASK                                  0xFFFFFFFFUL                    /**< Mask for GPIO_IFS */
#define _GPIO_IFS_EXT_SHIFT                             0                               /**< Shift value for GPIO_EXT */
#define _GPIO_IFS_EXT_MASK                              0xFFFFUL                        /**< Bit mask for GPIO_EXT */
#define _GPIO_IFS_EXT_DEFAULT                           0x00000000UL                    /**< Mode DEFAULT for GPIO_IFS */
#define GPIO_IFS_EXT_DEFAULT                            (_GPIO_IFS_EXT_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_IFS */
#define _GPIO_IFS_EM4WU_SHIFT                           16                              /**< Shift value for GPIO_EM4WU */
#define _GPIO_IFS_EM4WU_MASK                            0xFFFF0000UL                    /**< Bit mask for GPIO_EM4WU */
#define _GPIO_IFS_EM4WU_DEFAULT                         0x00000000UL                    /**< Mode DEFAULT for GPIO_IFS */
#define GPIO_IFS_EM4WU_DEFAULT                          (_GPIO_IFS_EM4WU_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_IFS */

/* Bit fields for GPIO IFC */
#define _GPIO_IFC_RESETVALUE                            0x00000000UL                    /**< Default value for GPIO_IFC */
#define _GPIO_IFC_MASK                                  0xFFFFFFFFUL                    /**< Mask for GPIO_IFC */
#define _GPIO_IFC_EXT_SHIFT                             0                               /**< Shift value for GPIO_EXT */
#define _GPIO_IFC_EXT_MASK                              0xFFFFUL                        /**< Bit mask for GPIO_EXT */
#define _GPIO_IFC_EXT_DEFAULT                           0x00000000UL                    /**< Mode DEFAULT for GPIO_IFC */
#define GPIO_IFC_EXT_DEFAULT                            (_GPIO_IFC_EXT_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_IFC */
#define _GPIO_IFC_EM4WU_SHIFT                           16                              /**< Shift value for GPIO_EM4WU */
#define _GPIO_IFC_EM4WU_MASK                            0xFFFF0000UL                    /**< Bit mask for GPIO_EM4WU */
#define _GPIO_IFC_EM4WU_DEFAULT                         0x00000000UL                    /**< Mode DEFAULT for GPIO_IFC */
#define GPIO_IFC_EM4WU_DEFAULT                          (_GPIO_IFC_EM4WU_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_IFC */

/* Bit fields for GPIO IEN */
#define _GPIO_IEN_RESETVALUE                            0x00000000UL                    /**< Default value for GPIO_IEN */
#define _GPIO_IEN_MASK                                  0xFFFFFFFFUL                    /**< Mask for GPIO_IEN */
#define _GPIO_IEN_EXT_SHIFT                             0                               /**< Shift value for GPIO_EXT */
#define _GPIO_IEN_EXT_MASK                              0xFFFFUL                        /**< Bit mask for GPIO_EXT */
#define _GPIO_IEN_EXT_DEFAULT                           0x00000000UL                    /**< Mode DEFAULT for GPIO_IEN */
#define GPIO_IEN_EXT_DEFAULT                            (_GPIO_IEN_EXT_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_IEN */
#define _GPIO_IEN_EM4WU_SHIFT                           16                              /**< Shift value for GPIO_EM4WU */
#define _GPIO_IEN_EM4WU_MASK                            0xFFFF0000UL                    /**< Bit mask for GPIO_EM4WU */
#define _GPIO_IEN_EM4WU_DEFAULT                         0x00000000UL                    /**< Mode DEFAULT for GPIO_IEN */
#define GPIO_IEN_EM4WU_DEFAULT                          (_GPIO_IEN_EM4WU_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_IEN */

/* Bit fields for GPIO EM4WUEN */
#define _GPIO_EM4WUEN_RESETVALUE                        0x00000000UL                          /**< Default value for GPIO_EM4WUEN */
#define _GPIO_EM4WUEN_MASK                              0xFFFF0000UL                          /**< Mask for GPIO_EM4WUEN */
#define _GPIO_EM4WUEN_EM4WUEN_SHIFT                     16                                    /**< Shift value for GPIO_EM4WUEN */
#define _GPIO_EM4WUEN_EM4WUEN_MASK                      0xFFFF0000UL                          /**< Bit mask for GPIO_EM4WUEN */
#define _GPIO_EM4WUEN_EM4WUEN_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for GPIO_EM4WUEN */
#define GPIO_EM4WUEN_EM4WUEN_DEFAULT                    (_GPIO_EM4WUEN_EM4WUEN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EM4WUEN */

/* Bit fields for GPIO ROUTEPEN */
#define _GPIO_ROUTEPEN_RESETVALUE                       0x0000000FUL                              /**< Default value for GPIO_ROUTEPEN */
#define _GPIO_ROUTEPEN_MASK                             0x001F001FUL                              /**< Mask for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWCLKTCKPEN                       (0x1UL << 0)                              /**< Serial Wire Clock and JTAG Test Clock Pin Enable */
#define _GPIO_ROUTEPEN_SWCLKTCKPEN_SHIFT                0                                         /**< Shift value for GPIO_SWCLKTCKPEN */
#define _GPIO_ROUTEPEN_SWCLKTCKPEN_MASK                 0x1UL                                     /**< Bit mask for GPIO_SWCLKTCKPEN */
#define _GPIO_ROUTEPEN_SWCLKTCKPEN_DEFAULT              0x00000001UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWCLKTCKPEN_DEFAULT               (_GPIO_ROUTEPEN_SWCLKTCKPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWDIOTMSPEN                       (0x1UL << 1)                              /**< Serial Wire Data and JTAG Test Mode Select Pin Enable */
#define _GPIO_ROUTEPEN_SWDIOTMSPEN_SHIFT                1                                         /**< Shift value for GPIO_SWDIOTMSPEN */
#define _GPIO_ROUTEPEN_SWDIOTMSPEN_MASK                 0x2UL                                     /**< Bit mask for GPIO_SWDIOTMSPEN */
#define _GPIO_ROUTEPEN_SWDIOTMSPEN_DEFAULT              0x00000001UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWDIOTMSPEN_DEFAULT               (_GPIO_ROUTEPEN_SWDIOTMSPEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_TDOPEN                            (0x1UL << 2)                              /**< JTAG Test Debug Output Pin Enable */
#define _GPIO_ROUTEPEN_TDOPEN_SHIFT                     2                                         /**< Shift value for GPIO_TDOPEN */
#define _GPIO_ROUTEPEN_TDOPEN_MASK                      0x4UL                                     /**< Bit mask for GPIO_TDOPEN */
#define _GPIO_ROUTEPEN_TDOPEN_DEFAULT                   0x00000001UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_TDOPEN_DEFAULT                    (_GPIO_ROUTEPEN_TDOPEN_DEFAULT << 2)      /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_TDIPEN                            (0x1UL << 3)                              /**< JTAG Test Debug Input Pin Enable */
#define _GPIO_ROUTEPEN_TDIPEN_SHIFT                     3                                         /**< Shift value for GPIO_TDIPEN */
#define _GPIO_ROUTEPEN_TDIPEN_MASK                      0x8UL                                     /**< Bit mask for GPIO_TDIPEN */
#define _GPIO_ROUTEPEN_TDIPEN_DEFAULT                   0x00000001UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_TDIPEN_DEFAULT                    (_GPIO_ROUTEPEN_TDIPEN_DEFAULT << 3)      /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWVPEN                            (0x1UL << 4)                              /**< Serial Wire Viewer Output Pin Enable */
#define _GPIO_ROUTEPEN_SWVPEN_SHIFT                     4                                         /**< Shift value for GPIO_SWVPEN */
#define _GPIO_ROUTEPEN_SWVPEN_MASK                      0x10UL                                    /**< Bit mask for GPIO_SWVPEN */
#define _GPIO_ROUTEPEN_SWVPEN_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_SWVPEN_DEFAULT                    (_GPIO_ROUTEPEN_SWVPEN_DEFAULT << 4)      /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTCLKPEN                        (0x1UL << 16)                             /**< ETM Trace Clock Pin Enable */
#define _GPIO_ROUTEPEN_ETMTCLKPEN_SHIFT                 16                                        /**< Shift value for GPIO_ETMTCLKPEN */
#define _GPIO_ROUTEPEN_ETMTCLKPEN_MASK                  0x10000UL                                 /**< Bit mask for GPIO_ETMTCLKPEN */
#define _GPIO_ROUTEPEN_ETMTCLKPEN_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTCLKPEN_DEFAULT                (_GPIO_ROUTEPEN_ETMTCLKPEN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD0PEN                         (0x1UL << 17)                             /**< ETM Trace Data Pin Enable */
#define _GPIO_ROUTEPEN_ETMTD0PEN_SHIFT                  17                                        /**< Shift value for GPIO_ETMTD0PEN */
#define _GPIO_ROUTEPEN_ETMTD0PEN_MASK                   0x20000UL                                 /**< Bit mask for GPIO_ETMTD0PEN */
#define _GPIO_ROUTEPEN_ETMTD0PEN_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD0PEN_DEFAULT                 (_GPIO_ROUTEPEN_ETMTD0PEN_DEFAULT << 17)  /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD1PEN                         (0x1UL << 18)                             /**< ETM Trace Data Pin Enable */
#define _GPIO_ROUTEPEN_ETMTD1PEN_SHIFT                  18                                        /**< Shift value for GPIO_ETMTD1PEN */
#define _GPIO_ROUTEPEN_ETMTD1PEN_MASK                   0x40000UL                                 /**< Bit mask for GPIO_ETMTD1PEN */
#define _GPIO_ROUTEPEN_ETMTD1PEN_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD1PEN_DEFAULT                 (_GPIO_ROUTEPEN_ETMTD1PEN_DEFAULT << 18)  /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD2PEN                         (0x1UL << 19)                             /**< ETM Trace Data Pin Enable */
#define _GPIO_ROUTEPEN_ETMTD2PEN_SHIFT                  19                                        /**< Shift value for GPIO_ETMTD2PEN */
#define _GPIO_ROUTEPEN_ETMTD2PEN_MASK                   0x80000UL                                 /**< Bit mask for GPIO_ETMTD2PEN */
#define _GPIO_ROUTEPEN_ETMTD2PEN_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD2PEN_DEFAULT                 (_GPIO_ROUTEPEN_ETMTD2PEN_DEFAULT << 19)  /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD3PEN                         (0x1UL << 20)                             /**< ETM Trace Data Pin Enable */
#define _GPIO_ROUTEPEN_ETMTD3PEN_SHIFT                  20                                        /**< Shift value for GPIO_ETMTD3PEN */
#define _GPIO_ROUTEPEN_ETMTD3PEN_MASK                   0x100000UL                                /**< Bit mask for GPIO_ETMTD3PEN */
#define _GPIO_ROUTEPEN_ETMTD3PEN_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTEPEN */
#define GPIO_ROUTEPEN_ETMTD3PEN_DEFAULT                 (_GPIO_ROUTEPEN_ETMTD3PEN_DEFAULT << 20)  /**< Shifted mode DEFAULT for GPIO_ROUTEPEN */

/* Bit fields for GPIO ROUTELOC0 */
#define _GPIO_ROUTELOC0_RESETVALUE                      0x00000000UL                          /**< Default value for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_MASK                            0x00000003UL                          /**< Mask for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_SWVLOC_SHIFT                    0                                     /**< Shift value for GPIO_SWVLOC */
#define _GPIO_ROUTELOC0_SWVLOC_MASK                     0x3UL                                 /**< Bit mask for GPIO_SWVLOC */
#define _GPIO_ROUTELOC0_SWVLOC_LOC0                     0x00000000UL                          /**< Mode LOC0 for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_SWVLOC_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_SWVLOC_LOC1                     0x00000001UL                          /**< Mode LOC1 for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_SWVLOC_LOC2                     0x00000002UL                          /**< Mode LOC2 for GPIO_ROUTELOC0 */
#define _GPIO_ROUTELOC0_SWVLOC_LOC3                     0x00000003UL                          /**< Mode LOC3 for GPIO_ROUTELOC0 */
#define GPIO_ROUTELOC0_SWVLOC_LOC0                      (_GPIO_ROUTELOC0_SWVLOC_LOC0 << 0)    /**< Shifted mode LOC0 for GPIO_ROUTELOC0 */
#define GPIO_ROUTELOC0_SWVLOC_DEFAULT                   (_GPIO_ROUTELOC0_SWVLOC_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_ROUTELOC0 */
#define GPIO_ROUTELOC0_SWVLOC_LOC1                      (_GPIO_ROUTELOC0_SWVLOC_LOC1 << 0)    /**< Shifted mode LOC1 for GPIO_ROUTELOC0 */
#define GPIO_ROUTELOC0_SWVLOC_LOC2                      (_GPIO_ROUTELOC0_SWVLOC_LOC2 << 0)    /**< Shifted mode LOC2 for GPIO_ROUTELOC0 */
#define GPIO_ROUTELOC0_SWVLOC_LOC3                      (_GPIO_ROUTELOC0_SWVLOC_LOC3 << 0)    /**< Shifted mode LOC3 for GPIO_ROUTELOC0 */

/* Bit fields for GPIO ROUTELOC1 */
#define _GPIO_ROUTELOC1_RESETVALUE                      0x00000000UL                              /**< Default value for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_MASK                            0x0C30C303UL                              /**< Mask for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_SHIFT                0                                         /**< Shift value for GPIO_ETMTCLKLOC */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_MASK                 0x3UL                                     /**< Bit mask for GPIO_ETMTCLKLOC */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_LOC0                 0x00000000UL                              /**< Mode LOC0 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_LOC1                 0x00000001UL                              /**< Mode LOC1 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_LOC2                 0x00000002UL                              /**< Mode LOC2 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTCLKLOC_LOC3                 0x00000003UL                              /**< Mode LOC3 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTCLKLOC_LOC0                  (_GPIO_ROUTELOC1_ETMTCLKLOC_LOC0 << 0)    /**< Shifted mode LOC0 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTCLKLOC_DEFAULT               (_GPIO_ROUTELOC1_ETMTCLKLOC_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTCLKLOC_LOC1                  (_GPIO_ROUTELOC1_ETMTCLKLOC_LOC1 << 0)    /**< Shifted mode LOC1 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTCLKLOC_LOC2                  (_GPIO_ROUTELOC1_ETMTCLKLOC_LOC2 << 0)    /**< Shifted mode LOC2 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTCLKLOC_LOC3                  (_GPIO_ROUTELOC1_ETMTCLKLOC_LOC3 << 0)    /**< Shifted mode LOC3 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD0LOC_SHIFT                 8                                         /**< Shift value for GPIO_ETMTD0LOC */
#define _GPIO_ROUTELOC1_ETMTD0LOC_MASK                  0x300UL                                   /**< Bit mask for GPIO_ETMTD0LOC */
#define _GPIO_ROUTELOC1_ETMTD0LOC_LOC0                  0x00000000UL                              /**< Mode LOC0 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD0LOC_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD0LOC_LOC1                  0x00000001UL                              /**< Mode LOC1 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD0LOC_LOC2                  0x00000002UL                              /**< Mode LOC2 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD0LOC_LOC3                  0x00000003UL                              /**< Mode LOC3 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD0LOC_LOC0                   (_GPIO_ROUTELOC1_ETMTD0LOC_LOC0 << 8)     /**< Shifted mode LOC0 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD0LOC_DEFAULT                (_GPIO_ROUTELOC1_ETMTD0LOC_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD0LOC_LOC1                   (_GPIO_ROUTELOC1_ETMTD0LOC_LOC1 << 8)     /**< Shifted mode LOC1 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD0LOC_LOC2                   (_GPIO_ROUTELOC1_ETMTD0LOC_LOC2 << 8)     /**< Shifted mode LOC2 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD0LOC_LOC3                   (_GPIO_ROUTELOC1_ETMTD0LOC_LOC3 << 8)     /**< Shifted mode LOC3 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD1LOC_SHIFT                 14                                        /**< Shift value for GPIO_ETMTD1LOC */
#define _GPIO_ROUTELOC1_ETMTD1LOC_MASK                  0xC000UL                                  /**< Bit mask for GPIO_ETMTD1LOC */
#define _GPIO_ROUTELOC1_ETMTD1LOC_LOC0                  0x00000000UL                              /**< Mode LOC0 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD1LOC_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD1LOC_LOC1                  0x00000001UL                              /**< Mode LOC1 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD1LOC_LOC2                  0x00000002UL                              /**< Mode LOC2 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD1LOC_LOC3                  0x00000003UL                              /**< Mode LOC3 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD1LOC_LOC0                   (_GPIO_ROUTELOC1_ETMTD1LOC_LOC0 << 14)    /**< Shifted mode LOC0 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD1LOC_DEFAULT                (_GPIO_ROUTELOC1_ETMTD1LOC_DEFAULT << 14) /**< Shifted mode DEFAULT for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD1LOC_LOC1                   (_GPIO_ROUTELOC1_ETMTD1LOC_LOC1 << 14)    /**< Shifted mode LOC1 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD1LOC_LOC2                   (_GPIO_ROUTELOC1_ETMTD1LOC_LOC2 << 14)    /**< Shifted mode LOC2 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD1LOC_LOC3                   (_GPIO_ROUTELOC1_ETMTD1LOC_LOC3 << 14)    /**< Shifted mode LOC3 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD2LOC_SHIFT                 20                                        /**< Shift value for GPIO_ETMTD2LOC */
#define _GPIO_ROUTELOC1_ETMTD2LOC_MASK                  0x300000UL                                /**< Bit mask for GPIO_ETMTD2LOC */
#define _GPIO_ROUTELOC1_ETMTD2LOC_LOC0                  0x00000000UL                              /**< Mode LOC0 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD2LOC_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD2LOC_LOC1                  0x00000001UL                              /**< Mode LOC1 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD2LOC_LOC2                  0x00000002UL                              /**< Mode LOC2 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD2LOC_LOC3                  0x00000003UL                              /**< Mode LOC3 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD2LOC_LOC0                   (_GPIO_ROUTELOC1_ETMTD2LOC_LOC0 << 20)    /**< Shifted mode LOC0 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD2LOC_DEFAULT                (_GPIO_ROUTELOC1_ETMTD2LOC_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD2LOC_LOC1                   (_GPIO_ROUTELOC1_ETMTD2LOC_LOC1 << 20)    /**< Shifted mode LOC1 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD2LOC_LOC2                   (_GPIO_ROUTELOC1_ETMTD2LOC_LOC2 << 20)    /**< Shifted mode LOC2 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD2LOC_LOC3                   (_GPIO_ROUTELOC1_ETMTD2LOC_LOC3 << 20)    /**< Shifted mode LOC3 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD3LOC_SHIFT                 26                                        /**< Shift value for GPIO_ETMTD3LOC */
#define _GPIO_ROUTELOC1_ETMTD3LOC_MASK                  0xC000000UL                               /**< Bit mask for GPIO_ETMTD3LOC */
#define _GPIO_ROUTELOC1_ETMTD3LOC_LOC0                  0x00000000UL                              /**< Mode LOC0 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD3LOC_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD3LOC_LOC1                  0x00000001UL                              /**< Mode LOC1 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD3LOC_LOC2                  0x00000002UL                              /**< Mode LOC2 for GPIO_ROUTELOC1 */
#define _GPIO_ROUTELOC1_ETMTD3LOC_LOC3                  0x00000003UL                              /**< Mode LOC3 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD3LOC_LOC0                   (_GPIO_ROUTELOC1_ETMTD3LOC_LOC0 << 26)    /**< Shifted mode LOC0 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD3LOC_DEFAULT                (_GPIO_ROUTELOC1_ETMTD3LOC_DEFAULT << 26) /**< Shifted mode DEFAULT for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD3LOC_LOC1                   (_GPIO_ROUTELOC1_ETMTD3LOC_LOC1 << 26)    /**< Shifted mode LOC1 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD3LOC_LOC2                   (_GPIO_ROUTELOC1_ETMTD3LOC_LOC2 << 26)    /**< Shifted mode LOC2 for GPIO_ROUTELOC1 */
#define GPIO_ROUTELOC1_ETMTD3LOC_LOC3                   (_GPIO_ROUTELOC1_ETMTD3LOC_LOC3 << 26)    /**< Shifted mode LOC3 for GPIO_ROUTELOC1 */

/* Bit fields for GPIO INSENSE */
#define _GPIO_INSENSE_RESETVALUE                        0x00000003UL                       /**< Default value for GPIO_INSENSE */
#define _GPIO_INSENSE_MASK                              0x00000003UL                       /**< Mask for GPIO_INSENSE */
#define GPIO_INSENSE_INT                                (0x1UL << 0)                       /**< Interrupt Sense Enable */
#define _GPIO_INSENSE_INT_SHIFT                         0                                  /**< Shift value for GPIO_INT */
#define _GPIO_INSENSE_INT_MASK                          0x1UL                              /**< Bit mask for GPIO_INT */
#define _GPIO_INSENSE_INT_DEFAULT                       0x00000001UL                       /**< Mode DEFAULT for GPIO_INSENSE */
#define GPIO_INSENSE_INT_DEFAULT                        (_GPIO_INSENSE_INT_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_INSENSE */
#define GPIO_INSENSE_EM4WU                              (0x1UL << 1)                       /**< EM4WU Interrupt Sense Enable */
#define _GPIO_INSENSE_EM4WU_SHIFT                       1                                  /**< Shift value for GPIO_EM4WU */
#define _GPIO_INSENSE_EM4WU_MASK                        0x2UL                              /**< Bit mask for GPIO_EM4WU */
#define _GPIO_INSENSE_EM4WU_DEFAULT                     0x00000001UL                       /**< Mode DEFAULT for GPIO_INSENSE */
#define GPIO_INSENSE_EM4WU_DEFAULT                      (_GPIO_INSENSE_EM4WU_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_INSENSE */

/* Bit fields for GPIO LOCK */
#define _GPIO_LOCK_RESETVALUE                           0x00000000UL                       /**< Default value for GPIO_LOCK */
#define _GPIO_LOCK_MASK                                 0x0000FFFFUL                       /**< Mask for GPIO_LOCK */
#define _GPIO_LOCK_LOCKKEY_SHIFT                        0                                  /**< Shift value for GPIO_LOCKKEY */
#define _GPIO_LOCK_LOCKKEY_MASK                         0xFFFFUL                           /**< Bit mask for GPIO_LOCKKEY */
#define _GPIO_LOCK_LOCKKEY_DEFAULT                      0x00000000UL                       /**< Mode DEFAULT for GPIO_LOCK */
#define _GPIO_LOCK_LOCKKEY_LOCK                         0x00000000UL                       /**< Mode LOCK for GPIO_LOCK */
#define _GPIO_LOCK_LOCKKEY_UNLOCKED                     0x00000000UL                       /**< Mode UNLOCKED for GPIO_LOCK */
#define _GPIO_LOCK_LOCKKEY_LOCKED                       0x00000001UL                       /**< Mode LOCKED for GPIO_LOCK */
#define _GPIO_LOCK_LOCKKEY_UNLOCK                       0x0000A534UL                       /**< Mode UNLOCK for GPIO_LOCK */
#define GPIO_LOCK_LOCKKEY_DEFAULT                       (_GPIO_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_LOCK */
#define GPIO_LOCK_LOCKKEY_LOCK                          (_GPIO_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for GPIO_LOCK */
#define GPIO_LOCK_LOCKKEY_UNLOCKED                      (_GPIO_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for GPIO_LOCK */
#define GPIO_LOCK_LOCKKEY_LOCKED                        (_GPIO_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for GPIO_LOCK */
#define GPIO_LOCK_LOCKKEY_UNLOCK                        (_GPIO_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for GPIO_LOCK */

#if defined(_GPIO_P_CTRL_DRIVESTRENGTH_MASK) && defined(_GPIO_P_CTRL_DRIVESTRENGTHALT_MASK)
/** GPIO drive strength. */
typedef enum {
  /** GPIO weak 1mA and alternate function weak 1mA. */
  gpioDriveStrengthWeakAlternateWeak     = GPIO_P_CTRL_DRIVESTRENGTH_WEAK | GPIO_P_CTRL_DRIVESTRENGTHALT_WEAK,

  /** GPIO weak 1mA and alternate function strong 10mA. */
  gpioDriveStrengthWeakAlternateStrong   = GPIO_P_CTRL_DRIVESTRENGTH_WEAK | GPIO_P_CTRL_DRIVESTRENGTHALT_STRONG,

  /** GPIO strong 10mA and alternate function weak 1mA. */
  gpioDriveStrengthStrongAlternateWeak   = GPIO_P_CTRL_DRIVESTRENGTH_STRONG | GPIO_P_CTRL_DRIVESTRENGTHALT_WEAK,

  /** GPIO strong 10mA and alternate function strong 10mA. */
  gpioDriveStrengthStrongAlternateStrong = GPIO_P_CTRL_DRIVESTRENGTH_STRONG | GPIO_P_CTRL_DRIVESTRENGTHALT_STRONG,
} GPIO_DriveStrength_TypeDef;

/* Deprecated enums. */
#define gpioDriveStrengthStrong   gpioDriveStrengthStrongAlternateStrong
#define gpioDriveStrengthWeak     gpioDriveStrengthWeakAlternateWeak
#endif

/** @} */
/** @} End of group EFR32FG13P_GPIO */
/** @} End of group Parts */

/** Pin mode. For more details on each mode, refer to the
 * reference manual. */
typedef enum {
  /** Input disabled. Pull-up if DOUT is set. */
  gpioModeDisabled                  = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set. */
  gpioModeInput                     = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction. */
  gpioModeInputPull                 = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction. */
  gpioModeInputPullFilter           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output. */
  gpioModePushPull                  = _GPIO_P_MODEL_MODE0_PUSHPULL,
#if defined(_GPIO_P_MODEL_MODE0_PUSHPULLDRIVE)
  /** Push-pull output with drive-strength set by DRIVEMODE. */
  gpioModePushPullDrive             = _GPIO_P_MODEL_MODE0_PUSHPULLDRIVE,
#endif
#if defined(_GPIO_P_MODEL_MODE0_PUSHPULLALT)
  /** Push-pull using alternate control. */
  gpioModePushPullAlternate       = _GPIO_P_MODEL_MODE0_PUSHPULLALT,
#endif
  /** Wired-or output. */
  gpioModeWiredOr                       = _GPIO_P_MODEL_MODE0_WIREDOR,
  /** Wired-or output with pull-down. */
  gpioModeWiredOrPullDown               = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output. */
  gpioModeWiredAnd                      = _GPIO_P_MODEL_MODE0_WIREDAND,
  /** Open-drain output with filter. */
  gpioModeWiredAndFilter                = _GPIO_P_MODEL_MODE0_WIREDANDFILTER,
  /** Open-drain output with pull-up. */
  gpioModeWiredAndPullUp                = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output with filter and pull-up. */
  gpioModeWiredAndPullUpFilter          = _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER,
#if defined(_GPIO_P_MODEL_MODE0_WIREDANDDRIVE)
  /** Open-drain output with drive-strength set by DRIVEMODE. */
  gpioModeWiredAndDrive                 = _GPIO_P_MODEL_MODE0_WIREDANDDRIVE,
  /** Open-drain output with filter and drive-strength set by DRIVEMODE. */
  gpioModeWiredAndDriveFilter           = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEFILTER,
  /** Open-drain output with pull-up and drive-strength set by DRIVEMODE. */
  gpioModeWiredAndDrivePullUp           = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUP,
  /** Open-drain output with filter, pull-up and drive-strength set by DRIVEMODE. */
  gpioModeWiredAndDrivePullUpFilter     = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUPFILTER
#endif
#if defined(_GPIO_P_MODEL_MODE0_WIREDANDALT)
  /** Open-drain output using alternate control. */
  gpioModeWiredAndAlternate             = _GPIO_P_MODEL_MODE0_WIREDANDALT,
  /** Open-drain output using alternate control with filter. */
  gpioModeWiredAndAlternateFilter       = _GPIO_P_MODEL_MODE0_WIREDANDALTFILTER,
  /** Open-drain output using alternate control with pull-up. */
  gpioModeWiredAndAlternatePullUp       = _GPIO_P_MODEL_MODE0_WIREDANDALTPULLUP,
  /** Open-drain output using alternate control with filter and pull-up. */
  gpioModeWiredAndAlternatePullUpFilter = _GPIO_P_MODEL_MODE0_WIREDANDALTPULLUPFILTER,
#endif
} GPIO_Mode_TypeDef;


typedef enum {
  /** Input disabled. Pullup if DOUT is set. */
  GPIOMODE_DISABLED                  = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set */
  GPIOMODE_INPUT                     = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction */
  GPIOMODE_INPUTPULL                 = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction */
  GPIOMODE_INPUTPULLFILTER           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output */
  GPIOMODE_OUTPUT_PUSHPULL           = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Wired-or output */
  GPIOMODE_OUTPUT_WIREDOR              = _GPIO_P_MODEL_MODE0_WIREDOR,
  /** Wired-or output with pull-down */
  GPIOMODE_OUTPUT_WIREDORPD             = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output */
  GPIOMODE_OUTPUT_OPENDRAIN             = _GPIO_P_MODEL_MODE0_WIREDAND,
  /** Open-drain output with filter */
  GPIOMODE_OUTPUT_OPENDRAINFLT          = _GPIO_P_MODEL_MODE0_WIREDANDFILTER,
  /** Open-drain output with pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUP           = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output with filter and pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUPFLT        = _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER,
} GPIO_Mode_t;

enum{
    DISABLED = GPIOMODE_DISABLED,
    OUTPUT = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT = GPIOMODE_INPUT,
    INPUT_PULLUP    = 0x100 | GPIOMODE_INPUTPULL,
    INPUT_PULLDOWN  = GPIOMODE_INPUTPULL,
	INPUT_PULLUP_FILTER = 0x100 | GPIOMODE_INPUTPULLFILTER,
	INPUT_PULLDOWN_FILTER = GPIOMODE_INPUTPULLFILTER,
    OUTPUT_UP = 0x100 | GPIOMODE_OUTPUT_PUSHPULL,
    OUTPUT_DOWN = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT_UP = 0x100 | GPIOMODE_INPUT,
    INPUT_DOWN = GPIOMODE_INPUT
};

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void GPIO_DbgLocationSet(unsigned int location);

/***************************************************************************//**
 * @brief
 *   Enable/disable serial wire clock pin.
 *
 * @note
 *   Disabling SWDClk will disable the debug interface, which may result in
 *   a lockout if done early in startup (before debugger is able to halt core).
 *
 * @param[in] enable
 *   @li false - disable serial wire clock.
 *   @li true - enable serial wire clock (default after reset).
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWDClkEnable(bool enable)
{
#if defined(_GPIO_ROUTE_SWCLKPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTE), _GPIO_ROUTE_SWCLKPEN_SHIFT, enable);
#elif defined(_GPIO_ROUTEPEN_SWCLKTCKPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTEPEN), _GPIO_ROUTEPEN_SWCLKTCKPEN_SHIFT, enable);
#elif defined(_GPIO_DBGROUTEPEN_SWCLKTCKPEN_MASK)
  BUS_RegBitWrite(&(GPIO->DBGROUTEPEN), _GPIO_DBGROUTEPEN_SWCLKTCKPEN_SHIFT, enable);
#else
#warning "ROUTE enable for SWCLK pin is not defined."
#endif
}

/***************************************************************************//**
 * @brief
 *   Enable/disable serial wire data I/O pin.
 *
 * @note
 *   Disabling SWDClk will disable the debug interface, which may result in
 *   a lockout if done early in startup (before debugger is able to halt core).
 *
 * @param[in] enable
 *   @li false - disable serial wire data pin.
 *   @li true - enable serial wire data pin (default after reset).
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWDIOEnable(bool enable)
{
#if defined(_GPIO_ROUTE_SWDIOPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTE), _GPIO_ROUTE_SWDIOPEN_SHIFT, enable);
#elif defined(_GPIO_ROUTEPEN_SWDIOTMSPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTEPEN), _GPIO_ROUTEPEN_SWDIOTMSPEN_SHIFT, enable);
#elif defined(_GPIO_DBGROUTEPEN_SWDIOTMSPEN_MASK)
  BUS_RegBitWrite(&(GPIO->DBGROUTEPEN), _GPIO_DBGROUTEPEN_SWDIOTMSPEN_SHIFT, enable);
#else
#warning "ROUTE enable for SWDIO pin is not defined."
#endif
}

#if defined(_GPIO_ROUTE_SWOPEN_MASK) || defined(_GPIO_ROUTEPEN_SWVPEN_MASK) \
  || defined(_GPIO_TRACEROUTEPEN_SWVPEN_MASK)
/***************************************************************************//**
 * @brief
 *   Enable/Disable serial wire output pin.
 *
 * @note
 *   Enabling this pin is not sufficient to fully enable serial wire output,
 *   which is also dependent on issues outside the GPIO module. Refer to
 *   @ref DBG_SWOEnable().
 *
 * @param[in] enable
 *   @li false - disable serial wire viewer pin (default after reset).
 *   @li true - enable serial wire viewer pin.
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWOEnable(bool enable)
{
#if defined(_GPIO_ROUTE_SWOPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTE), _GPIO_ROUTE_SWOPEN_SHIFT, enable);
#elif defined(_GPIO_ROUTEPEN_SWVPEN_MASK)
  BUS_RegBitWrite(&(GPIO->ROUTEPEN), _GPIO_ROUTEPEN_SWVPEN_SHIFT, enable);
#elif defined(_GPIO_TRACEROUTEPEN_SWVPEN_MASK)
  BUS_RegBitWrite(&(GPIO->TRACEROUTEPEN), _GPIO_TRACEROUTEPEN_SWVPEN_SHIFT, enable);
#else
#warning "ROUTE enable for SWO/SWV pin is not defined."
#endif
}
#endif

#if defined (_GPIO_P_CTRL_DRIVEMODE_MASK)
void GPIO_DriveModeSet(uint8_t port, GPIO_DriveMode_TypeDef mode);
#endif

#if defined(_GPIO_P_CTRL_DRIVESTRENGTH_MASK)
void GPIO_DriveStrengthSet(uint8_t port, GPIO_DriveStrength_TypeDef strength);
#endif

# if defined(_GPIO_EM4WUEN_MASK)
/**************************************************************************//**
 * @brief
 *   Disable GPIO pin wake-up from EM4.
 *
 * @param[in] pinmask
 *   Bit mask containing the bitwise logic OR of which GPIO pin(s) to disable.
 *   Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 *****************************************************************************/
__STATIC_INLINE void GPIO_EM4DisablePinWakeup(uint32_t pinmask)
{
  //EFM_ASSERT((pinmask & ~_GPIO_EM4WUEN_MASK) == 0);

  GPIO->EM4WUEN &= ~pinmask;
}
#endif

# if defined(_GPIO_EM4WUEN_MASK)
void GPIO_EM4EnablePinWakeup(uint32_t pinmask, uint32_t polaritymask);
#endif

#if defined(_GPIO_EM4WUCAUSE_MASK) || defined(_GPIO_IF_EM4WU_MASK)
/**************************************************************************//**
 * @brief
 *   Check which GPIO pin(s) that caused a wake-up from EM4.
 *
 * @return
 *   Bit mask containing the bitwise logic OR of which GPIO pin(s) caused the
 *   wake-up. Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 *****************************************************************************/
__STATIC_INLINE uint32_t GPIO_EM4GetPinWakeupCause(void)
{
#if defined(_GPIO_EM4WUCAUSE_MASK)
  return GPIO->EM4WUCAUSE & _GPIO_EM4WUCAUSE_MASK;
#else
  return GPIO->IF & _GPIO_IF_EM4WU_MASK;
#endif
}
#endif

#if defined(GPIO_CTRL_EM4RET) || defined(_EMU_EM4CTRL_EM4IORETMODE_MASK)
/**************************************************************************//**
 * @brief
 *   Enable GPIO pin retention of output enable, output value, pull enable, and
 *   pull direction in EM4.
 *
 * @note
 *   On series 0 devices EM4 gpio retention can either be turned on or off. On
 *   series 1 devices there are three EM4 GPIO retention modes available. These
 *   modes are "Disabled", "EM4EXIT" and "SWUNLATCH". Use the @ref EMU_EM4Init()
 *   to configure the GPIO retention mode on a series 1 device.
 *
 *   The behavior of this function depends on the configured GPIO retention mode.
 *   If the GPIO retention mode is configured to be "SWUNLATCH" then this
 *   function will not change anything. If the retention mode is anything else
 *   then this function will set the GPIO retention mode to "EM4EXIT" when the
 *   enable argument is true, and "Disabled" when false.
 *
 * @param[in] enable
 *   @li true - enable EM4 pin retention.
 *   @li false - disable EM4 pin retention.
 *****************************************************************************/
__STATIC_INLINE void GPIO_EM4SetPinRetention(bool enable)
{
#if defined(GPIO_CTRL_EM4RET)
  BUS_RegBitWrite(&GPIO->CTRL, _GPIO_CTRL_EM4RET_SHIFT, enable);
#else

  // Leave configuration alone when software unlatch is used.
  uint32_t mode = EMU->EM4CTRL & _EMU_EM4CTRL_EM4IORETMODE_MASK;
  if (mode == EMU_EM4CTRL_EM4IORETMODE_SWUNLATCH) {
    return;
  }

  if (enable) {
    EMU->EM4CTRL = (EMU->EM4CTRL & ~_EMU_EM4CTRL_EM4IORETMODE_MASK)
                   | EMU_EM4CTRL_EM4IORETMODE_EM4EXIT;
  } else {
    EMU->EM4CTRL = (EMU->EM4CTRL & ~_EMU_EM4CTRL_EM4IORETMODE_MASK)
                   | EMU_EM4CTRL_EM4IORETMODE_DISABLE;
  }
#endif
}
#endif

void GPIO_ExtIntConfig(uint8_t port,
                       unsigned int pin,
                       unsigned int intNo,
                       bool risingEdge,
                       bool fallingEdge,
                       bool enable);

/***************************************************************************//**
 * @brief
 *   Enable/disable input sensing.
 *
 * @details
 *   Disabling input sensing if not used, can save some energy consumption.
 *
 * @param[in] val
 *   Bitwise logic OR of one or more of:
 *   @li GPIO_INSENSE_INT - interrupt input sensing.
 *   @li GPIO_INSENSE_PRS - peripheral reflex system input sensing.
 *
 * @param[in] mask
 *   Mask containing bitwise logic OR of bits similar as for @p val used to
 *   indicate which input sense options to disable/enable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_InputSenseSet(uint32_t val, uint32_t mask)
{
#if defined(_GPIO_INSENSE_MASK)
  GPIO->INSENSE = (GPIO->INSENSE & ~mask) | (val & mask);
#else
  (void) val;
  (void) mask;
#endif
}

/***************************************************************************//**
 * @brief
 *   Clear one or more pending GPIO interrupts.
 *
 * @param[in] flags
 *   Bitwise logic OR of GPIO interrupt sources to clear.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntClear(uint32_t flags)
{
#if defined(GPIO_HAS_SET_CLEAR)
  GPIO->IF_CLR = flags;
#else
  GPIO->IFC = flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Disable one or more GPIO interrupts.
 *
 * @param[in] flags
 *   GPIO interrupt sources to disable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntDisable(uint32_t flags)
{
  GPIO->IEN &= ~flags;
}

/***************************************************************************//**
 * @brief
 *   Enable one or more GPIO interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. To ignore a pending interrupt, consider using
 *   GPIO_IntClear() prior to enabling the interrupt.
 *
 * @param[in] flags
 *   GPIO interrupt sources to enable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntEnable(uint32_t flags)
{
  GPIO->IEN |= flags;
}

/***************************************************************************//**
 * @brief
 *   Get pending GPIO interrupts.
 *
 * @return
 *   GPIO interrupt sources pending.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_IntGet(void)
{
  return GPIO->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending GPIO interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled GPIO interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in GPIO_IEN register
 *     and
 *   - the OR combination of valid interrupt flags in GPIO_IF register.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_IntGetEnabled(void)
{
  uint32_t tmp;

  /* Store GPIO->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = GPIO->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return GPIO->IF & tmp;
}

/**************************************************************************//**
 * @brief
 *   Set one or more pending GPIO interrupts from SW.
 *
 * @param[in] flags
 *   GPIO interrupt sources to set to pending.
 *****************************************************************************/
__STATIC_INLINE void GPIO_IntSet(uint32_t flags)
{
#if defined (GPIO_HAS_SET_CLEAR)
  GPIO->IF_SET = flags;
#else
  GPIO->IFS = flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Locks the GPIO configuration.
 ******************************************************************************/
__STATIC_INLINE void GPIO_Lock(void)
{
  GPIO->LOCK = ~GPIO_LOCK_LOCKKEY_UNLOCK;
}

/***************************************************************************//**
 * @brief
 *   Read the pad value for a single pin in a GPIO port.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number to read.
 *
 * @return
 *   The pin value, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE unsigned int GPIO_PinInGet(uint8_t port,
                                           unsigned int pin)
{
  //EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));
  return BUS_RegBitRead(&GPIO->P[port].DIN, pin);
}

#if defined (_GPIO_P_PINLOCKN_MASK)
/***************************************************************************//**
 * @brief
 *   Lock all GPIO configuration settings for a given pin.
 *   The lock can only be cleared by a chip reset.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number to lock.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PinLock(uint8_t port, unsigned int pin)
{
  BUS_RegBitWrite(&GPIO->P[port].PINLOCKN, pin, 0);
}
#endif

GPIO_Mode_TypeDef GPIO_PinModeGet(uint8_t port,
                                  unsigned int pin);

void GPIO_PinModeSet(uint8_t port,
                     unsigned int pin,
                     GPIO_Mode_TypeDef mode,
                     unsigned int out);

/***************************************************************************//**
 * @brief
 *   Set a single pin in GPIO data out port register to 0.
 *
 * @note
 *   In order for the setting to take effect on the output pad, the pin must
 *   have been configured properly. If not, it will take effect whenever the
 *   pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin to set.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PinOutClear(uint8_t port, unsigned int pin)
{
  //EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));
#if defined(_GPIO_P_DOUTCLR_MASK)
  GPIO->P[port].DOUTCLR = 1 << pin;
#elif defined(GPIO_HAS_SET_CLEAR)
  GPIO->P_CLR[port].DOUT = 1 << pin;
#else
  BUS_RegMaskedClear(&GPIO->P[port].DOUT, 1 << pin);
#endif
}

/***************************************************************************//**
 * @brief
 *   Get current setting for a pin in a GPIO port data out register.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin to get setting for.
 *
 * @return
 *   The DOUT setting for the requested pin, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE unsigned int GPIO_PinOutGet(uint8_t port,
                                            unsigned int pin)
{
  //EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));
  return BUS_RegBitRead(&GPIO->P[port].DOUT, pin);
}

/***************************************************************************//**
 * @brief
 *   Set a single pin in GPIO data out register to 1.
 *
 * @note
 *   In order for the setting to take effect on the output pad, the pin must
 *   have been configured properly. If not, it will take effect whenever the
 *   pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin to set.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PinOutSet(uint8_t port, unsigned int pin)
{
 // EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));
#if defined(_GPIO_P_DOUTSET_MASK)
  GPIO->P[port].DOUTSET = 1 << pin;
#elif defined(GPIO_HAS_SET_CLEAR)
  GPIO->P_SET[port].DOUT = 1 << pin;
#else
  BUS_RegMaskedSet(&GPIO->P[port].DOUT, 1 << pin);
#endif
}

/***************************************************************************//**
 * @brief
 *   Toggle a single pin in GPIO port data out register.
 *
 * @note
 *   In order for the setting to take effect on the output pad, the pin must
 *   have been configured properly. If not, it will take effect whenever the
 *   pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin to toggle.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PinOutToggle(uint8_t port, unsigned int pin)
{
  //EFM_ASSERT(GPIO_PORT_PIN_VALID(port, pin));

#if defined (_GPIO_P_DOUTTGL_MASK)
  GPIO->P[port].DOUTTGL = 1 << pin;
#elif defined(GPIO_HAS_SET_CLEAR)
  GPIO->P_TGL[port].DOUT = 1 << pin;
#else
  GPIO->P[port].DOUT ^= 1 << pin;
#endif
}

/***************************************************************************//**
 * @brief
 *   Read the pad values for GPIO port.
 *
 * @param[in] port
 *   The GPIO port to access.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_PortInGet(uint8_t port)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));

  return GPIO->P[port].DIN;
}

/***************************************************************************//**
 * @brief
 *   Set bits in DOUT register for a port to 0.
 *
 * @note
 *   In order for the setting to take effect on the output pad, the pin must
 *   have been configured properly. If not, it will take effect whenever the
 *   pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pins
 *   Bit mask for bits to clear in DOUT register.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PortOutClear(uint8_t port, uint32_t pins)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));
#if defined(_GPIO_P_DOUTCLR_MASK)
  GPIO->P[port].DOUTCLR = pins;
#elif defined(GPIO_HAS_SET_CLEAR)
  GPIO->P_CLR[port].DOUT = pins;
#else
  BUS_RegMaskedClear(&GPIO->P[port].DOUT, pins);
#endif
}

/***************************************************************************//**
 * @brief
 *   Get current setting for a GPIO port data out register.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @return
 *   The data out setting for the requested port.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_PortOutGet(uint8_t port)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));

  return GPIO->P[port].DOUT;
}

/***************************************************************************//**
 * @brief
 *   Set bits GPIO data out register to 1.
 *
 * @note
 *   In order for the setting to take effect on the respective output pads, the
 *   pins must have been configured properly. If not, it will take effect
 *   whenever the pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pins
 *   Bit mask for bits to set to 1 in DOUT register.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PortOutSet(uint8_t port, uint32_t pins)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));
#if defined(_GPIO_P_DOUTSET_MASK)
  GPIO->P[port].DOUTSET = pins;
#elif defined(GPIO_HAS_SET_CLEAR)
  GPIO->P_SET[port].DOUT = pins;
#else
  BUS_RegMaskedSet(&GPIO->P[port].DOUT, pins);
#endif
}

/***************************************************************************//**
 * @brief
 *   Set GPIO port data out register.
 *
 * @note
 *   In order for the setting to take effect on the respective output pads, the
 *   pins must have been configured properly. If not, it will take effect
 *   whenever the pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] val
 *   Value to write to port data out register.
 *
 * @param[in] mask
 *   Mask indicating which bits to modify.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PortOutSetVal(uint8_t port,
                                        uint32_t val,
                                        uint32_t mask)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));

  GPIO->P[port].DOUT = (GPIO->P[port].DOUT & ~mask) | (val & mask);
}

/***************************************************************************//**
 * @brief
 *   Toggle pins in GPIO port data out register.
 *
 * @note
 *   In order for the setting to take effect on the output pad, the pin must
 *   have been configured properly. If not, it will take effect whenever the
 *   pin has been properly configured.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pins
 *   Bit mask with pins to toggle.
 ******************************************************************************/
__STATIC_INLINE void GPIO_PortOutToggle(uint8_t port, uint32_t pins)
{
  //EFM_ASSERT(GPIO_PORT_VALID(port));
#if defined (GPIO_HAS_SET_CLEAR)
  GPIO->P_TGL[port].DOUT = pins;
#else
  GPIO->P[port].DOUTTGL = pins;
#endif
}

#if defined(_GPIO_P_CTRL_SLEWRATE_MASK)
/***************************************************************************//**
 * @brief
 *   Set slewrate for pins on a GPIO port.
 *
 * @param[in] port
 *   The GPIO port to configure.
 *
 * @param[in] slewrate
 *   The slewrate to configure for pins on this GPIO port.
 *
 * @param[in] slewrateAlt
 *   The slewrate to configure for pins using alternate modes on this GPIO port.
 ******************************************************************************/
__STATIC_INLINE void GPIO_SlewrateSet(uint8_t port,
                                      uint32_t slewrate,
                                      uint32_t slewrateAlt)
{
//   EFM_ASSERT(GPIO_PORT_VALID(port));
//   EFM_ASSERT(slewrate <= (_GPIO_P_CTRL_SLEWRATE_MASK
//                           >> _GPIO_P_CTRL_SLEWRATE_SHIFT));
//   EFM_ASSERT(slewrateAlt <= (_GPIO_P_CTRL_SLEWRATEALT_MASK
//                              >> _GPIO_P_CTRL_SLEWRATEALT_SHIFT));

  GPIO->P[port].CTRL = (GPIO->P[port].CTRL
                        & ~(_GPIO_P_CTRL_SLEWRATE_MASK
                            | _GPIO_P_CTRL_SLEWRATEALT_MASK))
                       | (slewrate << _GPIO_P_CTRL_SLEWRATE_SHIFT)
                       | (slewrateAlt << _GPIO_P_CTRL_SLEWRATEALT_SHIFT);
}
#endif

/***************************************************************************//**
 * @brief
 *   Unlocks the GPIO configuration.
 ******************************************************************************/
__STATIC_INLINE void GPIO_Unlock(void)
{
  GPIO->LOCK = GPIO_LOCK_LOCKKEY_UNLOCK;
}

/*******************************************************************************
 ***********************   DEPRECATED PROTOTYPES   *****************************
 ***********************     (will be removed)     *****************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Configure GPIO interrupt.
 *
 * @details
 *   If reconfiguring a GPIO interrupt that is already enabled, it is generally
 *   recommended to disable it first, see @ref GPIO_Disable().
 *
 *   The actual GPIO interrupt handler must be in place before enabling the
 *   interrupt.
 *
 *   Notice that any pending interrupt for the selected pin is cleared by this
 *   function.
 *
 * @deprecated
 *   Deprecated function. New code should use @ref GPIO_ExtIntConfig().
 *
 * @note
 *   A certain pin number can only be associated with one port; i.e., if GPIO
 *   interrupt 1 is assigned to port A/pin 1, then it is not possible to use
 *   pin 1 from any other ports for interrupts. Refer to the reference
 *   manual. On devices which implement GPIO_EXTIPINSEL registers a more
 *   flexible approach is possible, refer to @ref GPIO_ExtIntConfig().
 *
 * @param[in] port
 *   The port to associate with @p pin.
 *
 * @param[in] pin
 *   The pin number on the port ( == GPIO EXTI interrupt number).
 *
 * @param[in] risingEdge
 *   Set to true if interrupts will be enabled on rising edge, otherwise false.
 *
 * @param[in] fallingEdge
 *   Set to true if interrupts will be enabled on falling edge, otherwise false.
 *
 * @param[in] enable
 *   Set to true if interrupt will be enabled after configuration completed,
 *   false to leave disabled. See @ref GPIO_IntDisable() and @ref GPIO_IntEnable().
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntConfig(uint8_t port,
                                    unsigned int pin,
                                    bool risingEdge,
                                    bool fallingEdge,
                                    bool enable)
{
  GPIO_ExtIntConfig(port, pin, pin, risingEdge, fallingEdge, enable);
}

#endif // CORTEXGPIO_H