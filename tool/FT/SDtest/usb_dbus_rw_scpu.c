#include <asm/io.h>
#include <test_pattern/system.h>
#include <asm/arch-rtd1195/io.h>



const unsigned char dram_tx_trb[16]={
0x20,0xe4,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x04,0x00,0x00,0x13,0x00,0x00,0x00
};

const unsigned char dram_rx_trb[16]={
0x00,0xe0,0x00,0x00,0x00,0x04,0x00,0x00,
0x00,0x04,0x00,0x00,0x13,0x00,0x00,0x00
};


static void diag_pass(void); 
static void diag_fail(void); 

unsigned int tx_ptr= 0x03000010;//0xbb010;
unsigned int rx_ptr= 0x03000000;//0xbb000;

//#undef DELAY_C
//#define DELAY_C(count) \
//    {int i; for(i=count; i>0; i--); }


void usb_test_entry(void)
{
  unsigned int reg_value;
  int i;

 
   memcpy( (unsigned char *)tx_ptr,dram_tx_trb, sizeof(dram_tx_trb));	
   memcpy( (unsigned char *)rx_ptr,dram_rx_trb,sizeof(dram_rx_trb));	

   printf("0xe000=");
   for(i=0;i<8;i++)
   {		
		printf("0x%x,",rtd_inb(0xe000+i));
   }
	 printf("\n");
	 
	printf("0xe420=");
	for(i=0;i<8;i++)
	{		
		printf("0x%x,",rtd_inb(0xe420+i));
    }
	printf("\n");
   
   
    printf("0x03000010=");
    for(i=0;i<16;i++)
    {
		printf("0x%x,",rtd_inb(tx_ptr+i));	 
    }
	printf("\n");
	 
	 
	printf("0x03000000=");;
    for(i=0;i<16;i++)
	{
		printf("0x%x,",rtd_inb(rx_ptr+i));
	}
	 printf("\n"); 
   
   
  //read reg value
  //reg_value = *((volatile unsigned int*) 0xB8013200);

  //write reg value
  //*((volatile unsigned int*) 0xB8013830) = 0x7;

 // *((volatile unsigned int*) 0xB8000000) = 0x355;
 // *((volatile unsigned int*) 0xB800000c) = 0x11;
 // *((volatile unsigned int*) 0xB800000c) = 0x1;
 // *((volatile unsigned int*) 0xB800000c) = 0x11;
 

  udelay(5000); 

  *((volatile unsigned int*) 0x18028110) = 0x30c1201c;
  *((volatile unsigned int*) 0x18028704) = 0x40f00000;  
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);
  //reg_value = *((volatile unsigned int*) 0xB8013704);

  udelay(13000); 
  *((volatile unsigned int*) 0x18028400) = 0x29dc00;
  *((volatile unsigned int*) 0x18028404) = 0x0;
  *((volatile unsigned int*) 0x18028408) = 0x600200;
  *((volatile unsigned int*) 0x18028110) = 0x30c1201c; 
  *((volatile unsigned int*) 0x18028708) = 0xf;
//Start configuration
  *((volatile unsigned int*) 0x1802880c) = 0x409;
  udelay(200); 

//##EP0 parameter-2 w/ CMD1 
  *((volatile unsigned int*) 0x18028800) = 0x0;
//##EP0 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028804) = 0x2300;
//##EP0 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028808) = 0x1000;
//##EP0 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802880c) = 0x401;
  udelay(200); //for(i=0; i<200; i++); //DELAY_C(200);

//##EP1 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028810) = 0x0;
//##EP1 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028814) = 0x2002300;
//##EP1 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028818) = 0x1000;
//##EP1 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802881c) = 0x401;
  udelay(200); //for(i=0; i<200; i++); //DELAY_C(200);

//##EP2 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028820) = 0x0;
//##EP2 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028824) = 0x4002300;
//##EP2 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028828) = 0x3c02004;
//##EP2 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802882c) = 0x401;
  udelay(200); //for(i=0; i<200; i++); //DELAY_C(200);

