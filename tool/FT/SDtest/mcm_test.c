#include <asm/io.h>
#include <asm/arch/io.h>
#include <asm/arch/system.h>
#include <asm/system.h>
#include <common.h>
#include <asm/arch/rbus/misc_reg.h>
#include <asm/arch/rbus/crt_reg.h>

#include <test_pattern/system.h>
#include <test_pattern/mcp_defines.h>


#define ARM_STATR_BASE 0x0 
#undef CONFIG_SYS_NON_CACHE_LEN
#define CONFIG_SYS_NON_CACHE_LEN 0x40000


#define MD_BASE 	0x03000000
#define MCP_DT_BASE 0x03020000
//#define CP_SRC  	0x01000000
#define CP_DST  	0x03030000
#define TEST_SIZE   0x100000	//1M
//#define CP_LENGTH 0x400 
#define LEXTRA_TEST_BASE   0x01b00000
#define BYTE_TEST_BASE   0x02000000
#define HEAP_BASE	(UBOOT_HEAP_RELOCATION_ADDR & ~(TEST_SIZE-1))

#define MCM_DEBUG 1

#if MCM_DEBUG
#define MCM_DBG(format, ...) printf(format , ## __VA_ARGS__)
#else
#define MCM_DBG(format, ...) 
#endif

DECLARE_GLOBAL_DATA_PTR;
extern int _f_AE_test_pattern_img, _e_AE_test_pattern_img;

static void diag_pass(void); 
static void diag_fail(void); 

void enter_ddr_self_refresh_mode(void)
{	
   //IGPIO3
   //0x1800_7310, bit 11:10 = 0
   //0x1800_7100, bit 3 = 1
   //0x1800_7104, bit 3 = 1
   rtd_maskl(0x18007310, ~(_BIT11|_BIT10), 0);
   rtd_setbits(0x18007100,_BIT3);
   rtd_setbits(0x18007104,_BIT3);
   MCM_DBG("0x18007310=%x 0x18007100=%x 0x18007104=%x\n",readl(0x18007310),readl(0x18007100),readl(0x18007104)); 		

   printf("enter_ddr_self_refresh\n");
   rtd_setbits(0x18008828,_BIT3);
}

void exit_ddr_self_refresh_mode(void)
{
	printf("exit_ddr_self_refresh 0x18008828=%x\n",readl(0x18008828));
	
	rtd_setbits(0x18008828,_BIT2);	
	writel(0x3,0x1800899c);
   
}

int byte_verify(unsigned int start_add,unsigned int length,unsigned int size)
{
	ulong start;
	unsigned int addr;
	unsigned int pattern_0 = 0xa5;
	unsigned int pattern_1 = 0x5a;
	int count=0;
	
	for (addr = start_add;addr < start_add + length;addr++)	 
	{						
		writeb(pattern_0,addr);
	}	
	MCM_DBG("range0=%x ~ %x\n",addr - size,addr);
		
	for(count = addr - size; count < addr; count=count+4 )
	{
		if( readb(count) != pattern_0)
			return -1;
		else		
			writeb(pattern_1,addr);
	}
	MCM_DBG("range1=%x ~ %x\n",addr - size,addr);
	for(count = addr - size; count < size; count=count+4)
	{
		if( readb(count) != pattern_1)
			return -1;				
	}
	return 0;				
}



int word_verify(unsigned int start_add,unsigned int length,unsigned int size)
{

	unsigned int addr;
	unsigned int pattern_0 = 0xaaaa5555;
	unsigned int pattern_1 = 0x5555aaaa;
	bd_t *bd = gd->bd;
	int count=0;
	
	for (addr = start_add;
	     addr < start_add + length;
	     addr=addr+4)	 
	{
		
		if ( ( (ARM_STATR_BASE)  <= addr) && addr <= (ARM_STATR_BASE + ARM_ROMCODE_SIZE) ) {			
			continue;
		}	
		else if( ( (CONFIG_SYS_TEXT_BASE) <= addr ) && addr <= ((unsigned int)gd->bd + sizeof(bd_t)) ) {
			continue;
		}
		else if ( ( (RBUS_BASE_VIRT)  <= addr) && addr <= (RBUS_BASE_VIRT+RBUS_BASE_SIZE) ) {
			continue;
		}
		else if( ( (SPI_FLASH_BASE_VIRT) <= addr ) && addr <= (SPI_FLASH_BASE_VIRT+SPI_FLASH_BASE_SIZE) ) {
			continue;
		}		
		else if( ( HEAP_BASE <= addr ) && addr <= (UBOOT_HEAP_RELOCATION_ADDR + CONFIG_SYS_NON_CACHE_LEN) ) {	
			continue;
		}
							
		*((volatile unsigned int*)addr) = pattern_0;
	}	
	MCM_DBG("range0=%x ~ %x\n",addr - size,addr);
		
	for(count = addr - size; count < addr; count=count+4 )
	{
		if(*((volatile unsigned int*)count) != pattern_0)
			return -1;
		else		
			*((volatile unsigned int*)count) = pattern_1;
	}
	MCM_DBG("range1=%x ~ %x\n",addr - size,addr);
	for(count = addr - size; count < size; count=count+4)
	{
		if(*((volatile unsigned int*)count) != pattern_1)
			return -1;				
	}
		
	return 0;
		
}

