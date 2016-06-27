/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2014 by Wilma Wu <wilmawu@realtek.com>
 *
 */

#include <asm/armv7.h>
#include <asm/arch/io.h>


void _sync(void)
{
	asm("DMB");
	rtd_inl(0x1801a020);
	asm("DMB");
}