//##EP3 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028830) = 0x0;
//##EP3 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028834) = 0x6002300;
//##EP3 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028838) = 0x3c22004;
//##EP3 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802883c) = 0x401;
  udelay(200); //for(i=0; i<200; i++); //DELAY_C(200);
//#if 0 
//##EP0 parameter-2 w/ CMD2
  *((volatile unsigned int*) 0x18028800) = 0x0; 
//##EP0 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028804) = 0x0;
//##EP0 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028808) = 0x1;
//##EP0 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802880c) = 0x402;
  udelay(200);

//##EP1 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028810) = 0x0;
//##EP1 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028814) = 0x0;
//##EP1 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028818) = 0x1;
//##EP1 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802881c) = 0x402;
  udelay(200); 

//##EP2 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028820) = 0x0;
//##EP2 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028824) = 0x0;
//##EP2 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028828) = 0x1;
//##EP2 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802882c) = 0x402;
  udelay(200); 

//##EP3 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028830) = 0x0;
//##EP3 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028834) = 0x0;
//##EP3 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028838) = 0x1;
//##EP3 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802883c) = 0x402;
  udelay(200); 
 
  *((volatile unsigned int*) 0x18028720) = 0x3;
  *((volatile unsigned int*) 0x18028704) = 0x80f00200;
  *((volatile unsigned int*) 0x18028110) = 0x30c12038;
  *((volatile unsigned int*) 0x1802840c) = 0x4;
  udelay(200); 

  *((volatile unsigned int*) 0x18028300) = 0x82;
  *((volatile unsigned int*) 0x18028304) = 0x820104;
  *((volatile unsigned int*) 0x18028308) = 0x28a030c;

  *((volatile unsigned int*) 0x18028400) = 0xab000;
  *((volatile unsigned int*) 0x18028404) = 0x0;
  *((volatile unsigned int*) 0x18028408) = 0x100;

  *((volatile unsigned int*) 0x18028700) = 0x20004;
  *((volatile unsigned int*) 0x18028704) = 0x80000000;
  *((volatile unsigned int*) 0x18028720) = 0x3f;
  *((volatile unsigned int*) 0x1802880c) = 0x409;
  udelay(200); 
     
//##EP0 parameter-2 w/ CMD1 
  *((volatile unsigned int*) 0x18028800) = 0x0;
//##EP0 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028804) = 0x2700;
//##EP0 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028808) = 0x2004;
//##EP0 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802880c) = 0x401;
  udelay(200); 

//##EP1 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028810) = 0x0;
//##EP1 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028814) = 0x2002600;
//##EP1 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028818) = 0x2004;
//##EP1 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802881c) = 0x401;
  udelay(200); 

//##EP2 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028820) = 0x0;
//##EP2 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028824) = 0x4002700;
//##EP2 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028828) = 0x2004;
//##EP2 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802882c) = 0x401;
  udelay(200); 

//##EP3 parameter-2 w/ CMD1  
  *((volatile unsigned int*) 0x18028830) = 0x0;
//##EP3 parameter-1 w/ CMD1  
  *((volatile unsigned int*) 0x18028834) = 0x6002700;
//##EP3 parameter-0 w/ CMD1  
  *((volatile unsigned int*) 0x18028838) = 0x22004;
//##EP3 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802883c) = 0x401;
  for(i=0; i<200; i++);

//##EP0 parameter-2 w/ CMD2
  *((volatile unsigned int*) 0x18028800) = 0x0; 
//##EP0 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028804) = 0x0;
//##EP0 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028808) = 0x1;
//##EP0 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802880c) = 0x402;
  udelay(200); 

//##EP1 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028810) = 0x0;
//##EP1 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028814) = 0x0;
//##EP1 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028818) = 0x1;
//##EP1 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802881c) = 0x402;
  udelay(200); 

//##EP2 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028820) = 0x0;
//##EP2 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028824) = 0x0;
//##EP2 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028828) = 0x1;
//##EP2 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802882c) = 0x402;
  udelay(200); 

