#if (!defined(ZGECKO))
#define ZGECKO
#include "CrtxGcc.h"
#include "ZUNO_Definitions.h"

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/** @brief Round n up to closest interval of i. */
#define SL_CEILING(n, i)   ((((n) + (i) - 1U) / (i)) * (i))

/** @brief Round n down to closest interval of i. */
#define SL_FLOOR(n, i) ((n / i) * i))

/** @brief Stringify X */
#define STRINGIZE(X) #X

#if !defined(__GNUC__)
/* Not GCC compilers */

/** @brief Macro for getting minimum value. */
#define SL_MIN(a, b) ((a) < (b) ? (a) : (b))

/** @brief Macro for getting maximum value. */
#define SL_MAX(a, b) ((a) > (b) ? (a) : (b))

/** @brief Macros for handling packed structs. */
#define SL_PACK_START(X) _Pragma(STRINGIZE(pack(X)))
#define SL_PACK_END()    _Pragma("pack()")
#define SL_ATTRIBUTE_PACKED

#if defined(__CC_ARM)
/** @brief MDK-ARM compiler: Macros for handling aligned structs. */
#define SL_ALIGN(X) __align(X)

/** MDK-ARM compiler: Macro for handling weak symbols. */
#define SL_WEAK __attribute__ ((weak))

/** MDK-ARM compiler: Macro for handling non-returning functions. */
#define SL_NORETURN __attribute__ ((noreturn))

/** MDK-ARM compiler: Macro for handling section placement */
#define SL_ATTRIBUTE_SECTION(X) __attribute__ ((section(X)))
#endif

#if defined(__ICCARM__)

#if (__VER__ >= 8000000)
/** @brief Obsoleted macro from version 8.00 and on . */
#define _STD_BEGIN
/** @brief Obsoleted macro from version 8.00 and on . */
#define _STD_END
#endif

/** @brief IAR Embedded Workbench: Macros for handling aligned structs. */
#define SL_ALIGN(X) _Pragma(STRINGIZE(data_alignment = X))

/** @brief IAR Embedded Workbench: Macros for handling weak symbols. */
#define SL_WEAK __weak

/** @brief IAR Embedded Workbench: Macro for handling non-returning functions. */
#define SL_NORETURN __noreturn

/* *INDENT-OFF* */
/** IAR Embedded Workbench: Macro for handling section placement */
#define SL_ATTRIBUTE_SECTION(X) @ X
#endif
/* *INDENT-ON* */

#define SL_ATTRIBUTE_ALIGN(X)

/** @brief Macro for notifying the compiler of an intended
 *  switch case fallthrough. */
#define SL_FALLTHROUGH

#else // !defined(__GNUC__)
/* GCC compilers */

/** @brief A macro for getting the minimum value. No sideeffects, a and b are evaluated one time only. */
#define SL_MIN(a, b) __extension__({ __typeof__(a)_a = (a); __typeof__(b)_b = (b); _a < _b ? _a : _b; })

/** @brief A macro for getting the maximum value. No sideeffects, a and b are evaluated one time only. */
#define SL_MAX(a, b) __extension__({ __typeof__(a)_a = (a); __typeof__(b)_b = (b); _a > _b ? _a : _b; })

/** @brief A GCC style macro for handling packed structures. */
#define SL_ATTRIBUTE_PACKED __attribute__ ((packed))

/** @brief A macro for handling packed structures.
 *  @n Use this macro before the structure definition.
 *  @n X denotes the maximum alignment of structure members. X is not supported with
 *  GCC. GCC always uses 1 byte maximum alignment.
 */
#define SL_PACK_START(x)

/** @brief A macro for handling packed structures.
 *  @n Use this macro after the structure definition.
 *  @n With GCC, add SL_ATTRIBUTE_PACKED after the closing curly braces of the structure
 *  definition.
 */
#define SL_PACK_END()

/** @brief GCC style macro for aligning a variable. */
#define SL_ATTRIBUTE_ALIGN(X) __attribute__ ((aligned(X)))

/** @brief A macro for aligning a variable.
 *  @n Use this macro before the variable definition.
 *  @n X denotes the storage alignment value in bytes.
 *  @n To be GCC-compatible, use SL_ATTRIBUTE_ALIGN(X) before the semicolon on normal
 *  variables. Use SL_ATTRIBUTE_ALIGN(X) before the opening curly brace on structure variables.
 */
#define SL_ALIGN(X)

/** @brief A macro for defining a weak symbol. */
#define SL_WEAK __attribute__ ((weak))

/** @brief A macro for handling non-returning functions. */
#define SL_NORETURN __attribute__ ((noreturn))

/** A macro for placing a variable in a section.
 *  @n Use this macro after the variable definition, before the equal sign or a semicolon.
 *  @n X denotes the section to place the variable in.
 */
#define SL_ATTRIBUTE_SECTION(X) __attribute__ ((section(X)))

/** @brief A macro for notifying the compiler of an intended
 *  switch case fallthrough. */
#if __GNUC__ >= 7
  #define SL_FALLTHROUGH __attribute__ ((fallthrough));
#else
  #define SL_FALLTHROUGH
#endif

#endif // !defined(__GNUC__)

/** Interrupt Number Definition */
typedef enum IRQn{
/******  Cortex-M4 Processor Exceptions Numbers ********************************************/
  NonMaskableInt_IRQn   = -14,              /*!< 2  Cortex-M4 Non Maskable Interrupt      */
  HardFault_IRQn        = -13,              /*!< 3  Cortex-M4 Hard Fault Interrupt        */
  MemoryManagement_IRQn = -12,              /*!< 4  Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn         = -11,              /*!< 5  Cortex-M4 Bus Fault Interrupt         */
  UsageFault_IRQn       = -10,              /*!< 6  Cortex-M4 Usage Fault Interrupt       */
  SVCall_IRQn           = -5,               /*!< 11 Cortex-M4 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,               /*!< 12 Cortex-M4 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,               /*!< 14 Cortex-M4 Pend SV Interrupt           */
  SysTick_IRQn          = -1,               /*!< 15 Cortex-M4 System Tick Interrupt       */

/******  EFR32ZG13P Peripheral Interrupt Numbers ********************************************/

  EMU_IRQn              = 0,  /*!< 16+0 EFR32 EMU Interrupt */
  FRC_PRI_IRQn          = 1,  /*!< 16+1 EFR32 FRC_PRI Interrupt */
  WDOG0_IRQn            = 2,  /*!< 16+2 EFR32 WDOG0 Interrupt */
  WDOG1_IRQn            = 3,  /*!< 16+3 EFR32 WDOG1 Interrupt */
  FRC_IRQn              = 4,  /*!< 16+4 EFR32 FRC Interrupt */
  MODEM_IRQn            = 5,  /*!< 16+5 EFR32 MODEM Interrupt */
  RAC_SEQ_IRQn          = 6,  /*!< 16+6 EFR32 RAC_SEQ Interrupt */
  RAC_RSM_IRQn          = 7,  /*!< 16+7 EFR32 RAC_RSM Interrupt */
  BUFC_IRQn             = 8,  /*!< 16+8 EFR32 BUFC Interrupt */
  LDMA_IRQn             = 9,  /*!< 16+9 EFR32 LDMA Interrupt */
  GPIO_EVEN_IRQn        = 10, /*!< 16+10 EFR32 GPIO_EVEN Interrupt */
  TIMER0_IRQn           = 11, /*!< 16+11 EFR32 TIMER0 Interrupt */
  USART0_RX_IRQn        = 12, /*!< 16+12 EFR32 USART0_RX Interrupt */
  USART0_TX_IRQn        = 13, /*!< 16+13 EFR32 USART0_TX Interrupt */
  ACMP0_IRQn            = 14, /*!< 16+14 EFR32 ACMP0 Interrupt */
  ADC0_IRQn             = 15, /*!< 16+15 EFR32 ADC0 Interrupt */
  IDAC0_IRQn            = 16, /*!< 16+16 EFR32 IDAC0 Interrupt */
  I2C0_IRQn             = 17, /*!< 16+17 EFR32 I2C0 Interrupt */
  GPIO_ODD_IRQn         = 18, /*!< 16+18 EFR32 GPIO_ODD Interrupt */
  TIMER1_IRQn           = 19, /*!< 16+19 EFR32 TIMER1 Interrupt */
  USART1_RX_IRQn        = 20, /*!< 16+20 EFR32 USART1_RX Interrupt */
  USART1_TX_IRQn        = 21, /*!< 16+21 EFR32 USART1_TX Interrupt */
  LEUART0_IRQn          = 22, /*!< 16+22 EFR32 LEUART0 Interrupt */
  PCNT0_IRQn            = 23, /*!< 16+23 EFR32 PCNT0 Interrupt */
  CMU_IRQn              = 24, /*!< 16+24 EFR32 CMU Interrupt */
  MSC_IRQn              = 25, /*!< 16+25 EFR32 MSC Interrupt */
  CRYPTO0_IRQn          = 26, /*!< 16+26 EFR32 CRYPTO0 Interrupt */
  LETIMER0_IRQn         = 27, /*!< 16+27 EFR32 LETIMER0 Interrupt */
  AGC_IRQn              = 28, /*!< 16+28 EFR32 AGC Interrupt */
  PROTIMER_IRQn         = 29, /*!< 16+29 EFR32 PROTIMER Interrupt */
  PRORTC_IRQn           = 30, /*!< 16+30 EFR32 PRORTC Interrupt */
  RTCC_IRQn             = 31, /*!< 16+31 EFR32 RTCC Interrupt */
  SYNTH_IRQn            = 32, /*!< 16+32 EFR32 SYNTH Interrupt */
  CRYOTIMER_IRQn        = 33, /*!< 16+33 EFR32 CRYOTIMER Interrupt */
  RFSENSE_IRQn          = 34, /*!< 16+34 EFR32 RFSENSE Interrupt */
  FPUEH_IRQn            = 35, /*!< 16+35 EFR32 FPUEH Interrupt */
  SMU_IRQn              = 36, /*!< 16+36 EFR32 SMU Interrupt */
  WTIMER0_IRQn          = 37, /*!< 16+37 EFR32 WTIMER0 Interrupt */
  USART2_RX_IRQn        = 38, /*!< 16+38 EFR32 USART2_RX Interrupt */
  USART2_TX_IRQn        = 39, /*!< 16+39 EFR32 USART2_TX Interrupt */
  I2C1_IRQn             = 40, /*!< 16+40 EFR32 I2C1 Interrupt */
  VDAC0_IRQn            = 41, /*!< 16+41 EFR32 VDAC0 Interrupt */
  CSEN_IRQn             = 42, /*!< 16+42 EFR32 CSEN Interrupt */
  LESENSE_IRQn          = 43, /*!< 16+43 EFR32 LESENSE Interrupt */
  CRYPTO1_IRQn          = 44, /*!< 16+44 EFR32 CRYPTO1 Interrupt */
  TRNG0_IRQn            = 45, /*!< 16+45 EFR32 TRNG0 Interrupt */
} IRQn_Type;

#define __CORTEX_M                (4U)                                   /*!< Cortex-M Core */

#define CRYPTO_IRQn               CRYPTO0_IRQn /*!< Alias for CRYPTO0_IRQn */

/***************************************************************************//**
 * @defgroup ZGM130S037HGN1_Core Core
 * @{
 * @brief Processor and Core Peripheral Section
 ******************************************************************************/
#define __MPU_PRESENT             1U /**< Presence of MPU  */
#define __FPU_PRESENT             1U /**< Presence of FPU  */
#define __VTOR_PRESENT            1U /**< Presence of VTOR register in SCB */
#define __NVIC_PRIO_BITS          3U /**< NVIC interrupt priority bits */
#define __Vendor_SysTickConfig    0U /**< Is 1 if different SysTick counter is used */


#define __CORTEX_M                (4U)/*!< Cortex-M Core */

/** Part family */
#define _EFR32_ZEN_FAMILY                       1                                /**< ZEN Gecko RF SoC Family  */
#define _EFR_DEVICE                                                              /**< Silicon Labs EFR-type RF SoC */
#define _SILICON_LABS_MODULE                    1                                /**< Silicon Labs multi-chip module */
#define _SILICON_LABS_32B_SERIES_1                                               /**< Silicon Labs series number */
#define _SILICON_LABS_32B_SERIES                1                                /**< Silicon Labs series number */
#define _SILICON_LABS_32B_SERIES_1_CONFIG_3                                      /**< Series 1, Configuration 3 */
#define _SILICON_LABS_32B_SERIES_1_CONFIG       3                                /**< Series 1, Configuration 3 */
#define _SILICON_LABS_GECKO_INTERNAL_SDID       89                               /**< Silicon Labs internal use only, may change any time */
#define _SILICON_LABS_GECKO_INTERNAL_SDID_89                                     /**< Silicon Labs internal use only, may change any time */
#define _SILICON_LABS_EFR32_RADIO_SUBGHZ        1                                /**< Radio supports Sub-GHz */
#define _SILICON_LABS_EFR32_RADIO_2G4HZ         2                                /**< Radio supports 2.4 GHz */
#define _SILICON_LABS_EFR32_RADIO_DUALBAND      3                                /**< Radio supports dual band */
#define _SILICON_LABS_EFR32_RADIO_TYPE          _SILICON_LABS_EFR32_RADIO_SUBGHZ /**< Radio type */
#define _SILICON_LABS_32B_PLATFORM_2                                             /**< @deprecated Silicon Labs platform name */
#define _SILICON_LABS_32B_PLATFORM              2                                /**< @deprecated Silicon Labs platform name */
#define _SILICON_LABS_32B_PLATFORM_2_GEN_3                                       /**< @deprecated Platform 2, generation 3 */
#define _SILICON_LABS_32B_PLATFORM_2_GEN        3                                /**< @deprecated Platform 2, generation 3 */

/***************************************************************************//**
 * @defgroup ZGM130S037HGN1_UNLOCK Unlock Codes
 * @{
 ******************************************************************************/
#define MSC_UNLOCK_CODE      0x1B71 /**< MSC unlock code */
#define EMU_UNLOCK_CODE      0xADE8 /**< EMU unlock code */
#define RMU_UNLOCK_CODE      0xE084 /**< RMU unlock code */
#define CMU_UNLOCK_CODE      0x580E /**< CMU unlock code */
#define GPIO_UNLOCK_CODE     0xA534 /**< GPIO unlock code */
#define TIMER_UNLOCK_CODE    0xCE80 /**< TIMER unlock code */
#define RTCC_UNLOCK_CODE     0xAEE8 /**< RTCC unlock code */


/* Memory Base addresses and limits */
#define RAM0_CODE_MEM_BASE         ((uint32_t) 0x10000000UL) /**< RAM0_CODE base address  */
#define RAM0_CODE_MEM_SIZE         ((uint32_t) 0x8000UL)     /**< RAM0_CODE available address space  */
#define RAM0_CODE_MEM_END          ((uint32_t) 0x10007FFFUL) /**< RAM0_CODE end address  */
#define RAM0_CODE_MEM_BITS         ((uint32_t) 0x0000000FUL) /**< RAM0_CODE used bits  */
#define RAM2_MEM_BASE              ((uint32_t) 0x20010000UL) /**< RAM2 base address  */
#define RAM2_MEM_SIZE              ((uint32_t) 0x800UL)      /**< RAM2 available address space  */
#define RAM2_MEM_END               ((uint32_t) 0x200107FFUL) /**< RAM2 end address  */
#define RAM2_MEM_BITS              ((uint32_t) 0x0000000BUL) /**< RAM2 used bits  */
#define RAM1_MEM_BASE              ((uint32_t) 0x20008000UL) /**< RAM1 base address  */
#define RAM1_MEM_SIZE              ((uint32_t) 0x8000UL)     /**< RAM1 available address space  */
#define RAM1_MEM_END               ((uint32_t) 0x2000FFFFUL) /**< RAM1 end address  */
#define RAM1_MEM_BITS              ((uint32_t) 0x0000000FUL) /**< RAM1 used bits  */
#define CRYPTO1_BITCLR_MEM_BASE    ((uint32_t) 0x440F0400UL) /**< CRYPTO1_BITCLR base address  */
#define CRYPTO1_BITCLR_MEM_SIZE    ((uint32_t) 0x400UL)      /**< CRYPTO1_BITCLR available address space  */
#define CRYPTO1_BITCLR_MEM_END     ((uint32_t) 0x440F07FFUL) /**< CRYPTO1_BITCLR end address  */
#define CRYPTO1_BITCLR_MEM_BITS    ((uint32_t) 0x0000000AUL) /**< CRYPTO1_BITCLR used bits  */
#define PER_MEM_BASE               ((uint32_t) 0x40000000UL) /**< PER base address  */
#define PER_MEM_SIZE               ((uint32_t) 0xF0000UL)    /**< PER available address space  */
#define PER_MEM_END                ((uint32_t) 0x400EFFFFUL) /**< PER end address  */
#define PER_MEM_BITS               ((uint32_t) 0x00000014UL) /**< PER used bits  */
#define RAM1_CODE_MEM_BASE         ((uint32_t) 0x10008000UL) /**< RAM1_CODE base address  */
#define RAM1_CODE_MEM_SIZE         ((uint32_t) 0x8000UL)     /**< RAM1_CODE available address space  */
#define RAM1_CODE_MEM_END          ((uint32_t) 0x1000FFFFUL) /**< RAM1_CODE end address  */
#define RAM1_CODE_MEM_BITS         ((uint32_t) 0x0000000FUL) /**< RAM1_CODE used bits  */
#define CRYPTO1_MEM_BASE           ((uint32_t) 0x400F0400UL) /**< CRYPTO1 base address  */
#define CRYPTO1_MEM_SIZE           ((uint32_t) 0x400UL)      /**< CRYPTO1 available address space  */
#define CRYPTO1_MEM_END            ((uint32_t) 0x400F07FFUL) /**< CRYPTO1 end address  */
#define CRYPTO1_MEM_BITS           ((uint32_t) 0x0000000AUL) /**< CRYPTO1 used bits  */
#define FLASH_MEM_BASE             ((uint32_t) 0x00000000UL) /**< FLASH base address  */
#define FLASH_MEM_SIZE             ((uint32_t) 0x10000000UL) /**< FLASH available address space  */
#define FLASH_MEM_END              ((uint32_t) 0x0FFFFFFFUL) /**< FLASH end address  */
#define FLASH_MEM_BITS             ((uint32_t) 0x0000001CUL) /**< FLASH used bits  */
#define CRYPTO0_MEM_BASE           ((uint32_t) 0x400F0000UL) /**< CRYPTO0 base address  */
#define CRYPTO0_MEM_SIZE           ((uint32_t) 0x400UL)      /**< CRYPTO0 available address space  */
#define CRYPTO0_MEM_END            ((uint32_t) 0x400F03FFUL) /**< CRYPTO0 end address  */
#define CRYPTO0_MEM_BITS           ((uint32_t) 0x0000000AUL) /**< CRYPTO0 used bits  */
#define CRYPTO_MEM_BASE            CRYPTO0_MEM_BASE          /**< Alias for CRYPTO0_MEM_BASE */
#define CRYPTO_MEM_SIZE            CRYPTO0_MEM_SIZE          /**< Alias for CRYPTO0_MEM_SIZE */
#define CRYPTO_MEM_END             CRYPTO0_MEM_END           /**< Alias for CRYPTO0_MEM_END  */
#define CRYPTO_MEM_BITS            CRYPTO0_MEM_BITS          /**< Alias for CRYPTO0_MEM_BITS */
#define PER_BITCLR_MEM_BASE        ((uint32_t) 0x44000000UL) /**< PER_BITCLR base address  */
#define PER_BITCLR_MEM_SIZE        ((uint32_t) 0xF0000UL)    /**< PER_BITCLR available address space  */
#define PER_BITCLR_MEM_END         ((uint32_t) 0x440EFFFFUL) /**< PER_BITCLR end address  */
#define PER_BITCLR_MEM_BITS        ((uint32_t) 0x00000014UL) /**< PER_BITCLR used bits  */
#define CRYPTO0_BITSET_MEM_BASE    ((uint32_t) 0x460F0000UL) /**< CRYPTO0_BITSET base address  */
#define CRYPTO0_BITSET_MEM_SIZE    ((uint32_t) 0x400UL)      /**< CRYPTO0_BITSET available address space  */
#define CRYPTO0_BITSET_MEM_END     ((uint32_t) 0x460F03FFUL) /**< CRYPTO0_BITSET end address  */
#define CRYPTO0_BITSET_MEM_BITS    ((uint32_t) 0x0000000AUL) /**< CRYPTO0_BITSET used bits  */
#define CRYPTO_BITSET_MEM_BASE     CRYPTO0_BITSET_MEM_BASE   /**< Alias for CRYPTO0_BITSET_MEM_BASE */
#define CRYPTO_BITSET_MEM_SIZE     CRYPTO0_BITSET_MEM_SIZE   /**< Alias for CRYPTO0_BITSET_MEM_SIZE */
#define CRYPTO_BITSET_MEM_END      CRYPTO0_BITSET_MEM_END    /**< Alias for CRYPTO0_BITSET_MEM_END  */
#define CRYPTO_BITSET_MEM_BITS     CRYPTO0_BITSET_MEM_BITS   /**< Alias for CRYPTO0_BITSET_MEM_BITS */
#define CRYPTO0_BITCLR_MEM_BASE    ((uint32_t) 0x440F0000UL) /**< CRYPTO0_BITCLR base address  */
#define CRYPTO0_BITCLR_MEM_SIZE    ((uint32_t) 0x400UL)      /**< CRYPTO0_BITCLR available address space  */
#define CRYPTO0_BITCLR_MEM_END     ((uint32_t) 0x440F03FFUL) /**< CRYPTO0_BITCLR end address  */
#define CRYPTO0_BITCLR_MEM_BITS    ((uint32_t) 0x0000000AUL) /**< CRYPTO0_BITCLR used bits  */
#define CRYPTO_BITCLR_MEM_BASE     CRYPTO0_BITCLR_MEM_BASE   /**< Alias for CRYPTO0_BITCLR_MEM_BASE */
#define CRYPTO_BITCLR_MEM_SIZE     CRYPTO0_BITCLR_MEM_SIZE   /**< Alias for CRYPTO0_BITCLR_MEM_SIZE */
#define CRYPTO_BITCLR_MEM_END      CRYPTO0_BITCLR_MEM_END    /**< Alias for CRYPTO0_BITCLR_MEM_END  */
#define CRYPTO_BITCLR_MEM_BITS     CRYPTO0_BITCLR_MEM_BITS   /**< Alias for CRYPTO0_BITCLR_MEM_BITS */
#define PER_BITSET_MEM_BASE        ((uint32_t) 0x46000000UL) /**< PER_BITSET base address  */
#define PER_BITSET_MEM_SIZE        ((uint32_t) 0xF0000UL)    /**< PER_BITSET available address space  */
#define PER_BITSET_MEM_END         ((uint32_t) 0x460EFFFFUL) /**< PER_BITSET end address  */
#define PER_BITSET_MEM_BITS        ((uint32_t) 0x00000014UL) /**< PER_BITSET used bits  */
#define CRYPTO1_BITSET_MEM_BASE    ((uint32_t) 0x460F0400UL) /**< CRYPTO1_BITSET base address  */
#define CRYPTO1_BITSET_MEM_SIZE    ((uint32_t) 0x400UL)      /**< CRYPTO1_BITSET available address space  */
#define CRYPTO1_BITSET_MEM_END     ((uint32_t) 0x460F07FFUL) /**< CRYPTO1_BITSET end address  */
#define CRYPTO1_BITSET_MEM_BITS    ((uint32_t) 0x0000000AUL) /**< CRYPTO1_BITSET used bits  */
#define RAM2_CODE_MEM_BASE         ((uint32_t) 0x10010000UL) /**< RAM2_CODE base address  */
#define RAM2_CODE_MEM_SIZE         ((uint32_t) 0x800UL)      /**< RAM2_CODE available address space  */
#define RAM2_CODE_MEM_END          ((uint32_t) 0x100107FFUL) /**< RAM2_CODE end address  */
#define RAM2_CODE_MEM_BITS         ((uint32_t) 0x0000000BUL) /**< RAM2_CODE used bits  */
#define RAM_MEM_BASE               ((uint32_t) 0x20000000UL) /**< RAM base address  */
#define RAM_MEM_SIZE               ((uint32_t) 0x8000UL)     /**< RAM available address space  */
#define RAM_MEM_END                ((uint32_t) 0x20007FFFUL) /**< RAM end address  */
#define RAM_MEM_BITS               ((uint32_t) 0x0000000FUL) /**< RAM used bits  */

/** Bit banding area */
#define BITBAND_PER_BASE           ((uint32_t) 0x42000000UL) /**< Peripheral Address Space bit-band area */
#define BITBAND_RAM_BASE           ((uint32_t) 0x22000000UL) /**< SRAM Address Space bit-band area */

/** Flash and SRAM limits for EFR32FG13P231F512GM32 */
#define FLASH_BASE                 (0x00000000UL) /**< Flash Base Address */
#define FLASH_SIZE                 (0x00080000UL) /**< Available Flash Memory */
#define FLASH_PAGE_SIZE            2048U          /**< Flash Memory page size */
#define SRAM_BASE                  (0x20000000UL) /**< SRAM Base Address */
#define SRAM_SIZE                  (0x00010000UL) /**< Available SRAM Memory */
#define __CM4_REV                  0x001          /**< Cortex-M4 Core revision r0p1 */
#define PRS_CHAN_COUNT             12             /**< Number of PRS channels */
#define DMA_CHAN_COUNT             8              /**< Number of DMA channels */
#define EXT_IRQ_COUNT              47             /**< Number of External (NVIC) interrupts */

/** AF channels connect the different on-chip peripherals with the af-mux */
#define AFCHAN_MAX                 118U
/** AF channel maximum location number */
#define AFCHANLOC_MAX              32U
/** Analog AF channels */
#define AFACHAN_MAX                118U

/* Part number capabilities */