int cp_isr(void)
{
    unsigned int para_k1=0;
    unsigned int para_k0=0;
	ulong start = get_timer(0);	
	ulong delay = 5000;
	
	__asm__ __volatile__("": : :"memory");
	while (get_timer(start) < delay) {
		
		mdelay(15);
		__asm__ __volatile__("": : :"memory");
		para_k1 = get_MCP_STATUS_reg;
		para_k0 = (para_k1 & MCP_STATUS_compare_mask);			
		if(para_k0 == MCP_STATUS_compare(1))
        {					
            goto NEXT;
        }        
    }

	diag_fail();
	return -1;

NEXT:	
    para_k1 = get_MCP_DES_COUNT_reg;
    para_k1 = get_MCP_DES_COMPARE_reg;
    para_k1 = para_k1 + 1;
    set_MCP_DES_COMPARE_reg(para_k1);
    set_MCP_STATUS_reg(MCP_STATUS_compare(1) | MCP_STATUS_write_data(0));
  	
	start = get_timer(0);
	__asm__ __volatile__("": : :"memory");
	while (get_timer(start) < delay) {
		
		udelay(50);
		__asm__ __volatile__("": : :"memory");
		para_k1 = get_MCP_DES_COUNT_reg;		
		if(para_k1 == 1)
        {				            		
            MCM_DBG("diag_pass\n");
			break;
        }        
    }
	    
	DELAY_C(10);
    set_MCP_CTRL_reg(MCP_CTRL_go(1) | MCP_CTRL_write_data(1));
	return 0;
	
}

int mem_test_segment(unsigned int start , unsigned int len, unsigned int pattern)
{
	MCM_DBG("test 0x%08x ~ 0x%08x pattern=%x\n",start,start+len-1,pattern);
		
	set_MCP_DES_COUNT_reg(0);
	
	//fill md cmd
	*((volatile unsigned int*) MD_BASE) = 0x00000045;
	*((volatile unsigned int*) (MD_BASE+4)) = start;	//CP_SRC為MD要寫入的DRAM address(也是CP等會要讀出的address)
//	*((volatile unsigned int*) (MD_BASE+8)) = 0x87;	//改為0xa5 or 0x5a (constant value)
	*((volatile unsigned int*) (MD_BASE+8)) = pattern;	
	*((volatile unsigned int*) (MD_BASE+0xc)) = len; //寫入的constant數量
	
	//fill md ring buffer
	set_MD_SMQBASE_reg(MD_BASE);
	set_MD_SMQLIMIT_reg((MD_BASE+0x100));
	set_MD_SMQRDPTR_reg(MD_BASE);
	set_MD_SMQWRPTR_reg((MD_BASE+0x10));
	set_MD_SMQ_CNTL_reg(0x7);
		
    SET_DT_WD0(MCP_DT_BASE, MCP_MODE(E_MODE_SHA256) | MCP_ENDE(E_ENDE_DE) | MCP_BCM(E_BCM_ECB) );
   
    SET_DT_KEY0(MCP_DT_BASE, 0x6A09E667);
    SET_DT_KEY1(MCP_DT_BASE, 0xBB67AE85);
    SET_DT_KEY2(MCP_DT_BASE, 0x3C6EF372);
    SET_DT_KEY3(MCP_DT_BASE, 0xA54FF53A);
    SET_DT_KEY4(MCP_DT_BASE, 0x510E527F);
    SET_DT_KEY5(MCP_DT_BASE, 0x9B05688C);
    SET_DT_INI_KEY0(MCP_DT_BASE, 0x1F83D9AB);
    SET_DT_INI_KEY1(MCP_DT_BASE, 0x5BE0CD19);
    SET_DT_INI_KEY2(MCP_DT_BASE, 0x12345678);
    SET_DT_INI_KEY3(MCP_DT_BASE, 0x12345678);
    SET_DT_SADR(MCP_DT_BASE, start);
    SET_DT_DADR(MCP_DT_BASE, CP_DST);
    SET_DT_BC(MCP_DT_BASE, len);

    set_MCP_BASE_reg(MCP_DT_BASE);
    set_MCP_LIMIT_reg(MCP_DT_BASE + DT_SIZE * (1+1));
    set_MCP_RDPTR_reg(MCP_DT_BASE);
    set_MCP_WRPTR_reg(MCP_DT_BASE + DT_SIZE * 1);
    set_MCP_DES_INI_KEY_0_reg(0x10203040);
    set_MCP_DES_INI_KEY_1_reg(0x01020304);
    set_MCP_EN_reg(MCP_EN_compare_en(1) | MCP_EN_write_data(1));
    set_MCP_DES_COMPARE_reg(MCP_DES_COMPARE_compare(1));
	//printf("MD idle?\n");
	while((get_MD_SMQ_CNTL_reg & 0x8) != 0x8); //check md idle 
	//printf("MD idle\n");
	set_MD_SMQ_CNTL_reg(0x2); // diable go bit

    set_MCP_CTRL_reg(MCP_CTRL_go(1) | MCP_CTRL_write_data(1)); // cp go
	
	return cp_isr();
}

