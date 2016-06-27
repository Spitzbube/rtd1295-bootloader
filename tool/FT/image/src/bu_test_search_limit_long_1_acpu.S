#include "include/saturn.h"


.section ".text", "ax"
	.globl	test
	.ent	test
test:
	.set 	noreorder
	
   li $17, 0xdeadbeef
   sw $17, 0xb800d144	
	
   li $17, 0x64
   sw $17, 0xb8007800 
   
   li $17, 0x64
   sw $17, 0xb8007800 
   
   li $17, 0x76
   sw $17, 0xb8007800 
   
   li $17, 0x76
   sw $17, 0xb8007800
      
# write register SYS_MUXPAD1 
   lw t0, 0xb8000364
   and t0,0xfffffff3
   sw t0, 0xb8000364
# write register MIS_GP1DIR 
   li t0, 0x00000001
   sw t0, 0xb801B104
# write register MIS_GP1DATO
   li t0, 0x00000000
   sw t0, 0xb801B114
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

## end ##
b DIAG_PASS
nop
DIAG_PASS:
   la t0,TEST_PASS_ACPU
   jr t0
nop
DIAG_FAIL:
    # write register MIS_GP1DATO
       li t0, 0x00000001
       sw t0, 0xb801B114 
    la t0,TEST_FAIL_ACPU
    jr t0
nop
FILL_CACHE_LINE
   .end test
# Data section
#    .data
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