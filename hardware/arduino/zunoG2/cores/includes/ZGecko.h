#if (!defined(ZGECKO))
#define ZGECKO

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define __STATIC_INLINE static inline
#ifndef   __STATIC_FORCEINLINE                 
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#define __NOP()                             __ASM volatile ("nop")

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */



#define EFM_ASSERT(expr)		((void)(expr))

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

#define CRYPTO_IRQn               CRYPTO0_IRQn /*!< Alias for CRYPTO0_IRQn */

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


/** MSC Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;           /**< Memory System Control Register  */
  __IOM uint32_t READCTRL;       /**< Read Control Register  */
  __IOM uint32_t WRITECTRL;      /**< Write Control Register  */
  __IOM uint32_t WRITECMD;       /**< Write Command Register  */
  __IOM uint32_t ADDRB;          /**< Page Erase/Write Address Buffer  */
  uint32_t       RESERVED0[1U];  /**< Reserved for future use **/
  __IOM uint32_t WDATA;          /**< Write Data Register  */
  __IM uint32_t  STATUS;         /**< Status Register  */

  uint32_t       RESERVED1[4U];  /**< Reserved for future use **/
  __IM uint32_t  IF;             /**< Interrupt Flag Register  */
  __IOM uint32_t IFS;            /**< Interrupt Flag Set Register  */
  __IOM uint32_t IFC;            /**< Interrupt Flag Clear Register  */
  __IOM uint32_t IEN;            /**< Interrupt Enable Register  */
  __IOM uint32_t LOCK;           /**< Configuration Lock Register  */
  __IOM uint32_t CACHECMD;       /**< Flash Cache Command Register  */
  __IM uint32_t  CACHEHITS;      /**< Cache Hits Performance Counter  */
  __IM uint32_t  CACHEMISSES;    /**< Cache Misses Performance Counter  */

  uint32_t       RESERVED2[1U];  /**< Reserved for future use **/
  __IOM uint32_t MASSLOCK;       /**< Mass Erase Lock Register  */

  uint32_t       RESERVED3[1U];  /**< Reserved for future use **/
  __IOM uint32_t STARTUP;        /**< Startup Control  */

  uint32_t       RESERVED4[5U];  /**< Reserved for future use **/
  __IOM uint32_t CMD;            /**< Command Register  */

  uint32_t       RESERVED5[6U];  /**< Reserved for future use **/
  __IOM uint32_t BOOTLOADERCTRL; /**< Bootloader Read and Write Enable, Write Once Register  */
  __IOM uint32_t AAPUNLOCKCMD;   /**< Software Unlock AAP Command Register  */
  __IOM uint32_t CACHECONFIG0;   /**< Cache Configuration Register 0  */
} MSC_TypeDef;                   /** @} */

/***************************************************************************//**
 * @addtogroup ZGM13_MSC
 * @{
 * @defgroup ZGM13_MSC_BitFields  MSC Bit Fields
 * @{
 ******************************************************************************/

/* Bit fields for MSC CTRL */
#define _MSC_CTRL_RESETVALUE                          0x00000001UL                            /**< Default value for MSC_CTRL */
#define _MSC_CTRL_MASK                                0x0000001FUL                            /**< Mask for MSC_CTRL */
#define MSC_CTRL_ADDRFAULTEN                          (0x1UL << 0)                            /**< Invalid Address Bus Fault Response Enable */
#define _MSC_CTRL_ADDRFAULTEN_SHIFT                   0                                       /**< Shift value for MSC_ADDRFAULTEN */
#define _MSC_CTRL_ADDRFAULTEN_MASK                    0x1UL                                   /**< Bit mask for MSC_ADDRFAULTEN */
#define _MSC_CTRL_ADDRFAULTEN_DEFAULT                 0x00000001UL                            /**< Mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_ADDRFAULTEN_DEFAULT                  (_MSC_CTRL_ADDRFAULTEN_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_CLKDISFAULTEN                        (0x1UL << 1)                            /**< Clock-disabled Bus Fault Response Enable */
#define _MSC_CTRL_CLKDISFAULTEN_SHIFT                 1                                       /**< Shift value for MSC_CLKDISFAULTEN */
#define _MSC_CTRL_CLKDISFAULTEN_MASK                  0x2UL                                   /**< Bit mask for MSC_CLKDISFAULTEN */
#define _MSC_CTRL_CLKDISFAULTEN_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_CLKDISFAULTEN_DEFAULT                (_MSC_CTRL_CLKDISFAULTEN_DEFAULT << 1)  /**< Shifted mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_PWRUPONDEMAND                        (0x1UL << 2)                            /**< Power Up on Demand During Wake Up */
#define _MSC_CTRL_PWRUPONDEMAND_SHIFT                 2                                       /**< Shift value for MSC_PWRUPONDEMAND */
#define _MSC_CTRL_PWRUPONDEMAND_MASK                  0x4UL                                   /**< Bit mask for MSC_PWRUPONDEMAND */
#define _MSC_CTRL_PWRUPONDEMAND_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_PWRUPONDEMAND_DEFAULT                (_MSC_CTRL_PWRUPONDEMAND_DEFAULT << 2)  /**< Shifted mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_IFCREADCLEAR                         (0x1UL << 3)                            /**< IFC Read Clears IF */
#define _MSC_CTRL_IFCREADCLEAR_SHIFT                  3                                       /**< Shift value for MSC_IFCREADCLEAR */
#define _MSC_CTRL_IFCREADCLEAR_MASK                   0x8UL                                   /**< Bit mask for MSC_IFCREADCLEAR */
#define _MSC_CTRL_IFCREADCLEAR_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_IFCREADCLEAR_DEFAULT                 (_MSC_CTRL_IFCREADCLEAR_DEFAULT << 3)   /**< Shifted mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_TIMEOUTFAULTEN                       (0x1UL << 4)                            /**< Timeout Bus Fault Response Enable */
#define _MSC_CTRL_TIMEOUTFAULTEN_SHIFT                4                                       /**< Shift value for MSC_TIMEOUTFAULTEN */
#define _MSC_CTRL_TIMEOUTFAULTEN_MASK                 0x10UL                                  /**< Bit mask for MSC_TIMEOUTFAULTEN */
#define _MSC_CTRL_TIMEOUTFAULTEN_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_TIMEOUTFAULTEN_DEFAULT               (_MSC_CTRL_TIMEOUTFAULTEN_DEFAULT << 4) /**< Shifted mode DEFAULT for MSC_CTRL */

