#ifndef CRTX_MSC_H
#define CRTX_MSC_H

#include "ZGecko.h"

/* *INDENT-OFF* */
/***************************************************************************//**
 * @addtogroup emlib
 * @{
 * @addtogroup RAMFUNC
 * @brief RAM code support
 * @details
 *  Provides support for executing code from RAM.
 *  Provides a unified method to manage RAM code across all supported tools.
 * @{

  @note
   Other cross-compiler support macros are implemented in @ref COMMON.

  @note
    Functions executing from RAM should not be declared as static.

  @warning
    Standard library facilities are available to the tool with GCC in hosted
	mode (default), regardless of the section attribute. Calls to standard
    libraries placed in the default section may therefore occur. To disable
    hosted mode, add '-ffreestanding' to the build command line. This is the
    only way to guarantee no calls to standard libraries with GCC.
    Read more at www.gcc.gnu.org/onlinedocs/gcc-5.3.0/gcc/Standards.html

  @warning
    Keil/ARM uVision users must add a section named "ram_code" in their linker
    scatter file. This section must be in RAM memory. Look in the MCU SDK for
    example scatter files (ram_code.sct).

  @n @section ramfunc_usage Usage

  In your .h file:
  @verbatim
  #include "em_ramfunc.h"

  SL_RAMFUNC_DECLARATOR
  void MyPrint(const char* string);
  @endverbatim

  Issues have been observed with armgcc when there is no declarator. It is
  recommended to have a declarator also for internal functions, but move the
  declarator to the .c file.

  In your .c file:
  @verbatim
  #include "em_ramfunc.h"

  SL_RAMFUNC_DEFINITION_BEGIN
  void MyPrint(const char* string)
  {
  ...
  }
  SL_RAMFUNC_DEFINITION_END
  @endverbatim

 ******************************************************************************/
/* *INDENT-ON* */

/*******************************************************************************
 ******************************   DEFINES    ***********************************
 ******************************************************************************/

/**
 * @brief
 *    This define is not present by default. By compiling with define
 *    @ref SL_RAMFUNC_DISABLE, code placed in RAM by SL_RAMFUNC macros
 *    will be placed in default code space (Flash) instead.
 *
 * @note
 *    This define is not present by default.
 */
#if defined(DOXY_DOC_ONLY)
#define SL_RAMFUNC_DISABLE
#endif

#if defined(SL_RAMFUNC_DISABLE)
/** @brief Compiler ported function declarator for RAM code. */
#define SL_RAMFUNC_DECLARATOR

/** @brief Compiler ported function definition begin marker for RAM code. */
#define SL_RAMFUNC_DEFINITION_BEGIN

/** @brief Compiler ported function definition end marker for RAM code. */
#define SL_RAMFUNC_DEFINITION_END

#elif defined(__CC_ARM)
/* MDK-ARM compiler */
#define SL_RAMFUNC_DECLARATOR
#define SL_RAMFUNC_DEFINITION_BEGIN    _Pragma("arm section code=\"ram_code\"")
#define SL_RAMFUNC_DEFINITION_END      _Pragma("arm section code")

#elif defined(__ICCARM__)
/* IAR Embedded Workbench */
#define SL_RAMFUNC_DECLARATOR          __ramfunc
#define SL_RAMFUNC_DEFINITION_BEGIN    SL_RAMFUNC_DECLARATOR
#define SL_RAMFUNC_DEFINITION_END

#elif defined(__GNUC__) && (defined(__CROSSWORKS_ARM) || defined(__SES_ARM))
/* Rowley Crossworks and Segger Embedded Studio */
#define SL_RAMFUNC_DECLARATOR          __attribute__ ((section(".fast")))
#define SL_RAMFUNC_DEFINITION_BEGIN    SL_RAMFUNC_DECLARATOR
#define SL_RAMFUNC_DEFINITION_END

#elif defined(__GNUC__)
/* Simplicity Studio, Atollic and Vanilla armgcc */
#define SL_RAMFUNC_DECLARATOR          __attribute__ ((section(".ram")))
#define SL_RAMFUNC_DEFINITION_BEGIN    SL_RAMFUNC_DECLARATOR
#define SL_RAMFUNC_DEFINITION_END

