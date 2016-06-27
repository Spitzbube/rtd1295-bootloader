/****************************************************************************************
* Direct Test Name:      bu_ae_check_more
* Author:         R2161
* Date:           Fri May 11 10:01:01 CST 2007
* Description:	
* Copyright (C) 2007 Realtek Inc. All Right Reserved.
****************************************************************************************/
	
#include "mars.h"
	.set noreorder
	.set at
	.text
	.globl test
	.ent test

# Start of user-defined macros
# (fill in your marcos here)
# End of user-defined macros

test:

# write register SYS_MUXPAD1 
   lw t0, 0xb8000364
   and t0,0xfffffff3
   sw t0, 0xb8000364
# write register MIS_GP1DIR 
   li t0, 0x00000001
   sw t0, 0xb801B104
# write register MIS_GP1DATO
   li t0, 0x00000001
   sw t0, 0xb801B114


AEE_SEARCH_START:
##Below is add by scripts automatic## APP_ID=20050002
# write register ADSP_AEE_INT
li t0, 0x0000000e
sw t0, ADSP_AEE_INT_reg
## end ##
##Below is add by scripts automatic## APP_ID=20050003
# write register ADSP_AEE_THLD
li t0, 0x00000080|0x20000
sw t0, ADSP_AEE_THLD_reg
## end ##
# write register ADSP_AEE_CTRL 
   li t0, 0x00000018
   sw t0, 0xb8002084 
# write register ADSP_AEE_CTRL 
   li t0, 0x00000010
   sw t0, 0xb8002084 
# write register ADSP_AEE_INT_EN 
   li t0, 0x0000001E
   sw t0, 0xb800208c
# write register ADSP_AEE_RING_LIMIT 
   la t0, ring_limit
   sw t0, 0xb8002094
# write register ADSP_AEE_RING_BASE 
   la t0, ring_base
   sw t0, 0xb8002098
# write register ADSP_AEE_HUFFMODE 
#   li t0, 0x00000000
#   sw t0, 0xb80020a8
# write register ADSP_AEE_CRC_INIT 
   li t0, 0x0ba5c1de
   sw t0, 0xb80020ac
# write register ADSP_AEE_CRC_CNTL 
   li t0, 0x00000030
   sw t0, 0xb80020b0
# write register ADSP_AEE_CRC_CNTL 
   li t0, 0x00000020
   sw t0, 0xb80020b0
# write register ADSP_AEE_CRC_LENGTH 
   li t0, 0x00000000
   sw t0, 0xb80020b4
# write register ADSP_AEE_CRC_CNTL 
   li t0, 0x00000003
   sw t0, 0xb80020b0
# write register ADSP_AEE_SEARCH_LIMIT 
   li t0, 0x00002000
   sw t0, 0xb80020c8
# write register ADSP_AEE_VBIT_CNT 
   li t0, 0x00000000
   sw t0, 0xb800207c
# write register ADSP_AEE_USED_CNT 
   li t0, 0x00000000
   sw t0, 0xb8002080 
# write register ADSP_AEE_RING_RP 
   la t0, ring_rp+1
   sw t0, 0xb800209c
# write register ADSP_AEE_RING_WP 
   la t0, ring_wp
   sw t0, 0xb80020a0
# write register ADSP_AEE_RING_CP 
   la t0, ring_rp+1
   sw t0, 0xb80020a4
# write register ADSP_AEE_CTRL 
   li t0, 0x00000045
   sw t0, 0xb8002084 
# Read until go bit==1
1: lw t0, 0xb8002084 # aee_ctrl=>0xb8002084 
   nop
   and t0,0x00000001 
   beqz t0, 1b
   nop
   li t2, 0x29c7c76b
   nop
   nop
	asearchbits t7, t2
	nop
   nop
   nop
   li a0, 0x00000a93
   bne t7, a0, DIAG_FAIL
   nop
   li t2, 0x2f36e2d3
   nop
   nop
	asearchbits t7, t2
	nop
   nop
   nop
   li a0, 0x000018ab
   bne t7, a0, DIAG_FAIL
   nop
   li t3, 0xbc07c3d5
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x00001835
   bne t8, a0, DIAG_FAIL
   nop
   li t3, 0xa57b11ca
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x000008d2
   bne t8, a0, DIAG_FAIL
   nop
   li t1, 0x00000013
   li t4, 0x3ac92c02
   nop
	apeekbits t6, t1
	nop
   nop
   nop
	asearchbits t9, t4
	nop
   li a0, 0x0001de7b
   bne t6, a0, DIAG_FAIL
   nop
   li a0, 0x00000002
   bne t9, a0, DIAG_FAIL
   nop
   li t2, 0x0000001c
   li t3, 0x00000007
   nop
   nop
	apeekbits t7, t2
	nop
	agetbits t8, t3
	nop
   nop
   li a0, 0x0ef3db5c
   bne t7, a0, DIAG_FAIL
   nop
   li a0, 0x00000077
   bne t8, a0, DIAG_FAIL
   nop
   li t1, 0xd79beac6
   nop
	asearchbits t6, t1
	nop
   nop
   nop
   nop
   li a0, 0x00000026
   bne t6, a0, DIAG_FAIL
   nop
   li t1, 0x65db28ce
   li t4, 0x00000012
   nop
	asearchbits t6, t1
	nop
   nop
   nop
	agetbits t9, t4
	nop
   li a0, 0x00001b86
   bne t6, a0, DIAG_FAIL
   nop
   li a0, 0x00034b6f
   bne t9, a0, DIAG_FAIL
   nop
   li t2, 0xe9275b26
   nop
   nop
	asearchbits t7, t2
	nop
   nop
   nop
   li a0, 0x000000c6
   bne t7, a0, DIAG_FAIL
   nop
   li t3, 0x8ec4a878
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x00001da8
   bne t8, a0, DIAG_FAIL
   nop
   li t3, 0xdca63302
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x0000000a
   bne t8, a0, DIAG_FAIL
   nop
   li t3, 0xa6bd6513
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x00001b1b
   bne t8, a0, DIAG_FAIL
   nop
   li t4, 0x23bb3062
   nop
   nop
   nop
   nop
	asearchbits t9, t4
	nop
   li a0, 0x0000000a
   bne t9, a0, DIAG_FAIL
   nop
   li t4, 0x8a6ea685
   nop
   nop
   nop
   nop
	asearchbits t9, t4
	nop
   li a0, 0x000000dd
   bne t9, a0, DIAG_FAIL
   nop
   li t4, 0x4d4069ea
   nop
   nop
   nop
   nop
	asearchbits t9, t4
	nop
   li a0, 0x000006a2
   bne t9, a0, DIAG_FAIL
   nop
   li t2, 0x00000006
   li t3, 0x0000000f
   nop
   nop
	apeekbits t7, t2
	nop
	agetbits t8, t3
	nop
   nop
   li a0, 0x0000002d
   bne t7, a0, DIAG_FAIL
   nop
   li a0, 0x00005b0d
   bne t8, a0, DIAG_FAIL
   nop
   li t1, 0x34ef096c
   li t4, 0x00000015
   nop
	asearchbits t6, t1
	nop
   nop
   nop
	apeekbits t9, t4
	nop
   li a0, 0x800016b8
   bne t6, a0, DIAG_FAIL
   nop
   li a0, 0x80000000
   bne t9, a0, DIAG_FAIL
   nop
   li t0, 0x00000007
   li t3, 0x379b663b
	apeekbits t5, t0
	nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x80000000
   bne t5, a0, DIAG_FAIL
   nop
   li a0, 0x80000000
   bne t8, a0, DIAG_FAIL
   nop
   li t3, 0x937e2945
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x80000000
   bne t8, a0, DIAG_FAIL
   nop
   li t3, 0xfb5684c3
   nop
   nop
   nop
	asearchbits t8, t3
	nop
   nop
   li a0, 0x80000000
   bne t8, a0, DIAG_FAIL
   nop
   nop
   nop
   nop
   nop
# write register ADSP_AEE_CTRL 
   li t0, 0x00000018
   sw t0, 0xb8002084 
# write register ADSP_AEE_CRC_CNTL 
   li t0, 0x00000002
   sw t0, 0xb80020b0
# READ register ADSP_AEE_USED_CNT and compare
	lw t0, 0xb8002080 
	nop
   li t1, 0x0000b7ef
   bne t0, t1, DIAG_FAIL
   nop
# READ register ADSP_AEE_CRC_RESULT and compare
	lw t0, 0xb80020b8 
	nop
   li t1, 0x00006e83
   bne t0, t1, DIAG_FAIL
   nop
##Below is add by scripts automatic## APP_ID=20050001
# write register ADSP_AEE_INT
li t0, 0x0000000e
sw t0, ADSP_AEE_INT_reg

AEE_SEARCH_END:


AEE_GETI_START:
/* encode 1 decode 0 */
#define direction 0 

/*THLD CTRL*/
        li       t0,ADSP_AEE_THLD_max_xfer(0x10)|ADSP_AEE_THLD_threshold(0x10)
        sw	t0,ADSP_AEE_THLD_reg
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(0)|ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg

/*RING BUFFER */
	
	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_BASE_reg

	la	t0,ddr_data_limit
	sw	t0,ADSP_AEE_RING_LIMIT_reg

	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_RP_reg

	la	t0,ddr_data_limit
	sw	t0,ADSP_AEE_RING_WP_reg

	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_CP_reg

/*USED CNT*/

	REG_WR(ADSP_AEE_USED_CNT_reg,t1,0x0,t0)

/*VBIT CNT*/

	REG_WR(ADSP_AEE_VBIT_CNT_reg,t1,0x0,t0)

/*CRC SETTING*/
	/* CRC:0000/FFFF PARITY:0000*/
	REG_WR(ADSP_AEE_CRC_INIT_reg,t1,0xFFFF,t0)
	
	/* Length unit - bit*/
	REG_WR(ADSP_AEE_CRC_LENGTH_reg,t1,0x0020,t0)

/*CRC CONTROL reset, crc or parity, cont or not*/
	li 	t0,ADSP_AEE_CRC_CNTL_write_en4(1)|ADSP_AEE_CRC_CNTL_crc_mode(0) | ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(1) | ADSP_AEE_CRC_CNTL_write_en2(1) | ADSP_AEE_CRC_CNTL_crc_cont(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (0)

	sw	t0,ADSP_AEE_CRC_CNTL_reg
	
/*CRC CONTROL clean reset, crc_on*/
	li	t0,ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (1)
	sw	t0,ADSP_AEE_CRC_CNTL_reg
	WAIT(ADSP_AEE_CRC_CNTL_reg,0x1,0x1,t0,t1)

/*OGG_MODE*/
	REG_WR(AEE_OGG_MODE_reg,t1,0x0000,t0)

/*SEARCH_LIMIT*/
	REG_WR(ADSP_AEE_SEARCH_LIMIT_reg,t1,0x20,t0)

/*INTERRUPT*/
	REG_WR(ADSP_AEE_INT_EN_reg,t1,0xf,t0)

/*WAIT GO bit*/
	li	t0,ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction)|ADSP_AEE_CTRL_go(1)
	sw	t0,ADSP_AEE_CTRL_reg
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x1,t0,t1)#go == 1

/*======End of Register setting======*/
	li	t1,0x02000008
SETI1:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x2
GETI1:
	agetbitsi t1, 0x01
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI2
	nop
	b	  GETI1
	nop

SETI2:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x4
GETI2:
	agetbitsi t1, 0x02
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI3
	nop
	b	  GETI2
	nop

SETI3:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x8
GETI3:
	agetbitsi t1, 0x03
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI4
	nop
	b	  GETI3
	nop

SETI4:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x10
GETI4:
	agetbitsi t1, 0x04
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI5
	nop
	b	  GETI4
	nop

SETI5:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x20
GETI5:
	agetbitsi t1, 0x05
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI6
	nop
	b	  GETI5
	nop

SETI6:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x40
GETI6:
	agetbitsi t1, 0x06
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI7
	nop
	b	  GETI6
	nop

SETI7:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x80
GETI7:
	agetbitsi t1, 0x07
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI8
	nop
	b	  GETI7
	nop

SETI8:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x100
GETI8:
	agetbitsi t1, 0x08
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI9
	nop
	b	  GETI8
	nop

SETI9:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x200
GETI9:
	agetbitsi t1, 0x09
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI10
	nop
	b	  GETI9
	nop

SETI10:
	li	t5,0x0
	li	t6,0x1
	li	t7,0x400
GETI10:
	agetbitsi t1, 0x0a
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SETI_A5A5
	nop
	b	  GETI10
	nop

SETI_A5A5:
	li	t5,0x25a5a5a5
GETI_A5A5:
	agetbitsi t1, 0x1f
	nop
	bne	  t1, t5, DIAG_FAIL
	nop

SETI_5A5A:
	li	t5,0x5a5a5a5a
GETI_5A5A:
	agetbitsi t1, 0x1f
	nop
	bne	  t1, t5, DIAG_FAIL
	nop