void mem_test_entry(void)
{
	int i;
	unsigned int addr;
	bd_t *bd = gd->bd;
		
	//start CPU word access W/R/W/R of MD descriptor
	if(word_verify(MD_BASE,TEST_SIZE,TEST_SIZE))
		return;
		
	unsigned char *a,*b;
	a = (unsigned char *)&_e_AE_test_pattern_img;
	b = (unsigned char *)&_f_AE_test_pattern_img;
	unsigned int pattern_0=0xa5;
	unsigned int pattern_1=0x5a;

	MCM_DBG("_f_AE_test_pattern_img=%x\n",_f_AE_test_pattern_img);
	MCM_DBG("_e_AE_test_pattern_img=%x\n",_e_AE_test_pattern_img);
	MCM_DBG("a=%x b=%x a-b=%x\n",a,b,a-b);
	MCM_DBG("bd->bi_dram[0].start=%x\n",bd->bi_dram[0].start);
	MCM_DBG("bd->bi_dram[0].start + bd->bi_dram[0].size=%x\n",bd->bi_dram[0].start + bd->bi_dram[0].size);
	MCM_DBG("uboot txt=%x\n",(unsigned int)gd->bd + sizeof(bd_t));

	
	for (i = bd->bi_dram[0].start >>20;
	     i < (bd->bi_dram[0].start + bd->bi_dram[0].size) >> 20;
	     i++) {

		addr = i << 20;
	
		if ( ( (ARM_STATR_BASE)  <= addr) && addr <= (ARM_STATR_BASE + ARM_ROMCODE_SIZE) ) {			
			printf("skip ARM/Lextra 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1);
			continue;
		}	
		else if( ( (CONFIG_SYS_TEXT_BASE) <= addr ) && addr <= ((unsigned int)gd->bd + sizeof(bd_t)) ) {
			printf("skip uboot 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1);
			continue;
		}
		else if ( ( (RBUS_BASE_VIRT)  <=addr) && addr <= (RBUS_BASE_VIRT+RBUS_BASE_SIZE) ) {
			printf("skip Rbus 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1);
			continue;
		}
		else if( ( (SPI_FLASH_BASE_VIRT) <= addr ) && addr <= (SPI_FLASH_BASE_VIRT+SPI_FLASH_BASE_SIZE) ) {
			printf("skip Spi 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1);
			continue;
		}		
		else if( ( HEAP_BASE <= addr ) && addr <= (UBOOT_HEAP_RELOCATION_ADDR + CONFIG_SYS_NON_CACHE_LEN) ) {		
			
			printf("skip heap 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1);
			continue;
		}
		else if( ( MD_BASE <= addr ) && addr < (MD_BASE + TEST_SIZE)){
			printf("skip md/cp descriptor 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1 );
			continue;	
		}
		else if( ( LEXTRA_TEST_BASE <= addr ) && addr < (LEXTRA_TEST_BASE + (a-b))){
			printf("skip lextra test pattern 0x%x ~0x%x \n",addr, addr+TEST_SIZE-1 );
			continue;	
		}
					
		if(mem_test_segment(addr,TEST_SIZE,pattern_0))
			return;
		
		if(mem_test_segment(addr,TEST_SIZE,pattern_1))
			return;
			
	}
	
	if(!byte_verify(BYTE_TEST_BASE,TEST_SIZE,TEST_SIZE))
		diag_pass();
	
}

static void diag_pass(void) {

	rtd_maskl(CRT_MUXPAD1, ~(_BIT19|_BIT18),0);	
    rtd_setbits(GP0DIR,_BIT28);	
    rtd_setbits(GP0DATO,_BIT28);	
    printf("1095 GPIO28 high\n");
}

static void diag_fail(void) {
	printf("diag_fail\n");
}
