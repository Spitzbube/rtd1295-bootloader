#include <stdio.h>
#include <cpu.h>
#include "ddr_ctrl.h"
#include "ddr_addr.h"

#define ALIGN32_FLOOR(addr) ((addr) & 0xFFFFFFFC)
#define ALIGN16_FLOOR(addr) ((addr) & 0xFFFFFFFe)

#define WRITE_MEM32(addr, val)   (*(volatile unsigned int *) (addr)) = (val)
#define READ_MEM32(addr)         (*(volatile unsigned int *) (addr))
#define WRITE_MEM16(addr, val)   (*(volatile unsigned short *) (addr)) = (val)
#define READ_MEM16(addr)         (*(volatile unsigned short *) (addr))
#define WRITE_MEM8(addr, val)    (*(volatile unsigned char *) (addr)) = (val)
#define READ_MEM8(addr)          (*(volatile unsigned char *) (addr))

#define DATA_TRAINING 0
#define DATA_TRAINING_EACH_RUN 0
#define DATA_RETRAINING 0
#define REREAD_CHECK 0
#define REREAD_COUNT 20
#define SHOW_ERR_READ 1
#define SHOW_ERR_BLK 0
#define SHOW_LAST_ACC 0
#define SCAN_ERR_DATA 0
#define RANDOM_BG 1
#define BG_DATA 0xdeadbeef
// #define BG_DATA 0
#define CHANGE_SEED 0
#define CACHE_FLUSH 0
#define CACHE_FLUSH_WET 100
#define SHOW_DRIFT 0
#define CHECK_DRIFT 0

// Random Access type 
//   2: read+write, 
//   1: read only, 
//   0: write only
#define RANDOM_ACC 2


#ifdef CPU_MIPS
#define CacheLineSize 32
#define CacheWay 4
#define CacheSize 0x8000
#endif

static unsigned int x = 836293259;

void srand2(unsigned int seed)
{
   x = seed;
}

unsigned int rand2(void)
{
   static unsigned int y = 362436;
   static unsigned int z = 521288629;
   static unsigned int c = 7654321;

   unsigned long long t, a= 698769069;

   x = 69069 * x + 12345;
   y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5);
   t = a * z + c; c = (t >> 32); z = t;

   return x + y + z;
}



void flush_dcache_addr(unsigned int addr)
{
#if 0
#if !defined(_MIPS_ARCH_3081)
#ifdef CPU_RLX
     asm volatile (" cache %0, 0(%1)"
                    :
                    : "I" (0x15),
                      "r"(addr));
#else
     asm volatile ("cache 0x15, 0(%0);"::"r"(addr));
#endif //#ifdef CPU_RLX
#endif
#else
  cpu_dcache_flush_range(addr, addr+1);
#endif
}

void flush_dcache_all(void)
{
#if 0
#if !defined(_MIPS_ARCH_3081)
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
     unsigned int  addr;
     for(addr=0x80000000; addr < (0x80000000 + CacheSize/CacheWay); addr += CacheLineSize)
     {
       asm volatile ("cache 0x15, 0(%0);"
                  "cache 0x15, %1(%0);"
                  "cache 0x15, %2(%0);"
                  "cache 0x15, %3(%0);"
                : : "r"(addr),
                  "I" ((1*CacheSize)/CacheWay),
                  "I" ((2*CacheSize)/CacheWay),
                  "I" ((3*CacheSize)/CacheWay));
     }
#endif
#endif
#else
    cpu_dcache_flush_all();

#endif
}

int compare_data(unsigned int data0, unsigned int data1, unsigned int mask, unsigned int type)
{
  unsigned int result;
  result = data0 ^ data1;
  if(type == 0)
  {
    result = result & (mask >> 24);
  }
  else if(type == 1)
  {
    result = result & (mask >> 16);
  }
  else
  { 
    result = result & mask;
  }
  if(result == 0)
    return 1;
  else
    return 0;
}

#define MAX_BURST    0x400
#define MAX_SAMPLE   0x1000000


#define SOCKET_SUPPORT 0
#define STATUS_W2_SRAM 0

// Timeout setting
// Stress Test: 3600 sec (1hr)
// Normal Test: 65 sec
// Fast   test: 5 sec

#ifdef TEST_TIME_1HR
// Stress test
  #define STOP_ERR_CNT 1000
  #define MAX_TEST_RUN 90000
  #define MAX_TEST_PT  50000
  #define RANDOM_SINGLE 1
  #define RANDOM_BLOCK  1
  #define RANDOM_READ   1