AEE_GETI_END:



AEE_GET_START:
/* encode 1 decode 0 */
#define direction 0 

/*THLD CTRL*/
        li       t0,ADSP_AEE_THLD_max_xfer(0x10)|ADSP_AEE_THLD_threshold(0x10)
        sw	t0,ADSP_AEE_THLD_reg
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(0)|ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg

/*RING BUFFER */
	
	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_BASE_reg

	la	t0,ddr_data_limit
	sw	t0,ADSP_AEE_RING_LIMIT_reg

	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_RP_reg

	la	t0,ddr_data_limit
	sw	t0,ADSP_AEE_RING_WP_reg

	la	t0,ddr_data_base
	sw	t0,ADSP_AEE_RING_CP_reg

/*USED CNT*/

	REG_WR(ADSP_AEE_USED_CNT_reg,t1,0x0,t0)

/*VBIT CNT*/

	REG_WR(ADSP_AEE_VBIT_CNT_reg,t1,0x0,t0)

/*CRC SETTING*/
	/* CRC:0000/FFFF PARITY:0000*/
	REG_WR(ADSP_AEE_CRC_INIT_reg,t1,0xFFFF,t0)
	
	/* Length unit - bit*/
	REG_WR(ADSP_AEE_CRC_LENGTH_reg,t1,0x0020,t0)

/*CRC CONTROL reset, crc or parity, cont or not*/
	li 	t0,ADSP_AEE_CRC_CNTL_write_en4(1)|ADSP_AEE_CRC_CNTL_crc_mode(0) | ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(1) | ADSP_AEE_CRC_CNTL_write_en2(1) | ADSP_AEE_CRC_CNTL_crc_cont(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (0)

	sw	t0,ADSP_AEE_CRC_CNTL_reg
	
/*CRC CONTROL clean reset, crc_on*/
	li	t0,ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (1)
	sw	t0,ADSP_AEE_CRC_CNTL_reg
	WAIT(ADSP_AEE_CRC_CNTL_reg,0x1,0x1,t0,t1)

/*OGG_MODE*/
	REG_WR(AEE_OGG_MODE_reg,t1,0x0000,t0)

/*SEARCH_LIMIT*/
	REG_WR(ADSP_AEE_SEARCH_LIMIT_reg,t1,0x20,t0)

/*INTERRUPT*/
	REG_WR(ADSP_AEE_INT_EN_reg,t1,0xf,t0)

/*WAIT GO bit*/
	li	t0,ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction)|ADSP_AEE_CTRL_go(1)
	sw	t0,ADSP_AEE_CTRL_reg
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x1,t0,t1)#go == 1

/*======End of Register setting======*/
	li	t1,0x02000008
SET1:
	li	t4,0x1
	li	t5,0x0
	li	t6,0x1
	li	t7,0x2
GET1:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET2
	nop
	b	  GET1
	nop

SET2:
	li	t4,0x2
	li	t5,0x0
	li	t6,0x1
	li	t7,0x4
GET2:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET3
	nop
	b	  GET2
	nop

SET3:
	li	t4,0x3
	li	t5,0x0
	li	t6,0x1
	li	t7,0x8
GET3:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET4
	nop
	b	  GET3
	nop

SET4:
	li	t4,0x4
	li	t5,0x0
	li	t6,0x1
	li	t7,0x10
GET4:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET5
	nop
	b	  GET4
	nop

SET5:
	li	t4,0x5
	li	t5,0x0
	li	t6,0x1
	li	t7,0x20
GET5:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET6
	nop
	b	  GET5
	nop

SET6:
	li	t4,0x6
	li	t5,0x0
	li	t6,0x1
	li	t7,0x40
GET6:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET7
	nop
	b	  GET6
	nop

SET7:
	li	t4,0x7
	li	t5,0x0
	li	t6,0x1
	li	t7,0x80
GET7:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET8
	nop
	b	  GET7
	nop

SET8:
	li	t4,0x8
	li	t5,0x0
	li	t6,0x1
	li	t7,0x100
GET8:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET9
	nop
	b	  GET8
	nop

SET9:
	li	t4,0x9
	li	t5,0x0
	li	t6,0x1
	li	t7,0x200
GET9:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET10
	nop
	b	  GET9
	nop

SET10:
	li	t4,0xa
	li	t5,0x0
	li	t6,0x1
	li	t7,0x400
GET10:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop
	add	  t5, t5, t6
	nop
	beq	  t5, t7, SET_A5A5
	nop
	b	  GET10
	nop

SET_A5A5:
	li	t4,0x1f
	li	t5,0x25a5a5a5
GET_A5A5:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop

SET_5A5A:
	li	t4,0x1f
	li	t5,0x5a5a5a5a
GET_5A5A:
	agetbits  t1, t4
	nop
	bne	  t1, t5, DIAG_FAIL
	nop

AEE_GET_END:


	# add ddr register for ddr phy , test clock is 40ns, delay is 10ns
	la 	t7, 0xb8008c00 
	li	t6, 0x505 
	sw	t6, (t7)
	
	la 	t7, 0xb8008c04 
	li	t6, 0x505   
	sw	t6, (t7)


SRC_START:
	# user test follows	
	// SRC start
	la 	t7, 0xb8002100 
	la	t6, ddr_data_5a5aa5a5_base
	sw	t6, (t7)

	la 	t7, 0xb8002104 
	la	t6, ddr_data_5a5aa5a5_1f8+4
	sw	t6, (t7)

	la 	t7, 0xb8002108 
	la	t6, ddr_data_5a5aa5a5_base
	sw	t6, (t7)

	la 	t7, 0xb800210c 
	la	t6, ddr_data_dst_base
	sw	t6, (t7)

	la 	t7, 0xb8002110 
	la	t6, ddr_data_dst_base
	sw	t6, (t7)

	la 	t7, 0xb8002114 
	la	t6, ddr_data_dst_base+8
	sw	t6, (t7)

	la 	t7, 0xb800212c 
	li	t6, 0x7f   //src threshold
	sw	t6, (t7)

	la 	t7, 0xb8002118 
	li	t6, 0x9e9222a1   //src ctrl1
	sw	t6, (t7)

SRC_LOAD_COEF:
	// load coef
	la 	t7, 0xb8002134 
	la	t6, filter2_127t_05x_start
	sw	t6, (t7)

	la 	t7, 0xb8002138 
	li	t6, 0x1     //load coef
	sw	t6, (t7)
	
	CPU_TRACE_COMPARE_OFF
	WAIT(0xb8002138,0x00,0x00,t1,t2)
	DELAY(10,t8)
	CPU_TRACE_COMPARE_ON

SRC_GO:	
	// src go
	la 	t7, 0xb800211c 
	li	t6, 0x3   //src ctrl2, go bit
	sw	t6, (t7)
	CPU_TRACE_COMPARE_OFF
	WAIT(0xb8002124,0x40,0x40,t1,t2) // wait src done
	CPU_TRACE_COMPARE_ON

SRC_COMPARE:
	// compare DRAM result
	la  t0, ddr_data_dst_base
	or  t0, 0xa0000000
	lw  t1, (t0)
	nop
	// fail condition
	li	t0,AE_DUMMY_dummy(1)
	sw	t0,AE_DUMMY_reg


	bne t1, 0x005aa5a4, DIAG_FAIL
	nop


ADE_START:
	// ade start
   li t1, 0x10000000
   li t0, 0x10007fff

   nop
   nop
   mtc3 t1,$4
   nop
   mtc3 t0,$5
   nop

  li r2,  0xbeef0002 
  li r3,  0xbeef0003 
  li r4,  0xbeef0004 
  li r5,  0xbeef0005 
  li r6,  0xbeef0006 
  li r7,  0xbeef0007 
  li r8,  0xbeef0008 
  li r9,  0xbeef0009 
  li r10, 0xbeef000a 
  li r11, 0xbeef000b 
  li r12, 0xbeef000c 
  li r13, 0xbeef000d 
  li r14, 0xbeef000e 
  li r15, 0xbeef000f 
  li r16, 0xbeef0010 
  li r17, 0xbeef0011 
  li r18, 0xbeef0012 
  li r19, 0xbeef0013 
  li r20, 0xbeef0014 
  li r21, 0xbeef0015 
  li r22, 0xbeef0016 
  li r23, 0xbeef0017 
  li r24, 0xbeef0018 
  li r25, 0xbeef0019 
# **** program register round 0 ****

li t0, ADSP_ADE_CNTL_write_en1(1) | ADSP_ADE_CNTL_max_xfer(20) | ADSP_ADE_CNTL_write_en4(1) | ADSP_ADE_CNTL_stop(0) | ADSP_ADE_CNTL_write_en5(1) | ADSP_ADE_CNTL_go(0)	
       #li t0, 0x00027823 
       sw t0, ADSP_ADE_CNTL_reg
       #lw t5,0xaffffd78
       nop
//================================================    
//setting of ade entries
//================================================    
    # write register AEE_ADE_SRC[0]
       la t0, ddr_data_5a5a_base
       sw t0, 0xb8002000 
    # write register AEE_ADE_DST[0]
       li t0, 0x10000038 
       sw t0, 0xb8002020 
    # write register AEE_ADE_SIZE[0]
       li t0, ADSP_ADE_SIZE_valid(1) | ADSP_ADE_SIZE_dir(0) | ADSP_ADE_SIZE_size(256)
       #li t0, (0x400<<3)|(0x0<<14)|(0x1<<15)  # size, dir, valid 
       sw t0, ADSP_ADE_SIZE_0_reg
CPU_TRACE_COMPARE_OFF
WAIT(ADSP_ADE_STATUS_reg,0xFF,0xFF,t1,t2)
CPU_TRACE_COMPARE_ON

ADE_DMEM_CHK:
	// DMEM check
	la  t0, 0xb0000038 
	lw  t1, (t0)
	nop
	// fail condition
	li	t0,AE_DUMMY_dummy(2)
	sw	t0,AE_DUMMY_reg


	bne t1, 0x5a5a5a5a, DIAG_FAIL
	nop


	// ade write data to dram
	li t0, 0x10000038 
       sw t0,  ADSP_ADE_SRC_1_reg
       
       la t0, ddr_data_5a5a_base
       sw t0, ADSP_ADE_DST_1_reg 
       
       li t0, ADSP_ADE_SIZE_valid(1) | ADSP_ADE_SIZE_dir(1) | ADSP_ADE_SIZE_size(8) //ADSP_ADE_SIZE_size(200)
       sw t0, ADSP_ADE_SIZE_1_reg
CPU_TRACE_COMPARE_OFF
WAIT(ADSP_ADE_STATUS_reg,0xFF,0xFF,t1,t2)
CPU_TRACE_COMPARE_ON

ADE_DRAM_CHK:
	// DRAM check
	la  t0, ddr_data_5a5a_base
	or  t0, 0xa0000000
	lw  t1, (t0)
	nop
	// fail condition
	li	t0,AE_DUMMY_dummy(3)
	sw	t0,AE_DUMMY_reg


	bne t1, 0x5a5a5a5a, DIAG_FAIL
	nop


ADE_START_2:
	// ade start
   li t1, 0x10000000
   li t0, 0x10007fff

   nop
   nop
   mtc3 t1,$4
   nop
   mtc3 t0,$5
   nop

  li r2,  0xbeef0002 
  li r3,  0xbeef0003 
  li r4,  0xbeef0004 
  li r5,  0xbeef0005 
  li r6,  0xbeef0006 
  li r7,  0xbeef0007 
  li r8,  0xbeef0008 
  li r9,  0xbeef0009 
  li r10, 0xbeef000a 
  li r11, 0xbeef000b 
  li r12, 0xbeef000c 
  li r13, 0xbeef000d 
  li r14, 0xbeef000e 
  li r15, 0xbeef000f 
  li r16, 0xbeef0010 
  li r17, 0xbeef0011 
  li r18, 0xbeef0012 
  li r19, 0xbeef0013 
  li r20, 0xbeef0014 
  li r21, 0xbeef0015 
  li r22, 0xbeef0016 
  li r23, 0xbeef0017 
  li r24, 0xbeef0018 
  li r25, 0xbeef0019 
# **** program register round 0 ****

li t0, ADSP_ADE_CNTL_write_en1(1) | ADSP_ADE_CNTL_max_xfer(20) | ADSP_ADE_CNTL_write_en4(1) | ADSP_ADE_CNTL_stop(0) | ADSP_ADE_CNTL_write_en5(1) | ADSP_ADE_CNTL_go(0)	
       #li t0, 0x00027823 
       sw t0, ADSP_ADE_CNTL_reg
       #lw t5,0xaffffd78
       nop