#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Deprecated macro names */
#define RAMFUNC_DECLARATOR          SL_RAMFUNC_DECLARATOR
#define RAMFUNC_DEFINITION_BEGIN    SL_RAMFUNC_DEFINITION_BEGIN
#define RAMFUNC_DEFINITION_END      SL_RAMFUNC_DEFINITION_END
/** @endcond */

/** @} (end addtogroup RAMFUNC) */
/** @} (end addtogroup emlib) */

/***************************************************************************//**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @defgroup ZGM13_MSC MSC
 * @{
 * @brief ZGM13_MSC Register Declaration
 ******************************************************************************/
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

/***************************************************************************//**
 * @addtogroup emlib
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup MSC
 * @brief Memory System Controller API.
 * @details
 *  Contains functions to control the MSC, primarily the Flash.
 *  Users can perform Flash memory write and erase operations, as well as
 *  optimization of the CPU instruction fetch interface for the application.
 *  Available instruction fetch features depends on the MCU or SoC family, but
 *  features such as instruction pre-fetch, cache, and configurable branch prediction
 *  are typically available.
 *
 * @note Flash wait-state configuration is handled by @ref CMU module.
 *       When core clock configuration is changed by a call to functions such as
 *       @ref CMU_ClockSelectSet() or @ref CMU_HFRCOBandSet(), then Flash wait-state
 *       configuration is also updated.
 *
 *  MSC resets into a safe state. To initialize the instruction interface
 *  to recommended settings:
 *  @include em_msc_init_exec.c
 *
 * @note The optimal configuration is highly application dependent. Performance
 *       benchmarking is supported by most families. See @ref MSC_StartCacheMeasurement()
 *       and @ref MSC_GetCacheMeasurement() for more details.
 *
 * @note
 *   The flash write and erase runs from RAM on the EFM32G devices. On all other
 *   devices the flash write and erase functions run from flash.
 *
 * @note
 *   Flash erase may add ms of delay to interrupt latency if executing from Flash.
 *
 * Flash write and erase operations are supported by @ref MSC_WriteWord(),
 * @ref MSC_ErasePage(), and @ref MSC_MassErase().
 * Mass erase is supported for MCU and SoC families with larger Flash sizes.
 *
 * @note
 *  @ref MSC_Init() must be called prior to any Flash write or erase operation.
 *
 *  The following steps are necessary to perform a page erase and write:
 *  @include em_msc_erase_write.c
 *
 * @deprecated
 *   The configuration called EM_MSC_RUN_FROM_FLASH is deprecated. This was
 *   previously used for allocating the flash write functions in either flash
 *   or RAM. Flash write functions are now placed in flash on all devices
 *   except the EFM32G automatically.
 *
 * @deprecated
 *   The function called @ref MSC_WriteWordFast() is deprecated.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 *************************   DEFINES   *****************************************
 ******************************************************************************/

/**
 * @brief
 *    Timeout used while waiting for Flash to become ready after a write.
 *    This number indicates the number of iterations to perform before
 *    issuing a timeout.
 *
 * @note
 *    Timeout is set very large (in the order of 100x longer than
 *    necessary). This is to avoid any corner case.
 */
#define MSC_PROGRAM_TIMEOUT    10000000ul

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#if defined(_EFM32_GECKO_FAMILY) || defined(_SILICON_LABS_32B_SERIES_2)
#define MSC_RAMFUNC_DECLARATOR          SL_RAMFUNC_DECLARATOR
#define MSC_RAMFUNC_DEFINITION_BEGIN    SL_RAMFUNC_DEFINITION_BEGIN
#define MSC_RAMFUNC_DEFINITION_END      SL_RAMFUNC_DEFINITION_END
#else
#define MSC_RAMFUNC_DECLARATOR
#define MSC_RAMFUNC_DEFINITION_BEGIN
#define MSC_RAMFUNC_DEFINITION_END
#endif
/** @endcond */

/*******************************************************************************
 *************************   TYPEDEFS   ****************************************
 ******************************************************************************/

/** Return codes for writing/erasing Flash. */
typedef enum {
  mscReturnOk          =  0, /**< Flash write/erase successful. */
  mscReturnInvalidAddr = -1, /**< Invalid address. Write to an address that is not Flash. */
  mscReturnLocked      = -2, /**< Flash address is locked. */
  mscReturnTimeOut     = -3, /**< Timeout while writing to Flash. */
  mscReturnUnaligned   = -4  /**< Unaligned access to Flash. */
} MSC_Status_TypeDef;