/* Bit fields for MSC READCTRL */
#define _MSC_READCTRL_RESETVALUE                      0x01000100UL                          /**< Default value for MSC_READCTRL */
#define _MSC_READCTRL_MASK                            0x13000338UL                          /**< Mask for MSC_READCTRL */
#define MSC_READCTRL_IFCDIS                           (0x1UL << 3)                          /**< Internal Flash Cache Disable */
#define _MSC_READCTRL_IFCDIS_SHIFT                    3                                     /**< Shift value for MSC_IFCDIS */
#define _MSC_READCTRL_IFCDIS_MASK                     0x8UL                                 /**< Bit mask for MSC_IFCDIS */
#define _MSC_READCTRL_IFCDIS_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_IFCDIS_DEFAULT                   (_MSC_READCTRL_IFCDIS_DEFAULT << 3)   /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_AIDIS                            (0x1UL << 4)                          /**< Automatic Invalidate Disable */
#define _MSC_READCTRL_AIDIS_SHIFT                     4                                     /**< Shift value for MSC_AIDIS */
#define _MSC_READCTRL_AIDIS_MASK                      0x10UL                                /**< Bit mask for MSC_AIDIS */
#define _MSC_READCTRL_AIDIS_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_AIDIS_DEFAULT                    (_MSC_READCTRL_AIDIS_DEFAULT << 4)    /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_ICCDIS                           (0x1UL << 5)                          /**< Interrupt Context Cache Disable */
#define _MSC_READCTRL_ICCDIS_SHIFT                    5                                     /**< Shift value for MSC_ICCDIS */
#define _MSC_READCTRL_ICCDIS_MASK                     0x20UL                                /**< Bit mask for MSC_ICCDIS */
#define _MSC_READCTRL_ICCDIS_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_ICCDIS_DEFAULT                   (_MSC_READCTRL_ICCDIS_DEFAULT << 5)   /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_PREFETCH                         (0x1UL << 8)                          /**< Prefetch Mode */
#define _MSC_READCTRL_PREFETCH_SHIFT                  8                                     /**< Shift value for MSC_PREFETCH */
#define _MSC_READCTRL_PREFETCH_MASK                   0x100UL                               /**< Bit mask for MSC_PREFETCH */
#define _MSC_READCTRL_PREFETCH_DEFAULT                0x00000001UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_PREFETCH_DEFAULT                 (_MSC_READCTRL_PREFETCH_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_USEHPROT                         (0x1UL << 9)                          /**< AHB_HPROT Mode */
#define _MSC_READCTRL_USEHPROT_SHIFT                  9                                     /**< Shift value for MSC_USEHPROT */
#define _MSC_READCTRL_USEHPROT_MASK                   0x200UL                               /**< Bit mask for MSC_USEHPROT */
#define _MSC_READCTRL_USEHPROT_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_USEHPROT_DEFAULT                 (_MSC_READCTRL_USEHPROT_DEFAULT << 9) /**< Shifted mode DEFAULT for MSC_READCTRL */
#define _MSC_READCTRL_MODE_SHIFT                      24                                    /**< Shift value for MSC_MODE */
#define _MSC_READCTRL_MODE_MASK                       0x3000000UL                           /**< Bit mask for MSC_MODE */
#define _MSC_READCTRL_MODE_WS0                        0x00000000UL                          /**< Mode WS0 for MSC_READCTRL */
#define _MSC_READCTRL_MODE_DEFAULT                    0x00000001UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS1                        0x00000001UL                          /**< Mode WS1 for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS2                        0x00000002UL                          /**< Mode WS2 for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS3                        0x00000003UL                          /**< Mode WS3 for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS0                         (_MSC_READCTRL_MODE_WS0 << 24)        /**< Shifted mode WS0 for MSC_READCTRL */
#define MSC_READCTRL_MODE_DEFAULT                     (_MSC_READCTRL_MODE_DEFAULT << 24)    /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS1                         (_MSC_READCTRL_MODE_WS1 << 24)        /**< Shifted mode WS1 for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS2                         (_MSC_READCTRL_MODE_WS2 << 24)        /**< Shifted mode WS2 for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS3                         (_MSC_READCTRL_MODE_WS3 << 24)        /**< Shifted mode WS3 for MSC_READCTRL */
#define MSC_READCTRL_SCBTP                            (0x1UL << 28)                         /**< Suppress Conditional Branch Target Perfetch */
#define _MSC_READCTRL_SCBTP_SHIFT                     28                                    /**< Shift value for MSC_SCBTP */
#define _MSC_READCTRL_SCBTP_MASK                      0x10000000UL                          /**< Bit mask for MSC_SCBTP */
#define _MSC_READCTRL_SCBTP_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_SCBTP_DEFAULT                    (_MSC_READCTRL_SCBTP_DEFAULT << 28)   /**< Shifted mode DEFAULT for MSC_READCTRL */

/* Bit fields for MSC WRITECTRL */
#define _MSC_WRITECTRL_RESETVALUE                     0x00000000UL                                /**< Default value for MSC_WRITECTRL */
#define _MSC_WRITECTRL_MASK                           0x00000003UL                                /**< Mask for MSC_WRITECTRL */
#define MSC_WRITECTRL_WREN                            (0x1UL << 0)                                /**< Enable Write/Erase Controller */
#define _MSC_WRITECTRL_WREN_SHIFT                     0                                           /**< Shift value for MSC_WREN */
#define _MSC_WRITECTRL_WREN_MASK                      0x1UL                                       /**< Bit mask for MSC_WREN */
#define _MSC_WRITECTRL_WREN_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_WREN_DEFAULT                    (_MSC_WRITECTRL_WREN_DEFAULT << 0)          /**< Shifted mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_IRQERASEABORT                   (0x1UL << 1)                                /**< Abort Page Erase on Interrupt */
#define _MSC_WRITECTRL_IRQERASEABORT_SHIFT            1                                           /**< Shift value for MSC_IRQERASEABORT */
#define _MSC_WRITECTRL_IRQERASEABORT_MASK             0x2UL                                       /**< Bit mask for MSC_IRQERASEABORT */
#define _MSC_WRITECTRL_IRQERASEABORT_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_IRQERASEABORT_DEFAULT           (_MSC_WRITECTRL_IRQERASEABORT_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_WRITECTRL */

/* Bit fields for MSC WRITECMD */
#define _MSC_WRITECMD_RESETVALUE                      0x00000000UL                             /**< Default value for MSC_WRITECMD */
#define _MSC_WRITECMD_MASK                            0x0000113FUL                             /**< Mask for MSC_WRITECMD */
#define MSC_WRITECMD_LADDRIM                          (0x1UL << 0)                             /**< Load MSC_ADDRB Into ADDR */
#define _MSC_WRITECMD_LADDRIM_SHIFT                   0                                        /**< Shift value for MSC_LADDRIM */
#define _MSC_WRITECMD_LADDRIM_MASK                    0x1UL                                    /**< Bit mask for MSC_LADDRIM */
#define _MSC_WRITECMD_LADDRIM_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_LADDRIM_DEFAULT                  (_MSC_WRITECMD_LADDRIM_DEFAULT << 0)     /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEPAGE                        (0x1UL << 1)                             /**< Erase Page */
#define _MSC_WRITECMD_ERASEPAGE_SHIFT                 1                                        /**< Shift value for MSC_ERASEPAGE */
#define _MSC_WRITECMD_ERASEPAGE_MASK                  0x2UL                                    /**< Bit mask for MSC_ERASEPAGE */
#define _MSC_WRITECMD_ERASEPAGE_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEPAGE_DEFAULT                (_MSC_WRITECMD_ERASEPAGE_DEFAULT << 1)   /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEEND                         (0x1UL << 2)                             /**< End Write Mode */
#define _MSC_WRITECMD_WRITEEND_SHIFT                  2                                        /**< Shift value for MSC_WRITEEND */
#define _MSC_WRITECMD_WRITEEND_MASK                   0x4UL                                    /**< Bit mask for MSC_WRITEEND */
#define _MSC_WRITECMD_WRITEEND_DEFAULT                0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEEND_DEFAULT                 (_MSC_WRITECMD_WRITEEND_DEFAULT << 2)    /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEONCE                        (0x1UL << 3)                             /**< Word Write-Once Trigger */
#define _MSC_WRITECMD_WRITEONCE_SHIFT                 3                                        /**< Shift value for MSC_WRITEONCE */
#define _MSC_WRITECMD_WRITEONCE_MASK                  0x8UL                                    /**< Bit mask for MSC_WRITEONCE */
#define _MSC_WRITECMD_WRITEONCE_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEONCE_DEFAULT                (_MSC_WRITECMD_WRITEONCE_DEFAULT << 3)   /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITETRIG                        (0x1UL << 4)                             /**< Word Write Sequence Trigger */
#define _MSC_WRITECMD_WRITETRIG_SHIFT                 4                                        /**< Shift value for MSC_WRITETRIG */
#define _MSC_WRITECMD_WRITETRIG_MASK                  0x10UL                                   /**< Bit mask for MSC_WRITETRIG */
#define _MSC_WRITECMD_WRITETRIG_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITETRIG_DEFAULT                (_MSC_WRITECMD_WRITETRIG_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEABORT                       (0x1UL << 5)                             /**< Abort Erase Sequence */
#define _MSC_WRITECMD_ERASEABORT_SHIFT                5                                        /**< Shift value for MSC_ERASEABORT */
#define _MSC_WRITECMD_ERASEABORT_MASK                 0x20UL                                   /**< Bit mask for MSC_ERASEABORT */
#define _MSC_WRITECMD_ERASEABORT_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEABORT_DEFAULT               (_MSC_WRITECMD_ERASEABORT_DEFAULT << 5)  /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEMAIN0                       (0x1UL << 8)                             /**< Mass Erase Region 0 */
#define _MSC_WRITECMD_ERASEMAIN0_SHIFT                8                                        /**< Shift value for MSC_ERASEMAIN0 */
#define _MSC_WRITECMD_ERASEMAIN0_MASK                 0x100UL                                  /**< Bit mask for MSC_ERASEMAIN0 */
#define _MSC_WRITECMD_ERASEMAIN0_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEMAIN0_DEFAULT               (_MSC_WRITECMD_ERASEMAIN0_DEFAULT << 8)  /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_CLEARWDATA                       (0x1UL << 12)                            /**< Clear WDATA State */
#define _MSC_WRITECMD_CLEARWDATA_SHIFT                12                                       /**< Shift value for MSC_CLEARWDATA */
#define _MSC_WRITECMD_CLEARWDATA_MASK                 0x1000UL                                 /**< Bit mask for MSC_CLEARWDATA */
#define _MSC_WRITECMD_CLEARWDATA_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_CLEARWDATA_DEFAULT               (_MSC_WRITECMD_CLEARWDATA_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_WRITECMD */