//================================================    
//setting of ade entries
//================================================    
    # write register AEE_ADE_SRC[0]
       la t0, ddr_data_a5a5_base
       sw t0, 0xb8002000 
    # write register AEE_ADE_DST[0]
       li t0, 0x10000038 
       sw t0, 0xb8002020 
    # write register AEE_ADE_SIZE[0]
       li t0, ADSP_ADE_SIZE_valid(1) | ADSP_ADE_SIZE_dir(0) | ADSP_ADE_SIZE_size(256)
       #li t0, (0x400<<3)|(0x0<<14)|(0x1<<15)  # size, dir, valid 
       sw t0, ADSP_ADE_SIZE_0_reg
CPU_TRACE_COMPARE_OFF
WAIT(ADSP_ADE_STATUS_reg,0xFF,0xFF,t1,t2)
CPU_TRACE_COMPARE_ON

ADE_DMEM_CHK_2:
	// DMEM check
	la  t0, 0xb0000038
	lw  t1, (t0)
	nop
	// fail condition
	li	t0,AE_DUMMY_dummy(2)
	sw	t0,AE_DUMMY_reg


	bne t1, 0xa5a5a5a5, DIAG_FAIL
	nop


	// ade write data to dram
	li t0, 0x10000038 
       sw t0,  ADSP_ADE_SRC_1_reg
       
       la t0, ddr_data_a5a5_base
       sw t0, ADSP_ADE_DST_1_reg 
       
       li t0, ADSP_ADE_SIZE_valid(1) | ADSP_ADE_SIZE_dir(1) | ADSP_ADE_SIZE_size(8) //ADSP_ADE_SIZE_size(200)
       sw t0, ADSP_ADE_SIZE_1_reg
CPU_TRACE_COMPARE_OFF
WAIT(ADSP_ADE_STATUS_reg,0xFF,0xFF,t1,t2)
CPU_TRACE_COMPARE_ON

ADE_DRAM_CHK_2:
	// DRAM check
	la  t0, ddr_data_a5a5_base
	or  t0, 0xa0000000
	lw  t1, (t0)
	nop
	// fail condition
	li	t0,AE_DUMMY_dummy(3)
	sw	t0,AE_DUMMY_reg


	bne t1, 0xa5a5a5a5, DIAG_FAIL
	nop



AEE_PUTI_START:
/* encode 1 decode 0 */
#define direction1 1 

THLD_CTRL_I:
        li       t0,ADSP_AEE_THLD_max_xfer(0x2)|ADSP_AEE_THLD_threshold(0x2)
        sw	t0,ADSP_AEE_THLD_reg
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(0)|ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg

RING_BUFFER_I:

	la	t0,ddr_data_dst_base
	sw	t0,ADSP_AEE_RING_BASE_reg

	la	t0,ddr_data_dst_base+0x100
	sw	t0,ADSP_AEE_RING_LIMIT_reg

	la	t0,ddr_data_dst_base+0x10
	sw	t0,ADSP_AEE_RING_RP_reg

	la	t0,ddr_data_dst_base+0x5f
	sw	t0,ADSP_AEE_RING_WP_reg

	la	t0,ddr_data_dst_base+0x60
	sw	t0,ADSP_AEE_RING_CP_reg


USED_CNT_I:

	REG_WR(ADSP_AEE_USED_CNT_reg,t1,0x0,t0)

VBIT_CNT_I:

	REG_WR(ADSP_AEE_VBIT_CNT_reg,t1,0x0,t0)

CRC_SETTING_I:
	/* CRC:0000/FFFF PARITY:0000*/
	REG_WR(ADSP_AEE_CRC_INIT_reg,t1,0xffff,t0)
	
	/* Length unit - bit*/
	REG_WR(ADSP_AEE_CRC_LENGTH_reg,t1,0x10,t0)

/*CRC CONTROL reset, crc or parity, cont or not*/
	li 	t0,ADSP_AEE_CRC_CNTL_write_en4(1)|ADSP_AEE_CRC_CNTL_crc_mode(0) | ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(1) | ADSP_AEE_CRC_CNTL_write_en2(1) | ADSP_AEE_CRC_CNTL_crc_cont(1) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (0) #crc_reset1 

	sw	t0,ADSP_AEE_CRC_CNTL_reg
	
/*CRC CONTROL clean reset, crc_on*/
	li	t0,ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (1)#crc_setting1
	sw	t0,ADSP_AEE_CRC_CNTL_reg
	WAIT(ADSP_AEE_CRC_CNTL_reg,0x1,0x1,t0,t1)

OGG_MODE_I:
	REG_WR(AEE_OGG_MODE_reg,t1,0x0000,t0)

SEARCH_LIMIT_I:
	REG_WR(ADSP_AEE_SEARCH_LIMIT_reg,t1,0x20,t0)

INTERRUPT_I: /*turn off*/
	#REG_WR(ADSP_AEE_INT_EN_reg,t1,0xf,t0)

WAIT_GO_I: /*bit*/
	li	t0,ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(1)
	sw	t0,ADSP_AEE_CTRL_reg
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x1,t0,t1)#go == 1

/*======End of Register setting======*/
	li t1,0x5a5a5a5a
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0x5a5a5a5a
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0x5a5a5a5a
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0x5a5a5a5a
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
DRAM_chk1_I:

        # write register MIS_GP1DATO
        li t0, 0x00000000
        sw t0, 0xb801B114 

        // DRAM check
        la  t0, ddr_data_dst_base+0x70 
	or  t0, 0xa0000000
        lw  t1, (t0)
        nop
        // fail condition
        li      t0,AE_DUMMY_dummy(3)
        sw      t0,AE_DUMMY_reg
        
        bne t1, 0x5a5a5a5a, DRAM_chk1_I
        //bne t1, 0x5a5a5a5a, DIAG_FAIL
	nop

        # write register MIS_GP1DATO
        li t0, 0x00000001
        sw t0, 0xb801B114

// round 2
	li t1,0xa5a5a5a5
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xa5a5a5a5
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xa5a5a5a5
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xa5a5a5a5
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop
	li t1,0xdeaddead
	aputbitsi t1,0x20#4bytes
	nop


	apadbits 
	nop
//	aflushbs 
//	nop
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(1)|ADSP_AEE_CTRL_write_en2(0)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg
DRAM_chk2_I:

        # write register MIS_GP1DATO
        li t0, 0x00000000
        sw t0, 0xb801B114 

        // DRAM check
        la  t0, ddr_data_dst_base+0x90 
	or  t0, 0xa0000000
        lw  t1, (t0)
        nop
        // fail condition
        li      t0,AE_DUMMY_dummy(3)
        sw      t0,AE_DUMMY_reg

	bne t1, 0xa5a5a5a5, DRAM_chk2_I
	//bne t1, 0xa5a5a5a5, DIAG_FAIL
	nop

        # write register MIS_GP1DATO
        li t0, 0x00000001
        sw t0, 0xb801B114

/*wait until go == 0, then check registers*/
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x0,t0,t1)
	REG_RD(ADSP_AEE_CRC_ACC_reg,t1,t2)
	REG_RD(ADSP_AEE_CRC_ACC_CNT_reg,t1,t2)
	REG_RD(ADSP_AEE_CRC_RESULT_reg,t1,t2)
	REG_RD(ADSP_AEE_BIT_CNT_reg,t1,t2)

	REG_RD(ADSP_AEE_USED_CNT_reg,t1,t2)
	REG_RD(ADSP_AEE_RING_CP_reg,t1,t2)
AEE_PUTI_END:


AEE_PUT_START:
/* encode 1 decode 0 */
#define direction1 1 

THLD_CTRL:
        li       t0,ADSP_AEE_THLD_max_xfer(0x2)|ADSP_AEE_THLD_threshold(0x2)
        sw	t0,ADSP_AEE_THLD_reg
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(0)|ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg

RING_BUFFER:

	la	t0,ddr_data_dst_base
	sw	t0,ADSP_AEE_RING_BASE_reg

	la	t0,ddr_data_dst_base+0x100
	sw	t0,ADSP_AEE_RING_LIMIT_reg

	la	t0,ddr_data_dst_base+0x10
	sw	t0,ADSP_AEE_RING_RP_reg

	la	t0,ddr_data_dst_base+0x9f
	sw	t0,ADSP_AEE_RING_WP_reg

	la	t0,ddr_data_dst_base+0xa0
	sw	t0,ADSP_AEE_RING_CP_reg


USED_CNT:

	REG_WR(ADSP_AEE_USED_CNT_reg,t1,0x0,t0)

VBIT_CNT:

	REG_WR(ADSP_AEE_VBIT_CNT_reg,t1,0x0,t0)

CRC_SETTING:
	/* CRC:0000/FFFF PARITY:0000*/
	REG_WR(ADSP_AEE_CRC_INIT_reg,t1,0xffff,t0)
	
	/* Length unit - bit*/
	REG_WR(ADSP_AEE_CRC_LENGTH_reg,t1,0x10,t0)

/*CRC CONTROL reset, crc or parity, cont or not*/
	li 	t0,ADSP_AEE_CRC_CNTL_write_en4(1)|ADSP_AEE_CRC_CNTL_crc_mode(0) | ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(1) | ADSP_AEE_CRC_CNTL_write_en2(1) | ADSP_AEE_CRC_CNTL_crc_cont(1) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (0) #crc_reset1 

	sw	t0,ADSP_AEE_CRC_CNTL_reg
	
/*CRC CONTROL clean reset, crc_on*/
	li	t0,ADSP_AEE_CRC_CNTL_write_en1(1) | ADSP_AEE_CRC_CNTL_crc_reset(0) | ADSP_AEE_CRC_CNTL_write_en3(1) | ADSP_AEE_CRC_CNTL_crc_on (1)#crc_setting1
	sw	t0,ADSP_AEE_CRC_CNTL_reg
	WAIT(ADSP_AEE_CRC_CNTL_reg,0x1,0x1,t0,t1)

OGG_MODE:
	REG_WR(AEE_OGG_MODE_reg,t1,0x0000,t0)

SEARCH_LIMIT:
	REG_WR(ADSP_AEE_SEARCH_LIMIT_reg,t1,0x20,t0)

INTERRUPT: /*turn off*/
	#REG_WR(ADSP_AEE_INT_EN_reg,t1,0xf,t0)

WAIT_GO: /*bit*/
	li	t0,ADSP_AEE_CTRL_write_en2(1)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(1)
	sw	t0,ADSP_AEE_CTRL_reg
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x1,t0,t1)#go == 1

/*======End of Register setting======*/
	li t0,0x20
	li t1,0x5a5a5a5a
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0x5a5a5a5a
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0x5a5a5a5a
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0x5a5a5a5a
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop

DRAM_chk1:

        # write register MIS_GP1DATO
        li t0, 0x00000000
        sw t0, 0xb801B114 

        // DRAM check
        la  t0, ddr_data_dst_base+0xb0 
	or  t0, 0xa0000000
        lw  t1, (t0)
        nop
        // fail condition
        li      t0,AE_DUMMY_dummy(3)
        sw      t0,AE_DUMMY_reg
        
        
        bne t1, 0x5a5a5a5a, DRAM_chk1
        //bne t1, 0x5a5a5a5a, DIAG_FAIL
	nop

        # write register MIS_GP1DATO
        li t0, 0x00000001
        sw t0, 0xb801B114 

// round 2
	li t0,0x20
	li t1,0xa5a5a5a5
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xa5a5a5a5
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xa5a5a5a5
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xa5a5a5a5
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop
	li t0,0x20
	li t1,0xdeaddead
	aputbits t0,t1#4bytes
	nop


	apadbits 
	nop
//	aflushbs 
//	nop
	li	t0,ADSP_AEE_CTRL_write_en1(1)|ADSP_AEE_CTRL_stop(1)|ADSP_AEE_CTRL_write_en2(0)|ADSP_AEE_CTRL_dir(direction1)|ADSP_AEE_CTRL_go(0)
	sw	t0,ADSP_AEE_CTRL_reg
DRAM_chk2:

        # write register MIS_GP1DATO
        li t0, 0x00000000
        sw t0, 0xb801B114 

        // DRAM check
        la  t0, ddr_data_dst_base+0xd0
	or  t0, 0xa0000000
        lw  t1, (t0)
        nop
        // fail condition
        li      t0,AE_DUMMY_dummy(3)
        sw      t0,AE_DUMMY_reg

	bne t1, 0xa5a5a5a5, DRAM_chk2
	//bne t1, 0xa5a5a5a5, DIAG_FAIL
	nop

        # write register MIS_GP1DATO
        li t0, 0x00000001
        sw t0, 0xb801B114 

/*wait until go == 0, then check registers*/
	WAIT(ADSP_AEE_CTRL_reg,0x1,0x0,t0,t1)
	REG_RD(ADSP_AEE_CRC_ACC_reg,t1,t2)
	REG_RD(ADSP_AEE_CRC_ACC_CNT_reg,t1,t2)
	REG_RD(ADSP_AEE_CRC_RESULT_reg,t1,t2)
	REG_RD(ADSP_AEE_BIT_CNT_reg,t1,t2)

	REG_RD(ADSP_AEE_USED_CNT_reg,t1,t2)
	REG_RD(ADSP_AEE_RING_CP_reg,t1,t2)
