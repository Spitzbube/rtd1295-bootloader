/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * To match the U-Boot user interface on ARM platforms to the U-Boot
 * standard (as on PPC platforms), some messages with debug character
 * are removed from the default U-Boot build.
 *
 * Define DEBUG here if you want additional info as shown below
 * printed upon startup:
 *
 * U-Boot code: 00F00000 -> 00F3C774  BSS: -> 00FC3274
 * IRQ Stack: 00ebff7c
 * FIQ Stack: 00ebef7c
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <version.h>
#include <serial.h>

#include <uart/run.h>
#include <uart/UART.h>

DECLARE_GLOBAL_DATA_PTR;

ulong monitor_flash_len;
#define CONFIG_SPL_BUILD


#define debug(fmt, args...)       //printf(fmt, ##args)


static int init_baudrate(void)
{
	//gd->baudrate = CONFIG_BAUDRATE;
	return 0;
}


typedef int (init_fnc_t) (void);



void __dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size =  gd->ram_size;
}
void dram_init_banksize(void)
	__attribute__((weak, alias("__dram_init_banksize")));

int __arch_cpu_init(void)
{
	return 0;
}
int arch_cpu_init(void)
	__attribute__((weak, alias("__arch_cpu_init")));

init_fnc_t *init_sequence[] = {
	//arch_cpu_init,		/* basic arch cpu dependent setup */
	//timer_init,		/* initialize timer */
	//env_init,		/* initialize environment */
	init_baudrate,		/* initialze baudrate settings */
	//serial_init,		/* serial communications setup */
	//console_init_f,		/* stage 1 init of console */	
	//dram_init,		/* configure available RAM banks */
	NULL,
};


void board_init_f(ulong bootflag)
{
bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	gd_t *id;
	ulong addr, addr_sp;


	/* Pointer is writable since we allocated a register for it */
	gd = (gd_t *) ((CONFIG_SYS_INIT_SP_ADDR) & ~0x07);

	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	memset((void *)gd, 0, sizeof(gd_t));


	/*for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}*/

	addr = 0x10004000;

	/* round down to next 4 kB limit */
	addr &= ~(4096 - 1);

	/*
	 * reserve memory for U-Boot code, data & bss
	 * round down to next 4 kB limit
	 */
	addr -= gd->mon_len;
	addr &= ~(4096 - 1);

	addr_sp += 128;	/* leave 32 words for abort-stack   */
	gd->irq_sp = addr_sp;

	gd->relocaddr = addr;
	gd->start_addr_sp = addr_sp;
	gd->reloc_off = addr - _TEXT_BASE;
	memcpy(id, (void *)gd, sizeof(gd_t));
	relocate_code(addr_sp, id, addr);

	/* NOTREACHED - relocate_code() does not return */
}


void board_init_r(gd_t *id, ulong dest_addr)
{
	
	hello_world();
	
	config_hw_setting();
	
	run_GPHY_BIST_pattern();
	
    main();  //LED
	    
}

void hang(void)
{
	//puts("### ERROR ### Please RESET the board ###\n");
	for (;;);
}

