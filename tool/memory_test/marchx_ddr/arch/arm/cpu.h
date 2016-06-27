/*
 * Realtek Semiconductor Corp.
 *
 * cache-rlx.c: RLX specific mmu/cache code.
 *
 * Tony Wu (tonywu@realtek.com)
 * Dec. 07, 2008
 */
#ifndef __CPU_UTILS_H__
#define __CPU_UTILS_H__

#include <target/target.h>

#define REG32(reg)		(*(volatile unsigned int   *)(reg))
#define REG16(reg)		(*(volatile unsigned short *)(reg))
#define REG08(reg)		(*(volatile unsigned char  *)(reg))

/*
 * DCACHE part
 */
/* writeback dcache line for address area [start, end] */
extern void cpu_dcache_wback_range(unsigned long start, unsigned long end);

/* invalidate dcache line for address area [start, end] */
extern void cpu_dcache_invalid_range(unsigned long start, unsigned long end);

/* writeback-invalidate dcache line for address area [start, end] */
extern void cpu_dcache_flush_range(unsigned long start, unsigned long end);

/* writeback whole dcache */
extern void cpu_dcache_wback_all(void);

/* invalidate whole dcache */
extern void cpu_dcache_invalid_all(void);

/* writeback-invalidate whole dcache */
extern void cpu_dcache_flush_all(void);

/*
 * ICACHE part
 */
/* invalidate icache line for address area [start, end]  */
extern void cpu_icache_invalid_range(unsigned long start, unsigned long end);

/* invalidate whole icache */
extern void cpu_icache_invalid_all(void);

/* writeback-invalidate dcache line, then invalidate icache line for 
 * address area [start, end]  */
extern void cpu_cache_coherent_range(unsigned long start, unsigned long end);

/*
 * CACHE part
 */
/* flush all dcache and icache */
extern void cpu_cache_coherent_all(void);

/*
 * delay
 */
#define NOP() \
do { \
	asm volatile ( \
		"nop\n" \
	:::"memory"); \
} while (0)

#define NOP2() \
do { \
	asm volatile ( \
		"nop\n" \
		"nop\n" \
	:::"memory"); \
} while (0)

#define NOP4() \
do { \
	asm volatile ( \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
	:::"memory"); \
} while (0)

#define NOP8() \
do { \
	asm volatile ( \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
		"nop\n" \
	:::"memory"); \
} while (0)


/* coarse delay for several cpu count */
static inline void delay(int count)
{
	int i;
	for (i = 0; i < count; i++)
		NOP();
}


#endif /* __CPU_UTILS_H__ */