AEE_PUT_END:


	b	DIAG_PASS
	nop
	# End of user-defined test
1:	b	1b
	nop
DIAG_PASS:	
	la	t0,TEST_PASS
	jr	t0
	nop
DIAG_FAIL:

    # write register MIS_GP1DATO
       li t0, 0x00000000
       sw t0, 0xb801B114 

	la	t0,TEST_FAIL
	jr	t0
	nop
.align 5
    nop
	.end test
    .align 3 # bit stream data are 8 byte align
ddr_data_base:
   .dword 0x46c14e5dc048d159
   .dword 0xe26af37bc0110c85
   .dword 0x31d0952d8d73e119
   .dword 0x4e95b5f19d6f9df7
   .dword 0xc00420c41461c824 
   .dword 0xa2cc34e3d04524d4
   .dword 0x5565d865a6dc75e7 
   .dword 0xe08628e49669e8a6
   .dword 0xaaecb6ebf0c72cf4 
   .dword 0xd76df8e7aefcf7ef
   .dword 0xc001040c2050c1c4 
   .dword 0x09142c60d1c3c811
   .dword 0x244ca152c5cc1934 
   .dword 0x6ce1d3c7d021448d
   .dword 0x2254c9d42954ad62 
   .dword 0xd5cbd83164cda356
   .dword 0xcddc3974ede3d7cf 
   .dword 0xe041850e2458d1e4
   .dword 0x49952e64d9d3e851 
   .dword 0xa54ea55ad5ec59b5
   .dword 0x6ee5dbd7f061c58f 
   .dword 0x265cd9f469d5af66
   .dword 0xdddbf871e5cfa75e 
   .dword 0xddfc79f5efe7dfdf
   .dword 0xc0004080c1014181 
   .dword 0xc2024282c3034383
   .dword 0xc4044484c5054585 
   .dword 0xc6064686c7074787
   .dword 0xc8084888c9094989 
   .dword 0xca0a4a8acb0b4b8b
   .dword 0xcc0c4c8ccd0d4d8d 
   .dword 0xce0e4e8ecf0f4f8f
   .dword 0xd0105090d1115191 
   .dword 0xd2125292d3135393
   .dword 0xd4145494d5155595 
   .dword 0xd6165696d7175797
   .dword 0xd8185898d9195999 
   .dword 0xda1a5a9adb1b5b9b
   .dword 0xdc1c5c9cdd1d5d9d 
   .dword 0xde1e5e9edf1f5f9f
   .dword 0xe02060a0e12161a1 
   .dword 0xe22262a2e32363a3
   .dword 0xe42464a4e52565a5 
   .dword 0xe62666a6e72767a7
   .dword 0xe82868a8e92969a9 
   .dword 0xea2a6aaaeb2b6bab
   .dword 0xec2c6caced2d6dad 
   .dword 0xee2e6eaeef2f6faf
   .dword 0xf03070b0f13171b1 
   .dword 0xf23272b2f33373b3
   .dword 0xf43474b4f53575b5 
   .dword 0xf63676b6f73777b7
   .dword 0xf83878b8f93979b9 
   .dword 0xfa3a7abafb3b7bbb
   .dword 0xfc3c7cbcfd3d7dbd 
   .dword 0xfe3e7ebeff3f7fbf
   .dword 0xc00010100c080503 
   .dword 0x01c10090502c180d
   .dword 0x0703c20110904c28 
   .dword 0x150b05c30190d06c
   .dword 0x381d0f07c4021110 
   .dword 0x8c48251309c50291
   .dword 0x50ac582d170bc603 
   .dword 0x1190cc68351b0dc7
   .dword 0x0391d0ec783d1f0f 
   .dword 0xc80412110c884523
   .dword 0x11c90492512c984d 
   .dword 0x2713ca0512914ca8
   .dword 0x552b15cb0592d16c 
   .dword 0xb85d2f17cc061311
   .dword 0x8cc8653319cd0693 
   .dword 0x51acd86d371bce07
   .dword 0x1391cce8753b1dcf 
   .dword 0x0793d1ecf87d3f1f
   .dword 0xd00814120d088543 
   .dword 0x21d10894522d188d
   .dword 0x4723d20914924d28 
   .dword 0x954b25d30994d26d
   .dword 0x389d4f27d40a1512 
   .dword 0x8d48a55329d50a95
   .dword 0x52ad58ad572bd60b 
   .dword 0x1592cd68b55b2dd7
   .dword 0x0b95d2ed78bd5f2f 
   .dword 0xd80c16130d88c563
   .dword 0x31d90c96532d98cd 
   .dword 0x6733da0d16934da8
   .dword 0xd56b35db0d96d36d 
   .dword 0xb8dd6f37dc0e1713
   .dword 0x8dc8e57339dd0e97 
   .dword 0x53add8ed773bde0f
   .dword 0x1793cde8f57b3ddf 
   .dword 0x0f97d3edf8fd7f3f
   .dword 0xe01018140e090583 
   .dword 0x41e11098542e190d
   .dword 0x8743e21118944e29 
   .dword 0x158b45e31198d46e
   .dword 0x391d8f47e4121914 
   .dword 0x8e49259349e51299
   .dword 0x54ae592d974be613 
   .dword 0x1994ce69359b4de7
   .dword 0x1399d4ee793d9f4f 
   .dword 0xe8141a150e8945a3
   .dword 0x51e9149a552e994d 
   .dword 0xa753ea151a954ea9
   .dword 0x55ab55eb159ad56e 
   .dword 0xb95daf57ec161b15
   .dword 0x8ec965b359ed169b 
   .dword 0x55aed96db75bee17
   .dword 0x1b95cee975bb5def 
   .dword 0x179bd5eef97dbf5f
   .dword 0xf0181c160f0985c3 
   .dword 0x61f1189c562f198d
   .dword 0xc763f2191c964f29 
   .dword 0x95cb65f3199cd66f
   .dword 0x399dcf67f41a1d16 
   .dword 0x8f49a5d369f51a9d
   .dword 0x56af59add76bf61b 
   .dword 0x1d96cf69b5db6df7
   .dword 0x1b9dd6ef79bddf6f 
   .dword 0xf81c1e170f89c5e3
   .dword 0x71f91c9e572f99cd 
   .dword 0xe773fa1d1e974fa9
   .dword 0xd5eb75fb1d9ed76f 
   .dword 0xb9ddef77fc1e1f17
   .dword 0x8fc9e5f379fd1e9f 
   .dword 0x57afd9edf77bfe1f
   .dword 0x1f97cfe9f5fb7dff 
   .dword 0x1f9fd7eff9fdff7f
   .dword 0xc000040200c04014 
   .dword 0x0601c080240a02c0
   .dword 0xc0340e03c1004412 
   .dword 0x04c140541605c180
   .dword 0x641a06c1c0741e07 
   .dword 0xc200842208c24094
   .dword 0x2609c280a42a0ac2 
   .dword 0xc0b42e0bc300c432
   .dword 0x0cc340d4360dc380 
   .dword 0xe43a0ec3c0f43e0f
   .dword 0xc401044210c44114 
   .dword 0x4611c481244a12c4
   .dword 0xc1344e13c5014452 
   .dword 0x14c541545615c581
   .dword 0x645a16c5c1745e17 
   .dword 0xc601846218c64194
   .dword 0x6619c681a46a1ac6 
   .dword 0xc1b46e1bc701c472
   .dword 0x1cc741d4761dc781 
   .dword 0xe47a1ec7c1f47e1f
   .dword 0xc802048220c84214 
   .dword 0x8621c882248a22c8
   .dword 0xc2348e23c9024492 
   .dword 0x24c942549625c982
   .dword 0x649a26c9c2749e27 
   .dword 0xca0284a228ca4294
   .dword 0xa629ca82a4aa2aca 
   .dword 0xc2b4ae2bcb02c4b2
   .dword 0x2ccb42d4b62dcb82 
   .dword 0xe4ba2ecbc2f4be2f
   .dword 0xcc0304c230cc4314 
   .dword 0xc631cc8324ca32cc
   .dword 0xc334ce33cd0344d2 
   .dword 0x34cd4354d635cd83
   .dword 0x64da36cdc374de37 
   .dword 0xce0384e238ce4394
   .dword 0xe639ce83a4ea3ace 
   .dword 0xc3b4ee3bcf03c4f2
   .dword 0x3ccf43d4f63dcf83 
   .dword 0xe4fa3ecfc3f4fe3f
   .dword 0xd004050240d04415 
   .dword 0x0641d084250a42d0
   .dword 0xc4350e43d1044512 
   .dword 0x44d144551645d184
   .dword 0x651a46d1c4751e47 
   .dword 0xd204852248d24495
   .dword 0x2649d284a52a4ad2 
   .dword 0xc4b52e4bd304c532
   .dword 0x4cd344d5364dd384 
   .dword 0xe53a4ed3c4f53e4f
   .dword 0xd405054250d44515 
   .dword 0x4651d485254a52d4
   .dword 0xc5354e53d5054552 
   .dword 0x54d545555655d585
   .dword 0x655a56d5c5755e57 
   .dword 0xd605856258d64595
   .dword 0x6659d685a56a5ad6 
   .dword 0xc5b56e5bd705c572
   .dword 0x5cd745d5765dd785 
   .dword 0xe57a5ed7c5f57e5f
   .dword 0xd806058260d84615 
   .dword 0x8661d886258a62d8
   .dword 0xc6358e63d9064592 
   .dword 0x64d946559665d986
   .dword 0x659a66d9c6759e67 
   .dword 0xda0685a268da4695
   .dword 0xa669da86a5aa6ada 
   .dword 0xc6b5ae6bdb06c5b2
   .dword 0x6cdb46d5b66ddb86 
   .dword 0xe5ba6edbc6f5be6f
   .dword 0xdc0705c270dc4715 
   .dword 0xc671dc8725ca72dc
   .dword 0xc735ce73dd0745d2 
   .dword 0x74dd4755d675dd87
   .dword 0x65da76ddc775de77 
   .dword 0xde0785e278de4795
   .dword 0xe679de87a5ea7ade 
   .dword 0xc7b5ee7bdf07c5f2
   .dword 0x7cdf47d5f67ddf87 
   .dword 0xe5fa7edfc7f5fe7f
   .dword 0xe008060280e04816 
   .dword 0x0681e088260a82e0
   .dword 0xc8360e83e1084612 
   .dword 0x84e148561685e188
   .dword 0x661a86e1c8761e87 
   .dword 0xe208862288e24896
   .dword 0x2689e288a62a8ae2 
   .dword 0xc8b62e8be308c632
   .dword 0x8ce348d6368de388 
   .dword 0xe63a8ee3c8f63e8f
   .dword 0xe409064290e44916 
   .dword 0x4691e489264a92e4
   .dword 0xc9364e93e5094652 
   .dword 0x94e549565695e589
   .dword 0x665a96e5c9765e97 
   .dword 0xe609866298e64996
   .dword 0x6699e689a66a9ae6 
   .dword 0xc9b66e9be709c672
   .dword 0x9ce749d6769de789 
   .dword 0xe67a9ee7c9f67e9f
   .dword 0xe80a0682a0e84a16 
   .dword 0x86a1e88a268aa2e8
   .dword 0xca368ea3e90a4692 
   .dword 0xa4e94a5696a5e98a
   .dword 0x669aa6e9ca769ea7 
   .dword 0xea0a86a2a8ea4a96
   .dword 0xa6a9ea8aa6aaaaea 
   .dword 0xcab6aeabeb0ac6b2
   .dword 0xaceb4ad6b6adeb8a 
   .dword 0xe6baaeebcaf6beaf
   .dword 0xec0b06c2b0ec4b16 
   .dword 0xc6b1ec8b26cab2ec
   .dword 0xcb36ceb3ed0b46d2 
   .dword 0xb4ed4b56d6b5ed8b
   .dword 0x66dab6edcb76deb7 
   .dword 0xee0b86e2b8ee4b96
   .dword 0xe6b9ee8ba6eabaee 
   .dword 0xcbb6eebbef0bc6f2
   .dword 0xbcef4bd6f6bdef8b 
   .dword 0xe6fabeefcbf6febf
   .dword 0xf00c0702c0f04c17 
   .dword 0x06c1f08c270ac2f0
   .dword 0xcc370ec3f10c4712 
   .dword 0xc4f14c5716c5f18c
   .dword 0x671ac6f1cc771ec7 
   .dword 0xf20c8722c8f24c97
   .dword 0x26c9f28ca72acaf2 
   .dword 0xccb72ecbf30cc732
   .dword 0xccf34cd736cdf38c 
   .dword 0xe73acef3ccf73ecf
   .dword 0xf40d0742d0f44d17 
   .dword 0x46d1f48d274ad2f4
   .dword 0xcd374ed3f50d4752 
   .dword 0xd4f54d5756d5f58d
   .dword 0x675ad6f5cd775ed7 
   .dword 0xf60d8762d8f64d97
   .dword 0x66d9f68da76adaf6 
   .dword 0xcdb76edbf70dc772
   .dword 0xdcf74dd776ddf78d 
   .dword 0xe77adef7cdf77edf
   .dword 0xf80e0782e0f84e17 
   .dword 0x86e1f88e278ae2f8
   .dword 0xce378ee3f90e4792 
   .dword 0xe4f94e5796e5f98e
   .dword 0x679ae6f9ce779ee7 
   .dword 0xfa0e87a2e8fa4e97
   .dword 0xa6e9fa8ea7aaeafa 
   .dword 0xceb7aeebfb0ec7b2
   .dword 0xecfb4ed7b6edfb8e 
   .dword 0xe7baeefbcef7beef
   .dword 0xfc0f07c2f0fc4f17 
   .dword 0xc6f1fc8f27caf2fc
   .dword 0xcf37cef3fd0f47d2 
   .dword 0xf4fd4f57d6f5fd8f
   .dword 0x67daf6fdcf77def7 
   .dword 0xfe0f87e2f8fe4f97
   .dword 0xe6f9fe8fa7eafafe 
   .dword 0xcfb7eefbff0fc7f2
   .dword 0xfcff4fd7f6fdff8f 
   .dword 0xe7fafeffcff7feff
   .dword 0xd2d2d2d2da5a5a5a 
   .dword 0xc000000000000000 
