/* Linker script for Z-Wave.Me Z-UnoG2 (cortex based)                  */
/*                                                                     */
/* This file is subject to the license terms as defined in ARM's       */
/* CMSIS END USER LICENSE AGREEMENT.pdf, governing the use of          */
/* Example Code.                                                       */
/*                                                                     */
/* Copyright 2019 Z-Wave.Me http://z-uno.z-wave.me                     */
/*                                                                     */
/* Version 0.0.1                                                       */
/*                                                                     */


MEMORY
{
  /* FLASH (rx) : ORIGIN = 0x00030000, LENGTH = 48K */
  SKETCH_SYSCALL(rx): ORIGIN = 0x0002FF00, LENGTH = 0x100
  SKETCH_STRUCT(rx): ORIGIN = 0x00030000, LENGTH = 0xC0
  SKETCH_JMPTBL(rx): ORIGIN = 0x000300C0, LENGTH = 0x40
  SKETCH_MAINCODE(rx): ORIGIN = 0x00030100, LENGTH = 40704
  NVM (rx) :  ORIGIN = 0x00075000, LENGTH = 8K
  SKETCH_RAM (rwx)  : ORIGIN = 0x2000E000, LENGTH = 8k
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */

SECTIONS
{

  .nvm3App (NOLOAD):
  {
    . = ALIGN(1024);
    _nvm3App = . ;
    KEEP(*(.nvm3App))
    _envm3App = . ;
  } >NVM
 
  .sketch_struct :
  {
    _sketch_struct = . ;
    KEEP(*(.sketch_struct))
    _esketch_struct = . ;
  } >SKETCH_STRUCT
  
  .sketch_syscall :
  {
    _sketch_syscall = . ;
    KEEP(*(.sketch_syscall))
    _esketch_syscall = . ;
  } >SKETCH_SYSCALL
  
  .sketch_jmptbl :
  {
    _sketch_jmptbl = . ;
    KEEP(*(.sketch_jmptbl))
    _esketch_jmptbl = . ;
  } >SKETCH_JMPTBL
  .text :
  {
    _sketch_code_start = . ;
    *(.rodata.*)
    *(.text*)

	_write = . ;
	KEEP(*(._write))
	_close = . ;
	KEEP(*(._close))
	_lseek = . ;
	KEEP(*(._lseek))
	_read = . ;
	KEEP(*(._read))
	_sbrk = .;
	KEEP(*(._sbrk))

    KEEP(*(.init))
    KEEP(*(.fini))
    /* .ctors */
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)

    /* .dtors */
    *crtbegin.o(.dtors)
    *crtbegin?.o(.dtors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
    *(SORT(.dtors.*))
    *(.dtors)
    _sketch_code_end = . ;
  } > SKETCH_MAINCODE

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > SKETCH_MAINCODE

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > SKETCH_MAINCODE
  __exidx_end = .;

  /* To copy multiple ROM to RAM sections,
   * uncomment .copy.table section and,
   * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
  /*
  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;
    LONG (__etext)
    LONG (__data_start__)
    LONG (__data_end__ - __data_start__)
    LONG (__etext2)
    LONG (__data2_start__)
    LONG (__data2_end__ - __data2_start__)
    __copy_table_end__ = .;
  } > SKETCH_MAINCODE
  */

  /* To clear multiple BSS sections,
   * uncomment .zero.table section and,
   * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
  /*
  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    LONG (__bss_start__)
    LONG (__bss_end__ - __bss_start__)
    LONG (__bss2_start__)
    LONG (__bss2_end__ - __bss2_start__)
    __zero_table_end__ = .;
  } > SKETCH_MAINCODE
  */

  __etext = .;

  .reset_info (NOLOAD) : {
        *(.data.reset_info)
  } > SKETCH_RAM
  
  .data : AT (__etext)
  {
    __data_start__ = .;
    *(vtable)
    *(.data*)
    . = ALIGN (4);
    *(.ram)

    . = ALIGN(4);
    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    /* init data */
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    /* finit data */
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);

    KEEP(*(.jcr*))
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;

  } > SKETCH_RAM
    
  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > SKETCH_RAM
  
  .heap (COPY):
  {
    __HeapBase = .;
    __end__ = .;
    end = __end__;
    _end = __end__;
    KEEP(*(.heap*))
    __HeapLimit = .;
  } > SKETCH_RAM

  
  /* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy (COPY):
  {
    KEEP(*(.stack*))
  } > SKETCH_RAM

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(SKETCH_RAM) + LENGTH(SKETCH_RAM);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

  /* Check if FLASH usage exceeds FLASH size */
  /*
  ASSERT( LENGTH(SKETCH_MAINCODE) >= (__etext + SIZEOF(.data)), "FLASH memory overflowed !")
  */
}