/* Bit fields for MSC ADDRB */
#define _MSC_ADDRB_RESETVALUE                         0x00000000UL                    /**< Default value for MSC_ADDRB */
#define _MSC_ADDRB_MASK                               0xFFFFFFFFUL                    /**< Mask for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_SHIFT                        0                               /**< Shift value for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_MASK                         0xFFFFFFFFUL                    /**< Bit mask for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_DEFAULT                      0x00000000UL                    /**< Mode DEFAULT for MSC_ADDRB */
#define MSC_ADDRB_ADDRB_DEFAULT                       (_MSC_ADDRB_ADDRB_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_ADDRB */

/* Bit fields for MSC WDATA */
#define _MSC_WDATA_RESETVALUE                         0x00000000UL                    /**< Default value for MSC_WDATA */
#define _MSC_WDATA_MASK                               0xFFFFFFFFUL                    /**< Mask for MSC_WDATA */
#define _MSC_WDATA_WDATA_SHIFT                        0                               /**< Shift value for MSC_WDATA */
#define _MSC_WDATA_WDATA_MASK                         0xFFFFFFFFUL                    /**< Bit mask for MSC_WDATA */
#define _MSC_WDATA_WDATA_DEFAULT                      0x00000000UL                    /**< Mode DEFAULT for MSC_WDATA */
#define MSC_WDATA_WDATA_DEFAULT                       (_MSC_WDATA_WDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_WDATA */

/* Bit fields for MSC STATUS */
#define _MSC_STATUS_RESETVALUE                        0x00000008UL                                   /**< Default value for MSC_STATUS */
#define _MSC_STATUS_MASK                              0xFF00007FUL                                   /**< Mask for MSC_STATUS */
#define MSC_STATUS_BUSY                               (0x1UL << 0)                                   /**< Erase/Write Busy */
#define _MSC_STATUS_BUSY_SHIFT                        0                                              /**< Shift value for MSC_BUSY */
#define _MSC_STATUS_BUSY_MASK                         0x1UL                                          /**< Bit mask for MSC_BUSY */
#define _MSC_STATUS_BUSY_DEFAULT                      0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_BUSY_DEFAULT                       (_MSC_STATUS_BUSY_DEFAULT << 0)                /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_LOCKED                             (0x1UL << 1)                                   /**< Access Locked */
#define _MSC_STATUS_LOCKED_SHIFT                      1                                              /**< Shift value for MSC_LOCKED */
#define _MSC_STATUS_LOCKED_MASK                       0x2UL                                          /**< Bit mask for MSC_LOCKED */
#define _MSC_STATUS_LOCKED_DEFAULT                    0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_LOCKED_DEFAULT                     (_MSC_STATUS_LOCKED_DEFAULT << 1)              /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_INVADDR                            (0x1UL << 2)                                   /**< Invalid Write Address or Erase Page */
#define _MSC_STATUS_INVADDR_SHIFT                     2                                              /**< Shift value for MSC_INVADDR */
#define _MSC_STATUS_INVADDR_MASK                      0x4UL                                          /**< Bit mask for MSC_INVADDR */
#define _MSC_STATUS_INVADDR_DEFAULT                   0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_INVADDR_DEFAULT                    (_MSC_STATUS_INVADDR_DEFAULT << 2)             /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WDATAREADY                         (0x1UL << 3)                                   /**< WDATA Write Ready */
#define _MSC_STATUS_WDATAREADY_SHIFT                  3                                              /**< Shift value for MSC_WDATAREADY */
#define _MSC_STATUS_WDATAREADY_MASK                   0x8UL                                          /**< Bit mask for MSC_WDATAREADY */
#define _MSC_STATUS_WDATAREADY_DEFAULT                0x00000001UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WDATAREADY_DEFAULT                 (_MSC_STATUS_WDATAREADY_DEFAULT << 3)          /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WORDTIMEOUT                        (0x1UL << 4)                                   /**< Flash Write Word Timeout */
#define _MSC_STATUS_WORDTIMEOUT_SHIFT                 4                                              /**< Shift value for MSC_WORDTIMEOUT */
#define _MSC_STATUS_WORDTIMEOUT_MASK                  0x10UL                                         /**< Bit mask for MSC_WORDTIMEOUT */
#define _MSC_STATUS_WORDTIMEOUT_DEFAULT               0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WORDTIMEOUT_DEFAULT                (_MSC_STATUS_WORDTIMEOUT_DEFAULT << 4)         /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_ERASEABORTED                       (0x1UL << 5)                                   /**< The Current Flash Erase Operation Aborted */
#define _MSC_STATUS_ERASEABORTED_SHIFT                5                                              /**< Shift value for MSC_ERASEABORTED */
#define _MSC_STATUS_ERASEABORTED_MASK                 0x20UL                                         /**< Bit mask for MSC_ERASEABORTED */
#define _MSC_STATUS_ERASEABORTED_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_ERASEABORTED_DEFAULT               (_MSC_STATUS_ERASEABORTED_DEFAULT << 5)        /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_PCRUNNING                          (0x1UL << 6)                                   /**< Performance Counters Running */
#define _MSC_STATUS_PCRUNNING_SHIFT                   6                                              /**< Shift value for MSC_PCRUNNING */
#define _MSC_STATUS_PCRUNNING_MASK                    0x40UL                                         /**< Bit mask for MSC_PCRUNNING */
#define _MSC_STATUS_PCRUNNING_DEFAULT                 0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_PCRUNNING_DEFAULT                  (_MSC_STATUS_PCRUNNING_DEFAULT << 6)           /**< Shifted mode DEFAULT for MSC_STATUS */
#define _MSC_STATUS_WDATAVALID_SHIFT                  24                                             /**< Shift value for MSC_WDATAVALID */
#define _MSC_STATUS_WDATAVALID_MASK                   0xF000000UL                                    /**< Bit mask for MSC_WDATAVALID */
#define _MSC_STATUS_WDATAVALID_DEFAULT                0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WDATAVALID_DEFAULT                 (_MSC_STATUS_WDATAVALID_DEFAULT << 24)         /**< Shifted mode DEFAULT for MSC_STATUS */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_SHIFT          28                                             /**< Shift value for MSC_PWRUPCKBDFAILCOUNT */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_MASK           0xF0000000UL                                   /**< Bit mask for MSC_PWRUPCKBDFAILCOUNT */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT        0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT         (_MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT << 28) /**< Shifted mode DEFAULT for MSC_STATUS */

