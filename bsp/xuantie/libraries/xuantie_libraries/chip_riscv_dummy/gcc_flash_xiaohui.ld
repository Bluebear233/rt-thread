 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

MEMORY
{
	DRAM   : ORIGIN = 0x50000000, LENGTH = 0x100000   /* on-chip DRAM 1*1MB */
}

__min_heap_size = 0x20000;
PROVIDE (__ram_end  = 0x50100000 - 0x8);
PROVIDE (__heap_end = __ram_end);

REGION_ALIAS("REGION_TEXT",    DRAM);
REGION_ALIAS("REGION_RODATA",  DRAM);
REGION_ALIAS("REGION_DATA",    DRAM);
REGION_ALIAS("REGION_BSS",     DRAM);

ENTRY(Reset_Handler)
SECTIONS
{
 .text : {
  . = ALIGN(0x4) ;
  __stext = . ;
  KEEP(*startup.o(*.text))
  KEEP(*startup.o(*.vectors))
  KEEP(*vectors.o(*.text))
  KEEP(*(.text.entry))
  *(.text)
  *(.text*)
  *(.text.*)
  *(.gnu.warning)
  *(.stub)
  *(.gnu.linkonce.t*)
  *(.glue_7t)
  *(.glue_7)
  *(.jcr)
  KEEP (*(.init))
  KEEP (*(.fini))
  . = ALIGN(0x4) ;
  PROVIDE(__ctbp = .);
  *(.call_table_data)
  *(.call_table_text)
  . = ALIGN(0x4) ;
  __etext = . ;
 } > REGION_TEXT
 .gcc_except_table : ONLY_IF_RO {
  *(.gcc_except_table .gcc_except_table.*)
 } > REGION_TEXT
 .rodata : {
  . = ALIGN(0x4) ;
  __srodata = .;
  *(.rdata)
  *(.rdata*)
  *(.rdata1)
  *(.rdata.*)
  *(.rodata)
  *(.rodata1)
  *(.rodata*)
  *(.rodata.*)
  *(.rodata.str1.4)
  *(.srodata*)
  . = ALIGN(0x8) ;

  __init_array_start = .;
  __ctors_start__ = .;
  KEEP (*(SORT(.init_array.*)))
  KEEP (*(.init_array))
  __init_array_end = .;
  __ctors_end__ = .;

  . = ALIGN(0x8) ;
  __fini_array_start = .;
  __dtors_start__ = .;
  KEEP (*(SORT(.fini_array.*)))
  KEEP (*(.fini_array))
  __fini_array_end = .;
  __dtors_end__ = .;

  . = ALIGN(0x8) ;
  __ctor_start__ = .;
  KEEP (*(SORT(.ctors.*)))
  KEEP (*(.ctors))
  __ctor_end__ = .;
  KEEP (*(SORT(.dtors.*)))
  KEEP (*(.dtors))
  __dtor_end__ = .;
  . = ALIGN(0x4) ;
/*****************************************/
  /* section information for finsh shell */
  . = ALIGN(0x4);
  __fsymtab_start = .;
  KEEP(*(FSymTab))
  __fsymtab_end = .;
  . = ALIGN(0x4);
  __vsymtab_start = .;
  KEEP(*(VSymTab))
  __vsymtab_end = .;
  . = ALIGN(0x4);

  /* section information for initial. */
  __rt_init_start = .;
  KEEP(*(SORT(.rti_fn*)))
  __rt_init_end = .;
  . = ALIGN(0x4) ;

  /* section information for at utest */
  __rt_utest_tc_tab_start = .;
  KEEP(*(UtestTcTab))
  __rt_utest_tc_tab_end = .;
  . = ALIGN(0x4);

  /* section information for at server */
  . = ALIGN(0x4);
  __rtatcmdtab_start = .;
  KEEP(*(RtAtCmdTab))
  __rtatcmdtab_end = .;
  . = ALIGN(0x4);

  /* section information for modules */
  . = ALIGN(0x4);
  __rtmsymtab_start = .;
  KEEP(*(RTMSymTab))
  __rtmsymtab_end = .;

  /* section information for uPRC */
  . = ALIGN(0x4);
  __uRPCSvcTab_start = .;
  KEEP(*(uRPCSvcTab))
  __uRPCSvcTab_end = .;

  /* section information for var export */
  . = ALIGN(0x4);
  __ve_table_start = .;
  KEEP(*(SORT(*.VarExpTab.*)))
  __ve_table_end = .;
/*****************************************/
/************** added drivers **************/
  _cli_region_begin = .;
  KEEP(*(CliRegion))
  . = ALIGN(0x4) ;
  _cli_region_end = .;

  __core_driver_start__ = .;
  KEEP(*(.core_driver_entry))
  . = ALIGN(0x4) ;
  __core_driver_end__ = .;

  __bus_driver_start__ = .;
  KEEP(*(*.bus_driver_entry))
  __bus_driver_end__ = .;

  __early_driver_start__ = .;
  KEEP(*(*.early_driver_entry))
  __early_driver_end__ = .;

  __vfs_driver_start__ = .;
  KEEP(*(*.vfs_driver_entry))
  __vfs_driver_end__ = .;

  __level0_driver_start__ = .;
  KEEP(*(*.level0_driver_entry))
  __level0_driver_end__ = .;

  __level1_driver_start__ = .;
  KEEP(*(*.level1_driver_entry))
  __level1_driver_end__ = .;

  __level2_driver_start__ = .;
  KEEP(*(*.level2_driver_entry))
  __level2_driver_end__ = .;

  __level3_driver_start__ = .;
  KEEP(*(*.level3_driver_entry))
  __level3_driver_end__ = .;

  __post_driver_start__ = .;
  KEEP(*(*.post_driver_entry))
  __post_driver_end__ = .;
/************** end of drivers *********/
  . = ALIGN(0x4) ;
  __erodata = .;
  __rodata_end__ = .;
 } > REGION_RODATA
 .data : {
  . = ALIGN(0x4) ;
  __sdata = . ;
  __data_start__ = . ;
  data_start = . ;
  *(.got.plt)
  *(.got)
  *(.gnu.linkonce.r*)
  *(.data)
  *(.data*)
  *(.data1)
  *(.data.*)
  *(.gnu.linkonce.d*)
  *(.data1)
  *(.gcc_except_table)
  *(.gcc_except_table*)
  __start_init_call = .;
  *(.initcall.init)
  __stop_init_call = .;
  __start_cmd = .;
  *(.bootloaddata.cmd)
  . = ALIGN(4) ;
  __stop_cmd = .;
  __global_pointer$ = .;
  *(.sdata)
  *(.sdata.*)
  *(.sdata2.*)
  *(.gnu.linkonce.s.*)
  *(__libc_atexit)
  *(__libc_subinit)
  *(__libc_subfreeres)
  *(.note.ABI-tag)
  . = ALIGN(0x4) ;
  __edata = .;
  __data_end__ = .;
 } > REGION_DATA
 ._ram_code : {
  . = ALIGN(0x4) ;
  __ram_code_start__ = .;
  *(.ram.code*)
  . = ALIGN(0x4) ;
  __ram_code_end__ = .;
 } > REGION_DATA
 .bss : {
  . = ALIGN(0x4) ;
  __sbss = ALIGN(0x4) ;
  __bss_start__ = . ;
  *(.dynsbss)
  *(.sbss)
  *(.sbss.*)
  *(.scommon)
  *(.dynbss)
  *(.bss)
  *(.bss.*)
  *(COMMON)
  . = ALIGN(0x4) ;
  __ebss = . ;
  __bss_end__ = .;
  __end = . ;
  end = . ;
 } > REGION_BSS 
 ._user_heap (NOLOAD): {
  . = ALIGN(0x4) ;
  *(.stack*)
  . = ALIGN(0x4) ;
  __heap_start = .;
  . += __min_heap_size;
  . = ALIGN(0x4) ;
 } > REGION_BSS
}
