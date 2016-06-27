#ifdef FPGA
#include <stdio.h>
#include <stdlib.h>
#endif
#include "project_config_f.h"
//#include "extern_param.h"
#include "shell_golinux.h"
#include "platform_iso.h"
#include "flashdev_n.h"
#include "flashdev_e.h"
#include "flashdev_s.h"
#include "otp.h"
#include "dvrboot_inc/mis_reg.h"
#include "dvrboot_inc/sys_reg.h"
#include "dvrboot_inc/util.h"
#include "dvrboot_inc/mcp.h"
#include "dvrboot_inc/string.h"
#include "uart.h"

//#define SPI_ENV_PARAM_ADDR              0x18200000
//#define SPI_ENV_PARAM_SIZE              0x00010000

#define FLASH_MAGICNO_NOR_PARALLEL		0xBE
#define FLASH_MAGICNO_NAND				0xCE
#define FLASH_MAGICNO_NOR_SERIAL		0xDE
#define FLASH_MAGICNO_EMMC	 			0xEE

#define EXT_PARA_DDR_BASE				(0xA0A00000 - UBOOT_DDR_OFFSET)	// t_extern_param + logo + rescue base address on DDR
#define NAND_ENV_DDR_BASE				(0xA0040000 - UBOOT_DDR_OFFSET)	// modify by angus, original value is 0xa0010000

#define BOOTCODE_SIZE_ADDR				0XB801A60C
#define SIMULATION_DUMP_ADDR			(0xA3000000 - UBOOT_DDR_OFFSET)	// dump hwsetting/bootcode related to DDR
#define NAND_BOOT_BACKUP_COUNT			3								// number of backup bootcode in NAND flash

extern unsigned char resetrom[];		//rom data : 0x1FC0_0000 ~ 0x1FC0_1FFF
extern unsigned char resetrom_end;
extern unsigned char mips_resetrom[];		
extern unsigned char mips_resetrom_end;
extern unsigned char hwsetting[];
extern unsigned char hwsetting_end;
extern unsigned char hasharray[];
extern unsigned char hasharray_end;
extern unsigned char signature[];
extern unsigned char signature_end;
extern unsigned char fsbl[];
extern unsigned char fsbl_signature[];
extern unsigned char fsbl_signature_end;
extern unsigned char fsbl_end;
extern unsigned char fsbl_os[];
extern unsigned char fsbl_os_signature[];
extern unsigned char fsbl_os_signature_end;
extern unsigned char fsbl_os_end;
extern unsigned char rsa_pub[];
extern unsigned char rsa_pub_end;
#ifdef MAGALLAN_PRJ
extern unsigned char bootcode2_boot_hasharray[];
extern unsigned char bootcode2_boot_hasharray_end;
extern unsigned char bootcode2_boot_signature[];
extern unsigned char bootcode2_boot_signature_end;
extern unsigned char bootcode3_boot_hasharray[];
extern unsigned char bootcode3_boot_hasharray_end;
extern unsigned char bootcode3_boot_signature[];
extern unsigned char bootcode3_boot_signature_end;
#endif
extern unsigned char ecbarray[];
extern unsigned char ecbarray_end;
extern unsigned char linux_rescue_hasharray[];
extern unsigned char linux_rescue_hasharray_end;
extern unsigned char linux_rescue_signature[];
extern unsigned char linux_rescue_signature_end;
extern unsigned char cbc_linux[];
extern unsigned char cbc_linux_end;
extern unsigned char hwsetting_sig_image[];
extern unsigned char hwsetting_sig_image_end;
extern unsigned char dcas_key_sig_image[];
extern unsigned char dcas_key_sig_image_end;
extern unsigned char logo[];
extern unsigned char logo_end;
extern unsigned char logo2[];
extern unsigned char logo2_end;
extern unsigned char logo3[];
extern unsigned char logo3_end;
extern unsigned char logo4[];
extern unsigned char logo4_end;
extern unsigned char logo5[];
extern unsigned char logo5_end;
extern unsigned char logo6[];
extern unsigned char logo6_end;
extern unsigned char logo7[];
extern unsigned char logo7_end;
extern unsigned char logo8[];
extern unsigned char logo8_end;

extern unsigned int  pages_per_block;
extern unsigned int  blocks_per_flash;

extern unsigned int  mcp_dscpt_addr;

unsigned char  verify_after_write;
unsigned char  force_secure;
unsigned char  test_secure;
unsigned char  noreset;

