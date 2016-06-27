/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 */

#include <common.h>
#include <asm/armv7.h>
#include <asm/sizes.h>
#include <config.h>
#include <asm/errno.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

unsigned int cortex_rev(void)
{

    unsigned int rev;

    /* Read Main ID Register (MIDR) */
    asm ("mrc p15, 0, %0, c0, c0, 0" : "=r" (rev));

    return rev;
}

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
    unsigned int iMedia;
#if 0 // test SCPU BISR
	unsigned int iTemp;
	printf("SCPU : BISR testinng ....\n");
	rtd_outl( 0x1805c500, 0x03 );
	mdelay(400);
	while( rtd_inl(0x1805c51c) != 0x03 );
	rtd_outl(0x1805c504, 0x03);
	printf("SCPU : Finish BISR testinng\n");
#endif    
    printf("CPU  : Cortex-A7 dual core\n");
#if 0 // for boot device information
	extern unsigned int UATAG_ADDRESS9;
	extern unsigned int UATAG_ADDRESS10;
	printf("Media: ");
    if( *((unsigned int *)&UATAG_ADDRESS9) == 0xF9E8D7C6UL ){
    	iMedia = *((unsigned int *)&UATAG_ADDRESS10);
    	if( iMedia == 0 ){
    		printf("NAND\n");
    	}
    	else if( iMedia == 1 ){
    		printf("SPI\n");
    	}
    	else if( (iMedia&0xFF) == 2 ){
    		iMedia = (iMedia >> 8) & 0xFF;
    		if( iMedia == 2 ) {
    			printf("eMMC BP2\n");
    		}
    		else if( iMedia == 1 ) {
    			printf("eMMC BP1\n");
    		}
    		else if( iMedia == 0 ) {
    			printf("eMMC BP0\n");
    		}
    		else {
    			printf("eMMC (unknown BP)\n");
    		}
    	}
    	else if( *((unsigned int *)&UATAG_ADDRESS10) == 0 ){
    		printf("unknown\n");
    	}    	
    }
    else {
    	printf("undefined\n");
    }
#if 0 // turn on ARM JTAG port
	  // please all switch jumper, JS9
    printf("JTAG chain : 0x%08x\n", rtd_inl(0xb8000200));
    printf("Debug mode : 0x%08x\n", rtd_inl(0xb805c104));
    rtd_outl( 0xb8000200, 0x10 );
    rtd_outl( 0xb805c104, 0x4f3 );
	printf("JTAG chain : 0x%08x\n", rtd_inl(0xb8000200));
    printf("Debug mode : 0x%08x\n", rtd_inl(0xb805c104));
#endif
	//printf("uatag9(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS9, *((unsigned int *)&UATAG_ADDRESS9));
	//printf("uatag10(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS10, *((unsigned int *)&UATAG_ADDRESS10));
	//printf("uatag11(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS11, *((unsigned int *)&UATAG_ADDRESS11));
	//printf("uatag12(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS12, *((unsigned int *)&UATAG_ADDRESS12));
#endif
    return 0;
}

#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{
    /* Enable D-cache. I-cache is already enabled in start.S */
    dcache_enable();
}
#endif

#ifndef CONFIG_SYS_L2CACHE_OFF
void v7_outer_cache_enable(void)
{
	//set_pl310_ctrl_reg(1);
}

void v7_outer_cache_disable(void)
{
	//set_pl310_ctrl_reg(0);
}
#endif