#if defined(_MSC_READCTRL_BUSSTRATEGY_MASK)
/** Strategy for prioritized bus access. */
typedef enum {
  mscBusStrategyCPU = MSC_READCTRL_BUSSTRATEGY_CPU,       /**< Prioritize CPU bus accesses. */
  mscBusStrategyDMA = MSC_READCTRL_BUSSTRATEGY_DMA,       /**< Prioritize DMA bus accesses. */
  mscBusStrategyDMAEM1 = MSC_READCTRL_BUSSTRATEGY_DMAEM1, /**< Prioritize DMAEM1 for bus accesses. */
  mscBusStrategyNone = MSC_READCTRL_BUSSTRATEGY_NONE      /**< No unit has bus priority. */
} MSC_BusStrategy_Typedef;
#endif

#if defined(MSC_READCTRL_DOUTBUFEN)
/** Code execution configuration */
typedef struct {
  bool doutBufEn;       /**< Flash dout pipeline buffer enable */
} MSC_ExecConfig_TypeDef;

/** Default MSC ExecConfig initialization */
#define MSC_EXECCONFIG_DEFAULT \
  {                            \
    false,                     \
  }

#else
/** Code execution configuration. */
typedef struct {
  bool scbtEn;          /**< Enable Suppressed Conditional Branch Target Prefetch. */
  bool prefetchEn;      /**< Enable MSC prefetching. */
  bool ifcDis;          /**< Disable instruction cache. */
  bool aiDis;           /**< Disable automatic cache invalidation on write or erase. */
  bool iccDis;          /**< Disable automatic caching of fetches in interrupt context. */
  bool useHprot;        /**< Use ahb_hprot to determine if the instruction is cacheable or not. */
} MSC_ExecConfig_TypeDef;

/** Default MSC ExecConfig initialization. */
#define MSC_EXECCONFIG_DEFAULT \
  {                            \
    false,                     \
    true,                      \
    false,                     \
    false,                     \
    false,                     \
    false,                     \
  }
#endif

#if defined(_MSC_ECCCTRL_MASK) || defined(_SYSCFG_DMEM0ECCCTRL_MASK)

#if defined(_SILICON_LABS_32B_SERIES_1_CONFIG_1)
/** EFM32GG11B incorporates 2 memory banks including ECC support. */
#define MSC_ECC_BANKS  (2)

/** Default MSC EccConfig initialization. */
#define MSC_ECCCONFIG_DEFAULT \
  {                           \
    { false, false },         \
    { 0, 1 },                 \
  }

#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_106)
/** EFM32GG12B incorporates 3 memory banks including ECC support. */
#define MSC_ECC_BANKS  (3)

/** Default MSC EccConfig initialization. */
#define MSC_ECCCONFIG_DEFAULT \
  {                           \
    { false, false, false },  \
    { 0, 1 },                 \
  }

#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
/** EFR32XG21 incorporates 1 memory bank including ECC support. */
#define MSC_ECC_BANKS  (1)
/** Default MSC EccConfig initialization */
#define MSC_ECCCONFIG_DEFAULT \
  {                           \
    { false },                \
    { 0, 1 },                 \
  }
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
/** EFR32XG21 incorporates 1 memory bank including ECC support. */
#define MSC_ECC_BANKS  (1)
/** Default MSC EccConfig initialization */
#define MSC_ECCCONFIG_DEFAULT \
  {                           \
    { false },                \
    { 0, 1 },                 \
  }
#else
#error Device not supported.
#endif

/** ECC configuration. */
typedef struct {
  bool     enableEccBank[MSC_ECC_BANKS]; /**< Array of bools to enable/disable
                                            Error Correcting Code (ECC) for
                                            each RAM bank that supports ECC on
                                            the device. */
  uint32_t dmaChannels[2];               /**< Array of 2 DMA channel numbers to
                                            use for ECC initialization. */
} MSC_EccConfig_TypeDef;