PrintFuncPtr_t 			rtprintf=NULL;
Flush_Dcache_AllPtr_t 	rtflush_dcache_all=NULL;
Flush_CachePtr_t  		rtflush_cache=NULL;

/************************************************************************
 *
 ************************************************************************/
unsigned int align_to_boundary(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? size / block_size + 1 : size / block_size);
}

unsigned int align_to_boundary_length(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? (size / block_size + 1)*block_size : (size / block_size)*block_size );
}

void set_spi_pin_mux(void)
{
#ifndef FPGA	  //wilma+  0802
	//1195
	//set sf_en=1
	REG32(SYS_muxpad5) |= 0x01;
#endif	
}

void set_nand_pin_mux(void)
{
	//1195
	//set default i/f to nf
	REG32(SYS_muxpad0) = 0x55555554;	
}

void set_emmc_pin_mux(void)
{
        //1195
        //set default i/f to cr
        unsigned int reg_val=0;
        reg_val = REG32(SYS_muxpad0);
        reg_val &= ~0xFFFF0FFF;
        reg_val |= 0xaaaa0aa8;
        REG32(SYS_muxpad0) = reg_val;

        //select SD
        REG8(CARD_SELECT) = 0x2;                  
}

/************************************************************************
 * get uboot domain function pointer to dvrmain domain function pointer
 ************************************************************************/
void rebuild_function_pointer_from_uboot_to_dvrmain( void )
{
    // get fun ptr of printf(...) from specified address
    #define DUMMY                               (*((unsigned int *)0x00020060))
    #define DUMMY2                              (*((unsigned int *)0x00020064))
    #define UBOOT_PRINTF_ADDRESS_TAG            (*((unsigned int *)0x00020068))
    #define UBOOT_PRINTF_ADDRESS                (*((unsigned int *)0x0002006C))
    #define UBOOT_FLUSH_DCACHE_ALL_ADDRESS_TAG  (*((unsigned int *)0x00020070))
    #define UBOOT_FLUSH_DCACHE_ALL_ADDRESS      (*((unsigned int *)0x00020074))
    #define UBOOT_FLUSH_CACHE_ADDRESS_TAG       (*((unsigned int *)0x00020078))
    #define UBOOT_FLUSH_CACHE_ADDRESS           (*((unsigned int *)0x0002007C))

    if( UBOOT_PRINTF_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        rtprintf = (PrintFuncPtr_t) (UBOOT_PRINTF_ADDRESS);
        rtprintf("\n\nHello World(%s %s), get printf ptr=%p\n\n", __DATE__, __TIME__, rtprintf);
    }
    else {
        rtprintf = NULL;
    }

    if( UBOOT_FLUSH_DCACHE_ALL_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        rtflush_dcache_all = (Flush_Dcache_AllPtr_t) (UBOOT_FLUSH_DCACHE_ALL_ADDRESS);
    }
    else {
        rtflush_dcache_all = NULL;
    }

    if( UBOOT_FLUSH_CACHE_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        if (UBOOT_FLUSH_CACHE_ADDRESS != UBOOT_PRINTF_ADDRESS) // prevent side effect
        {
            rtflush_cache = (Flush_CachePtr_t) (UBOOT_FLUSH_CACHE_ADDRESS);
        }
        else
        {
            rtflush_cache = NULL;
        }
    }
    else {
        rtflush_cache = NULL;
    }
}

/************************************************************************
 *
 *  dvrmain
 *  Description :
 *  -------------
 *  main function of flash writer
 *  attention:
 *  1. since 0xbfc0_0000 ~ 0xbfc0_1fff occupied by ROM code,
 *     space from 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash can not be utilized.
 *     In order to write data to the space, we shift writing address space from
 *     0xbed0_0000 ~ 0xbfcf_ffff to 0xbdd0_0000 ~ 0xbecf_ffff. So that we can
 *     access to space 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash.
 *  2. we left 0xbecf_f000 ~ 0xbecf_ffff for ext_param.
 *  3. ext_param is located from 0xbecf_f800.
 *
 *  Parameters :
 *  Return values :
 *
 ************************************************************************/
