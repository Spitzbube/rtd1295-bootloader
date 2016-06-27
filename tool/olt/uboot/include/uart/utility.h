#include <asm/io.h>
#ifndef	NULL
#define NULL	((void *)0)
#endif

//#  define memcpy(d, s, n)   bcopy((s), (d), (n)) 

#define KSEG1ADDR(a)	(CPHYSADDR(a) | KSEG1)
#define KSEG1			0xa0000000
#define CPHYSADDR(a)	((_ACAST32_(a)) & 0x1fffffff)
#define KSEGX(a)		((_ACAST32_ (a)) & 0xe0000000)
#define KSEGX(a)		((_ACAST32_ (a)) & 0xe0000000)

#define _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen if necessary */
#define _ATYPE_		__PTRDIFF_TYPE__
#define _ATYPE32_		int


#define size_t       unsigned int

#ifndef _utility_H_
   #define _utility_H_

   // Define Data type
	typedef unsigned int	UINT32;
	typedef unsigned short	UINT16;
	typedef unsigned char	UINT8;
	typedef unsigned char	BOOLEAN;

	#define OK                 true
	#define NG                 false



   // macro definition
#define Rreg32(Addr)            readl(Addr)
	#define Wreg32(Addr,Value)      writel(Value,Addr)
	#define Rreg16(Addr)            readw(Addr)
    #define Wreg16(Addr,Value)      writew(Value,Addr)
	#define Rreg8(Addr)             readb(Addr)
	#define Wreg8(Addr,Value)       writeb(Value,Addr)



#define SYS_CLK 33*1000000	//FPGA
//#define SYS_CLK 27*1000000	//For MISC ASIC
#define CPU_CLK 337*1000000
#define UART_CLK 27*1000000
#define UART_BaudRate 115200

#define BIT0    ((UINT32)(0x1)<<0)
#define BIT1    ((UINT32)(0x1)<<1)
#define BIT2    ((UINT32)(0x1)<<2)
#define BIT3    ((UINT32)(0x1)<<3)
#define BIT4    ((UINT32)(0x1)<<4)
#define BIT5    ((UINT32)(0x1)<<5)
#define BIT6    ((UINT32)(0x1)<<6)
#define BIT7    ((UINT32)(0x1)<<7)
#define BIT8    ((UINT32)(0x1)<<8)
#define BIT9    ((UINT32)(0x1)<<9)
#define BIT10   ((UINT32)(0x1)<<10)
#define BIT11   ((UINT32)(0x1)<<11)
#define BIT12   ((UINT32)(0x1)<<12)
#define BIT13   ((UINT32)(0x1)<<13)
#define BIT14   ((UINT32)(0x1)<<14)
#define BIT15   ((UINT32)(0x1)<<15)
#define BIT16   ((UINT32)(0x1)<<16)
#define BIT17   ((UINT32)(0x1)<<17)
#define BIT18   ((UINT32)(0x1)<<18)
#define BIT19   ((UINT32)(0x1)<<19)
#define BIT20   ((UINT32)(0x1)<<20)
#define BIT21   ((UINT32)(0x1)<<21)
#define BIT22   ((UINT32)(0x1)<<22)
#define BIT23   ((UINT32)(0x1)<<23)
#define BIT24   ((UINT32)(0x1)<<24)
#define BIT25   ((UINT32)(0x1)<<25)
#define BIT26   ((UINT32)(0x1)<<26)
#define BIT27   ((UINT32)(0x1)<<27)
#define BIT28   ((UINT32)(0x1)<<28)
#define BIT29   ((UINT32)(0x1)<<29)
#define BIT30   ((UINT32)(0x1)<<30)
#define BIT31   ((UINT32)(0x1)<<31)




extern void setmem8(UINT8 *, UINT32, UINT8 );
extern void fmemcpy(UINT8 *, UINT8 *, int );
extern void fmemset(void * ,int , int count);
extern int fmemcmp(const void * cs,const void * ct,int count);
extern void sys_wait_ms(UINT32 );
extern void sys_wait_us(UINT32 );
extern void Disable_ETN_Interrupts( );
extern void Disable_Misc_Interrupts( );
extern void dump_reg( );
extern UINT32 ETN_PHY_Read(UINT8 );
extern void ETN_PHY_Write( UINT16, UINT16 );
extern void usdelay();

#endif  // _utility_H_

/*===========================================================================*/