#endif /* #if defined(_MSC_ECCCTRL_MASK) */

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Deprecated type names. */
#define mscBusStrategy_Typedef MSC_BusStrategy_Typedef
#define msc_Return_TypeDef MSC_Status_TypeDef
/** @endcond */

/***************************************************************************//**
 * @brief
 *    Clear one or more pending MSC interrupts.
 *
 * @param[in] flags
 *    Pending MSC intterupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void MSC_IntClear(uint32_t flags)
{
#if defined(MSC_HAS_SET_CLEAR)
  MSC->IF_CLR = flags;
#else
  MSC->IFC = flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Disable one or more MSC interrupts.
 *
 * @param[in] flags
 *   MSC interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void MSC_IntDisable(uint32_t flags)
{
#if defined(MSC_HAS_SET_CLEAR)
  MSC->IEN_CLR = flags;
#else
  MSC->IEN &= ~(flags);
#endif
}

/***************************************************************************//**
 * @brief
 *   Enable one or more MSC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. To ignore a pending interrupt, consider using
 *   MSC_IntClear() prior to enabling the interrupt.
 *
 * @param[in] flags
 *   MSC interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void MSC_IntEnable(uint32_t flags)
{
#if defined(MSC_HAS_SET_CLEAR)
  MSC->IEN_SET = flags;
#else
  MSC->IEN |= flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Get pending MSC interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   MSC interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t MSC_IntGet(void)
{
  return MSC->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending MSC interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled MSC interrupt sources.
 *   The return value is the bitwise AND of
 *   - the enabled interrupt sources in MSC_IEN and
 *   - the pending interrupt flags MSC_IF
 ******************************************************************************/
__STATIC_INLINE uint32_t MSC_IntGetEnabled(void)
{
  uint32_t ien;

  ien = MSC->IEN;
  return MSC->IF & ien;
}

/***************************************************************************//**
 * @brief
 *   Set one or more pending MSC interrupts from SW.
 *
 * @param[in] flags
 *   MSC interrupt sources to set to pending. Use a bitwise logic OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void MSC_IntSet(uint32_t flags)
{
#if defined(MSC_HAS_SET_CLEAR)
  MSC->IF_SET = flags;
#else
  MSC->IFS = flags;
#endif
}

#if defined(MSC_IF_CHOF) && defined(MSC_IF_CMOF)
/***************************************************************************//**
 * @brief
 *   Starts measuring cache hit ratio.
 * @details
 *   Starts performance counters. It is defined inline to
 *   minimize the impact of this code on the measurement itself.
 ******************************************************************************/
__STATIC_INLINE void MSC_StartCacheMeasurement(void)
{
  /* Clear CMOF and CHOF to catch these later. */
  MSC->IFC = MSC_IF_CHOF | MSC_IF_CMOF;

  /* Start performance counters. */
#if defined(_MSC_CACHECMD_MASK)
  MSC->CACHECMD = MSC_CACHECMD_STARTPC;
#else
  MSC->CMD = MSC_CMD_STARTPC;
#endif
}

/***************************************************************************//**
 * @brief
 *   Stops measuring hit rate.
 * @note
 *   Defined inline to minimize the impact of this
 *   code on the measurement itself.
 *   Only works for relatively short sections of code.
 *   To measure longer sections of code, implement an IRQ Handler for
 *   the CHOF and CMOF overflow interrupts. These overflows need to be
 *   counted and included in the total.
 *   Functions can then be implemented as follows:
 * @verbatim
 * volatile uint32_t hitOverflows
 * volatile uint32_t missOverflows
 *
 * void MSC_IRQHandler(void)
 * {
 *   uint32_t flags;
 *   flags = MSC->IF;
 *   if (flags & MSC_IF_CHOF) {
 *      MSC->IFC = MSC_IF_CHOF;
 *      hitOverflows++;
 *   }
 *   if (flags & MSC_IF_CMOF) {
 *     MSC->IFC = MSC_IF_CMOF;
 *     missOverflows++;
 *   }
 * }
 *
 * void startPerformanceCounters(void)
 * {
 *   hitOverflows = 0;
 *   missOverflows = 0;
 *
 *   MSC_IntEnable(MSC_IF_CHOF | MSC_IF_CMOF);
 *   NVIC_EnableIRQ(MSC_IRQn);
 *
 *   MSC_StartCacheMeasurement();
 * }
 * @endverbatim
 * @return
 *   Returns -1 if there has been no cache accesses.
 *   Returns -2 if there has been an overflow in the performance counters.
 *   If not, it will return the percentage of hits versus misses.
 ******************************************************************************/
