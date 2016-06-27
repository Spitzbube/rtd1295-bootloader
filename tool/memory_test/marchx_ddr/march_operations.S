#include "rlx_reg.h"

######################################################################    
    .globl march_write_word_up
    .ent march_write_word_up
# UWa : up sequence, write word (32bits)
# a0: start address
# a1: stop address
# a2: data pattern

march_write_word_up:
    ## get start address
    addiu   t4, a0, 0x0

CoreLoop0:
    sw      a2, 0(t4)
    addiu   t4, t4, 0x4
    bne     t4, a1, CoreLoop0
    nop
    jr      ra
    .end march_write_word_up
######################################################################    
    .globl march_write_word_down
    .ent march_write_word_down
# DWa : down sequence, write word (32bits)
# a0: start address
# a1: stop address
# a2: data pattern

march_write_word_down:
    ## get start address
    addiu   t4, a1, 0

CoreLoop1:
    addiu   t4, t4, -4
    sw      a2, 0(t4)
    bne     t4, a0, CoreLoop1
    nop
    jr      ra
    .end march_write_word_down
######################################################################    
    .globl march_read_word_up
    .ent march_read_word_up
# URa : up sequence, read word (32bits)
# a0: start address
# a1: stop address
# a2: data pattern
# a3: compare mask
# v0: return results

march_read_word_up:
    ## get start address
    addiu   t4, a0, 0x0
    li      v0, 0

CoreLoop2:
    lw      t0, 0(t4)
    nop
    xor     t3, a2, t0
    and     t3, a3, t3
    beqz    t3, check_loop  
    nop
    addiu   v0, v0, 0x1
check_loop:
    addiu   t4, t4, 0x4
    bne     t4, a1, CoreLoop2
    nop
    jr      ra
    nop
    .end march_read_word_up
######################################################################    
    .globl march_read_word_down
    .ent march_read_word_down
# DRa : down sequence, read word (32bits)
# a0: start address
# a1: stop address
# a2: data pattern
# a3: compare mask
# v0: return results

march_read_word_down:
    ## get start address
    addiu   t4, a1, 0
    li      v0, 0   

CoreLoop3:
    addiu   t4, t4, -4
    lw      t0, 0(t4)
    nop
    xor     t3, a2, t0
    and     t3, a3, t3
    beqz    t3, check_loop2  
    nop
    addiu   v0, v0, 0x1
check_loop2:
    bne     t4, a0, CoreLoop3
    nop
    jr      ra
    .end march_read_word_down
######################################################################    
    .globl march_row_write_word_up
    .ent march_row_write_word_up
# UWa : up sequence, write word (32bits)
# a0: start address;  a1: stop address
# a2: data pattern
# a3: compare mask
# a4: strip size

march_row_write_word_up:
    ## get start address
    addiu   t0, a0, 0x4000
CoreLoop5:
    addiu   t4, a0, 0x0

CoreLoop4:
    sw      a2, 0(t4)
    addiu   t4, t4, 0x4000
    bne     t4, a1, CoreLoop4
    nop
    addiu   a0, a0, 0x4
    addiu   a1, a1, 0x4
    bne     a0, t0, CoreLoop5 
    nop
    jr      ra
    .end march_row_write_word_up
