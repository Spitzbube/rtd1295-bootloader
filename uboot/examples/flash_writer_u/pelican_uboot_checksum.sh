#!/bin/sh
#
#	river.chen@wdc.com
#


CURR=$PWD

HW_SETTING_HEADER="${CURR}/Bind/hwsetting_header.bin"
HW_SETTING_BIN="${CURR}/Bind/hwsetting.bin"

HW_SETTING_COMBINED="hwsetting_combined.bin"
HW_SETTING_CHECKSUM="hwsetting_checksum.bin"

UBOOT_BIN="${CURR}/Bind/uboot.bin"
UBOOT_CHECKSUM="uboot_checksum.bin"

FSBL_BIN="${CURR}/Bind/fsbl.bin"
FSBL_CHECKSUM="fsbl_checksum.bin"

SECURE_OS_BIN="${CURR}/Bind/fsbl_os.bin"
SECURE_OS_CHECKSUM="fsbl_os_checksum.bin"

BL31_BIN="${CURR}/Bind/bl31.bin"
BL31_CHECKSUM="bl31_checksum.bin"

UBOOT64_BIN="${CURR}/Bind/uboot64.bin"
UBOOT64_CHECKSUM="uboot64_checksum.bin"

ALIGNEDMENT=512

BOOTCODE_CHECKSUM="bootcode_checksum.bin"


if [ -e ${UBOOT64_CHECKSUM} ]; then 
	rm ${UBOOT64_CHECKSUM}
fi

if [ -e ${BOOTCODE_CHECKSUM} ]; then 
	rm ${BOOTCODE_CHECKSUM}
fi

##### Generate hwsetting_checksum.bin #####
cat ${HW_SETTING_HEADER} ${HW_SETTING_BIN} > ${HW_SETTING_COMBINED}
if [ -e ${HW_SETTING_COMBINED} ]; then 
	HW_SETTING_COMBINED_BIN_SIZE=$(stat -c%s "${HW_SETTING_COMBINED}")
	#echo "hwsetting_combined.bin size = $HW_SETTING_COMBINED_BIN_SIZE bytes."
	BLOCK_SIZE=$(((HW_SETTING_COMBINED_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $HW_SETTING_CHECKSUM
	dd if=$HW_SETTING_COMBINED of=$HW_SETTING_CHECKSUM conv=notrunc

else
	echo "Error: ${HW_SETTING_COMBINED_BIN_SIZE} not found, exit!" 
	exit 1;
fi 

##### Generate uboot_checksum.bin #####
if [ -e ${UBOOT_BIN} ]; then 
	UBOOT_BIN_SIZE=$(stat -c%s "${UBOOT_BIN}")
	#echo "uboot.bin size = $BOOTCODE_BIN_SIZE bytes."
	BLOCK_SIZE=$(((UBOOT_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $UBOOT_CHECKSUM
	dd if=$UBOOT_BIN of=$UBOOT_CHECKSUM conv=notrunc

else
	echo "Error: ${UBOOT_BIN} not found, exit!" 
	exit 1;
fi 

##### Generate fsbl_checksum.bin #####
if [ -e ${FSBL_BIN} ]; then 
	FSBL_BIN_SIZE=$(stat -c%s "${FSBL_BIN}")
	#echo "fsbl.bin size = $FSBL_BIN_SIZE bytes."
	BLOCK_SIZE=$(((FSBL_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $FSBL_CHECKSUM
	dd if=$FSBL_BIN of=$FSBL_CHECKSUM conv=notrunc

else
	echo "Error: ${FSBL_BIN} not found, exit!" 
	exit 1;
fi 

##### Generate fsbl_os_checksum.bin #####
if [ -e ${SECURE_OS_BIN} ]; then 
	SECURE_OS_BIN_SIZE=$(stat -c%s "${SECURE_OS_BIN}")
	#echo "fsbl_os.bin size = $SECURE_OS_BIN_SIZE bytes."
	BLOCK_SIZE=$(((SECURE_OS_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $SECURE_OS_CHECKSUM
	dd if=$SECURE_OS_BIN of=$SECURE_OS_CHECKSUM conv=notrunc

else
	echo "Error: ${SECURE_OS_BIN} not found, exit!" 
	exit 1;
fi 

##### Generate bl31_checksum.bin #####
if [ -e ${BL31_BIN} ]; then 
	BL31_BIN_SIZE=$(stat -c%s "${BL31_BIN}")
	#echo "bl31.bin size = $BL31_BIN_SIZE bytes."
	BLOCK_SIZE=$(((BL31_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $BL31_CHECKSUM
	dd if=$BL31_BIN of=$BL31_CHECKSUM conv=notrunc

else
	echo "Error: ${BL31_BIN} not found, exit!" 
	exit 1;
fi 

cat ${HW_SETTING_CHECKSUM} ${UBOOT_CHECKSUM} ${FSBL_CHECKSUM} ${SECURE_OS_CHECKSUM} ${BL31_CHECKSUM} > ${BOOTCODE_CHECKSUM}


##### Generate uboot64_padding.bin #####
if [ -e ${UBOOT64_BIN} ]; then 
	UBOOT64_BIN_SIZE=$(stat -c%s "$UBOOT64_BIN")
	#echo "uboot64.bin size = $UBOOT64_BIN_SIZE bytes."
	BLOCK_SIZE=$(((UBOOT64_BIN_SIZE + ALIGNEDMENT - 1) / ALIGNEDMENT))
	#echo $BLOCK_SIZE

	ALIGNED_SIZE=$((BLOCK_SIZE * ALIGNEDMENT))
	echo $ALIGNED_SIZE

	dd if=/dev/zero ibs=1 count=$ALIGNED_SIZE | tr "\000" "\377" > $UBOOT64_CHECKSUM
	dd if=$UBOOT64_BIN of=$UBOOT64_CHECKSUM conv=notrunc

else
	echo "Error: ${UBOOT64_BIN} not found, exit!" 
	exit 1;
fi