ddr_data_limit:
    .align 3 # bit stream data are 8 byte align
ddr_data_5a5a_base:
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
   .dword 0x5a5a5a5a5a5a5a5a
ddr_data_5a5a_limit:
    .align 3 # bit stream data are 8 byte align
ddr_data_a5a5_base:
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
   .dword 0xa5a5a5a5a5a5a5a5
ddr_data_a5a5_limit:
    .align 3 # bit stream data are 8 byte align
ddr_data_5a5aa5a5_base:
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
ddr_data_5a5aa5a5_1f8:
   .dword 0x5a5aa5a55a5aa5a5
   .dword 0x5a5aa5a55a5aa5a5
ddr_data_5a5aa5a5_limit:
    .align 3 # bit stream data are 8 byte align
ddr_data_dst_base:
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
ddr_data_dst_limit:
    .align 4 # bit stream data are 8 byte align
filter2_127t_05x_start:
   .dword 0x00002a3601fb9600 
   .dword 0x0057fffe01ffff78
   .dword 0x01ffcbca0118effe 
   .dword 0x01460000000000e2
   .dword 0x01fe439c01ada7fe 
   .dword 0x00b3fffc0000021a
   .dword 0x0004bc6000646000 
   .dword 0x00bbfffe01fff7d8
   .dword 0x01ff6bb8003577fe 
   .dword 0x011c000c00000564
   .dword 0x01f005c000588ffe 
   .dword 0x0049fff2000011e0
   .dword 0x0019b51a004cce00 
   .dword 0x002bfff001ffd6f6
   .dword 0x0006db7801e06e00 
   .dword 0x01e4003800000b2a
   .dword 0x01b7105801d67bfe 
   .dword 0x014fffd600005164
   .dword 0x0050561c00c65e00 
   .dword 0x000fffb201ff7e76
   .dword 0x0035ea4400939200 
   .dword 0x01bc00b601fffa64
   .dword 0x01191834007f51fe 
   .dword 0x01b9ffb8000106d4
   .dword 0x00b190da01a63000 
   .dword 0x00e9fef601fecc50
   .dword 0x00dc91f000cf4a00 
   .dword 0x005e01c201ff8a4a
   .dword 0x01b2be9c015785fc 
   .dword 0x007dffc80002bae2
   .dword 0x012d63da0018dc00 
   .dword 0x00c1fd1201fd9406
   .dword 0x00c3dad401803002 
   .dword 0x014003e601fdea14
   .dword 0x00734fd8007e7ffa 
   .dword 0x011800b600074112
   .dword 0x0198cf1800a8b000 
   .dword 0x0009f71a01fab806
   .dword 0x005882c0002be00a 
   .dword 0x00600b6e01f48460
   .dword 0x01e51d40016131e6 
   .dword 0x00800c34005071ce
   .dword 0x018ac80001ce8072 
   .dword 0x01305070000c3560
   .dword 0x01e51d40006061e6 
   .dword 0x01e1f484000b6e2a
   .dword 0x005882c00006080a 
   .dword 0x00b1fab801f71aa8
   .dword 0x0198cf1801131800 
   .dword 0x007e07400000b67e
   .dword 0x00734fd8001541fa 
   .dword 0x0031fdea0003e780
   .dword 0x00c3dad40006c002 
   .dword 0x00ddfd9401fd1218
   .dword 0x012d63da00e27c00 
   .dword 0x018402ba01ffc956
   .dword 0x01b2be9c004a5ffc 
   .dword 0x014bff8a0001c2ce
   .dword 0x00dc91f00050e800 
   .dword 0x0031fecc01fef7a6
   .dword 0x00b190da00d5b800 
   .dword 0x0150010601ffb87e
   .dword 0x011918340065bdfe 
   .dword 0x0193fffa0000b692
   .dword 0x0035ea4400760e00 
   .dword 0x005fff7e01ffb2c6
   .dword 0x0050561c01654e00 
   .dword 0x007a005001ffd7d6
   .dword 0x01b71058012be5fe 
   .dword 0x006e000a000039e0
   .dword 0x0006db7800f62a00 
   .dword 0x00cfffd601fff04c
   .dword 0x0019b51a01e04800 
   .dword 0x008e001001fff258
   .dword 0x01f005c001651dfe 
   .dword 0x0176000400000c34
   .dword 0x01ff6bb801d8bbfe 
   .dword 0x0061fff601fffe64
   .dword 0x0004bc60001ab200 
   .dword 0x01a6000201fffdac
   .dword 0x01fe439c00e347fe 
   .dword 0x00ee000000000118
   .dword 0x01ffcbca017857fe 
   .dword 0x0197fffe01fffffa
   .dword 0x00002a3600000000 
filter2_127t_05x_end: 
    .align 3 # bit stream data are 8 byte align
