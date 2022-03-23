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
  /* FLASH (rx) : ORIGIN = 0x00034000, LENGTH = 40K */
  SKETCH_SYSCALL(rx): ORIGIN = 0x00034000, LENGTH = 0x100
  SKETCH_STRUCT(rx): ORIGIN = 0x00034800, LENGTH = 0xC0
  SKETCH_JMPTBL(rx): ORIGIN = 0x000348C0, LENGTH = 0x40
  SKETCH_MAINCODE(rx): ORIGIN = 0x00034900, LENGTH = 0x5F800
  SKETCH_RAM (rwx)  : ORIGIN = 0x2000C000, LENGTH = 16k
}

SECTIONS
{
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
		*(.init)
		*(.fini)
		*(.text*)
		*(.rodata.*)
	} > SKETCH_MAINCODE

	. = ALIGN (4);
	__etext = .;

	.data : AT (__etext)
	{
		. = ALIGN (4);
		__data_start__ = .;
		*(.ram)
		*(.data*)
		*(vtable)

		/* preinit data */
		. = ALIGN (4);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		/* init data */
		. = ALIGN(4);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);

		. = ALIGN(4);
		__data_end__ = .;
	} > SKETCH_RAM

	.data_count_size (NOLOAD):
	{
		. = . + SIZEOF(.data);
	} > SKETCH_MAINCODE

	.bss (NOLOAD):
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)

		. = ALIGN(4);
		__heap_start__ = .;
		*(.heap)
		. = ALIGN(4);
		__bss_end__ = .;
	} > SKETCH_RAM

	__data_size__ = __data_end__ - __data_start__;
	__bss_size__ = __bss_end__ - __bss_start__;
	__heap_end__ = ORIGIN(SKETCH_RAM) + LENGTH(SKETCH_RAM);
	__heap_size__ = __heap_end__ - __heap_start__;
	__HeapBase = __bss_end__;
	__HeapLimit = ORIGIN(SKETCH_RAM) + LENGTH(SKETCH_RAM);
	__HeapSize = __HeapLimit - __HeapBase;
}
