/*
 * (C) Copyright 2014
 * Realtek Semiconductor Corp. 
 * Wilma Wu  <wilmawu@realtek.com>
 *
 * Configuration settings for the 1195 board.
 */

#ifndef __CONFIG_PHONEIX_TEST_H
#define __CONFIG_PHONEIX_TEST_H



/*
 * Realtek IC type
 */
#define CONFIG_PHOENIX	1


/*
 * High Level Configuration Options
 */
#define CONFIG_ARMV7		1	/* This is an ARM V7 CPU core */

/* Get CPU defs */
#include <asm/arch/cpu.h>

#define CONFIG_FLASH_WRITER_SETTING            "1195_force_spi_nS_nE"

//#define CONFIG_SKIP_LOWLEVEL_INIT	1

#undef CONFIG_USE_IRQ				/* no support for IRQs */


/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (256 << 10))
#define CONFIG_SYS_NON_CACHE_LEN	(1 << 20)
/* Vector Base */
#define CONFIG_SYS_CA9_VECTOR_BASE	SRAM_ROM_VECT_BASE

/*
 * Hardware drivers
 */

/*
 *Nand support
 */

/*
 * serial port - NS16550 compatible
 */
/*#define V_NS16550_CLK			33000000

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK

// for phoenix, refer to romcode uart_reg.h , iso doc
#define UART1_BASE				0x1801B200		//FPGA
#define UART0_BASE				0x18007800
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_COM1     UART0_BASE

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}*/

#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

/* Flash */
#define CONFIG_SYS_NO_FLASH	1

/* commands to include */


/*
 * Environment setup
 */

//#define CONFIG_CMDLINE_EDITING
//#define CONFIG_AUTO_COMPLETE

/*
 * Miscellaneous configurable options
 */


/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		0x03000000


/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
//stack size is setup in linker script 1MB
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 << 10)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4 << 10)	/* FIQ stack */
#endif

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000		//512MB

#define ARM_ROMCODE_SIZE			(42*1024)
#define MIPS_RESETROM_SIZE              (0x1000UL)
#define CONFIG_NR_DRAM_BANKS		1
//#define CONFIG_SYS_SDRAM_BASE		(ARM_ROMCODE_SIZE)		//for arm, first 32K can't be used as ddr. for lextra, it's okay
//#define CONFIG_SYS_RAM_DCU1_SIZE	(0x20000000-ARM_ROMCODE_SIZE)

//#define CONFIG_NO_RELOCATION
//if the relocation is enabled, the address is used to be the stack at very beginning.
#define CONFIG_SYS_INIT_SP_ADDR     0x10001250


#if 1 // 1:cache disable   0:enable
#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_DCACHE_OFF
#else
//#define CONFIG_NONCACHE_ALLOCATION
#define CONFIG_CMD_CACHE
#endif

#define CONFIG_SYS_CACHELINE_SIZE	32



#define CONFIG_SYS_TEXT_BASE    0x10001000


#define CONFIG_BOOT_PARAM_BASE			(0x00100000 + 0x100)
#define CONFIG_HEAP_RELOCATION

/* ENV related config options */
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SYS_PROMPT       "Realtek> "


#endif /* __CONFIG_PHONEIX_TEST_H */