/* Bit fields for MSC IF */
#define _MSC_IF_RESETVALUE                            0x00000000UL                    /**< Default value for MSC_IF */
#define _MSC_IF_MASK                                  0x0000017FUL                    /**< Mask for MSC_IF */
#define MSC_IF_ERASE                                  (0x1UL << 0)                    /**< Erase Done Interrupt Read Flag */
#define _MSC_IF_ERASE_SHIFT                           0                               /**< Shift value for MSC_ERASE */
#define _MSC_IF_ERASE_MASK                            0x1UL                           /**< Bit mask for MSC_ERASE */
#define _MSC_IF_ERASE_DEFAULT                         0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_ERASE_DEFAULT                          (_MSC_IF_ERASE_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_WRITE                                  (0x1UL << 1)                    /**< Write Done Interrupt Read Flag */
#define _MSC_IF_WRITE_SHIFT                           1                               /**< Shift value for MSC_WRITE */
#define _MSC_IF_WRITE_MASK                            0x2UL                           /**< Bit mask for MSC_WRITE */
#define _MSC_IF_WRITE_DEFAULT                         0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_WRITE_DEFAULT                          (_MSC_IF_WRITE_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_CHOF                                   (0x1UL << 2)                    /**< Cache Hits Overflow Interrupt Flag */
#define _MSC_IF_CHOF_SHIFT                            2                               /**< Shift value for MSC_CHOF */
#define _MSC_IF_CHOF_MASK                             0x4UL                           /**< Bit mask for MSC_CHOF */
#define _MSC_IF_CHOF_DEFAULT                          0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_CHOF_DEFAULT                           (_MSC_IF_CHOF_DEFAULT << 2)     /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_CMOF                                   (0x1UL << 3)                    /**< Cache Misses Overflow Interrupt Flag */
#define _MSC_IF_CMOF_SHIFT                            3                               /**< Shift value for MSC_CMOF */
#define _MSC_IF_CMOF_MASK                             0x8UL                           /**< Bit mask for MSC_CMOF */
#define _MSC_IF_CMOF_DEFAULT                          0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_CMOF_DEFAULT                           (_MSC_IF_CMOF_DEFAULT << 3)     /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_PWRUPF                                 (0x1UL << 4)                    /**< Flash Power Up Sequence Complete Flag */
#define _MSC_IF_PWRUPF_SHIFT                          4                               /**< Shift value for MSC_PWRUPF */
#define _MSC_IF_PWRUPF_MASK                           0x10UL                          /**< Bit mask for MSC_PWRUPF */
#define _MSC_IF_PWRUPF_DEFAULT                        0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_PWRUPF_DEFAULT                         (_MSC_IF_PWRUPF_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_ICACHERR                               (0x1UL << 5)                    /**< ICache RAM Parity Error Flag */
#define _MSC_IF_ICACHERR_SHIFT                        5                               /**< Shift value for MSC_ICACHERR */
#define _MSC_IF_ICACHERR_MASK                         0x20UL                          /**< Bit mask for MSC_ICACHERR */
#define _MSC_IF_ICACHERR_DEFAULT                      0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_ICACHERR_DEFAULT                       (_MSC_IF_ICACHERR_DEFAULT << 5) /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_WDATAOV                                (0x1UL << 6)                    /**< Flash Controller Write Buffer Overflow */
#define _MSC_IF_WDATAOV_SHIFT                         6                               /**< Shift value for MSC_WDATAOV */
#define _MSC_IF_WDATAOV_MASK                          0x40UL                          /**< Bit mask for MSC_WDATAOV */
#define _MSC_IF_WDATAOV_DEFAULT                       0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_WDATAOV_DEFAULT                        (_MSC_IF_WDATAOV_DEFAULT << 6)  /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_LVEWRITE                               (0x1UL << 8)                    /**< Flash LVE Write Error Flag */
#define _MSC_IF_LVEWRITE_SHIFT                        8                               /**< Shift value for MSC_LVEWRITE */
#define _MSC_IF_LVEWRITE_MASK                         0x100UL                         /**< Bit mask for MSC_LVEWRITE */
#define _MSC_IF_LVEWRITE_DEFAULT                      0x00000000UL                    /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_LVEWRITE_DEFAULT                       (_MSC_IF_LVEWRITE_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_IF */

/* Bit fields for MSC IFS */
#define _MSC_IFS_RESETVALUE                           0x00000000UL                     /**< Default value for MSC_IFS */
#define _MSC_IFS_MASK                                 0x0000017FUL                     /**< Mask for MSC_IFS */
#define MSC_IFS_ERASE                                 (0x1UL << 0)                     /**< Set ERASE Interrupt Flag */
#define _MSC_IFS_ERASE_SHIFT                          0                                /**< Shift value for MSC_ERASE */
#define _MSC_IFS_ERASE_MASK                           0x1UL                            /**< Bit mask for MSC_ERASE */
#define _MSC_IFS_ERASE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_ERASE_DEFAULT                         (_MSC_IFS_ERASE_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_WRITE                                 (0x1UL << 1)                     /**< Set WRITE Interrupt Flag */
#define _MSC_IFS_WRITE_SHIFT                          1                                /**< Shift value for MSC_WRITE */
#define _MSC_IFS_WRITE_MASK                           0x2UL                            /**< Bit mask for MSC_WRITE */
#define _MSC_IFS_WRITE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_WRITE_DEFAULT                         (_MSC_IFS_WRITE_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_CHOF                                  (0x1UL << 2)                     /**< Set CHOF Interrupt Flag */
#define _MSC_IFS_CHOF_SHIFT                           2                                /**< Shift value for MSC_CHOF */
#define _MSC_IFS_CHOF_MASK                            0x4UL                            /**< Bit mask for MSC_CHOF */
#define _MSC_IFS_CHOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_CHOF_DEFAULT                          (_MSC_IFS_CHOF_DEFAULT << 2)     /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_CMOF                                  (0x1UL << 3)                     /**< Set CMOF Interrupt Flag */
#define _MSC_IFS_CMOF_SHIFT                           3                                /**< Shift value for MSC_CMOF */
#define _MSC_IFS_CMOF_MASK                            0x8UL                            /**< Bit mask for MSC_CMOF */
#define _MSC_IFS_CMOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_CMOF_DEFAULT                          (_MSC_IFS_CMOF_DEFAULT << 3)     /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_PWRUPF                                (0x1UL << 4)                     /**< Set PWRUPF Interrupt Flag */
#define _MSC_IFS_PWRUPF_SHIFT                         4                                /**< Shift value for MSC_PWRUPF */
#define _MSC_IFS_PWRUPF_MASK                          0x10UL                           /**< Bit mask for MSC_PWRUPF */
#define _MSC_IFS_PWRUPF_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_PWRUPF_DEFAULT                        (_MSC_IFS_PWRUPF_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_ICACHERR                              (0x1UL << 5)                     /**< Set ICACHERR Interrupt Flag */
#define _MSC_IFS_ICACHERR_SHIFT                       5                                /**< Shift value for MSC_ICACHERR */
#define _MSC_IFS_ICACHERR_MASK                        0x20UL                           /**< Bit mask for MSC_ICACHERR */
#define _MSC_IFS_ICACHERR_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_ICACHERR_DEFAULT                      (_MSC_IFS_ICACHERR_DEFAULT << 5) /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_WDATAOV                               (0x1UL << 6)                     /**< Set WDATAOV Interrupt Flag */
#define _MSC_IFS_WDATAOV_SHIFT                        6                                /**< Shift value for MSC_WDATAOV */
#define _MSC_IFS_WDATAOV_MASK                         0x40UL                           /**< Bit mask for MSC_WDATAOV */
#define _MSC_IFS_WDATAOV_DEFAULT                      0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_WDATAOV_DEFAULT                       (_MSC_IFS_WDATAOV_DEFAULT << 6)  /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_LVEWRITE                              (0x1UL << 8)                     /**< Set LVEWRITE Interrupt Flag */
#define _MSC_IFS_LVEWRITE_SHIFT                       8                                /**< Shift value for MSC_LVEWRITE */
#define _MSC_IFS_LVEWRITE_MASK                        0x100UL                          /**< Bit mask for MSC_LVEWRITE */
#define _MSC_IFS_LVEWRITE_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_LVEWRITE_DEFAULT                      (_MSC_IFS_LVEWRITE_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_IFS */

