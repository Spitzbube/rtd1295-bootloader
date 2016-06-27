/****************************************************************************************
* Direct Test Name:      invalid_addr
* Author:         
* Date:           Tue Jun  5 15:47:09 CST 2007
* Description:	
* Copyright (C) 2007 Realtek Inc. All Right Reserved.
****************************************************************************************/
//#include "system.h"	
//#include "saturn.h"
//#include "etn.h"
//#include "mis_reg.h"
//#include "crt_sys_reg.h"
#include <asm/io.h>

#include <test_pattern/system.h>
#include <test_pattern/etn.h>
#include <asm/arch-rtd1195/io.h>
#include <config.h>

#define SPEED_m 0x2
#define DUPLEX_m 0x1

#define INTERRUPT_SCPU_ETN  54

const char data_array[64] ={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

const char tx_data_array[32] ={0x40,0x00,0x00,0xb0,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x00,0x00,0x00};

const char rx_data_array[64] ={0x00,0x30,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00};

static void diag_pass(void); 
static void diag_fail(void); 
void etn_isr();

void set_eri_reg(unsigned int addr, unsigned int data);
unsigned int get_eri_reg(unsigned int addr);
void set_ocp_reg(unsigned int ocp_addr, unsigned int ocp_data16b);
unsigned int get_ocp_reg(unsigned int ocp_addr);

void init_system();
void change_dma_control(unsigned int enable, unsigned int tx, unsigned int rx);
void pre_tally(unsigned int tally_bass_addr);
unsigned int dump_tally_counter(unsigned int dump_addr);
void post_tally();
void mii_if_cfg();

#define set_dram(addr,data)  (*((volatile unsigned int*) (addr|0xA0000000))=data)
#define get_dram(addr)       (*((volatile unsigned int*) (addr|0xA0000000)))

//#define set_reg(addr,data)  (*((volatile unsigned int*) addr)=data)
//#define get_reg(addr)       (*((volatile unsigned int*) addr))


#define get_reg(addr) __raw_readl(addr)
#define set_reg(addr,data) __raw_writel(data,addr)

unsigned int tx_dsc_base_addr, tx_data_base_addr, rx_dsc_base_addr, rx_data_base_addr, tally_base_addr;
//int main() {
int etn_test_entry(void) {
	unsigned int addr, data;
        unsigned int buf_addr, max_buf_size;
        unsigned int i;
        unsigned int tx_pkt_num, rx_pkt_num, tx_pkt_num_dut, rx_pkt_num_dut;
		printf("%s\n",__FUNCTION__);
//#ifdef SCPU_ARM
    //SET_INT(INTERRUPT_SCPU_ETN, etn_isr);
//#else
//	*((unsigned int*)HW_INTVEC_ADDR54_SCPU) = (void*)etn_isr;
//#endif

    tx_pkt_num = 1;
    rx_pkt_num = tx_pkt_num;  //lbk
	///include/test_pattern/wrap_a7_reg.h:#define A7_DEBUG_CTRL_reg_addr "0xB801D004"
	set_A7_DEBUG_CTRL_reg(0x01000000);
	// include/test_pattern/crt_sys_reg.h #define SYS_DEBUG_reg_addr  "0xB8000404"
    set_SYS_DEBUG_reg(0x00004596);
	printf("0x1801D004=%x 0x18000404=%x\n",get_reg(0x1801D004),get_reg(0x18000404));
	
	
	
    //1. enable iso for etn
    //enable etn pll
    data = get_ISO_POWERCUT_ETN_reg;
    data |= ( 0x1 <<0 );
    set_ISO_POWERCUT_ETN_reg(data); //bit0:1
    //enable etn pll
    data = get_ISO_PLL_ETN_reg;
    data = ( data & 0xF7FFFFFF | 0x1 << 26 | 0x1 << 14 | 0x1 << 13 );
    set_ISO_PLL_ETN_reg(data);
    //enable misc clk
    data = get_ISO_CLOCK_ENABLE_reg;
    data |= ( 0x1 << 0 | 0x1 << 11 | 0x1 << 12 );
    set_ISO_CLOCK_ENABLE_reg(data);
    //disable etn_reset
    data = get_ISO_SOFT_RESET_reg;
    data |= ( 0x1 << 10 );
    set_ISO_SOFT_RESET_reg(data);
    data = get_ISO_SOFT_RESET_reg;
    data |= ( 0x1 << 9 );
    set_ISO_SOFT_RESET_reg(data);
    //set etn_bpsgphy_mode
    data = get_ISO_ETN_TESTIO_reg;
    data |= ( 0x1 << 1);//bit1:1
    set_ISO_ETN_TESTIO_reg(data);  

    data = get_ISO_MUXPAD0_reg;
    data = data & 0x0FFFFFFF | 0x5<<28;
    set_ISO_MUXPAD0_reg(data);
    //2. init tx/rx dsc ring
    tx_dsc_base_addr  = 0x01010000;   //size: 0x80*32=0x1000
    tx_data_base_addr = 0x01100000;
    rx_dsc_base_addr  = 0x01080000;   //size: 0x80*32=0x1000
    rx_data_base_addr = 0x01800000;
    tally_base_addr   = 0x010f0000;
    max_buf_size = 0x1000;
    //init tx_dsc move to run.scr
    //init rx_dsc, move to run.scr

#if 0	
    //3. wait autoload done
    for(i=0;i<700000;i++) {
asm("\
.rept   16;\
        nop;\
.endr;\
");
    }
#else
	printf("delay 100 ms\n");
	mdelay(100);  //delay 10 ms.	
#endif	
	
	printf("wait autoload done\n");

    //3. wait autoload done
    addr = ETN_IO_CONFIG0;
    do {
        data = get_reg(addr);
	
asm("\
.rept   16;\
        nop;\
.endr;\
");
    }

//    addr = ETN_IO_CONFIG0;
//    do {
//       data = get_reg(addr);
//asm("\
//.rept   16;\
//        nop;\
//.endr;\
//");
//    }

    while((data & 0x00000010) == 0);  //wait bit[4] is 1 => break
	printf("start cfg_dut \n");
    //4. cfg_dut
    init_system();

    pre_tally(tally_base_addr);
    mii_if_cfg();
	printf("start config macloopback \n");
    //5. config macloopback
    addr = ETN_IO_TCR0;
    data = get_reg(addr);
    data = (data&0xfffd1fff) | (0x1<<15) | ((SPEED_m+0x1)<<13) | (0x1<<17);
    set_reg(addr,data);
	 printf("start step6 \n");
    //6. while (1) write tx packet
    //6-1 init pkt/dsc => have been at dram
    //6-2 set poll_flag
    addr = ETN_IO_IMR4;
    data = get_reg(addr);
    data = (data&0xffffff00) | (0x1<<6);
    set_reg(addr,data);
    //6-3 wati poll_flag been 0
    addr = ETN_IO_IMR4;
    do {
       data = get_reg(addr);
asm("\
.rept   16;\
        nop;\
.endr;\
");
    } while( (data&0x00000040) ==0x00000040);

	 printf("start report tally \n");
	 
    //7. report tally
//    do {
//asm("\
//.rept   200;\
//        nop;\
//.endr;\
//");
//       post_tally();
//       //txok
//       tx_pkt_num_dut = dump_tally_counter(tally_base_addr);
//       //rxok
//       rx_pkt_num_dut = dump_tally_counter(tally_base_addr+8);
//	   printf("tx=%x rx=%x\n",tx_pkt_num_dut,rx_pkt_num_dut);
//    } while (!((rx_pkt_num_dut==rx_pkt_num) && (tx_pkt_num_dut==tx_pkt_num) ));
 
    diag_pass();

 // while(1);

    return(0);
}

static void diag_pass()
{
//   const char data_array[74] = {0xff,0xff,0xff,0xff,
//                            0xff,0xff,0x52,0x54,
//                            0x4c,0x00,0x00,0x08,
//                            0x86,0xdd,0x64,0xd7,
//                             0x36,0x72,0x02,0xef,
//                             0x06,0x45,0xe3,0x82,
//                             0x4d,0x00,0xee,0xfd,
//                             0xa2,0x52,0x65,0xd4,
//                             0xf1,0xca,0xed,0xfd,
//                             0x32,0x12,0x8d,0x2a,
//                             0xf3,0xf1,0x6f,0x66,
//                             0x80,0xe2,0x02,0xf6,
//                             0x44,0xf2,0x4b,0xb2,
//                             0xc6,0xab,0x67,0x19,
//                            0xdd,0xbd,0x85,0xd8,
//                             0x78,0x80,0xa0,0x46,
//                             0x1d,0xda,0x50,0x04,
//                             0x8b,0x4b,0x08,0x24,
//                             0x8f,0x24};
//
//const char data_array[64] ={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

   char rd_dram(int dram_addr);

   int j;
   int dram_addr = 0x01800000; 
   for (j = 0; j < 64; j++)
   {
		//printf("rd_dram(dram_addr + %d)=%x\n",j,rd_dram(dram_addr + j));
        if (data_array[j] != rd_dram(dram_addr + j))
         {	
            diag_fail();	
			return;	
         }
   }
  
  // set_SYS_MUXPAD3_reg(0x10025555);
  // set_MIS_GP1DIR_reg(0x00800000);
  // set_MIS_GP1DATO_reg(0x00800000);
#ifndef CONFIG_BOARD_DEMO_RTD1095  
   //MISC GPIO50 
   rtd_setbits(0x1801b104,_BIT18);
   rtd_setbits(0x1801b114,_BIT18);
   printf("0x1801b104=%x 0x1801b114=%x\n",get_reg(0x1801b104),get_reg(0x1801b114));
#else
   //ETN pass, Igpio 2 pull high
   //0x1800_7310, bit 9:8 = 0
   //0x1800_7100, bit 2 = 1
   //0x1800_7104, bit 2 = 1

   rtd_maskl(0x18007310, ~(_BIT9|_BIT8), 0);
   rtd_setbits(0x18007100,_BIT2);
   rtd_setbits(0x18007104,_BIT2);
   printf("0x18007310=%x 0x18007100=%x 0x18007104=%x\n",get_reg(0x18007310),get_reg(0x18007100),get_reg(0x18007104)); 		
#endif
   //((void(*)())(TEST_PASS_ADDR))();
}
static void diag_fail()
{
	 printf("diag_fail\n");
    //((void(*)())(TEST_FAIL_ADDR))();
}

char rd_dram(int dram_addr)
{
      return (*((volatile char*) dram_addr));
}

void wr_dram(char dram_data[], int dram_addr, int size)
{
    char  *pointer = dram_addr;
      int i;

        for (i = 0; i < size; i++)
            {
                  *(pointer + i) = dram_data[i];
                    }
}


void etn_isr()
{
    unsigned int addr, data;
    unsigned int isr;
	printf("%s\n",__FUNCTION__);
    //1. mark all int
    addr = ETN_IO_IMR0;
    data = get_reg(addr);
    isr = (data & 0xffff0000) >> 16;
    if(isr != 0x0000) {
       data = (data & 0xffff0000) | 0x0000;
       set_reg(addr, data);
       set_SYS_MUXPAD0_reg(0x00000000);
       set_MIS_GP0DIR_reg(0x00200000);
       set_MIS_GP0DATO_reg(0x00200000);
    }
    else {
       return;
    }

//    //[5]. linkchg int
//    if((isr & 0x00000020)) {
//       addr = ETN_IO_ISR5;
//       data = get_reg(addr);
//       if( (data&0x00000002) ==0x00000000) {
//          addr = ETN_ERI_LWAKE_CTRL_REG;
//          data = 0x04030000;
//          set_eri_reg(addr,data);
//       }
//    }
    //[0]. rxok int / [4]. rdu int / [6]. rxfifofull int
    if( (isr & 0x00000001) | (isr & 0x00000010) | (isr & 0x00000040)) {
asm("\
.rept   200;\
        nop;\
.endr;\
");
    }

    //3. clear int
    addr = ETN_IO_IMR0;
    data = get_reg(addr);
    data = data&0x0000ffff | (isr << 16);
    set_reg(addr,data);
    data = data&0xffff0000 | 0xffff;
    set_reg(addr,data);
}

void set_ocp_reg(unsigned int ocp_addr, unsigned int ocp_data16b){
    unsigned int addr, data;

    addr = ETN_IO_PATCH_DBG;
    data = (0x1<<31) | ((ocp_addr&0x0000fffe)<<15) | (ocp_data16b&0x0000ffff);
    set_reg(addr, data);
}

unsigned int get_ocp_reg(unsigned int ocp_addr){
    unsigned int addr, data, ocp_data16b;

    addr = ETN_IO_PATCH_DBG;
    data = (0x0<<31) | ((ocp_addr&0x0000fffe)<<15) | (0x0000);
    set_reg(addr, data);
    data = get_reg(addr);
    ocp_data16b = data & 0x0000ffff;
    return ocp_data16b;
}

void set_eri_reg(unsigned int eri_addr, unsigned int eri_data){
    unsigned int addr, data;

    addr = ETN_IO_ERIDR;
    data = eri_data;
    set_reg(addr, data);
      
    addr = ETN_IO_ERIAR;
    data =  (0x8000 << 16) | (0xf << 12) | (eri_addr & 0xfff);
    set_reg(addr, data);

    while( (data&0x80000000) == 0x80000000) {
       addr = ETN_IO_ERIAR;
       data = get_reg(addr);
    }
}

unsigned int get_eri_reg(unsigned int eri_addr){
    unsigned int addr, data;

    addr = ETN_IO_ERIAR;
    data =  (0x0000 << 16) | (0xf << 12) | (eri_addr & 0xfff);
    set_reg(addr, data);

    while( (data&0x80000000) == 0x00000000) {
       addr = ETN_IO_ERIAR;
       data = get_reg(addr);
    }

    addr = ETN_IO_ERIDR;
    data = get_reg(addr);    

    return data;
}

void init_system()
{	 

    unsigned int addr, data;
	int i;
    wr_dram(data_array, tx_data_base_addr, 64);

//	for(i=0;i<64;i++)
//	{
//		printf("tx_data_base_addr=%x\n",rd_dram(tx_data_base_addr+i));
//	
//	}

    wr_dram(tx_data_array, tx_dsc_base_addr, 32);
	
//	for(i=0;i<32;i++)
//	{
//		printf("tx_dsc_base_addr=%x\n",rd_dram(tx_dsc_base_addr+i));
//	
//	}
	
    wr_dram(rx_data_array, rx_dsc_base_addr, 64);
//	for(i=0;i<64;i++)
//	{
//		printf("rx_dsc_base_addr=%x\n",rd_dram(rx_dsc_base_addr+i));
//	
//	}

    asm("\
        .rept   16;\
                nop;\
                .endr;\
                ");
	 
     //9346C register
    addr = ETN_IO_CONFIG0;
    data = get_reg(addr);
    data = (data & 0xffffff00) | 0xc0;
    set_reg(addr, data);
	 
asm("\
.rept   16;\
        nop;\
.endr;\
");
    //config0-conifg5
    //cfg0-cfg2
	 
    addr = ETN_IO_CONFIG0;
    data = get_reg(addr);
	 
    data = (data & 0x000000ff) | (0x04<<8) | (0x00<<16) | (0x3d<<24);
    set_reg(addr, data);
    //cfg3-cfg5
    addr = ETN_IO_CONFIG4;
    data = get_reg(addr);
    data = (data & 0xff000000) | (0x26<<0) | (0x00<<8) | (0x02<<16);
    set_reg(addr, data);
	 
    //multicaster register
    //mar = ffff_ffff_ffff_ffff
    addr = ETN_IO_MAR6;
    data = 0xffffffff;
    set_reg(addr, data);
	 
    addr = ETN_IO_MAR2;
    data = 0xffffffff;
    set_reg(addr, data);
	 
	
    //ID Register
    //macid = 5254_4c00_0008
    addr = ETN_IO_MACID0;
    data = 0x004c5452;
    set_reg(addr, data);
	 
    addr = ETN_IO_MACID2;
    data = 0x00000800;
    set_reg(addr, data);
	 
    //umac MAC_ID for rx
    addr = ETN_ERI_MACID_VLAN0_0;
    data = 0x54520000;
    set_eri_reg(addr,data);
	 
    addr = ETN_ERI_MACID_VLAN0_2;
    data = 0x0800004c;
    set_eri_reg(addr,data);
 
    //txq dsc start addr
    //txq0
    addr = ETN_IO_TXQ0_DSC_ADDR0;
    data = tx_dsc_base_addr;
    set_reg(addr, data);
    addr = ETN_IO_TXQ0_DSC_ADDR1;
    data = 0x00000000;
    set_reg(addr, data);
	 
    //txq1
    addr = ETN_IO_TXQ1_DSC_ADDR0;
    data = tx_dsc_base_addr+0x00010000;
    set_reg(addr, data);
    addr = ETN_IO_TXQ1_DSC_ADDR1;
    data = 0x00000000;
    set_reg(addr, data);
	 

    //max fetch transmit descriptor num
    addr = ETN_IO_CONFIG4;
    data = get_reg(addr);
    data = (data & 0x00ffffff) | (0x04<<24);
    set_reg(addr, data);
	 

    //rx dsc start addr
    addr = ETN_IO_RDSAR0;
    data = rx_dsc_base_addr;
    set_reg(addr, data);
    addr = ETN_IO_RDSAR2;
    data = 0x00000000;
    set_reg(addr, data);
	 

    //interrupt mask/status register
    addr = ETN_IO_IMR0;
    data = get_reg(addr);
    data = (data & 0xffff0000) | 0xffff;
    set_reg(addr, data);
	 
    //c+c register
    addr = ETN_IO_CCR;
    data = get_reg(addr);
    data = (data & 0xffff0000) | 0x2c61;
    set_reg(addr, data);
     
    //rx packet max size register
    addr = ETN_IO_RMS;
    data = get_reg(addr);
    data = (data & 0x0000ffff) | (0x3000<<16);
    set_reg(addr, data);    
 
    //max transmitt packet size register
    addr = ETN_IO_MTPS;
    data = get_reg(addr);
    data = (data & 0xffffff00) | 0x0f;
    set_reg(addr, data);
 
    //fifo threshold
    addr = ETN_ERI_FIFOFULL_TH;
    data = 0x00080002;
    set_eri_reg(addr, data);
 
    addr = ETN_ERI_RFIFONFULL_TH;
    data = 0x02000038;
    set_eri_reg(addr, data);
 
    addr = ETN_ERI_RFIFOEMPTY_TH;
    data = 0x00000048;
    set_eri_reg(addr, data);
 
    addr = ETN_ERI_TFIFOFULL_TH;
    data = 0x00100006;
    set_eri_reg(addr, data);
 
    //enable rx filter
   addr = ETN_ERI_FTR_MCU_CTRL;
   data = get_eri_reg(addr);
   data = (data & 0xffff0000) | 0x000d;
	 
   set_eri_reg(addr, data);
		 
   //enable tx_enable, rx_eanble
    change_dma_control(1,1,1);
		 
asm("\
.rept   16;\
        nop;\
.endr;\
");

}

void change_dma_control(unsigned int enable, unsigned int tx, unsigned int rx){
   unsigned int addr, data, data_d;

   //set_tcr
   addr = ETN_IO_TCR0;
   if(tx==1 && enable==1) 
      data = 0x03000480;
   else if (tx==1 && enable==0)
      data = 0x00000000;
   set_reg(addr, data);

   //turn-on
   if(enable==1) {
      //1. wait link_list_rdy true
      addr = ETN_IO_PHY_PWR_DUNC;
      do {
			printf("%s %d data=%x\n",__FUNCTION__,__LINE__,data);
         data = get_reg(addr);
		 	 
asm("\
.rept   16;\
        nop;\
.endr;\
");
      } while(( data & 0x02000000) ==0x00000000);
      //2. set_rcr
      if(rx==1) {
         addr = ETN_IO_RCR0;
         data = get_reg(addr);
         data = (data & 0xfeff8740) | (0x0 <<24) | (0x0 << 14) | (0x1 <<11) | (0x0 <<7) | (0xe);
         set_reg(addr,data);
      }
      //3. set_cr tx/rx enable
      addr = ETN_IO_CR;
      data = get_reg(addr);
      data = (data & 0x73ffff00) | (0x1 <<31) | ((rx&0x1) <<27) | ((tx&0x1) <<26);
      set_reg(addr,data);
      //5. set_cr stop_req disable
      addr = ETN_IO_CR;
      data = get_reg(addr);
      data = (data & 0x7fffffff) | (0x0 <<31);
      set_reg(addr,data);
      //6. set_rcr
      if(rx==1) {
         addr = ETN_IO_RCR0;
         data = get_reg(addr);
         data = (data & 0xfeff8740) | (0x0 <<24) | (0x0 << 14) | (0x1 <<11) | (0x0 <<7) | (0xe);
         set_reg(addr,data);
      }
   }
   //turn-off
   else if (enable==0) {
      //1. assert stop_all_req, tx_en, rx_en
      addr = ETN_IO_CR;
      data = get_reg(addr);
      data_d = data;
      data = (data & 0x00ffffff) | (0x8c << 24);
      set_reg(addr,data);
      //2. rx
      if(rx==1) {
         //close rcr
         addr = ETN_IO_RCR0;
         data = 0;
         set_reg(addr,data);
         //enbale stop_req
         addr = ETN_IO_CR;
         data = (data_d & 0x7fffffff) | (0x1<<31);
         data_d = data;
         set_reg(addr,data);
         //wait rx_empty
         addr = ETN_IO_RCR0;
         do {
            data = get_reg(addr);
asm("\
.rept   16;\
        nop;\
.endr;\
");
         } while((data&0x00020000)==0x00000000);
         data_d = (data_d & 0xf7ffffff) | (0x1<<27);
      }
      if(tx==1) {
         data_d = (data_d & 0xfbffffff) | (0x1<<26);
      }
      //3. disable tx/ rx enable
      addr = ETN_IO_CR;
      data = data_d;
      set_reg(addr,data);
   }
}

void pre_tally(unsigned int tally_bass_addr){
   unsigned int addr, data;

   addr = ETN_IO_DTCCR0;
   data = tally_bass_addr & 0xffffffc0;
   set_reg(addr,data);

   addr = ETN_IO_DTCCR2;
   data = 0x00000000;
   set_reg(addr,data);
}

void post_tally() {
   unsigned int addr, data;

   addr = ETN_IO_DTCCR0;
   data = get_reg(addr);
   data = (data & 0xffffffc0) | (0x1<<3);
   set_reg(addr,data);
}

unsigned int dump_tally_counter(unsigned int dump_addr) {
   unsigned int addr, data, data_d;

   addr = ETN_IO_DTCCR0;
   do {
      data = get_reg(addr);
   } while ((data&0x00000008) == 0x00000008);

   data = get_dram(dump_addr);  //this will be 0
   
   return data;
}

void mii_if_cfg() {
   unsigned int addr, data;

  #ifdef RGMII
   addr = ETN_OCP_RGMII_REG;
   data = get_ocp_reg(addr);
   data = (data & 0x000080bd) | (0x0<<14) | (0x1<<7) | (0x1<<5) | (SPEED_m<<3) | (DUPLEX_m<<2) | (0x1);
   set_ocp_reg(addr,data);
  #elif RMII
   addr = ETN_OCP_RMII_REG;
   data = get_ocp_reg(addr);
   data = (data & 0x000080bd) | (0x1<<7) | (SPEED_m<<5) | (DUPLEX_m<<4) | (0xd);
   set_ocp_reg(addr,data);
  #else
   addr = ETN_OCP_RGMII_REG;
   data = get_ocp_reg(addr);
   data = (data & 0x0000fffd) | (0x1<<1);
   set_ocp_reg(addr,data);
  #endif
}
