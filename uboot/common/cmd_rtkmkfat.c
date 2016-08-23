/*
 * Realtek fat32 format tool
 * jinn.cheng@realtek.com
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <part.h>
#include <usb.h>
#include <sata.h>
#include <part_efi.h>
#include <fat.h>
#include <rtkmkfat.h>

#define SEL_SATA 0
#define SEL_EMMC 1
#define SEL_USB  2

#define RTKMKFAT "rtkfat:"

#define RTKFAT_DEBUG(fmt, args...) \
    { \
        if ( debug ) { \
            printf("%s %03d: " fmt, RTKMKFAT, __LINE__, ##args); \
        } \
    }
#define RTKFAT_PRINT(fmt, args...) \
    { \
        printf("%s %03d: " fmt, RTKMKFAT, __LINE__, ##args); \
    }

extern int sata_curr_device;
extern block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];
extern unsigned int get_checksum(uchar *p, uint len);

DECLARE_GLOBAL_DATA_PTR;

static int debug;
static int dev_sel;
static int part_sel;
static unsigned int target_start_lba;;
static unsigned int target_szie;
static unsigned int target_cluster_szie;

/*
 *
 *
 *
 */
static void rtkfat_hexdump( const char * str, unsigned int start_address, unsigned int length )
{
    unsigned int i, j, rows, count;
    unsigned char * ptmp = (unsigned char *)start_address;
    printf("======================================================\n");
    printf("%s(base=0x%08x)\n", str, start_address);
    count = 0;
    rows = (length+((1<<4)-1)) >> 4;
    for( i = 0; ( i < rows ) && (count < length); i++ ) {
        printf("%03x :", i<<4 );
        for( j = 0; ( j < 16 ) && (count < length); j++ ) {

            printf(" %02x",  *ptmp );
            count++;
            ptmp++;
        }
        printf("\n");
    }
}

/*
 *
 *
 *
 */
int run_rtkfat_sata_partinfo( unsigned int dev_id, int part_no, unsigned long long * pGPT_base, unsigned long long * pGPT_szie )
{
	block_dev_desc_t *dev_desc = NULL;
	disk_partition_t cur_part_info; 
	
	if( dev_id != 0 ) {
		RTKFAT_PRINT("Error! only support dev_id 0\n", dev_id);
		return -1;
	}
	
	if( part_sel < 0 ) {
		RTKFAT_PRINT("part_sel %d error\n", part_sel);
		return -2;
	}
	
	dev_desc = get_dev("sata", dev_id);
	if (dev_desc == NULL) {
		RTKFAT_PRINT("Invalid sata device\n");
		return -3;
	}
	
	/* Read the partition table, if present */
	if (!get_partition_info(dev_desc, part_no, &cur_part_info)) {
		// find partition
	}
	else {
		RTKFAT_PRINT("Can not find partition info from part %d\n", part_no);
		return -4;
	}

#ifdef CONFIG_SYS_64BIT_LBA	
	RTKFAT_DEBUG("sata %x:%x start 0x%llx\n", dev_id, part_no, cur_part_info.start);
	RTKFAT_DEBUG("sata %x:%x size  0x%llx\n", dev_id, part_no, cur_part_info.size);
#else
	RTKFAT_DEBUG("sata %x:%x start 0x%lx\n", dev_id, part_no, cur_part_info.start);
	RTKFAT_DEBUG("sata %x:%x size  0x%lx\n", dev_id, part_no, cur_part_info.size);
#endif
	
#if 0 // force for debug
	*pGPT_base = target_start_lba = 0x258000;
	*pGPT_szie = 0x100000; /*512MB*/
#else
	*pGPT_base = cur_part_info.start;
	*pGPT_szie = cur_part_info.size;
#endif

	return 0;
}

// cluster size = 8
// sector size 0x0010_0000
// max cluster = 0x0010_0000 * 64/513 ~ 130816
// fat size = 130816 / 128 = 1022 = 0x3FE
// 
/*
 *
 *
 *
 */
