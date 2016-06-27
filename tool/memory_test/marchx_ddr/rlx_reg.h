/*
 * Realtek Semiconductor Corp.
 *
 * rlx_reg.h
 *   Register alias for RLX processors
 *
 * Viller Hsiao(villerhsiao@realtek.com.tw)
 * Tony Wu (tonywu@realtek.com.tw)
 */
#ifndef _RLX_REG_H_
#define _RLX_REG_H_

/*
 * Coprocessor 0 register names
 */

#define CP0_INDEX                      $0
#define CP0_RANDOM                     $1
#define CP0_ENTRYLO                    $2
#define CP0_CONTEXT                    $4
#define CP0_WIRED                      $6
#define CP0_BADVADDR                   $8
#define CP0_ENTRYHI                    $10
#define CP0_STATUS                     $12
#define CP0_SR                         $12
#define CP0_CAUSE                      $13
#define CP0_EPC                        $14
#define CP0_PRID                       $15
#define CP0_DREG                       $16
#define CP0_DEPC                       $17
#define CP0_CCTL                       $20
#define CP0_DESAVE                     $31

/*
 * R4640/R4650 cp0 register names.  These registers are listed
 * here only for completeness; without MMU these CPUs are not useable
 * by Linux.  A future ELKS port might take make Linux run on them
 * though ...
 */
#define CP0_IBASE                      $0
#define CP0_IBOUND                     $1
#define CP0_DBASE                      $2
#define CP0_DBOUND                     $3
#define CP0_CALG                       $17
#define CP0_IWATCH                     $18
#define CP0_DWATCH                     $19

/*
 * Coprocessor 0 Set 1 register names
 */
#define CP0_S1_DERRADDR0               $26
#define CP0_S1_DERRADDR1               $27
#define CP0_S1_INTCONTROL              $20

/*
 * Coprocessor 0 Set 2 register names
 */
#define CP0_S2_SRSCTL                  $12             /* MIPSR2 */

/*
 * Coprocessor 0 Set 3 register names
 */
#define CP0_S3_SRSMAP                  $12             /* MIPSR2 */

/*
 * Bitfields in the R3000 cp0 status register.
 */
#define ST0_IEC                        0x00000001
#define ST0_KUC                        0x00000002
#define ST0_IEP                        0x00000004
#define ST0_KUP                        0x00000008
#define ST0_IEO                        0x00000010
#define ST0_KUO                        0x00000020
/* bits 6 & 7 are reserved on R3000 */
#define ST0_ISC                        0x00010000
#define ST0_SWC                        0x00020000
#define ST0_CM                         0x00080000

/*
 * Status register bits available in all MIPS CPUs.
 */
#define _ULCAST_(i)                    (i)
#define ST0_IM                         0x0000ff00
#define STATUSB_IP0                    8
#define STATUSF_IP0                    (_ULCAST_(1) <<  8)
#define STATUSB_IP1                    9
#define STATUSF_IP1                    (_ULCAST_(1) <<  9)
#define STATUSB_IP2                    10
#define STATUSF_IP2                    (_ULCAST_(1) << 10)
#define STATUSB_IP3                    11
#define STATUSF_IP3                    (_ULCAST_(1) << 11)
#define STATUSB_IP4                    12
#define STATUSF_IP4                    (_ULCAST_(1) << 12)
#define STATUSB_IP5                    13
#define STATUSF_IP5                    (_ULCAST_(1) << 13)
#define STATUSB_IP6                    14
#define STATUSF_IP6                    (_ULCAST_(1) << 14)
#define STATUSB_IP7                    15
#define STATUSF_IP7                    (_ULCAST_(1) << 15)
#define STATUSB_IP8                    0
#define STATUSF_IP8                    (_ULCAST_(1) <<  0)
#define STATUSB_IP9                    1
#define STATUSF_IP9                    (_ULCAST_(1) <<  1)
#define STATUSB_IP10                   2
#define STATUSF_IP10                   (_ULCAST_(1) <<  2)
#define STATUSB_IP11                   3
#define STATUSF_IP11                   (_ULCAST_(1) <<  3)
#define STATUSB_IP12                   4
#define STATUSF_IP12                   (_ULCAST_(1) <<  4)
#define STATUSB_IP13                   5
#define STATUSF_IP13                   (_ULCAST_(1) <<  5)
#define STATUSB_IP14                   6
#define STATUSF_IP14                   (_ULCAST_(1) <<  6)
#define STATUSB_IP15                   7
#define STATUSF_IP15                   (_ULCAST_(1) <<  7)
#define ST0_CH                         0x00040000
#define ST0_SR                         0x00100000
#define ST0_TS                         0x00200000
#define ST0_BEV                        0x00400000
#define ST0_RE                         0x02000000
#define ST0_FR                         0x04000000
#define ST0_CU                         0xf0000000
#define ST0_CU0                        0x10000000
#define ST0_CU1                        0x20000000
#define ST0_CU2                        0x40000000
#define ST0_CU3                        0x80000000
#define ST0_XX                         0x80000000      /* MIPS IV naming */