ring_base:
   .dword 0x52a8e6c4c53e5dbf
   .dword 0xd13e997f5770d6f7
   .dword 0x1bd3181215c01ae0
   .dword 0xeb5b2622f36befd2
   .dword 0xdb12d1aa535efbc0
   .dword 0xb03d8a2479f63de2
   .dword 0x0eeb42abad2b1301
   .dword 0xd979d52922e91640
   .dword 0xd820c3041f1823c1
   .dword 0xf72d5faa94813f91
   .dword 0xceb2ae113b49de34
   .dword 0xdf322ea46c4f8c6d
   .dword 0xbe95a3adb5744af0
   .dword 0xac3dea303af2387a
   .dword 0x8e3431423838b684
   .dword 0x503525bac989966f
   .dword 0x696e52e66dc0d163
   .dword 0x9e84f6c4a67e9677
   .dword 0xd4c02777aa1bb786
   .dword 0x0b480dc837aaae34
   .dword 0x9a23e853cec01fbd
   .dword 0xa8ea6616ba02387e
   .dword 0x32cec2715758fa7f
   .dword 0x1ec3caee0aaf416f
   .dword 0x06a831143cfdb4e5
   .dword 0xc4072e2587a80810
   .dword 0xb885a02416490f5c
   .dword 0x3ff4b588b969649a
   .dword 0x3335f42fccb14432
   .dword 0x7724361c15e7e80a
   .dword 0xb8ae4c82547df2fb
   .dword 0xde9a9e5d935c0d58
   .dword 0x016d813d6e1437de
   .dword 0xe1dbe1c9fb66560a
   .dword 0x34ae9e7306a203c8
   .dword 0x8922b83c1e96ceed
   .dword 0xf56e820ca0549bab
   .dword 0x5a35a3fe9d283bcb
   .dword 0x54a1b24f5fc6615b
   .dword 0x700f2ab1baf1e12b
   .dword 0xf071579169e14efc
   .dword 0xb7c383a9ee394768
   .dword 0x0dd3291f16cdd913
   .dword 0xcefaacb8108ea720
   .dword 0xb7dd11a9cc0db181
   .dword 0x8ff5c18026f01f01
   .dword 0xf68390dd29276980
   .dword 0xedf87709d05db94e
   .dword 0x4c5bd001deaa5ca1
   .dword 0xe2323cda395dd97f
   .dword 0x9ad9e76a8bc4887b
   .dword 0x12a87cfad6d252d7
   .dword 0x6d5f0c0e4df58f38
   .dword 0xbbf85177143c472f
   .dword 0x7b342e58ffb0d35e
   .dword 0x4e4073d90ee0a26d
   .dword 0x5fcc1c0c379db0c3
   .dword 0xc22636f32ffc668c
   .dword 0xcbf8d41cbe5c95ff
   .dword 0x9a1ddc8c5684b5a0
   .dword 0x74f567caaab099c1
   .dword 0xce794e05103feb26
   .dword 0x370c744ceab1439e
   .dword 0x51a1a7b6ef566206
   .dword 0x05691b5cdc75fb98
   .dword 0xd78ce1f9b7f721aa
   .dword 0x8df4faab6382ab96
   .dword 0x7a908aef23f045b4
   .dword 0x4abcd668d2db01bc
   .dword 0x910c5c9e2d719135
   .dword 0xbe92f8a4a4d9899b
   .dword 0x21e8f84d59fd0f69
   .dword 0x3e620fc2494d2bf4
   .dword 0x197fe4a98c1a3dae
   .dword 0x1327cc135034974a
   .dword 0x14e90eebce74c22a
   .dword 0x9ad243131a274400
   .dword 0xef9cfb4b052ee6ce
   .dword 0x9f7017376e1fa0d7
   .dword 0x51d16185446f66e3
   .dword 0xb7af878264a91aa0
   .dword 0x94a9de7b6b8bf354
   .dword 0xfc63c5e53f5719f2
   .dword 0x009bb687f12880a8
   .dword 0x6974713ac1d18ecf
   .dword 0xca0dd738e3a865db
   .dword 0x5d31777b01cbb77a
   .dword 0xc1a396926839bc41
   .dword 0xe32e3da14fd8136b
   .dword 0xfed024da148cd673
   .dword 0xdd2529ee2ccc2b2b
   .dword 0x998b85be7081a9df
   .dword 0x380d2b80ba6f6b48
   .dword 0xde8b34e8f3a4aa93
   .dword 0x85b09eac1fc92798
   .dword 0xe87c46fbf948444e
   .dword 0x2e75f4eb54e8163b
   .dword 0xb514c80e48a813b8
   .dword 0x7f9f82877a23c474
   .dword 0x40592e5dd6b4b79f
   .dword 0x6dba7710c8e68fec
   .dword 0xcec5b8d38c8ecbcb
   .dword 0xcbc1bc72286af348
   .dword 0xc125c1f75935b006
   .dword 0xa37407bfb40228b8
   .dword 0x624bea7e02468270
   .dword 0xcbd7ccb6b547884a
   .dword 0x5402a73642b15861
   .dword 0x1b11c510981e395c
   .dword 0x6326ab4748fe6544
   .dword 0x53f929096ee5b270
   .dword 0xc7c7294b5206c71a
   .dword 0xed25e628ce9f7b6e
   .dword 0x023c3c6c87ce8c86
   .dword 0x971382c9a6eaf052
   .dword 0x2accab42b968a95c
   .dword 0x82b7255ca86898b3
   .dword 0x85ad163f317b248f
   .dword 0xa9235c2be9e1ccac
   .dword 0xab1a7ee74ffe7aef
   .dword 0xd0c930aa951629bd
   .dword 0x55cd4fe478eb4e3f
   .dword 0xeef13f5e15511a06
   .dword 0x2fdcda97d83c012b
   .dword 0xf3691d3e8cae46b6
   .dword 0xe09e872698251bdb
   .dword 0xc0126f21ecc97d91
   .dword 0xb3859d36a10ce039
   .dword 0x6cf16f2052375549
   .dword 0xeec77359e166a74b
   .dword 0x73cda80e4022755d
   .dword 0xbadd2374204995fc
   .dword 0x14ddf425599ec4ee
   .dword 0xc532b978fdde15c0
   .dword 0xc2ccac56888013c7
   .dword 0xf47fca37e4b386be
   .dword 0xd421e210862158a0
   .dword 0x4fb861c14cdb2608
   .dword 0xfdb7603631c2fe55
   .dword 0xf371c5bb05460cab
   .dword 0xc9bb6ba19db835c0
   .dword 0x4d55cf8384f534da
   .dword 0x0e4206ecf732ed7c
   .dword 0x93f25c7752cfc0eb
   .dword 0x7bf4990bc1bb37ba
   .dword 0x0e4a7bed85fb46da
   .dword 0x609be46a17cc9050
   .dword 0x249cd40b7206ea51
   .dword 0xa02ae4c1476ed2fa
   .dword 0x1182258a24833227
   .dword 0xfd2ef87c093877cb
   .dword 0x6ae10d5dbb78ec8d
   .dword 0x60c7f994ef955e61
   .dword 0xda5911f3a9f13113
   .dword 0xbf8a06d793583a25
   .dword 0xd8d3bf83210321f4
   .dword 0xdf76ad390f47dbc1
   .dword 0x225d803bf1bc4c9b
   .dword 0xbcbb8df59a831814
   .dword 0xedb4dffa2ea0a3f7
   .dword 0xa01b12a11f40503d
   .dword 0xbeaa50df4cc31ae2
   .dword 0xf57937b6a6f9f9fb
   .dword 0xbb81bf8580abc9e4
   .dword 0x6b86a005d000f61b
   .dword 0x64d99284ddf8a5ef
   .dword 0x4e10736532e66db8
   .dword 0xea877db18cdf038e
   .dword 0xa98087c5b7cea9bb
   .dword 0x9dd4bc105b8c54d9
   .dword 0x18d050ff88712157
   .dword 0x07a6c9335bf23513
   .dword 0x7ea066567bde1056
   .dword 0x0164ec3bbe470d49
   .dword 0x20d79b15e7f22e50
   .dword 0x445f95d2e8a68a06
   .dword 0xcf0f4e09bf1d1066
   .dword 0x41a93c75c4d800ae
   .dword 0xc26942c41d83d062
   .dword 0x6ec5cd1aae5fb75b
   .dword 0xe9c3b2cadc711fe0
   .dword 0x5f30864691f0eac4
   .dword 0x79ff570327b2c5d4
   .dword 0xb1215aded92bf350
   .dword 0x858c1c4835798e24
   .dword 0xd566999523f2da04
   .dword 0xb7b85309e02a9f7f
   .dword 0x908ba8be3debabb3
   .dword 0x43ad1023229e84a9
   .dword 0x304fc0893e006ab3
   .dword 0xc8ce6a832c6ea189
   .dword 0x28d83c37ad6a665d
   .dword 0xb4b6f574ac42e0f8
   .dword 0x8a06e0d0e9dc2ba9
   .dword 0x4c974f9bc829b8a4
   .dword 0xe63fcebebe556395
   .dword 0x3b3b696cd25b587b
   .dword 0x965c60eb1c519a63
   .dword 0x782f0330d5dc477a
   .dword 0x7279a5c15c691bd4
   .dword 0x39ff54646fd5deff
   .dword 0x144b7fd7e5c9abd5
   .dword 0xa461b42910b28b55
   .dword 0xd10eadae82abcdfd
   .dword 0xe08063f4ac84b65d
   .dword 0xa8d889a9e30e3718
   .dword 0x5fc1c8bf45ca9efb
   .dword 0xb7f953f26f8a156b
   .dword 0x8a1d129f25c3e973
   .dword 0x475e23b1ca9bfb74
   .dword 0x3f1b4eccd1472e8e
   .dword 0xc594434b3eee88be
   .dword 0xb084151da545ad15
   .dword 0x29deffc433f2987c
   .dword 0xeb9b5d57411e8b4c
   .dword 0xfa840d152628f691
   .dword 0x5c5e62ad42b66700
   .dword 0x5e7eb2044774f4f5
   .dword 0x716d0c3662e2f68c
   .dword 0x056be264171d1b0d
   .dword 0x708defb39d5c01e7
   .dword 0x4837097706849901
   .dword 0x0ac413ca5d5ab732
   .dword 0x23beef1e67eae6f5
   .dword 0xccda2d8976a274cb
   .dword 0xab42b9df7aefbbc8
   .dword 0x453b06ba190fb745
   .dword 0x429cd6a72de882c3
   .dword 0x3832b2f7bce8e1cf
   .dword 0x9d81bdbbf7ad98cd
   .dword 0x2e011fd34597aba7
   .dword 0xd9fac912d8c33460
   .dword 0xde6f1a0087cc46c8
   .dword 0xb01846a30676a2b7
   .dword 0x873f1bb1d5082362
   .dword 0x458ee3ed026fe3df
   .dword 0x0f6bc83de49258e0
   .dword 0x3f92e4b836adb2f9
   .dword 0x9dc2bc7b5fc435a8
   .dword 0x3cfbcf6051ba798d
   .dword 0xa62ab005d6e9c326
   .dword 0xf4a15adab0def811
   .dword 0x2e1d64d95e2e58ab
   .dword 0x9a559d2885c6ebe9
   .dword 0x103d20128e3215b1
   .dword 0x98aa7e152a820d62
   .dword 0xc3531dd27fdd7d16
   .dword 0x3bac0577354cd73a
   .dword 0x73ddf6aa1d1d07bf
   .dword 0x1b0c3a5d7588c34a
   .dword 0xf684c415103cad34
   .dword 0xd7a52b09add766c5
   .dword 0x795e04ee10ed2196
   .dword 0x1166489abe2bf70f
   .dword 0xc245396b7407c9f2
   .dword 0xe0428d014d939983
   .dword 0x8b9d614ce2fb6b9f
   .dword 0x0c35affda9706ac4
   .dword 0xcf8790a2acf8d8b2
   .dword 0x06eb9f6143d33850
   .dword 0x1d7258829cc050a1
   .dword 0xf3b1870086e72962
   .dword 0x6d2fe6d512990973
   .dword 0x7a27839dd9134d75
   .dword 0xb015456ad2b3e033
   .dword 0x1c4439905f8c4797
   .dword 0x26f2d13bd7ee272b
   .dword 0x04a34ecb475313bc
   .dword 0x58dca6d7bc435dee
   .dword 0xea8921d5c1cb99eb
   .dword 0x83003131547c4f2b
   .dword 0xaa66b5f02dc445ff
   .dword 0xf7112c5c66293aa1
   .dword 0x97adbec398b57147
   .dword 0x408334b6c5f9c7c0
   .dword 0x71087b5a2de402bc
   .dword 0xcec38727be7815c0
   .dword 0xf83fad765257e04a
   .dword 0x0c55543dab19ec34
   .dword 0x5fe08569410a9157
   .dword 0x1c8509b811b8c305
   .dword 0x2a1fbb38d8ef9ce3
   .dword 0xfc8654171c5110bf
   .dword 0xb1454bfd18c39a13
   .dword 0x3c2426f71124e8bd
   .dword 0x695862e5098464da
   .dword 0xb282289ce83ed6c9
   .dword 0x04ab6b85266d0975
   .dword 0x1d6f9bdb5949945b
   .dword 0xe737ec82b6b2d925
   .dword 0x87370133b3aef6f0
   .dword 0x837758061f78f662
   .dword 0x5871646842054cc9
   .dword 0x0b517fc9ccdaab89
   .dword 0xb39db0ad06c63aac
   .dword 0xe38224a3fb13abce
   .dword 0x5a65e62408d9593e
   .dword 0x2f52081b11b44ffb
   .dword 0xeb2e093601e33ba2
   .dword 0x1a00cb205be5c4c6
   .dword 0xf9058310c0252d1e
   .dword 0xb40613563aa174a2
   .dword 0x617b0c76bfc3206c
   .dword 0xfe230f7eda30d6d5
   .dword 0x7a53bc5d590bb372
   .dword 0xdfa28afe69b4994e
   .dword 0xa2eae4778b02af82
   .dword 0x5e65ad90f1454274
   .dword 0x5c3d17c1485ef301
   .dword 0xb6854c5fe1a29d15
   .dword 0xae6cf5b95dea2718
   .dword 0x6c7ed54f80b81f36
   .dword 0x32a12a7152833dd6
   .dword 0x6fc47e7cc623b12a
   .dword 0x06fdd743bdc6d32a
   .dword 0x5cb5d2495f0e0271
   .dword 0x3bf7d0b7ec813d0d
   .dword 0xa71d4836b5636cca
   .dword 0xe0a457881e4668a0
   .dword 0x1e7e9945684fb3a2
   .dword 0x140b781dc4f8512e
   .dword 0x0fda7c16c9c22136
   .dword 0x36fd1bb828161387
   .dword 0x78e0fc5ad45e7fe5
   .dword 0x9d6da404d1645845
   .dword 0x61d3cd03c9ed4bb1
   .dword 0x2e4ab14c9c9249fb
   .dword 0x59fc3e050add2233
   .dword 0x1408711c2f9a7f6f
   .dword 0xa9befdd3fa0bcfd0
   .dword 0xbbbdaa56577e4a3a
   .dword 0xec3778fd284d54c3
   .dword 0x2d081da5b97cf472
   .dword 0x8686d49101ad9f67
   .dword 0xab905ac4ea855ee9
   .dword 0xf10fda997601d8d3
   .dword 0xdbd4d1403ed93583
   .dword 0x22df5a23df888903
   .dword 0xd62fb34d3e0f7c4e
   .dword 0x895504e98e9830de
   .dword 0x729664631cc15f48
   .dword 0x63adc17d0886eaa0
   .dword 0xf2deef2763134407
   .dword 0x7dd00b9a6ddb5c64
   .dword 0x84e37a7df64fa77d
   .dword 0x339989dc9f55b495
   .dword 0x2e2486570ed0e36f
   .dword 0xcbfd048f476c9c65
   .dword 0x3bd2d285dc30df22
   .dword 0xad10102abb86ed1b
   .dword 0x48b7f7d07e464ca8
   .dword 0xbb9536b2cea5a286
   .dword 0x6b45dfac2c9118b0
   .dword 0x6c1d64f5834f8577
   .dword 0x3407f2686f2143af
   .dword 0xb8e99f9c0896fa9d
   .dword 0x0dedfb925fc1e00d
   .dword 0x5bdc3d50e4d1b7ee
   .dword 0x5e602da27585e92c
   .dword 0xd52caf42ba138b30
   .dword 0x229b0045d1f2411f
   .dword 0x8b2b715174bb181a
   .dword 0x2b97b67ed732f3fe
   .dword 0x3be258674cb6a24b
   .dword 0x8329f3fbe27eada8
   .dword 0xbe3bba6fba65e27f
   .dword 0x9e50a7fb58ed282e
   .dword 0x667440f5bd0b3f94
   .dword 0xeadf8ca22df66b1d
   .dword 0xac1a2a417c91e24d
   .dword 0x79e1918f53583094
   .dword 0x35b5552b93836764
   .dword 0x96f3e7cf53d29ca4
   .dword 0xa4654c761b6a5258
   .dword 0x1f31c0ea516248cd
   .dword 0x4c53b22ded5d9af3
   .dword 0x196b19454c0520c2
   .dword 0x26d4d7fcd3a8b608
   .dword 0x8a3e29f09184f21d
   .dword 0x26b4f0a4896b9096
   .dword 0x81c04066220177d1
   .dword 0x6b93350872ed73bd
   .dword 0xd49a1677f2a02473
   .dword 0xdcf6c85f47a444d5
   .dword 0xceaeeef8324b9467
   .dword 0xbd7b0d766b37649b
   .dword 0xaee26828ceb5826c
   .dword 0x27f82d58c958a9e8
   .dword 0x444ceb8b7d260141
   .dword 0xd88ac045fa58e55d
   .dword 0x5c1a6afd0cb5959a
   .dword 0x11626fa5dff21320
   .dword 0xe803952d6e393622
   .dword 0xe3605059fc844041
   .dword 0x0adf123e39df8bd7
   .dword 0x4bfad60d52215930
   .dword 0xc239a4dc580095a0
   .dword 0xa5a0505f3cd923b6
   .dword 0x5bfef3e31f797e2b
   .dword 0x80d7e02c37e61d16
   .dword 0xacc1b5ab044e9b0a
   .dword 0x7445e053357032bd
   .dword 0xf639780e8ca0f984
   .dword 0xa87a8af840148ff2
   .dword 0x7d0bf3696b1268d4
   .dword 0x7d58d76b39553007
   .dword 0x43b050e4a5f4a25d
   .dword 0xf735182b8f0a410d
   .dword 0x9e313e8a591e39b6
   .dword 0xbb8700a01a055876
   .dword 0xc3e486d34f03c20a
   .dword 0xc2029da23f60ecef
   .dword 0xccc89862bc3c09fd
   .dword 0xa5aa69433bd6b2e4
   .dword 0x341132cf540191a3
   .dword 0x818e2ff8e9c90d92
   .dword 0x37a39ff53d82fff1
   .dword 0x48d85eb5af1b6b1b
   .dword 0xdd81bc99803587a7
   .dword 0x8c766d8de05fe808
   .dword 0xfe4dbb04cba63971
   .dword 0x304f01de77a4de69
   .dword 0xe7186a6bd6a2641c
   .dword 0xa7ac7803f50a88da
   .dword 0xa80f6e3049828524
   .dword 0x878bb4520fc8bbee
   .dword 0x3047bab0a57337b7
   .dword 0x56950ee7c7d00a2a
   .dword 0xb2d5d137befd06c9
   .dword 0xab77bc24df5d0502
   .dword 0x1eb315ebcebadde4
   .dword 0xb96b9e4a28ae9cdf
   .dword 0xa64f2900a00d413c
   .dword 0x7738f60271489e89
   .dword 0x2b566d235c95bff5
   .dword 0x98d465424e8cd187
   .dword 0x334a59ee0d2178f6
   .dword 0xd172d2b81ed405f3
   .dword 0x36f0c67626f874dc
   .dword 0xd414a4b0a7380fbc
   .dword 0xad081b1aac09dc6d
   .dword 0x714d4fd4b61583fe
   .dword 0xac2c3bceb520613e
   .dword 0xf62ad563052f860a
   .dword 0xe105b074e27bfb57
   .dword 0x6af469238389a486
   .dword 0x7cd2fe93114138b5
   .dword 0x7796e3dbec19c67a
   .dword 0x229b5b825b382c71
   .dword 0x3326913eba99e4f1
   .dword 0x1c7b51f7d756f58f
   .dword 0xc6895c4050228c45
   .dword 0xb6bfc74ddd35b61b
   .dword 0x6c498f1fa4559d34
   .dword 0x2052740178363c36
   .dword 0xea9e1d85661ed622
   .dword 0x61fad328c333969c
   .dword 0x05cb9d1b8d939798
   .dword 0x377a34db14f55340
   .dword 0xe587ce0991ce5407
   .dword 0x8216cbe1b9f645ac
   .dword 0x2bcb8a2d0f6ee63a
   .dword 0x7fe756626bd9d4a4
   .dword 0xa973d83a23fe7ffb
   .dword 0x7df4211b53daed11
   .dword 0x6b43734ad650e342
   .dword 0x1f1fd1c17b248733
   .dword 0x2ebcbd2189cf5ced
   .dword 0x09b1bbcfaeecef0f
   .dword 0xa74d6fd0a89facc0
   .dword 0x4a3f4a5fe30d4215
   .dword 0xaaf10a65e2a7b451
   .dword 0xfaa766bda0d9f013
   .dword 0x72d21e6cf2221352
   .dword 0x421716261295bf25
   .dword 0x61146c223484fd88
   .dword 0x3a929b153e0b81af
   .dword 0xc51c9e23e9424a49
   .dword 0xd28d56200a9d5214
   .dword 0x7cde3592e312cb9c
   .dword 0xbf2b74a218c402e0
   .dword 0x2b48b8d8df07c3b6
   .dword 0xdd61c76772485b7d
   .dword 0xe481ed3ac1023c4d
   .dword 0xc2288102df6a1e35
   .dword 0x014072fe1c1069fb
   .dword 0x7454f4e43b43a72b
   .dword 0x503f75790fe45f36
   .dword 0x4d78e5abc2911500
   .dword 0x5fd6a5f07947f502
   .dword 0xb81b0e7ffc3d679d
   .dword 0x22ef75af740ea0cf
   .dword 0xee5aafc41c2e972a
   .dword 0xe6723872502046e8
   .dword 0xeeebb9eba48753d3
   .dword 0x5fe24cf1ce58e1df
   .dword 0x744d23626f624ad6
   .dword 0x65104f9dbbede43b
   .dword 0xe77022f12c47c37c
   .dword 0x6610b4ef5f9a33b1
   .dword 0x913f1c683f369206
   .dword 0xc4d2fe7c3da4e4d2
   .dword 0x306bdb73d0290ebe
   .dword 0xe5b654b72e692546
   .dword 0x73ecb2cf9cb8c7b1
   .dword 0x283d1cfba009fde0
   .dword 0xc9e9ac59dd5c958f
   .dword 0x82281deac824c433
   .dword 0xab0447656456988f
   .dword 0x919a9d9792faff00
   .dword 0xa7c547695ccf69d9
   .dword 0xe4d8fd1a8a4d1551
   .dword 0x4b1b45e1f7c0a632
   .dword 0xd913a832249ca989
   .dword 0xbaacbad5a28c9c59
   .dword 0xb0bea8c02229197b
   .dword 0x0c52b3a51eff4fb3
   .dword 0x647e37c4a4b9d084
   .dword 0x7d376c2ebaff2833
   .dword 0xe409b7159ff6381e
   .dword 0xd216812625621057
   .dword 0x4d3c265f0dfc7862
   .dword 0x8cb355229da18008
   .dword 0x674293b67dd48a61
   .dword 0xe9cc34b47a9bc083
   .dword 0xed9aa97c8bebd041
   .dword 0xb95a428d5e9c1588
   .dword 0xb37c45b091b5f2ff
   .dword 0x8a99cfe56b87919e
   .dword 0x6a7ccb1fc80b7b90
   .dword 0x3145071c55652036
   .dword 0xff0abbe667e0ae51
   .dword 0x51f639b465c41335
   .dword 0x65a704fc3803813d
   .dword 0x27b67db9cd493f54
   .dword 0x20c568b3c790f59c
   .dword 0xadf33918addb9054
   .dword 0xb48674784cc01ccc
   .dword 0xb5d8b5f74f15ce84
   .dword 0xd8b6fe5272b689f8
   .dword 0x6b96de9c029081b2
   .dword 0x143b3e88533f6846
   .dword 0x7edcfe66525ae6e3
   .dword 0x711d7e6c46b6cd76