int dvrmain	( int argc, char * const argv[] )
{
    // spi used
    unsigned char * spi_resetrom_addr;
	unsigned char * spi_mips_resetrom_addr;
    unsigned char * spi_hwsetting_addr;
    unsigned char * spi_param_addr;
    unsigned char * spi_param_addr2;
    unsigned char * spi_bootcode_addr;
    unsigned char * spi_rescue_addr;
    unsigned char * spi_rescue_sig_addr;
    unsigned char * spi_fsbl_addr;
    unsigned char * spi_fsbl_sig_addr;
    unsigned char * spi_fsbl_os_addr;
    unsigned char * spi_fsbl_os_sig_addr;
    unsigned char * spi_rsa_pub_addr;
	unsigned char * spi_bootcode_sig_addr;
    unsigned char * spi_bootcode_addr2;
    unsigned char * spi_bootcode_addr3;
    unsigned char * spi_key_sig_addr;
    unsigned char * spi_key_sig_addr2;
    unsigned char * spi_key_sig_addr3;

    // for nand

    // for emmc

    // common
    unsigned char * logo_addr;
    unsigned char * logo2_addr;
    unsigned char * logo3_addr;
    unsigned char * logo4_addr;
    unsigned char * logo5_addr;
    unsigned char * logo6_addr;
    unsigned char * logo7_addr;
    unsigned char * logo8_addr;

    unsigned int  resetrom_size;
    unsigned int  mips_resetrom_size;
    unsigned int  hwsetting_size;
    unsigned int  hasharray_size;
	unsigned int  signature_size;
	unsigned int  bootcode2_boot_hasharray_size;
	unsigned int  bootcode2_boot_signature_size;
	unsigned int  bootcode3_boot_hasharray_size;
	unsigned int  bootcode3_boot_signature_size;
	unsigned int  linux_rescue_hasharray_size;
	unsigned int  linux_rescue_signature_size;
    unsigned int  hwsetting_sig_size;
    unsigned int  dcas_key_sig_size;
    unsigned int  logo_size;
    unsigned int  logo2_size;
    unsigned int  logo3_size;
    unsigned int  logo4_size;
    unsigned int  logo5_size;
    unsigned int  logo6_size;
    unsigned int  logo7_size;
    unsigned int  logo8_size;

    unsigned char * env_param_addr;
    unsigned char * linux_sec1_addr;
    unsigned char * linux_sec2_addr;
    unsigned int    linux_sec1_size;
    unsigned int    linux_sec2_size;

    unsigned char * programmed_img_base;
    unsigned int    programmed_img_size;

	unsigned char * programmed_img_sig_base;
	unsigned int	programmed_img_sig_size;
	unsigned char * programmed_linux_rescue_sig_base;
	unsigned int	programmed_linux_rescue_sig_size;

	unsigned char * programmed_fsbl_base;
	unsigned int	programmed_fsbl_size;
	unsigned char * programmed_fsbl_sig_base;
	unsigned int	programmed_fsbl_sig_size;
	unsigned char * programmed_fsbl_os_base;
	unsigned int	programmed_fsbl_os_size;
	unsigned char * programmed_fsbl_os_sig_base;
	unsigned int	programmed_fsbl_os_sig_size;
	unsigned char * programmed_rsa_pub_base;
	unsigned int	programmed_rsa_pub_size;
    
    unsigned char * bootcode2_boot_programmed_img_base;
    unsigned int    bootcode2_boot_programmed_img_size;
    
    unsigned char * bootcode3_boot_programmed_img_base;
    unsigned int    bootcode3_boot_programmed_img_size;    

    unsigned char * programmed_linux_rescue_img_base;
    unsigned int    programmed_linux_rescue_img_size;

    unsigned char   flash_type;
    unsigned char   flash_magicno;
    unsigned int    idx, i, j;
    unsigned int    temp, reg_addr;
    unsigned char * temp_ptr;
    unsigned int *  temp_ptr32;
	void * device;
    int res;
    int save_nand_env;

    unsigned int  block_size;
    unsigned int  total_block_cnt;

    //t_extern_param param;
    //t_extern_param *orignal_param;


	// -------------------------------------------------------------------------
	// function declaration
	// -------------------------------------------------------------------------
    int (*do_erase)(void  *, unsigned int * , unsigned int);
    int (*do_write)(void *, unsigned char *, unsigned int *, unsigned int, unsigned int, const unsigned int);
    int (*do_identify)(void **);
    int (*do_init)(void *);
    int (*do_read)(void *, unsigned int *, unsigned char *, unsigned int, INT32);
    int (*do_hide_hwsetting)(void *, unsigned char *, unsigned int *, unsigned int, unsigned int, const unsigned int);
    void (*do_exit)(void *dev);

    // -------------------------------------------------------------------------
	// copy uboot domain fun pointer to dvrmoan domain
	// -------------------------------------------------------------------------
	#ifndef FOR_ICE_LOAD
	rebuild_function_pointer_from_uboot_to_dvrmain();
    #else
	// make a copy here to avoid flush function pointer being invalid.
	rebuild_function_pointer_from_uboot_to_dvrmain();
    init_uart();
    set_focus_uart(0); //default : uart0
	#endif

	// -------------------------------------------------------------------------
	// initial global variable
	// -------------------------------------------------------------------------
	block_size = 0x00001000;													// block size == 4096 bytes
	total_block_cnt = 0x00100000 / block_size;									// 256 blocks for 1MB ( 0xbec0_0000~0xbecf_ffff )
	mcp_dscpt_addr = 0;

	// -------------------------------------------------------------------------
	// initial local variable
	// -------------------------------------------------------------------------
	// sort by address value
	resetrom_size  				  = (unsigned int )(&resetrom_end  			   - resetrom);
	mips_resetrom_size  		  = (unsigned int )(&mips_resetrom_end  	   - mips_resetrom);
    hwsetting_size 				  = (unsigned int )(&hwsetting_end 			   - hwsetting);	//hwsetting + signature for both secure/non-secure
    hasharray_size                = (unsigned int )(&hasharray_end 			   - hasharray);	//bootcode for secure/non-secure
	signature_size                = (unsigned int )(&signature_end 			   - signature);	//bootcode signature for secure/non-secure

	linux_rescue_hasharray_size   = (unsigned int )(&linux_rescue_hasharray_end - linux_rescue_hasharray);
	linux_rescue_signature_size   = (unsigned int )(&linux_rescue_signature_end - linux_rescue_signature);
    hwsetting_sig_size 	          = (unsigned int )(&hwsetting_sig_image_end    - hwsetting_sig_image);
	dcas_key_sig_size 	          = (unsigned int )(&dcas_key_sig_image_end     - dcas_key_sig_image);
	logo_size      				  = (unsigned int )(&logo_end      			   - logo);
    logo2_size     				  = (unsigned int )(&logo2_end     			   - logo2);
    logo3_size     				  = (unsigned int )(&logo3_end     			   - logo3);
    logo4_size     				  = (unsigned int )(&logo4_end     			   - logo4);
    logo5_size     				  = (unsigned int )(&logo5_end     			   - logo5);
    logo6_size     				  = (unsigned int )(&logo6_end     			   - logo6);
    logo7_size     				  = (unsigned int )(&logo7_end     			   - logo7);
    logo8_size     				  = (unsigned int )(&logo8_end     			   - logo8);

    programmed_img_size 		  = hasharray_size;
	programmed_img_base           = hasharray;			//without signature

	programmed_img_sig_base		  = signature;

	programmed_fsbl_size          = (unsigned int )(&fsbl_end - fsbl);
    programmed_fsbl_base          = fsbl;
	programmed_fsbl_sig_size      = (unsigned int )(&fsbl_signature_end - fsbl_signature);
    programmed_fsbl_sig_base      = fsbl_signature;
	programmed_fsbl_os_size       = (unsigned int )(&fsbl_os_end - fsbl_os);
    programmed_fsbl_os_base       = fsbl_os;
	programmed_fsbl_os_sig_size   = (unsigned int )(&fsbl_os_signature_end - fsbl_os_signature);
    programmed_fsbl_os_sig_base   = fsbl_os_signature;
	programmed_rsa_pub_size   = (unsigned int )(&rsa_pub_end - rsa_pub);
    programmed_rsa_pub_base       = rsa_pub;

	if (signature_size>=sizeof(unsigned int))
		programmed_img_sig_size		  = signature_size;
	else
		programmed_img_sig_size = 0;


	programmed_linux_rescue_img_size = linux_rescue_hasharray_size;
	programmed_linux_rescue_img_base = linux_rescue_hasharray;
	programmed_linux_rescue_sig_size = linux_rescue_signature_size;
	programmed_linux_rescue_sig_base = linux_rescue_signature;

#ifdef ROMCODE_ON_SPI
    spi_resetrom_addr  			 = (unsigned char *)SPI_CODE_PART1; //assign arm romcode start address
    spi_mips_resetrom_addr  	 = (unsigned char *)SPI_CODE_PART11; //assign lexra romcode start address
    spi_param_addr 				 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE);
    spi_hwsetting_addr 			 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE + SPI_MAX_PARAM_SIZE); //assign hw setting start address, moidfy by angus, original value is 0xb8108000
