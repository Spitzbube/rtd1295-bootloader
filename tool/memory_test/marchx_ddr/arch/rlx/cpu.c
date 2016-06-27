/*
 * Realtek Semiconductor Corp.
 *
 * cache-rlx.c: RLX specific mmu/cache code.
 *
 * Tony Wu (tonywu@realtek.com)
 * Dec. 07, 2008
 */
#include <cpu.h>

/*
 * Determine whether CPU has CACHE OP
 */
#if defined(CONFIG_CPU_RLX4181) || defined(CONFIG_CPU_RLX5181) || \
    defined(CONFIG_CPU_RLX4281) || defined(CONFIG_CPU_RLX5281) || \
    defined(CONFIG_CPU_RLX4381) || defined(CONFIG_CPU_RLX5381)
  #define CONFIG_CPU_HAS_DCACHE_OP
  #define CONFIG_CPU_HAS_WBC
#else
  #undef CONFIG_CPU_HAS_DCACHE_OP
#endif

#if defined(CONFIG_CPU_RLX4281) || defined(CONFIG_CPU_RLX5281) || \
    defined(CONFIG_CPU_RLX4381) || defined(CONFIG_CPU_RLX5381)
  #define CONFIG_CPU_HAS_ICACHE_OP
  #define CONFIG_CPU_HAS_WBIC
#else
  #undef CONFIG_CPU_HAS_ICACHE_OP
#endif

/*
 *  CACHE OP
 *   0x10 = IInval
 *   0x11 = DInval
 *   0x15 = DWBInval
 *   0x19 = DWB
 *   0x1b = DWB_IInval
 */
#if defined(CONFIG_CPU_HAS_WBC) || defined(CONFIG_CPU_HAS_L2C)
  #define CACHE_ICACHE_INVAL	0x10
  #define CACHE_DCACHE_INVAL	0x11
  #define CACHE_DCACHE_FLUSH	0x15
  #define CACHE_DCACHE_WBACK	0x19
#else
  #define CACHE_ICACHE_INVAL	0x10
  #define CACHE_DCACHE_INVAL	0x11
  #define CACHE_DCACHE_FLUSH	0x11
  #define CACHE_DCACHE_WBACK	0x11
#endif

#ifdef CONFIG_CPU_HAS_WBIC
  #define CACHE_ICACHE_FLUSH	0x1b
#else
  #define CACHE_ICACHE_FLUSH	0x10
#endif

#define CACHE_OP(op, p)          \
    __asm__ __volatile__ (       \
         ".set  push\n"          \
         ".set  noreorder\n"     \
         "cache %0, 0x000(%1)\n" \
         ".set  pop\n"           \
         : : "i" (op), "r" (p)   \
    )

/*
 *  CCTL OP
 *   0x1   = DInval
 *   0x2   = IInval
 *   0x100 = DWB
 *   0x200 = DWB_Inval
 */
#define CCTL_ICACHE_FLUSH		0x2
#if defined(CONFIG_CPU_HAS_WBC) || defined(CONFIG_CPU_HAS_L2C)
  #define CCTL_ICACHE_INVAL		0x002
  #define CCTL_DCACHE_INVAL		0x001
  #define CCTL_DCACHE_WBACK		0x100
  #define CCTL_DCACHE_FLUSH		0x200
#else
  #define CCTL_ICACHE_INVAL		0x002
  #define CCTL_DCACHE_INVAL		0x001
  #define CCTL_DCACHE_WBACK		0x001
  #define CCTL_DCACHE_FLUSH		0x001
#endif

#if defined(CONFIG_CPU_RLX4281) || defined(CONFIG_CPU_RLX5281) || \
    defined(CONFIG_CPU_RLX4281) || defined(CONFIG_CPU_RLX5281)
#define CCTL_OP(op)		\
    __asm__ __volatile__(	\
       ".set  push\n"		\
       ".set  noreorder\n"	\
       "mtc0	$0, $20\n"	\
       "li	$8, %0\n"	\
       "mtc0	$8, $20\n"	\
       ".set  pop\n"		\
       : : "i" (op)		\
   )
#else
#define CCTL_OP(op)		\
    __asm__ __volatile__(	\
       ".set  push\n"		\
       ".set  noreorder\n"	\
       "mfc0	$8, $20\n"	\
       "ori	$8, %0\n"	\
       "xori	$9, $8, %0\n"	\
       "mtc0	$9, $20\n"	\
       "mtc0	$8, $20\n"	\
       ".set pop\n"		\
       : : "i" (op)		\
   )
#endif

/*
 * Dummy cache handling routines for machines without boardcaches
 */
static inline void rlx_flush_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line) {
		CACHE_OP(CACHE_DCACHE_FLUSH, p);
	}

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(CACHE_DCACHE_FLUSH, p);
}

