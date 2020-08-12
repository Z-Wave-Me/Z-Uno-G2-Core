#if (!defined(ZGECKO))
#define ZGECKO

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define __STATIC_INLINE static inline
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

enum{
    cmuClock_HFPER = CMU_CLOCK_TYPE_HFPER,
    cmuClock_ADC0 = CMU_CLOCK_TYPE_ADC0,
    cmuClock_TIMER0 = CMU_CLOCK_TYPE_TIMER0,
    cmuClock_TIMER1 = CMU_CLOCK_TYPE_TIMER1,
    cmuClock_I2C0 = CMU_CLOCK_TYPE_I2C0,
    cmuClock_I2C1 = CMU_CLOCK_TYPE_I2C1,
    cmuClock_USART0 = CMU_CLOCK_TYPE_USART0,
    cmuClock_USART1 = CMU_CLOCK_TYPE_USART1,
    cmuClock_USART2 = CMU_CLOCK_TYPE_USART2,
    cmuClock_GPIO = CMU_CLOCK_TYPE_GPIO
    
};

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

#define CMU_ClockFreqGet(C) ((uint32_t)zunoSysCall(ZUNO_FUNC_GECKOEXT_CMUCLOCK, 2, CMU_CLOCK_SUBFUNC_GETFREQ, C))
#define CMU_ClockEnable(C, E) zunoSysCall(ZUNO_FUNC_GECKOEXT_CMUCLOCK, 3, CMU_CLOCK_SUBFUNC_ENABLE, C, E)

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

#endif // ZGECKO