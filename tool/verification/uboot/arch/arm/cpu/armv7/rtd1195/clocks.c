/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * Time initialization.
 */

#include <common.h>
#include <asm/utils.h>
#include <asm/arch/system.h>
#include <asm/arch/rbus/iso_reg.h>

/*
 * clock enable api
 */
void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock)
{
	// clk = 0
	rtd_outl(reg_clock, rtd_inl(reg_clock) & (~mask_clock));

	// rst = 0
	rtd_outl(reg_reset, rtd_inl(reg_reset) & (~mask_reset));

	// wait
	udelay(10);

	// rst = 1
	rtd_outl(reg_reset, rtd_inl(reg_reset) | mask_reset);

	// wait
	udelay(10);

	// clk = 1
	rtd_outl(reg_clock, rtd_inl(reg_clock) | mask_clock);

}

static int rtc_init(void)
{
#if 0 // (wilma+ 2013/06/29)	
	uint rtcstop_regValue;

	rtcstop_regValue = rtd_inl(RTCSTOP_reg);

	// check RTC status
	if (RTCSTOP_get_RTCSTOP(rtcstop_regValue) == 0x0) // status: running
	{
		;	// RTC: Already running ... do nothing ...
	}
	else // status: stopped
	{
		// initialize RTC
		rtd_outl(RTCACR_reg, RTCACR_BC(0x0) | RTCACR_CLKSEL(0x0)); // clk select

		// reset time info
		rtd_outl(RTCSEC_reg, RTCSEC_RTCSEC(0x0)); // sec
		rtd_outl(RTCMIN_reg, RTCMIN_RTCMIN(0x0)); // min
		rtd_outl(RTCHR_reg, RTCHR_RTCHR(0x0)); // hour
		rtd_outl(RTCDATE1_reg, RTCDATE1_RTCDATE1(0x0)); // date LSB
		rtd_outl(RTCDATE2_reg, RTCDATE2_RTCDATE2(0x0)); // date MSB

		// enable RTC
		rtd_outl(RTCEN_reg, RTCEN_RTCEN(0x5A));

		// check RTC status
		rtcstop_regValue = rtd_inl(RTCSTOP_reg);
		if (RTCSTOP_get_RTCSTOP(rtcstop_regValue) == 0x0)
		{
			;	// RTC: Running
		}
		else
		{
			;	// RTC: Stop
		}
	}
#endif
	return 0;
}

/*
 * Enable essential clock domains, modules and
 * do some additional special settings needed
 */
int clock_init(void)
{

	int mask_clock=_BIT0;

    /* enable 90KHz counter */
	rtd_setbits(0x1801b538,_BIT0);

#if 0  
	
#if 1 // patch for SB2 write merge disable
	rtd_outl(0xb801a018, 0x000c2cc0);
#endif

#if 1 // add by cfyeh +++
	//rtd_outl(0xb8000100,0xffffffff);
	rtd_outl(0xb8000104,0xffffffff);
	rtd_outl(0xb8000108,0xffffffff);
	rtd_outl(0xb800010c,0xffffffff);

	//rtd_outl(0xb8000110,0xffffffff);
	rtd_outl(0xb8000114,0xffffffff);
	rtd_outl(0xb8000118,0xffffffff);
	//rtd_outl(0xb800011c,0xffffffff);

	rtd_outl(0xb8060040,0xffffffff);
	rtd_outl(0xb80004a4,0x53);

	//HDMI band gap
	//bit25
	rtd_outl(0xb800da40,0x03000000);

	//UTMI reset
	rtd_outl(0xb8013008,0xf);
	rtd_outl(0xb8013008,0x0);

	//USB3_ANA_PHY
	rtd_outl(0xb80130c4,0xe);
	//USB2_POW_gate
	rtd_outl(0xb80130c8,0xf);

	//2. set the USB2PHYCFG[6]=0=Suspend USB2.0 HS/FS/LS PHY (SusPHY)
	rtd_outl(0xb8058200,0x00001408);
	rtd_outl(0xb8058204,0x00001408);
	rtd_outl(0xb8058208,0x00001408);
	rtd_outl(0xb805820c,0x00001408);
#endif // add by cfyeh ---

	// enable RTC
	rtc_init();
#endif
	return 0;
}