/* Bit fields for MSC IFC */
#define _MSC_IFC_RESETVALUE                           0x00000000UL                     /**< Default value for MSC_IFC */
#define _MSC_IFC_MASK                                 0x0000017FUL                     /**< Mask for MSC_IFC */
#define MSC_IFC_ERASE                                 (0x1UL << 0)                     /**< Clear ERASE Interrupt Flag */
#define _MSC_IFC_ERASE_SHIFT                          0                                /**< Shift value for MSC_ERASE */
#define _MSC_IFC_ERASE_MASK                           0x1UL                            /**< Bit mask for MSC_ERASE */
#define _MSC_IFC_ERASE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_ERASE_DEFAULT                         (_MSC_IFC_ERASE_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_WRITE                                 (0x1UL << 1)                     /**< Clear WRITE Interrupt Flag */
#define _MSC_IFC_WRITE_SHIFT                          1                                /**< Shift value for MSC_WRITE */
#define _MSC_IFC_WRITE_MASK                           0x2UL                            /**< Bit mask for MSC_WRITE */
#define _MSC_IFC_WRITE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_WRITE_DEFAULT                         (_MSC_IFC_WRITE_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_CHOF                                  (0x1UL << 2)                     /**< Clear CHOF Interrupt Flag */
#define _MSC_IFC_CHOF_SHIFT                           2                                /**< Shift value for MSC_CHOF */
#define _MSC_IFC_CHOF_MASK                            0x4UL                            /**< Bit mask for MSC_CHOF */
#define _MSC_IFC_CHOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_CHOF_DEFAULT                          (_MSC_IFC_CHOF_DEFAULT << 2)     /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_CMOF                                  (0x1UL << 3)                     /**< Clear CMOF Interrupt Flag */
#define _MSC_IFC_CMOF_SHIFT                           3                                /**< Shift value for MSC_CMOF */
#define _MSC_IFC_CMOF_MASK                            0x8UL                            /**< Bit mask for MSC_CMOF */
#define _MSC_IFC_CMOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_CMOF_DEFAULT                          (_MSC_IFC_CMOF_DEFAULT << 3)     /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_PWRUPF                                (0x1UL << 4)                     /**< Clear PWRUPF Interrupt Flag */
#define _MSC_IFC_PWRUPF_SHIFT                         4                                /**< Shift value for MSC_PWRUPF */
#define _MSC_IFC_PWRUPF_MASK                          0x10UL                           /**< Bit mask for MSC_PWRUPF */
#define _MSC_IFC_PWRUPF_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_PWRUPF_DEFAULT                        (_MSC_IFC_PWRUPF_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_ICACHERR                              (0x1UL << 5)                     /**< Clear ICACHERR Interrupt Flag */
#define _MSC_IFC_ICACHERR_SHIFT                       5                                /**< Shift value for MSC_ICACHERR */
#define _MSC_IFC_ICACHERR_MASK                        0x20UL                           /**< Bit mask for MSC_ICACHERR */
#define _MSC_IFC_ICACHERR_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_ICACHERR_DEFAULT                      (_MSC_IFC_ICACHERR_DEFAULT << 5) /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_WDATAOV                               (0x1UL << 6)                     /**< Clear WDATAOV Interrupt Flag */
#define _MSC_IFC_WDATAOV_SHIFT                        6                                /**< Shift value for MSC_WDATAOV */
#define _MSC_IFC_WDATAOV_MASK                         0x40UL                           /**< Bit mask for MSC_WDATAOV */
#define _MSC_IFC_WDATAOV_DEFAULT                      0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_WDATAOV_DEFAULT                       (_MSC_IFC_WDATAOV_DEFAULT << 6)  /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_LVEWRITE                              (0x1UL << 8)                     /**< Clear LVEWRITE Interrupt Flag */
#define _MSC_IFC_LVEWRITE_SHIFT                       8                                /**< Shift value for MSC_LVEWRITE */
#define _MSC_IFC_LVEWRITE_MASK                        0x100UL                          /**< Bit mask for MSC_LVEWRITE */
#define _MSC_IFC_LVEWRITE_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_LVEWRITE_DEFAULT                      (_MSC_IFC_LVEWRITE_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_IFC */

/* Bit fields for MSC IEN */
#define _MSC_IEN_RESETVALUE                           0x00000000UL                     /**< Default value for MSC_IEN */
#define _MSC_IEN_MASK                                 0x0000017FUL                     /**< Mask for MSC_IEN */
#define MSC_IEN_ERASE                                 (0x1UL << 0)                     /**< ERASE Interrupt Enable */
#define _MSC_IEN_ERASE_SHIFT                          0                                /**< Shift value for MSC_ERASE */
#define _MSC_IEN_ERASE_MASK                           0x1UL                            /**< Bit mask for MSC_ERASE */
#define _MSC_IEN_ERASE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_ERASE_DEFAULT                         (_MSC_IEN_ERASE_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_WRITE                                 (0x1UL << 1)                     /**< WRITE Interrupt Enable */
#define _MSC_IEN_WRITE_SHIFT                          1                                /**< Shift value for MSC_WRITE */
#define _MSC_IEN_WRITE_MASK                           0x2UL                            /**< Bit mask for MSC_WRITE */
#define _MSC_IEN_WRITE_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_WRITE_DEFAULT                         (_MSC_IEN_WRITE_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_CHOF                                  (0x1UL << 2)                     /**< CHOF Interrupt Enable */
#define _MSC_IEN_CHOF_SHIFT                           2                                /**< Shift value for MSC_CHOF */
#define _MSC_IEN_CHOF_MASK                            0x4UL                            /**< Bit mask for MSC_CHOF */
#define _MSC_IEN_CHOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_CHOF_DEFAULT                          (_MSC_IEN_CHOF_DEFAULT << 2)     /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_CMOF                                  (0x1UL << 3)                     /**< CMOF Interrupt Enable */
#define _MSC_IEN_CMOF_SHIFT                           3                                /**< Shift value for MSC_CMOF */
#define _MSC_IEN_CMOF_MASK                            0x8UL                            /**< Bit mask for MSC_CMOF */
#define _MSC_IEN_CMOF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_CMOF_DEFAULT                          (_MSC_IEN_CMOF_DEFAULT << 3)     /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_PWRUPF                                (0x1UL << 4)                     /**< PWRUPF Interrupt Enable */
#define _MSC_IEN_PWRUPF_SHIFT                         4                                /**< Shift value for MSC_PWRUPF */
#define _MSC_IEN_PWRUPF_MASK                          0x10UL                           /**< Bit mask for MSC_PWRUPF */
#define _MSC_IEN_PWRUPF_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_PWRUPF_DEFAULT                        (_MSC_IEN_PWRUPF_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_ICACHERR                              (0x1UL << 5)                     /**< ICACHERR Interrupt Enable */
#define _MSC_IEN_ICACHERR_SHIFT                       5                                /**< Shift value for MSC_ICACHERR */
#define _MSC_IEN_ICACHERR_MASK                        0x20UL                           /**< Bit mask for MSC_ICACHERR */
#define _MSC_IEN_ICACHERR_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_ICACHERR_DEFAULT                      (_MSC_IEN_ICACHERR_DEFAULT << 5) /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_WDATAOV                               (0x1UL << 6)                     /**< WDATAOV Interrupt Enable */
#define _MSC_IEN_WDATAOV_SHIFT                        6                                /**< Shift value for MSC_WDATAOV */
#define _MSC_IEN_WDATAOV_MASK                         0x40UL                           /**< Bit mask for MSC_WDATAOV */
#define _MSC_IEN_WDATAOV_DEFAULT                      0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_WDATAOV_DEFAULT                       (_MSC_IEN_WDATAOV_DEFAULT << 6)  /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_LVEWRITE                              (0x1UL << 8)                     /**< LVEWRITE Interrupt Enable */
#define _MSC_IEN_LVEWRITE_SHIFT                       8                                /**< Shift value for MSC_LVEWRITE */
#define _MSC_IEN_LVEWRITE_MASK                        0x100UL                          /**< Bit mask for MSC_LVEWRITE */
#define _MSC_IEN_LVEWRITE_DEFAULT                     0x00000000UL                     /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_LVEWRITE_DEFAULT                      (_MSC_IEN_LVEWRITE_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_IEN */

/* Bit fields for MSC LOCK */
#define _MSC_LOCK_RESETVALUE                          0x00000000UL                      /**< Default value for MSC_LOCK */
#define _MSC_LOCK_MASK                                0x0000FFFFUL                      /**< Mask for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_SHIFT                       0                                 /**< Shift value for MSC_LOCKKEY */
#define _MSC_LOCK_LOCKKEY_MASK                        0xFFFFUL                          /**< Bit mask for MSC_LOCKKEY */
#define _MSC_LOCK_LOCKKEY_DEFAULT                     0x00000000UL                      /**< Mode DEFAULT for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_UNLOCKED                    0x00000000UL                      /**< Mode UNLOCKED for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_LOCK                        0x00000000UL                      /**< Mode LOCK for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_LOCKED                      0x00000001UL                      /**< Mode LOCKED for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_UNLOCK                      0x00001B71UL                      /**< Mode UNLOCK for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_DEFAULT                      (_MSC_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_UNLOCKED                     (_MSC_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_LOCK                         (_MSC_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_LOCKED                       (_MSC_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_UNLOCK                       (_MSC_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for MSC_LOCK */