#define CRYPTO_PRESENT          /**< CRYPTO is available in this part */
#define CRYPTO_COUNT          2 /**< 2 CRYPTOs available  */
#define TIMER_PRESENT           /**< TIMER is available in this part */
#define TIMER_COUNT           2 /**< 2 TIMERs available  */
#define WTIMER_PRESENT          /**< WTIMER is available in this part */
#define WTIMER_COUNT          1 /**< 1 WTIMERs available  */
#define USART_PRESENT           /**< USART is available in this part */
#define USART_COUNT           3 /**< 3 USARTs available  */
#define LEUART_PRESENT          /**< LEUART is available in this part */
#define LEUART_COUNT          1 /**< 1 LEUARTs available  */
#define LETIMER_PRESENT         /**< LETIMER is available in this part */
#define LETIMER_COUNT         1 /**< 1 LETIMERs available  */
#define PCNT_PRESENT            /**< PCNT is available in this part */
#define PCNT_COUNT            1 /**< 1 PCNTs available  */
#define I2C_PRESENT             /**< I2C is available in this part */
#define I2C_COUNT             2 /**< 2 I2Cs available  */
#define ADC_PRESENT             /**< ADC is available in this part */
#define ADC_COUNT             1 /**< 1 ADCs available  */
#define ACMP_PRESENT            /**< ACMP is available in this part */
#define ACMP_COUNT            2 /**< 2 ACMPs available  */
#define VDAC_PRESENT            /**< VDAC is available in this part */
#define VDAC_COUNT            1 /**< 1 VDACs available  */
#define WDOG_PRESENT            /**< WDOG is available in this part */
#define WDOG_COUNT            2 /**< 2 WDOGs available  */
#define IDAC_PRESENT            /**< IDAC is available in this part */
#define IDAC_COUNT            1 /**< 1 IDACs available  */
#define TRNG_PRESENT            /**< TRNG is available in this part */
#define TRNG_COUNT            1 /**< 1 TRNGs available  */
#define MSC_PRESENT             /**< MSC is available in this part */
#define MSC_COUNT             1 /**< 1 MSC available */
#define EMU_PRESENT             /**< EMU is available in this part */
#define EMU_COUNT             1 /**< 1 EMU available */
#define RMU_PRESENT             /**< RMU is available in this part */
#define RMU_COUNT             1 /**< 1 RMU available */
#define CMU_PRESENT             /**< CMU is available in this part */
#define CMU_COUNT             1 /**< 1 CMU available */
#define GPIO_PRESENT            /**< GPIO is available in this part */
#define GPIO_COUNT            1 /**< 1 GPIO available */
#define PRS_PRESENT             /**< PRS is available in this part */
#define PRS_COUNT             1 /**< 1 PRS available */
#define LDMA_PRESENT            /**< LDMA is available in this part */
#define LDMA_COUNT            1 /**< 1 LDMA available */
#define FPUEH_PRESENT           /**< FPUEH is available in this part */
#define FPUEH_COUNT           1 /**< 1 FPUEH available */
#define GPCRC_PRESENT           /**< GPCRC is available in this part */
#define GPCRC_COUNT           1 /**< 1 GPCRC available */
#define CRYOTIMER_PRESENT       /**< CRYOTIMER is available in this part */
#define CRYOTIMER_COUNT       1 /**< 1 CRYOTIMER available */
#define CSEN_PRESENT            /**< CSEN is available in this part */
#define CSEN_COUNT            1 /**< 1 CSEN available */
#define LESENSE_PRESENT         /**< LESENSE is available in this part */
#define LESENSE_COUNT         1 /**< 1 LESENSE available */
#define RTCC_PRESENT            /**< RTCC is available in this part */
#define RTCC_COUNT            1 /**< 1 RTCC available */
#define ETM_PRESENT             /**< ETM is available in this part */
#define ETM_COUNT             1 /**< 1 ETM available */
#define BOOTLOADER_PRESENT      /**< BOOTLOADER is available in this part */
#define BOOTLOADER_COUNT      1 /**< 1 BOOTLOADER available */
#define SMU_PRESENT             /**< SMU is available in this part */
#define SMU_COUNT             1 /**< 1 SMU available */
#define DCDC_PRESENT            /**< DCDC is available in this part */
#define DCDC_COUNT            1 /**< 1 DCDC available */
/**************************************************************************
 * @defgroup EFR32FG13P231F512GM32_Peripheral_Base Peripheral Memory Map
 * @{
 *****************************************************************************/

#define MSC_BASE          (0x400E0000UL) /**< MSC base address  */
#define EMU_BASE          (0x400E3000UL) /**< EMU base address  */
#define RMU_BASE          (0x400E5000UL) /**< RMU base address  */
#define CMU_BASE          (0x400E4000UL) /**< CMU base address  */
#define CRYPTO0_BASE      (0x400F0000UL) /**< CRYPTO0 base address  */
#define CRYPTO_BASE       CRYPTO0_BASE   /**< Alias for CRYPTO0 base address */
#define CRYPTO1_BASE      (0x400F0400UL) /**< CRYPTO1 base address  */
#define GPIO_BASE         (0x4000A000UL) /**< GPIO base address  */
#define PRS_BASE          (0x400E6000UL) /**< PRS base address  */
#define LDMA_BASE         (0x400E2000UL) /**< LDMA base address  */
#define FPUEH_BASE        (0x400E1000UL) /**< FPUEH base address  */
#define GPCRC_BASE        (0x4001C000UL) /**< GPCRC base address  */
#define TIMER0_BASE       (0x40018000UL) /**< TIMER0 base address  */
#define TIMER1_BASE       (0x40018400UL) /**< TIMER1 base address  */
#define WTIMER0_BASE      (0x4001A000UL) /**< WTIMER0 base address  */
#define USART0_BASE       (0x40010000UL) /**< USART0 base address  */
#define USART1_BASE       (0x40010400UL) /**< USART1 base address  */
#define USART2_BASE       (0x40010800UL) /**< USART2 base address  */
#define LEUART0_BASE      (0x4004A000UL) /**< LEUART0 base address  */
#define LETIMER0_BASE     (0x40046000UL) /**< LETIMER0 base address  */
#define CRYOTIMER_BASE    (0x4001E000UL) /**< CRYOTIMER base address  */
#define PCNT0_BASE        (0x4004E000UL) /**< PCNT0 base address  */
#define I2C0_BASE         (0x4000C000UL) /**< I2C0 base address  */
#define I2C1_BASE         (0x4000C400UL) /**< I2C1 base address  */
#define ADC0_BASE         (0x40002000UL) /**< ADC0 base address  */
#define ACMP0_BASE        (0x40000000UL) /**< ACMP0 base address  */
#define ACMP1_BASE        (0x40000400UL) /**< ACMP1 base address  */
#define VDAC0_BASE        (0x40008000UL) /**< VDAC0 base address  */
#define CSEN_BASE         (0x4001F000UL) /**< CSEN base address  */
#define LESENSE_BASE      (0x40055000UL) /**< LESENSE base address  */
#define RTCC_BASE         (0x40042000UL) /**< RTCC base address  */
#define WDOG0_BASE        (0x40052000UL) /**< WDOG0 base address  */
#define WDOG1_BASE        (0x40052400UL) /**< WDOG1 base address  */
#define ETM_BASE          (0xE0041000UL) /**< ETM base address  */
#define IDAC0_BASE        (0x40006000UL) /**< IDAC0 base address  */
#define SMU_BASE          (0x40022000UL) /**< SMU base address  */
#define TRNG0_BASE        (0x4001D000UL) /**< TRNG0 base address  */
#define DEVINFO_BASE      (0x0FE081B0UL) /**< DEVINFO base address */
#define ROMTABLE_BASE     (0xE00FFFD0UL) /**< ROMTABLE base address */
#define LOCKBITS_BASE     (0x0FE04000UL) /**< Lock-bits page base address */
#define USERDATA_BASE     (0x0FE00000UL) /**< User data page base address */

#define DWT_BASE          (0xE0001000UL)                            /*!< DWT Base Address */

/** @} End of group EFR32FG13P231F512GM32_Peripheral_Base */

/** RMU Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;     /**< Control Register  */
  __IM uint32_t  RSTCAUSE; /**< Reset Cause Register  */
  __IOM uint32_t CMD;      /**< Command Register  */
  __IOM uint32_t RST;      /**< Reset Control Register  */
  __IOM uint32_t LOCK;     /**< Configuration Lock Register  */
} RMU_TypeDef;             /** @} */

/***************************************************************************//**
 * @addtogroup ZGM13_RMU
 * @{
 * @defgroup ZGM13_RMU_BitFields  RMU Bit Fields
 * @{
 ******************************************************************************/
/* Bit fields for RMU CTRL */
#define _RMU_CTRL_RESETVALUE               0x00004204UL                          /**< Default value for RMU_CTRL */
#define _RMU_CTRL_MASK                     0x03007777UL                          /**< Mask for RMU_CTRL */
#define _RMU_CTRL_WDOGRMODE_SHIFT          0                                     /**< Shift value for RMU_WDOGRMODE */
#define _RMU_CTRL_WDOGRMODE_MASK           0x7UL                                 /**< Bit mask for RMU_WDOGRMODE */
#define _RMU_CTRL_WDOGRMODE_DISABLED       0x00000000UL                          /**< Mode DISABLED for RMU_CTRL */
#define _RMU_CTRL_WDOGRMODE_LIMITED        0x00000001UL                          /**< Mode LIMITED for RMU_CTRL */
#define _RMU_CTRL_WDOGRMODE_EXTENDED       0x00000002UL                          /**< Mode EXTENDED for RMU_CTRL */
#define _RMU_CTRL_WDOGRMODE_DEFAULT        0x00000004UL                          /**< Mode DEFAULT for RMU_CTRL */
#define _RMU_CTRL_WDOGRMODE_FULL           0x00000004UL                          /**< Mode FULL for RMU_CTRL */
#define RMU_CTRL_WDOGRMODE_DISABLED        (_RMU_CTRL_WDOGRMODE_DISABLED << 0)   /**< Shifted mode DISABLED for RMU_CTRL */
#define RMU_CTRL_WDOGRMODE_LIMITED         (_RMU_CTRL_WDOGRMODE_LIMITED << 0)    /**< Shifted mode LIMITED for RMU_CTRL */
#define RMU_CTRL_WDOGRMODE_EXTENDED        (_RMU_CTRL_WDOGRMODE_EXTENDED << 0)   /**< Shifted mode EXTENDED for RMU_CTRL */
#define RMU_CTRL_WDOGRMODE_DEFAULT         (_RMU_CTRL_WDOGRMODE_DEFAULT << 0)    /**< Shifted mode DEFAULT for RMU_CTRL */
#define RMU_CTRL_WDOGRMODE_FULL            (_RMU_CTRL_WDOGRMODE_FULL << 0)       /**< Shifted mode FULL for RMU_CTRL */
#define _RMU_CTRL_LOCKUPRMODE_SHIFT        4                                     /**< Shift value for RMU_LOCKUPRMODE */
#define _RMU_CTRL_LOCKUPRMODE_MASK         0x70UL                                /**< Bit mask for RMU_LOCKUPRMODE */
#define _RMU_CTRL_LOCKUPRMODE_DEFAULT      0x00000000UL                          /**< Mode DEFAULT for RMU_CTRL */
#define _RMU_CTRL_LOCKUPRMODE_DISABLED     0x00000000UL                          /**< Mode DISABLED for RMU_CTRL */
#define _RMU_CTRL_LOCKUPRMODE_LIMITED      0x00000001UL                          /**< Mode LIMITED for RMU_CTRL */
#define _RMU_CTRL_LOCKUPRMODE_EXTENDED     0x00000002UL                          /**< Mode EXTENDED for RMU_CTRL */
#define _RMU_CTRL_LOCKUPRMODE_FULL         0x00000004UL                          /**< Mode FULL for RMU_CTRL */
#define RMU_CTRL_LOCKUPRMODE_DEFAULT       (_RMU_CTRL_LOCKUPRMODE_DEFAULT << 4)  /**< Shifted mode DEFAULT for RMU_CTRL */
#define RMU_CTRL_LOCKUPRMODE_DISABLED      (_RMU_CTRL_LOCKUPRMODE_DISABLED << 4) /**< Shifted mode DISABLED for RMU_CTRL */
#define RMU_CTRL_LOCKUPRMODE_LIMITED       (_RMU_CTRL_LOCKUPRMODE_LIMITED << 4)  /**< Shifted mode LIMITED for RMU_CTRL */
#define RMU_CTRL_LOCKUPRMODE_EXTENDED      (_RMU_CTRL_LOCKUPRMODE_EXTENDED << 4) /**< Shifted mode EXTENDED for RMU_CTRL */
#define RMU_CTRL_LOCKUPRMODE_FULL          (_RMU_CTRL_LOCKUPRMODE_FULL << 4)     /**< Shifted mode FULL for RMU_CTRL */
#define _RMU_CTRL_SYSRMODE_SHIFT           8                                     /**< Shift value for RMU_SYSRMODE */
#define _RMU_CTRL_SYSRMODE_MASK            0x700UL                               /**< Bit mask for RMU_SYSRMODE */
#define _RMU_CTRL_SYSRMODE_DISABLED        0x00000000UL                          /**< Mode DISABLED for RMU_CTRL */
#define _RMU_CTRL_SYSRMODE_LIMITED         0x00000001UL                          /**< Mode LIMITED for RMU_CTRL */
#define _RMU_CTRL_SYSRMODE_DEFAULT         0x00000002UL                          /**< Mode DEFAULT for RMU_CTRL */
#define _RMU_CTRL_SYSRMODE_EXTENDED        0x00000002UL                          /**< Mode EXTENDED for RMU_CTRL */
#define _RMU_CTRL_SYSRMODE_FULL            0x00000004UL                          /**< Mode FULL for RMU_CTRL */
#define RMU_CTRL_SYSRMODE_DISABLED         (_RMU_CTRL_SYSRMODE_DISABLED << 8)    /**< Shifted mode DISABLED for RMU_CTRL */
#define RMU_CTRL_SYSRMODE_LIMITED          (_RMU_CTRL_SYSRMODE_LIMITED << 8)     /**< Shifted mode LIMITED for RMU_CTRL */
#define RMU_CTRL_SYSRMODE_DEFAULT          (_RMU_CTRL_SYSRMODE_DEFAULT << 8)     /**< Shifted mode DEFAULT for RMU_CTRL */
#define RMU_CTRL_SYSRMODE_EXTENDED         (_RMU_CTRL_SYSRMODE_EXTENDED << 8)    /**< Shifted mode EXTENDED for RMU_CTRL */
#define RMU_CTRL_SYSRMODE_FULL             (_RMU_CTRL_SYSRMODE_FULL << 8)        /**< Shifted mode FULL for RMU_CTRL */
#define _RMU_CTRL_PINRMODE_SHIFT           12                                    /**< Shift value for RMU_PINRMODE */
#define _RMU_CTRL_PINRMODE_MASK            0x7000UL                              /**< Bit mask for RMU_PINRMODE */
#define _RMU_CTRL_PINRMODE_DISABLED        0x00000000UL                          /**< Mode DISABLED for RMU_CTRL */
#define _RMU_CTRL_PINRMODE_LIMITED         0x00000001UL                          /**< Mode LIMITED for RMU_CTRL */
#define _RMU_CTRL_PINRMODE_EXTENDED        0x00000002UL                          /**< Mode EXTENDED for RMU_CTRL */
#define _RMU_CTRL_PINRMODE_DEFAULT         0x00000004UL                          /**< Mode DEFAULT for RMU_CTRL */
#define _RMU_CTRL_PINRMODE_FULL            0x00000004UL                          /**< Mode FULL for RMU_CTRL */
#define RMU_CTRL_PINRMODE_DISABLED         (_RMU_CTRL_PINRMODE_DISABLED << 12)   /**< Shifted mode DISABLED for RMU_CTRL */
#define RMU_CTRL_PINRMODE_LIMITED          (_RMU_CTRL_PINRMODE_LIMITED << 12)    /**< Shifted mode LIMITED for RMU_CTRL */
#define RMU_CTRL_PINRMODE_EXTENDED         (_RMU_CTRL_PINRMODE_EXTENDED << 12)   /**< Shifted mode EXTENDED for RMU_CTRL */
#define RMU_CTRL_PINRMODE_DEFAULT          (_RMU_CTRL_PINRMODE_DEFAULT << 12)    /**< Shifted mode DEFAULT for RMU_CTRL */
#define RMU_CTRL_PINRMODE_FULL             (_RMU_CTRL_PINRMODE_FULL << 12)       /**< Shifted mode FULL for RMU_CTRL */
#define _RMU_CTRL_RESETSTATE_SHIFT         24                                    /**< Shift value for RMU_RESETSTATE */
#define _RMU_CTRL_RESETSTATE_MASK          0x3000000UL                           /**< Bit mask for RMU_RESETSTATE */
#define _RMU_CTRL_RESETSTATE_DEFAULT       0x00000000UL                          /**< Mode DEFAULT for RMU_CTRL */
#define RMU_CTRL_RESETSTATE_DEFAULT        (_RMU_CTRL_RESETSTATE_DEFAULT << 24)  /**< Shifted mode DEFAULT for RMU_CTRL */

/* Bit fields for RMU RSTCAUSE */
#define _RMU_RSTCAUSE_RESETVALUE           0x00000000UL                            /**< Default value for RMU_RSTCAUSE */
#define _RMU_RSTCAUSE_MASK                 0x00010F1DUL                            /**< Mask for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_PORST                 (0x1UL << 0)                            /**< Power on Reset */
#define _RMU_RSTCAUSE_PORST_SHIFT          0                                       /**< Shift value for RMU_PORST */
#define _RMU_RSTCAUSE_PORST_MASK           0x1UL                                   /**< Bit mask for RMU_PORST */
#define _RMU_RSTCAUSE_PORST_DEFAULT        0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_PORST_DEFAULT         (_RMU_RSTCAUSE_PORST_DEFAULT << 0)      /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_AVDDBOD               (0x1UL << 2)                            /**< Brown Out Detector AVDD Reset */
#define _RMU_RSTCAUSE_AVDDBOD_SHIFT        2                                       /**< Shift value for RMU_AVDDBOD */
#define _RMU_RSTCAUSE_AVDDBOD_MASK         0x4UL                                   /**< Bit mask for RMU_AVDDBOD */
#define _RMU_RSTCAUSE_AVDDBOD_DEFAULT      0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_AVDDBOD_DEFAULT       (_RMU_RSTCAUSE_AVDDBOD_DEFAULT << 2)    /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_DVDDBOD               (0x1UL << 3)                            /**< Brown Out Detector DVDD Reset */
#define _RMU_RSTCAUSE_DVDDBOD_SHIFT        3                                       /**< Shift value for RMU_DVDDBOD */
#define _RMU_RSTCAUSE_DVDDBOD_MASK         0x8UL                                   /**< Bit mask for RMU_DVDDBOD */
#define _RMU_RSTCAUSE_DVDDBOD_DEFAULT      0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_DVDDBOD_DEFAULT       (_RMU_RSTCAUSE_DVDDBOD_DEFAULT << 3)    /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_DECBOD                (0x1UL << 4)                            /**< Brown Out Detector Decouple Domain Reset */
#define _RMU_RSTCAUSE_DECBOD_SHIFT         4                                       /**< Shift value for RMU_DECBOD */
#define _RMU_RSTCAUSE_DECBOD_MASK          0x10UL                                  /**< Bit mask for RMU_DECBOD */
#define _RMU_RSTCAUSE_DECBOD_DEFAULT       0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_DECBOD_DEFAULT        (_RMU_RSTCAUSE_DECBOD_DEFAULT << 4)     /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_EXTRST                (0x1UL << 8)                            /**< External Pin Reset */
#define _RMU_RSTCAUSE_EXTRST_SHIFT         8                                       /**< Shift value for RMU_EXTRST */
#define _RMU_RSTCAUSE_EXTRST_MASK          0x100UL                                 /**< Bit mask for RMU_EXTRST */
#define _RMU_RSTCAUSE_EXTRST_DEFAULT       0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_EXTRST_DEFAULT        (_RMU_RSTCAUSE_EXTRST_DEFAULT << 8)     /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_LOCKUPRST             (0x1UL << 9)                            /**< LOCKUP Reset */
#define _RMU_RSTCAUSE_LOCKUPRST_SHIFT      9                                       /**< Shift value for RMU_LOCKUPRST */
#define _RMU_RSTCAUSE_LOCKUPRST_MASK       0x200UL                                 /**< Bit mask for RMU_LOCKUPRST */
#define _RMU_RSTCAUSE_LOCKUPRST_DEFAULT    0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_LOCKUPRST_DEFAULT     (_RMU_RSTCAUSE_LOCKUPRST_DEFAULT << 9)  /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_SYSREQRST             (0x1UL << 10)                           /**< System Request Reset */
#define _RMU_RSTCAUSE_SYSREQRST_SHIFT      10                                      /**< Shift value for RMU_SYSREQRST */
#define _RMU_RSTCAUSE_SYSREQRST_MASK       0x400UL                                 /**< Bit mask for RMU_SYSREQRST */
#define _RMU_RSTCAUSE_SYSREQRST_DEFAULT    0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_SYSREQRST_DEFAULT     (_RMU_RSTCAUSE_SYSREQRST_DEFAULT << 10) /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_WDOGRST               (0x1UL << 11)                           /**< Watchdog Reset */
#define _RMU_RSTCAUSE_WDOGRST_SHIFT        11                                      /**< Shift value for RMU_WDOGRST */
#define _RMU_RSTCAUSE_WDOGRST_MASK         0x800UL                                 /**< Bit mask for RMU_WDOGRST */
#define _RMU_RSTCAUSE_WDOGRST_DEFAULT      0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_WDOGRST_DEFAULT       (_RMU_RSTCAUSE_WDOGRST_DEFAULT << 11)   /**< Shifted mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_EM4RST                (0x1UL << 16)                           /**< EM4 Reset */
#define _RMU_RSTCAUSE_EM4RST_SHIFT         16                                      /**< Shift value for RMU_EM4RST */
#define _RMU_RSTCAUSE_EM4RST_MASK          0x10000UL                               /**< Bit mask for RMU_EM4RST */
#define _RMU_RSTCAUSE_EM4RST_DEFAULT       0x00000000UL                            /**< Mode DEFAULT for RMU_RSTCAUSE */
#define RMU_RSTCAUSE_EM4RST_DEFAULT        (_RMU_RSTCAUSE_EM4RST_DEFAULT << 16)    /**< Shifted mode DEFAULT for RMU_RSTCAUSE */

/* Bit fields for RMU CMD */
#define _RMU_CMD_RESETVALUE                0x00000000UL                  /**< Default value for RMU_CMD */
#define _RMU_CMD_MASK                      0x00000001UL                  /**< Mask for RMU_CMD */
#define RMU_CMD_RCCLR                      (0x1UL << 0)                  /**< Reset Cause Clear */
#define _RMU_CMD_RCCLR_SHIFT               0                             /**< Shift value for RMU_RCCLR */
#define _RMU_CMD_RCCLR_MASK                0x1UL                         /**< Bit mask for RMU_RCCLR */
#define _RMU_CMD_RCCLR_DEFAULT             0x00000000UL                  /**< Mode DEFAULT for RMU_CMD */
#define RMU_CMD_RCCLR_DEFAULT              (_RMU_CMD_RCCLR_DEFAULT << 0) /**< Shifted mode DEFAULT for RMU_CMD */

/* Bit fields for RMU RST */
#define _RMU_RST_RESETVALUE                0x00000000UL /**< Default value for RMU_RST */
#define _RMU_RST_MASK                      0x00000000UL /**< Mask for RMU_RST */

/* Bit fields for RMU LOCK */
#define _RMU_LOCK_RESETVALUE               0x00000000UL                      /**< Default value for RMU_LOCK */
#define _RMU_LOCK_MASK                     0x0000FFFFUL                      /**< Mask for RMU_LOCK */
#define _RMU_LOCK_LOCKKEY_SHIFT            0                                 /**< Shift value for RMU_LOCKKEY */
#define _RMU_LOCK_LOCKKEY_MASK             0xFFFFUL                          /**< Bit mask for RMU_LOCKKEY */
#define _RMU_LOCK_LOCKKEY_DEFAULT          0x00000000UL                      /**< Mode DEFAULT for RMU_LOCK */
#define _RMU_LOCK_LOCKKEY_LOCK             0x00000000UL                      /**< Mode LOCK for RMU_LOCK */
#define _RMU_LOCK_LOCKKEY_UNLOCKED         0x00000000UL                      /**< Mode UNLOCKED for RMU_LOCK */
#define _RMU_LOCK_LOCKKEY_LOCKED           0x00000001UL                      /**< Mode LOCKED for RMU_LOCK */
#define _RMU_LOCK_LOCKKEY_UNLOCK           0x0000E084UL                      /**< Mode UNLOCK for RMU_LOCK */
#define RMU_LOCK_LOCKKEY_DEFAULT           (_RMU_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for RMU_LOCK */
#define RMU_LOCK_LOCKKEY_LOCK              (_RMU_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for RMU_LOCK */
#define RMU_LOCK_LOCKKEY_UNLOCKED          (_RMU_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for RMU_LOCK */
#define RMU_LOCK_LOCKKEY_LOCKED            (_RMU_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for RMU_LOCK */
#define RMU_LOCK_LOCKKEY_UNLOCK            (_RMU_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for RMU_LOCK */


/**************************************************************************//**
 * @defgroup EFR32FG13P231F512GM32_Peripheral_Declaration Peripheral Declarations
 * @{
 *****************************************************************************/
