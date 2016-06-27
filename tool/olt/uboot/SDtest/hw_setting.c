#include <asm/io.h>
#include <asm/arch/io.h>
#include <malloc.h>
//#include <compiler.h>

#define HW_SETTING_START_ADDR 0x1810c000
#define HW_SETTING_HEADER_SIZE 96
#define HW_SETTING_TEMP_BUFFER 0x10002500
		  	

#define uswap_32(x) \
     ((((x) & 0xff000000) >> 24) | \
      (((x) & 0x00ff0000) >>  8) | \
      (((x) & 0x0000ff00) <<  8) | \
      (((x) & 0x000000ff) << 24))

	  
#define print_comma rtd_outl(0x18007800,44)
#define print_space rtd_outl(0x18007800,32)


void config_hw_setting(void)
{
	unsigned int hw_setting_fisrt_wd=0;
	unsigned int hw_setting_precise_size=0;
	unsigned int s_hw_setting_precise_size=0;
	unsigned int reg=0;
	unsigned int value=0;
	unsigned int mask=0;
	unsigned int *hw_ptr;
	int type=0;
	int i=0;
		
	hw_setting_fisrt_wd= rtd_inl(HW_SETTING_START_ADDR);  //hw_setting + padding (w/o header)
	//print_val(hw_setting_fisrt_wd,8);
	//print_comma;

	memcpy(HW_SETTING_TEMP_BUFFER,(HW_SETTING_START_ADDR + HW_SETTING_HEADER_SIZE),hw_setting_fisrt_wd);
	hw_setting_precise_size = rtd_inl( HW_SETTING_START_ADDR + HW_SETTING_HEADER_SIZE + hw_setting_fisrt_wd -4); // precise size is saved at the last word of (hw_setting + padding). 

	//print_val( HW_SETTING_START_ADDR + HW_SETTING_HEADER_SIZE + hw_setting_fisrt_wd -4,8);	
	//print_val(hw_setting_precise_size,8);
	//print_comma;
	
	s_hw_setting_precise_size=uswap_32(hw_setting_precise_size);		
	//print_val(s_hw_setting_precise_size,8);
	//print_comma;
	
	s_hw_setting_precise_size/=8;
	s_hw_setting_precise_size-=4;
	//print_val(s_hw_setting_precise_size,8);
	//print_comma;
	
	hw_ptr = HW_SETTING_TEMP_BUFFER;
    

	while(i <s_hw_setting_precise_size/4)
	{
		reg = hw_ptr[i];			
		type = reg & 0x3;
		
		switch (type) {
			case 0:	// write instruction
				value = hw_ptr[i+1];	
				print_space;	
				print_val(reg,8);
				print_comma;				
				print_val(value,8);	
				rtd_outl(reg,value);									
				i+=2;
				break;

			case 1:	// polling instruction		
				i+=3;
				break;

			case 2:	// mask instruction	
				print_space;
				mask = hw_ptr[i+1];
				value = hw_ptr[i+2];				
				print_val(mask,8);				
				print_val(value,8);
				//rtd_maskl(reg,mask,value);
				i+=2;
               	break;

			case 3:	// NOP instruction									
				value = hw_ptr[i+1];
				print_space;
				print_val(value,8);
				func_nop(0,0,0,value);
				i+=2;
				break;
			default:	// should not happen
				break;
		}
	}
		
}


