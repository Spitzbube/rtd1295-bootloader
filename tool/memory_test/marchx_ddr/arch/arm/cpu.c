/*
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 * Aneesh V <aneesh@ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <cpu.h>
#include <armv7.h>
#include "cache-l2x0.h"

#define ARMV7_DCACHE_INVAL_ALL		1
#define ARMV7_DCACHE_CLEAN_INVAL_ALL	2
#define ARMV7_DCACHE_INVAL_RANGE	3
#define ARMV7_DCACHE_CLEAN_INVAL_RANGE	4

#ifdef CONFIG_CACHE_L2X0
# define CONFIG_CACHE_PL310

void *l2x0_base = (void *) BSP_L2_BASE_ADDR;

static inline void cache_wait_way(void *reg, unsigned long mask)
{
	/* wait for cache operation by line or way to complete */
	while (REG32(reg) & mask)
		;
}

#ifdef CONFIG_CACHE_PL310
static inline void cache_wait(void *reg, unsigned long mask)
{
	/* cache operations by line are atomic on PL310 */
}
#else
#define cache_wait	cache_wait_way
#endif


static inline void cache_sync(void)
{
	void *base = l2x0_base;

	REG32(base + L2X0_CACHE_SYNC) = 0;
	cache_wait(base + L2X0_CACHE_SYNC, 1);
}

static unsigned int get_l2x0_way_mask(void)
{
        unsigned int aux;
        unsigned int cache_id;
        unsigned int mask;
        int ways;

        cache_id = REG32(l2x0_base + L2X0_CACHE_ID);
        aux = REG32(l2x0_base + L2X0_AUX_CTRL);

        /* Determine the number of ways */
        switch (cache_id & L2X0_CACHE_ID_PART_MASK) {
        case L2X0_CACHE_ID_PART_L310:
                if (aux & (1 << 16))
                        ways = 16;
                else
                        ways = 8;
                break;
        case L2X0_CACHE_ID_PART_L210:
                ways = (aux >> 13) & 0xf;
                break;
        default:
                /* Assume unknown chips have 8 ways */
                ways = 8;
                break;
        }

        mask = (1 << ways) - 1;

	return mask;
}

static inline void l2x0_clean_line(unsigned long addr)
{
	void *base = l2x0_base;
	cache_wait(base + L2X0_CLEAN_LINE_PA, 1);
	REG32(base + L2X0_CLEAN_LINE_PA) = addr;
}

static inline void l2x0_inv_line(unsigned long addr)
{
	void *base = l2x0_base;
	cache_wait(base + L2X0_INV_LINE_PA, 1);
	REG32(base + L2X0_INV_LINE_PA) = addr;
}

static inline void l2x0_flush_line(unsigned long addr)
{
	void *base = l2x0_base;
	cache_wait(base + L2X0_CLEAN_INV_LINE_PA, 1);
	REG32(base + L2X0_CLEAN_INV_LINE_PA) = addr;
}

static inline void l2x0_inv_range(unsigned long start, unsigned long stop, unsigned long line_len)
{
	unsigned long mva;

	start = start & ~(line_len -1);
	for (mva = start; mva <= stop; mva += line_len) {
		l2x0_inv_line(mva);
	}
	cache_sync();
}

static inline void l2x0_clean_range(unsigned long start, unsigned long stop, unsigned long line_len)
{
	unsigned long mva;

	start = start & ~(line_len -1);
	for (mva = start; mva <= stop; mva += line_len) {
		l2x0_clean_line(mva);
	}
	cache_sync();
}

static inline void l2x0_flush_range(unsigned long start, unsigned long stop, unsigned long line_len)
{
	unsigned long mva;

	start = start & ~(line_len -1);
	for (mva = start; mva <= stop; mva += line_len) {
		l2x0_flush_line(mva);
	}
	cache_sync();
}