#define MSC          ((MSC_TypeDef *) MSC_BASE)             /**< MSC base pointer */
#define EMU          ((EMU_TypeDef *) EMU_BASE)             /**< EMU base pointer */
#define RMU          ((RMU_TypeDef *) RMU_BASE)             /**< RMU base pointer */
#define CMU          ((CMU_TypeDef *) CMU_BASE)             /**< CMU base pointer */
#define CRYPTO0      ((CRYPTO_TypeDef *) CRYPTO0_BASE)      /**< CRYPTO0 base pointer */
#define CRYPTO       CRYPTO0                                /**< Alias for CRYPTO0 base pointer */
#define CRYPTO1      ((CRYPTO_TypeDef *) CRYPTO1_BASE)      /**< CRYPTO1 base pointer */
#define GPIO         ((GPIO_TypeDef *) GPIO_BASE)           /**< GPIO base pointer */
#define PRS          ((PRS_TypeDef *) PRS_BASE)             /**< PRS base pointer */
#define LDMA         ((LDMA_TypeDef *) LDMA_BASE)           /**< LDMA base pointer */
#define FPUEH        ((FPUEH_TypeDef *) FPUEH_BASE)         /**< FPUEH base pointer */
#define GPCRC        ((GPCRC_TypeDef *) GPCRC_BASE)         /**< GPCRC base pointer */
#define TIMER0       ((TIMER_TypeDef *) TIMER0_BASE)        /**< TIMER0 base pointer */
#define TIMER1       ((TIMER_TypeDef *) TIMER1_BASE)        /**< TIMER1 base pointer */
#define WTIMER0      ((TIMER_TypeDef *) WTIMER0_BASE)       /**< WTIMER0 base pointer */
#define USART0       ((USART_TypeDef *) USART0_BASE)        /**< USART0 base pointer */
#define USART1       ((USART_TypeDef *) USART1_BASE)        /**< USART1 base pointer */
#define USART2       ((USART_TypeDef *) USART2_BASE)        /**< USART2 base pointer */
#define LEUART0      ((LEUART_TypeDef *) LEUART0_BASE)      /**< LEUART0 base pointer */
#define LETIMER0     ((LETIMER_TypeDef *) LETIMER0_BASE)    /**< LETIMER0 base pointer */
#define CRYOTIMER    ((CRYOTIMER_TypeDef *) CRYOTIMER_BASE) /**< CRYOTIMER base pointer */
#define PCNT0        ((PCNT_TypeDef *) PCNT0_BASE)          /**< PCNT0 base pointer */
#define I2C0         ((I2C_TypeDef *) I2C0_BASE)            /**< I2C0 base pointer */
#define I2C1         ((I2C_TypeDef *) I2C1_BASE)            /**< I2C1 base pointer */
#define ADC0         ((ADC_TypeDef *) ADC0_BASE)            /**< ADC0 base pointer */
#define ACMP0        ((ACMP_TypeDef *) ACMP0_BASE)          /**< ACMP0 base pointer */
#define ACMP1        ((ACMP_TypeDef *) ACMP1_BASE)          /**< ACMP1 base pointer */
#define VDAC0        ((VDAC_TypeDef *) VDAC0_BASE)          /**< VDAC0 base pointer */
#define CSEN         ((CSEN_TypeDef *) CSEN_BASE)           /**< CSEN base pointer */
#define LESENSE      ((LESENSE_TypeDef *) LESENSE_BASE)     /**< LESENSE base pointer */
#define RTCC         ((RTCC_TypeDef *) RTCC_BASE)           /**< RTCC base pointer */
#define WDOG0        ((WDOG_TypeDef *) WDOG0_BASE)          /**< WDOG0 base pointer */
#define WDOG1        ((WDOG_TypeDef *) WDOG1_BASE)          /**< WDOG1 base pointer */
#define ETM          ((ETM_TypeDef *) ETM_BASE)             /**< ETM base pointer */
#define IDAC0        ((IDAC_TypeDef *) IDAC0_BASE)          /**< IDAC0 base pointer */
#define SMU          ((SMU_TypeDef *) SMU_BASE)             /**< SMU base pointer */
#define TRNG0        ((TRNG_TypeDef *) TRNG0_BASE)          /**< TRNG0 base pointer */
#define DEVINFO      ((DEVINFO_TypeDef *) DEVINFO_BASE)     /**< DEVINFO base pointer */
#define ROMTABLE     ((ROMTABLE_TypeDef *) ROMTABLE_BASE)   /**< ROMTABLE base pointer */


/** @} End of group EFR32FG13P231F512GM32_Peripheral_Declaration */

/**************************************************************************//**
 * @defgroup EFR32FG13P231F512GM32_Peripheral_Offsets Peripheral Offsets
 * @{
 *****************************************************************************/

#define CRYPTO_OFFSET     0x400 /**< Offset in bytes between CRYPTO instances */
#define TIMER_OFFSET      0x400 /**< Offset in bytes between TIMER instances */
#define WTIMER_OFFSET     0x400 /**< Offset in bytes between WTIMER instances */
#define USART_OFFSET      0x400 /**< Offset in bytes between USART instances */
#define LEUART_OFFSET     0x400 /**< Offset in bytes between LEUART instances */
#define LETIMER_OFFSET    0x400 /**< Offset in bytes between LETIMER instances */
#define PCNT_OFFSET       0x400 /**< Offset in bytes between PCNT instances */
#define I2C_OFFSET        0x400 /**< Offset in bytes between I2C instances */
#define ADC_OFFSET        0x400 /**< Offset in bytes between ADC instances */
#define ACMP_OFFSET       0x400 /**< Offset in bytes between ACMP instances */
#define VDAC_OFFSET       0x400 /**< Offset in bytes between VDAC instances */
#define WDOG_OFFSET       0x400 /**< Offset in bytes between WDOG instances */
#define IDAC_OFFSET       0x400 /**< Offset in bytes between IDAC instances */
#define TRNG_OFFSET       0x400 /**< Offset in bytes between TRNG instances */


/** DEVINFO Register Declaration */
typedef struct {
  __IM uint32_t CAL;              /**< CRC of DI-page and calibration temperature  */
  uint32_t      RESERVED0[7];     /**< Reserved for future use **/
  __IM uint32_t EXTINFO;          /**< External Component description  */
  uint32_t      RESERVED1[1];     /**< Reserved for future use **/
  __IM uint32_t EUI48L;           /**< EUI48 OUI and Unique identifier  */
  __IM uint32_t EUI48H;           /**< OUI  */
  __IM uint32_t CUSTOMINFO;       /**< Custom information  */
  __IM uint32_t MEMINFO;          /**< Flash page size and misc. chip information  */
  uint32_t      RESERVED2[2];     /**< Reserved for future use **/
  __IM uint32_t UNIQUEL;          /**< Low 32 bits of device unique number  */
  __IM uint32_t UNIQUEH;          /**< High 32 bits of device unique number  */
  __IM uint32_t MSIZE;            /**< Flash and SRAM Memory size in kB  */
  __IM uint32_t PART;             /**< Part description  */
  __IM uint32_t DEVINFOREV;       /**< Device information page revision  */
  __IM uint32_t EMUTEMP;          /**< EMU Temperature Calibration Information  */
  uint32_t      RESERVED3[2];     /**< Reserved for future use **/
  __IM uint32_t ADC0CAL0;         /**< ADC0 calibration register 0  */
  __IM uint32_t ADC0CAL1;         /**< ADC0 calibration register 1  */
  __IM uint32_t ADC0CAL2;         /**< ADC0 calibration register 2  */
  __IM uint32_t ADC0CAL3;         /**< ADC0 calibration register 3  */
  uint32_t      RESERVED4[4];     /**< Reserved for future use **/
  __IM uint32_t HFRCOCAL0;        /**< HFRCO Calibration Register (4 MHz)  */
  uint32_t      RESERVED5[2];     /**< Reserved for future use **/
  __IM uint32_t HFRCOCAL3;        /**< HFRCO Calibration Register (7 MHz)  */
  uint32_t      RESERVED6[2];     /**< Reserved for future use **/
  __IM uint32_t HFRCOCAL6;        /**< HFRCO Calibration Register (13 MHz)  */
  __IM uint32_t HFRCOCAL7;        /**< HFRCO Calibration Register (16 MHz)  */
  __IM uint32_t HFRCOCAL8;        /**< HFRCO Calibration Register (19 MHz)  */
  uint32_t      RESERVED7[1];     /**< Reserved for future use **/
  __IM uint32_t HFRCOCAL10;       /**< HFRCO Calibration Register (26 MHz)  */
  __IM uint32_t HFRCOCAL11;       /**< HFRCO Calibration Register (32 MHz)  */
  __IM uint32_t HFRCOCAL12;       /**< HFRCO Calibration Register (38 MHz)  */
  uint32_t      RESERVED8[11];    /**< Reserved for future use **/
  __IM uint32_t AUXHFRCOCAL0;     /**< AUXHFRCO Calibration Register (4 MHz)  */
  uint32_t      RESERVED9[2];     /**< Reserved for future use **/
  __IM uint32_t AUXHFRCOCAL3;     /**< AUXHFRCO Calibration Register (7 MHz)  */
  uint32_t      RESERVED10[2];    /**< Reserved for future use **/
  __IM uint32_t AUXHFRCOCAL6;     /**< AUXHFRCO Calibration Register (13 MHz)  */
  __IM uint32_t AUXHFRCOCAL7;     /**< AUXHFRCO Calibration Register (16 MHz)  */
  __IM uint32_t AUXHFRCOCAL8;     /**< AUXHFRCO Calibration Register (19 MHz)  */
  uint32_t      RESERVED11[1];    /**< Reserved for future use **/
  __IM uint32_t AUXHFRCOCAL10;    /**< AUXHFRCO Calibration Register (26 MHz)  */
  __IM uint32_t AUXHFRCOCAL11;    /**< AUXHFRCO Calibration Register (32 MHz)  */
  __IM uint32_t AUXHFRCOCAL12;    /**< AUXHFRCO Calibration Register (38 MHz)  */
  uint32_t      RESERVED12[11];   /**< Reserved for future use **/
  __IM uint32_t VMONCAL0;         /**< VMON Calibration Register 0  */
  __IM uint32_t VMONCAL1;         /**< VMON Calibration Register 1  */
  __IM uint32_t VMONCAL2;         /**< VMON Calibration Register 2  */
  uint32_t      RESERVED13[3];    /**< Reserved for future use **/
  __IM uint32_t IDAC0CAL0;        /**< IDAC0 Calibration Register 0  */
  __IM uint32_t IDAC0CAL1;        /**< IDAC0 Calibration Register 1  */
  uint32_t      RESERVED14[2];    /**< Reserved for future use **/
  __IM uint32_t DCDCLNVCTRL0;     /**< DCDC Low-noise VREF Trim Register 0  */
  __IM uint32_t DCDCLPVCTRL0;     /**< DCDC Low-power VREF Trim Register 0  */
  __IM uint32_t DCDCLPVCTRL1;     /**< DCDC Low-power VREF Trim Register 1  */
  __IM uint32_t DCDCLPVCTRL2;     /**< DCDC Low-power VREF Trim Register 2  */
  __IM uint32_t DCDCLPVCTRL3;     /**< DCDC Low-power VREF Trim Register 3  */
  __IM uint32_t DCDCLPCMPHYSSEL0; /**< DCDC LPCMPHYSSEL Trim Register 0  */
  __IM uint32_t DCDCLPCMPHYSSEL1; /**< DCDC LPCMPHYSSEL Trim Register 1  */
  __IM uint32_t VDAC0MAINCAL;     /**< VDAC0 Cals for Main Path  */
  __IM uint32_t VDAC0ALTCAL;      /**< VDAC0 Cals for Alternate Path  */
  __IM uint32_t VDAC0CH1CAL;      /**< VDAC0 CH1 Error Cal  */
  __IM uint32_t OPA0CAL0;         /**< OPA0 Calibration Register for DRIVESTRENGTH 0, INCBW=1  */
  __IM uint32_t OPA0CAL1;         /**< OPA0 Calibration Register for DRIVESTRENGTH 1, INCBW=1  */
  __IM uint32_t OPA0CAL2;         /**< OPA0 Calibration Register for DRIVESTRENGTH 2, INCBW=1  */
  __IM uint32_t OPA0CAL3;         /**< OPA0 Calibration Register for DRIVESTRENGTH 3, INCBW=1  */
  __IM uint32_t OPA1CAL0;         /**< OPA1 Calibration Register for DRIVESTRENGTH 0, INCBW=1  */
  __IM uint32_t OPA1CAL1;         /**< OPA1 Calibration Register for DRIVESTRENGTH 1, INCBW=1  */
  __IM uint32_t OPA1CAL2;         /**< OPA1 Calibration Register for DRIVESTRENGTH 2, INCBW=1  */
  __IM uint32_t OPA1CAL3;         /**< OPA1 Calibration Register for DRIVESTRENGTH 3, INCBW=1  */
  __IM uint32_t OPA2CAL0;         /**< OPA2 Calibration Register for DRIVESTRENGTH 0, INCBW=1  */
  __IM uint32_t OPA2CAL1;         /**< OPA2 Calibration Register for DRIVESTRENGTH 1, INCBW=1  */
  __IM uint32_t OPA2CAL2;         /**< OPA2 Calibration Register for DRIVESTRENGTH 2, INCBW=1  */
  __IM uint32_t OPA2CAL3;         /**< OPA2 Calibration Register for DRIVESTRENGTH 3, INCBW=1  */
  __IM uint32_t CSENGAINCAL;      /**< Cap Sense Gain Adjustment  */
  uint32_t      RESERVED15[3];    /**< Reserved for future use **/
  __IM uint32_t OPA0CAL4;         /**< OPA0 Calibration Register for DRIVESTRENGTH 0, INCBW=0  */
  __IM uint32_t OPA0CAL5;         /**< OPA0 Calibration Register for DRIVESTRENGTH 1, INCBW=0  */
  __IM uint32_t OPA0CAL6;         /**< OPA0 Calibration Register for DRIVESTRENGTH 2, INCBW=0  */
  __IM uint32_t OPA0CAL7;         /**< OPA0 Calibration Register for DRIVESTRENGTH 3, INCBW=0  */
  __IM uint32_t OPA1CAL4;         /**< OPA1 Calibration Register for DRIVESTRENGTH 0, INCBW=0  */
  __IM uint32_t OPA1CAL5;         /**< OPA1 Calibration Register for DRIVESTRENGTH 1, INCBW=0  */
  __IM uint32_t OPA1CAL6;         /**< OPA1 Calibration Register for DRIVESTRENGTH 2, INCBW=0  */
  __IM uint32_t OPA1CAL7;         /**< OPA1 Calibration Register for DRIVESTRENGTH 3, INCBW=0  */
  __IM uint32_t OPA2CAL4;         /**< OPA2 Calibration Register for DRIVESTRENGTH 0, INCBW=0  */
  __IM uint32_t OPA2CAL5;         /**< OPA2 Calibration Register for DRIVESTRENGTH 1, INCBW=0  */
  __IM uint32_t OPA2CAL6;         /**< OPA2 Calibration Register for DRIVESTRENGTH 2, INCBW=0  */
  __IM uint32_t OPA2CAL7;         /**< OPA2 Calibration Register for DRIVESTRENGTH 3, INCBW=0  */
} DEVINFO_TypeDef;                /** @} */

/**************************************************************************//**
 * @addtogroup EFR32FG13P_DEVINFO
 * @{
 * @defgroup EFR32FG13P_DEVINFO_BitFields DEVINFO Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for DEVINFO CAL */
#define _DEVINFO_CAL_MASK                                        0x00FFFFFFUL /**< Mask for DEVINFO_CAL */
#define _DEVINFO_CAL_CRC_SHIFT                                   0            /**< Shift value for CRC */
#define _DEVINFO_CAL_CRC_MASK                                    0xFFFFUL     /**< Bit mask for CRC */
#define _DEVINFO_CAL_TEMP_SHIFT                                  16           /**< Shift value for TEMP */
#define _DEVINFO_CAL_TEMP_MASK                                   0xFF0000UL   /**< Bit mask for TEMP */

/* Bit fields for DEVINFO EXTINFO */
#define _DEVINFO_EXTINFO_MASK                                    0x00FFFFFFUL                            /**< Mask for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_TYPE_SHIFT                              0                                       /**< Shift value for TYPE */
#define _DEVINFO_EXTINFO_TYPE_MASK                               0xFFUL                                  /**< Bit mask for TYPE */
#define _DEVINFO_EXTINFO_TYPE_IS25LQ040B                         0x00000001UL                            /**< Mode IS25LQ040B for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_TYPE_AT25S041                           0x00000002UL                            /**< Mode AT25S041 for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_TYPE_NONE                               0x000000FFUL                            /**< Mode NONE for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_TYPE_IS25LQ040B                          (_DEVINFO_EXTINFO_TYPE_IS25LQ040B << 0) /**< Shifted mode IS25LQ040B for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_TYPE_AT25S041                            (_DEVINFO_EXTINFO_TYPE_AT25S041 << 0)   /**< Shifted mode AT25S041 for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_TYPE_NONE                                (_DEVINFO_EXTINFO_TYPE_NONE << 0)       /**< Shifted mode NONE for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_CONNECTION_SHIFT                        8                                       /**< Shift value for CONNECTION */
#define _DEVINFO_EXTINFO_CONNECTION_MASK                         0xFF00UL                                /**< Bit mask for CONNECTION */
#define _DEVINFO_EXTINFO_CONNECTION_SPI                          0x00000001UL                            /**< Mode SPI for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_CONNECTION_NONE                         0x000000FFUL                            /**< Mode NONE for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_CONNECTION_SPI                           (_DEVINFO_EXTINFO_CONNECTION_SPI << 8)  /**< Shifted mode SPI for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_CONNECTION_NONE                          (_DEVINFO_EXTINFO_CONNECTION_NONE << 8) /**< Shifted mode NONE for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_REV_SHIFT                               16                                      /**< Shift value for REV */
#define _DEVINFO_EXTINFO_REV_MASK                                0xFF0000UL                              /**< Bit mask for REV */
#define _DEVINFO_EXTINFO_REV_REV1                                0x00000001UL                            /**< Mode REV1 for DEVINFO_EXTINFO */
#define _DEVINFO_EXTINFO_REV_NONE                                0x000000FFUL                            /**< Mode NONE for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_REV_REV1                                 (_DEVINFO_EXTINFO_REV_REV1 << 16)       /**< Shifted mode REV1 for DEVINFO_EXTINFO */
#define DEVINFO_EXTINFO_REV_NONE                                 (_DEVINFO_EXTINFO_REV_NONE << 16)       /**< Shifted mode NONE for DEVINFO_EXTINFO */

/* Bit fields for DEVINFO EUI48L */
#define _DEVINFO_EUI48L_MASK                                     0xFFFFFFFFUL /**< Mask for DEVINFO_EUI48L */
#define _DEVINFO_EUI48L_UNIQUEID_SHIFT                           0            /**< Shift value for UNIQUEID */
#define _DEVINFO_EUI48L_UNIQUEID_MASK                            0xFFFFFFUL   /**< Bit mask for UNIQUEID */
#define _DEVINFO_EUI48L_OUI48L_SHIFT                             24           /**< Shift value for OUI48L */
#define _DEVINFO_EUI48L_OUI48L_MASK                              0xFF000000UL /**< Bit mask for OUI48L */

/* Bit fields for DEVINFO EUI48H */
#define _DEVINFO_EUI48H_MASK                                     0x0000FFFFUL /**< Mask for DEVINFO_EUI48H */
#define _DEVINFO_EUI48H_OUI48H_SHIFT                             0            /**< Shift value for OUI48H */
#define _DEVINFO_EUI48H_OUI48H_MASK                              0xFFFFUL     /**< Bit mask for OUI48H */

/* Bit fields for DEVINFO CUSTOMINFO */
#define _DEVINFO_CUSTOMINFO_MASK                                 0xFFFF0000UL /**< Mask for DEVINFO_CUSTOMINFO */
#define _DEVINFO_CUSTOMINFO_PARTNO_SHIFT                         16           /**< Shift value for PARTNO */
#define _DEVINFO_CUSTOMINFO_PARTNO_MASK                          0xFFFF0000UL /**< Bit mask for PARTNO */

/* Bit fields for DEVINFO MEMINFO */
#define _DEVINFO_MEMINFO_MASK                                    0xFFFFFFFFUL                               /**< Mask for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_TEMPGRADE_SHIFT                         0                                          /**< Shift value for TEMPGRADE */
#define _DEVINFO_MEMINFO_TEMPGRADE_MASK                          0xFFUL                                     /**< Bit mask for TEMPGRADE */
#define _DEVINFO_MEMINFO_TEMPGRADE_N40TO85                       0x00000000UL                               /**< Mode N40TO85 for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_TEMPGRADE_N40TO125                      0x00000001UL                               /**< Mode N40TO125 for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_TEMPGRADE_N40TO105                      0x00000002UL                               /**< Mode N40TO105 for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_TEMPGRADE_N0TO70                        0x00000003UL                               /**< Mode N0TO70 for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_TEMPGRADE_N40TO85                        (_DEVINFO_MEMINFO_TEMPGRADE_N40TO85 << 0)  /**< Shifted mode N40TO85 for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_TEMPGRADE_N40TO125                       (_DEVINFO_MEMINFO_TEMPGRADE_N40TO125 << 0) /**< Shifted mode N40TO125 for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_TEMPGRADE_N40TO105                       (_DEVINFO_MEMINFO_TEMPGRADE_N40TO105 << 0) /**< Shifted mode N40TO105 for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_TEMPGRADE_N0TO70                         (_DEVINFO_MEMINFO_TEMPGRADE_N0TO70 << 0)   /**< Shifted mode N0TO70 for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_PKGTYPE_SHIFT                           8                                          /**< Shift value for PKGTYPE */
#define _DEVINFO_MEMINFO_PKGTYPE_MASK                            0xFF00UL                                   /**< Bit mask for PKGTYPE */
#define _DEVINFO_MEMINFO_PKGTYPE_WLCSP                           0x0000004AUL                               /**< Mode WLCSP for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_PKGTYPE_BGA                             0x0000004CUL                               /**< Mode BGA for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_PKGTYPE_QFN                             0x0000004DUL                               /**< Mode QFN for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_PKGTYPE_QFP                             0x00000051UL                               /**< Mode QFP for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_PKGTYPE_WLCSP                            (_DEVINFO_MEMINFO_PKGTYPE_WLCSP << 8)      /**< Shifted mode WLCSP for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_PKGTYPE_BGA                              (_DEVINFO_MEMINFO_PKGTYPE_BGA << 8)        /**< Shifted mode BGA for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_PKGTYPE_QFN                              (_DEVINFO_MEMINFO_PKGTYPE_QFN << 8)        /**< Shifted mode QFN for DEVINFO_MEMINFO */
#define DEVINFO_MEMINFO_PKGTYPE_QFP                              (_DEVINFO_MEMINFO_PKGTYPE_QFP << 8)        /**< Shifted mode QFP for DEVINFO_MEMINFO */
#define _DEVINFO_MEMINFO_PINCOUNT_SHIFT                          16                                         /**< Shift value for PINCOUNT */
#define _DEVINFO_MEMINFO_PINCOUNT_MASK                           0xFF0000UL                                 /**< Bit mask for PINCOUNT */
#define _DEVINFO_MEMINFO_FLASH_PAGE_SIZE_SHIFT                   24                                         /**< Shift value for FLASH_PAGE_SIZE */
#define _DEVINFO_MEMINFO_FLASH_PAGE_SIZE_MASK                    0xFF000000UL                               /**< Bit mask for FLASH_PAGE_SIZE */

/* Bit fields for DEVINFO UNIQUEL */
#define _DEVINFO_UNIQUEL_MASK                                    0xFFFFFFFFUL /**< Mask for DEVINFO_UNIQUEL */
#define _DEVINFO_UNIQUEL_UNIQUEL_SHIFT                           0            /**< Shift value for UNIQUEL */
#define _DEVINFO_UNIQUEL_UNIQUEL_MASK                            0xFFFFFFFFUL /**< Bit mask for UNIQUEL */

/* Bit fields for DEVINFO UNIQUEH */
#define _DEVINFO_UNIQUEH_MASK                                    0xFFFFFFFFUL /**< Mask for DEVINFO_UNIQUEH */
#define _DEVINFO_UNIQUEH_UNIQUEH_SHIFT                           0            /**< Shift value for UNIQUEH */
#define _DEVINFO_UNIQUEH_UNIQUEH_MASK                            0xFFFFFFFFUL /**< Bit mask for UNIQUEH */

/* Bit fields for DEVINFO MSIZE */
#define _DEVINFO_MSIZE_MASK                                      0xFFFFFFFFUL /**< Mask for DEVINFO_MSIZE */
#define _DEVINFO_MSIZE_FLASH_SHIFT                               0            /**< Shift value for FLASH */
#define _DEVINFO_MSIZE_FLASH_MASK                                0xFFFFUL     /**< Bit mask for FLASH */
#define _DEVINFO_MSIZE_SRAM_SHIFT                                16           /**< Shift value for SRAM */
#define _DEVINFO_MSIZE_SRAM_MASK                                 0xFFFF0000UL /**< Bit mask for SRAM */