__STATIC_INLINE int32_t MSC_GetCacheMeasurement(void)
{
  int32_t total;
  int32_t hits;
  /* Stop counter before computing hit-rate. */
#if defined(_MSC_CACHECMD_MASK)
  MSC->CACHECMD = MSC_CACHECMD_STOPPC;
#else
  MSC->CMD = MSC_CMD_STOPPC;
#endif

  /* Check for overflows in performance counters. */
  if (MSC->IF & (MSC_IF_CHOF | MSC_IF_CMOF)) {
    return -2;
  }

  hits  = MSC->CACHEHITS;
  total = MSC->CACHEMISSES + hits;

  /* To avoid a division by zero. */
  if (total == 0) {
    return -1;
  }

  return (hits * 100) / total;
}

/***************************************************************************//**
 * @brief
 *   Flush contents of instruction cache.
 ******************************************************************************/
__STATIC_INLINE void MSC_FlushCache(void)
{
#if defined(_MSC_CACHECMD_MASK)
  MSC->CACHECMD = MSC_CACHECMD_INVCACHE;
#else
  MSC->CMD = MSC_CMD_INVCACHE;
#endif
}

/***************************************************************************//**
 * @brief
 *   Enable or disable instruction cache functionality.
 * @param[in] enable
 *   Enable instruction cache. Default is on.
 ******************************************************************************/
__STATIC_INLINE void MSC_EnableCache(bool enable)
{
  BUS_RegBitWrite(&(MSC->READCTRL), _MSC_READCTRL_IFCDIS_SHIFT, !enable);
}

#if defined(MSC_READCTRL_ICCDIS)
/***************************************************************************//**
 * @brief
 *   Enable or disable instruction cache functionality in IRQs.
 * @param[in] enable
 *   Enable instruction cache. Default is on.
 ******************************************************************************/
__STATIC_INLINE void MSC_EnableCacheIRQs(bool enable)
{
  BUS_RegBitWrite(&(MSC->READCTRL), _MSC_READCTRL_ICCDIS_SHIFT, !enable);
}
#endif

/***************************************************************************//**
 * @brief
 *   Enable or disable instruction cache flushing when writing to flash.
 * @param[in] enable
 *   Enable automatic cache flushing. Default is on.
 ******************************************************************************/
__STATIC_INLINE void MSC_EnableAutoCacheFlush(bool enable)
{
  BUS_RegBitWrite(&(MSC->READCTRL), _MSC_READCTRL_AIDIS_SHIFT, !enable);
}
#endif /* defined( MSC_IF_CHOF ) && defined( MSC_IF_CMOF ) */

#if defined(_MSC_READCTRL_BUSSTRATEGY_MASK)
/***************************************************************************//**
 * @brief
 *   Configure which unit should get priority on system bus.
 * @param[in] mode
 *   Unit to prioritize bus accesses for.
 ******************************************************************************/
__STATIC_INLINE void MSC_BusStrategy(mscBusStrategy_Typedef mode)
{
  MSC->READCTRL = (MSC->READCTRL & ~(_MSC_READCTRL_BUSSTRATEGY_MASK)) | mode;
}
#endif

/*******************************************************************************
 *************************   PROTOTYPES   **************************************
 ******************************************************************************/
#if defined(_SILICON_LABS_32B_SERIES_2)
/***************************************************************************//**
 * @brief
 *   Initialize MSC module. Puts MSC hw in a known state.
 ******************************************************************************/
__STATIC_INLINE void MSC_Init(void)
{
#if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_SET = CMU_CLKEN1_MSC;
#endif
  // Unlock MSC
  MSC->LOCK = MSC_LOCK_LOCKKEY_UNLOCK;
  // Disable flash write
  MSC->WRITECTRL_CLR = MSC_WRITECTRL_WREN;
}

/***************************************************************************//**
 * @brief
 *   Turn off MSC flash write enable and lock MSC registers.
 ******************************************************************************/
