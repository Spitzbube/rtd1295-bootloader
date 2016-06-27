#include <stdio.h>
#include <cpu.h>

/* cache operations */

#define CACHE_OPCODE( code, type )                  ( ((code) << 2) | (type) )

#define ICACHE_INDEX_INVALIDATE                 CACHE_OPCODE(0x0, 0)
#define ICACHE_INDEX_LOAD_TAG                   CACHE_OPCODE(0x1, 0)
#define ICACHE_INDEX_STORE_TAG                  CACHE_OPCODE(0x2, 0)
#define DCACHE_INDEX_WRITEBACK_INVALIDATE       CACHE_OPCODE(0x0, 1)
#define DCACHE_INDEX_LOAD_TAG                   CACHE_OPCODE(0x1, 1)
#define DCACHE_INDEX_STORE_TAG                  CACHE_OPCODE(0x2, 1)
#define SCACHE_INDEX_WRITEBACK_INVALIDATE       CACHE_OPCODE(0x0, 3)
#define SCACHE_INDEX_STORE_TAG                  CACHE_OPCODE(0x2, 3)

#define ICACHE_ADDR_HIT_INVALIDATE              CACHE_OPCODE(0x4, 0)
#define ICACHE_ADDR_FILL                        CACHE_OPCODE(0x5, 0)
#define ICACHE_ADDR_FETCH_LOCK                  CACHE_OPCODE(0x7, 0)
#define DCACHE_ADDR_HIT_INVALIDATE              CACHE_OPCODE(0x4, 1)
#define DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE    CACHE_OPCODE(0x5, 1)
#define DCACHE_ADDR_HIT_WRITEBACK               CACHE_OPCODE(0x6, 1)
#define DCACHE_ADDR_FETCH_LOCK                  CACHE_OPCODE(0x7, 1)

#define SCACHE_ADDR_HIT_INVALIDATE              CACHE_OPCODE(0x4, 3)
#define SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE    CACHE_OPCODE(0x5, 3)
#define SCACHE_ADDR_HIT_WRITEBACK               CACHE_OPCODE(0x6, 3)

#define CACHE_OP(op, p)          \
    __asm__ __volatile__ (       \
         ".set  push\n"          \
         ".set  noreorder\n"     \
         "cache %0, 0x000(%1)\n" \
         ".set  pop\n"           \
         : : "i" (op), "r" (p)   \
    )

#if defined(CONFIG_CPU_MIPS1074K)
#define CLEAR_DTAG_HILO		\
    __asm__ __volatile__ (      \
	".set  push\n"          \
	".set  noreorder\n"     \
	"mtc0  $0, $29, 2\n"	\
	"mtc0  $0, $28, 2\n"	\
	".set  pop\n"           \
	: : 			\
    )
#else
#define CLEAR_DTAG_HILO         \
    __asm__ __volatile__ (      \
        ".set  push\n"          \
        ".set  noreorder\n"     \
        "mtc0  $0, $28, 2\n"  \
        ".set  pop\n"           \
        : :                     \
    )
#endif

#if defined(CONFIG_CPU_L2CACHE)
#define CLEAR_L23TAG_HILO       \
    __asm__ __volatile__ (      \
        ".set  push\n"          \
        ".set  noreorder\n"     \
        "mtc0  $0, $29, 4\n"  \
        "mtc0  $0, $28, 4\n"  \
        ".set  pop\n"           \
        : :                     \
    )

static inline void mips_invalid_l2cache_all(void)
{
        unsigned long p;
        unsigned long start = KSEG0BASE;
        unsigned long end = KSEG0BASE + cpu_l2cache_size - cpu_l2cache_line;

	CLEAR_L23TAG_HILO;
        for (p = start; p < end; p += cpu_l2cache_line)
                CACHE_OP(SCACHE_INDEX_STORE_TAG, p);

        p = p & ~(cpu_l2cache_line -1);
        if (p <= end)
                CACHE_OP(SCACHE_INDEX_STORE_TAG, p);
}

static inline void mips_flush_l2cache_all(void)
{
        unsigned long p;
        unsigned long start = KSEG0BASE;
        unsigned long end = KSEG0BASE + cpu_l2cache_size - cpu_l2cache_line;

        for (p = start; p < end; p += cpu_l2cache_line)
                CACHE_OP(SCACHE_INDEX_WRITEBACK_INVALIDATE, p);

        p = p & ~(cpu_l2cache_line -1);
        if (p <= end)
                CACHE_OP(SCACHE_INDEX_WRITEBACK_INVALIDATE, p);
}

static inline void mips_flush_l2cache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

        for (p = start; p < end; p += cpu_dcache_line)
		CACHE_OP(SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, p);

        p = p & ~(cpu_dcache_line -1);
        if (p <= end)
		CACHE_OP(SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, p);
}

static inline void mips_invalid_l2cache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

        for (p = start; p < end; p += cpu_dcache_line)
                CACHE_OP(SCACHE_ADDR_HIT_INVALIDATE, p);

        p = p & ~(cpu_dcache_line -1);
        if (p <= end)
                CACHE_OP(SCACHE_ADDR_HIT_INVALIDATE, p);
}

static inline void mips_wback_l2cache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

        for (p = start; p < end; p += cpu_dcache_line)
                CACHE_OP(SCACHE_ADDR_HIT_WRITEBACK, p);

        p = p & ~(cpu_dcache_line -1);
        if (p <= end)
                CACHE_OP(SCACHE_ADDR_HIT_WRITEBACK, p);
}
#endif

/*
 * Dummy cache handling routines for machines without boardcaches
 */