ring_wp:
   .dword 0x217d50b45efb16c2
   .dword 0x71920adedcdf9dca
   .dword 0x36d611fe55bd3a4b
   .dword 0xc935e7b7e7749739
   .dword 0x8fbf067baf52a8c4
   .dword 0x3168f7fb37e10efe
   .dword 0xdf621e2cc713c5dd
   .dword 0x06d0bb3e759a03a0
   .dword 0x1e086ce8247f8dc7
   .dword 0xa085c5c6927ae719
   .dword 0x0d3b25a113f81766
   .dword 0x96719b2239811577
   .dword 0x14dedc313f7f36b0
   .dword 0x02b2a0aef2d1087e
   .dword 0x2d24fa3d47742a12
   .dword 0xf3763e4a0b2eadde
   .dword 0x1d2698e30e8d160f
   .dword 0xc1890d4cdb27e6ad
   .dword 0x40f578233cc9ad8d
   .dword 0x1e93df47b612aa18
   .dword 0x4dba4ebfad3537b3
   .dword 0x7e4093ec06a29044
   .dword 0x4bc6e1b206196b68
   .dword 0xd83ea7a4582f16b5
   .dword 0x264fb308925277fe
   .dword 0xce285af683a4ee17
   .dword 0x00d8761459fa6518
   .dword 0xed99d70675834c45
   .dword 0xd008525d38038e78
   .dword 0xe8cd05ab6650e71a
   .dword 0x6296a0b9c8f656f2
   .dword 0xde52722cac11af9d
   .dword 0x53b08a94695924c0
   .dword 0xed4106bf73976d71
   .dword 0x5c7fb56dc2cb3752
   .dword 0xb06a70477c988780
   .dword 0x0300fa59f17e6a69
   .dword 0xc8994acc8baae23a
   .dword 0xbea27c31e6c283ef
   .dword 0xc6371c6eef9910db
   .dword 0xd08302ea1b15cc16
   .dword 0x1102798aae68218f
   .dword 0x6b2faef29a82d03f
   .dword 0xdaf1ec34962d8a15
   .dword 0x47e46871df0788a1
   .dword 0xd8a324dee3013705
   .dword 0x4f740229c9e6d9ef
   .dword 0x50fa73d812a0ae0d
   .dword 0x5a7d99df8f01a2b7
   .dword 0xbf5aa2ecbfe6fff9
   .dword 0x771689acf907f1a0
   .dword 0xa9759094e506034d
   .dword 0x3621836e2867cba0
   .dword 0x029364969dab6216
   .dword 0xb081135dce9dc240
   .dword 0x06067d04f133f64e
   .dword 0x3fadca5d6874ee69
   .dword 0x5bdafd526a8002b2
   .dword 0x003d2b8451471060
   .dword 0x976142cbea7aadd3
   .dword 0x0e9798aa70c92130
   .dword 0x1aaf423ed7b85f20
   .dword 0x95f4da49e42565a7
   .dword 0xdbb9f5c1e353b614
   .dword 0x7d0deb825b24d177
   .dword 0x9da7758b0540fabe
   .dword 0x8f99ada5ef4b8eab
   .dword 0xe00f82acb018e5ac
   .dword 0x83a67b68e3820d08
   .dword 0x69688b6612fdd298
   .dword 0x24b3bf5547e0c3a4
   .dword 0xc6fa8a1c0407840e
   .dword 0x66642ef8dfcd5b2f
   .dword 0x96cf8c73c933d697
   .dword 0xd70143297c9aa4ca
   .dword 0x24b841eeb6b4d6bd
   .dword 0x95eec2c8d4b11f59
   .dword 0x5d0a1065c5232583
   .dword 0x7411305d3bf15e4e
   .dword 0xa049b0bf11c3dafc
   .dword 0xe3875e4bab7155d0
   .dword 0x02b870dec79b6db3
   .dword 0x666aa1aa9381343d
   .dword 0x4e8e8a7e910e1e97
   .dword 0x8fe7e44338679c42
   .dword 0x1c2c2b91babee0e1
   .dword 0x3ed3febb9daf7175
   .dword 0xbf619cdd4d60a7ae
   .dword 0x3ae43d8239200278
   .dword 0xaeb8262e84d91e89
   .dword 0x87e5e2d26cc80de4
   .dword 0xa774e3b9dc1968fc
   .dword 0x3a55bce7a5d622ac
   .dword 0xd5fa29db4e0f266e
   .dword 0x05acdf1def4bd85a
   .dword 0xe990d675f800e980
   .dword 0xde2164ec714e8980
   .dword 0xad5d5ace804a6601
   .dword 0x0a40a0e3c2297101
   .dword 0x164ff5cb39a1cfc9
   .dword 0xef221e98da4e094e
   .dword 0x4a72373381eca437
   .dword 0xf917188b9d776a5d
   .dword 0x48daaa6e50de42c7
   .dword 0x261817eddeb1a791
   .dword 0xf57d637f16211f8e
   .dword 0x0a6044b80ab840db
   .dword 0x3a10330ccfd310c2
   .dword 0xf479d233f2b64aa8
   .dword 0xdee2ff062dbc578b
   .dword 0x19e970957a324e50
   .dword 0x47f487883e06adf1
   .dword 0x6452b2c4d7323a3d
   .dword 0x66b2ad53c256e816
   .dword 0x3792dc0ef1307535
   .dword 0xdebe391b9993c402
   .dword 0xed9faffe7a78bf87
   .dword 0x0d031403fe895557
   .dword 0xd7d75b63bcfdf666
   .dword 0xe6270e416d2a85ea
   .dword 0xf16ff6b5aaeb5d2c
   .dword 0x2a2cd86cbdf8e183
   .dword 0x8ae4eb75d8b9aaa5
   .dword 0x01070c883c398111
   .dword 0x02495072f1dceb4e
   .dword 0x40f1e52a123928d3
   .dword 0x5880a84dd3b065e2
   .dword 0xd223709bd1d38299
   .dword 0xf59f586d72befff2
   .dword 0xb36af3cfdb4b387d
   .dword 0x1eb13740df4da269
   .dword 0x1e00d01e34a2a3eb
   .dword 0x265e742d5e0a2194
   .dword 0x0ac6cf04b913a02f
   .dword 0xd14f432b71aa93e8
   .dword 0x4a4b95bb59472587
   .dword 0x209cdd7fa9a45eb0
   .dword 0xdaf0b9d686a52db0
   .dword 0xcb6c9a45745eba91
   .dword 0xdee58143aaeaec63
   .dword 0xfd19611149778b6e
   .dword 0xe7815d2d652d8cea
   .dword 0x3d08af393f642f78
   .dword 0xf0984aae3160d052
   .dword 0xbd07a56cdb0f2ca3
   .dword 0x8da1971d51ecfbdc
   .dword 0x1186b9b64e912b9b
   .dword 0x6ba32b0b767589ee
   .dword 0x07829d265a2447ae
   .dword 0x376aec0171c5ea95
   .dword 0x56850c2b58806ba4
   .dword 0x79ec84179209838b
   .dword 0x15ed60f98a7e284c
   .dword 0xc6ae661bb734384e
   .dword 0xf88d95b968b733df
   .dword 0x5a969dd85abaca25
   .dword 0x802a1b98be449237
   .dword 0xf01fa3a844d9868c
   .dword 0x16100174f077d35d
   .dword 0xf809fbc0efedb67d
   .dword 0x791b9efc5c583b90
   .dword 0xcefcbb9d6416299f
   .dword 0x62927769330b3e41
   .dword 0xa008b65f0f9156aa
   .dword 0x3b0db5d3cfe1af5d
   .dword 0x4090469e8b639ae7
   .dword 0xfb050b0b89d3cce4
   .dword 0x3114ffd7cfde4589
   .dword 0xc65d5647863c8b4e
   .dword 0x9cc6cc2ce28dc084
   .dword 0xbd68110317e0ede0
   .dword 0x2543367d5db81cec
   .dword 0x69dff0eda5187783
   .dword 0x86b2631ef1604f01
   .dword 0x193845d14c9dc78f
   .dword 0xc1c3f4237e115d1d
   .dword 0x00ce10eccf12f6d7
   .dword 0x97be33ce565a08e9
   .dword 0x92df58f7607ba6d8
   .dword 0x9446a33163dedcfe
   .dword 0xe745e9cd9f7a66ba
   .dword 0x01e4a912ee6f43bc
   .dword 0x0a1a46c558734426
   .dword 0x0b4eb67c95abeebf
   .dword 0x16d68eaf69310157
   .dword 0xcdd82d89c5d5c215
   .dword 0xd4fc2d5109e5e84d
   .dword 0xfee56f0b273a3751
   .dword 0xb8241ffda2a8d42c
   .dword 0xb42e37e46a7c60e8
   .dword 0x681044dd8df82a97
   .dword 0xee9354375368565a
   .dword 0xf426a2bb0f6ab302
   .dword 0xe11f24b2efc6ffb9
   .dword 0x464eef0151289551
   .dword 0xffdd467381b85213
   .dword 0x18edbd75e54786bf
   .dword 0xea388f8e8bbbd691
   .dword 0xe2f83ada0fd91487
   .dword 0xfbd86a02bbb9c446
   .dword 0x8cbcc192f54ab785
   .dword 0xaad1ff7e01ab63a4
   .dword 0x57f60b6dc1f610e8
   .dword 0x7ca8b1e739554987
   .dword 0x4ece3b8b1dc5ee99
   .dword 0xca2c9ff671927bfd
   .dword 0x4584492612931080
   .dword 0xbec41222a311b2a2
   .dword 0x78ceebed883a777e
   .dword 0x422e8fdf1ed79ba3
   .dword 0x784b42ac3d72d6db
   .dword 0xc28844b577a17750
   .dword 0x79fb6b815944aea4
   .dword 0xe626b1bb550d10b0
   .dword 0xfe6d8d8b2a27f3cd
   .dword 0xcaec1700961560ea
   .dword 0xe1530ae90deda338
   .dword 0x5a8174970878c14a
   .dword 0x5c791ab8acd7132d
   .dword 0x966706aaa2c15255
   .dword 0x2109e740cc028a5f
   .dword 0x8d1f6a5bf8ded704
   .dword 0x1b396f3023d2041d
   .dword 0xf35afe7a95247078
   .dword 0xbed05c0ca6a23230
   .dword 0xbbb5ec566ed09cec
   .dword 0xd55f0e9591f35947
   .dword 0xcb0957fd71df3c53
   .dword 0x0c87355a3e763074
   .dword 0x7bb00153cc52df20
   .dword 0x56434b1e24ed1585
   .dword 0xb8c9965942184f39
   .dword 0x98e46542dcf5d453
   .dword 0x918a787521b94e7f
   .dword 0xe2656a4f181a4203
   .dword 0xd009128659d6f67d
   .dword 0x9495d082a1529625
   .dword 0xdc42a0ed5397bdec
   .dword 0xd6a6de8472fb3427
   .dword 0xa404e50f3a4368da
   .dword 0x08d446974a272600
   .dword 0x8e7328e3a6878025
   .dword 0xe8664e445b8fdfe5
   .dword 0xcb99ab02e3b7c6b5
   .dword 0x6789067701f8fc5d
   .dword 0x4837379c9732b31c
   .dword 0xf98e1748d86d33bc
   .dword 0xd0b0df0345e11d2c
   .dword 0x359e744dcb3e3858
   .dword 0xceeea8f073aa6a3d
   .dword 0x0ed3d9557048e458
   .dword 0x96cd375856638727
   .dword 0x9afe8c2d9c80d165
   .dword 0x6a6108455fb6d73b
   .dword 0xe5a492df5bebe004
   .dword 0x932d374d858260b8
   .dword 0x82f47126427fe735
   .dword 0x64c82ec3a82ed559
   .dword 0x9e0a5c0826988970
   .dword 0x83f75b4523a804d1
   .dword 0x9974e376e99f47fa
   .dword 0x49cf78c94ebe153e
   .dword 0xdbb509cf0eae3406
   .dword 0xef021a734b5223cf
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
   .dword 0x0000000000000000
