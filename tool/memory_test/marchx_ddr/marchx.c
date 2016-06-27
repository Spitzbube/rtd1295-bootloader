#include <stdio.h>
#include "ddr_ctrl.h"
#include "march_elm.h"
#include "marchx_addr.h"

#define CPU_MIPS
#ifdef CPU_MIPS
#define CacheLineSize 32
#define CacheWay 4
#define CacheSize 0x8000
#endif

void up_w_r_marco(unsigned int, unsigned int, unsigned int, unsigned int);

void flush_dcache_all(void)
{
#ifdef CPU_RLX
    __asm__ __volatile__(
       ".set\tnoreorder\n"
       ".set\tnoat\n"
       "\tmfc0\t$1, $20\n"
       "\tandi\t$1, (~(0x00000200)) & 0xffff\n"
       "\tmtc0\t$1, $20\n"
       "\tor\t$1, 0x00000200\n"
       "\tmtc0\t$1, $20\n"
       ".set\tat\n"
       ".set\treorder\n");
#else
  int Cmd = 0x15; /* Dcache writeback invalidate*/
  unsigned int  addr;

  for(addr=0x80000000; addr < addr + CacheSize; addr += CacheLineSize)
  {
    asm volatile ("cache 0x15, 0(%0);"
                  "cache 0x15, %1(%0);"
                  "cache 0x15, %2(%0);"
                  "cache 0x15, %3(%0);"
                : :"r" (addr),
                  "I" ((1*CacheSize)/CacheWay),
                  "I" ((2*CacheSize)/CacheWay),
                  "I" ((3*CacheSize)/CacheWay));
  }
#endif
};


void delay_loop(int);

#define DATA_TRAINING  0
#define SOCKET_SUPPORT 0
#define STATUS_W2_SRAM 0
#define VERIFY_UnCache 1
#define VERIFY_Cache   1
#define SPEED_CHANGE   0

#define LOG_ADDR                0xb002ff00       
#define WR_FREQ_PTR             0xb002fff4
#define RD_FREQ_PTR             0xb002fff8
#define DUMMY_PTR               0xb002fffc


int test_pass;

int main(void)
{
  unsigned int start_addr;
  unsigned int stop_addr; //test to less than here 
  unsigned int write_data0;
  //unsigned int write_data0_b;
  unsigned int mask; 
  //int          pass;
 // unsigned int mask_all = 0xffffffff; 
  //struct rxi310_dramc_portmap *ddr_ctrl_ptr = (struct rxi310_dramc_portmap *)DDR_BASE;
  
  printf("Start\n");
//  if (DATA_TRAINING)
//  {
//    // Data Training test
//    if (run_data_training() != 0) 
//       // return fail_ddr_test(1, fail_count);
//       return fail_uart();
//  } // DATA_TRAINING
//
  test_pass     = 1;
  start_addr    = START_ADDR;
  stop_addr     = STOP_ADDR;
//start_addr    = 0xba000000;
 // stop_addr     = 0xba100000;
//
//  if(SOCKET_SUPPORT == 1)
//  {
//    mask          = 0xefefffff; //0 means no compare
//    printf("\nStart March Test for Socket Board from %x to %x!\n", start_addr, stop_addr);
//  }
//  else
//  {
    mask          = 0xffffffff; //0 means no compare
    printf("\nStart March Test for Eval Board from %x to %x!\n", start_addr, stop_addr);
//  }

  if(VERIFY_UnCache == 1)
  {
    printf("Test UnCachable Region!\n");
    //0xffffffff
    write_data0 = 0xffffffff;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

//    write_data0 = 0x12345678;
//    march_write_byte_up(start_addr, stop_addr, write_data0);

//    pass = march_read_word_up(start_addr, stop_addr, write_data0, mask);

    //0x00000000
    write_data0 = 0x00000000;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x55555555
    write_data0 = 0x55555555;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xaaaaaaaa
    write_data0 = 0xaaaaaaaa;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x33333333
    write_data0 = 0x33333333;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xcccccccc
    write_data0 = 0xcccccccc;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x01234567
    write_data0 = 0x01234567;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x89abcdef
    write_data0 = 0x89abcdef;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x76543210
    write_data0 = 0x76543210;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xfedcba98
    write_data0 = 0xfedcba98;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);
  }

  if(VERIFY_Cache == 1)
  {
    printf("Test Cachable Region!\n");
    start_addr    = start_addr - 0x20000000;
    stop_addr     = stop_addr  - 0x20000000;

    //0xffffffff
    write_data0 = 0xffffffff;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x00000000
    write_data0 = 0x00000000;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x55555555
    write_data0 = 0x55555555;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xaaaaaaaa
    write_data0 = 0xaaaaaaaa;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x33333333
    write_data0 = 0x33333333;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xcccccccc
    write_data0 = 0xcccccccc;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x01234567
    write_data0 = 0x01234567;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x89abcdef
    write_data0 = 0x89abcdef;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0x76543210
    write_data0 = 0x76543210;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);

    //0xfedcba98
    write_data0 = 0xfedcba98;
    up_w_r_marco(start_addr, stop_addr, write_data0, mask);
  }

  if(test_pass == 1)
  {
    printf("March Test X Done and Passed!\n");
    //if(STATUS_W2_SRAM == 1)
    //  *status_ptr   = 0xabcd;
    return 0; //call pass_uart();
  }
  else
  {
    printf("March Test X Done and Failed!\n");
    //if(STATUS_W2_SRAM == 1)
    //  *status_ptr   = 0xdead;
    return -1;// call fail_uart();
  }
}

void up_w_r_marco(unsigned int start_add, unsigned int stop_add, 
                  unsigned int data_pattern, unsigned int mask)
{
  int local_pass;
  volatile unsigned int *pll_ptr = (unsigned int *) 0xbfb06020;
  volatile unsigned int *freq_ptr;

  
  //>(wa)
  march_write_word_up(start_add, stop_add, data_pattern & mask);
  //printf("Write Done!\n");

  if(SPEED_CHANGE == 1)
  {   
    //change PLL freq
    freq_ptr = (unsigned int *) RD_FREQ_PTR;
    delay_loop(100);
    *pll_ptr = *freq_ptr;
    delay_loop(100);
  }

  //>(ra)
  local_pass = march_read_word_up(start_add, stop_add, data_pattern, mask);
  if(local_pass != 0)
  {
    //printf("Failed at Read with data %x, fail count = %d\n", data_pattern, pass);
    printf("Failed at Read with data %x\n", data_pattern);
    test_pass = 0;
  }
  else
  {
    printf("Passed at Read with data %x\n", data_pattern);
  }

  if(SPEED_CHANGE == 1)
  {   
    //change PLL freq
    freq_ptr = (unsigned int *) WR_FREQ_PTR;
    delay_loop(100);
    *pll_ptr = *freq_ptr; //266MHz
    delay_loop(100);
  }

  return;
};