/* Bit fields for MSC CACHECMD */
#define _MSC_CACHECMD_RESETVALUE                      0x00000000UL                          /**< Default value for MSC_CACHECMD */
#define _MSC_CACHECMD_MASK                            0x00000007UL                          /**< Mask for MSC_CACHECMD */
#define MSC_CACHECMD_INVCACHE                         (0x1UL << 0)                          /**< Invalidate Instruction Cache */
#define _MSC_CACHECMD_INVCACHE_SHIFT                  0                                     /**< Shift value for MSC_INVCACHE */
#define _MSC_CACHECMD_INVCACHE_MASK                   0x1UL                                 /**< Bit mask for MSC_INVCACHE */
#define _MSC_CACHECMD_INVCACHE_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for MSC_CACHECMD */
#define MSC_CACHECMD_INVCACHE_DEFAULT                 (_MSC_CACHECMD_INVCACHE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_CACHECMD */
#define MSC_CACHECMD_STARTPC                          (0x1UL << 1)                          /**< Start Performance Counters */
#define _MSC_CACHECMD_STARTPC_SHIFT                   1                                     /**< Shift value for MSC_STARTPC */
#define _MSC_CACHECMD_STARTPC_MASK                    0x2UL                                 /**< Bit mask for MSC_STARTPC */
#define _MSC_CACHECMD_STARTPC_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for MSC_CACHECMD */
#define MSC_CACHECMD_STARTPC_DEFAULT                  (_MSC_CACHECMD_STARTPC_DEFAULT << 1)  /**< Shifted mode DEFAULT for MSC_CACHECMD */
#define MSC_CACHECMD_STOPPC                           (0x1UL << 2)                          /**< Stop Performance Counters */
#define _MSC_CACHECMD_STOPPC_SHIFT                    2                                     /**< Shift value for MSC_STOPPC */
#define _MSC_CACHECMD_STOPPC_MASK                     0x4UL                                 /**< Bit mask for MSC_STOPPC */
#define _MSC_CACHECMD_STOPPC_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for MSC_CACHECMD */
#define MSC_CACHECMD_STOPPC_DEFAULT                   (_MSC_CACHECMD_STOPPC_DEFAULT << 2)   /**< Shifted mode DEFAULT for MSC_CACHECMD */

/* Bit fields for MSC CACHEHITS */
#define _MSC_CACHEHITS_RESETVALUE                     0x00000000UL                            /**< Default value for MSC_CACHEHITS */
#define _MSC_CACHEHITS_MASK                           0x000FFFFFUL                            /**< Mask for MSC_CACHEHITS */
#define _MSC_CACHEHITS_CACHEHITS_SHIFT                0                                       /**< Shift value for MSC_CACHEHITS */
#define _MSC_CACHEHITS_CACHEHITS_MASK                 0xFFFFFUL                               /**< Bit mask for MSC_CACHEHITS */
#define _MSC_CACHEHITS_CACHEHITS_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for MSC_CACHEHITS */
#define MSC_CACHEHITS_CACHEHITS_DEFAULT               (_MSC_CACHEHITS_CACHEHITS_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_CACHEHITS */

/* Bit fields for MSC CACHEMISSES */
#define _MSC_CACHEMISSES_RESETVALUE                   0x00000000UL                                /**< Default value for MSC_CACHEMISSES */
#define _MSC_CACHEMISSES_MASK                         0x000FFFFFUL                                /**< Mask for MSC_CACHEMISSES */
#define _MSC_CACHEMISSES_CACHEMISSES_SHIFT            0                                           /**< Shift value for MSC_CACHEMISSES */
#define _MSC_CACHEMISSES_CACHEMISSES_MASK             0xFFFFFUL                                   /**< Bit mask for MSC_CACHEMISSES */
#define _MSC_CACHEMISSES_CACHEMISSES_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MSC_CACHEMISSES */
#define MSC_CACHEMISSES_CACHEMISSES_DEFAULT           (_MSC_CACHEMISSES_CACHEMISSES_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_CACHEMISSES */

/* Bit fields for MSC MASSLOCK */
#define _MSC_MASSLOCK_RESETVALUE                      0x00000001UL                          /**< Default value for MSC_MASSLOCK */
#define _MSC_MASSLOCK_MASK                            0x0000FFFFUL                          /**< Mask for MSC_MASSLOCK */
#define _MSC_MASSLOCK_LOCKKEY_SHIFT                   0                                     /**< Shift value for MSC_LOCKKEY */
#define _MSC_MASSLOCK_LOCKKEY_MASK                    0xFFFFUL                              /**< Bit mask for MSC_LOCKKEY */
#define _MSC_MASSLOCK_LOCKKEY_UNLOCKED                0x00000000UL                          /**< Mode UNLOCKED for MSC_MASSLOCK */
#define _MSC_MASSLOCK_LOCKKEY_LOCK                    0x00000000UL                          /**< Mode LOCK for MSC_MASSLOCK */
#define _MSC_MASSLOCK_LOCKKEY_DEFAULT                 0x00000001UL                          /**< Mode DEFAULT for MSC_MASSLOCK */
#define _MSC_MASSLOCK_LOCKKEY_LOCKED                  0x00000001UL                          /**< Mode LOCKED for MSC_MASSLOCK */
#define _MSC_MASSLOCK_LOCKKEY_UNLOCK                  0x0000631AUL                          /**< Mode UNLOCK for MSC_MASSLOCK */
#define MSC_MASSLOCK_LOCKKEY_UNLOCKED                 (_MSC_MASSLOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for MSC_MASSLOCK */
#define MSC_MASSLOCK_LOCKKEY_LOCK                     (_MSC_MASSLOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for MSC_MASSLOCK */
#define MSC_MASSLOCK_LOCKKEY_DEFAULT                  (_MSC_MASSLOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_MASSLOCK */
#define MSC_MASSLOCK_LOCKKEY_LOCKED                   (_MSC_MASSLOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for MSC_MASSLOCK */
#define MSC_MASSLOCK_LOCKKEY_UNLOCK                   (_MSC_MASSLOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for MSC_MASSLOCK */

/* Bit fields for MSC STARTUP */
#define _MSC_STARTUP_RESETVALUE                       0x1300104DUL                         /**< Default value for MSC_STARTUP */
#define _MSC_STARTUP_MASK                             0x773FF3FFUL                         /**< Mask for MSC_STARTUP */
#define _MSC_STARTUP_STDLY0_SHIFT                     0                                    /**< Shift value for MSC_STDLY0 */
#define _MSC_STARTUP_STDLY0_MASK                      0x3FFUL                              /**< Bit mask for MSC_STDLY0 */
#define _MSC_STARTUP_STDLY0_DEFAULT                   0x0000004DUL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STDLY0_DEFAULT                    (_MSC_STARTUP_STDLY0_DEFAULT << 0)   /**< Shifted mode DEFAULT for MSC_STARTUP */
#define _MSC_STARTUP_STDLY1_SHIFT                     12                                   /**< Shift value for MSC_STDLY1 */
#define _MSC_STARTUP_STDLY1_MASK                      0x3FF000UL                           /**< Bit mask for MSC_STDLY1 */
#define _MSC_STARTUP_STDLY1_DEFAULT                   0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STDLY1_DEFAULT                    (_MSC_STARTUP_STDLY1_DEFAULT << 12)  /**< Shifted mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_ASTWAIT                           (0x1UL << 24)                        /**< Active Startup Wait */
#define _MSC_STARTUP_ASTWAIT_SHIFT                    24                                   /**< Shift value for MSC_ASTWAIT */
#define _MSC_STARTUP_ASTWAIT_MASK                     0x1000000UL                          /**< Bit mask for MSC_ASTWAIT */
#define _MSC_STARTUP_ASTWAIT_DEFAULT                  0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_ASTWAIT_DEFAULT                   (_MSC_STARTUP_ASTWAIT_DEFAULT << 24) /**< Shifted mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STWSEN                            (0x1UL << 25)                        /**< Startup Waitstates Enable */
#define _MSC_STARTUP_STWSEN_SHIFT                     25                                   /**< Shift value for MSC_STWSEN */
#define _MSC_STARTUP_STWSEN_MASK                      0x2000000UL                          /**< Bit mask for MSC_STWSEN */
#define _MSC_STARTUP_STWSEN_DEFAULT                   0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STWSEN_DEFAULT                    (_MSC_STARTUP_STWSEN_DEFAULT << 25)  /**< Shifted mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STWSAEN                           (0x1UL << 26)                        /**< Startup Waitstates Always Enable */
#define _MSC_STARTUP_STWSAEN_SHIFT                    26                                   /**< Shift value for MSC_STWSAEN */
#define _MSC_STARTUP_STWSAEN_MASK                     0x4000000UL                          /**< Bit mask for MSC_STWSAEN */
#define _MSC_STARTUP_STWSAEN_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STWSAEN_DEFAULT                   (_MSC_STARTUP_STWSAEN_DEFAULT << 26) /**< Shifted mode DEFAULT for MSC_STARTUP */
#define _MSC_STARTUP_STWS_SHIFT                       28                                   /**< Shift value for MSC_STWS */
#define _MSC_STARTUP_STWS_MASK                        0x70000000UL                         /**< Bit mask for MSC_STWS */
#define _MSC_STARTUP_STWS_DEFAULT                     0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP */
#define MSC_STARTUP_STWS_DEFAULT                      (_MSC_STARTUP_STWS_DEFAULT << 28)    /**< Shifted mode DEFAULT for MSC_STARTUP */

