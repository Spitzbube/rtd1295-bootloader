#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define HEAP_START _end

extern caddr_t HEAP_START;                /* HEAP_START is set in the linker command file */

#define MAX_HEAPSIZE 0x14000

/*
** The RAMSIZE value must be greater than HEAP_START
** for malloc to work.
*/

#  define RAMSIZE             (caddr_t)(((unsigned long)&HEAP_START + (unsigned long)MAX_HEAPSIZE) \
					& ~((unsigned long)0xf))