static void l2x0_clean_all(void)
{
	unsigned int l2x0_way_mask = get_l2x0_way_mask();

	/* clean all ways */
	REG32(l2x0_base + L2X0_CLEAN_WAY) = l2x0_way_mask;
	cache_wait_way(l2x0_base + L2X0_CLEAN_WAY, l2x0_way_mask);
	cache_sync();
}

static void l2x0_inv_all(void)
{
	unsigned int l2x0_way_mask = get_l2x0_way_mask();

	/* invalidate all ways */
	/* Invalidating when L2 is enabled is a nono */
	REG32(l2x0_base + L2X0_INV_WAY) = l2x0_way_mask;
	cache_wait_way(l2x0_base + L2X0_INV_WAY, l2x0_way_mask);
	cache_sync();
}

static void __l2x0_flush_all(void)
{
	unsigned int l2x0_way_mask = get_l2x0_way_mask();

	REG32(l2x0_base + L2X0_CLEAN_INV_WAY) = l2x0_way_mask;
	cache_wait_way(l2x0_base + L2X0_CLEAN_INV_WAY, l2x0_way_mask);
	cache_sync();
}
#endif

static inline long log_2_n_round_up(unsigned long n)
{
        long log2n = -1;
        unsigned long temp = n;

        while (temp) {
                log2n++;
                temp >>= 1;
        }   

        if (n & (n - 1)) 
                return log2n + 1; /* not power of 2 - round up */
        else
                return log2n; /* power of 2 */
}

/*
 * Write the level and type you want to Cache Size Selection Register(CSSELR)
 * to get size details from Current Cache Size ID Register(CCSIDR)
 */
static void set_csselr(unsigned long level, unsigned long type)
{	unsigned long csselr = level << 1 | type;

	/* Write to Cache Size Selection Register(CSSELR) */
	asm volatile ("mcr p15, 2, %0, c0, c0, 0" : : "r" (csselr));
}

static unsigned long get_ccsidr(void)
{
	unsigned long ccsidr;

	/* Read current CP15 Cache Size ID Register */
	asm volatile ("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
	return ccsidr;
}

static unsigned long get_clidr(void)
{
	unsigned long clidr;

	/* Read current CP15 Cache Level ID Register */
	asm volatile ("mrc p15,1,%0,c0,c0,1" : "=r" (clidr));
	return clidr;
}

static void v7_inval_dcache_level_setway(unsigned long level, unsigned long num_sets,
					 unsigned long num_ways, unsigned long way_shift,
					 unsigned long log2_line_len)
{
	int way, set, setway;

	/*
	 * For optimal assembly code:
	 *	a. count down
	 *	b. have bigger loop inside
	 */
	for (way = num_ways - 1; way >= 0 ; way--) {
		for (set = num_sets - 1; set >= 0; set--) {
			setway = (level << 1) | (set << log2_line_len) |
				 (way << way_shift);
			/* Invalidate data/unified cache line by set/way */
			asm volatile ("	mcr p15, 0, %0, c7, c6, 2"
					: : "r" (setway));
		}
	}
	/* DSB to make sure the operation is complete */
	CP15DSB;
}

static void v7_clean_inval_dcache_level_setway(unsigned long level, unsigned long num_sets,
					       unsigned long num_ways, unsigned long way_shift,
					       unsigned long log2_line_len)
{
	int way, set, setway;

	/*
	 * For optimal assembly code:
	 *	a. count down
	 *	b. have bigger loop inside
	 */
	for (way = num_ways - 1; way >= 0 ; way--) {
		for (set = num_sets - 1; set >= 0; set--) {
			setway = (level << 1) | (set << log2_line_len) |
				 (way << way_shift);
			/*
			 * Clean & Invalidate data/unified
			 * cache line by set/way
			 */
			asm volatile ("	mcr p15, 0, %0, c7, c14, 2"
					: : "r" (setway));
		}
	}
	/* DSB to make sure the operation is complete */
	CP15DSB;
}

static void v7_maint_dcache_level_setway(unsigned long level, unsigned long operation)
{
	unsigned long ccsidr;
	unsigned long num_sets, num_ways, log2_line_len, log2_num_ways;
	unsigned long way_shift;

	set_csselr(level, ARMV7_CSSELR_IND_DATA_UNIFIED);

	ccsidr = get_ccsidr();

	log2_line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>
				CCSIDR_LINE_SIZE_OFFSET) + 2;
	/* Converting from words to bytes */
	log2_line_len += 2;

	num_ways  = ((ccsidr & CCSIDR_ASSOCIATIVITY_MASK) >>
			CCSIDR_ASSOCIATIVITY_OFFSET) + 1;
	num_sets  = ((ccsidr & CCSIDR_NUM_SETS_MASK) >>
			CCSIDR_NUM_SETS_OFFSET) + 1;
	/*
	 * According to ARMv7 ARM number of sets and number of ways need
	 * not be a power of 2
	 */
	log2_num_ways = log_2_n_round_up(num_ways);

	way_shift = (32 - log2_num_ways);
	if (operation == ARMV7_DCACHE_INVAL_ALL) {
		v7_inval_dcache_level_setway(level, num_sets, num_ways,
				      way_shift, log2_line_len);
	} else if (operation == ARMV7_DCACHE_CLEAN_INVAL_ALL) {
		v7_clean_inval_dcache_level_setway(level, num_sets, num_ways,
						   way_shift, log2_line_len);
	}
}

