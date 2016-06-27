#include <asm/arch/io.h>
#include <asm/arch/rbus/misc_reg.h>
#include <asm/arch/rbus/crt_reg.h>
#include <arm_test_pattern.h>
#include <config.h>



void DDR_test_pattern_0(void)
{

#ifdef CONFIG_BOARD_DEMO_RTD1095
  mem_test_entry();
#else
  rtd_maskl(CRT_MUXPAD1, ~(_BIT19|_BIT18),0);	
  rtd_setbits(GP0DIR,_BIT28);	
  rtd_setbits(GP0DATO,_BIT28);
  printf("GPIO28 high\n");
#endif
}

void ACPU_test_pattern_0(void)
{ 
  flush_dcache_all();		
 /* Enable ACPU */
  rtd_setbits(CLOCK_ENABLE2_reg,_BIT4);  
    	
  printf("%s\n",__FUNCTION__);
}

void ETN_test_pattern_0(void)
{ 				  		
	etn_test_entry();
			
	printf("%s\n",__FUNCTION__);
}

void USB_test_pattern_0(void)
{ 				  		
	usb_test_entry();
			
	printf("%s\n",__FUNCTION__);
}

void sd_test_0(void)
{

  printf("Go DDR -> ACPU -> USB test pattern\n");	

  DDR_test_pattern_0();
  
  ACPU_test_pattern_0();
  
  USB_test_pattern_0();
   
  printf("delay 100ms; Go ETN test pattern\n");

  mdelay(100);
  
  ETN_test_pattern_0();
#ifdef CONFIG_BOARD_DEMO_RTD1095  
  enter_ddr_self_refresh_mode();
#endif
  
}