int run_rtkfat_sata( unsigned int dev_id, unsigned long long bpa_base, unsigned long long total_sectors, unsigned int cluster_size )
{
	unsigned long long cur_lba;
    unsigned long long cur_blkcnt;
    unsigned long long blkcnt;
    unsigned long long useable_size;
    unsigned int fat_size;
    unsigned int total_clusters;
    block_dev_desc_t * dev_desc;
    boot_sector * pBPB;
    fat32_fsinfo * pFSINFO;
    void * pTemp;
    ALLOC_CACHE_ALIGN_BUFFER_PAD(dummy_data_512B, pData512B, 1, 512);
    pTemp = memalign(ARCH_DMA_MINALIGN, 8192);
    
    // show info
    RTKFAT_DEBUG("dev %d\n", dev_id);
    RTKFAT_DEBUG("bpa_base 0x%llx\n", bpa_base);
    RTKFAT_DEBUG("total_sectors 0x%llx\n", total_sectors); 
    RTKFAT_DEBUG("cluster_size 0x%08x\n", cluster_size);   

	if( !pTemp || !pData512B ) {
		RTKFAT_PRINT("allocate memory fail\n");
		return -1;
	}

	if( sata_curr_device < 0 ) {
        RTKFAT_PRINT("sata_curr_device %d\n", sata_curr_device);
        RTKFAT_PRINT("please init SATA first\n");
        return -2;
    }
    
    if( dev_id != 0 ) {
    	RTKFAT_PRINT("dev_id %d\n", dev_id);
        RTKFAT_PRINT("only support sata 0\n");
        return -3;
    }

    dev_desc = &sata_dev_desc[dev_id];

    if( total_sectors < 0x00010000 ) { // at least 32MB
    	return -10;
    }

    useable_size = total_sectors - 0x24;
    
    if( cluster_size == 1 ||
    	cluster_size == 2 ||
    	cluster_size == 4 ||
    	cluster_size == 8 ||
    	cluster_size == 16 ||
    	cluster_size == 32 ||
    	cluster_size == 64 ||
    	cluster_size == 128 )
    {
		total_clusters = ( useable_size * 64 ) / ( (64 * cluster_size) +1 );    		
	}
	else {
		RTKFAT_PRINT("cluster_size=%d error. (must be 1,2,4,8,16,32,64 or 128)\n", cluster_size);
		return -11;
	}
	
	if( total_clusters == 0 ) {
		RTKFAT_PRINT("total_clusters=%d error\n", total_clusters);
		return -12;
	}
    
    fat_size = total_clusters / 128;
    
    // show status
    RTKFAT_DEBUG("total_clusters 0x%08x\n", total_clusters);
    RTKFAT_DEBUG("fat_size 0x%08x\n", fat_size);
    RTKFAT_DEBUG("pData512B 0x%08x\n", pData512B);
    RTKFAT_DEBUG("pTemp 0x%08x\n", pTemp);

	// clear partition data
	memset(pTemp, 0, 8192);
	cur_lba = bpa_base;
	blkcnt = 0x24 + fat_size + fat_size + cluster_size;
	RTKFAT_PRINT("clear sata partition from 0x%llx to 0x%llx (total 0x%08x)\n", cur_lba, (cur_lba+blkcnt-1), blkcnt);

	while( blkcnt ) {
		if( blkcnt > 8 ) {
			cur_blkcnt = 8;
		}
		else {
			cur_blkcnt = blkcnt;
		}			
		if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pTemp) != cur_blkcnt)) {
	        RTKFAT_PRINT("write LBA %lld, cnt %lld fail\n", cur_lba, cur_blkcnt);
	        return -100;
	    }
	    if( (cur_lba&0x7F)==0 ) {
    		printf(".");
	    }
	    blkcnt -= cur_blkcnt;
	    cur_lba += cur_blkcnt;
	}
    printf("\n");
    
    // write BPF
    memcpy(pData512B, myBPB, sizeof(myBPB));
    pBPB = (block_dev_desc_t *)pData512B;
    pBPB->fat32_length = fat_size;
    pBPB->total_sect = total_sectors; 
    pBPB->reserved = 0x24;
    //rtkfat_hexdump("BPB", (unsigned int)pData512B, sizeof(myBPB));
    cur_lba = bpa_base;
    cur_blkcnt = 1;
	if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %lldd, cnt %lld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write BPF@LBA %lld(0x%llx) done\n", cur_lba, cur_lba);
	
	// write FSINFO
	memcpy(pData512B, myFS_INFO, sizeof(myFS_INFO));
    pFSINFO = (fat32_fsinfo *)pData512B;
    pFSINFO->free_count = total_clusters-1;
    pFSINFO->next_free = 3;
    //rtkfat_hexdump("FSINFO", (unsigned int)pData512B, sizeof(myFS_INFO));
    cur_lba = bpa_base+1;
    cur_blkcnt = 1;
	if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %lld, cnt %lld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FSINFO@LBA %lld(0x%llx) done\n", cur_lba, cur_lba);
	
	// write FAT1
	memcpy(pData512B, myFAT, sizeof(myFAT));
    //rtkfat_hexdump("FAT", (unsigned int)pData512B, sizeof(myFAT));
    cur_lba = bpa_base+0x24;
    cur_blkcnt = 1;
	if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %lld, cnt %lld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FAT1@LBA %lld(0x%llx) done\n", cur_lba, cur_lba);
	
	// write FAT2
	cur_lba = bpa_base+0x24+fat_size;
    cur_blkcnt = 1;
	if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %lld, cnt %lld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FAT2@LBA %lld(0x%llx) done\n", cur_lba, cur_lba);
	
	// init ROOT and weite 0-byte file entry
	memcpy(pData512B, myRootDir, sizeof(myRootDir));
    //rtkfat_hexdump("Root DIR", (unsigned int)pData512B, sizeof(myFAT));
    cur_lba = bpa_base+0x24+fat_size+fat_size;
    cur_blkcnt = 1;
	if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %lld, cnt %lld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write rootdir@LBA %lld(0x%llx) done\n", cur_lba, cur_lba);
    
    return 0;
}