#else // TEST_TIME_1HR
  #ifdef TEST_TIME_10MIN
    #define STOP_ERR_CNT 1000
    #define MAX_TEST_RUN 2000
    #define MAX_TEST_PT  5000
    #define RANDOM_SINGLE 1
    #define RANDOM_BLOCK  1
    #define RANDOM_READ   1
  #else // else TEST_TIME_10MIN
    #ifdef TEST_TIME_5SEC
    // Fast test
      #define STOP_ERR_CNT 20
      #define MAX_TEST_RUN 500
      #define MAX_TEST_PT  2000
      #define RANDOM_SINGLE 1
      #define RANDOM_BLOCK  1
      #define RANDOM_READ   1
    #else // FAST_TEST
    // Normal test, test time 1 min
      #define STOP_ERR_CNT 100
      #define MAX_TEST_RUN 1000
      #define MAX_TEST_PT  3000
      #define RANDOM_SINGLE 0
      #define RANDOM_BLOCK  1
      #define RANDOM_READ   1
    #endif // else TEST_TIME_1SEC
  #endif // else TEST_TIME_10MIN
#endif // else TEST_TIME_1HR

#define DEBUG 0


struct ACC {
  unsigned int cache_type;
  unsigned int access_type;
  unsigned int access_oper;
  unsigned int sram_addr;
  unsigned int gold_data;
  unsigned int dram_addr;
  unsigned int rdata;
  unsigned int wdata;
};


void show_mem (unsigned int addr) {
  volatile unsigned int *mem_ptr = (unsigned int *)addr;
  printf("Show Mem Addr: 0x%08x = 0x%08x.\n", addr, *mem_ptr);
}