#else
    spi_resetrom_addr			 = NULL;
    spi_mips_resetrom_addr  	 = NULL; 
    spi_param_addr 				 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE);
    spi_hwsetting_addr 			 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE + SPI_MAX_PARAM_SIZE); //assign hw setting start address, moidfy by angus, original value is 0xb8108000
#endif
	spi_bootcode_addr            = spi_hwsetting_addr + hwsetting_size;
	spi_bootcode_sig_addr        = spi_bootcode_addr + hasharray_size;
	spi_fsbl_addr                = spi_bootcode_sig_addr + signature_size;
	spi_fsbl_sig_addr            = spi_fsbl_addr + programmed_fsbl_size;
	spi_fsbl_os_addr             = spi_fsbl_sig_addr + programmed_fsbl_sig_size;
	spi_fsbl_os_sig_addr         = spi_fsbl_os_addr + programmed_fsbl_os_size;    
	spi_rescue_addr            = spi_fsbl_os_sig_addr + programmed_fsbl_os_sig_size;
	spi_rescue_sig_addr        = spi_rescue_addr + linux_rescue_hasharray_size;
	spi_rsa_pub_addr             = SPI_CODE_PART1+0x80000;
	spi_bootcode_addr2           = SPI_CODE_PART2;
	spi_bootcode_addr3           = SPI_CODE_PART3;

	rtprintf("*** %s %d : resetrom_size                      = 0x%08x\n", __FUNCTION__, __LINE__, resetrom_size);
	rtprintf("*** %s %d : mips_resetrom_size                 = 0x%08x\n", __FUNCTION__, __LINE__, mips_resetrom_size);
	rtprintf("*** %s %d : hwsetting_size                     = 0x%08x\n", __FUNCTION__, __LINE__, hwsetting_size);
	rtprintf("*** %s %d : hwsetting_sig_size                 = 0x%08x\n", __FUNCTION__, __LINE__, hwsetting_sig_size);
	rtprintf("*** %s %d : hasharray_size                     = 0x%08x\n", __FUNCTION__, __LINE__, hasharray_size);
	rtprintf("*** %s %d : signature_size                     = 0x%08x\n", __FUNCTION__, __LINE__, signature_size);
	rtprintf("*** %s %d : bootcode2_boot_hasharray_size      = 0x%08x\n", __FUNCTION__, __LINE__, bootcode2_boot_hasharray_size);
	rtprintf("*** %s %d : bootcode2_boot_signature_size      = 0x%08x\n", __FUNCTION__, __LINE__, bootcode2_boot_signature_size);
	rtprintf("*** %s %d : bootcode3_boot_hasharray_size      = 0x%08x\n", __FUNCTION__, __LINE__, bootcode3_boot_hasharray_size);
	rtprintf("*** %s %d : bootcode3_boot_signature_size      = 0x%08x\n", __FUNCTION__, __LINE__, bootcode3_boot_signature_size);
	rtprintf("*** %s %d : programmed_img_base                = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)programmed_img_base);
	rtprintf("*** %s %d : programmed_img_size                = 0x%08x\n", __FUNCTION__, __LINE__, programmed_img_size);
	rtprintf("*** %s %d : bootcode2_boot_programmed_img_base = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)bootcode2_boot_programmed_img_base);
	rtprintf("*** %s %d : bootcode2_boot_programmed_img_size = 0x%08x\n", __FUNCTION__, __LINE__, bootcode2_boot_programmed_img_size);
	rtprintf("*** %s %d : bootcode3_boot_programmed_img_base = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)bootcode3_boot_programmed_img_base);
	rtprintf("*** %s %d : bootcode3_boot_programmed_img_size = 0x%08x\n", __FUNCTION__, __LINE__, bootcode3_boot_programmed_img_size);
	rtprintf("*** %s %d : linux_rescue_hasharray             = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)linux_rescue_hasharray);
	rtprintf("*** %s %d : linux_rescue_hasharray_size        = 0x%08x\n", __FUNCTION__, __LINE__, linux_rescue_hasharray_size);
	rtprintf("*** %s %d : linux_rescue_signature             = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)linux_rescue_signature);
	rtprintf("*** %s %d : linux_rescue_signature_size        = 0x%08x\n", __FUNCTION__, __LINE__, linux_rescue_signature_size);
	rtprintf("*** %s %d : dcas_key_sig_size                  = 0x%08x\n", __FUNCTION__, __LINE__, dcas_key_sig_size);
    /* reserve one block in 0xbecf_f000 ~ 0xbecf_ffff for ext_param */
    total_block_cnt = total_block_cnt - 1;

    /***********************************************************************
     * determine flash type and program flow
     * 0 for nand flash		FLASH_TYPE_NAND
     * 1 for spi nor		FLASH_TYPE_SPI
     * 2 for eMMC		FLASH_TYPE_EMMC
     ***********************************************************************/
    verify_after_write = 0;
    force_secure = 0;
    test_secure = 0;
    noreset = 0;

	flash_type = FLASH_TYPE_SPI;
	
    rtprintf("flash_type: ");
    #ifdef FOR_ICE_LOAD
    prints("flash_type: ");
    #endif
    switch( flash_type )
    {
    	case FLASH_TYPE_SPI:
            #ifdef FOR_ICE_LOAD
            prints("SPI\n");
            #endif
	    	rtprintf("SPI\n");
	    	flash_magicno     = FLASH_MAGICNO_NOR_SERIAL;
	    	do_erase          = do_erase_s;
	    	do_write          = do_write_s;
	    	do_identify       = do_identify_s;
	    	do_init           = do_init_s;
	    	do_exit           = do_exit_s;
	    	do_read           = NULL;
	    	do_hide_hwsetting = NULL;
	    	env_param_addr    = (unsigned char *)SPI_ENV_PARAM_ADDR;
    		break;

    	default:
            #ifdef FOR_ICE_LOAD
            prints("unknown!\n");
            #endif
    		rtprintf("unknown!\n");
    		return -1;

    		break;
    }

    /***********************************************************************
     * update bootcode size of the HW setting table
     ***********************************************************************/

    /***********************************************************************
     * calculate images start address
     ***********************************************************************/
	logo_addr  = 0x0;
	logo2_addr = 0x0;
	logo3_addr = 0x0;
	logo4_addr = 0x0;
	logo5_addr = 0x0;
	logo6_addr = 0x0;
	logo7_addr = 0x0;
	logo8_addr = 0x0;
    linux_sec1_addr = 0;
    linux_sec1_size = 0;
    linux_sec2_addr = 0;
    linux_sec2_size = 0;
   
    if (flash_magicno == FLASH_MAGICNO_NOR_SERIAL)	// NOR flash case
    {
	    res = check_secure_boot();
	    if( res == DCAS_SECURE_BOOT ) {
	    	temp = ((programmed_img_size + hwsetting_size + dcas_key_sig_size ) / block_size )+ 1;
	    }
		else {
        	temp = ((programmed_img_size + hwsetting_size) / block_size )+ 1;
		}
        total_block_cnt -= temp;
        temp_ptr = (unsigned char *)(spi_hwsetting_addr + (temp * block_size));
        
    }
    else
    {
    	rtprintf("unknown flash_magicno\n");
    	return -66;
    }
#if 0	
    /***********************************************************************
     * assign value to param object
     ***********************************************************************/
    param.secure_mode        	= check_secure_boot();
    param.flash_type 		 	= flash_magicno;
    param.region     		 	= 0;

	param.mac_hi     		 	= Param_MAC_hi;
	param.mac_lo     		 	= Param_MAC_lo;

    param.array_img_saddr        = 0;
    param.array_img_size         = 0;
    param.secure_mode            = check_secure_boot();
    param.rescue_img_size        = programmed_linux_rescue_img_size;
    param.rescue_img_addr        = 0;
    param.rescue_img_part0_saddr = linux_sec1_addr;
    param.rescue_img_part0_len   = linux_sec1_size;
    param.rescue_img_part1_saddr = linux_sec2_addr;
    param.rescue_img_part1_len   = linux_sec2_size;

	//clear logo value if logo2, logo3 ,logo4 was not used
	param.logo_img_saddr         = 0;
	param.logo2_img_saddr        = 0;
	param.logo3_img_saddr        = 0;
	param.logo4_img_saddr        = 0;
	param.logo5_img_saddr        = 0;
	param.logo6_img_saddr        = 0;
	param.logo7_img_saddr        = 0;
	param.logo8_img_saddr        = 0;

	param.logo_img_len           = 0;
	param.logo2_img_len          = 0;
	param.logo3_img_len          = 0;
	param.logo4_img_len          = 0;
	param.logo5_img_len          = 0;
	param.logo6_img_len          = 0;
	param.logo7_img_len          = 0;
	param.logo8_img_len          = 0;

	param.logo_type              = 0;
	param.logo2_type             = 0;
	param.logo3_type             = 0;
	param.logo4_type             = 0;
	param.logo5_type             = 0;
	param.logo6_type             = 0;
	param.logo7_type             = 0;
	param.logo8_type             = 0;

	param.logo_offset     		 = 0;
	param.logo2_offset    		 = 0;
	param.logo3_offset    		 = 0;
	param.logo4_offset    		 = 0;
	param.logo5_offset    		 = 0;
	param.logo6_offset    		 = 0;
	param.logo7_offset    		 = 0;
	param.logo8_offset    		 = 0;

	param.logo_reg_5370   		 = 0;
	param.logo2_reg_5370  		 = 0;
	param.logo3_reg_5370  		 = 0;
	param.logo4_reg_5370  		 = 0;
	param.logo5_reg_5370  		 = 0;
	param.logo6_reg_5370  		 = 0;
	param.logo7_reg_5370  		 = 0;
	param.logo8_reg_5370  		 = 0;

	param.logo_reg_5374   		 = 0;
	param.logo2_reg_5374  		 = 0;
	param.logo3_reg_5374  		 = 0;
	param.logo4_reg_5374  		 = 0;
	param.logo5_reg_5374  		 = 0;
	param.logo6_reg_5374  		 = 0;
	param.logo7_reg_5374  		 = 0;
	param.logo8_reg_5374  		 = 0;

	param.logo_reg_5378   		 = 0;
	param.logo2_reg_5378  		 = 0;
	param.logo3_reg_5378  		 = 0;
	param.logo4_reg_5378  		 = 0;
	param.logo5_reg_5378  		 = 0;
	param.logo6_reg_5378  		 = 0;
	param.logo7_reg_5378  		 = 0;
	param.logo8_reg_5378  		 = 0;

	param.logo_reg_537c   		 = 0;
	param.logo2_reg_537c  		 = 0;
	param.logo3_reg_537c  		 = 0;
	param.logo4_reg_537c  		 = 0;
	param.logo5_reg_537c  		 = 0;
	param.logo6_reg_537c  		 = 0;
	param.logo7_reg_537c  		 = 0;
	param.logo8_reg_537c  		 = 0;

	// clear hdmi key
	for (i = 0; i < sizeof(param.hdmi_key1); i++)
		param.hdmi_key1[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key2); i++)
		param.hdmi_key2[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key3); i++)
		param.hdmi_key3[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key4); i++)
		param.hdmi_key4[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key5); i++)
		param.hdmi_key5[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key6); i++)
		param.hdmi_key6[i] = 0;

	set_memory(param.custom_field, 0, sizeof(param.custom_field));
    param.env_param_saddr = env_param_addr;
    param.data_start_blk = 0;

