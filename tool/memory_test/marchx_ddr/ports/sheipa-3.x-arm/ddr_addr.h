#ifndef _DDR_ADDR_

//#define TEST_ON_SRAM
#ifdef TEST_ON_SRAM
#define DRAM_BASE   0x90010400
#define DRAM_SIZE   0x00000800
#define TEST_BLOCK  0x00000400
#define SRAM_BASE   0x90010000
#else
#define DRAM_BASE   0x80020000
#define DRAM_SIZE   0x00010000
#define TEST_BLOCK  0x00004000
#define SRAM_BASE   0x80018000
#endif 
#endif //_DDR_ADDR_