/*
 *
 *
 *
 */
int run_rtkfat_gen(void)
{
    unsigned int ret_val;
    unsigned long long gpt_start_lba;
    unsigned long long gpt_size;
    
    ret_val = -1;
    gpt_start_lba = 0;
    gpt_size = 0;

#if 0 // force for debug
		target_start_lba = 0x258000;
		target_szie = 0x100000; /*512MB*/
		target_cluster_szie  = 8;
#endif

    if( dev_sel == SEL_SATA ) {
    	
    	if( !target_start_lba || !target_szie ) {
    		// read GPT table get partition info
    		run_rtkfat_sata_partinfo(0, part_sel, &gpt_start_lba, &gpt_size );
    	}
    	else {
    		gpt_start_lba = target_start_lba;
			gpt_size = target_szie;	
    	}

    	ret_val = run_rtkfat_sata(0, gpt_start_lba, gpt_size, target_cluster_szie);
	}
	
	if( dev_sel == SEL_EMMC ) {
		RTKFAT_PRINT("Not support eMMC\n");
		ret_val = -1;
	}
    
    RTKFAT_PRINT("ret val = 0x%08x(%s)\n", ret_val, ret_val == 0 ? "OK" : "FAIL" );
    	
	return ret_val;
}

/*
 *
 *
 *
 */
int do_rtkfat(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int cmd;

    dev_sel = -1;
    part_sel = -1;
    target_start_lba = 0;
    target_szie = 0;
    target_cluster_szie = 0;
    cmd = -1;

    debug = 0;

    // parse command
    if( argc > 1 ) {
    	if( strncmp( argv[1], "gen", 3 ) == 0 ) {
            cmd = 0;
            if( argc > 2 ) {
                if( strncmp( argv[2], "sata", 4 ) == 0  ) {
                	dev_sel = SEL_SATA;	
                }
                if( strncmp( argv[2], "emmc", 4 ) == 0  ) {
                	dev_sel = SEL_EMMC;	
                }
				do {
	                if( dev_sel < 0 ) {
	                	break;	
	                }
	                if( argc > 3 ) {
	                	if( strncmp( argv[3], "auto", 4 ) == 0  ) {
		                	if( argc > 4 ) {
	                			part_sel = simple_strtoul(argv[4], NULL, 16);
	                		}
	                		if( argc > 5 ) {
	                			if( strncmp( argv[5], "debug", 5 ) == 0  ) {
				            		debug = 1;
				            	}
				            	else {
	                				target_cluster_szie = simple_strtoul(argv[5], NULL, 16);				            		
	                				if( argc > 6 ) {
			                			if( strncmp( argv[6], "debug", 5 ) == 0  ) {
			                				debug = 1;
			                			}
			                		}
				            	}
	                		}
		                }
		                if( strncmp( argv[3], "manual", 6 ) == 0  ) {
		                	if( argc > 5 ) {
			                	target_start_lba = simple_strtoul(argv[4], NULL, 16);
			                	target_szie = simple_strtoul(argv[5], NULL, 16);
				            }
				            if( argc > 6 ) {
				            	if( strncmp( argv[6], "debug", 5 ) == 0  ) {
				            		debug = 1;
				            	}
				            	else {
			                		target_cluster_szie = simple_strtoul(argv[6], NULL, 16);
			                		if( argc > 7 ) {
			                			if( strncmp( argv[7], "debug", 5 ) == 0  ) {
			                				debug = 1;
			                			}
			                		}
			                	}
				            }
		                }
	                }	                
		        }
		        while(0);
            }
        }
    }
    
    if( target_cluster_szie == 0 ) {
    	target_cluster_szie = 8; // default
    }

    if( cmd < 0 || (dev_sel < 0) ) {
        RTKFAT_PRINT("Error: argu error\n", argv[1]);
        return -1;
    }
    
    if( part_sel < 0 ) {
    	if( !target_start_lba || !target_szie ) {
    		RTKFAT_PRINT("Error: start_lba(%d), size(%d) should not be zero if assigned\n", target_start_lba, target_szie );
        	return -1;
    	}    	
    }

    run_rtkfat_gen();

    return 0;
}

U_BOOT_CMD(
    rtkfat, 8, 0,   do_rtkfat,
    "Realtek FAT32 format utility v1.0",
    "\n(1)rtkfat gen sata auto part [cluster_size] [debug]"
    "\n(2)rtkfat gen sata manual startlba part_size [cluster_size] [debug]"
    "\n cluster_size: default 8"
);

