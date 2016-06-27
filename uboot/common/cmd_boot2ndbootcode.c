/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

#include <common.h>
#include <command.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <fdt_support.h>
#include <environment.h>

#ifdef CONFIG_GOLDENBOOT_SUPPORT
#include <goldenboot.h>
#endif

#ifdef CONFIG_PRELOAD_BOOT_IMAGES
int rtk_preload_bootimages_from_emmc(void);
int rtk_preload_bootimages_from_spi(void);
int rtk_preload_bootimages_from_sata(void);
#endif

int rtk_boot2ndbootcode(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	void *fdt_addr = 0;
	env_t *env_out = (env_t*)CONFIG_ENV_EXPORT_ADDR;

	mdelay(1000);

	if (env_export_uboot64(env_out))
		printf("\n\EXPORT ENV FAIL!!\n");
	else
		printf("\n\nEXPORT ENV AT 0x%08p, ENV size info:0x%08x,0x%08x,0x%08x\n", env_out, CONFIG_ENV_SIZE, ENV_SIZE, ENV_HEADER_SIZE);

	do {
		
#ifdef CONFIG_GOLDENBOOT_SUPPORT
		unsigned fw_load_result = 0;
#ifdef CONFIG_PRELOAD_BOOT_IMAGES
	#ifdef CONFIG_RTK_MMC
		fw_load_result = rtk_preload_bootimages_emmc();
	#endif
	#ifdef CONFIG_RTKSPI
		fw_load_result = rtk_preload_bootimages_spi();
	#endif
	#ifdef CONFIG_RTK_SATA
		fw_load_result = rtk_preload_bootimages_sata();
	#endif
#endif
		if (fdt_addr = getenv_ulong("fdt_loadaddr", 16, 0))
			fdt_chosen(fdt_addr, 1);
		if(!getenv_ulong("bootcode2nd_loadaddr", 16, 0))
			fw_load_result = rtk_plat_prepare_fw_image_from_eMMC();
		if(!fw_load_result)
			start_2nd_bootcode_from_golden();
#else
		printf("2nd stage bootcode NOT supported!!\n");
#endif
	} while(0);

	printf("Could not perform 2nd stage bootcode!!!\n");

	return 0;
}

U_BOOT_CMD(
	b2ndbc, 4, 0,	rtk_boot2ndbootcode,
	"load 2nd stage bootcode",
	"b2ndbc\n"
);