static void v7_maint_dcache_all(unsigned long operation)
{
	unsigned long level, cache_type, level_start_bit = 0;

	unsigned long clidr = get_clidr();

	for (level = 0; level < 7; level++) {
		cache_type = (clidr >> level_start_bit) & 0x7;
		if ((cache_type == ARMV7_CLIDR_CTYPE_DATA_ONLY) ||
		    (cache_type == ARMV7_CLIDR_CTYPE_INSTRUCTION_DATA) ||
		    (cache_type == ARMV7_CLIDR_CTYPE_UNIFIED))
			v7_maint_dcache_level_setway(level, operation);
		level_start_bit += 3;
	}
}

static void v7_dcache_clean_inval_range(unsigned long start,
					unsigned long stop, unsigned long line_len)
{
	unsigned long mva = 0;

	/* Align start to cache line boundary */
	start &= ~(line_len - 1);
	for (mva = start; mva <= stop; mva = mva + line_len) {
		/* DCCIMVAC - Clean & Invalidate data cache by MVA to PoC */
		asm volatile ("mcr p15, 0, %0, c7, c14, 1" : : "r" (mva));
	}
}

static void v7_icache_inval_range(unsigned long start, unsigned long stop)
{
	unsigned long mva;
	unsigned long line_len, ccsidr;

	ccsidr = get_ccsidr();
	line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>
			CCSIDR_LINE_SIZE_OFFSET) + 2;
	/* Converting from words to bytes */
	line_len += 2;
	/* converting from log2(linelen) to linelen */
	line_len = 1 << line_len;

	/* Align start to cache line boundary */
	start &= ~(line_len - 1);
	for (mva = start; mva <= stop; mva = mva + line_len) {
		/* DCCIMVAC - Clean & Invalidate data cache by MVA to PoC */
		asm volatile ("mcr p15, 0, %0, c7, c5, 1" : : "r" (mva));
	}

	/* Invalidate entire branch predictor array */
	asm volatile ("mcr p15, 0, %0, c7, c5, 6" : : "r" (0));

	/* Full system DSB - make sure that the invalidation is complete */
	CP15DSB;

	/* ISB - make sure the instruction stream sees it */
	CP15ISB;

}

static void v7_dcache_inval_range(unsigned long start, unsigned long stop, unsigned long line_len)
{
	unsigned long mva;

	start = start & ~(line_len -1);
	for (mva = start; mva <= stop; mva += line_len) {
		/* DCIMVAC - Invalidate data cache by MVA to PoC */
		asm volatile ("mcr p15, 0, %0, c7, c6, 1;DMB;" : : "r" (mva));

	}

}