/* Bit fields for DEVINFO PART */
#define _DEVINFO_PART_MASK                                       0xFFFFFFFFUL                                   /**< Mask for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_NUMBER_SHIFT                        0                                              /**< Shift value for DEVICE_NUMBER */
#define _DEVINFO_PART_DEVICE_NUMBER_MASK                         0xFFFFUL                                       /**< Bit mask for DEVICE_NUMBER */
#define _DEVINFO_PART_DEVICE_FAMILY_SHIFT                        16                                             /**< Shift value for DEVICE_FAMILY */
#define _DEVINFO_PART_DEVICE_FAMILY_MASK                         0xFF0000UL                                     /**< Bit mask for DEVICE_FAMILY */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG1P                    0x00000010UL                                   /**< Mode EFR32MG1P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG1B                    0x00000011UL                                   /**< Mode EFR32MG1B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG1V                    0x00000012UL                                   /**< Mode EFR32MG1V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG1P                    0x00000013UL                                   /**< Mode EFR32BG1P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG1B                    0x00000014UL                                   /**< Mode EFR32BG1B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG1V                    0x00000015UL                                   /**< Mode EFR32BG1V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG1P                    0x00000019UL                                   /**< Mode EFR32FG1P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG1B                    0x0000001AUL                                   /**< Mode EFR32FG1B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG1V                    0x0000001BUL                                   /**< Mode EFR32FG1V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG12P                   0x0000001CUL                                   /**< Mode EFR32MG12P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG12B                   0x0000001DUL                                   /**< Mode EFR32MG12B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG12V                   0x0000001EUL                                   /**< Mode EFR32MG12V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG12P                   0x0000001FUL                                   /**< Mode EFR32BG12P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG12B                   0x00000020UL                                   /**< Mode EFR32BG12B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG12V                   0x00000021UL                                   /**< Mode EFR32BG12V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG12P                   0x00000025UL                                   /**< Mode EFR32FG12P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG12B                   0x00000026UL                                   /**< Mode EFR32FG12B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG12V                   0x00000027UL                                   /**< Mode EFR32FG12V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG13P                   0x00000028UL                                   /**< Mode EFR32MG13P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG13B                   0x00000029UL                                   /**< Mode EFR32MG13B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG13V                   0x0000002AUL                                   /**< Mode EFR32MG13V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG13P                   0x0000002BUL                                   /**< Mode EFR32BG13P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG13B                   0x0000002CUL                                   /**< Mode EFR32BG13B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG13V                   0x0000002DUL                                   /**< Mode EFR32BG13V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG13P                   0x00000031UL                                   /**< Mode EFR32FG13P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG13B                   0x00000032UL                                   /**< Mode EFR32FG13B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG13V                   0x00000033UL                                   /**< Mode EFR32FG13V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG14P                   0x00000034UL                                   /**< Mode EFR32MG14P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG14B                   0x00000035UL                                   /**< Mode EFR32MG14B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32MG14V                   0x00000036UL                                   /**< Mode EFR32MG14V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG14P                   0x00000037UL                                   /**< Mode EFR32BG14P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG14B                   0x00000038UL                                   /**< Mode EFR32BG14B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32BG14V                   0x00000039UL                                   /**< Mode EFR32BG14V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG14P                   0x0000003DUL                                   /**< Mode EFR32FG14P for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG14B                   0x0000003EUL                                   /**< Mode EFR32FG14B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFR32FG14V                   0x0000003FUL                                   /**< Mode EFR32FG14V for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32G                       0x00000047UL                                   /**< Mode EFM32G for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_G                            0x00000047UL                                   /**< Mode G for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32GG                      0x00000048UL                                   /**< Mode EFM32GG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_GG                           0x00000048UL                                   /**< Mode GG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_TG                           0x00000049UL                                   /**< Mode TG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32TG                      0x00000049UL                                   /**< Mode EFM32TG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32LG                      0x0000004AUL                                   /**< Mode EFM32LG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_LG                           0x0000004AUL                                   /**< Mode LG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32WG                      0x0000004BUL                                   /**< Mode EFM32WG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_WG                           0x0000004BUL                                   /**< Mode WG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_ZG                           0x0000004CUL                                   /**< Mode ZG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32ZG                      0x0000004CUL                                   /**< Mode EFM32ZG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_HG                           0x0000004DUL                                   /**< Mode HG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32HG                      0x0000004DUL                                   /**< Mode EFM32HG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32PG1B                    0x00000051UL                                   /**< Mode EFM32PG1B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32JG1B                    0x00000053UL                                   /**< Mode EFM32JG1B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32PG12B                   0x00000055UL                                   /**< Mode EFM32PG12B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32JG12B                   0x00000057UL                                   /**< Mode EFM32JG12B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32GG11B                   0x00000064UL                                   /**< Mode EFM32GG11B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EFM32TG11B                   0x00000067UL                                   /**< Mode EFM32TG11B for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EZR32LG                      0x00000078UL                                   /**< Mode EZR32LG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EZR32WG                      0x00000079UL                                   /**< Mode EZR32WG for DEVINFO_PART */
#define _DEVINFO_PART_DEVICE_FAMILY_EZR32HG                      0x0000007AUL                                   /**< Mode EZR32HG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG1P                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG1P << 16)  /**< Shifted mode EFR32MG1P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG1B                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG1B << 16)  /**< Shifted mode EFR32MG1B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG1V                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG1V << 16)  /**< Shifted mode EFR32MG1V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG1P                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG1P << 16)  /**< Shifted mode EFR32BG1P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG1B                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG1B << 16)  /**< Shifted mode EFR32BG1B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG1V                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG1V << 16)  /**< Shifted mode EFR32BG1V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG1P                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG1P << 16)  /**< Shifted mode EFR32FG1P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG1B                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG1B << 16)  /**< Shifted mode EFR32FG1B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG1V                     (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG1V << 16)  /**< Shifted mode EFR32FG1V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG12P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG12P << 16) /**< Shifted mode EFR32MG12P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG12B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG12B << 16) /**< Shifted mode EFR32MG12B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG12V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG12V << 16) /**< Shifted mode EFR32MG12V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG12P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG12P << 16) /**< Shifted mode EFR32BG12P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG12B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG12B << 16) /**< Shifted mode EFR32BG12B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG12V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG12V << 16) /**< Shifted mode EFR32BG12V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG12P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG12P << 16) /**< Shifted mode EFR32FG12P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG12B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG12B << 16) /**< Shifted mode EFR32FG12B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG12V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG12V << 16) /**< Shifted mode EFR32FG12V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG13P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG13P << 16) /**< Shifted mode EFR32MG13P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG13B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG13B << 16) /**< Shifted mode EFR32MG13B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG13V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG13V << 16) /**< Shifted mode EFR32MG13V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG13P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG13P << 16) /**< Shifted mode EFR32BG13P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG13B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG13B << 16) /**< Shifted mode EFR32BG13B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG13V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG13V << 16) /**< Shifted mode EFR32BG13V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG13P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG13P << 16) /**< Shifted mode EFR32FG13P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG13B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG13B << 16) /**< Shifted mode EFR32FG13B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG13V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG13V << 16) /**< Shifted mode EFR32FG13V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG14P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG14P << 16) /**< Shifted mode EFR32MG14P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG14B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG14B << 16) /**< Shifted mode EFR32MG14B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32MG14V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32MG14V << 16) /**< Shifted mode EFR32MG14V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG14P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG14P << 16) /**< Shifted mode EFR32BG14P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG14B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG14B << 16) /**< Shifted mode EFR32BG14B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32BG14V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32BG14V << 16) /**< Shifted mode EFR32BG14V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG14P                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG14P << 16) /**< Shifted mode EFR32FG14P for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG14B                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG14B << 16) /**< Shifted mode EFR32FG14B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFR32FG14V                    (_DEVINFO_PART_DEVICE_FAMILY_EFR32FG14V << 16) /**< Shifted mode EFR32FG14V for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32G                        (_DEVINFO_PART_DEVICE_FAMILY_EFM32G << 16)     /**< Shifted mode EFM32G for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_G                             (_DEVINFO_PART_DEVICE_FAMILY_G << 16)          /**< Shifted mode G for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32GG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32GG << 16)    /**< Shifted mode EFM32GG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_GG                            (_DEVINFO_PART_DEVICE_FAMILY_GG << 16)         /**< Shifted mode GG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_TG                            (_DEVINFO_PART_DEVICE_FAMILY_TG << 16)         /**< Shifted mode TG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32TG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32TG << 16)    /**< Shifted mode EFM32TG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32LG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32LG << 16)    /**< Shifted mode EFM32LG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_LG                            (_DEVINFO_PART_DEVICE_FAMILY_LG << 16)         /**< Shifted mode LG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32WG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32WG << 16)    /**< Shifted mode EFM32WG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_WG                            (_DEVINFO_PART_DEVICE_FAMILY_WG << 16)         /**< Shifted mode WG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_ZG                            (_DEVINFO_PART_DEVICE_FAMILY_ZG << 16)         /**< Shifted mode ZG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32ZG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32ZG << 16)    /**< Shifted mode EFM32ZG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_HG                            (_DEVINFO_PART_DEVICE_FAMILY_HG << 16)         /**< Shifted mode HG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32HG                       (_DEVINFO_PART_DEVICE_FAMILY_EFM32HG << 16)    /**< Shifted mode EFM32HG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32PG1B                     (_DEVINFO_PART_DEVICE_FAMILY_EFM32PG1B << 16)  /**< Shifted mode EFM32PG1B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32JG1B                     (_DEVINFO_PART_DEVICE_FAMILY_EFM32JG1B << 16)  /**< Shifted mode EFM32JG1B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32PG12B                    (_DEVINFO_PART_DEVICE_FAMILY_EFM32PG12B << 16) /**< Shifted mode EFM32PG12B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32JG12B                    (_DEVINFO_PART_DEVICE_FAMILY_EFM32JG12B << 16) /**< Shifted mode EFM32JG12B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32GG11B                    (_DEVINFO_PART_DEVICE_FAMILY_EFM32GG11B << 16) /**< Shifted mode EFM32GG11B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EFM32TG11B                    (_DEVINFO_PART_DEVICE_FAMILY_EFM32TG11B << 16) /**< Shifted mode EFM32TG11B for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EZR32LG                       (_DEVINFO_PART_DEVICE_FAMILY_EZR32LG << 16)    /**< Shifted mode EZR32LG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EZR32WG                       (_DEVINFO_PART_DEVICE_FAMILY_EZR32WG << 16)    /**< Shifted mode EZR32WG for DEVINFO_PART */
#define DEVINFO_PART_DEVICE_FAMILY_EZR32HG                       (_DEVINFO_PART_DEVICE_FAMILY_EZR32HG << 16)    /**< Shifted mode EZR32HG for DEVINFO_PART */
#define _DEVINFO_PART_PROD_REV_SHIFT                             24                                             /**< Shift value for PROD_REV */
#define _DEVINFO_PART_PROD_REV_MASK                              0xFF000000UL                                   /**< Bit mask for PROD_REV */

/* Bit fields for DEVINFO DEVINFOREV */
#define _DEVINFO_DEVINFOREV_MASK                                 0x000000FFUL /**< Mask for DEVINFO_DEVINFOREV */
#define _DEVINFO_DEVINFOREV_DEVINFOREV_SHIFT                     0            /**< Shift value for DEVINFOREV */
#define _DEVINFO_DEVINFOREV_DEVINFOREV_MASK                      0xFFUL       /**< Bit mask for DEVINFOREV */

/* Bit fields for DEVINFO EMUTEMP */
#define _DEVINFO_EMUTEMP_MASK                                    0x000000FFUL /**< Mask for DEVINFO_EMUTEMP */
#define _DEVINFO_EMUTEMP_EMUTEMPROOM_SHIFT                       0            /**< Shift value for EMUTEMPROOM */
#define _DEVINFO_EMUTEMP_EMUTEMPROOM_MASK                        0xFFUL       /**< Bit mask for EMUTEMPROOM */

/* Bit fields for DEVINFO ADC0CAL0 */
#define _DEVINFO_ADC0CAL0_MASK                                   0x7FFF7FFFUL /**< Mask for DEVINFO_ADC0CAL0 */
#define _DEVINFO_ADC0CAL0_OFFSET1V25_SHIFT                       0            /**< Shift value for OFFSET1V25 */
#define _DEVINFO_ADC0CAL0_OFFSET1V25_MASK                        0xFUL        /**< Bit mask for OFFSET1V25 */
#define _DEVINFO_ADC0CAL0_NEGSEOFFSET1V25_SHIFT                  4            /**< Shift value for NEGSEOFFSET1V25 */
#define _DEVINFO_ADC0CAL0_NEGSEOFFSET1V25_MASK                   0xF0UL       /**< Bit mask for NEGSEOFFSET1V25 */
#define _DEVINFO_ADC0CAL0_GAIN1V25_SHIFT                         8            /**< Shift value for GAIN1V25 */
#define _DEVINFO_ADC0CAL0_GAIN1V25_MASK                          0x7F00UL     /**< Bit mask for GAIN1V25 */
#define _DEVINFO_ADC0CAL0_OFFSET2V5_SHIFT                        16           /**< Shift value for OFFSET2V5 */
#define _DEVINFO_ADC0CAL0_OFFSET2V5_MASK                         0xF0000UL    /**< Bit mask for OFFSET2V5 */
#define _DEVINFO_ADC0CAL0_NEGSEOFFSET2V5_SHIFT                   20           /**< Shift value for NEGSEOFFSET2V5 */
#define _DEVINFO_ADC0CAL0_NEGSEOFFSET2V5_MASK                    0xF00000UL   /**< Bit mask for NEGSEOFFSET2V5 */
#define _DEVINFO_ADC0CAL0_GAIN2V5_SHIFT                          24           /**< Shift value for GAIN2V5 */
#define _DEVINFO_ADC0CAL0_GAIN2V5_MASK                           0x7F000000UL /**< Bit mask for GAIN2V5 */

/* Bit fields for DEVINFO ADC0CAL1 */
#define _DEVINFO_ADC0CAL1_MASK                                   0x7FFF7FFFUL /**< Mask for DEVINFO_ADC0CAL1 */
#define _DEVINFO_ADC0CAL1_OFFSETVDD_SHIFT                        0            /**< Shift value for OFFSETVDD */
#define _DEVINFO_ADC0CAL1_OFFSETVDD_MASK                         0xFUL        /**< Bit mask for OFFSETVDD */
#define _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_SHIFT                   4            /**< Shift value for NEGSEOFFSETVDD */
#define _DEVINFO_ADC0CAL1_NEGSEOFFSETVDD_MASK                    0xF0UL       /**< Bit mask for NEGSEOFFSETVDD */
#define _DEVINFO_ADC0CAL1_GAINVDD_SHIFT                          8            /**< Shift value for GAINVDD */
#define _DEVINFO_ADC0CAL1_GAINVDD_MASK                           0x7F00UL     /**< Bit mask for GAINVDD */
#define _DEVINFO_ADC0CAL1_OFFSET5VDIFF_SHIFT                     16           /**< Shift value for OFFSET5VDIFF */
#define _DEVINFO_ADC0CAL1_OFFSET5VDIFF_MASK                      0xF0000UL    /**< Bit mask for OFFSET5VDIFF */
#define _DEVINFO_ADC0CAL1_NEGSEOFFSET5VDIFF_SHIFT                20           /**< Shift value for NEGSEOFFSET5VDIFF */
#define _DEVINFO_ADC0CAL1_NEGSEOFFSET5VDIFF_MASK                 0xF00000UL   /**< Bit mask for NEGSEOFFSET5VDIFF */
#define _DEVINFO_ADC0CAL1_GAIN5VDIFF_SHIFT                       24           /**< Shift value for GAIN5VDIFF */
#define _DEVINFO_ADC0CAL1_GAIN5VDIFF_MASK                        0x7F000000UL /**< Bit mask for GAIN5VDIFF */

/* Bit fields for DEVINFO ADC0CAL2 */
#define _DEVINFO_ADC0CAL2_MASK                                   0x000000FFUL /**< Mask for DEVINFO_ADC0CAL2 */
#define _DEVINFO_ADC0CAL2_OFFSET2XVDD_SHIFT                      0            /**< Shift value for OFFSET2XVDD */
#define _DEVINFO_ADC0CAL2_OFFSET2XVDD_MASK                       0xFUL        /**< Bit mask for OFFSET2XVDD */
#define _DEVINFO_ADC0CAL2_NEGSEOFFSET2XVDD_SHIFT                 4            /**< Shift value for NEGSEOFFSET2XVDD */
#define _DEVINFO_ADC0CAL2_NEGSEOFFSET2XVDD_MASK                  0xF0UL       /**< Bit mask for NEGSEOFFSET2XVDD */

/* Bit fields for DEVINFO ADC0CAL3 */
#define _DEVINFO_ADC0CAL3_MASK                                   0x0000FFF0UL /**< Mask for DEVINFO_ADC0CAL3 */
#define _DEVINFO_ADC0CAL3_TEMPREAD1V25_SHIFT                     4            /**< Shift value for TEMPREAD1V25 */
#define _DEVINFO_ADC0CAL3_TEMPREAD1V25_MASK                      0xFFF0UL     /**< Bit mask for TEMPREAD1V25 */

/* Bit fields for DEVINFO HFRCOCAL0 */
#define _DEVINFO_HFRCOCAL0_MASK                                  0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL0 */
#define _DEVINFO_HFRCOCAL0_TUNING_SHIFT                          0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL0_TUNING_MASK                           0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL0_FINETUNING_SHIFT                      8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL0_FINETUNING_MASK                       0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL0_FREQRANGE_SHIFT                       16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL0_FREQRANGE_MASK                        0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL0_CMPBIAS_SHIFT                         21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL0_CMPBIAS_MASK                          0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL0_LDOHP_SHIFT                           24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL0_LDOHP_MASK                            0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL0_CLKDIV_SHIFT                          25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL0_CLKDIV_MASK                           0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL0_FINETUNINGEN_SHIFT                    27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL0_FINETUNINGEN_MASK                     0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL0_VREFTC_SHIFT                          28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL0_VREFTC_MASK                           0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL3 */
#define _DEVINFO_HFRCOCAL3_MASK                                  0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL3 */
#define _DEVINFO_HFRCOCAL3_TUNING_SHIFT                          0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL3_TUNING_MASK                           0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL3_FINETUNING_SHIFT                      8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL3_FINETUNING_MASK                       0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL3_FREQRANGE_SHIFT                       16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL3_FREQRANGE_MASK                        0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL3_CMPBIAS_SHIFT                         21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL3_CMPBIAS_MASK                          0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL3_LDOHP_SHIFT                           24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL3_LDOHP_MASK                            0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL3_CLKDIV_SHIFT                          25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL3_CLKDIV_MASK                           0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL3_FINETUNINGEN_SHIFT                    27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL3_FINETUNINGEN_MASK                     0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL3_VREFTC_SHIFT                          28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL3_VREFTC_MASK                           0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL6 */
#define _DEVINFO_HFRCOCAL6_MASK                                  0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL6 */
#define _DEVINFO_HFRCOCAL6_TUNING_SHIFT                          0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL6_TUNING_MASK                           0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL6_FINETUNING_SHIFT                      8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL6_FINETUNING_MASK                       0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL6_FREQRANGE_SHIFT                       16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL6_FREQRANGE_MASK                        0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL6_CMPBIAS_SHIFT                         21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL6_CMPBIAS_MASK                          0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL6_LDOHP_SHIFT                           24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL6_LDOHP_MASK                            0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL6_CLKDIV_SHIFT                          25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL6_CLKDIV_MASK                           0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL6_FINETUNINGEN_SHIFT                    27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL6_FINETUNINGEN_MASK                     0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL6_VREFTC_SHIFT                          28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL6_VREFTC_MASK                           0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL7 */
#define _DEVINFO_HFRCOCAL7_MASK                                  0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL7 */
#define _DEVINFO_HFRCOCAL7_TUNING_SHIFT                          0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL7_TUNING_MASK                           0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL7_FINETUNING_SHIFT                      8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL7_FINETUNING_MASK                       0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL7_FREQRANGE_SHIFT                       16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL7_FREQRANGE_MASK                        0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL7_CMPBIAS_SHIFT                         21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL7_CMPBIAS_MASK                          0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL7_LDOHP_SHIFT                           24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL7_LDOHP_MASK                            0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL7_CLKDIV_SHIFT                          25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL7_CLKDIV_MASK                           0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL7_FINETUNINGEN_SHIFT                    27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL7_FINETUNINGEN_MASK                     0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL7_VREFTC_SHIFT                          28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL7_VREFTC_MASK                           0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL8 */
#define _DEVINFO_HFRCOCAL8_MASK                                  0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL8 */
#define _DEVINFO_HFRCOCAL8_TUNING_SHIFT                          0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL8_TUNING_MASK                           0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL8_FINETUNING_SHIFT                      8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL8_FINETUNING_MASK                       0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL8_FREQRANGE_SHIFT                       16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL8_FREQRANGE_MASK                        0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL8_CMPBIAS_SHIFT                         21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL8_CMPBIAS_MASK                          0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL8_LDOHP_SHIFT                           24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL8_LDOHP_MASK                            0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL8_CLKDIV_SHIFT                          25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL8_CLKDIV_MASK                           0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL8_FINETUNINGEN_SHIFT                    27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL8_FINETUNINGEN_MASK                     0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL8_VREFTC_SHIFT                          28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL8_VREFTC_MASK                           0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL10 */
#define _DEVINFO_HFRCOCAL10_MASK                                 0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL10 */
#define _DEVINFO_HFRCOCAL10_TUNING_SHIFT                         0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL10_TUNING_MASK                          0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL10_FINETUNING_SHIFT                     8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL10_FINETUNING_MASK                      0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL10_FREQRANGE_SHIFT                      16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL10_FREQRANGE_MASK                       0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL10_CMPBIAS_SHIFT                        21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL10_CMPBIAS_MASK                         0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL10_LDOHP_SHIFT                          24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL10_LDOHP_MASK                           0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL10_CLKDIV_SHIFT                         25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL10_CLKDIV_MASK                          0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL10_FINETUNINGEN_SHIFT                   27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL10_FINETUNINGEN_MASK                    0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL10_VREFTC_SHIFT                         28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL10_VREFTC_MASK                          0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL11 */
#define _DEVINFO_HFRCOCAL11_MASK                                 0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL11 */
#define _DEVINFO_HFRCOCAL11_TUNING_SHIFT                         0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL11_TUNING_MASK                          0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL11_FINETUNING_SHIFT                     8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL11_FINETUNING_MASK                      0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL11_FREQRANGE_SHIFT                      16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL11_FREQRANGE_MASK                       0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL11_CMPBIAS_SHIFT                        21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL11_CMPBIAS_MASK                         0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL11_LDOHP_SHIFT                          24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL11_LDOHP_MASK                           0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL11_CLKDIV_SHIFT                         25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL11_CLKDIV_MASK                          0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL11_FINETUNINGEN_SHIFT                   27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL11_FINETUNINGEN_MASK                    0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL11_VREFTC_SHIFT                         28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL11_VREFTC_MASK                          0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO HFRCOCAL12 */
#define _DEVINFO_HFRCOCAL12_MASK                                 0xFFFF3F7FUL /**< Mask for DEVINFO_HFRCOCAL12 */
#define _DEVINFO_HFRCOCAL12_TUNING_SHIFT                         0            /**< Shift value for TUNING */
#define _DEVINFO_HFRCOCAL12_TUNING_MASK                          0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_HFRCOCAL12_FINETUNING_SHIFT                     8            /**< Shift value for FINETUNING */
#define _DEVINFO_HFRCOCAL12_FINETUNING_MASK                      0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_HFRCOCAL12_FREQRANGE_SHIFT                      16           /**< Shift value for FREQRANGE */
#define _DEVINFO_HFRCOCAL12_FREQRANGE_MASK                       0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_HFRCOCAL12_CMPBIAS_SHIFT                        21           /**< Shift value for CMPBIAS */
#define _DEVINFO_HFRCOCAL12_CMPBIAS_MASK                         0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_HFRCOCAL12_LDOHP_SHIFT                          24           /**< Shift value for LDOHP */
#define _DEVINFO_HFRCOCAL12_LDOHP_MASK                           0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_HFRCOCAL12_CLKDIV_SHIFT                         25           /**< Shift value for CLKDIV */
#define _DEVINFO_HFRCOCAL12_CLKDIV_MASK                          0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_HFRCOCAL12_FINETUNINGEN_SHIFT                   27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL12_FINETUNINGEN_MASK                    0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_HFRCOCAL12_VREFTC_SHIFT                         28           /**< Shift value for VREFTC */
#define _DEVINFO_HFRCOCAL12_VREFTC_MASK                          0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL0 */
#define _DEVINFO_AUXHFRCOCAL0_MASK                               0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL0 */
#define _DEVINFO_AUXHFRCOCAL0_TUNING_SHIFT                       0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL0_TUNING_MASK                        0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL0_FINETUNING_SHIFT                   8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL0_FINETUNING_MASK                    0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL0_FREQRANGE_SHIFT                    16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL0_FREQRANGE_MASK                     0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL0_CMPBIAS_SHIFT                      21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL0_CMPBIAS_MASK                       0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL0_LDOHP_SHIFT                        24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL0_LDOHP_MASK                         0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL0_CLKDIV_SHIFT                       25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL0_CLKDIV_MASK                        0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL0_FINETUNINGEN_SHIFT                 27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL0_FINETUNINGEN_MASK                  0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL0_VREFTC_SHIFT                       28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL0_VREFTC_MASK                        0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL3 */
#define _DEVINFO_AUXHFRCOCAL3_MASK                               0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL3 */
#define _DEVINFO_AUXHFRCOCAL3_TUNING_SHIFT                       0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL3_TUNING_MASK                        0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL3_FINETUNING_SHIFT                   8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL3_FINETUNING_MASK                    0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL3_FREQRANGE_SHIFT                    16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL3_FREQRANGE_MASK                     0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL3_CMPBIAS_SHIFT                      21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL3_CMPBIAS_MASK                       0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL3_LDOHP_SHIFT                        24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL3_LDOHP_MASK                         0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL3_CLKDIV_SHIFT                       25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL3_CLKDIV_MASK                        0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL3_FINETUNINGEN_SHIFT                 27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL3_FINETUNINGEN_MASK                  0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL3_VREFTC_SHIFT                       28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL3_VREFTC_MASK                        0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL6 */
#define _DEVINFO_AUXHFRCOCAL6_MASK                               0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL6 */
#define _DEVINFO_AUXHFRCOCAL6_TUNING_SHIFT                       0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL6_TUNING_MASK                        0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL6_FINETUNING_SHIFT                   8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL6_FINETUNING_MASK                    0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL6_FREQRANGE_SHIFT                    16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL6_FREQRANGE_MASK                     0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL6_CMPBIAS_SHIFT                      21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL6_CMPBIAS_MASK                       0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL6_LDOHP_SHIFT                        24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL6_LDOHP_MASK                         0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL6_CLKDIV_SHIFT                       25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL6_CLKDIV_MASK                        0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL6_FINETUNINGEN_SHIFT                 27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL6_FINETUNINGEN_MASK                  0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL6_VREFTC_SHIFT                       28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL6_VREFTC_MASK                        0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL7 */
#define _DEVINFO_AUXHFRCOCAL7_MASK                               0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL7 */
#define _DEVINFO_AUXHFRCOCAL7_TUNING_SHIFT                       0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL7_TUNING_MASK                        0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL7_FINETUNING_SHIFT                   8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL7_FINETUNING_MASK                    0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL7_FREQRANGE_SHIFT                    16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL7_FREQRANGE_MASK                     0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL7_CMPBIAS_SHIFT                      21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL7_CMPBIAS_MASK                       0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL7_LDOHP_SHIFT                        24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL7_LDOHP_MASK                         0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL7_CLKDIV_SHIFT                       25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL7_CLKDIV_MASK                        0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL7_FINETUNINGEN_SHIFT                 27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL7_FINETUNINGEN_MASK                  0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL7_VREFTC_SHIFT                       28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL7_VREFTC_MASK                        0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL8 */
#define _DEVINFO_AUXHFRCOCAL8_MASK                               0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL8 */
#define _DEVINFO_AUXHFRCOCAL8_TUNING_SHIFT                       0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL8_TUNING_MASK                        0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL8_FINETUNING_SHIFT                   8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL8_FINETUNING_MASK                    0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL8_FREQRANGE_SHIFT                    16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL8_FREQRANGE_MASK                     0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL8_CMPBIAS_SHIFT                      21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL8_CMPBIAS_MASK                       0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL8_LDOHP_SHIFT                        24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL8_LDOHP_MASK                         0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL8_CLKDIV_SHIFT                       25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL8_CLKDIV_MASK                        0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL8_FINETUNINGEN_SHIFT                 27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL8_FINETUNINGEN_MASK                  0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL8_VREFTC_SHIFT                       28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL8_VREFTC_MASK                        0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL10 */
#define _DEVINFO_AUXHFRCOCAL10_MASK                              0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL10 */
#define _DEVINFO_AUXHFRCOCAL10_TUNING_SHIFT                      0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL10_TUNING_MASK                       0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL10_FINETUNING_SHIFT                  8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL10_FINETUNING_MASK                   0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL10_FREQRANGE_SHIFT                   16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL10_FREQRANGE_MASK                    0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL10_CMPBIAS_SHIFT                     21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL10_CMPBIAS_MASK                      0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL10_LDOHP_SHIFT                       24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL10_LDOHP_MASK                        0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL10_CLKDIV_SHIFT                      25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL10_CLKDIV_MASK                       0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL10_FINETUNINGEN_SHIFT                27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL10_FINETUNINGEN_MASK                 0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL10_VREFTC_SHIFT                      28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL10_VREFTC_MASK                       0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL11 */
#define _DEVINFO_AUXHFRCOCAL11_MASK                              0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL11 */
#define _DEVINFO_AUXHFRCOCAL11_TUNING_SHIFT                      0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL11_TUNING_MASK                       0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL11_FINETUNING_SHIFT                  8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL11_FINETUNING_MASK                   0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL11_FREQRANGE_SHIFT                   16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL11_FREQRANGE_MASK                    0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL11_CMPBIAS_SHIFT                     21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL11_CMPBIAS_MASK                      0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL11_LDOHP_SHIFT                       24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL11_LDOHP_MASK                        0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL11_CLKDIV_SHIFT                      25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL11_CLKDIV_MASK                       0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL11_FINETUNINGEN_SHIFT                27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL11_FINETUNINGEN_MASK                 0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL11_VREFTC_SHIFT                      28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL11_VREFTC_MASK                       0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO AUXHFRCOCAL12 */
#define _DEVINFO_AUXHFRCOCAL12_MASK                              0xFFFF3F7FUL /**< Mask for DEVINFO_AUXHFRCOCAL12 */
#define _DEVINFO_AUXHFRCOCAL12_TUNING_SHIFT                      0            /**< Shift value for TUNING */
#define _DEVINFO_AUXHFRCOCAL12_TUNING_MASK                       0x7FUL       /**< Bit mask for TUNING */
#define _DEVINFO_AUXHFRCOCAL12_FINETUNING_SHIFT                  8            /**< Shift value for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL12_FINETUNING_MASK                   0x3F00UL     /**< Bit mask for FINETUNING */
#define _DEVINFO_AUXHFRCOCAL12_FREQRANGE_SHIFT                   16           /**< Shift value for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL12_FREQRANGE_MASK                    0x1F0000UL   /**< Bit mask for FREQRANGE */
#define _DEVINFO_AUXHFRCOCAL12_CMPBIAS_SHIFT                     21           /**< Shift value for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL12_CMPBIAS_MASK                      0xE00000UL   /**< Bit mask for CMPBIAS */
#define _DEVINFO_AUXHFRCOCAL12_LDOHP_SHIFT                       24           /**< Shift value for LDOHP */
#define _DEVINFO_AUXHFRCOCAL12_LDOHP_MASK                        0x1000000UL  /**< Bit mask for LDOHP */
#define _DEVINFO_AUXHFRCOCAL12_CLKDIV_SHIFT                      25           /**< Shift value for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL12_CLKDIV_MASK                       0x6000000UL  /**< Bit mask for CLKDIV */
#define _DEVINFO_AUXHFRCOCAL12_FINETUNINGEN_SHIFT                27           /**< Shift value for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL12_FINETUNINGEN_MASK                 0x8000000UL  /**< Bit mask for FINETUNINGEN */
#define _DEVINFO_AUXHFRCOCAL12_VREFTC_SHIFT                      28           /**< Shift value for VREFTC */
#define _DEVINFO_AUXHFRCOCAL12_VREFTC_MASK                       0xF0000000UL /**< Bit mask for VREFTC */