/*
 * Bitfields and bit numbers in the coprocessor 0 cause register.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.
 */
#define CAUSEB_EXCCODE                 2
#define CAUSEF_EXCCODE                 (_ULCAST_(31)  <<  2)
#define CAUSEB_IP                      8
#define CAUSEF_IP                      (_ULCAST_(255) <<  8)
#define CAUSEB_IP0                     8
#define CAUSEF_IP0                     (_ULCAST_(1)   <<  8)
#define CAUSEB_IP1                     9
#define CAUSEF_IP1                     (_ULCAST_(1)   <<  9)
#define CAUSEB_IP2                     10
#define CAUSEF_IP2                     (_ULCAST_(1)   << 10)
#define CAUSEB_IP3                     11
#define CAUSEF_IP3                     (_ULCAST_(1)   << 11)
#define CAUSEB_IP4                     12
#define CAUSEF_IP4                     (_ULCAST_(1)   << 12)
#define CAUSEB_IP5                     13
#define CAUSEF_IP5                     (_ULCAST_(1)   << 13)
#define CAUSEB_IP6                     14
#define CAUSEF_IP6                     (_ULCAST_(1)   << 14)
#define CAUSEB_IP7                     15
#define CAUSEF_IP7                     (_ULCAST_(1)   << 15)
#define CAUSEB_IV                      23
#define CAUSEF_IV                      (_ULCAST_(1)   << 23)
#define CAUSEB_CE                      28
#define CAUSEF_CE                      (_ULCAST_(3)   << 28)
#define CAUSEB_BD                      31
#define CAUSEF_BD                      (_ULCAST_(1)   << 31)

/*
 * Bits in the coprocessor 0 config register.
 */
/* Generic bits.  */
#define CONF_CM_CACHABLE_NO_WA         0
#define CONF_CM_CACHABLE_WA            1
#define CONF_CM_UNCACHED               2
#define CONF_CM_CACHABLE_NONCOHERENT   3
#define CONF_CM_CACHABLE_CE            4
#define CONF_CM_CACHABLE_COW           5
#define CONF_CM_CACHABLE_CUW           6
#define CONF_CM_CACHABLE_ACCELERATED   7
#define CONF_CM_CMASK                  7
#define CONF_BE                        (_ULCAST_(1) << 15)