/* Bit fields for MSC CMD */
#define _MSC_CMD_RESETVALUE                           0x00000000UL                  /**< Default value for MSC_CMD */
#define _MSC_CMD_MASK                                 0x00000001UL                  /**< Mask for MSC_CMD */
#define MSC_CMD_PWRUP                                 (0x1UL << 0)                  /**< Flash Power Up Command */
#define _MSC_CMD_PWRUP_SHIFT                          0                             /**< Shift value for MSC_PWRUP */
#define _MSC_CMD_PWRUP_MASK                           0x1UL                         /**< Bit mask for MSC_PWRUP */
#define _MSC_CMD_PWRUP_DEFAULT                        0x00000000UL                  /**< Mode DEFAULT for MSC_CMD */
#define MSC_CMD_PWRUP_DEFAULT                         (_MSC_CMD_PWRUP_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_CMD */

/* Bit fields for MSC BOOTLOADERCTRL */
#define _MSC_BOOTLOADERCTRL_RESETVALUE                0x00000000UL                              /**< Default value for MSC_BOOTLOADERCTRL */
#define _MSC_BOOTLOADERCTRL_MASK                      0x00000003UL                              /**< Mask for MSC_BOOTLOADERCTRL */
#define MSC_BOOTLOADERCTRL_BLRDIS                     (0x1UL << 0)                              /**< Flash Bootloader Read Disable */
#define _MSC_BOOTLOADERCTRL_BLRDIS_SHIFT              0                                         /**< Shift value for MSC_BLRDIS */
#define _MSC_BOOTLOADERCTRL_BLRDIS_MASK               0x1UL                                     /**< Bit mask for MSC_BLRDIS */
#define _MSC_BOOTLOADERCTRL_BLRDIS_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MSC_BOOTLOADERCTRL */
#define MSC_BOOTLOADERCTRL_BLRDIS_DEFAULT             (_MSC_BOOTLOADERCTRL_BLRDIS_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_BOOTLOADERCTRL */
#define MSC_BOOTLOADERCTRL_BLWDIS                     (0x1UL << 1)                              /**< Flash Bootloader Write/Erase Disable */
#define _MSC_BOOTLOADERCTRL_BLWDIS_SHIFT              1                                         /**< Shift value for MSC_BLWDIS */
#define _MSC_BOOTLOADERCTRL_BLWDIS_MASK               0x2UL                                     /**< Bit mask for MSC_BLWDIS */
#define _MSC_BOOTLOADERCTRL_BLWDIS_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MSC_BOOTLOADERCTRL */
#define MSC_BOOTLOADERCTRL_BLWDIS_DEFAULT             (_MSC_BOOTLOADERCTRL_BLWDIS_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_BOOTLOADERCTRL */

/* Bit fields for MSC AAPUNLOCKCMD */
#define _MSC_AAPUNLOCKCMD_RESETVALUE                  0x00000000UL                               /**< Default value for MSC_AAPUNLOCKCMD */
#define _MSC_AAPUNLOCKCMD_MASK                        0x00000001UL                               /**< Mask for MSC_AAPUNLOCKCMD */
#define MSC_AAPUNLOCKCMD_UNLOCKAAP                    (0x1UL << 0)                               /**< Software Unlock AAP Command */
#define _MSC_AAPUNLOCKCMD_UNLOCKAAP_SHIFT             0                                          /**< Shift value for MSC_UNLOCKAAP */
#define _MSC_AAPUNLOCKCMD_UNLOCKAAP_MASK              0x1UL                                      /**< Bit mask for MSC_UNLOCKAAP */
#define _MSC_AAPUNLOCKCMD_UNLOCKAAP_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for MSC_AAPUNLOCKCMD */
#define MSC_AAPUNLOCKCMD_UNLOCKAAP_DEFAULT            (_MSC_AAPUNLOCKCMD_UNLOCKAAP_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_AAPUNLOCKCMD */

/* Bit fields for MSC CACHECONFIG0 */
#define _MSC_CACHECONFIG0_RESETVALUE                  0x00000003UL                                      /**< Default value for MSC_CACHECONFIG0 */
#define _MSC_CACHECONFIG0_MASK                        0x00000003UL                                      /**< Mask for MSC_CACHECONFIG0 */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_SHIFT          0                                                 /**< Shift value for MSC_CACHELPLEVEL */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_MASK           0x3UL                                             /**< Bit mask for MSC_CACHELPLEVEL */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_BASE           0x00000000UL                                      /**< Mode BASE for MSC_CACHECONFIG0 */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_ADVANCED       0x00000001UL                                      /**< Mode ADVANCED for MSC_CACHECONFIG0 */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_DEFAULT        0x00000003UL                                      /**< Mode DEFAULT for MSC_CACHECONFIG0 */
#define _MSC_CACHECONFIG0_CACHELPLEVEL_MINACTIVITY    0x00000003UL                                      /**< Mode MINACTIVITY for MSC_CACHECONFIG0 */
#define MSC_CACHECONFIG0_CACHELPLEVEL_BASE            (_MSC_CACHECONFIG0_CACHELPLEVEL_BASE << 0)        /**< Shifted mode BASE for MSC_CACHECONFIG0 */
#define MSC_CACHECONFIG0_CACHELPLEVEL_ADVANCED        (_MSC_CACHECONFIG0_CACHELPLEVEL_ADVANCED << 0)    /**< Shifted mode ADVANCED for MSC_CACHECONFIG0 */
#define MSC_CACHECONFIG0_CACHELPLEVEL_DEFAULT         (_MSC_CACHECONFIG0_CACHELPLEVEL_DEFAULT << 0)     /**< Shifted mode DEFAULT for MSC_CACHECONFIG0 */
#define MSC_CACHECONFIG0_CACHELPLEVEL_MINACTIVITY     (_MSC_CACHECONFIG0_CACHELPLEVEL_MINACTIVITY << 0) /**< Shifted mode MINACTIVITY for MSC_CACHECONFIG0 */

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

static inline void BUS_RegMaskedSet(volatile uint32_t *addr,
                                      uint32_t mask)
{
#if defined(PER_BITSET_MEM_BASE) && !defined(ZUNO_PREPROC_PHASE)
  uint32_t aliasAddr = PER_BITSET_MEM_BASE + ((uint32_t)addr - PER_MEM_BASE);
  *(volatile uint32_t *)aliasAddr = mask;
#else
  *addr |= mask;
#endif
}

static inline void BUS_RegMaskedClear(volatile uint32_t *addr,
                                        uint32_t mask)
{
#if defined(PER_BITCLR_MEM_BASE) && !defined(ZUNO_PREPROC_PHASE)
  uint32_t aliasAddr = PER_BITCLR_MEM_BASE + ((uint32_t)addr - PER_MEM_BASE);
  *(volatile uint32_t *)aliasAddr = mask;
#else
  *addr &= ~mask;
#endif
}

static inline void BUS_RegBitWrite(volatile uint32_t *addr,
                                     unsigned int bit,
                                     unsigned int val)
{
#if defined(BITBAND_PER_BASE) && !defined(ZUNO_PREPROC_PHASE)
  uint32_t aliasAddr =
    BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);

  *(volatile uint32_t *)aliasAddr = (uint32_t)val;
#else
  uint32_t tmp = *addr;

  /* Make sure val is not more than 1, because we only want to set one bit. */
  *addr = (tmp & ~(1 << bit)) | ((val & 1) << bit);