/* Bit fields for DEVINFO VMONCAL0 */
#define _DEVINFO_VMONCAL0_MASK                                   0xFFFFFFFFUL /**< Mask for DEVINFO_VMONCAL0 */
#define _DEVINFO_VMONCAL0_AVDD1V86THRESFINE_SHIFT                0            /**< Shift value for AVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL0_AVDD1V86THRESFINE_MASK                 0xFUL        /**< Bit mask for AVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL0_AVDD1V86THRESCOARSE_SHIFT              4            /**< Shift value for AVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL0_AVDD1V86THRESCOARSE_MASK               0xF0UL       /**< Bit mask for AVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL0_AVDD2V98THRESFINE_SHIFT                8            /**< Shift value for AVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL0_AVDD2V98THRESFINE_MASK                 0xF00UL      /**< Bit mask for AVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL0_AVDD2V98THRESCOARSE_SHIFT              12           /**< Shift value for AVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL0_AVDD2V98THRESCOARSE_MASK               0xF000UL     /**< Bit mask for AVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL0_ALTAVDD1V86THRESFINE_SHIFT             16           /**< Shift value for ALTAVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL0_ALTAVDD1V86THRESFINE_MASK              0xF0000UL    /**< Bit mask for ALTAVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL0_ALTAVDD1V86THRESCOARSE_SHIFT           20           /**< Shift value for ALTAVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL0_ALTAVDD1V86THRESCOARSE_MASK            0xF00000UL   /**< Bit mask for ALTAVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL0_ALTAVDD2V98THRESFINE_SHIFT             24           /**< Shift value for ALTAVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL0_ALTAVDD2V98THRESFINE_MASK              0xF000000UL  /**< Bit mask for ALTAVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL0_ALTAVDD2V98THRESCOARSE_SHIFT           28           /**< Shift value for ALTAVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL0_ALTAVDD2V98THRESCOARSE_MASK            0xF0000000UL /**< Bit mask for ALTAVDD2V98THRESCOARSE */

/* Bit fields for DEVINFO VMONCAL1 */
#define _DEVINFO_VMONCAL1_MASK                                   0xFFFFFFFFUL /**< Mask for DEVINFO_VMONCAL1 */
#define _DEVINFO_VMONCAL1_DVDD1V86THRESFINE_SHIFT                0            /**< Shift value for DVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL1_DVDD1V86THRESFINE_MASK                 0xFUL        /**< Bit mask for DVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL1_DVDD1V86THRESCOARSE_SHIFT              4            /**< Shift value for DVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL1_DVDD1V86THRESCOARSE_MASK               0xF0UL       /**< Bit mask for DVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL1_DVDD2V98THRESFINE_SHIFT                8            /**< Shift value for DVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL1_DVDD2V98THRESFINE_MASK                 0xF00UL      /**< Bit mask for DVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL1_DVDD2V98THRESCOARSE_SHIFT              12           /**< Shift value for DVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL1_DVDD2V98THRESCOARSE_MASK               0xF000UL     /**< Bit mask for DVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL1_IO01V86THRESFINE_SHIFT                 16           /**< Shift value for IO01V86THRESFINE */
#define _DEVINFO_VMONCAL1_IO01V86THRESFINE_MASK                  0xF0000UL    /**< Bit mask for IO01V86THRESFINE */
#define _DEVINFO_VMONCAL1_IO01V86THRESCOARSE_SHIFT               20           /**< Shift value for IO01V86THRESCOARSE */
#define _DEVINFO_VMONCAL1_IO01V86THRESCOARSE_MASK                0xF00000UL   /**< Bit mask for IO01V86THRESCOARSE */
#define _DEVINFO_VMONCAL1_IO02V98THRESFINE_SHIFT                 24           /**< Shift value for IO02V98THRESFINE */
#define _DEVINFO_VMONCAL1_IO02V98THRESFINE_MASK                  0xF000000UL  /**< Bit mask for IO02V98THRESFINE */
#define _DEVINFO_VMONCAL1_IO02V98THRESCOARSE_SHIFT               28           /**< Shift value for IO02V98THRESCOARSE */
#define _DEVINFO_VMONCAL1_IO02V98THRESCOARSE_MASK                0xF0000000UL /**< Bit mask for IO02V98THRESCOARSE */

/* Bit fields for DEVINFO VMONCAL2 */
#define _DEVINFO_VMONCAL2_MASK                                   0xFFFFFFFFUL /**< Mask for DEVINFO_VMONCAL2 */
#define _DEVINFO_VMONCAL2_PAVDD1V86THRESFINE_SHIFT               0            /**< Shift value for PAVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL2_PAVDD1V86THRESFINE_MASK                0xFUL        /**< Bit mask for PAVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL2_PAVDD1V86THRESCOARSE_SHIFT             4            /**< Shift value for PAVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL2_PAVDD1V86THRESCOARSE_MASK              0xF0UL       /**< Bit mask for PAVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL2_PAVDD2V98THRESFINE_SHIFT               8            /**< Shift value for PAVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL2_PAVDD2V98THRESFINE_MASK                0xF00UL      /**< Bit mask for PAVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL2_PAVDD2V98THRESCOARSE_SHIFT             12           /**< Shift value for PAVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL2_PAVDD2V98THRESCOARSE_MASK              0xF000UL     /**< Bit mask for PAVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL2_FVDD1V86THRESFINE_SHIFT                16           /**< Shift value for FVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL2_FVDD1V86THRESFINE_MASK                 0xF0000UL    /**< Bit mask for FVDD1V86THRESFINE */
#define _DEVINFO_VMONCAL2_FVDD1V86THRESCOARSE_SHIFT              20           /**< Shift value for FVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL2_FVDD1V86THRESCOARSE_MASK               0xF00000UL   /**< Bit mask for FVDD1V86THRESCOARSE */
#define _DEVINFO_VMONCAL2_FVDD2V98THRESFINE_SHIFT                24           /**< Shift value for FVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL2_FVDD2V98THRESFINE_MASK                 0xF000000UL  /**< Bit mask for FVDD2V98THRESFINE */
#define _DEVINFO_VMONCAL2_FVDD2V98THRESCOARSE_SHIFT              28           /**< Shift value for FVDD2V98THRESCOARSE */
#define _DEVINFO_VMONCAL2_FVDD2V98THRESCOARSE_MASK               0xF0000000UL /**< Bit mask for FVDD2V98THRESCOARSE */

/* Bit fields for DEVINFO IDAC0CAL0 */
#define _DEVINFO_IDAC0CAL0_MASK                                  0xFFFFFFFFUL /**< Mask for DEVINFO_IDAC0CAL0 */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE0TUNING_SHIFT              0            /**< Shift value for SOURCERANGE0TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE0TUNING_MASK               0xFFUL       /**< Bit mask for SOURCERANGE0TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE1TUNING_SHIFT              8            /**< Shift value for SOURCERANGE1TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE1TUNING_MASK               0xFF00UL     /**< Bit mask for SOURCERANGE1TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE2TUNING_SHIFT              16           /**< Shift value for SOURCERANGE2TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE2TUNING_MASK               0xFF0000UL   /**< Bit mask for SOURCERANGE2TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE3TUNING_SHIFT              24           /**< Shift value for SOURCERANGE3TUNING */
#define _DEVINFO_IDAC0CAL0_SOURCERANGE3TUNING_MASK               0xFF000000UL /**< Bit mask for SOURCERANGE3TUNING */

/* Bit fields for DEVINFO IDAC0CAL1 */
#define _DEVINFO_IDAC0CAL1_MASK                                  0xFFFFFFFFUL /**< Mask for DEVINFO_IDAC0CAL1 */
#define _DEVINFO_IDAC0CAL1_SINKRANGE0TUNING_SHIFT                0            /**< Shift value for SINKRANGE0TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE0TUNING_MASK                 0xFFUL       /**< Bit mask for SINKRANGE0TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE1TUNING_SHIFT                8            /**< Shift value for SINKRANGE1TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE1TUNING_MASK                 0xFF00UL     /**< Bit mask for SINKRANGE1TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE2TUNING_SHIFT                16           /**< Shift value for SINKRANGE2TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE2TUNING_MASK                 0xFF0000UL   /**< Bit mask for SINKRANGE2TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE3TUNING_SHIFT                24           /**< Shift value for SINKRANGE3TUNING */
#define _DEVINFO_IDAC0CAL1_SINKRANGE3TUNING_MASK                 0xFF000000UL /**< Bit mask for SINKRANGE3TUNING */

/* Bit fields for DEVINFO DCDCLNVCTRL0 */
#define _DEVINFO_DCDCLNVCTRL0_MASK                               0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLNVCTRL0 */
#define _DEVINFO_DCDCLNVCTRL0_1V2LNATT0_SHIFT                    0            /**< Shift value for 1V2LNATT0 */
#define _DEVINFO_DCDCLNVCTRL0_1V2LNATT0_MASK                     0xFFUL       /**< Bit mask for 1V2LNATT0 */
#define _DEVINFO_DCDCLNVCTRL0_1V8LNATT0_SHIFT                    8            /**< Shift value for 1V8LNATT0 */
#define _DEVINFO_DCDCLNVCTRL0_1V8LNATT0_MASK                     0xFF00UL     /**< Bit mask for 1V8LNATT0 */
#define _DEVINFO_DCDCLNVCTRL0_1V8LNATT1_SHIFT                    16           /**< Shift value for 1V8LNATT1 */
#define _DEVINFO_DCDCLNVCTRL0_1V8LNATT1_MASK                     0xFF0000UL   /**< Bit mask for 1V8LNATT1 */
#define _DEVINFO_DCDCLNVCTRL0_3V0LNATT1_SHIFT                    24           /**< Shift value for 3V0LNATT1 */
#define _DEVINFO_DCDCLNVCTRL0_3V0LNATT1_MASK                     0xFF000000UL /**< Bit mask for 3V0LNATT1 */

/* Bit fields for DEVINFO DCDCLPVCTRL0 */
#define _DEVINFO_DCDCLPVCTRL0_MASK                               0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLPVCTRL0 */
#define _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS0_SHIFT          0            /**< Shift value for 1V2LPATT0LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS0_MASK           0xFFUL       /**< Bit mask for 1V2LPATT0LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS0_SHIFT          8            /**< Shift value for 1V8LPATT0LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS0_MASK           0xFF00UL     /**< Bit mask for 1V8LPATT0LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS1_SHIFT          16           /**< Shift value for 1V2LPATT0LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS1_MASK           0xFF0000UL   /**< Bit mask for 1V2LPATT0LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS1_SHIFT          24           /**< Shift value for 1V8LPATT0LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS1_MASK           0xFF000000UL /**< Bit mask for 1V8LPATT0LPCMPBIAS1 */

/* Bit fields for DEVINFO DCDCLPVCTRL1 */
#define _DEVINFO_DCDCLPVCTRL1_MASK                               0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLPVCTRL1 */
#define _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS2_SHIFT          0            /**< Shift value for 1V2LPATT0LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS2_MASK           0xFFUL       /**< Bit mask for 1V2LPATT0LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS2_SHIFT          8            /**< Shift value for 1V8LPATT0LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS2_MASK           0xFF00UL     /**< Bit mask for 1V8LPATT0LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS3_SHIFT          16           /**< Shift value for 1V2LPATT0LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS3_MASK           0xFF0000UL   /**< Bit mask for 1V2LPATT0LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS3_SHIFT          24           /**< Shift value for 1V8LPATT0LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS3_MASK           0xFF000000UL /**< Bit mask for 1V8LPATT0LPCMPBIAS3 */

/* Bit fields for DEVINFO DCDCLPVCTRL2 */
#define _DEVINFO_DCDCLPVCTRL2_MASK                               0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLPVCTRL2 */
#define _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS0_SHIFT          0            /**< Shift value for 1V8LPATT1LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS0_MASK           0xFFUL       /**< Bit mask for 1V8LPATT1LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS0_SHIFT          8            /**< Shift value for 3V0LPATT1LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS0_MASK           0xFF00UL     /**< Bit mask for 3V0LPATT1LPCMPBIAS0 */
#define _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS1_SHIFT          16           /**< Shift value for 1V8LPATT1LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS1_MASK           0xFF0000UL   /**< Bit mask for 1V8LPATT1LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS1_SHIFT          24           /**< Shift value for 3V0LPATT1LPCMPBIAS1 */
#define _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS1_MASK           0xFF000000UL /**< Bit mask for 3V0LPATT1LPCMPBIAS1 */

/* Bit fields for DEVINFO DCDCLPVCTRL3 */
#define _DEVINFO_DCDCLPVCTRL3_MASK                               0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLPVCTRL3 */
#define _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS2_SHIFT          0            /**< Shift value for 1V8LPATT1LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS2_MASK           0xFFUL       /**< Bit mask for 1V8LPATT1LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS2_SHIFT          8            /**< Shift value for 3V0LPATT1LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS2_MASK           0xFF00UL     /**< Bit mask for 3V0LPATT1LPCMPBIAS2 */
#define _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS3_SHIFT          16           /**< Shift value for 1V8LPATT1LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS3_MASK           0xFF0000UL   /**< Bit mask for 1V8LPATT1LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS3_SHIFT          24           /**< Shift value for 3V0LPATT1LPCMPBIAS3 */
#define _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS3_MASK           0xFF000000UL /**< Bit mask for 3V0LPATT1LPCMPBIAS3 */

/* Bit fields for DEVINFO DCDCLPCMPHYSSEL0 */
#define _DEVINFO_DCDCLPCMPHYSSEL0_MASK                           0x0000FFFFUL /**< Mask for DEVINFO_DCDCLPCMPHYSSEL0 */
#define _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT0_SHIFT        0            /**< Shift value for LPCMPHYSSELLPATT0 */
#define _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT0_MASK         0xFFUL       /**< Bit mask for LPCMPHYSSELLPATT0 */
#define _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT1_SHIFT        8            /**< Shift value for LPCMPHYSSELLPATT1 */
#define _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT1_MASK         0xFF00UL     /**< Bit mask for LPCMPHYSSELLPATT1 */

/* Bit fields for DEVINFO DCDCLPCMPHYSSEL1 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_MASK                           0xFFFFFFFFUL /**< Mask for DEVINFO_DCDCLPCMPHYSSEL1 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS0_SHIFT    0            /**< Shift value for LPCMPHYSSELLPCMPBIAS0 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS0_MASK     0xFFUL       /**< Bit mask for LPCMPHYSSELLPCMPBIAS0 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS1_SHIFT    8            /**< Shift value for LPCMPHYSSELLPCMPBIAS1 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS1_MASK     0xFF00UL     /**< Bit mask for LPCMPHYSSELLPCMPBIAS1 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS2_SHIFT    16           /**< Shift value for LPCMPHYSSELLPCMPBIAS2 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS2_MASK     0xFF0000UL   /**< Bit mask for LPCMPHYSSELLPCMPBIAS2 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS3_SHIFT    24           /**< Shift value for LPCMPHYSSELLPCMPBIAS3 */
#define _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS3_MASK     0xFF000000UL /**< Bit mask for LPCMPHYSSELLPCMPBIAS3 */

/* Bit fields for DEVINFO VDAC0MAINCAL */
#define _DEVINFO_VDAC0MAINCAL_MASK                               0x3FFFFFFFUL /**< Mask for DEVINFO_VDAC0MAINCAL */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM1V25LN_SHIFT            0            /**< Shift value for GAINERRTRIM1V25LN */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM1V25LN_MASK             0x3FUL       /**< Bit mask for GAINERRTRIM1V25LN */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM2V5LN_SHIFT             6            /**< Shift value for GAINERRTRIM2V5LN */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM2V5LN_MASK              0xFC0UL      /**< Bit mask for GAINERRTRIM2V5LN */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM1V25_SHIFT              12           /**< Shift value for GAINERRTRIM1V25 */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM1V25_MASK               0x3F000UL    /**< Bit mask for GAINERRTRIM1V25 */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM2V5_SHIFT               18           /**< Shift value for GAINERRTRIM2V5 */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIM2V5_MASK                0xFC0000UL   /**< Bit mask for GAINERRTRIM2V5 */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIMVDDANAEXTPIN_SHIFT      24           /**< Shift value for GAINERRTRIMVDDANAEXTPIN */
#define _DEVINFO_VDAC0MAINCAL_GAINERRTRIMVDDANAEXTPIN_MASK       0x3F000000UL /**< Bit mask for GAINERRTRIMVDDANAEXTPIN */

/* Bit fields for DEVINFO VDAC0ALTCAL */
#define _DEVINFO_VDAC0ALTCAL_MASK                                0x3FFFFFFFUL /**< Mask for DEVINFO_VDAC0ALTCAL */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM1V25LNALT_SHIFT          0            /**< Shift value for GAINERRTRIM1V25LNALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM1V25LNALT_MASK           0x3FUL       /**< Bit mask for GAINERRTRIM1V25LNALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM2V5LNALT_SHIFT           6            /**< Shift value for GAINERRTRIM2V5LNALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM2V5LNALT_MASK            0xFC0UL      /**< Bit mask for GAINERRTRIM2V5LNALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM1V25ALT_SHIFT            12           /**< Shift value for GAINERRTRIM1V25ALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM1V25ALT_MASK             0x3F000UL    /**< Bit mask for GAINERRTRIM1V25ALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM2V5ALT_SHIFT             18           /**< Shift value for GAINERRTRIM2V5ALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIM2V5ALT_MASK              0xFC0000UL   /**< Bit mask for GAINERRTRIM2V5ALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIMVDDANAEXTPINALT_SHIFT    24           /**< Shift value for GAINERRTRIMVDDANAEXTPINALT */
#define _DEVINFO_VDAC0ALTCAL_GAINERRTRIMVDDANAEXTPINALT_MASK     0x3F000000UL /**< Bit mask for GAINERRTRIMVDDANAEXTPINALT */

/* Bit fields for DEVINFO VDAC0CH1CAL */
#define _DEVINFO_VDAC0CH1CAL_MASK                                0x00000FF7UL /**< Mask for DEVINFO_VDAC0CH1CAL */
#define _DEVINFO_VDAC0CH1CAL_OFFSETTRIM_SHIFT                    0            /**< Shift value for OFFSETTRIM */
#define _DEVINFO_VDAC0CH1CAL_OFFSETTRIM_MASK                     0x7UL        /**< Bit mask for OFFSETTRIM */
#define _DEVINFO_VDAC0CH1CAL_GAINERRTRIMCH1A_SHIFT               4            /**< Shift value for GAINERRTRIMCH1A */
#define _DEVINFO_VDAC0CH1CAL_GAINERRTRIMCH1A_MASK                0xF0UL       /**< Bit mask for GAINERRTRIMCH1A */
#define _DEVINFO_VDAC0CH1CAL_GAINERRTRIMCH1B_SHIFT               8            /**< Shift value for GAINERRTRIMCH1B */
#define _DEVINFO_VDAC0CH1CAL_GAINERRTRIMCH1B_MASK                0xF00UL      /**< Bit mask for GAINERRTRIMCH1B */

/* Bit fields for DEVINFO OPA0CAL0 */
#define _DEVINFO_OPA0CAL0_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL0 */
#define _DEVINFO_OPA0CAL0_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL0_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL0_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL0_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL0_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL0_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL0_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL0_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL0_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL0_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL0_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL0_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL0_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL0_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL1 */
#define _DEVINFO_OPA0CAL1_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL1 */
#define _DEVINFO_OPA0CAL1_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL1_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL1_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL1_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL1_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL1_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL1_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL1_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL1_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL1_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL1_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL1_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL1_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL1_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL2 */
#define _DEVINFO_OPA0CAL2_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL2 */
#define _DEVINFO_OPA0CAL2_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL2_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL2_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL2_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL2_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL2_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL2_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL2_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL2_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL2_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL2_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL2_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL2_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL2_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL3 */
#define _DEVINFO_OPA0CAL3_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL3 */
#define _DEVINFO_OPA0CAL3_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL3_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL3_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL3_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL3_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL3_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL3_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL3_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL3_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL3_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL3_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL3_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL3_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL3_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL0 */
#define _DEVINFO_OPA1CAL0_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL0 */
#define _DEVINFO_OPA1CAL0_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL0_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL0_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL0_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL0_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL0_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL0_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL0_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL0_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL0_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL0_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL0_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL0_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL0_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL1 */
#define _DEVINFO_OPA1CAL1_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL1 */
#define _DEVINFO_OPA1CAL1_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL1_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL1_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL1_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL1_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL1_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL1_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL1_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL1_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL1_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL1_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL1_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL1_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL1_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL2 */
#define _DEVINFO_OPA1CAL2_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL2 */
#define _DEVINFO_OPA1CAL2_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL2_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL2_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL2_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL2_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL2_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL2_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL2_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL2_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL2_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL2_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL2_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL2_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL2_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL3 */
#define _DEVINFO_OPA1CAL3_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL3 */
#define _DEVINFO_OPA1CAL3_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL3_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL3_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL3_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL3_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL3_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL3_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL3_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL3_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL3_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL3_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL3_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL3_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL3_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL0 */
#define _DEVINFO_OPA2CAL0_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL0 */
#define _DEVINFO_OPA2CAL0_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL0_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL0_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL0_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL0_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL0_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL0_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL0_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL0_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL0_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL0_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL0_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL0_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL0_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL1 */
#define _DEVINFO_OPA2CAL1_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL1 */
#define _DEVINFO_OPA2CAL1_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL1_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL1_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL1_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL1_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL1_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL1_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL1_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL1_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL1_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL1_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL1_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL1_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL1_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL2 */
#define _DEVINFO_OPA2CAL2_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL2 */
#define _DEVINFO_OPA2CAL2_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL2_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL2_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL2_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL2_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL2_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL2_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL2_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL2_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL2_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL2_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL2_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL2_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL2_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL3 */
#define _DEVINFO_OPA2CAL3_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL3 */
#define _DEVINFO_OPA2CAL3_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL3_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL3_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL3_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL3_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL3_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL3_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL3_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL3_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL3_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL3_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL3_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL3_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL3_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO CSENGAINCAL */
#define _DEVINFO_CSENGAINCAL_MASK                                0x000000FFUL /**< Mask for DEVINFO_CSENGAINCAL */
#define _DEVINFO_CSENGAINCAL_GAINCAL_SHIFT                       0            /**< Shift value for GAINCAL */
#define _DEVINFO_CSENGAINCAL_GAINCAL_MASK                        0xFFUL       /**< Bit mask for GAINCAL */