#endif
    //dump 'Begin' string to RS232 to notify uset that flash write start to program
	#ifdef FOR_ICE_LOAD
    prints("begin: \n");
    #endif
    rtprintf("Begin:");

	if ( flash_magicno == FLASH_MAGICNO_NOR_SERIAL)
	{
	   	  
	    /***********************************************************************
	     * copy parameters in flash to DDR
	     ***********************************************************************/
	    for (idx = 0; idx < SPI_MAX_PARAM_SIZE; idx +=4) {
			rtd_outl( (PARAMETER_TMP_ADDR + idx) ,rtd_inl((unsigned int)(SPI_ENV_PARAM_ADDR + idx))); //copy to ddr : 0x02400000 , len: 0x10000
		}
        
	    /***********************************************************************
	     * set pin mux
	     ***********************************************************************/
	    set_spi_pin_mux();
	    if ((*do_identify)(&device) < 0) {
	    	rtprintf("error identify flash!!\n");
            #ifdef FOR_ICE_LOAD
            prints("error identify flash!!\n");
            #endif
	    	return -2;
	    }
	    #ifdef FOR_ICE_LOAD
        prints("init\n");
        #endif

	    (*do_init)(device);

		//erase first 1MB
        #ifdef FOR_ICE_LOAD
        prints("spi : erase 1MB from 0x");
        print_hex(SPI_CODE_PART1);
        prints("\n");
        #endif
		rtprintf("spi : erase 1MB from 0x%08x\n", SPI_CODE_PART1);
	    if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART1, 0x00100000) !=0 ) {
			return -3;
		}