//##EP3 parameter-2 w/ CMD2  
  *((volatile unsigned int*) 0x18028830) = 0x0;
//##EP3 parameter-1 w/ CMD2  
  *((volatile unsigned int*) 0x18028834) = 0x0;
//##EP3 parameter-0 w/ CMD2  
  *((volatile unsigned int*) 0x18028838) = 0x1;
//##EP3 CMD2 Set Endpoint Transfer Resource  
  *((volatile unsigned int*) 0x1802883c) = 0x402;
  udelay(200); 

/////Setup Loopback
  //##DGCMDPAR##   command enable  
  *((volatile unsigned int*) 0x18028710) = 0x1;
  //##DGCMD##      command active
  *((volatile unsigned int*) 0x18028714) = 0x410;
  udelay(200); 
  
//##EP0 parameter-2 w/ CMD6
  *((volatile unsigned int*) 0x18028800) = 0x0;
//##EP0 parameter-1 w/ CMD6  
  *((volatile unsigned int*) 0x18028804) = tx_ptr;//0xbb010;
//##EP0 parameter-0 w/ CMD6  
  *((volatile unsigned int*) 0x18028808) = 0x0;
//##EP0 CMD1 set endpoint configuration  
  *((volatile unsigned int*) 0x1802880c) = 0x406;
  udelay(200); 
	
//##EP1 parameter-2 w/ CMD6  
  *((volatile unsigned int*) 0x18028810) = 0x0;
//##EP1 parameter-1 w/ CMD6  
  *((volatile unsigned int*) 0x18028814) = rx_ptr; //0xbb000;
//##EP1 parameter-0 w/ CMD6  
  *((volatile unsigned int*) 0x18028818) = 0x0;
//##EP1 CMD6 set endpoint configuration  
  *((volatile unsigned int*) 0x1802881c) = 0x406;
  udelay(200); 


  *((volatile unsigned int*) 0x18028720) = 0xff;

////////##EP2 parameter-2 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028820) = 0x0;
////////##EP2 parameter-1 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028824) = 0x60000;
////////##EP2 parameter-0 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028828) = 0x0;
////////##EP2 CMD2 Set Endpoint Transfer Resource  
//////  *((volatile unsigned int*) 0xB802882c) = 0x406;
//////  DELAY_C(200);
////////##EP3 parameter-2 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028830) = 0x0;
////////##EP3 parameter-1 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028834) = 0x60000;
////////##EP3 parameter-0 w/ CMD2  
//////  *((volatile unsigned int*) 0xB8028838) = 0x0;
////////##EP3 CMD2 Set Endpoint Transfer Resource  
//////  *((volatile unsigned int*) 0xB802883c) = 0x406;


  diag_pass();

	



}
static void diag_pass(void) {

	int j;
	unsigned char write_back_data;
	unsigned char origin_data;
			    	                                       
	for (j = 0; j < 8; j++)
	{		
		write_back_data = rtd_inb(0xe420+j);
		origin_data = rtd_inb(0xe000+j);
        if (write_back_data!= origin_data)
        {	
			printf("Origin[%d]:0x%x Write_back:0x%x ",j, origin_data,write_back_data);
			diag_fail();
            return;			
        }		
    }
  

	//GPIO[21] (NF_CLE)default LOWï¼?	//[0x1800_0360] bit 11:10 = 00 ... pinmux to GPIO21
	//[0x1801_B100] bit 21 = 1 ... output pin
	//[0x1801_B110] bit 21 = 1 ... if PASS, output HIGH

	rtd_setbits(0x1801b100,_BIT21);
	rtd_setbits(0x1801b110,_BIT21);
	printf("0x1801b100=%x 0x1801b110=%x\n",rtd_inl(0x1801b100),rtd_inl(0x1801b110));	
  
	//((void(*)())(TEST_PASS_ADDR))();
}

static void diag_fail(void) {
	printf("diag_fail\n");
}