/* Bit fields for DEVINFO OPA0CAL4 */
#define _DEVINFO_OPA0CAL4_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL4 */
#define _DEVINFO_OPA0CAL4_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL4_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL4_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL4_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL4_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL4_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL4_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL4_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL4_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL4_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL4_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL4_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL4_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL4_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL5 */
#define _DEVINFO_OPA0CAL5_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL5 */
#define _DEVINFO_OPA0CAL5_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL5_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL5_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL5_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL5_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL5_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL5_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL5_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL5_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL5_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL5_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL5_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL5_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL5_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL6 */
#define _DEVINFO_OPA0CAL6_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL6 */
#define _DEVINFO_OPA0CAL6_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL6_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL6_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL6_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL6_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL6_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL6_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL6_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL6_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL6_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL6_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL6_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL6_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL6_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA0CAL7 */
#define _DEVINFO_OPA0CAL7_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA0CAL7 */
#define _DEVINFO_OPA0CAL7_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA0CAL7_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA0CAL7_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA0CAL7_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA0CAL7_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA0CAL7_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA0CAL7_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA0CAL7_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA0CAL7_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA0CAL7_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA0CAL7_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA0CAL7_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA0CAL7_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA0CAL7_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL4 */
#define _DEVINFO_OPA1CAL4_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL4 */
#define _DEVINFO_OPA1CAL4_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL4_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL4_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL4_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL4_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL4_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL4_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL4_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL4_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL4_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL4_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL4_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL4_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL4_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL5 */
#define _DEVINFO_OPA1CAL5_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL5 */
#define _DEVINFO_OPA1CAL5_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL5_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL5_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL5_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL5_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL5_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL5_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL5_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL5_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL5_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL5_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL5_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL5_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL5_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL6 */
#define _DEVINFO_OPA1CAL6_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL6 */
#define _DEVINFO_OPA1CAL6_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL6_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL6_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL6_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL6_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL6_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL6_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL6_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL6_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL6_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL6_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL6_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL6_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL6_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA1CAL7 */
#define _DEVINFO_OPA1CAL7_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA1CAL7 */
#define _DEVINFO_OPA1CAL7_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA1CAL7_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA1CAL7_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA1CAL7_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA1CAL7_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA1CAL7_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA1CAL7_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA1CAL7_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA1CAL7_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA1CAL7_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA1CAL7_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA1CAL7_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA1CAL7_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA1CAL7_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL4 */
#define _DEVINFO_OPA2CAL4_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL4 */
#define _DEVINFO_OPA2CAL4_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL4_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL4_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL4_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL4_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL4_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL4_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL4_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL4_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL4_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL4_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL4_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL4_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL4_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL5 */
#define _DEVINFO_OPA2CAL5_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL5 */
#define _DEVINFO_OPA2CAL5_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL5_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL5_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL5_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL5_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL5_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL5_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL5_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL5_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL5_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL5_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL5_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL5_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL5_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL6 */
#define _DEVINFO_OPA2CAL6_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL6 */
#define _DEVINFO_OPA2CAL6_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL6_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL6_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL6_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL6_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL6_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL6_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL6_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL6_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL6_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL6_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL6_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL6_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL6_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */

/* Bit fields for DEVINFO OPA2CAL7 */
#define _DEVINFO_OPA2CAL7_MASK                                   0x7DF6EDEFUL /**< Mask for DEVINFO_OPA2CAL7 */
#define _DEVINFO_OPA2CAL7_CM1_SHIFT                              0            /**< Shift value for CM1 */
#define _DEVINFO_OPA2CAL7_CM1_MASK                               0xFUL        /**< Bit mask for CM1 */
#define _DEVINFO_OPA2CAL7_CM2_SHIFT                              5            /**< Shift value for CM2 */
#define _DEVINFO_OPA2CAL7_CM2_MASK                               0x1E0UL      /**< Bit mask for CM2 */
#define _DEVINFO_OPA2CAL7_CM3_SHIFT                              10           /**< Shift value for CM3 */
#define _DEVINFO_OPA2CAL7_CM3_MASK                               0xC00UL      /**< Bit mask for CM3 */
#define _DEVINFO_OPA2CAL7_GM_SHIFT                               13           /**< Shift value for GM */
#define _DEVINFO_OPA2CAL7_GM_MASK                                0xE000UL     /**< Bit mask for GM */
#define _DEVINFO_OPA2CAL7_GM3_SHIFT                              17           /**< Shift value for GM3 */
#define _DEVINFO_OPA2CAL7_GM3_MASK                               0x60000UL    /**< Bit mask for GM3 */
#define _DEVINFO_OPA2CAL7_OFFSETP_SHIFT                          20           /**< Shift value for OFFSETP */
#define _DEVINFO_OPA2CAL7_OFFSETP_MASK                           0x1F00000UL  /**< Bit mask for OFFSETP */
#define _DEVINFO_OPA2CAL7_OFFSETN_SHIFT                          26           /**< Shift value for OFFSETN */
#define _DEVINFO_OPA2CAL7_OFFSETN_MASK                           0x7C000000UL /**< Bit mask for OFFSETN */


/**
  \brief  Structure type to access the Data Watchpoint and Trace Register (DWT).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
  __IOM uint32_t CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
  __IOM uint32_t CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
  __IOM uint32_t EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  __IOM uint32_t SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  __IOM uint32_t LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  __IOM uint32_t FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __IM  uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  __IOM uint32_t COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
  __IOM uint32_t MASK0;                  /*!< Offset: 0x024 (R/W)  Mask Register 0 */
  __IOM uint32_t FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
        uint32_t RESERVED0[1U];
  __IOM uint32_t COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
  __IOM uint32_t MASK1;                  /*!< Offset: 0x034 (R/W)  Mask Register 1 */
  __IOM uint32_t FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
        uint32_t RESERVED1[1U];
  __IOM uint32_t COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
  __IOM uint32_t MASK2;                  /*!< Offset: 0x044 (R/W)  Mask Register 2 */
  __IOM uint32_t FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
        uint32_t RESERVED2[1U];
  __IOM uint32_t COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
  __IOM uint32_t MASK3;                  /*!< Offset: 0x054 (R/W)  Mask Register 3 */
  __IOM uint32_t FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
} DWT_Type;

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */
/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IOM uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IOM uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[24U];
  __IOM uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IOM uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IOM uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IOM uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __OM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
		uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos          24U                                            /*!< SCB CPUID: IMPLEMENTER Position */
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)          /*!< SCB CPUID: IMPLEMENTER Mask */

#define SCB_CPUID_VARIANT_Pos              20U                                            /*!< SCB CPUID: VARIANT Position */
#define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)               /*!< SCB CPUID: VARIANT Mask */

#define SCB_CPUID_ARCHITECTURE_Pos         16U                                            /*!< SCB CPUID: ARCHITECTURE Position */
#define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)          /*!< SCB CPUID: ARCHITECTURE Mask */

#define SCB_CPUID_PARTNO_Pos                4U                                            /*!< SCB CPUID: PARTNO Position */
#define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)              /*!< SCB CPUID: PARTNO Mask */

#define SCB_CPUID_REVISION_Pos              0U                                            /*!< SCB CPUID: REVISION Position */
#define SCB_CPUID_REVISION_Msk             (0xFUL /*<< SCB_CPUID_REVISION_Pos*/)          /*!< SCB CPUID: REVISION Mask */

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_Pos            31U                                            /*!< SCB ICSR: NMIPENDSET Position */
#define SCB_ICSR_NMIPENDSET_Msk            (1UL << SCB_ICSR_NMIPENDSET_Pos)               /*!< SCB ICSR: NMIPENDSET Mask */

#define SCB_ICSR_PENDSVSET_Pos             28U                                            /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR: PENDSVSET Mask */

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            /*!< SCB ICSR: PENDSVCLR Position */
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR: PENDSVCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR: PENDSTSET Mask */

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            /*!< SCB ICSR: ISRPREEMPT Position */
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR: ISRPREEMPT Mask */

#define SCB_ICSR_ISRPENDING_Pos            22U                                            /*!< SCB ICSR: ISRPENDING Position */
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR: ISRPENDING Mask */

#define SCB_ICSR_VECTPENDING_Pos           12U                                            /*!< SCB ICSR: VECTPENDING Position */
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR: VECTPENDING Mask */

#define SCB_ICSR_RETTOBASE_Pos             11U                                            /*!< SCB ICSR: RETTOBASE Position */
#define SCB_ICSR_RETTOBASE_Msk             (1UL << SCB_ICSR_RETTOBASE_Pos)                /*!< SCB ICSR: RETTOBASE Mask */

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            /*!< SCB ICSR: VECTACTIVE Position */
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL /*<< SCB_ICSR_VECTACTIVE_Pos*/)       /*!< SCB ICSR: VECTACTIVE Mask */

/* SCB Vector Table Offset Register Definitions */
#define SCB_VTOR_TBLOFF_Pos                 7U                                            /*!< SCB VTOR: TBLOFF Position */
#define SCB_VTOR_TBLOFF_Msk                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)           /*!< SCB VTOR: TBLOFF Mask */

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            /*!< SCB AIRCR: VECTKEYSTAT Position */
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            /*!< SCB AIRCR: ENDIANESS Position */
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR: ENDIANESS Mask */

#define SCB_AIRCR_PRIGROUP_Pos              8U                                            /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR: SYSRESETREQ Mask */

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            /*!< SCB AIRCR: VECTCLRACTIVE Position */
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR: VECTCLRACTIVE Mask */

#define SCB_AIRCR_VECTRESET_Pos             0U                                            /*!< SCB AIRCR: VECTRESET Position */
#define SCB_AIRCR_VECTRESET_Msk            (1UL /*<< SCB_AIRCR_VECTRESET_Pos*/)           /*!< SCB AIRCR: VECTRESET Mask */

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos               4U                                            /*!< SCB SCR: SEVONPEND Position */
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR: SEVONPEND Mask */

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR: SLEEPDEEP Mask */

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            /*!< SCB SCR: SLEEPONEXIT Position */
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR: SLEEPONEXIT Mask */

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_STKALIGN_Pos                9U                                            /*!< SCB CCR: STKALIGN Position */
#define SCB_CCR_STKALIGN_Msk               (1UL << SCB_CCR_STKALIGN_Pos)                  /*!< SCB CCR: STKALIGN Mask */

#define SCB_CCR_BFHFNMIGN_Pos               8U                                            /*!< SCB CCR: BFHFNMIGN Position */
#define SCB_CCR_BFHFNMIGN_Msk              (1UL << SCB_CCR_BFHFNMIGN_Pos)                 /*!< SCB CCR: BFHFNMIGN Mask */

#define SCB_CCR_DIV_0_TRP_Pos               4U                                            /*!< SCB CCR: DIV_0_TRP Position */
#define SCB_CCR_DIV_0_TRP_Msk              (1UL << SCB_CCR_DIV_0_TRP_Pos)                 /*!< SCB CCR: DIV_0_TRP Mask */

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            /*!< SCB CCR: UNALIGN_TRP Position */
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR: UNALIGN_TRP Mask */

#define SCB_CCR_USERSETMPEND_Pos            1U                                            /*!< SCB CCR: USERSETMPEND Position */
#define SCB_CCR_USERSETMPEND_Msk           (1UL << SCB_CCR_USERSETMPEND_Pos)              /*!< SCB CCR: USERSETMPEND Mask */

#define SCB_CCR_NONBASETHRDENA_Pos          0U                                            /*!< SCB CCR: NONBASETHRDENA Position */
#define SCB_CCR_NONBASETHRDENA_Msk         (1UL /*<< SCB_CCR_NONBASETHRDENA_Pos*/)        /*!< SCB CCR: NONBASETHRDENA Mask */

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_USGFAULTENA_Pos          18U                                            /*!< SCB SHCSR: USGFAULTENA Position */
#define SCB_SHCSR_USGFAULTENA_Msk          (1UL << SCB_SHCSR_USGFAULTENA_Pos)             /*!< SCB SHCSR: USGFAULTENA Mask */

#define SCB_SHCSR_BUSFAULTENA_Pos          17U                                            /*!< SCB SHCSR: BUSFAULTENA Position */
#define SCB_SHCSR_BUSFAULTENA_Msk          (1UL << SCB_SHCSR_BUSFAULTENA_Pos)             /*!< SCB SHCSR: BUSFAULTENA Mask */

#define SCB_SHCSR_MEMFAULTENA_Pos          16U                                            /*!< SCB SHCSR: MEMFAULTENA Position */
#define SCB_SHCSR_MEMFAULTENA_Msk          (1UL << SCB_SHCSR_MEMFAULTENA_Pos)             /*!< SCB SHCSR: MEMFAULTENA Mask */

#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            /*!< SCB SHCSR: SVCALLPENDED Position */
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR: SVCALLPENDED Mask */

#define SCB_SHCSR_BUSFAULTPENDED_Pos       14U                                            /*!< SCB SHCSR: BUSFAULTPENDED Position */
#define SCB_SHCSR_BUSFAULTPENDED_Msk       (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos)          /*!< SCB SHCSR: BUSFAULTPENDED Mask */

#define SCB_SHCSR_MEMFAULTPENDED_Pos       13U                                            /*!< SCB SHCSR: MEMFAULTPENDED Position */
#define SCB_SHCSR_MEMFAULTPENDED_Msk       (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos)          /*!< SCB SHCSR: MEMFAULTPENDED Mask */

#define SCB_SHCSR_USGFAULTPENDED_Pos       12U                                            /*!< SCB SHCSR: USGFAULTPENDED Position */
#define SCB_SHCSR_USGFAULTPENDED_Msk       (1UL << SCB_SHCSR_USGFAULTPENDED_Pos)          /*!< SCB SHCSR: USGFAULTPENDED Mask */

#define SCB_SHCSR_SYSTICKACT_Pos           11U                                            /*!< SCB SHCSR: SYSTICKACT Position */
#define SCB_SHCSR_SYSTICKACT_Msk           (1UL << SCB_SHCSR_SYSTICKACT_Pos)              /*!< SCB SHCSR: SYSTICKACT Mask */

#define SCB_SHCSR_PENDSVACT_Pos            10U                                            /*!< SCB SHCSR: PENDSVACT Position */
#define SCB_SHCSR_PENDSVACT_Msk            (1UL << SCB_SHCSR_PENDSVACT_Pos)               /*!< SCB SHCSR: PENDSVACT Mask */

#define SCB_SHCSR_MONITORACT_Pos            8U                                            /*!< SCB SHCSR: MONITORACT Position */
#define SCB_SHCSR_MONITORACT_Msk           (1UL << SCB_SHCSR_MONITORACT_Pos)              /*!< SCB SHCSR: MONITORACT Mask */

#define SCB_SHCSR_SVCALLACT_Pos             7U                                            /*!< SCB SHCSR: SVCALLACT Position */
#define SCB_SHCSR_SVCALLACT_Msk            (1UL << SCB_SHCSR_SVCALLACT_Pos)               /*!< SCB SHCSR: SVCALLACT Mask */

#define SCB_SHCSR_USGFAULTACT_Pos           3U                                            /*!< SCB SHCSR: USGFAULTACT Position */
#define SCB_SHCSR_USGFAULTACT_Msk          (1UL << SCB_SHCSR_USGFAULTACT_Pos)             /*!< SCB SHCSR: USGFAULTACT Mask */

#define SCB_SHCSR_BUSFAULTACT_Pos           1U                                            /*!< SCB SHCSR: BUSFAULTACT Position */
#define SCB_SHCSR_BUSFAULTACT_Msk          (1UL << SCB_SHCSR_BUSFAULTACT_Pos)             /*!< SCB SHCSR: BUSFAULTACT Mask */

#define SCB_SHCSR_MEMFAULTACT_Pos           0U                                            /*!< SCB SHCSR: MEMFAULTACT Position */
#define SCB_SHCSR_MEMFAULTACT_Msk          (1UL /*<< SCB_SHCSR_MEMFAULTACT_Pos*/)         /*!< SCB SHCSR: MEMFAULTACT Mask */

/* SCB Configurable Fault Status Register Definitions */
#define SCB_CFSR_USGFAULTSR_Pos            16U                                            /*!< SCB CFSR: Usage Fault Status Register Position */
#define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)          /*!< SCB CFSR: Usage Fault Status Register Mask */

#define SCB_CFSR_BUSFAULTSR_Pos             8U                                            /*!< SCB CFSR: Bus Fault Status Register Position */
#define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)            /*!< SCB CFSR: Bus Fault Status Register Mask */

#define SCB_CFSR_MEMFAULTSR_Pos             0U                                            /*!< SCB CFSR: Memory Manage Fault Status Register Position */
#define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL /*<< SCB_CFSR_MEMFAULTSR_Pos*/)        /*!< SCB CFSR: Memory Manage Fault Status Register Mask */

/* MemManage Fault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_MMARVALID_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 7U)               /*!< SCB CFSR (MMFSR): MMARVALID Position */
#define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)                /*!< SCB CFSR (MMFSR): MMARVALID Mask */

#define SCB_CFSR_MLSPERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 5U)               /*!< SCB CFSR (MMFSR): MLSPERR Position */
#define SCB_CFSR_MLSPERR_Msk               (1UL << SCB_CFSR_MLSPERR_Pos)                  /*!< SCB CFSR (MMFSR): MLSPERR Mask */

#define SCB_CFSR_MSTKERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 4U)               /*!< SCB CFSR (MMFSR): MSTKERR Position */
#define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)                  /*!< SCB CFSR (MMFSR): MSTKERR Mask */

#define SCB_CFSR_MUNSTKERR_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 3U)               /*!< SCB CFSR (MMFSR): MUNSTKERR Position */
#define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)                /*!< SCB CFSR (MMFSR): MUNSTKERR Mask */

#define SCB_CFSR_DACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 1U)               /*!< SCB CFSR (MMFSR): DACCVIOL Position */
#define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)                 /*!< SCB CFSR (MMFSR): DACCVIOL Mask */

#define SCB_CFSR_IACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 0U)               /*!< SCB CFSR (MMFSR): IACCVIOL Position */
#define SCB_CFSR_IACCVIOL_Msk              (1UL /*<< SCB_CFSR_IACCVIOL_Pos*/)             /*!< SCB CFSR (MMFSR): IACCVIOL Mask */

/* BusFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)                  /*!< SCB CFSR (BFSR): BFARVALID Position */
#define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)                 /*!< SCB CFSR (BFSR): BFARVALID Mask */

#define SCB_CFSR_LSPERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 5U)                  /*!< SCB CFSR (BFSR): LSPERR Position */
#define SCB_CFSR_LSPERR_Msk               (1UL << SCB_CFSR_LSPERR_Pos)                    /*!< SCB CFSR (BFSR): LSPERR Mask */

#define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)                  /*!< SCB CFSR (BFSR): STKERR Position */
#define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)                    /*!< SCB CFSR (BFSR): STKERR Mask */

#define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)                  /*!< SCB CFSR (BFSR): UNSTKERR Position */
#define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)                  /*!< SCB CFSR (BFSR): UNSTKERR Mask */

#define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)                  /*!< SCB CFSR (BFSR): IMPRECISERR Position */
#define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)               /*!< SCB CFSR (BFSR): IMPRECISERR Mask */

#define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)                  /*!< SCB CFSR (BFSR): PRECISERR Position */
#define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)                 /*!< SCB CFSR (BFSR): PRECISERR Mask */

#define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)                  /*!< SCB CFSR (BFSR): IBUSERR Position */
#define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)                   /*!< SCB CFSR (BFSR): IBUSERR Mask */

/* UsageFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)                  /*!< SCB CFSR (UFSR): DIVBYZERO Position */
#define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)                 /*!< SCB CFSR (UFSR): DIVBYZERO Mask */

#define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)                  /*!< SCB CFSR (UFSR): UNALIGNED Position */
#define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)                 /*!< SCB CFSR (UFSR): UNALIGNED Mask */

#define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)                  /*!< SCB CFSR (UFSR): NOCP Position */
#define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)                      /*!< SCB CFSR (UFSR): NOCP Mask */

#define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)                  /*!< SCB CFSR (UFSR): INVPC Position */
#define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)                     /*!< SCB CFSR (UFSR): INVPC Mask */

#define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)                  /*!< SCB CFSR (UFSR): INVSTATE Position */
#define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)                  /*!< SCB CFSR (UFSR): INVSTATE Mask */

#define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)                  /*!< SCB CFSR (UFSR): UNDEFINSTR Position */
#define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)                /*!< SCB CFSR (UFSR): UNDEFINSTR Mask */

/* SCB Hard Fault Status Register Definitions */
#define SCB_HFSR_DEBUGEVT_Pos              31U                                            /*!< SCB HFSR: DEBUGEVT Position */
#define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)                 /*!< SCB HFSR: DEBUGEVT Mask */

#define SCB_HFSR_FORCED_Pos                30U                                            /*!< SCB HFSR: FORCED Position */
#define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)                   /*!< SCB HFSR: FORCED Mask */

#define SCB_HFSR_VECTTBL_Pos                1U                                            /*!< SCB HFSR: VECTTBL Position */
#define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)                  /*!< SCB HFSR: VECTTBL Mask */

/* SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_EXTERNAL_Pos               4U                                            /*!< SCB DFSR: EXTERNAL Position */
#define SCB_DFSR_EXTERNAL_Msk              (1UL << SCB_DFSR_EXTERNAL_Pos)                 /*!< SCB DFSR: EXTERNAL Mask */

#define SCB_DFSR_VCATCH_Pos                 3U                                            /*!< SCB DFSR: VCATCH Position */
#define SCB_DFSR_VCATCH_Msk                (1UL << SCB_DFSR_VCATCH_Pos)                   /*!< SCB DFSR: VCATCH Mask */

#define SCB_DFSR_DWTTRAP_Pos                2U                                            /*!< SCB DFSR: DWTTRAP Position */
#define SCB_DFSR_DWTTRAP_Msk               (1UL << SCB_DFSR_DWTTRAP_Pos)                  /*!< SCB DFSR: DWTTRAP Mask */

#define SCB_DFSR_BKPT_Pos                   1U                                            /*!< SCB DFSR: BKPT Position */
#define SCB_DFSR_BKPT_Msk                  (1UL << SCB_DFSR_BKPT_Pos)                     /*!< SCB DFSR: BKPT Mask */

#define SCB_DFSR_HALTED_Pos                 0U                                            /*!< SCB DFSR: HALTED Position */
#define SCB_DFSR_HALTED_Msk                (1UL /*<< SCB_DFSR_HALTED_Pos*/)               /*!< SCB DFSR: HALTED Mask */

/**
  \brief  Structure type to access the Core Debug Register (CoreDebug).
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} CoreDebug_Type;

/* Debug Halting Control and Status Register Definitions */
#define CoreDebug_DHCSR_DBGKEY_Pos         16U                                            /*!< CoreDebug DHCSR: DBGKEY Position */
#define CoreDebug_DHCSR_DBGKEY_Msk         (0xFFFFUL << CoreDebug_DHCSR_DBGKEY_Pos)       /*!< CoreDebug DHCSR: DBGKEY Mask */

#define CoreDebug_DHCSR_S_RESET_ST_Pos     25U                                            /*!< CoreDebug DHCSR: S_RESET_ST Position */
#define CoreDebug_DHCSR_S_RESET_ST_Msk     (1UL << CoreDebug_DHCSR_S_RESET_ST_Pos)        /*!< CoreDebug DHCSR: S_RESET_ST Mask */

#define CoreDebug_DHCSR_S_RETIRE_ST_Pos    24U                                            /*!< CoreDebug DHCSR: S_RETIRE_ST Position */
#define CoreDebug_DHCSR_S_RETIRE_ST_Msk    (1UL << CoreDebug_DHCSR_S_RETIRE_ST_Pos)       /*!< CoreDebug DHCSR: S_RETIRE_ST Mask */

#define CoreDebug_DHCSR_S_LOCKUP_Pos       19U                                            /*!< CoreDebug DHCSR: S_LOCKUP Position */
#define CoreDebug_DHCSR_S_LOCKUP_Msk       (1UL << CoreDebug_DHCSR_S_LOCKUP_Pos)          /*!< CoreDebug DHCSR: S_LOCKUP Mask */

#define CoreDebug_DHCSR_S_SLEEP_Pos        18U                                            /*!< CoreDebug DHCSR: S_SLEEP Position */
#define CoreDebug_DHCSR_S_SLEEP_Msk        (1UL << CoreDebug_DHCSR_S_SLEEP_Pos)           /*!< CoreDebug DHCSR: S_SLEEP Mask */

#define CoreDebug_DHCSR_S_HALT_Pos         17U                                            /*!< CoreDebug DHCSR: S_HALT Position */
#define CoreDebug_DHCSR_S_HALT_Msk         (1UL << CoreDebug_DHCSR_S_HALT_Pos)            /*!< CoreDebug DHCSR: S_HALT Mask */

#define CoreDebug_DHCSR_S_REGRDY_Pos       16U                                            /*!< CoreDebug DHCSR: S_REGRDY Position */
#define CoreDebug_DHCSR_S_REGRDY_Msk       (1UL << CoreDebug_DHCSR_S_REGRDY_Pos)          /*!< CoreDebug DHCSR: S_REGRDY Mask */

