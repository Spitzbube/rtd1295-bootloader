#########################################################################
# Path Setting
#########################################################################
#	# Chuck add an auto-check of toolchain
	TOOLCHAIN_READY := $(wildcard ../tmp)
	ifeq ($(strip $(TOOLCHAIN_READY)),)
        $(warning toolchain is not ready, intalling...)
        $(shell mkdir -p ../tmp)
        $(shell tar xfj ../toolchain/asdk-4.4.7-linux-newlib.tar.bz2 -C ../tmp)
	endif

SDK ?= ../tmp/asdk-4.4.7/linux/newlib
CROSS_COMPILE=$(SDK)/bin/asdk-elf-

#########################################################################
# MPU specuific arguments
#########################################################################
ARCH:=arm

CFLAGS += -mcpu=cortex-a9 -g -O0 \
          -mlittle-endian  -DCORTEX_A9_MPCORE -DCORTEX_A9_TC 

LDFLAGS += -mlittle-endian

#########################################################################
# Sources
#########################################################################
PWD := ./ports/$(PORT)
ASM_FILE := crt0.S

C_SOURCE += 

ASM_SOURCE += $(addprefix $(PWD)/, $(ASM_FILE))

PORTLIB += 
#########################################################################
# End
#########################################################################