/* Bits common to various processors.  */
#define CONF_CU                        (_ULCAST_(1) <<  3)
#define CONF_DB                        (_ULCAST_(1) <<  4)
#define CONF_IB                        (_ULCAST_(1) <<  5)
#define CONF_DC                        (_ULCAST_(7) <<  6)
#define CONF_IC                        (_ULCAST_(7) <<  9)
#define CONF_EB                        (_ULCAST_(1) << 13)
#define CONF_EM                        (_ULCAST_(1) << 14)
#define CONF_SM                        (_ULCAST_(1) << 16)
#define CONF_SC                        (_ULCAST_(1) << 17)
#define CONF_EW                        (_ULCAST_(3) << 18)
#define CONF_EP                        (_ULCAST_(15)<< 24)
#define CONF_EC                        (_ULCAST_(7) << 28)
#define CONF_CM                        (_ULCAST_(1) << 31)

/* 
 * Bits in the coprocessor 0 control register 
 */
#define CP0_CCTL_DMEMON            0x00000400          /* Enable the DMEM              */
#define CP0_CCTL_DMEMOFF           0x00000800          /* Disable the DMEM             */
#define CP0_CCTL_IMEMFILL          0x00000010          /* IMEM fill                    */
#define CP0_CCTL_IMEMOFF           0x00000020          /* Disable the IMEM             */
#define CP0_CCTL_DINVAL            0x00000001          /* The value of DInval          */
#define CP0_CCTL_IINVAL            0x00000002          /* The value of IInval          */
#define CP0_CCTL_DWB               0x00000100          /* The value of DWB             */
#define CP0_CCTL_DWBINVAL          0x00000200          /* The value of DWBInval        */
#define CP0_CCTL_ILOCK_MASK        0x0000000C          /* The mask of ILock            */
#define CP0_CCTL_ILOCK_OFFSET      2                   /* The offset of ILock          */
#define CP0_CCTL_ILOCK_NORMAL      0x00                /* ILock = 00: normal operation */
#define CP0_CCTL_ILOCK_LOCKGATHER  0x02                /* ILock = 10: LockGather mode  */
#define CP0_CCTL_ILOCK_LOCKDOWN    0x03                /* ILock = 11: LockedDown mode  */

/*
 * CP3 register
 */
/* control register */
#define CP3_CTRL                       $0 
/* general register */
#define CP3_IWBASE                     $0              /* Base addr of IW - high order bits */
#define CP3_IWTOP                      $1              /* Top  addr of IW - low  order bits */ 
/* CP3 general register 2 is reserved */
/* CP3 general register 3 is reserved */
#define CP3_DWBASE                     $4              /* Base addr of DW - high order bits */ 
#define CP3_DWTOP                      $5              /* Top  addr of DW - low  order bits */ 
/* CP3 general register 6 is reserved */
/* CP3 general register 7 is reserved */
#define CP3_MONCNT0LO                  $8              /* cnt 0 low  order 32 bits */ 
#define CP3_MONCNT0HI                  $9              /* cnt 0 high order 16 bits */ 
#define CP3_MONCNT1LO                  $10             /* cnt 1 low  order 32 bits */ 
#define CP3_MONCNT1HI                  $11             /* cnt 1 high order 16 bits */ 
#define CP3_MONCNT2LO                  $12             /* cnt 2 low  order 32 bits */ 
#define CP3_MONCNT2HI                  $13             /* cnt 2 high order 16 bits */ 
#define CP3_MONCNT3LO                  $14             /* cnt 3 low  order 32 bits */ 
#define CP3_MONCNT3HI                  $15             /* cnt 3 high order 16 bits */ 
#define CP3_CNTR_EN                    0x1b1a1610


/*
 * Symbolic register names for 32 bit ABI
 */
#define zero                           $0              /* wired zero */
#define AT                             $1              /* assembler temp - uppercase because 
                                                        *  of ".set at" 
                                                        */
