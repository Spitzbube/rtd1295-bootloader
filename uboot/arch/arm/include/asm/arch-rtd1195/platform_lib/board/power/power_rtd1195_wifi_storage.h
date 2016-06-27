#ifndef _POWER_RTD1195_WIFI_STORAGE_H_
#define _POWER_RTD1195_WIFI_STORAGE_H_


#define CONFIG_POWER_DOWN_SDIO
#define CONFIG_POWER_DOWN_GSPI
#if defined(CONFIG_SYS_RTK_NAND_FLASH) || defined(CONFIG_SYS_RTK_SPI_FLASH)
#define CONFIG_POWER_DOWN_eMMC
#endif
#define CONFIG_POWER_DOWN_CardReader
#if defined(CONFIG_SYS_RTK_NAND_FLASH) || defined(CONFIG_SYS_RTK_EMMC_FLASH)
#define CONFIG_POWER_DOWN_CP_RNG
#endif
//#define CONFIG_POWER_DOWN_MD *
//#define CONFIG_POWER_DOWN_AE *
#define CONFIG_POWER_DOWN_VCPU_VE1_VE2_GPU
#define CONFIG_POWER_DOWN_VO_TVE
#define CONFIG_POWER_DOWN_VideoDAC_A
#define CONFIG_POWER_DOWN_TP
#define CONFIG_POWER_DOWN_SE
#define CONFIG_POWER_DOWN_HDMITx_MHLTx
#define CONFIG_POWER_DOWN_Audio_I2S	
//#define CONFIG_POWER_DOWN_AudioDAC	*
//#define CONFIG_POWER_DOWN_SPDIF	*
#define CONFIG_POWER_DOWN_HDMIRx_MHLRx
#define CONFIG_POWER_DOWN_LVDS
#define CONFIG_POWER_DOWN_MIPI
#define CONFIG_POWER_DOWN_LSADC
#define CONFIG_POWER_DOWN_ALL_AV
//#define CONFIG_POWER_DOWN_ETN  *
#define CONFIG_POWER_DOWN_VFD
#define CONFIG_POWER_DOWN_CBUS
#define CONFIG_POWER_DOWN_CEC  
#define CONFIG_POWER_DOWN_IR  

#endif /* _POWER_RTD1195_WIFI_STORAGE_H_ */