#endif
}
static inline void BUS_RegMaskedWrite(volatile uint32_t *addr,
                                        uint32_t mask,
                                        uint32_t val)
{
#if defined(PER_BITCLR_MEM_BASE)
  BUS_RegMaskedClear(addr, mask);
  BUS_RegMaskedSet(addr, val);
#else
  *addr = (*addr & ~mask) | val;
#endif
}
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

/**************************************************************************//**
 * @defgroup EFR32FG13P_EMU EMU
 * @{
 * @brief EFR32FG13P_EMU Register Declaration
 *****************************************************************************/
/** EMU Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;                  /**< Control Register  */
  __IM uint32_t  STATUS;                /**< Status Register  */
  __IOM uint32_t LOCK;                  /**< Configuration Lock Register  */
  __IOM uint32_t RAM0CTRL;              /**< Memory Control Register  */
  __IOM uint32_t CMD;                   /**< Command Register  */

  uint32_t       RESERVED0[1];          /**< Reserved for future use **/
  __IOM uint32_t EM4CTRL;               /**< EM4 Control Register  */
  __IOM uint32_t TEMPLIMITS;            /**< Temperature Limits for Interrupt Generation  */
  __IM uint32_t  TEMP;                  /**< Value of Last Temperature Measurement  */
  __IM uint32_t  IF;                    /**< Interrupt Flag Register  */
  __IOM uint32_t IFS;                   /**< Interrupt Flag Set Register  */
  __IOM uint32_t IFC;                   /**< Interrupt Flag Clear Register  */
  __IOM uint32_t IEN;                   /**< Interrupt Enable Register  */
  __IOM uint32_t PWRLOCK;               /**< Regulator and Supply Lock Register  */

  uint32_t       RESERVED1[1];          /**< Reserved for future use **/
  __IOM uint32_t PWRCTRL;               /**< Power Control Register  */
  __IOM uint32_t DCDCCTRL;              /**< DCDC Control  */

  uint32_t       RESERVED2[2];          /**< Reserved for future use **/
  __IOM uint32_t DCDCMISCCTRL;          /**< DCDC Miscellaneous Control Register  */
  __IOM uint32_t DCDCZDETCTRL;          /**< DCDC Power Train NFET Zero Current Detector Control Register  */
  __IOM uint32_t DCDCCLIMCTRL;          /**< DCDC Power Train PFET Current Limiter Control Register  */
  __IOM uint32_t DCDCLNCOMPCTRL;        /**< DCDC Low Noise Compensator Control Register  */
  __IOM uint32_t DCDCLNVCTRL;           /**< DCDC Low Noise Voltage Register  */

  uint32_t       RESERVED3[1];          /**< Reserved for future use **/
  __IOM uint32_t DCDCLPVCTRL;           /**< DCDC Low Power Voltage Register  */

  uint32_t       RESERVED4[1];          /**< Reserved for future use **/
  __IOM uint32_t DCDCLPCTRL;            /**< DCDC Low Power Control Register  */
  __IOM uint32_t DCDCLNFREQCTRL;        /**< DCDC Low Noise Controller Frequency Control  */

  uint32_t       RESERVED5[1];          /**< Reserved for future use **/
  __IM uint32_t  DCDCSYNC;              /**< DCDC Read Status Register  */

  uint32_t       RESERVED6[5];          /**< Reserved for future use **/
  __IOM uint32_t VMONAVDDCTRL;          /**< VMON AVDD Channel Control  */
  __IOM uint32_t VMONALTAVDDCTRL;       /**< Alternate VMON AVDD Channel Control  */
  __IOM uint32_t VMONDVDDCTRL;          /**< VMON DVDD Channel Control  */
  __IOM uint32_t VMONIO0CTRL;           /**< VMON IOVDD0 Channel Control  */

  uint32_t       RESERVED7[4];          /**< Reserved for future use **/
  __IOM uint32_t RAM1CTRL;              /**< Memory Control Register  */
  __IOM uint32_t RAM2CTRL;              /**< Memory Control Register  */

  uint32_t       RESERVED8[10];         /**< Reserved for future use **/
  __IOM uint32_t DCDCLPEM01CFG;         /**< Configuration Bits for Low Power Mode to Be Applied During EM01, This Field is Only Relevant If LP Mode is Used in EM01  */

  uint32_t       RESERVED9[4];          /**< Reserved for future use **/
  __IOM uint32_t EM23PERNORETAINCMD;    /**< Clears Corresponding Bits in EM23PERNORETAINSTATUS Unlocking Access to Peripheral  */
  __IM uint32_t  EM23PERNORETAINSTATUS; /**< Status Indicating If Peripherals Were Powered Down in EM23, Subsequently Locking Access to It  */
  __IOM uint32_t EM23PERNORETAINCTRL;   /**< When Set Corresponding Peripherals May Get Powered Down in EM23  */
} EMU_TypeDef;                          /** @} */
/**************************************************************************//**
 * @addtogroup EFR32FG13P_EMU
 * @{
 * @defgroup EFR32FG13P_EMU_BitFields  EMU Bit Fields
 * @{
 *****************************************************************************/

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
#define EMU_CTRL_EM23VSCALEAUTOWSEN                          (0x1UL << 4)                                /**< Automatically Configures Flash, Ram and Frequency to Wakeup From EM2 or EM3 at Low Voltage */
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
#define EMU_EM23PERNORETAINCTRL_DAC0DIS                      (0x1UL << 7)                                         /**< Allow Power Down of DAC0 During EM23 */
#define _EMU_EM23PERNORETAINCTRL_DAC0DIS_SHIFT               7                                                    /**< Shift value for EMU_DAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_DAC0DIS_MASK                0x80UL                                               /**< Bit mask for EMU_DAC0DIS */
#define _EMU_EM23PERNORETAINCTRL_DAC0DIS_DEFAULT             0x00000000UL                                         /**< Mode DEFAULT for EMU_EM23PERNORETAINCTRL */
#define EMU_EM23PERNORETAINCTRL_DAC0DIS_DEFAULT              (_EMU_EM23PERNORETAINCTRL_DAC0DIS_DEFAULT << 7)      /**< Shifted mode DEFAULT for EMU_EM23PERNORETAINCTRL */
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

/** @} */
/** @} End of group EFR32FG13P_EMU */
/** @} End of group Parts */
/**************************************************************************//**
 * @defgroup EFR32FG13P_CSEN CSEN
 * @{
 * @brief EFR32FG13P_CSEN Register Declaration
 *****************************************************************************/
/** CSEN Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;          /**< Control  */
  __IOM uint32_t TIMCTRL;       /**< Timing Control  */
  __IOM uint32_t CMD;           /**< Command  */
  __IM uint32_t  STATUS;        /**< Status  */
  __IOM uint32_t PRSSEL;        /**< PRS Select  */
  __IOM uint32_t DATA;          /**< Output Data  */
  __IOM uint32_t SCANMASK0;     /**< Scan Channel Mask 0  */
  __IOM uint32_t SCANINPUTSEL0; /**< Scan Input Selection 0  */
  __IOM uint32_t SCANMASK1;     /**< Scan Channel Mask 1  */
  __IOM uint32_t SCANINPUTSEL1; /**< Scan Input Selection 1  */
  __IM uint32_t  APORTREQ;      /**< APORT Request Status  */
  __IM uint32_t  APORTCONFLICT; /**< APORT Request Conflict  */
  __IOM uint32_t CMPTHR;        /**< Comparator Threshold  */
  __IOM uint32_t EMA;           /**< Exponential Moving Average  */
  __IOM uint32_t EMACTRL;       /**< Exponential Moving Average Control  */
  __IOM uint32_t SINGLECTRL;    /**< Single Conversion Control  */
  __IOM uint32_t DMBASELINE;    /**< Delta Modulation Baseline  */
  __IOM uint32_t DMCFG;         /**< Delta Modulation Configuration  */
  __IOM uint32_t ANACTRL;       /**< Analog Control  */

  uint32_t       RESERVED0[2];  /**< Reserved for future use **/
  __IM uint32_t  IF;            /**< Interrupt Flag  */
  __IOM uint32_t IFS;           /**< Interrupt Flag Set  */
  __IOM uint32_t IFC;           /**< Interrupt Flag Clear  */
  __IOM uint32_t IEN;           /**< Interrupt Enable  */
} CSEN_TypeDef;                 /** @} */

#define NVIC_USER_IRQ_OFFSET          16

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
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb 0xF":::"memory");
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

#endif // ZGECKO