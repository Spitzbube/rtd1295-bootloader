
.equ UART_BASE_ADDRESS, 0x1801B100
.equ PERIPH_BASE, 0x1801E000
.equ CPU_INIT, 0

@ Distributor
.equ IC_DIST_BASE, PERIPH_BASE + 0x1000 
.equ IC_INT_BASE, PERIPH_BASE + 0x100
.equ ACK_IRQ, 0x0c
.equ EOI_IRQ, 0x10

    .arm
    .global start
    .global _exit
    .global __PutCharacter

.section ".text.boot", "ax"
.align  4
start:
    @ cache initialize has been done by
    @ uboot in OMAP platform. Therefore
    @ we just start with MMU initialization

    @ -----------------------
    @ INIT the MMU
    @ -----------------------
    @ disable MMU first
    MRC    p15, 0, r1, c1, c0, 0       @ get control register (c1)
    BIC    r1, r1, #1                  @ M bit (MMU enabled)
    BIC    r1, r1, #(1 << 2)           @ C bit (Data cache)
    BIC    r1, r1, #(1 << 3)           @ W bit (Write buffer)
    BIC    r1, r1, #(1 << 11)          @ Z bit (Branch prediction)
    BIC    r1, r1, #(1 << 12)          @ I bit (Instruction cache)
    BIC    r1, r1, #(1 << 13)          @ V bit (Low exception vectors)
    ORR    r1, r1, #(1 << 22)          @ U bit (Unaligned data access)
    ORR    r1, r1, #(1 << 23)          @ XP bit (Extended page tables)
    MCR    p15, 0, r1, c1, c0, 0

    @ Invalidate TLBs
    MOV    r0, #0
    MCR    p15, 0, r0, c8, c7, 0       @ Invalidate TLBs
    MCR    p15, 0, r0, c7, c5, 0
    MCR    p15, 0, r0, c7, c5, 6
    DSB
    ISB

    @ program Translation Table Base register
    LDR     r0, =MMU_PageTable
    MCR     p15, 0, r0, c2, c0, 0
    DSB
    ISB

    @ program Domain Access Control register
    LDR     r0, =0x55555555      @ D0-D15 = Client
    MCR     p15, 0, r0, c3, c0, 0
#if 1
    @ program Control register, enabling MMU
    MRC    p15, 0, r1, c1, c0, 0       @ get control register (c1)
    ORR    r1, r1, #1                  @ M bit (MMU enabled)
    BIC    r1, r1, #(1 << 2)           @ C bit (Data cache)
    BIC    r1, r1, #(1 << 3)           @ W bit (Write buffer)
    ORR    r1, r1, #(1 << 11)          @ Z bit (Branch prediction)
    BIC    r1, r1, #(1 << 12)          @ I bit (Instruction cache)
    ORR    r1, r1, #(1 << 13)          @ V bit (Low exception vectors)
    BIC    r1, r1, #(1 << 22)          @ U bit (Unaligned data access)
    BIC    r1, r1, #(1 << 23)          @ XP bit (Extended page tables)
    MCR    p15, 0, r1, c1, c0, 0
    DSB
    ISB
#endif
    MRC     p15, 0, r11, c0, c0, 5
    AND     r11, r11, #0xf
    CMP     r11, #CPU_INIT

    @ invalidate SCU tag RAMs
    LDR     r10, =PERIPH_BASE + 0xc
    LDR     r11, =0xffff
    STR     r11, [r10]
    DSB

    @ enable SCU
    LDR     r10, =PERIPH_BASE
    LDR     r1, [r10]
    ORR     r1, r1, #1
    STR     r1, [r10]

    @ Initialising Interrupt controller
    LDR     r12, =IC_DIST_BASE
    MOV     r0, #1
    STR     r0, [r12]

    @ Initialising UART
    LDR     r0, =UART_BASE_ADDRESS
    LDR     r1, =0x80                    @ UART_LCR = LCR_DLAB
    STR     r1, [r0, #0xc]
    LDR     r1, =0x0                     @ UART_LCR = LCR_DLAB
    STR     r1, [r0, #0x4]
    LDR     r1, =0x1b                    @ UART_LCR = LCR_DLAB
    STR     r1, [r0, #0x0]
    LDR     r1, =0x3                     @ UART_LCR = LCR_DLAB
    STR     r1, [r0, #0xc]
    @ -----------------------
    @ C initialization
    @ -----------------------
    LDR     sp, =stack_base
    BL      main
    nop

_exit:
    B     _exit

 /*
** PutC
** Instruction used to perform character output
** from programs running during simulation.
*/
 __PutCharacter:
    LDR     r1, =UART_BASE_ADDRESS
#if 1
1:
    LDR     r2, [r1, #0x14]  @ get page table physical address
    ANDS    r2, #0x20
    BEQ     1b
#endif
    STR     r0, [r1]
    MOV     pc, r14

@ mmu table
#include "page_table.inc"

.bss
    .global stack_top
    .global stack_base
    .align 4
stack_top:
    .fill 4096, 4, 0
    .align 4
stack_base:
    .fill 4, 4, 0

