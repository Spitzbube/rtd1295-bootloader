#include <uart/UART.h>
#include <asm/arch/io.h>

#define print_reg(y,x) 	print_val(y,8); rtd_outl(0x18007800,46); print_val(rtd_inl(x),8); rtd_outl(0x18007800,44); \	

void hello_world(void)
{
	*(volatile unsigned int*)0x18007800=9;
	*(volatile unsigned int*)0x18007800=72;
	*(volatile unsigned int*)0x18007800=69;
	*(volatile unsigned int*)0x18007800=76;
	*(volatile unsigned int*)0x18007800=76;
	*(volatile unsigned int*)0x18007800=79;
	
	*(volatile unsigned int*)0x18007800=87;
	*(volatile unsigned int*)0x18007800=79;
	*(volatile unsigned int*)0x18007800=82;
	*(volatile unsigned int*)0x18007800=76;
	*(volatile unsigned int*)0x18007800=68;
	*(volatile unsigned int*)0x18007800=33;
}

void run_GPHY_BIST_pattern(void)
{	
	int count=0;
	
	__asm__ __volatile__("": : :"memory");
	rtd_outl(0x18016060, 0x801f0A42); //page 0xA42
	rtd_outl(0x18016060, 0x00100000);                       
	rtd_outl(0x18016060, 0x801f0A43); //page 0xA43
	rtd_outl(0x18016060, 0x801b8184); //item selection for mpbist
	rtd_outl(0x18016060, 0x801c0f00); //10 mdi/mdix, 100mdix,giga nway open loopback	
	rtd_outl(0x18016060, 0x801f0A47); //page 0xA47
	rtd_outl(0x18016060, 0x80110100); //bit[8]=1, mpbist enable
	rtd_outl(0x18007800,35);
//	__asm__ __volatile__("": : :"memory");
    

	while(1)
	{
		count++;
		__asm__ __volatile__("": : :"memory");
		if(count == 50000)
			break;		
	}	
	
//	__asm__ __volatile__("": : :"memory");
    rtd_outl(0x18007800,36);                    
	rtd_outl(0x18016060, 0x00110000);                              
	rtd_outl(0x18016060, 0x801f0A43); //page 0xA43
	rtd_outl(0x18016060, 0x801b8186); //read result for mpbist
	rtd_outl(0x18016060, 0x001c0000); //read                              
	rtd_outl(0x18016060, 0x801b8188); //read fail case for mpbist
	rtd_outl(0x18016060, 0x001c0000); //read

}

void main(void)
{
	int count=0;
	int i;
	
	*(volatile unsigned int*)0x18000360=0x55551554;	//bit 15:14=0 mux to gpio23
	*(volatile unsigned int*)0x1801B100=0x00800020; //bit 23=1 output
    *(volatile unsigned int*)0x1801B110=0x00800020; //bit 23=1 on
	//__asm__ __volatile__("": : :"memory");
		
	while(1)
	{
		
		count++;
		__asm__ __volatile__("": : :"memory");
		if(count==50000){
			*(volatile unsigned int*)0x1801B110=0x00000020;
			for(i=0; i<50000;i++);
			count=0;
			*(volatile unsigned int*)0x1801B110=0x00800020;
		}		
	}
}