__STATIC_INLINE void MSC_Deinit(void)
{
  // Unlock MSC
  MSC->LOCK = MSC_LOCK_LOCKKEY_UNLOCK;
  // Disable flash write
  MSC->WRITECTRL_CLR = MSC_WRITECTRL_WREN;
  // Lock MSC
  MSC->LOCK = MSC_LOCK_LOCKKEY_LOCK;
#if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_CLR = CMU_CLKEN1_MSC;
#endif
}

/***************************************************************************//**
 * @brief
 *   Set MSC code execution configuration
 *
 * @param[in] execConfig
 *   Code execution configuration
 ******************************************************************************/
__STATIC_INLINE void MSC_ExecConfigSet(MSC_ExecConfig_TypeDef *execConfig)
{
  uint32_t mscReadCtrl;

  mscReadCtrl = MSC->READCTRL & ~MSC_READCTRL_DOUTBUFEN;

  if (execConfig->doutBufEn) {
    mscReadCtrl |= MSC_READCTRL_DOUTBUFEN;
  }

  MSC->READCTRL = mscReadCtrl;
};

#else // defined(_SILICON_LABS_32B_SERIES_2)
/***************************************************************************//**
 * @brief
 *   Enables the flash controller for writing.
 * @note
 *   This function must be called before flash operations when
 *   AUXHFRCO clock has been changed from a default band.
 ******************************************************************************/
__STATIC_INLINE void MSC_Init(void)
{
#if defined(_MSC_TIMEBASE_MASK)
  uint32_t freq, cycles;
#endif

#if defined(_EMU_STATUS_VSCALE_MASK)
  /* VSCALE must be done. Flash erase and write requires VSCALE2. */
//   EFM_ASSERT(!(EMU->STATUS & _EMU_STATUS_VSCALEBUSY_MASK));
//   EFM_ASSERT((EMU->STATUS & _EMU_STATUS_VSCALE_MASK) == EMU_STATUS_VSCALE_VSCALE2);
#endif

  /* Unlock the MSC module. */
  MSC->LOCK = MSC_UNLOCK_CODE;
  /* Disable writing to the Flash. */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;

#if defined(_MSC_TIMEBASE_MASK)
  /* Configure MSC->TIMEBASE according to a selected frequency. */
  freq = CMU_ClockFreqGet(cmuClock_AUX);

  /* Timebase 5us is used for the 1/1.2 MHz band only. Note that the 1 MHz band
     is tuned to 1.2 MHz on newer revisions.  */
  if (freq > 1200000) {
    /* Calculate a number of clock cycles for 1 us as a base period. */
    freq   = (freq * 11) / 10;
    cycles = (freq / 1000000) + 1;

    /* Configure clock cycles for flash timing. */
    MSC->TIMEBASE = (MSC->TIMEBASE & ~(_MSC_TIMEBASE_BASE_MASK
                                       | _MSC_TIMEBASE_PERIOD_MASK))
                    | MSC_TIMEBASE_PERIOD_1US
                    | (cycles << _MSC_TIMEBASE_BASE_SHIFT);
  } else {
    /* Calculate a number of clock cycles for 5 us as a base period. */
    freq   = (freq * 5 * 11) / 10;
    cycles = (freq / 1000000) + 1;

    /* Configure clock cycles for flash timing */
    MSC->TIMEBASE = (MSC->TIMEBASE & ~(_MSC_TIMEBASE_BASE_MASK
                                       | _MSC_TIMEBASE_PERIOD_MASK))
                    | MSC_TIMEBASE_PERIOD_5US
                    | (cycles << _MSC_TIMEBASE_BASE_SHIFT);
  }
#endif
};

/***************************************************************************//**
 * @brief
 *   Disables the flash controller for writing.
 ******************************************************************************/
__STATIC_INLINE void MSC_Deinit(void)
{
  /* Disable writing to the Flash. */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
  /* Lock the MSC module.*/
  MSC->LOCK = 0;
};

/***************************************************************************//**
 * @brief
 *   Set the MSC code execution configuration.
 *
 * @param[in] execConfig
 *   The code execution configuration.
 ******************************************************************************/