#define CoreDebug_DHCSR_C_SNAPSTALL_Pos     5U                                            /*!< CoreDebug DHCSR: C_SNAPSTALL Position */
#define CoreDebug_DHCSR_C_SNAPSTALL_Msk    (1UL << CoreDebug_DHCSR_C_SNAPSTALL_Pos)       /*!< CoreDebug DHCSR: C_SNAPSTALL Mask */

#define CoreDebug_DHCSR_C_MASKINTS_Pos      3U                                            /*!< CoreDebug DHCSR: C_MASKINTS Position */
#define CoreDebug_DHCSR_C_MASKINTS_Msk     (1UL << CoreDebug_DHCSR_C_MASKINTS_Pos)        /*!< CoreDebug DHCSR: C_MASKINTS Mask */

#define CoreDebug_DHCSR_C_STEP_Pos          2U                                            /*!< CoreDebug DHCSR: C_STEP Position */
#define CoreDebug_DHCSR_C_STEP_Msk         (1UL << CoreDebug_DHCSR_C_STEP_Pos)            /*!< CoreDebug DHCSR: C_STEP Mask */

#define CoreDebug_DHCSR_C_HALT_Pos          1U                                            /*!< CoreDebug DHCSR: C_HALT Position */
#define CoreDebug_DHCSR_C_HALT_Msk         (1UL << CoreDebug_DHCSR_C_HALT_Pos)            /*!< CoreDebug DHCSR: C_HALT Mask */

#define CoreDebug_DHCSR_C_DEBUGEN_Pos       0U                                            /*!< CoreDebug DHCSR: C_DEBUGEN Position */
#define CoreDebug_DHCSR_C_DEBUGEN_Msk      (1UL /*<< CoreDebug_DHCSR_C_DEBUGEN_Pos*/)     /*!< CoreDebug DHCSR: C_DEBUGEN Mask */

/* Debug Core Register Selector Register Definitions */
#define CoreDebug_DCRSR_REGWnR_Pos         16U                                            /*!< CoreDebug DCRSR: REGWnR Position */
#define CoreDebug_DCRSR_REGWnR_Msk         (1UL << CoreDebug_DCRSR_REGWnR_Pos)            /*!< CoreDebug DCRSR: REGWnR Mask */

#define CoreDebug_DCRSR_REGSEL_Pos          0U                                            /*!< CoreDebug DCRSR: REGSEL Position */
#define CoreDebug_DCRSR_REGSEL_Msk         (0x1FUL /*<< CoreDebug_DCRSR_REGSEL_Pos*/)     /*!< CoreDebug DCRSR: REGSEL Mask */

/* Debug Exception and Monitor Control Register Definitions */
#define CoreDebug_DEMCR_TRCENA_Pos         24U                                            /*!< CoreDebug DEMCR: TRCENA Position */
#define CoreDebug_DEMCR_TRCENA_Msk         (1UL << CoreDebug_DEMCR_TRCENA_Pos)            /*!< CoreDebug DEMCR: TRCENA Mask */

#define CoreDebug_DEMCR_MON_REQ_Pos        19U                                            /*!< CoreDebug DEMCR: MON_REQ Position */
#define CoreDebug_DEMCR_MON_REQ_Msk        (1UL << CoreDebug_DEMCR_MON_REQ_Pos)           /*!< CoreDebug DEMCR: MON_REQ Mask */

#define CoreDebug_DEMCR_MON_STEP_Pos       18U                                            /*!< CoreDebug DEMCR: MON_STEP Position */
#define CoreDebug_DEMCR_MON_STEP_Msk       (1UL << CoreDebug_DEMCR_MON_STEP_Pos)          /*!< CoreDebug DEMCR: MON_STEP Mask */

#define CoreDebug_DEMCR_MON_PEND_Pos       17U                                            /*!< CoreDebug DEMCR: MON_PEND Position */
#define CoreDebug_DEMCR_MON_PEND_Msk       (1UL << CoreDebug_DEMCR_MON_PEND_Pos)          /*!< CoreDebug DEMCR: MON_PEND Mask */

#define CoreDebug_DEMCR_MON_EN_Pos         16U                                            /*!< CoreDebug DEMCR: MON_EN Position */
#define CoreDebug_DEMCR_MON_EN_Msk         (1UL << CoreDebug_DEMCR_MON_EN_Pos)            /*!< CoreDebug DEMCR: MON_EN Mask */

#define CoreDebug_DEMCR_VC_HARDERR_Pos     10U                                            /*!< CoreDebug DEMCR: VC_HARDERR Position */
#define CoreDebug_DEMCR_VC_HARDERR_Msk     (1UL << CoreDebug_DEMCR_VC_HARDERR_Pos)        /*!< CoreDebug DEMCR: VC_HARDERR Mask */

#define CoreDebug_DEMCR_VC_INTERR_Pos       9U                                            /*!< CoreDebug DEMCR: VC_INTERR Position */
#define CoreDebug_DEMCR_VC_INTERR_Msk      (1UL << CoreDebug_DEMCR_VC_INTERR_Pos)         /*!< CoreDebug DEMCR: VC_INTERR Mask */

#define CoreDebug_DEMCR_VC_BUSERR_Pos       8U                                            /*!< CoreDebug DEMCR: VC_BUSERR Position */
#define CoreDebug_DEMCR_VC_BUSERR_Msk      (1UL << CoreDebug_DEMCR_VC_BUSERR_Pos)         /*!< CoreDebug DEMCR: VC_BUSERR Mask */

#define CoreDebug_DEMCR_VC_STATERR_Pos      7U                                            /*!< CoreDebug DEMCR: VC_STATERR Position */
#define CoreDebug_DEMCR_VC_STATERR_Msk     (1UL << CoreDebug_DEMCR_VC_STATERR_Pos)        /*!< CoreDebug DEMCR: VC_STATERR Mask */

#define CoreDebug_DEMCR_VC_CHKERR_Pos       6U                                            /*!< CoreDebug DEMCR: VC_CHKERR Position */
#define CoreDebug_DEMCR_VC_CHKERR_Msk      (1UL << CoreDebug_DEMCR_VC_CHKERR_Pos)         /*!< CoreDebug DEMCR: VC_CHKERR Mask */

#define CoreDebug_DEMCR_VC_NOCPERR_Pos      5U                                            /*!< CoreDebug DEMCR: VC_NOCPERR Position */
#define CoreDebug_DEMCR_VC_NOCPERR_Msk     (1UL << CoreDebug_DEMCR_VC_NOCPERR_Pos)        /*!< CoreDebug DEMCR: VC_NOCPERR Mask */

#define CoreDebug_DEMCR_VC_MMERR_Pos        4U                                            /*!< CoreDebug DEMCR: VC_MMERR Position */
#define CoreDebug_DEMCR_VC_MMERR_Msk       (1UL << CoreDebug_DEMCR_VC_MMERR_Pos)          /*!< CoreDebug DEMCR: VC_MMERR Mask */

#define CoreDebug_DEMCR_VC_CORERESET_Pos    0U                                            /*!< CoreDebug DEMCR: VC_CORERESET Position */
#define CoreDebug_DEMCR_VC_CORERESET_Msk   (1UL /*<< CoreDebug_DEMCR_VC_CORERESET_Pos*/)  /*!< CoreDebug DEMCR: VC_CORERESET Mask */

/*@} end of group CMSIS_CoreDebug */


// WDOG 
typedef struct {
  __IOM uint32_t PRSCTRL; /**< PRS Control Register  */
} WDOG_PCH_TypeDef;

/** WDOG Register Declaration */
typedef struct {
  __IOM uint32_t   CTRL;         /**< Control Register  */
  __IOM uint32_t   CMD;          /**< Command Register  */

  __IM uint32_t    SYNCBUSY;     /**< Synchronization Busy Register  */

  WDOG_PCH_TypeDef PCH[2];       /**< PCH */

  uint32_t         RESERVED0[2]; /**< Reserved for future use **/
  __IM uint32_t    IF;           /**< Watchdog Interrupt Flags  */
  __IOM uint32_t   IFS;          /**< Interrupt Flag Set Register  */
  __IOM uint32_t   IFC;          /**< Interrupt Flag Clear Register  */
  __IOM uint32_t   IEN;          /**< Interrupt Enable Register  */
} WDOG_TypeDef;      


/* Bit fields for WDOG CTRL */
#define _WDOG_CTRL_RESETVALUE                     0x00000F00UL                          /**< Default value for WDOG_CTRL */
#define _WDOG_CTRL_MASK                           0xC7033F7FUL                          /**< Mask for WDOG_CTRL */
#define WDOG_CTRL_EN                              (0x1UL << 0)                          /**< Watchdog Timer Enable */
#define _WDOG_CTRL_EN_SHIFT                       0                                     /**< Shift value for WDOG_EN */
#define _WDOG_CTRL_EN_MASK                        0x1UL                                 /**< Bit mask for WDOG_EN */
#define _WDOG_CTRL_EN_DEFAULT                     0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EN_DEFAULT                      (_WDOG_CTRL_EN_DEFAULT << 0)          /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_DEBUGRUN                        (0x1UL << 1)                          /**< Debug Mode Run Enable */
#define _WDOG_CTRL_DEBUGRUN_SHIFT                 1                                     /**< Shift value for WDOG_DEBUGRUN */
#define _WDOG_CTRL_DEBUGRUN_MASK                  0x2UL                                 /**< Bit mask for WDOG_DEBUGRUN */
#define _WDOG_CTRL_DEBUGRUN_DEFAULT               0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_DEBUGRUN_DEFAULT                (_WDOG_CTRL_DEBUGRUN_DEFAULT << 1)    /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM2RUN                          (0x1UL << 2)                          /**< Energy Mode 2 Run Enable */
#define _WDOG_CTRL_EM2RUN_SHIFT                   2                                     /**< Shift value for WDOG_EM2RUN */
#define _WDOG_CTRL_EM2RUN_MASK                    0x4UL                                 /**< Bit mask for WDOG_EM2RUN */
#define _WDOG_CTRL_EM2RUN_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM2RUN_DEFAULT                  (_WDOG_CTRL_EM2RUN_DEFAULT << 2)      /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM3RUN                          (0x1UL << 3)                          /**< Energy Mode 3 Run Enable */
#define _WDOG_CTRL_EM3RUN_SHIFT                   3                                     /**< Shift value for WDOG_EM3RUN */
#define _WDOG_CTRL_EM3RUN_MASK                    0x8UL                                 /**< Bit mask for WDOG_EM3RUN */
#define _WDOG_CTRL_EM3RUN_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM3RUN_DEFAULT                  (_WDOG_CTRL_EM3RUN_DEFAULT << 3)      /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_LOCK                            (0x1UL << 4)                          /**< Configuration Lock */
#define _WDOG_CTRL_LOCK_SHIFT                     4                                     /**< Shift value for WDOG_LOCK */
#define _WDOG_CTRL_LOCK_MASK                      0x10UL                                /**< Bit mask for WDOG_LOCK */
#define _WDOG_CTRL_LOCK_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_LOCK_DEFAULT                    (_WDOG_CTRL_LOCK_DEFAULT << 4)        /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM4BLOCK                        (0x1UL << 5)                          /**< Energy Mode 4 Block */
#define _WDOG_CTRL_EM4BLOCK_SHIFT                 5                                     /**< Shift value for WDOG_EM4BLOCK */
#define _WDOG_CTRL_EM4BLOCK_MASK                  0x20UL                                /**< Bit mask for WDOG_EM4BLOCK */
#define _WDOG_CTRL_EM4BLOCK_DEFAULT               0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_EM4BLOCK_DEFAULT                (_WDOG_CTRL_EM4BLOCK_DEFAULT << 5)    /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_SWOSCBLOCK                      (0x1UL << 6)                          /**< Software Oscillator Disable Block */
#define _WDOG_CTRL_SWOSCBLOCK_SHIFT               6                                     /**< Shift value for WDOG_SWOSCBLOCK */
#define _WDOG_CTRL_SWOSCBLOCK_MASK                0x40UL                                /**< Bit mask for WDOG_SWOSCBLOCK */
#define _WDOG_CTRL_SWOSCBLOCK_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_SWOSCBLOCK_DEFAULT              (_WDOG_CTRL_SWOSCBLOCK_DEFAULT << 6)  /**< Shifted mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_PERSEL_SHIFT                   8                                     /**< Shift value for WDOG_PERSEL */
#define _WDOG_CTRL_PERSEL_MASK                    0xF00UL                               /**< Bit mask for WDOG_PERSEL */
#define _WDOG_CTRL_PERSEL_DEFAULT                 0x0000000FUL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_PERSEL_DEFAULT                  (_WDOG_CTRL_PERSEL_DEFAULT << 8)      /**< Shifted mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_CLKSEL_SHIFT                   12                                    /**< Shift value for WDOG_CLKSEL */
#define _WDOG_CTRL_CLKSEL_MASK                    0x3000UL                              /**< Bit mask for WDOG_CLKSEL */
#define _WDOG_CTRL_CLKSEL_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_CLKSEL_ULFRCO                  0x00000000UL                          /**< Mode ULFRCO for WDOG_CTRL */
#define _WDOG_CTRL_CLKSEL_LFRCO                   0x00000001UL                          /**< Mode LFRCO for WDOG_CTRL */
#define _WDOG_CTRL_CLKSEL_LFXO                    0x00000002UL                          /**< Mode LFXO for WDOG_CTRL */
#define _WDOG_CTRL_CLKSEL_HFCORECLK               0x00000003UL                          /**< Mode HFCORECLK for WDOG_CTRL */
#define WDOG_CTRL_CLKSEL_DEFAULT                  (_WDOG_CTRL_CLKSEL_DEFAULT << 12)     /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_CLKSEL_ULFRCO                   (_WDOG_CTRL_CLKSEL_ULFRCO << 12)      /**< Shifted mode ULFRCO for WDOG_CTRL */
#define WDOG_CTRL_CLKSEL_LFRCO                    (_WDOG_CTRL_CLKSEL_LFRCO << 12)       /**< Shifted mode LFRCO for WDOG_CTRL */
#define WDOG_CTRL_CLKSEL_LFXO                     (_WDOG_CTRL_CLKSEL_LFXO << 12)        /**< Shifted mode LFXO for WDOG_CTRL */
#define WDOG_CTRL_CLKSEL_HFCORECLK                (_WDOG_CTRL_CLKSEL_HFCORECLK << 12)   /**< Shifted mode HFCORECLK for WDOG_CTRL */
#define _WDOG_CTRL_WARNSEL_SHIFT                  16                                    /**< Shift value for WDOG_WARNSEL */
#define _WDOG_CTRL_WARNSEL_MASK                   0x30000UL                             /**< Bit mask for WDOG_WARNSEL */
#define _WDOG_CTRL_WARNSEL_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_WARNSEL_DEFAULT                 (_WDOG_CTRL_WARNSEL_DEFAULT << 16)    /**< Shifted mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_WINSEL_SHIFT                   24                                    /**< Shift value for WDOG_WINSEL */
#define _WDOG_CTRL_WINSEL_MASK                    0x7000000UL                           /**< Bit mask for WDOG_WINSEL */
#define _WDOG_CTRL_WINSEL_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_WINSEL_DEFAULT                  (_WDOG_CTRL_WINSEL_DEFAULT << 24)     /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_CLRSRC                          (0x1UL << 30)                         /**< Watchdog Clear Source */
#define _WDOG_CTRL_CLRSRC_SHIFT                   30                                    /**< Shift value for WDOG_CLRSRC */
#define _WDOG_CTRL_CLRSRC_MASK                    0x40000000UL                          /**< Bit mask for WDOG_CLRSRC */
#define _WDOG_CTRL_CLRSRC_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_CLRSRC_SW                      0x00000000UL                          /**< Mode SW for WDOG_CTRL */
#define _WDOG_CTRL_CLRSRC_PCH0                    0x00000001UL                          /**< Mode PCH0 for WDOG_CTRL */
#define WDOG_CTRL_CLRSRC_DEFAULT                  (_WDOG_CTRL_CLRSRC_DEFAULT << 30)     /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_CLRSRC_SW                       (_WDOG_CTRL_CLRSRC_SW << 30)          /**< Shifted mode SW for WDOG_CTRL */
#define WDOG_CTRL_CLRSRC_PCH0                     (_WDOG_CTRL_CLRSRC_PCH0 << 30)        /**< Shifted mode PCH0 for WDOG_CTRL */
#define WDOG_CTRL_WDOGRSTDIS                      (0x1UL << 31)                         /**< Watchdog Reset Disable */
#define _WDOG_CTRL_WDOGRSTDIS_SHIFT               31                                    /**< Shift value for WDOG_WDOGRSTDIS */
#define _WDOG_CTRL_WDOGRSTDIS_MASK                0x80000000UL                          /**< Bit mask for WDOG_WDOGRSTDIS */
#define _WDOG_CTRL_WDOGRSTDIS_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for WDOG_CTRL */
#define _WDOG_CTRL_WDOGRSTDIS_EN                  0x00000000UL                          /**< Mode EN for WDOG_CTRL */
#define _WDOG_CTRL_WDOGRSTDIS_DIS                 0x00000001UL                          /**< Mode DIS for WDOG_CTRL */
#define WDOG_CTRL_WDOGRSTDIS_DEFAULT              (_WDOG_CTRL_WDOGRSTDIS_DEFAULT << 31) /**< Shifted mode DEFAULT for WDOG_CTRL */
#define WDOG_CTRL_WDOGRSTDIS_EN                   (_WDOG_CTRL_WDOGRSTDIS_EN << 31)      /**< Shifted mode EN for WDOG_CTRL */
#define WDOG_CTRL_WDOGRSTDIS_DIS                  (_WDOG_CTRL_WDOGRSTDIS_DIS << 31)     /**< Shifted mode DIS for WDOG_CTRL */

/* Bit fields for WDOG CMD */
#define _WDOG_CMD_RESETVALUE                      0x00000000UL                     /**< Default value for WDOG_CMD */
#define _WDOG_CMD_MASK                            0x00000001UL                     /**< Mask for WDOG_CMD */
#define WDOG_CMD_CLEAR                            (0x1UL << 0)                     /**< Watchdog Timer Clear */
#define _WDOG_CMD_CLEAR_SHIFT                     0                                /**< Shift value for WDOG_CLEAR */
#define _WDOG_CMD_CLEAR_MASK                      0x1UL                            /**< Bit mask for WDOG_CLEAR */
#define _WDOG_CMD_CLEAR_DEFAULT                   0x00000000UL                     /**< Mode DEFAULT for WDOG_CMD */
#define _WDOG_CMD_CLEAR_UNCHANGED                 0x00000000UL                     /**< Mode UNCHANGED for WDOG_CMD */
#define _WDOG_CMD_CLEAR_CLEARED                   0x00000001UL                     /**< Mode CLEARED for WDOG_CMD */
#define WDOG_CMD_CLEAR_DEFAULT                    (_WDOG_CMD_CLEAR_DEFAULT << 0)   /**< Shifted mode DEFAULT for WDOG_CMD */
#define WDOG_CMD_CLEAR_UNCHANGED                  (_WDOG_CMD_CLEAR_UNCHANGED << 0) /**< Shifted mode UNCHANGED for WDOG_CMD */
#define WDOG_CMD_CLEAR_CLEARED                    (_WDOG_CMD_CLEAR_CLEARED << 0)   /**< Shifted mode CLEARED for WDOG_CMD */

/* Bit fields for WDOG SYNCBUSY */
#define _WDOG_SYNCBUSY_RESETVALUE                 0x00000000UL                               /**< Default value for WDOG_SYNCBUSY */
#define _WDOG_SYNCBUSY_MASK                       0x0000000FUL                               /**< Mask for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_CTRL                        (0x1UL << 0)                               /**< CTRL Register Busy */
#define _WDOG_SYNCBUSY_CTRL_SHIFT                 0                                          /**< Shift value for WDOG_CTRL */
#define _WDOG_SYNCBUSY_CTRL_MASK                  0x1UL                                      /**< Bit mask for WDOG_CTRL */
#define _WDOG_SYNCBUSY_CTRL_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_CTRL_DEFAULT                (_WDOG_SYNCBUSY_CTRL_DEFAULT << 0)         /**< Shifted mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_CMD                         (0x1UL << 1)                               /**< CMD Register Busy */
#define _WDOG_SYNCBUSY_CMD_SHIFT                  1                                          /**< Shift value for WDOG_CMD */
#define _WDOG_SYNCBUSY_CMD_MASK                   0x2UL                                      /**< Bit mask for WDOG_CMD */
#define _WDOG_SYNCBUSY_CMD_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_CMD_DEFAULT                 (_WDOG_SYNCBUSY_CMD_DEFAULT << 1)          /**< Shifted mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_PCH0_PRSCTRL                (0x1UL << 2)                               /**< PCH0_PRSCTRL Register Busy */
#define _WDOG_SYNCBUSY_PCH0_PRSCTRL_SHIFT         2                                          /**< Shift value for WDOG_PCH0_PRSCTRL */
#define _WDOG_SYNCBUSY_PCH0_PRSCTRL_MASK          0x4UL                                      /**< Bit mask for WDOG_PCH0_PRSCTRL */
#define _WDOG_SYNCBUSY_PCH0_PRSCTRL_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_PCH0_PRSCTRL_DEFAULT        (_WDOG_SYNCBUSY_PCH0_PRSCTRL_DEFAULT << 2) /**< Shifted mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_PCH1_PRSCTRL                (0x1UL << 3)                               /**< PCH1_PRSCTRL Register Busy */
#define _WDOG_SYNCBUSY_PCH1_PRSCTRL_SHIFT         3                                          /**< Shift value for WDOG_PCH1_PRSCTRL */
#define _WDOG_SYNCBUSY_PCH1_PRSCTRL_MASK          0x8UL                                      /**< Bit mask for WDOG_PCH1_PRSCTRL */
#define _WDOG_SYNCBUSY_PCH1_PRSCTRL_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for WDOG_SYNCBUSY */
#define WDOG_SYNCBUSY_PCH1_PRSCTRL_DEFAULT        (_WDOG_SYNCBUSY_PCH1_PRSCTRL_DEFAULT << 3) /**< Shifted mode DEFAULT for WDOG_SYNCBUSY */

/* Bit fields for WDOG PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_RESETVALUE              0x00000000UL                                  /**< Default value for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_MASK                    0x0000010FUL                                  /**< Mask for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_SHIFT            0                                             /**< Shift value for WDOG_PRSSEL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_MASK             0xFUL                                         /**< Bit mask for WDOG_PRSSEL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_DEFAULT          0x00000000UL                                  /**< Mode DEFAULT for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH0           0x00000000UL                                  /**< Mode PRSCH0 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH1           0x00000001UL                                  /**< Mode PRSCH1 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH2           0x00000002UL                                  /**< Mode PRSCH2 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH3           0x00000003UL                                  /**< Mode PRSCH3 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH4           0x00000004UL                                  /**< Mode PRSCH4 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH5           0x00000005UL                                  /**< Mode PRSCH5 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH6           0x00000006UL                                  /**< Mode PRSCH6 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH7           0x00000007UL                                  /**< Mode PRSCH7 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH8           0x00000008UL                                  /**< Mode PRSCH8 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH9           0x00000009UL                                  /**< Mode PRSCH9 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH10          0x0000000AUL                                  /**< Mode PRSCH10 for WDOG_PCH_PRSCTRL */
#define _WDOG_PCH_PRSCTRL_PRSSEL_PRSCH11          0x0000000BUL                                  /**< Mode PRSCH11 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_DEFAULT           (_WDOG_PCH_PRSCTRL_PRSSEL_DEFAULT << 0)       /**< Shifted mode DEFAULT for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH0            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH0 << 0)        /**< Shifted mode PRSCH0 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH1            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH1 << 0)        /**< Shifted mode PRSCH1 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH2            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH2 << 0)        /**< Shifted mode PRSCH2 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH3            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH3 << 0)        /**< Shifted mode PRSCH3 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH4            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH4 << 0)        /**< Shifted mode PRSCH4 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH5            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH5 << 0)        /**< Shifted mode PRSCH5 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH6            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH6 << 0)        /**< Shifted mode PRSCH6 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH7            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH7 << 0)        /**< Shifted mode PRSCH7 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH8            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH8 << 0)        /**< Shifted mode PRSCH8 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH9            (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH9 << 0)        /**< Shifted mode PRSCH9 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH10           (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH10 << 0)       /**< Shifted mode PRSCH10 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSSEL_PRSCH11           (_WDOG_PCH_PRSCTRL_PRSSEL_PRSCH11 << 0)       /**< Shifted mode PRSCH11 for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSMISSRSTEN             (0x1UL << 8)                                  /**< PRS Missing Event Will Trigger a Watchdog Reset */
#define _WDOG_PCH_PRSCTRL_PRSMISSRSTEN_SHIFT      8                                             /**< Shift value for WDOG_PRSMISSRSTEN */
#define _WDOG_PCH_PRSCTRL_PRSMISSRSTEN_MASK       0x100UL                                       /**< Bit mask for WDOG_PRSMISSRSTEN */
#define _WDOG_PCH_PRSCTRL_PRSMISSRSTEN_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for WDOG_PCH_PRSCTRL */
#define WDOG_PCH_PRSCTRL_PRSMISSRSTEN_DEFAULT     (_WDOG_PCH_PRSCTRL_PRSMISSRSTEN_DEFAULT << 8) /**< Shifted mode DEFAULT for WDOG_PCH_PRSCTRL */