######################################################################    
#    li      t3, 0xffffffff
#    li      t2, 0x0
#    li      t0, 0x0
#
#    #>(w0)
#    addiu   t4, t5, 0x0
#E0_loop:
#    sw      t2, 0(t4)
#    addiu   t4, t4, 0x4
#    bne     t4, t6, E0_loop
#    nop
#    addiu   t0, t0, 0x1
#    
#    #>(r0, w1)
#
#passE0:    
#    ori     a0, zero, 0xE0
#    pass_seg   
#
#    addiu   t4, t5, 0x0    
#E1_loop:
#    lw      t1, 0(t4)
#    sw      t3, 0(t4)
#    bne     t1, t2, asm_fail
#    addiu   t4, t4, 0x4
#    bne     t4, t6, E1_loop
#    nop
#    addiu   t0, t0, 0x1
#
#    #>(r1, w0)
#passE1:    
#    ori     a0, zero, 0xE1
#    pass_seg   
#
#    
#    addiu   t4, t5, 0x0
#E2_loop:
#    lw      t1, 0(t4)
#    sw      t2, 0(t4)
#    bne     t1, t3, asm_fail
#    addiu   t4, t4, 0x4
#    bne     t4, t6, E2_loop
#    nop
#    addiu   t0, t0, 0x1
#
#    #<(r0, w1)
#passE2:    
#    ori     a0, zero, 0xE2
#    pass_seg 
#    
#    
#    addiu   t4, t6, 0x0
#    addiu   t4, t4, -4
#E3_loop:
#    lw      t1, 0(t4)
#    sw      t3, 0(t4)
#    or      a0, t4, zero              # print error addr 
#    or      a1, t1, zero              # print error data
#    bne     t1, t2, asm_fail  
#    addiu   t4, t4, -4
#    bne     t4, t5, E3_loop
#    nop
#    addiu   t0, t0, 0x1
#
#    #<(r1, w0)
#passE3:    
#    ori     a0, zero, 0xE3
#    pass_seg 
#
#    
#    addiu   t4, t6, 0x0
#    addiu   t4, t4, -4
#E4_loop:
#    lw      t1,  0(t4)
#    sw      t2, 0(t4)
#    bne     t1, t3, asm_fail
#    addiu   t4, t4, -4
#    bne     t4, t5, E4_loop
#    nop
#    addiu   t0, t0, 0x1
#
#    #>(r0)
#passE4:    
#    ori     a0, zero, 0xE4
#    pass_seg 
#    
#    addiu   t4, t6, 0x0
#    addiu   t4, t4, -4
#E5_loop:
#    lw      t1,  0(t4)
#    addiu   t4, t4, -4
#    bne     t1, t2, asm_fail
#    nop
#    bne     t4, t5, E5_loop
#    nop
#    addiu   t0, t0, 0x1
# 
#passE5:    
#    ori     a0, zero, 0xE5
#    pass_seg 
#
#######################################################################
#
## Program falls through to here if it passed 
## Else it already jumped to the fail label.
##	.globl	pass
##	pass:
##  b  common
##  ori v0, $0, 0xabcd
##	.globl	fail
##	fail:
## ori v0, $0, 0xdead
#common:
#    jal     pass_uart
#    nop
#    EPILOGUE
#
#asm_fail:
#    jal     fail_uart
#    nop
#    EPILOGUE
#
#  .end mem_test_asm
######################################################################    
    .globl march_write_byte_up
    .ent march_write_byte_up
# UWa : up sequence, write byte (8bits)
# a0: start address
# a1: stop address
# a2: data pattern

march_write_byte_up:
    ## get start address
    addiu   t4, a0, 0x0
    addiu   t5, a2, 0x0
    addiu   t6, a2, 0x0
    addiu   t7, a2, 0x0
    srl     t5, t5, 0x8
    srl     t6, t6, 0x10
    srl     t7, t7, 0x18

CoreLoop6:
    sb      a2, 0(t4)
    sb      t5, 1(t4)
    sb      t6, 2(t4)
    sb      t7, 3(t4)
    addiu   t4, t4, 0x4
    bne     t4, a1, CoreLoop6
    nop
    jr      ra
    .end march_write_byte_up
######################################################################    
    .globl march_read_byte_up
    .ent march_read_byte_up
# URa : up sequence, read byte (8bits)
# a0: start address
# a1: stop address
# a2: data pattern
# a3: compare mask
# v0: return results

march_read_byte_up:
    ## get start address
    addiu   t4, a0, 0x0
    li      v0, 0

CoreLoop7:
    lw      t0, 0(t4)
    nop
    xor     t3, a2, t0
    and     t3, a3, t3
    beqz    t3, check_loop7  
    nop
    addiu   v0, v0, 0x1
check_loop7:
    addiu   t4, t4, 0x4
    bne     t4, a1, CoreLoop7
    nop
    jr      ra
    nop
    .end march_read_byte_up