static inline void rlx_invalid_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line) {
		CACHE_OP(CACHE_DCACHE_INVAL, p);
	}

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(CACHE_DCACHE_INVAL, p);
}

static inline void rlx_wback_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line) {
		CACHE_OP(CACHE_DCACHE_WBACK, p);
	}

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(CACHE_DCACHE_WBACK, p);
}

#ifdef CONFIG_CPU_HAS_ICACHE_OP
static inline void rlx_invalid_icache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_icache_line) {
		CACHE_OP(CACHE_ICACHE_INVAL, p);
	}

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(CACHE_ICACHE_INVAL, p);
}

static inline void rlx_flush_icache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_icache_line) {
		CACHE_OP(CACHE_ICACHE_FLUSH, p);
	}

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(CACHE_ICACHE_FLUSH, p);
}
#endif /* CONFIG_CPU_HAS_ICACHE_OP */

/*
 * DCACHE part
 */
void cpu_dcache_wback_range(unsigned long start, unsigned long end)
{
#ifdef CONFIG_CPU_HAS_DCACHE_OP
	if (end - start > cpu_dcache_size) {
		CCTL_OP(CCTL_DCACHE_WBACK);
		return;
	}
	rlx_wback_dcache_fast(start, end);
#else
	CCTL_OP(CCTL_DCACHE_WBACK);
#endif
}

void cpu_dcache_invalid_range(unsigned long start, unsigned long end)
{
#ifdef CONFIG_CPU_HAS_DCACHE_OP
	if (end - start > cpu_dcache_size) {
		CCTL_OP(CCTL_DCACHE_INVAL);
		return;
	}
	rlx_invalid_dcache_fast(start, end);
#else
	CCTL_OP(CCTL_DCACHE_INVAL);
#endif
}

void cpu_dcache_flush_range(unsigned long start, unsigned long end)
{
#ifdef CONFIG_CPU_HAS_DCACHE_OP
	if (end - start > cpu_dcache_size) {
		CCTL_OP(CCTL_DCACHE_FLUSH);
		return;
	}
	rlx_flush_dcache_fast(start, end);
#else
	CCTL_OP(CCTL_DCACHE_FLUSH);
#endif
}

void cpu_dcache_wback_all(void)
{
	CCTL_OP(CCTL_DCACHE_WBACK);
}

void cpu_dcache_invalid_all(void)
{
	CCTL_OP(CCTL_DCACHE_INVAL);
}

void cpu_dcache_flush_all(void)
{
	CCTL_OP(CCTL_DCACHE_FLUSH);
}


/*
 * ICACHE part
 */
void cpu_icache_invalid_range(unsigned long start, unsigned long end)
{
#ifdef CONFIG_CPU_HAS_ICACHE_OP
	unsigned long size;

	size = end - start;
	if (size > cpu_icache_size) {
		CCTL_OP(CCTL_ICACHE_INVAL);
		return;
	}

	rlx_invalid_icache_fast(start, end);
#else
	CCTL_OP(CCTL_ICACHE_INVAL);
#endif
}

void cpu_cache_coherent_range(unsigned long start, unsigned long end)
{
#ifdef CONFIG_CPU_HAS_ICACHE_OP
	unsigned long size;

  #if !defined(CONFIG_CPU_HAS_WBIC) \
	&& (defined(CONFIG_CPU_HAS_WBC) \
		|| defined(CONFIG_CPU_HAS_L2C))
	cpu_dcache_flush_range(start, end);
  #endif

	size = end - start;
	if (size > cpu_icache_size) {
  #ifdef CONFIG_CPU_HAS_WBIC
		if (size > cpu_dcache_size) {
			CCTL_OP(CCTL_ICACHE_FLUSH | CCTL_DCACHE_FLUSH);
			return;
		} else
			rlx_flush_dcache_fast(start, end);
  #endif
		CCTL_OP(CCTL_ICACHE_FLUSH);
		return;
	}

	rlx_flush_icache_fast(start, end);
#else
	cpu_dcache_flush_range(start, end);
	CCTL_OP(CCTL_ICACHE_FLUSH);
#endif
}

void cpu_icache_invalid_all(void)
{
	CCTL_OP(CCTL_ICACHE_FLUSH);
}


/*
 * CACHE part
 */
void cpu_cache_coherent_all(void)
{
#ifdef CONFIG_CPU_HAS_WBIC
	CCTL_OP(CCTL_ICACHE_FLUSH | CCTL_DCACHE_FLUSH);
#else
	CCTL_OP(CCTL_DCACHE_FLUSH);
	CCTL_OP(CCTL_ICACHE_FLUSH);
#endif
}