int main(void)
{
  unsigned int i, j, k,l ;
  unsigned int cache_type;
  unsigned int access_type;
  unsigned int access_oper;
  unsigned int offset_addr;
  unsigned int sram_addr;
  unsigned int dram_addr;
  unsigned int burst;
  unsigned int rdata, wdata;
  unsigned int samples;
  int          test_run;
  unsigned int dram_test_base;
  unsigned     golddata;
  
  //unsigned int wdata_array[MAX_BURST];
  unsigned int fail_count = 0;
  unsigned int overall_fail = 0;
  unsigned int mask;
  struct ACC last_acc;
  unsigned int rand_bg = BG_DATA;
  volatile unsigned int *status_ptr = (unsigned int *)LOG_ADDR;
  unsigned int new_seed;
  //unsigned int cur_dqs_lat_b0, cur_dqs_lat_b1;
  //unsigned int last_dqs_lat_b0, last_dqs_lat_b1;
  unsigned int cur_drift_b0, cur_drift_b1;
  unsigned int last_drift_b0, last_drift_b1;

  int retest_total_run = REREAD_COUNT;
  int retest_pass;
  int retest_rdata_match;
  int retest_run;
  unsigned int retest_dram_addr;
  unsigned int retest_rdata;
  unsigned int rd_err_count = 0;
  unsigned int pos_rd_err_count = 0;
  unsigned int pos_wr_err_count = 0;

  unsigned int eblk_addr;
  unsigned int eblk_data[8];
  int eblk_idx;

  unsigned int scan_data;
  unsigned int scan_sram_addr;
  unsigned int scan_dram_addr;
  unsigned int scan_dram_data;
  int scan_match_cnt;
  // Show some memory data for debug

  // show_mem (0xbfb06020); // DDR PLL
  // printf("START HERE\n");


  //User define the test type
  cache_type = 0;  //1: cacheable, 0: uncacheable
  access_type = 2; //0: Byte, 1: HWord, 2: Word

  last_acc.access_type = 2;
  last_acc.access_oper = 1;
  last_acc.sram_addr = 0xdeadbeef;
  last_acc.gold_data = 0xdeadbeef;
  last_acc.dram_addr = 0xdeadbeef;
  last_acc.rdata = 0xdeadbeef;
  last_acc.wdata = 0xdeadbeef;

  //clean log SRAM
  // for(i=0; i < 8; i++)
  //   *(status_ptr+i) = 0x1234dead;


  if (CHANGE_SEED == 1)
  {
    new_seed = *(status_ptr + 16);
    printf ("Current seed: 0x%08x.\n", new_seed);
    srand2(new_seed);
    *(status_ptr + 16) = rand2();

  }
  else
  {
    srand2(0x91282617);//srand2(0x1042F);  
  }
  //if(cache_type==1) 
  //   flush_dcache_all();

  if(SOCKET_SUPPORT == 1)
  {
    mask = 0xefefffff;
    printf("\nDDR Random Test with block size %x from %x size %x, DQ12 skip\n", TEST_BLOCK, DRAM_BASE, DRAM_SIZE);
  }
  else
  {
    mask = 0xffffffff;
    printf("\nDDR Random Test with block size %x from %x size %x SRAM_BASE %x, All Bits\n", TEST_BLOCK, DRAM_BASE, DRAM_SIZE,SRAM_BASE);
  }

//  if (DATA_TRAINING)
//  {
//    // Data Training test
//    if (run_data_training(&cur_dqs_lat_b0, &cur_dqs_lat_b1) != 0) 
//       return fail_ddr_test(1, 0, 0, 0);
//    printf("Current DQS latency: DQS_LAT0=%d, DQS_LAT1=%d\n", cur_dqs_lat_b0, cur_dqs_lat_b1);
//    last_dqs_lat_b0 = cur_dqs_lat_b0;
//    last_dqs_lat_b1 = cur_dqs_lat_b1;
//  } // DATA_TRAINING

 // if ((SHOW_DRIFT==1) || (CHECK_DRIFT==1))
 // {
 //   get_dqs_drift(&cur_drift_b0, &cur_drift_b1);
 //   if (SHOW_DRIFT==1)
 //   {
 //     printf("DDR DQS Drift (B0, B1) = (%d%d, %d%d)\n",
 //           (cur_drift_b0>>1) & 1, cur_drift_b0 & 1, 
 //           (cur_drift_b1>>1) & 1, cur_drift_b1 & 1 );
 //   }
 //   last_drift_b0 = cur_drift_b0;
 //   last_drift_b1 = cur_drift_b1;
 // }


  if(RANDOM_SINGLE == 1)
  {
    printf("\nSTART MEM_TEST1: Random Single Test with Block size %x\n", TEST_BLOCK);

    for (test_run = 1; test_run <= MAX_TEST_RUN; test_run++)
    {
      //printf("Run %d\n", test_run);
      //if (DATA_TRAINING_EACH_RUN)
      //{
      //  // Data Training test
      //  if (run_data_training(&cur_dqs_lat_b0, &cur_dqs_lat_b1) != 0) 
      //     return fail_ddr_test(1, fail_count, rd_err_count+pos_rd_err_count, pos_wr_err_count);
      //  if ((cur_dqs_lat_b0 != last_dqs_lat_b0) || (cur_dqs_lat_b1 != last_dqs_lat_b1))
      //  {
      //    printf("Data Re-training DQS latency changed: from (%d, %d) to (%d,%d)\n", 
      //        last_dqs_lat_b0, last_dqs_lat_b1, cur_dqs_lat_b0, cur_dqs_lat_b1);
      //  }
      //  last_dqs_lat_b0 = cur_dqs_lat_b0;
      //  last_dqs_lat_b1 = cur_dqs_lat_b1;
      //} // DATA_TRAINING

      //Decide the base address of DRAM
      dram_test_base = (rand2() % (unsigned int) (DRAM_SIZE - TEST_BLOCK));
      // dram_test_base = (rand2() % (unsigned int) DRAM_SIZE);
      // if (dram_test_base > TEST_BLOCK)
      //   dram_test_base -= TEST_BLOCK;
      dram_test_base = ALIGN32_FLOOR(DRAM_BASE + dram_test_base);
      cache_type = rand2() % 2;
      //cache_type = 0; // Uncache only
     
      if(cache_type == 0) //uncache
      {
        dram_test_base = dram_test_base | 0x20000000;
      }

      //clean the dram and sram
      for(i = dram_test_base, j = SRAM_BASE; i < TEST_BLOCK + dram_test_base; i+=4, j+=4)
      {
        if (RANDOM_BG)
          rand_bg = rand2();
        WRITE_MEM32(i, rand_bg);
        WRITE_MEM32(j, rand_bg);
	//printf("Sram_addr = %x , Write rand_bg = %x\n",j,rand_bg);
	//rand_bg = READ_MEM32(j);
	//printf("Sram_addr = %x, Read rand_bg = %x\n",j,rand_bg);
       // printf("%x_%x=%x\n", i, j, rand_bg);
      }
      if(cache_type == 0)//cachable
         flush_dcache_all();

      for(i = 0; i < MAX_TEST_PT; i++)
      {
        //if (CHECK_DRIFT==1)
        //{
        //  get_dqs_drift(&cur_drift_b0, &cur_drift_b1);
        //  if ((cur_drift_b0 != last_drift_b0) || (cur_drift_b1 != last_drift_b1))
        //  {
        //    printf("Run %d, PT %d, DQS drift changed from (%d%d, %d%d) to (%d%d, %d%d)\n", 
        //      test_run, i,
        //      (last_drift_b0>>1) & 1, last_drift_b0 & 1, 
        //      (last_drift_b1>>1) & 1, last_drift_b1 & 1, 
        //      (cur_drift_b0>>1) & 1, cur_drift_b0 & 1, 
        //      (cur_drift_b1>>1) & 1, cur_drift_b1 & 1 );
        //  }
        //  last_drift_b0 = cur_drift_b0;
        //  last_drift_b1 = cur_drift_b1;
        //}
        // Test random add cache flush 
        if (CACHE_FLUSH == 1) {
          if ((rand2() % CACHE_FLUSH_WET) == 0) {
            // printf(" Flush DCache\n");
	if(cache_type == 0)//cachable
            flush_dcache_all();
          }
        } // CACHE_FLUSH

        // Randomly determine operation/addr/data
        if (RANDOM_ACC > 1)
          access_oper = rand2() % 2; //R+W
        else
          access_oper = RANDOM_ACC;

        // access_type = rand2() % 4; //Byte/Half/Word/TW
        access_type = 2; // Word only
        // access_type = 0; // Byte only
        offset_addr = rand2() % (unsigned int) TEST_BLOCK;
    
        if(access_oper == 0) //write
        {
          wdata       = rand2() & mask;
          // wdata       =  dram_test_base + offset_addr;
          if (access_type == 0) //byte
          {
            wdata = wdata & 0xFF;
            WRITE_MEM8((offset_addr + dram_test_base), wdata);
	    if(cache_type !=0)
                flush_dcache_addr(offset_addr + dram_test_base);
            WRITE_MEM8((offset_addr + SRAM_BASE), wdata);
          }
          else if (access_type == 1) //hword
          {
            dram_addr = ALIGN16_FLOOR(offset_addr + dram_test_base);
            sram_addr = ALIGN16_FLOOR(offset_addr + SRAM_BASE);
            wdata = wdata & 0xFFFF;
            WRITE_MEM16(dram_addr, wdata);
	    if(cache_type !=0)
                flush_dcache_addr(dram_addr);
            WRITE_MEM16(sram_addr, wdata);
          }
          else if (access_type == 2) //word
          {
            dram_addr = ALIGN32_FLOOR(offset_addr + dram_test_base);
            sram_addr = ALIGN32_FLOOR(offset_addr + SRAM_BASE);
	    //printf("sram_addr =  %x, dram_addr =%x, wdata = %x\n", sram_addr, dram_addr, wdata);
            WRITE_MEM32(dram_addr, wdata);
                flush_dcache_addr(dram_addr);
            WRITE_MEM32(sram_addr, wdata);
          }
          else //twin-word
          {
            continue;
          }
        }
        else  //read
        {
          if (access_type == 0) //byte
          {
            dram_addr = offset_addr + dram_test_base;
            sram_addr = offset_addr + SRAM_BASE;
            rdata = READ_MEM8(dram_addr);
            golddata = READ_MEM8(sram_addr);
          }
          else if (access_type == 1) //hword
          {
            dram_addr = ALIGN16_FLOOR(offset_addr + dram_test_base);
            sram_addr = ALIGN16_FLOOR(offset_addr + SRAM_BASE);
            rdata = READ_MEM16(dram_addr);
            golddata = READ_MEM16(sram_addr);
          }
          else if (access_type == 2) //word
          {
            dram_addr = ALIGN32_FLOOR(offset_addr + dram_test_base);
            sram_addr = ALIGN32_FLOOR(offset_addr + SRAM_BASE);
            rdata = READ_MEM32(dram_addr);
            golddata = READ_MEM32(sram_addr);
	    //printf("sram_addr =  %x,  golddata = %x, dram_addr = %x,rdata = %x\n", sram_addr, golddata,dram_addr,rdata);
          }
          else //twin-word
          {
            continue;
          }

          //if(rdata != golddata)
          if(compare_data(rdata, golddata, mask, access_type) == 0)
          {
            if (SHOW_LAST_ACC) 
            {
              if (last_acc.access_oper == 0) 
              {
                printf("Last acc write Addr:0x%08x, Data:0x%08x\n", last_acc.dram_addr, last_acc.wdata);
              } else 
              {
                printf("Last acc Read Addr:0x%08x, Expect:0x%08x Actual:0x%08x ErrBit:%08x\n", 
                  last_acc.dram_addr, last_acc.gold_data, last_acc.rdata, 
                  last_acc.gold_data ^ last_acc.rdata);
              }
            } // SHOW_LAST_ACC

            //if (DATA_RETRAINING) {
            //  if (run_data_training(&cur_dqs_lat_b0, &cur_dqs_lat_b1) != 0) 
            //     return fail_ddr_test(0, fail_count, rd_err_count+pos_rd_err_count, pos_wr_err_count);
            //  if ((cur_dqs_lat_b0 != last_dqs_lat_b0) || (cur_dqs_lat_b1 != last_dqs_lat_b1))
            //  {
            //    printf("Data Re-training DQS latency changed: from (%d, %d) to (%d,%d)\n", 
            //        last_dqs_lat_b0, last_dqs_lat_b1, cur_dqs_lat_b0, cur_dqs_lat_b1);
            //  }
            //  last_dqs_lat_b0 = cur_dqs_lat_b0;
            //  last_dqs_lat_b1 = cur_dqs_lat_b1;
            //} // DATA_RETRAINING

            if (SHOW_ERR_BLK) 
            {
              eblk_addr = (dram_addr & 0xffffffe0) | 0x20000000; // uncacheable
              for (eblk_idx = 0; eblk_idx < 8; eblk_idx++) 
              {
                eblk_data[eblk_idx] = READ_MEM32(eblk_addr + eblk_idx*4);
              }
              printf("Error Block Addr:0x%08x, %08x, %08x, %08x, %08x.\n", 
                eblk_addr, eblk_data[0], eblk_data[1], eblk_data[2], eblk_data[3]);
              printf("Error Block Addr:0x%08x, %08x, %08x, %08x, %08x.\n", 
                eblk_addr+16, eblk_data[4], eblk_data[5], eblk_data[6], eblk_data[7]);
            } // SHOW_ERR_BLK

            if (REREAD_CHECK) 
            {
              retest_dram_addr = dram_addr | 0x20000000; // Force uncacheable read
              retest_pass =0;
              retest_rdata_match = 0;
              for ( retest_run=0; retest_run < retest_total_run; retest_run++) 
              {
                delay_loop(10000);
                if (access_type == 0) //byte
                  retest_rdata = READ_MEM8(retest_dram_addr);
                else if (access_type == 1) //hword
                  retest_rdata = READ_MEM16(retest_dram_addr);
                else if (access_type == 2) //word
                  retest_rdata = READ_MEM32(retest_dram_addr);
                // printf("[Info] Double check the read word: %x\n", retest_rdata);
                if(compare_data(retest_rdata, golddata, mask, access_type) != 0) 
                {
                  // printf("[Info] Re-Read check pass: %x\n", retest_rdata);
                  retest_pass++;
                } 
                else 
                {
                  if(compare_data(retest_rdata, rdata, mask, access_type) != 0) 
                  {
                    // printf("[Info] Re-read check fail: %x, but match first read data\n", retest_rdata);
                    retest_rdata_match++;
                  }
                  //else
                  //{
                    // printf("[Info] Re-read check fail: %x\n", retest_rdata);
                  //}
                }
              }
              if (retest_pass == retest_total_run)
              {
                rd_err_count++;
              }
              else if ( retest_pass > 3)
              {
                pos_rd_err_count++;
              }
              else if (retest_rdata_match == retest_total_run)
              {
                pos_wr_err_count++;
              }
            } // REREAD_CHECK

            if (SHOW_ERR_READ == 1)
            {
              printf("[Fail] Run:%d, PT:%d, SrcAddr:0x%08x, Addr:0x%08x Expect:0x%08x Actual:0x%08x ErrBit:%08x",
                test_run, i, sram_addr, dram_addr, golddata, rdata, golddata^rdata);
              if (REREAD_CHECK)
              {
                if (retest_pass == retest_total_run)
                {
                  printf(" ErrType: read");
                }
                else if ((retest_total_run - retest_pass) < 4)
                {
                  printf(" ErrType: Possible read\n");
                  printf("[Info] Re-read pass: %d/%d(RD Err), match first rdata: %d/%d", 
                         retest_pass, retest_total_run, retest_rdata_match, retest_total_run);
                }
                else if (retest_rdata_match == retest_total_run)
                {
                  printf(" ErrType: Possible write");
                }
                else
                {
                  printf(" ErrType: Unknown\n");
                  printf("[Info] Re-read pass: %d/%d(RD Err), match first rdata: %d/%d", 
                         retest_pass, retest_total_run, retest_rdata_match, retest_total_run);
                }
              }
              printf("\n");
            } // SHOW_ERR_READ

            if (SCAN_ERR_DATA) // Scan error data pattern from SRAM
            {
               if (RANDOM_BG || (rdata != BG_DATA)) 
               {
                scan_match_cnt = 0;
                for(scan_sram_addr = SRAM_BASE, scan_dram_addr = dram_test_base; 
                  scan_sram_addr < TEST_BLOCK + SRAM_BASE; 
                  scan_sram_addr+=4, scan_dram_addr+=4)
                {
                  scan_data = READ_MEM32(scan_sram_addr);
                  if (scan_data == rdata) {
                    scan_dram_data = READ_MEM32(scan_dram_addr);
                    printf("Scan SRAM Match, DRAM Addr:0x%08x, ErrBit:0x%08x, Data:%08x, ErrBit:0x%08x.\n", 
                      scan_dram_addr, (dram_addr ^ scan_dram_addr) & 0x0fffffff,
                      scan_dram_data, rdata ^ scan_dram_data);
                    scan_match_cnt++;
                  }
                }
                // printf("Scan SRAM Match count: %d\n", scan_match_cnt);
                if (scan_match_cnt == 0) {
                    printf("Scan SRAM no match.\n"); 
                }
              } else {
                    printf("Scan SRAM abort due to error data is bg pattern.\n"); 
              }
            }  // SCAN_ERR_DATA
            fail_count = fail_count + 1;

            if (STOP_ERR_CNT != 0) 
            {
              if (fail_count >= STOP_ERR_CNT) 
              {
                if (REREAD_CHECK) 
                {
                  printf("[ABORT] Test1 abort, exceed max err count runs:%d, faults:%d RD_ERR:%d, possible RD_ERR:%d possible WR_ERR:%d\n", 
                       test_run, fail_count, rd_err_count, pos_rd_err_count, pos_wr_err_count);
                }
                else
                {
                  printf("[ABORT] Test1 abort, exceed max err count runs:%d, faults:%d.\n", 
                       test_run, fail_count);
                }
                //return fail_ddr_test(0, fail_count, rd_err_count+pos_rd_err_count, pos_wr_err_count);
                return -1;
              }
            }
          }
        }
      }

      // for write only test, read and check whole block after write done
      if (RANDOM_ACC == 0) 
      {
        for(i = dram_test_base, j = SRAM_BASE; i < TEST_BLOCK + dram_test_base; i+=4, j+=4)
        {
          rdata = READ_MEM32(i|0x20000000);
          golddata = READ_MEM32(j);
          if(compare_data(rdata, golddata, mask, 2) == 0)
          {
            if (SHOW_ERR_READ)
            {
              printf("[Fail] Read back, Run:%d, PT:%d, Addr:0x%08x Expect:0x%08x Actual:0x%08x ErrBit:%08x\n", test_run, i, dram_addr, golddata, rdata, golddata^rdata);
            }
            fail_count = fail_count + 1;
          }
        }
      } // RANDOM_ACC == 0 , write only test

      if(DEBUG == 1)
      {
        if(test_run % 100 == 0)
        {
          printf("Complete %3d runs from %x, fail count = %d\n", test_run, dram_test_base, fail_count);   
        }else
        {
          printf("Complete %3d runs from %x, fail count = %d\n", test_run, dram_test_base, fail_count);   
        }
      }
      else
      {
        if(test_run % 100 == 0)
        {
          if ((SHOW_DRIFT==1))
          {
            get_dqs_drift(&cur_drift_b0, &cur_drift_b1);
            printf("Complete %5d runs from %x, fail count = %d, DQS drift = (%d%d, %d%d)\n", 
              test_run, dram_test_base, fail_count,
              (cur_drift_b0>>1) & 1, cur_drift_b0 & 1, 
              (cur_drift_b1>>1) & 1, cur_drift_b1 & 1 );
          }
          else
          {
            printf("Complete %5d runs from %x, fail count = %d\n", test_run, dram_test_base, fail_count);   
          }
        }
      }
      last_acc.access_type = access_type;
      last_acc.access_oper = access_oper;
      last_acc.sram_addr = sram_addr;
      last_acc.gold_data = golddata;
      last_acc.dram_addr = dram_addr;
      last_acc.wdata = wdata;
      last_acc.rdata = rdata;
      if (CHECK_DRIFT==1)
      {
        get_dqs_drift(&cur_drift_b0, &cur_drift_b1);
        if ((cur_drift_b0 != last_drift_b0) || (cur_drift_b1 != last_drift_b1))
        {
          printf("Run %d, DQS drift changed from (%d%d, %d%d) to (%d%d, %d%d)\n", test_run, 
            (last_drift_b0>>1) & 1, last_drift_b0 & 1, 
            (last_drift_b1>>1) & 1, last_drift_b1 & 1, 
            (cur_drift_b0>>1) & 1, cur_drift_b0 & 1, 
            (cur_drift_b1>>1) & 1, cur_drift_b1 & 1 );
        }
        last_drift_b0 = cur_drift_b0;
        last_drift_b1 = cur_drift_b1;
      }
    }
    printf("[DONE] Test1 Done with %d runs, %d faults!", test_run, fail_count);
    if (REREAD_CHECK == 1) 
    {
      printf(" RD_ERR:%d, possible RD_ERR:%d, possible WR_ERR:%d", 
             rd_err_count, pos_rd_err_count, pos_wr_err_count);
    }
    printf("\n");
    overall_fail += fail_count;
  }
//----------------------------------------------------------------------//
  fail_count = 0;
  //User define the test type
  cache_type = 0;  //0: cacheable, 1: uncacheable
  access_type = 2; //0: Byte, 1: HWord, 2: Word
 
 
  if(RANDOM_BLOCK == 1)
  {
    printf("\nSTART MEM_TEST2: Random Block\n");
    for (test_run = 0; test_run < MAX_TEST_RUN; test_run++)
    {
      //Generate burst length and write data randomly
      burst = rand2() % (unsigned int) MAX_BURST;
      access_type = rand2() % 3;
      
      //Generate addrress randomly
      offset_addr = rand2() % (unsigned int) DRAM_SIZE;
      
      //Refine the write data and address depends on access width
      if (access_type == 0)
      {
      	//wdata = wdata & 0xFF;
      }
      else if (access_type == 1)
      {
        offset_addr = ALIGN16_FLOOR(offset_addr);
      }
      else
      {
        offset_addr = ALIGN32_FLOOR(offset_addr);
      }

      dram_addr   = DRAM_BASE + offset_addr;
      sram_addr  = SRAM_BASE;

      cache_type = rand2() % 2;

      dram_addr = cache_type ? (dram_addr | 0x20000000) : dram_addr;
      sram_addr = cache_type ? (sram_addr | 0x20000000) : sram_addr;

      if(DEBUG)
        printf("Test %x vs %x with size %x\n", sram_addr, dram_addr, burst);

      /* Prepare Write Data */
      for (i = 0, j = sram_addr; i < burst ; i++)
      {
        wdata = rand2();

        if (access_type == 0)
        {    
          wdata = wdata & 0xFF;
          WRITE_MEM8(j, wdata);
        }
        else if (access_type == 1)
        {
          wdata = wdata & 0xFFFF;
          WRITE_MEM16(j, wdata);
        }
        else
        {
          WRITE_MEM32(j, wdata);
        }

        j = j + (1 << access_type);
      }

      /* Write to memory */
      for (i = 0, j = dram_addr, k = sram_addr; i < burst ; i++)
      {
        if (access_type == 0)
        {
          WRITE_MEM8(j, *(unsigned char*)k);
        }
        else if (access_type == 1)
        {
          WRITE_MEM16(j, *(unsigned short*)k);
        }
        else
        {
          WRITE_MEM32(j, *(unsigned int*)k);
        }
      
        j = j + (1 << access_type);
        k = k + (1 << access_type);
      }
      
      //flush cache if cacheable address is used
//      printf("flush 2!\n");
      if(cache_type==0)   //cachable region
        flush_dcache_all();

      /* Read Verify */
      for (i = 0, j = dram_addr, k= sram_addr; i < burst ; i++)
      {
      //Read data from external memory
        if (access_type == 0)
        {
        	rdata       = READ_MEM8(j);
        	golddata    = READ_MEM8(k);
        }
        else if (access_type == 1)
        {
        	rdata       = READ_MEM16(j);
        	golddata    = READ_MEM16(k);
        }
        else
        {
        	rdata       = READ_MEM32(j);
        	golddata    = READ_MEM32(k);
        }
      //Compare data
        //if (rdata != golddata)
        if(compare_data(rdata, golddata, mask, access_type) == 0)
        {
          if(DEBUG)
          {
            printf("[Fail] Addr:0x%08x Expect:0x%08x Actual:0x%08x\n", j, golddata, rdata);
            rdata = READ_MEM32(j);
            printf("[Info] Double check the read word: %x\n", rdata);
          }
          fail_count = fail_count + 1;
        }

        j = j + (1 << access_type);
        k = k + (1 << access_type);

      }
       
      //Report Procedure  
      if ((test_run % 1000) == 0 && test_run >0)
        printf ("Now samples is %d (%d), fail count %d\n", test_run, access_type, fail_count);
    }
    printf("[DONE] Test2 Done with %d faults!\n", fail_count);
    overall_fail += fail_count;
  }
//--------------------------------------------------------------//
  if(RANDOM_READ == 1)
  {
    printf("\nSTART MEM_TEST3: Random Read Test\n");
    fail_count = 0;
 
    for (samples = 0; samples < MAX_TEST_RUN; samples++)
    {
      //Generate burst length and write data randomly
      //burst = rand2() % (unsigned int) TEST_BLOCK;
      //burst = 2000;
      access_type = rand2() % 3;
      cache_type = rand2() % 2;
      burst = TEST_BLOCK >> access_type;
//      printf("burst = 0x%x, cache_type = %d\n ", burst, cache_type);
      //Generate addrress randomly
      offset_addr = rand2() % (unsigned int) DRAM_SIZE;
 
      //Refine the write data and address depends on access width
      if (access_type == 0)
      {
         //wdata = wdata & 0xFF;
      }
      else if (access_type == 1)
      {
        offset_addr = ALIGN16_FLOOR(offset_addr);
      }
      else
      {
        offset_addr = ALIGN32_FLOOR(offset_addr);
      }
 
      dram_addr   = DRAM_BASE + offset_addr;
      sram_addr   = SRAM_BASE;
      
      //Modify due to cacheble
      dram_addr = cache_type ? (dram_addr | 0x20000000) : dram_addr;
      //dram_addr = dram_addr | 0x20000000;
 
      //printf("Copy DRAM %x to SRAM %x %x\n", dram_addr, sram_addr, burst);

      //clean SRAM
      for (i = 0, j = sram_addr; i < burst ; i++)
      {
        if (access_type == 0)
        {    
          WRITE_MEM8(j, 0);
        }
        else if (access_type == 1)
        {
          WRITE_MEM16(j, 0);
        }
        else
        {
          WRITE_MEM32(j, 0);
        }
        j = j + (1 << access_type);
      }

      //Initial read from DRAM
      for (i = 0, j = sram_addr, k = dram_addr; i < burst ; i++)
      {
        if (access_type == 0)
        {    
          WRITE_MEM8(j, *(unsigned char*)k);
	  flush_dcache_addr(j);
        }
        else if (access_type == 1)
        {
          WRITE_MEM16(j, *(unsigned short*)k);
	  flush_dcache_addr(j);
        }
        else
        {
          WRITE_MEM32(j, *(unsigned int*)k);
	  flush_dcache_addr(j);
        }
 
        j = j + (1 << access_type);
        k = k + (1 << access_type);

      }

      //printf("Init Done\n");
      //for (i = 0, j = sram_addr, k = dram_addr; i < burst ; i++)
      //{
      //  if (access_type == 0)
      //  {    
      //    rdata       = READ_MEM8(j);
      //    golddata    = READ_MEM8(k);
      //  }
      //  else if (access_type == 1)
      //  {
      //    rdata       = READ_MEM16(j);
      //    golddata    = READ_MEM16(k);
      //  }
      //  else
      //  {
      //    rdata       = READ_MEM32(j);
      //    golddata    = READ_MEM32(k);
      //  }
 
      //  printf("%x_%x:%x vs %x --> %d\n", j, k, rdata, golddata, (rdata == golddata));
      //  j = j + (1 << access_type);
      //  k = k + (1 << access_type);
      //}

      //dram_addr = cache_type ? dram_addr : (dram_addr - 0x20000000);

      //Compare data
      for (l = 0; l < 10 ; l++)
      {
        for (i = 0, j = sram_addr, k = dram_addr; i < burst ; i++)
        {
          if (access_type == 0)
          {    
            rdata       = READ_MEM8(j);
            golddata    = READ_MEM8(k);
          }
          else if (access_type == 1)
          {
            rdata       = READ_MEM16(j);
            golddata    = READ_MEM16(k);
          }
          else
          {
            rdata       = READ_MEM32(j);
            golddata    = READ_MEM32(k);
          }
            //if (rdata != golddata)
          if(compare_data(rdata, golddata, mask, access_type) == 0)
          {
            if(1)
            {
              printf("Compare Failed at %x with %x\n", k, golddata);
            }  
            fail_count++;
          }
      
          j = j + (1 << access_type);
          k = k + (1 << access_type);
        }
      }
      if(DEBUG)
      {
        if (fail_count > 0) {
          printf("Copy DRAM %x to SRAM %x and compare with %d errors\n", dram_addr, sram_addr, fail_count);
        }
      }  
      if ((samples % 200) == 0 && samples >0)
        printf ("Now samples count %d , fail count %d\n", samples, fail_count);
    }
    printf("[DONE] Test3 Done with %d faults!\n", fail_count);
    overall_fail += fail_count;
  }

  if(overall_fail == 0)
  {
    //return pass_ddr_test();
    return 0;
  }
  else
  {
    //return fail_ddr_test(0, overall_fail, rd_err_count+pos_rd_err_count, pos_wr_err_count);
    return -1;
  }
}

