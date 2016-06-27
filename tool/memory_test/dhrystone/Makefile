#########################################################################
# default setting
#########################################################################
PORT ?= sheipa-3.x-arm

CFLAGS :=
ASFLAGS :=
LDFLAGS :=

C_SOURCE :=
ASM_SOURCE :=

# object directories
OBJ_DIR=.

PORTLIB :=
# board specific setting
include ./ports/$(PORT)/port.mak

#########################################################################
# MPU specuific arguments
#########################################################################
CC=$(CROSS_COMPILE)gcc
ASM=$(CC)
OBJDUMP=$(CROSS_COMPILE)objdump
OBJCOPY=$(CROSS_COMPILE)objcopy
LD=$(CROSS_COMPILE)gcc

CFLAGS += -c -O2  -Wall 
ASFLAGS += $(CFLAGS)
LDFLAGS += -nostartfiles -N -n  -Wl,--start-group -lc -lgcc $(PORTLIB) -Wl,--end-group
IFLAGS += -I. -I./target

#########################################################################
# Sources
#########################################################################
C_SOURCE += dhry21a.c dhry21b.c cstub.c strcmp.c

#########################################################################
# VPATH
#########################################################################
vpath %.o .:./target:$(OBJ_DIR)
vpath %.o .:./target

#########################################################################
# Objects
#########################################################################
C_OBJS := $(addprefix $(OBJ_DIR)/, $(C_SOURCE:.c=.o))
ASM_OBJS := $(addprefix $(OBJ_DIR)/, $(ASM_SOURCE:.S=.o))
BIN_NAME := dhry-$(PORT)
LINK_MAP=$(BIN_NAME).map

#########################################################################
# D flags
#########################################################################
DFLAGS =  -DDISABLE_MALLOC -DTIMER_STUB -DNUMBER_OF_RUNS=30000

#########################################################################
# Rules
#########################################################################
.PHONY: all clean portpath

all: portpath $(OBJ_DIR)/$(BIN_NAME).elf 

portpath:
	-rm target
	ln -s ports/$(PORT) target

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS)  $< -o $@

#$(OBJ_DIR)/cstub.o: cstub.c
#	$(CC) $(CFLAGS) -msoft-float $(DFLAGS) $(IFLAGS)  $< -o $@

$(OBJ_DIR)/%.o: %.S
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@

$(OBJ_DIR)/$(BIN_NAME).elf: $(C_OBJS) $(ASM_OBJS)
	$(LD) $^ -T ./target/link.ld  -o $(OBJ_DIR)/$(BIN_NAME).elf \
            $(LDFLAGS) -Wl,-Map,$(OBJ_DIR)/$(LINK_MAP) 
	$(OBJDUMP) -DS $(BIN_NAME).elf > $(BIN_NAME).text
	$(OBJCOPY) -O binary $(BIN_NAME).elf  $(BIN_NAME).bin

clean:
	-rm -f $(OBJ_DIR)/*.o
	-rm -f $(OBJ_DIR)/*.elf
	-rm -f $(OBJ_DIR)/*.map
	-rm -f $(OBJ_DIR)/*.text
	-rm -f $(OBJ_DIR)/*.bin
	-rm -f $(OBJ_DIR)/target/*.o
	-rm -f target

#########################################################################
# End
#########################################################################