#if 0 // dump flash
		spi_switch_read_mode();
		spi_hexdump("spi data", SPI_CODE_PART1, 512);
#endif

#ifdef ROMCODE_ON_SPI
		//arm
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write arm romcode, start=0x");
        print_hex(spi_resetrom_addr);
        prints(", len=0x");
        print_hex(resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write arm romcode, start=0x%08x, len=0x%08x\n", spi_resetrom_addr, resetrom_size);
	    if ((*do_write)(device, resetrom, (unsigned int *)spi_resetrom_addr, resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
		//lexra
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write lexra romcode, start=0x");
        print_hex(spi_mips_resetrom_addr);
        prints(", len=0x");
        print_hex(mips_resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write lexra romcode, start=0x%08x, len=0x%08x\n", spi_mips_resetrom_addr, mips_resetrom_size);
	    if ((*do_write)(device, mips_resetrom, (unsigned int *)spi_mips_resetrom_addr, mips_resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
#endif
#if 1
		//for secure / non-secure
		//hwsetting
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write hw setting&signature, start=0x");
        print_hex(spi_hwsetting_addr);
        prints(", len=0x");
        print_hex(hwsetting_size);
        prints("\n");
        #endif
		spi_hwsetting_addr= 0x1810c000;
	   	    if ((*do_write)(device, hwsetting, (unsigned int *)spi_hwsetting_addr, hwsetting_size, 0, 0)!= 0 ) {
	        return -5;
	    }
#endif		
		//bootcode
		spi_bootcode_addr= 0x18100000;
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write bootcode, start=0x");
        print_hex(spi_bootcode_addr);
        prints(", len=0x");
        print_hex(programmed_img_size);
        prints("\n");
        #endif	    
	    if ((*do_write)(device, programmed_img_base, (unsigned int *)spi_bootcode_addr, programmed_img_size, 0, 0)!= 0 ) {
	        return -6;
	    }
		//bootcode signature
	    /*if (programmed_img_sig_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write bootcode signature, start=0x");
            print_hex(spi_bootcode_addr);
            prints(", len=0x");
            print_hex(programmed_img_sig_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write bootcode signature, start=0x%08x, len=0x%08x\n", spi_bootcode_addr, programmed_img_sig_size);
	    	if ((*do_write)(device, programmed_img_sig_base, (unsigned int *)spi_bootcode_sig_addr, programmed_img_sig_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }*/
      
	 
	    /***********************************************************************
	        * prepare for hwsetting signature or DCAS key1

	        ***********************************************************************/	    
#if 0			
	    // write parameter in bootcode1
	    #ifdef FOR_ICE_LOAD
        prints("\nspi : write parameter, start=0x");
        print_hex(spi_param_addr);
        prints(", len=0x");
        print_hex(sizeof(t_extern_param));
        prints("\n");
        #endif
	    rtprintf("\nspi : write parameter, start=0x%08x, len=0x%08x\n", spi_param_addr, sizeof(t_extern_param));
	    if ((*do_write)(device, (unsigned char *)&param, (unsigned int *)spi_param_addr, sizeof(t_extern_param), 0, 0)!= 0 ) {
	        return -14;
	    }
#endif
#if 0 // dump flash
		spi_switch_read_mode();
		spi_hexdump("spi data", spi_param_addr, 64);
		spi_hexdump("spi data", spi_bootcode_addr2, 64);
		spi_hexdump("spi data", spi_bootcode_addr3, 64);
#endif

	    #ifdef FOR_ICE_LOAD
        prints("exit\n");
        #endif
	    /* Reset Command */
	    (*do_exit)(device);

	}
	
    //dump 'Finish' string to RS232
    #ifdef FOR_ICE_LOAD
    prints("Finish\n");
    #endif
    rtprintf("Finish\n");
	#ifndef FPGA
	    if (noreset == 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("reset...\n");
            #endif
	        rtprintf("reset...\n");
            watchdog_reset();
    }
	#endif

	#ifdef FOR_ICE_LOAD
    prints("end\n");
    #endif
    return 0;
}
