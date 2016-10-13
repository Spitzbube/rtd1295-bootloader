#!/bin/sh
#
#	river.chen@wdc.com
#


CURR=$PWD
BIN_FOLDER="uboot_bins"
TAR_FILE_NAME="uboot.tar"

HW_SETTING_HEADER="${CURR}/Bind/hwsetting_header.bin"
HW_SETTING="RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1600_DDRSS_all.bin"
BOOTCODE="uboot_packed_padding.bin"
BOOTCODE_SIG="signature.bin"
FSBL="fsbl_padding.bin"
FSBL_SIG="fsbl_sha256_digest.bin"
BL31="bl31_padding.bin"
BL31_SIG="bl31_sha256_digest.bin"
BOOTCODE64="${CURR}/bootimage/u-boot64.bin"

if [ -d ${BIN_FOLDER} ]; then
	echo "Remove all bin files in ${BIN_FOLDER} "
	rm -f ${BIN_FOLDER}/*
else
	echo "Making ${BIN_FOLDER}"
	mkdir -p ${BIN_FOLDER}
fi

if [ -e ${HW_SETTING_HEADER} ]; then 
	cp ${HW_SETTING_HEADER} $BIN_FOLDER
else
	echo "Error: ${HW_SETTING_HEADER} not found, exit!"
	exit 1;
fi 

if [ -e ${HW_SETTING} ]; then 
	cp ${HW_SETTING} $BIN_FOLDER
else
	echo "Error: ${HW_SETTING} not found, exit!"
	exit 1;
fi 

if [ -e ${BOOTCODE} ]; then 
	cp ${BOOTCODE} $BIN_FOLDER
else
	echo "Error: ${BOOTCODE} not found, exit!"
	exit 1;
fi
 
if [ -e ${BOOTCODE_SIG} ]; then 
	cp ${BOOTCODE_SIG} $BIN_FOLDER
else
	echo "Error: ${BOOTCODE_SIG} not found, exit!"
	exit 1;
fi
 
if [ -e ${FSBL} ]; then 
	cp ${FSBL} $BIN_FOLDER
else
	echo "Error: ${FSBL} not found, exit"
	exit 1;
fi 

if [ -e ${FSBL_SIG} ]; then 
	cp ${FSBL_SIG} $BIN_FOLDER
else
	echo "Error: ${FSBL_SIG} not found, exit!" 
	exit 1;
fi 

if [ -e ${BL31} ]; then 
	cp ${BL31} $BIN_FOLDER
else
	echo "Error: ${BL31} not found, exit!" 
	exit 1;
fi 

if [ -e ${BL31_SIG} ]; then 
	cp ${BL31_SIG} $BIN_FOLDER
else
	echo "Error: ${BL31_SIG} not found, exit!" 
	exit 1;
fi 

if [ -e ${BOOTCODE64} ]; then 
	cp ${BOOTCODE64} $BIN_FOLDER
else
	echo "Error: ${BOOTCODE64} not found, exit!" 
	exit 1;
fi

cd ${BIN_FOLDER}
tar -cvf ${TAR_FILE_NAME} *
ls ${TAR_FILE_NAME} -al
cd ${CURR}