#define v0                             $2              /* return value */
#define v1                             $3              
#define a0                             $4              /* argument registers */
#define a1                             $5              
#define a2                             $6              
#define a3                             $7              
#define t0                             $8              /* caller saved */
#define t1                             $9              
#define t2                             $10             
#define t3                             $11             
#define t4                             $12             
#define t5                             $13             
#define t6                             $14             
#define t7                             $15             
#define s0                             $16             /* callee saved */
#define s1                             $17             
#define s2                             $18             
#define s3                             $19             
#define s4                             $20             
#define s5                             $21             
#define s6                             $22             
#define s7                             $23             
#define t8                             $24             /* caller saved */
#define t9                             $25             
#define jp                             $25             /* PIC jump register */
#define k0                             $26             /* kernel scratch */
#define k1                             $27             
#define gp                             $28             /* global pointer */
#define sp                             $29             /* stack pointer */
#define fp                             $30             /* frame pointer */
#define s8                             $30             /* same like fp! */
#define ra                             $31             /* return address */

/* System Control Coprocessor (CP0) exception processing registers */
#define C0_CONTEXT                     $4              /* Context */
#define C0_BADVADDR                    $8              /* Bad Virtual Address */
#define C0_COUNT                       $9              /* Count */
#define C0_COMPARE                     $11             /* Compare */
#define C0_STATUS                      $12             /* Processor Status */
#define C0_CAUSE                       $13             /* Exception Cause */
#define C0_EPC                         $14             /* Exception PC */
#define C0_WATCHLO                     $18             /* Watchpoint LO */
#define C0_WATCHHI                     $19             /* Watchpoint HI */
#define C0_XCONTEXT                    $20             /* XContext */
#define C0_ECC                         $26             /* ECC */
#define C0_CACHEERR                    $27             /* CacheErr */
#define C0_ERROREPC                    $30             /* ErrorEPC */
#define C0_SR                          $12
#define C0_CCTL                        $20

/* Status register fields */
#define SR_CUMASK                      0xf0000000      /* Coprocessor usable bits */
#define SR_CU3                         0x80000000      /* Coprocessor 3 usable */
#define SR_CU2                         0x40000000      /* coprocessor 2 usable */
#define SR_CU1                         0x20000000      /* Coprocessor 1 usable */
#define SR_CU0                         0x10000000      /* Coprocessor 0 usable */
                                       
#define SR_FR                          0x04000000      /* Enable 32 floating-point registers */
#define SR_RE                          0x02000000      /* Reverse Endian in user mode */
                                       
#define SR_BEV                         0x00400000      /* Bootstrap Exception Vector */
#define SR_TS                          0x00200000      /* TLB shutdown (reserved on R4600) */
#define SR_SR                          0x00100000      /* Soft Reset */
                                       
#define SR_CH                          0x00040000      /* Cache Hit */
#define SR_CE                          0x00020000      /* ECC register modifies check bits */
#define SR_DE                          0x00010000      /* Disable cache errors */
                                       
#define SR_SWC                         0x00020000      /* Swap Caches */
#define SR_ISC                         0x00010000      /* Isolate Cache */
                                       
#define SR_IMASK                       0x0000ff00      /* Interrupt Mask */
#define SR_IMASK8                      0x00000000      /* Interrupt Mask level=8 */
#define SR_IMASK7                      0x00008000      /* Interrupt Mask level=7 */
#define SR_IMASK6                      0x0000c000      /* Interrupt Mask level=6 */
#define SR_IMASK5                      0x0000e000      /* Interrupt Mask level=5 */
#define SR_IMASK4                      0x0000f000      /* Interrupt Mask level=4 */
#define SR_IMASK3                      0x0000f800      /* Interrupt Mask level=3 */
#define SR_IMASK2                      0x0000fc00      /* Interrupt Mask level=2 */
#define SR_IMASK1                      0x0000fe00      /* Interrupt Mask level=1 */
#define SR_IMASK0                      0x0000ff00      /* Interrupt Mask level=0 */
                                       