__STATIC_INLINE void MSC_ExecConfigSet(MSC_ExecConfig_TypeDef *execConfig)
{
  uint32_t mscReadCtrl;

#if defined(MSC_READCTRL_MODE_WS0SCBTP)
  mscReadCtrl = MSC->READCTRL & _MSC_READCTRL_MODE_MASK;
  if ((mscReadCtrl == MSC_READCTRL_MODE_WS0) && (execConfig->scbtEn)) {
    mscReadCtrl |= MSC_READCTRL_MODE_WS0SCBTP;
  } else if ((mscReadCtrl == MSC_READCTRL_MODE_WS1) && (execConfig->scbtEn)) {
    mscReadCtrl |= MSC_READCTRL_MODE_WS1SCBTP;
  } else if ((mscReadCtrl == MSC_READCTRL_MODE_WS0SCBTP) && (!execConfig->scbtEn)) {
    mscReadCtrl |= MSC_READCTRL_MODE_WS0;
  } else if ((mscReadCtrl == MSC_READCTRL_MODE_WS1SCBTP) && (!execConfig->scbtEn)) {
    mscReadCtrl |= MSC_READCTRL_MODE_WS1;
  } else {
    /* No change needed. */
  }
#endif

  mscReadCtrl = MSC->READCTRL & ~(0
#if defined(MSC_READCTRL_SCBTP)
                                  | MSC_READCTRL_SCBTP
#endif
#if defined(MSC_READCTRL_USEHPROT)
                                  | MSC_READCTRL_USEHPROT
#endif
#if defined(MSC_READCTRL_PREFETCH)
                                  | MSC_READCTRL_PREFETCH
#endif
#if defined(MSC_READCTRL_ICCDIS)
                                  | MSC_READCTRL_ICCDIS
#endif
#if defined(MSC_READCTRL_AIDIS)
                                  | MSC_READCTRL_AIDIS
#endif
#if defined(MSC_READCTRL_IFCDIS)
                                  | MSC_READCTRL_IFCDIS
#endif
                                  );
  mscReadCtrl |= (0
#if defined(MSC_READCTRL_SCBTP)
                  | (execConfig->scbtEn ? MSC_READCTRL_SCBTP : 0)
#endif
#if defined(MSC_READCTRL_USEHPROT)
                  | (execConfig->useHprot ? MSC_READCTRL_USEHPROT : 0)
#endif
#if defined(MSC_READCTRL_PREFETCH)
                  | (execConfig->prefetchEn ? MSC_READCTRL_PREFETCH : 0)
#endif
#if defined(MSC_READCTRL_ICCDIS)
                  | (execConfig->iccDis ? MSC_READCTRL_ICCDIS : 0)
#endif
#if defined(MSC_READCTRL_AIDIS)
                  | (execConfig->aiDis ? MSC_READCTRL_AIDIS : 0)
#endif
#if defined(MSC_READCTRL_IFCDIS)
                  | (execConfig->ifcDis ? MSC_READCTRL_IFCDIS : 0)
#endif
                  );

  MSC->READCTRL = mscReadCtrl;
};
#endif

#if defined(_MSC_ECCCTRL_MASK) || defined(_SYSCFG_DMEM0ECCCTRL_MASK)
void MSC_EccConfigSet(MSC_EccConfig_TypeDef *eccConfig);
#endif

MSC_RAMFUNC_DECLARATOR MSC_Status_TypeDef
MSC_WriteWord(uint32_t *address,
              void const *data,
              uint32_t numBytes);

/* Note that this function is deprecated because we no longer support
 * placing msc code in ram. */
MSC_RAMFUNC_DECLARATOR MSC_Status_TypeDef
MSC_WriteWordFast(uint32_t *address,
                  void const *data,
                  uint32_t numBytes);

MSC_RAMFUNC_DECLARATOR MSC_Status_TypeDef
MSC_ErasePage(uint32_t *startAddress);

#if defined(MSC_WRITECMD_ERASEMAIN0)
SL_RAMFUNC_DECLARATOR MSC_Status_TypeDef
MSC_MassErase(void);
#endif

#if (_SILICON_LABS_32B_SERIES > 0)
MSC_Status_TypeDef MSC_WriteWordDma(int ch,
                                    uint32_t *address,
                                    const void *data,
                                    uint32_t numBytes);
#endif

/** @} (end addtogroup MSC) */
/** @} (end addtogroup emlib) */

#endif // CRTX_MSC_H