static void v7_dcache_maint_range(unsigned long start, unsigned long stop, unsigned long range_op)
{
	unsigned long line_len, ccsidr;

	ccsidr = get_ccsidr();
	line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>
			CCSIDR_LINE_SIZE_OFFSET) + 2;
	/* Converting from words to bytes */
	line_len += 2;
	/* converting from log2(linelen) to linelen */
	line_len = 1 << line_len;

	switch (range_op) {
	case ARMV7_DCACHE_CLEAN_INVAL_RANGE:
		v7_dcache_clean_inval_range(start, stop, line_len);
		break;
	case ARMV7_DCACHE_INVAL_RANGE:
		v7_dcache_inval_range(start, stop, line_len);
		break;
	}

	/* DSB to make sure the operation is complete */
	CP15DSB;

#ifdef CONFIG_CACHE_L2X0
	switch (range_op) {
	case ARMV7_DCACHE_CLEAN_INVAL_RANGE:
		l2x0_flush_range(start, stop, line_len);
		break;
	case ARMV7_DCACHE_INVAL_RANGE:
		l2x0_inv_range(start, stop, line_len);
		break;
	}

#endif

}

void cpu_dcache_invalid_all(void)
{
	v7_maint_dcache_all(ARMV7_DCACHE_INVAL_ALL);

#ifdef CONFIG_CACHE_L2X0
	l2x0_inv_all();
#endif

}

/*
 * Performs a clean of the entire data cache
 * at all levels
 */
void cpu_dcache_wback_all(void)
{
	v7_maint_dcache_all(ARMV7_DCACHE_CLEAN_INVAL_ALL);

#ifdef CONFIG_CACHE_L2X0
	l2x0_clean_all();
#endif

}

/*
 * Performs a clean & invalidation of the entire data cache
 * at all levels
 */
void cpu_dcache_flush_all(void)
{
	v7_maint_dcache_all(ARMV7_DCACHE_CLEAN_INVAL_ALL);

#ifdef CONFIG_CACHE_L2X0
	__l2x0_flush_all();
#endif

}

/*
 * Invalidates range in all levels of D-cache/unified cache used:
 * Affects the range [start, stop - 1]
 */
void cpu_dcache_invalid_range(unsigned long start, unsigned long stop)
{
	v7_dcache_maint_range(start, stop, ARMV7_DCACHE_INVAL_RANGE);
}

/*
 * Clean range in all levels of D-cache/unified cache used:
 * Affects the range [start, stop - 1]
 */
void cpu_dcache_wback_range(unsigned long start, unsigned long stop)
{
	v7_dcache_maint_range(start, stop, ARMV7_DCACHE_CLEAN_INVAL_RANGE);
}

/*
 * Flush range(clean & invalidate) from all levels of D-cache/unified
 * cache used:
 * Affects the range [start, stop - 1]
 */
void cpu_dcache_flush_range(unsigned long start, unsigned long stop)
{
	v7_dcache_maint_range(start, stop, ARMV7_DCACHE_CLEAN_INVAL_RANGE);
}

void cpu_cache_coherent_range(unsigned long start, unsigned long stop)
{
	cpu_dcache_flush_range(start, stop);

	v7_icache_inval_range(start, stop);
}


void cpu_icache_invalid_range(unsigned long start, unsigned long stop)
{
	v7_icache_inval_range(start, stop);
}

/* Invalidate entire I-cache and branch predictor array */
void cpu_icache_invalid_all(void)
{
	/*
	 * Invalidate all instruction caches to PoU.
	 * Also flushes branch target cache.
	 */
	asm volatile ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

	/* Invalidate entire branch predictor array */
	asm volatile ("mcr p15, 0, %0, c7, c5, 6" : : "r" (0));

	/* Full system DSB - make sure that the invalidation is complete */
	CP15DSB;

	/* ISB - make sure the instruction stream sees it */
	CP15ISB;
}


void cpu_cache_coherent_all(void)
{
	cpu_dcache_flush_all();

	cpu_icache_invalid_all();
}