static inline void mips_invalid_dcache_all(void)
{
        unsigned long p;
	unsigned long start = KSEG0BASE;
	unsigned long end = KSEG0BASE + cpu_dcache_size - cpu_dcache_line;

	CLEAR_DTAG_HILO;
        for (p = start; p < end; p += cpu_dcache_line)
                CACHE_OP(DCACHE_INDEX_STORE_TAG, p);

        p = p & ~(cpu_dcache_line -1);
        if (p <= end)
                CACHE_OP(DCACHE_INDEX_STORE_TAG, p);
}

static inline void mips_flush_dcache_all(void)
{
        unsigned long p;
	unsigned long start = KSEG0BASE;
        unsigned long end = KSEG0BASE + cpu_dcache_size - cpu_dcache_line;

        for (p = start; p < end; p += cpu_dcache_line)
                CACHE_OP(DCACHE_INDEX_WRITEBACK_INVALIDATE, p);

        p = p & ~(cpu_dcache_line -1);
        if (p <= end)
                CACHE_OP(DCACHE_INDEX_WRITEBACK_INVALIDATE, p);
}

static inline void mips_flush_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line)
		CACHE_OP(DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, p);

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, p);
}

static inline void mips_invalid_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line)
		CACHE_OP(DCACHE_ADDR_HIT_INVALIDATE, p);

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(DCACHE_ADDR_HIT_INVALIDATE, p);
}

static inline void mips_wback_dcache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_dcache_line)
		CACHE_OP(DCACHE_ADDR_HIT_WRITEBACK, p);

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(DCACHE_ADDR_HIT_WRITEBACK, p);
}

static inline void mips_invalid_icache_all(void)
{
        unsigned long p;
        unsigned long start = KSEG0BASE;
        unsigned long end = KSEG0BASE + cpu_icache_size - cpu_icache_line;

        for (p = start; p < end; p += cpu_icache_line)
                CACHE_OP(ICACHE_INDEX_INVALIDATE, p);

        p = p & ~(cpu_icache_line -1);
        if (p <= end)
                CACHE_OP(ICACHE_INDEX_INVALIDATE, p);
}

static inline void mips_invalid_icache_fast(unsigned long start, unsigned long end)
{
	unsigned long p;

	for (p = start; p < end; p += cpu_icache_line)
		CACHE_OP(ICACHE_ADDR_HIT_INVALIDATE, p);

	p = p & ~(cpu_dcache_line -1);
	if (p <= end)
		CACHE_OP(ICACHE_ADDR_HIT_INVALIDATE, p);
}

/*
 * DCACHE part
 */
void cpu_dcache_wback_range(unsigned long start, unsigned long end)
{
	if (end - start > cpu_dcache_size) {
		mips_flush_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
		mips_flush_l2cache_all();
#endif
		return;
	}

	mips_wback_dcache_fast(start, end);
#if defined(CONFIG_CPU_L2CACHE)
	mips_wback_l2cache_fast(start, end);
#endif
}

void cpu_dcache_invalid_range(unsigned long start, unsigned long end)
{
	if (end - start > cpu_dcache_size) {
		mips_invalid_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
		mips_invalid_l2cache_all();
#endif
		return;
	}
	mips_invalid_dcache_fast(start, end);
#if defined(CONFIG_CPU_L2CACHE)
	mips_invalid_l2cache_fast(start, end);
#endif
}

void cpu_dcache_flush_range(unsigned long start, unsigned long end)
{
	if (end - start > cpu_dcache_size) {
		mips_flush_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
		mips_flush_l2cache_all();
#endif
		return;
	}
	mips_flush_dcache_fast(start, end);
#if defined(CONFIG_CPU_L2CACHE)
	mips_flush_l2cache_fast(start, end);
#endif
}

void cpu_dcache_wback_all(void)
{
	mips_flush_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
	mips_flush_l2cache_all();
#endif
}

void cpu_dcache_invalid_all(void)
{
	mips_invalid_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
	mips_invalid_l2cache_all();
#endif
}

void cpu_dcache_flush_all(void)
{
	mips_flush_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
	mips_flush_l2cache_all();
#endif
}


/*
 * ICACHE part
 */
void cpu_icache_invalid_range(unsigned long start, unsigned long end)
{
	unsigned long size;

	size = end - start;
	if (size > cpu_icache_size) {
		mips_invalid_icache_all();
#if defined(CONFIG_CPU_L2CACHE)
		mips_invalid_l2cache_all();
#endif
		return;
	}

	mips_invalid_icache_fast(start, end);
#if defined(CONFIG_CPU_L2CACHE)
	mips_invalid_l2cache_fast(start, end);
#endif
}

void cpu_cache_coherent_range(unsigned long start, unsigned long end)
{
	unsigned long size;

	size = end - start;

	if (size > cpu_dcache_size) {
		mips_flush_dcache_all();
	} else
		mips_flush_dcache_fast(start, end);
#if defined(CONFIG_CPU_L2CACHE)
	if (size > cpu_l2cache_size) {
		mips_flush_l2cache_all();
	} else
		mips_flush_l2cache_fast(start, end);
#endif
	if (size > cpu_icache_size) {
		mips_invalid_icache_all();
	} else {
		mips_invalid_icache_fast(start,end);
	}

}

void cpu_icache_invalid_all(void)
{
	mips_invalid_icache_all();
#if defined(CONFIG_CPU_L2CACHE)
	mips_invalid_l2cache_all();
#endif
}


/*
 * CACHE part
 */
void cpu_cache_coherent_all(void)
{
	mips_flush_dcache_all();
#if defined(CONFIG_CPU_L2CACHE)
	mips_flush_l2cache_all();
#endif
	mips_invalid_icache_all();
}