/* Bit fields for WDOG IF */
#define _WDOG_IF_RESETVALUE                       0x00000000UL                 /**< Default value for WDOG_IF */
#define _WDOG_IF_MASK                             0x0000001FUL                 /**< Mask for WDOG_IF */
#define WDOG_IF_TOUT                              (0x1UL << 0)                 /**< WDOG Timeout Interrupt Flag */
#define _WDOG_IF_TOUT_SHIFT                       0                            /**< Shift value for WDOG_TOUT */
#define _WDOG_IF_TOUT_MASK                        0x1UL                        /**< Bit mask for WDOG_TOUT */
#define _WDOG_IF_TOUT_DEFAULT                     0x00000000UL                 /**< Mode DEFAULT for WDOG_IF */
#define WDOG_IF_TOUT_DEFAULT                      (_WDOG_IF_TOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for WDOG_IF */
#define WDOG_IF_WARN                              (0x1UL << 1)                 /**< WDOG Warning Timeout Interrupt Flag */
#define _WDOG_IF_WARN_SHIFT                       1                            /**< Shift value for WDOG_WARN */
#define _WDOG_IF_WARN_MASK                        0x2UL                        /**< Bit mask for WDOG_WARN */
#define _WDOG_IF_WARN_DEFAULT                     0x00000000UL                 /**< Mode DEFAULT for WDOG_IF */
#define WDOG_IF_WARN_DEFAULT                      (_WDOG_IF_WARN_DEFAULT << 1) /**< Shifted mode DEFAULT for WDOG_IF */
#define WDOG_IF_WIN                               (0x1UL << 2)                 /**< WDOG Window Interrupt Flag */
#define _WDOG_IF_WIN_SHIFT                        2                            /**< Shift value for WDOG_WIN */
#define _WDOG_IF_WIN_MASK                         0x4UL                        /**< Bit mask for WDOG_WIN */
#define _WDOG_IF_WIN_DEFAULT                      0x00000000UL                 /**< Mode DEFAULT for WDOG_IF */
#define WDOG_IF_WIN_DEFAULT                       (_WDOG_IF_WIN_DEFAULT << 2)  /**< Shifted mode DEFAULT for WDOG_IF */
#define WDOG_IF_PEM0                              (0x1UL << 3)                 /**< PRS Channel Zero Event Missing Interrupt Flag */
#define _WDOG_IF_PEM0_SHIFT                       3                            /**< Shift value for WDOG_PEM0 */
#define _WDOG_IF_PEM0_MASK                        0x8UL                        /**< Bit mask for WDOG_PEM0 */
#define _WDOG_IF_PEM0_DEFAULT                     0x00000000UL                 /**< Mode DEFAULT for WDOG_IF */
#define WDOG_IF_PEM0_DEFAULT                      (_WDOG_IF_PEM0_DEFAULT << 3) /**< Shifted mode DEFAULT for WDOG_IF */
#define WDOG_IF_PEM1                              (0x1UL << 4)                 /**< PRS Channel One Event Missing Interrupt Flag */
#define _WDOG_IF_PEM1_SHIFT                       4                            /**< Shift value for WDOG_PEM1 */
#define _WDOG_IF_PEM1_MASK                        0x10UL                       /**< Bit mask for WDOG_PEM1 */
#define _WDOG_IF_PEM1_DEFAULT                     0x00000000UL                 /**< Mode DEFAULT for WDOG_IF */
#define WDOG_IF_PEM1_DEFAULT                      (_WDOG_IF_PEM1_DEFAULT << 4) /**< Shifted mode DEFAULT for WDOG_IF */

/* Bit fields for WDOG IFS */
#define _WDOG_IFS_RESETVALUE                      0x00000000UL                  /**< Default value for WDOG_IFS */
#define _WDOG_IFS_MASK                            0x0000001FUL                  /**< Mask for WDOG_IFS */
#define WDOG_IFS_TOUT                             (0x1UL << 0)                  /**< Set TOUT Interrupt Flag */
#define _WDOG_IFS_TOUT_SHIFT                      0                             /**< Shift value for WDOG_TOUT */
#define _WDOG_IFS_TOUT_MASK                       0x1UL                         /**< Bit mask for WDOG_TOUT */
#define _WDOG_IFS_TOUT_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_TOUT_DEFAULT                     (_WDOG_IFS_TOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_WARN                             (0x1UL << 1)                  /**< Set WARN Interrupt Flag */
#define _WDOG_IFS_WARN_SHIFT                      1                             /**< Shift value for WDOG_WARN */
#define _WDOG_IFS_WARN_MASK                       0x2UL                         /**< Bit mask for WDOG_WARN */
#define _WDOG_IFS_WARN_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_WARN_DEFAULT                     (_WDOG_IFS_WARN_DEFAULT << 1) /**< Shifted mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_WIN                              (0x1UL << 2)                  /**< Set WIN Interrupt Flag */
#define _WDOG_IFS_WIN_SHIFT                       2                             /**< Shift value for WDOG_WIN */
#define _WDOG_IFS_WIN_MASK                        0x4UL                         /**< Bit mask for WDOG_WIN */
#define _WDOG_IFS_WIN_DEFAULT                     0x00000000UL                  /**< Mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_WIN_DEFAULT                      (_WDOG_IFS_WIN_DEFAULT << 2)  /**< Shifted mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_PEM0                             (0x1UL << 3)                  /**< Set PEM0 Interrupt Flag */
#define _WDOG_IFS_PEM0_SHIFT                      3                             /**< Shift value for WDOG_PEM0 */
#define _WDOG_IFS_PEM0_MASK                       0x8UL                         /**< Bit mask for WDOG_PEM0 */
#define _WDOG_IFS_PEM0_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_PEM0_DEFAULT                     (_WDOG_IFS_PEM0_DEFAULT << 3) /**< Shifted mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_PEM1                             (0x1UL << 4)                  /**< Set PEM1 Interrupt Flag */
#define _WDOG_IFS_PEM1_SHIFT                      4                             /**< Shift value for WDOG_PEM1 */
#define _WDOG_IFS_PEM1_MASK                       0x10UL                        /**< Bit mask for WDOG_PEM1 */
#define _WDOG_IFS_PEM1_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFS */
#define WDOG_IFS_PEM1_DEFAULT                     (_WDOG_IFS_PEM1_DEFAULT << 4) /**< Shifted mode DEFAULT for WDOG_IFS */

/* Bit fields for WDOG IFC */
#define _WDOG_IFC_RESETVALUE                      0x00000000UL                  /**< Default value for WDOG_IFC */
#define _WDOG_IFC_MASK                            0x0000001FUL                  /**< Mask for WDOG_IFC */
#define WDOG_IFC_TOUT                             (0x1UL << 0)                  /**< Clear TOUT Interrupt Flag */
#define _WDOG_IFC_TOUT_SHIFT                      0                             /**< Shift value for WDOG_TOUT */
#define _WDOG_IFC_TOUT_MASK                       0x1UL                         /**< Bit mask for WDOG_TOUT */
#define _WDOG_IFC_TOUT_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_TOUT_DEFAULT                     (_WDOG_IFC_TOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_WARN                             (0x1UL << 1)                  /**< Clear WARN Interrupt Flag */
#define _WDOG_IFC_WARN_SHIFT                      1                             /**< Shift value for WDOG_WARN */
#define _WDOG_IFC_WARN_MASK                       0x2UL                         /**< Bit mask for WDOG_WARN */
#define _WDOG_IFC_WARN_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_WARN_DEFAULT                     (_WDOG_IFC_WARN_DEFAULT << 1) /**< Shifted mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_WIN                              (0x1UL << 2)                  /**< Clear WIN Interrupt Flag */
#define _WDOG_IFC_WIN_SHIFT                       2                             /**< Shift value for WDOG_WIN */
#define _WDOG_IFC_WIN_MASK                        0x4UL                         /**< Bit mask for WDOG_WIN */
#define _WDOG_IFC_WIN_DEFAULT                     0x00000000UL                  /**< Mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_WIN_DEFAULT                      (_WDOG_IFC_WIN_DEFAULT << 2)  /**< Shifted mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_PEM0                             (0x1UL << 3)                  /**< Clear PEM0 Interrupt Flag */
#define _WDOG_IFC_PEM0_SHIFT                      3                             /**< Shift value for WDOG_PEM0 */
#define _WDOG_IFC_PEM0_MASK                       0x8UL                         /**< Bit mask for WDOG_PEM0 */
#define _WDOG_IFC_PEM0_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_PEM0_DEFAULT                     (_WDOG_IFC_PEM0_DEFAULT << 3) /**< Shifted mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_PEM1                             (0x1UL << 4)                  /**< Clear PEM1 Interrupt Flag */
#define _WDOG_IFC_PEM1_SHIFT                      4                             /**< Shift value for WDOG_PEM1 */
#define _WDOG_IFC_PEM1_MASK                       0x10UL                        /**< Bit mask for WDOG_PEM1 */
#define _WDOG_IFC_PEM1_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IFC */
#define WDOG_IFC_PEM1_DEFAULT                     (_WDOG_IFC_PEM1_DEFAULT << 4) /**< Shifted mode DEFAULT for WDOG_IFC */

/* Bit fields for WDOG IEN */
#define _WDOG_IEN_RESETVALUE                      0x00000000UL                  /**< Default value for WDOG_IEN */
#define _WDOG_IEN_MASK                            0x0000001FUL                  /**< Mask for WDOG_IEN */
#define WDOG_IEN_TOUT                             (0x1UL << 0)                  /**< TOUT Interrupt Enable */
#define _WDOG_IEN_TOUT_SHIFT                      0                             /**< Shift value for WDOG_TOUT */
#define _WDOG_IEN_TOUT_MASK                       0x1UL                         /**< Bit mask for WDOG_TOUT */
#define _WDOG_IEN_TOUT_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_TOUT_DEFAULT                     (_WDOG_IEN_TOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_WARN                             (0x1UL << 1)                  /**< WARN Interrupt Enable */
#define _WDOG_IEN_WARN_SHIFT                      1                             /**< Shift value for WDOG_WARN */
#define _WDOG_IEN_WARN_MASK                       0x2UL                         /**< Bit mask for WDOG_WARN */
#define _WDOG_IEN_WARN_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_WARN_DEFAULT                     (_WDOG_IEN_WARN_DEFAULT << 1) /**< Shifted mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_WIN                              (0x1UL << 2)                  /**< WIN Interrupt Enable */
#define _WDOG_IEN_WIN_SHIFT                       2                             /**< Shift value for WDOG_WIN */
#define _WDOG_IEN_WIN_MASK                        0x4UL                         /**< Bit mask for WDOG_WIN */
#define _WDOG_IEN_WIN_DEFAULT                     0x00000000UL                  /**< Mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_WIN_DEFAULT                      (_WDOG_IEN_WIN_DEFAULT << 2)  /**< Shifted mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_PEM0                             (0x1UL << 3)                  /**< PEM0 Interrupt Enable */
#define _WDOG_IEN_PEM0_SHIFT                      3                             /**< Shift value for WDOG_PEM0 */
#define _WDOG_IEN_PEM0_MASK                       0x8UL                         /**< Bit mask for WDOG_PEM0 */
#define _WDOG_IEN_PEM0_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_PEM0_DEFAULT                     (_WDOG_IEN_PEM0_DEFAULT << 3) /**< Shifted mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_PEM1                             (0x1UL << 4)                  /**< PEM1 Interrupt Enable */
#define _WDOG_IEN_PEM1_SHIFT                      4                             /**< Shift value for WDOG_PEM1 */
#define _WDOG_IEN_PEM1_MASK                       0x10UL                        /**< Bit mask for WDOG_PEM1 */
#define _WDOG_IEN_PEM1_DEFAULT                    0x00000000UL                  /**< Mode DEFAULT for WDOG_IEN */
#define WDOG_IEN_PEM1_DEFAULT                     (_WDOG_IEN_PEM1_DEFAULT << 4) /**< Shifted mode DEFAULT for WDOG_IEN */

/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define ITM_BASE            (0xE0000000UL)                            /*!< ITM Base Address */
#define DWT_BASE            (0xE0001000UL)                            /*!< DWT Base Address */
#define TPI_BASE            (0xE0040000UL)                            /*!< TPI Base Address */
#define CoreDebug_BASE      (0xE000EDF0UL)                            /*!< Core Debug Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define SCnSCB              ((SCnSCB_Type    *)     SCS_BASE      )   /*!< System control Register not in SCB */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */
#define ITM                 ((ITM_Type       *)     ITM_BASE      )   /*!< ITM configuration struct */
#define DWT                 ((DWT_Type       *)     DWT_BASE      )   /*!< DWT configuration struct */
#define TPI                 ((TPI_Type       *)     TPI_BASE      )   /*!< TPI configuration struct */
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug configuration struct */


#define NVIC_USER_IRQ_OFFSET          16

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*@} end of group CMSIS_SysTick */

/***************************************************************************//**
 * @addtogroup BUS
 * @brief BUS register and RAM bit/field read/write API
 * @details
 *  API to perform bit-band and field set/clear access to RAM and peripherals.
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Perform a single-bit write operation on a 32-bit word in RAM.
 *
 * @details
 *   This function uses Cortex-M bit-banding hardware to perform an atomic
 *   read-modify-write operation on a single bit write on a 32-bit word in RAM.
 *   See the reference manual for more details about bit-banding.
 *
 * @note
 *   This function is atomic on Cortex-M cores with bit-banding support. Bit-
 *   banding is a multicycle read-modify-write bus operation. RAM bit-banding is
 *   performed using the memory alias region at BITBAND_RAM_BASE.
 *
 * @param[in] addr An ddress of a 32-bit word in RAM.
 *
 * @param[in] bit A bit position to write, 0-31.
 *
 * @param[in] val A value to set bit to, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE void BUS_RamBitWrite(volatile uint32_t *addr,
                                     unsigned int bit,
                                     unsigned int val)
{
#if defined(BITBAND_RAM_BASE)
  uint32_t aliasAddr =
    BITBAND_RAM_BASE + (((uint32_t)addr - SRAM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);

  *(volatile uint32_t *)aliasAddr = (uint32_t)val;
#else
  uint32_t tmp = *addr;

  /* Make sure val is not more than 1 because only one bit needs to be set. */
  *addr = (tmp & ~(1 << bit)) | ((val & 1) << bit);
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a single-bit read operation on a 32-bit word in RAM.
 *
 * @details
 *   This function uses Cortex-M bit-banding hardware to perform an atomic
 *   read operation on a single register bit. See the
 *   reference manual for more details about bit-banding.
 *
 * @note
 *   This function is atomic on Cortex-M cores with bit-banding support.
 *   RAM bit-banding is performed using the memory alias region
 *   at BITBAND_RAM_BASE.
 *
 * @param[in] addr RAM address.
 *
 * @param[in] bit A bit position to read, 0-31.
 *
 * @return
 *     The requested bit shifted to bit position 0 in the return value.
 ******************************************************************************/
__STATIC_INLINE unsigned int BUS_RamBitRead(volatile const uint32_t *addr,
                                            unsigned int bit)
{
#if defined(BITBAND_RAM_BASE)
  uint32_t aliasAddr =
    BITBAND_RAM_BASE + (((uint32_t)addr - SRAM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);

  return *(volatile uint32_t *)aliasAddr;
#else
  return ((*addr) >> bit) & 1;
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a single-bit write operation on a peripheral register.
 *
 * @details
 *   This function uses Cortex-M bit-banding hardware to perform an atomic
 *   read-modify-write operation on a single register bit. See the
 *   reference manual for more details about bit-banding.
 *
 * @note
 *   This function is atomic on Cortex-M cores with bit-banding support. Bit-
 *   banding is a multicycle read-modify-write bus operation. Peripheral register
 *   bit-banding is performed using the memory alias region at BITBAND_PER_BASE.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] bit A bit position to write, 0-31.
 *
 * @param[in] val A value to set bit to, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE void BUS_RegBitWrite(volatile uint32_t *addr,
                                     unsigned int bit,
                                     unsigned int val)
{
#if defined(PER_REG_BLOCK_SET_OFFSET) && defined(PER_REG_BLOCK_CLR_OFFSET)
  uint32_t aliasAddr;
  if (val) {
    aliasAddr = (uint32_t)addr + PER_REG_BLOCK_SET_OFFSET;
  } else {
    aliasAddr = (uint32_t)addr + PER_REG_BLOCK_CLR_OFFSET;
  }
  *(volatile uint32_t *)aliasAddr = 1 << bit;
#elif defined(BITBAND_PER_BASE)
  uint32_t aliasAddr =
    BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);

  *(volatile uint32_t *)aliasAddr = (uint32_t)val;
#else
  uint32_t tmp = *addr;

  /* Make sure val is not more than 1 because only one bit needs to be set. */
  *addr = (tmp & ~(1 << bit)) | ((val & 1) << bit);
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a single-bit read operation on a peripheral register.
 *
 * @details
 *   This function uses Cortex-M bit-banding hardware to perform an atomic
 *   read operation on a single register bit. See the
 *   reference manual for more details about bit-banding.
 *
 * @note
 *   This function is atomic on Cortex-M cores with bit-banding support.
 *   Peripheral register bit-banding is performed using the memory alias
 *   region at BITBAND_PER_BASE.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] bit A bit position to read, 0-31.
 *
 * @return
 *     The requested bit shifted to bit position 0 in the return value.
 ******************************************************************************/
__STATIC_INLINE unsigned int BUS_RegBitRead(volatile const uint32_t *addr,
                                            unsigned int bit)
{
#if defined(BITBAND_PER_BASE)
  uint32_t aliasAddr =
    BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * (uint32_t)32) + (bit * (uint32_t) 4);

  return *(volatile uint32_t *)aliasAddr;
#else
  return ((*addr) >> bit) & 1;
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a masked set operation on a peripheral register address.
 *
 * @details
 *   A peripheral register masked set provides a single-cycle and atomic set
 *   operation of a bit-mask in a peripheral register. All 1s in the mask are
 *   set to 1 in the register. All 0s in the mask are not changed in the
 *   register.
 *   RAMs and special peripherals are not supported. See the
 *   reference manual for more details about the peripheral register field set.
 *
 * @note
 *   This function is single-cycle and atomic on cores with peripheral bit set
 *   and clear support. It uses the memory alias region at PER_BITSET_MEM_BASE.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] mask A mask to set.
 ******************************************************************************/
__STATIC_INLINE void BUS_RegMaskedSet(volatile uint32_t *addr,
                                      uint32_t mask)
{
#if defined(PER_REG_BLOCK_SET_OFFSET)
  uint32_t aliasAddr = (uint32_t)addr + PER_REG_BLOCK_SET_OFFSET;
  *(volatile uint32_t *)aliasAddr = mask;
#elif defined(PER_BITSET_MEM_BASE)
  uint32_t aliasAddr = PER_BITSET_MEM_BASE + ((uint32_t)addr - PER_MEM_BASE);
  *(volatile uint32_t *)aliasAddr = mask;
#else
  *addr |= mask;
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a masked clear operation on the peripheral register address.
 *
 * @details
 *   A peripheral register masked clear provides a single-cycle and atomic clear
 *   operation of a bit-mask in a peripheral register. All 1s in the mask are
 *   set to 0 in the register.
 *   All 0s in the mask are not changed in the register.
 *   RAMs and special peripherals are not supported. See the
 *   reference manual for more details about the peripheral register field clear.
 *
 * @note
 *   This function is single-cycle and atomic on cores with peripheral bit set
 *   and clear support. It uses the memory alias region at PER_BITCLR_MEM_BASE.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] mask A mask to clear.
 ******************************************************************************/
__STATIC_INLINE void BUS_RegMaskedClear(volatile uint32_t *addr,
                                        uint32_t mask)
{
#if defined(PER_REG_BLOCK_CLR_OFFSET)
  uint32_t aliasAddr = (uint32_t)addr + PER_REG_BLOCK_CLR_OFFSET;
  *(volatile uint32_t *)aliasAddr = mask;
#elif defined(PER_BITCLR_MEM_BASE)
  uint32_t aliasAddr = PER_BITCLR_MEM_BASE + ((uint32_t)addr - PER_MEM_BASE);
  *(volatile uint32_t *)aliasAddr = mask;
#else
  *addr &= ~mask;
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform peripheral register masked clear and value write.
 *
 * @details
 *   This function first clears the mask in the peripheral register, then
 *   writes the value. Typically, the mask is a bit-field in the register and
 *   the value val is within the mask.
 *
 * @note
 *   This operation is not atomic. Note that the mask is first set to 0 before
 *   the val is set.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] mask A peripheral register mask.
 *
 * @param[in] val  A peripheral register value. The value must be shifted to the
                  correct bit position in the register corresponding to the field
                  defined by the mask parameter. The register value must be
                  contained in the field defined by the mask parameter. This
                  function is not performing masking of val internally.
 ******************************************************************************/
__STATIC_INLINE void BUS_RegMaskedWrite(volatile uint32_t *addr,
                                        uint32_t mask,
                                        uint32_t val)
{
#if defined(PER_BITCLR_MEM_BASE) || defined(PER_REG_BLOCK_SET_OFFSET)
  BUS_RegMaskedClear(addr, mask);
  BUS_RegMaskedSet(addr, val);
#else
  *addr = (*addr & ~mask) | val;
#endif
}

/***************************************************************************//**
 * @brief
 *   Perform a peripheral register masked read.
 *
 * @details
 *   Read an unshifted and masked value from a peripheral register.
 *
 * @note
 *   This operation is not hardware accelerated.
 *
 * @param[in] addr A peripheral register address.
 *
 * @param[in] mask A peripheral register mask.
 *
 * @return
 *   An unshifted and masked register value.
 ******************************************************************************/
__STATIC_INLINE uint32_t BUS_RegMaskedRead(volatile const uint32_t *addr,
                                           uint32_t mask)
{
  return *addr & mask;
}

/***************************************************************************//**
 * @brief
 *   Count trailing number of zeros. Use CLZ instruction if available.
 *
 * @param[in] value
 *   Data value to check for number of trailing zero bits.
 *
 * @return
 *   A number of trailing zeros in value.
 ******************************************************************************/
__STATIC_INLINE uint32_t SL_CTZ(uint32_t value)
{
#if (__CORTEX_M >= 3)
  return __CLZ(__RBIT(value));

#else
  uint32_t zeros;
  for (zeros = 0; (zeros < 32) && ((value & 0x1) == 0); zeros++, value >>= 1) {
    ;
  }
  return zeros;
#endif
}

/***************************************************************************//**
 * @brief
 *   Convert logarithm of 2 to division factor.
 *
 * @param[in] log2
 *   Logarithm of 2.
 *
 * @return
 *   Dividend.
 ******************************************************************************/
__STATIC_INLINE uint32_t SL_Log2ToDiv(uint32_t log2)
{
//   EFM_ASSERT(log2 < 32U);
  return 1UL << log2;
}

#if ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI || ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER
/**
  \brief   Set Priority Grouping
  \details Sets the priority grouping field using the required unlock sequence.
           The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
           Only values from 0..7 are used.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  \param [in]      PriorityGroup  Priority grouping field.
 */
__STATIC_INLINE void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

  reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* Insert write key and priority group */
  SCB->AIRCR =  reg_value;
}


/**
  \brief   Get Priority Grouping
  \details Reads the priority grouping field from the NVIC Interrupt Controller.
  \return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
__STATIC_INLINE uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}


/**
  \brief   Enable Interrupt
  \details Enables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Interrupt Enable status
  \details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt is not enabled.
  \return             1  Interrupt is enabled.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Disable Interrupt
  \details Disables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}


/**
  \brief   Get Pending Interrupt
  \details Reads the NVIC pending register and returns the pending bit for the specified device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Active Interrupt
  \details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Interrupt Priority
  \details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
  \note    The priority cannot be set for every processor exception.
 */
__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief   Get Interrupt Priority
  \details Reads the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC->IP[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}


/**
  \brief   Encode Priority
  \details Encodes the priority for an interrupt with the given priority group,
           preemptive priority value, and subpriority value.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  \param [in]     PriorityGroup  Used priority group.
  \param [in]   PreemptPriority  Preemptive priority value (starting from 0).
  \param [in]       SubPriority  Subpriority value (starting from 0).
  \return                        Encoded priority. Value can be used in the function \ref NVIC_SetPriority().
 */
__STATIC_INLINE uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}


/**
  \brief   Decode Priority
  \details Decodes an interrupt priority value with a given priority group to
           preemptive priority value and subpriority value.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS) the smallest possible priority group is set.
  \param [in]         Priority   Priority value, which can be retrieved with the function \ref NVIC_GetPriority().
  \param [in]     PriorityGroup  Used priority group.
  \param [out] pPreemptPriority  Preemptive priority value (starting from 0).
  \param [out]     pSubPriority  Subpriority value (starting from 0).
 */
__STATIC_INLINE void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}


/**
  \brief   Set Interrupt Vector
  \details Sets an interrupt vector in SRAM based interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
           VTOR must been relocated to SRAM before.
  \param [in]   IRQn      Interrupt number
  \param [in]   vector    Address of interrupt handler function
 */
__STATIC_INLINE void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET] = vector;
}


/**
  \brief   Get Interrupt Vector
  \details Reads an interrupt vector from interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn      Interrupt number.
  \return                 Address of interrupt handler function
 */
__STATIC_INLINE uint32_t NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  return vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET];
}


/**
  \brief   System Reset
  \details Initiates a system reset request to reset the MCU.
 */
__STATIC_INLINE void NVIC_SystemReset(void)
{
  __DSB();                                                          /* Ensure all outstanding memory accesses included
                                                                       buffered write are completed before reset */
  SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)    |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                            SCB_AIRCR_SYSRESETREQ_Msk    );         /* Keep priority group unchanged */
  __DSB();                                                          /* Ensure completion of memory access */

  for(;;)                                                           /* wait until reset */
  {
    __NOP();
  }
}

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

#if defined (__Vendor_SysTickConfig) && (__Vendor_SysTickConfig == 0U)

/**
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

#endif

/***************************************************************************//**
 * @brief
 *   Get unique number for this device.
 *
 * @return
 *   Unique number for this device.
 ******************************************************************************/
__STATIC_INLINE uint64_t SYSTEM_GetUnique(void)
{
#if defined (_DEVINFO_EUI64H_MASK)
  uint32_t tmp = DEVINFO->EUI64L;
  return (uint64_t)((uint64_t)DEVINFO->EUI64H << 32) | tmp;
#elif defined(_DEVINFO_UNIQUEH_MASK)
  uint32_t tmp = DEVINFO->UNIQUEL;
  return (uint64_t)((uint64_t)DEVINFO->UNIQUEH << 32) | tmp;
#else
#error Location of device unique number is not defined.
#endif
}
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	void *zunoSysCall(uint8_t ct, uint8_t n, ...);
	__STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CONTROL, 2, IRQn, false);
	}
	__STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CONTROL, 2, IRQn, true);
	}
	__STATIC_INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_CLEARPENDING, 1, IRQn);
	}
	__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
	{
		zunoSysCall(ZUNO_SYSFUNC_INT_SETPRIORITY, 2, IRQn, priority);
	}
#endif

#endif // ZGECKO