ring_rp:
   .dword 0xaab71e1ed4231e23
   .dword 0xe1160725dbccebfe
   .dword 0xf536c73f1131ad34
   .dword 0x12abe646ed29b5c7
   .dword 0x020fd647d606217b
   .dword 0xab1b2340048d05de
   .dword 0x228f938fa9b5c7dd
   .dword 0x817c4fb62aad8dd6
   .dword 0xed0abbddfbcad753
   .dword 0xf76990326f3f4871
   .dword 0x153c539ecebfe8d6
   .dword 0x23bf3f67483a43e2
   .dword 0xe8187396acd204a0
   .dword 0x6c6879bd3bf0de3c
   .dword 0x4702f3638b988ba9
   .dword 0x753aa286a6eaf631
   .dword 0x6e64b18ee80e6153
   .dword 0xc0584e38e201c617
   .dword 0xf107c1624c8ef6b6
   .dword 0xb29ce1144bf78c9c
   .dword 0xcc740c2491497cb9
   .dword 0x9891d52ad2035687
   .dword 0xe80aee1f2fa5a167
   .dword 0xaa6e4a4ce29fd83a
   .dword 0xea53efe55ca06d09
   .dword 0xf84fadce704fe960
   .dword 0x71e9aeeb75362d62
   .dword 0x9284689d0e01bcc4
   .dword 0x53ce78ed547500e9
   .dword 0x4686bcba44450541
   .dword 0x8e9165ed212b3be9
   .dword 0x10c06e91bc6882e7
   .dword 0x68ab795a3924bee1
   .dword 0xbe49e60ebf626c92
   .dword 0xf71593406166854d
   .dword 0x785dd1b1886ccb97
   .dword 0x91db7969d75d28f9
   .dword 0x6754b2d57af1d312
   .dword 0x9898bf371661fd14
   .dword 0x1d463c6d9eb1551b
   .dword 0x52072800064bbab4
   .dword 0xa1b12a919fd38d21
   .dword 0x043229dc6368b5fb
   .dword 0xd4d651968c4fb2f7
   .dword 0xe5d100ea1c53e433
   .dword 0x388895787e9624b6
   .dword 0xe6395d4afad01114
   .dword 0x3b77b67d9a1bfa6e
   .dword 0x796b43613ae7c089
   .dword 0xcd0b29a336369867
   .dword 0x184ae365b82383a7
   .dword 0x94ec33d7018dbc4c
   .dword 0x85265787d62a639e
   .dword 0x34ce0c1267cc9564
   .dword 0xe190e5b378a297ba
   .dword 0x7b4445f7e55bd904
   .dword 0x8f28ae65ebce7840
   .dword 0xace5a16108fe3fe9
   .dword 0x7264e6048ecf9e46
   .dword 0x05db085320bbf9eb
   .dword 0x88ab77bea6152a61
   .dword 0xc144181797b4097d
   .dword 0x7cb5e58ab24f4ba8
   .dword 0x02af5c28708e4979
   .dword 0xbd43dca687e2b20d
   .dword 0xfeae191dbb240ee7
   .dword 0x2c513e4bfdaf35f5
   .dword 0x2b46e444fe24cd09
   .dword 0x208b9346f42330d5
   .dword 0xd1014ef353db7f25
   .dword 0xe9bd9dbe2a4f0a2e
   .dword 0x9d39e4374c8d3825
   .dword 0x610c98a3c26bfa75
   .dword 0x4f1ccce81f500ad9
   .dword 0xde4614b8c8c8029a
   .dword 0xde9ee3b9bc717798
   .dword 0x8f9926802f497c7d
   .dword 0xca650f6a17a55405
   .dword 0xa7b1c4e290408216
   .dword 0xa6dc3affc7d9dcf9
   .dword 0x719b2102d8056932
   .dword 0x57dd4a2dab70e4ec
   .dword 0xc0abfe47f482800f
   .dword 0xe35e7965746cd88a
   .dword 0xdd6248da8ba9a4de
   .dword 0x3d182a5480064de4
   .dword 0x20f7cce73ed58aab
   .dword 0xcd55d08925bcb45a
   .dword 0xd1049b27b882ebb8
   .dword 0x7a0da8c09f6171ea
   .dword 0xd926f1c431db4223
   .dword 0xbd384985c0661601
   .dword 0xa1eb91dc545ba7f9
   .dword 0x6a0070a28250c221
   .dword 0x6d5e7a5b107197b4
   .dword 0xf565aa90bb44b34c
   .dword 0xbacb825ca1e39119
   .dword 0x247212d71e245917
   .dword 0xf957da919fc62844
   .dword 0xf95c27aaf5367105
   .dword 0x0ea61608ddba4d3e
   .dword 0xc0bc9d251d39160f
   .dword 0x29947e0f7660b0f5
   .dword 0x03a226d98b881a17
   .dword 0x679e04382a6319e6
   .dword 0x44eb83b234687a80
   .dword 0x647d5e9e30feac3f
   .dword 0xc37424ad4dc0c081
   .dword 0x42ef8a80c49161b2
   .dword 0xc8c5c0a2a0da7996
   .dword 0xa88f98473a91621a
   .dword 0x8584a3df1a5b1566
   .dword 0xe25f888128e97972
   .dword 0x06bd567c07a56c57
   .dword 0xcc17d30b02dae863
   .dword 0x1eebc9868a00c156
   .dword 0x46892656a446967f
   .dword 0xe254893ecc90d67a
   .dword 0x16657f5d42889650
   .dword 0x716037e777977996
   .dword 0x6e837689fc144a64
   .dword 0x05ba2b36bedddec8
   .dword 0x0c6ba06f9861fe14
   .dword 0x3aac671c3cc0c2d0
   .dword 0x12c65038d5d57178
   .dword 0xd3cd9907ca69c34e
   .dword 0xa59a56ca18a1ac27
   .dword 0x2051a4ba372c4fe5
   .dword 0x05f4ee00fdfef593
   .dword 0xea2150ebc4da8941
   .dword 0xbfa1007f53ddb8b0
   .dword 0x96b9ffd1786c4acc
   .dword 0xb52beae5f4755cab
   .dword 0xf8a21c2e0e28a017
   .dword 0xf363871837e9d3d2
   .dword 0x19b225746915e296
   .dword 0xbda0743ab62f9277
   .dword 0x409c6820d8c93b09
   .dword 0x58b6315d58f5dd76
   .dword 0x640dcf85b7455569
   .dword 0xadce31afc11be5e6
   .dword 0xddd194cfd538dc55
   .dword 0x90cd522c30830465
   .dword 0x6ce97de9576a4d0d
   .dword 0x6476007177380470
   .dword 0xdf6886068b11bee5
   .dword 0xa6bc3b3e664e766a
   .dword 0xb421d375a98db23c
   .dword 0x8abd7d2267600efb
   .dword 0xe651b0379453461a
   .dword 0x9e9a606445ee8c30
   .dword 0xd80ae11f1f8050b6
   .dword 0x06db16d6d093d319
   .dword 0x052ddc3391447f1d
   .dword 0x9c91bf337b24e172
   .dword 0xaf86afe56557b14b
   .dword 0x629e5b27b3a302bf
   .dword 0xbcebac93a7fc2cb1
   .dword 0xca91c3acb557bffc
   .dword 0x39c132098001c9c7
   .dword 0xc66f49c1f4daf722
   .dword 0x5f06c2505de1df45
   .dword 0x3229efb9d4b58393
   .dword 0x3879e44c54f55075
   .dword 0x94898a08572a3d11
   .dword 0xd07776255b7e2b96
   .dword 0xfb0a9fdd588109ce
   .dword 0xf316f857410e75f9
   .dword 0x903b429f1d484c8c
   .dword 0x4e371d4c4d7e93f8
   .dword 0xd33b36436801462a
   .dword 0xc8012ce84231a391
   .dword 0xf04f9cec619f0a2d
   .dword 0x1c8688a916ebf20d
   .dword 0x66bd1680098c7aaf
   .dword 0xbc44e2cdce26a2a2
   .dword 0x52f4b772aa617db1
   .dword 0xea9fcd32e9af255a
   .dword 0xef0cacaa30797cde
   .dword 0xa89aa6b8d0794191
   .dword 0xfa0bbcd74e918793
   .dword 0xff006d368142375a
   .dword 0x9a2e0ede7daf8913
   .dword 0xa33e113c957f0458
   .dword 0x473eafb106268f6f
   .dword 0xa66740c099f4ac05
   .dword 0xd74e29d2c4f07363
   .dword 0xe802a01f6f504d14
   .dword 0xeb2aa5e9e26d15fd
   .dword 0x2be6d3333eb5a24a
   .dword 0x00ea2d8926fe75b7
   .dword 0x42d8a4747c214138
ring_limit:
