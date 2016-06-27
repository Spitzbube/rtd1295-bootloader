#########################################################################
# default setting
#########################################################################
MSDK=/home/STools/RLX/msdk-4.3.5/linux/newlib 

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
include ./arch/$(ARCH)/arch.mak
LINK_SCR = ./ports/$(PORT)/link.ld

#########################################################################
# MPU specuific arguments
#########################################################################
CC=$(CROSS_COMPILE)gcc
ASM=$(CC)
OBJDUMP=$(CROSS_COMPILE)objdump
OBJCOPY=$(CROSS_COMPILE)objcopy
LD=$(CROSS_COMPILE)gcc

CFLAGS += -c -Wall 
ASFLAGS += $(CFLAGS)
LDFLAGS += -nostartfiles -N -n -Wl,--start-group -lc -lgcc $(PORTLIB) -Wl,--end-group -Wl
IFLAGS += -I. -I./target -I./arch/$(ARCH)

#########################################################################
# Sources
#########################################################################
C_SOURCE += ddr_random.c cstub.c ddr_ctrl.c

ASM_SOURCE +=

#########################################################################
# VPATH
#########################################################################
vpath %.o .:./target:./arch/$(ARCH):$(OBJ_DIR)
vpath %.S .:./ports/$(PORT)

#########################################################################
# Objects
#########################################################################
C_OBJS := $(addprefix $(OBJ_DIR)/, $(C_SOURCE:.c=.o))
ASM_OBJS := $(addprefix $(OBJ_DIR)/, $(ASM_SOURCE:.S=.o))
#TEST1_NAME := marchx
TEST2_NAME := ddr_random_5sec
TEST3_NAME := ddr_random_1min
TEST4_NAME := ddr_random_10min
TEST5_NAME := ddr_random_1hr
TEST7_NAME := hello

#########################################################################
# D flags
#########################################################################
DFLAGS =

#########################################################################
# Rules
#########################################################################
.PHONY: all clean portpath print

all: portpath $(OBJ_DIR)/$(TEST2_NAME).elf $(OBJ_DIR)/$(TEST3_NAME).elf $(OBJ_DIR)/$(TEST4_NAME).elf $(OBJ_DIR)/$(TEST5_NAME).elf

portpath:
	-rm target
	ln -s ports/$(PORT) target

ddr_random_5sec.o: ddr_random.c
	$(CC) $(CFLAGS) $(DFLAGS) -DTEST_TIME_5SEC $(IFLAGS)  $< -o $@

ddr_random_1min.o: ddr_random.c
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS)  $< -o $@

ddr_random_10min.o: ddr_random.c
	$(CC) $(CFLAGS) $(DFLAGS) -DTEST_TIME_10MIN $(IFLAGS)  $< -o $@

ddr_random_1hr.o: ddr_random.c
	$(CC) $(CFLAGS) $(DFLAGS) -DTEST_TIME_1HR $(IFLAGS)  $< -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS)  $< -o $@

$(OBJ_DIR)/%.o: %.S
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@


#$(OBJ_DIR)/$(TEST1_NAME).elf:$(ASM_OBJS) $(TEST1_NAME).o cstub.o ddr_ctrl.o
#	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST1_NAME).elf \
#            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST1_NAME).map
#	$(OBJDUMP) -DS $(TEST1_NAME).elf > $(TEST1_NAME).text
#	$(OBJCOPY) -O binary $(TEST1_NAME).elf  $(TEST1_NAME).bin

$(OBJ_DIR)/$(TEST2_NAME).elf:$(ASM_OBJS) $(TEST2_NAME).o cstub.o ddr_ctrl.o arch/$(ARCH)/cpu.o
	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST2_NAME).elf \
            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST2_NAME).map
	$(OBJDUMP) -DS $(TEST2_NAME).elf > $(TEST2_NAME).text
	$(OBJCOPY) -O binary $(TEST2_NAME).elf  $(TEST2_NAME).bin

$(OBJ_DIR)/$(TEST3_NAME).elf:$(ASM_OBJS) $(TEST3_NAME).o cstub.o ddr_ctrl.o arch/$(ARCH)/cpu.o
	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST3_NAME).elf \
            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST3_NAME).map
	$(OBJDUMP) -DS $(TEST3_NAME).elf > $(TEST3_NAME).text
	$(OBJCOPY) -O binary $(TEST3_NAME).elf  $(TEST3_NAME).bin

$(OBJ_DIR)/$(TEST4_NAME).elf:$(ASM_OBJS) $(TEST4_NAME).o cstub.o ddr_ctrl.o arch/$(ARCH)/cpu.o
	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST4_NAME).elf \
            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST4_NAME).map
	$(OBJDUMP) -DS $(TEST4_NAME).elf > $(TEST4_NAME).text
	$(OBJCOPY) -O binary $(TEST4_NAME).elf  $(TEST4_NAME).bin

$(OBJ_DIR)/$(TEST5_NAME).elf:$(ASM_OBJS) $(TEST5_NAME).o cstub.o ddr_ctrl.o arch/$(ARCH)/cpu.o
	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST5_NAME).elf \
            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST5_NAME).map
	$(OBJDUMP) -DS $(TEST5_NAME).elf > $(TEST5_NAME).text
	$(OBJCOPY) -O binary $(TEST5_NAME).elf  $(TEST5_NAME).bin

$(OBJ_DIR)/$(TEST7_NAME).elf:$(ASM_OBJS) $(TEST7_NAME).o cstub.o ddr_ctrl.o arch/$(ARCH)/cpu.o
	$(LD) $^ -T $(LINK_SCR)  -o $(OBJ_DIR)/$(TEST7_NAME).elf \
            $(LDFLAGS),-Map,$(OBJ_DIR)/$(TEST7_NAME).map
	$(OBJDUMP) -DS $(TEST7_NAME).elf > $(TEST7_NAME).text
	$(OBJCOPY) -O binary $(TEST7_NAME).elf  $(TEST7_NAME).bin


clean:
	-rm -f $(OBJ_DIR)/*.o
	-rm -f $(OBJ_DIR)/*.elf
	-rm -f $(OBJ_DIR)/*.map
	-rm -f $(OBJ_DIR)/*.text
	-rm -f $(OBJ_DIR)/*.bin
	-rm -f $(OBJ_DIR)/target/*.o
	-rm -f $(OBJ_DIR)/arch/$(ARCH)/*.o
	-rm -f target
print:
	echo ./ports/$(PORT)

#########################################################################
# End
#########################################################################
