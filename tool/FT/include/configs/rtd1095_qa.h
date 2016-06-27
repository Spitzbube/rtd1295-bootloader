/*
 * Configuration settings for the Realtek 1095 board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1095_QA_H
#define __CONFIG_RTK_RTD1095_QA_H

/*
 * Include the common settings of RTD1195 platform.
 */
#include <configs/rtd1195_common.h>

/* Board config name */
#define CONFIG_BOARD_DEMO_RTD1095

#define CONFIG_BOARD_FPGA_RTD1195_EMMC 
         

#define CONFIG_SYS_RTK_SPI_FLASH
#if defined(CONFIG_SYS_RTK_SPI_FLASH)
#define CONFIG_FLASH_WRITER_SETTING            "1095_force_spi_nS_nE"
#define CONFIG_CHIP_ID            			   "rtd1095"
#define CONFIG_CUSTOMER_ID            		   "ASIC" 
#define CONFIG_CHIP_TYPE            		   "0000"
#define CONFIG_FACTORY_SIZE		0x20000		/* For SPI */
#endif

/* Boot Revision */
#define CONFIG_COMPANY_ID 		"0000"
#define CONFIG_BOARD_ID         "0705"
#define CONFIG_VERSION          "0000"

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#if 1 	
// undefine existed configs to prevent compile warning
#undef CONFIG_NR_DRAM_BANKS
#undef CONFIG_SYS_SDRAM_BASE
#undef CONFIG_SYS_RAM_DCU1_SIZE


#define ARM_ROMCODE_SIZE			(44*1024)
#define MIPS_RESETROM_SIZE              (0x1000UL)
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0		
#define CONFIG_SYS_RAM_DCU1_SIZE	0x10000000

#undef  V_NS16550_CLK
#define V_NS16550_CLK			27000000
	
#endif


#endif /* __CONFIG_RTK_RTD1095_QA_H */

