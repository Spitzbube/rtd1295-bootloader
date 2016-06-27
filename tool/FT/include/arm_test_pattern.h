#ifndef __ARM_TEST_PATTERN_H_
#define __ARM_TEST_PATTERN_H_	

//#define EXECUTE_CUSTOMIZED_FUNCTION	  	env_handler_customized("set Let env");
//#define EXECUTE_CUSTOMIZED_FUNCTION_1 	({int __ret=0; __ret = detect_recovery_flag("Check Let Recovery"); __ret; })
						
										

int etn_test_entry(void);
void usb_test_entry(void);
void mem_test_entry(void);
void enter_ddr_self_refresh_mode(void);



#endif	/* __ARM_TEST_PATTERN_H_ */