#define SR_IBIT8                       0x00008000      /*  (Intr5) */
#define SR_IBIT7                       0x00004000      /*  (Intr4) */
#define SR_IBIT6                       0x00002000      /*  (Intr3) */
#define SR_IBIT5                       0x00001000      /*  (Intr2) */
#define SR_IBIT4                       0x00000800      /*  (Intr1) */
#define SR_IBIT3                       0x00000400      /*  (Intr0) */
#define SR_IBIT2                       0x00000200      /*  (Software Interrupt 1) */
#define SR_IBIT1                       0x00000100      /*  (Software Interrupt 0) */
                                       
#define SR_KX                          0x00000080      /* xtlb in kernel mode */
#define SR_SX                          0x00000040      /* mips3 & xtlb in supervisor mode */
#define SR_UX                          0x00000020      /* mips3 & xtlb in user mode */
                                       
#define SR_KSU_MASK                    0x00000018      /* ksu mode mask */
#define SR_KSU_USER                    0x00000010      /* user mode */
#define SR_KSU_SUPV                    0x00000008      /* supervisor mode */
#define SR_KSU_KERN                    0x00000000      /* kernel mode */
                                       
#define SR_ERL                         0x00000004      /* error level */
#define SR_EXL                         0x00000002      /* exception level */
#define SR_IE                          0x00000001      /* interrupt enable */

/* Cause register fields */
#define CAUSE_BD                       0x80000000      /* Branch Delay */
#define CAUSE_CEMASK                   0x30000000      /* Coprocessor Error */
#define CAUSE_CESHIFT                  28              /* Right justify CE  */
#define CAUSE_IPMASK                   0x0000ff00      /* Interrupt Pending */
#define CAUSE_IPSHIFT                  8               /* Right justify IP  */
#define CAUSE_IP8                      0x00008000      /*  (Intr5) */
#define CAUSE_IP7                      0x00004000      /*  (Intr4) */
#define CAUSE_IP6                      0x00002000      /*  (Intr3) */
#define CAUSE_IP5                      0x00001000      /*  (Intr2) */
#define CAUSE_IP4                      0x00000800      /*  (Intr1) */
#define CAUSE_IP3                      0x00000400      /*  (Intr0) */
#define CAUSE_SW2                      0x00000200      /*  (Software Interrupt 1) */
#define CAUSE_SW1                      0x00000100      /*  (Software Interrupt 0) */
#define CAUSE_EXCMASK                  0x0000007c      /* Exception Code */
#define CAUSE_EXCSHIFT                 2               /* Right justify EXC */

/* Exception Codes */

#define EXC_INT                        (0 << 2)        /* External interrupt exception code */
#define EXC_SYSCALL                    (8 << 2)        /* system call */
#define EXC_BREAK                      (9 << 2)        /* breakpoint */

#define EXC_MOD                        1               /* TLB modification exception */
#define EXC_TLBL                       2               /* TLB miss (Load or Ifetch) */
#define EXC_TLBS                       3               /* TLB miss (Store) */
#define EXC_ADEL                       4               /* Address error (Load or Ifetch) */
#define EXC_ADES                       5               /* Address error (Store) */
#define EXC_IBE                        6               /* Bus error (Ifetch) */
#define EXC_DBE                        7               /* Bus error (data load or store) */
#define EXC_SYS                        8               /* System call */
#define EXC_BP                         9               /* Break point */
#define EXC_RI                         10              /* Reserved instruction */
#define EXC_CPU                        11              /* Coprocessor unusable */
#define EXC_OVF                        12              /* Arithmetic overflow */
#define EXC_TRAP                       13              /* Trap exception */
#define EXC_FPE                        15              /* Floating Point Exception */

#define KUBASE                         0x00000000
#define K0BASE                         0x80000000
#define K1BASE                         0xa0000000
#define K2BASE                         0xc0000000

/* PRID */
#define PRID_COMP_x181                 0x0000cf01
#define PRID_COMP_5280                 0x0000c601
#define PRID_COMP_4281                 0x0000dc01
#define PRID_COMP_5281                 0x0000dc02

#endif /* _RLX_REG_H_ */
