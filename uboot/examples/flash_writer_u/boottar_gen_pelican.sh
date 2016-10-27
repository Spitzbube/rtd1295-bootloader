#!/bin/sh
#
#	river.chen@wdc.com
#


CURR=$PWD
BIN_FOLDER="uboot_bins_pelican"
TAR_FILE_NAME="uboot.tar"

HW_SETTING_HEADER="${CURR}/Bind/hwsetting_header.bin"
HW_SETTING="RTD1296_hwsetting_BOOT_2DDR3_4Gb_s1600_all.bin"
HW_SETTING_BIN="${BIN_FOLDER}/hwsetting.bin"

BOOTCODE="uboot_packed_padding.bin"
BOOTCODE_SIG="signature.bin"
BOOTCODE_BIN="${CURR}/Bind/uboot.bin"

FSBL="fsbl_padding.bin"
FSBL_SIG="fsbl_sha256_digest.bin"
FSBL_BIN="${CURR}/Bind/fsbl.bin"

SECURE_OS="fsbl_os_padding.bin"
SECURE_OS_SIG="fsbl_os_sha256_digest.bin"
SECURE_OS_BIN="${CURR}/Bind/fsbl_os.bin"

BL31="bl31_padding.bin"
BL31_SIG="bl31_sha256_digest.bin"
BL31_BIN="${CURR}/Bind/bl31.bin"


echo 

if [ -d ${BIN_FOLDER} ]; then
	echo "Remove all bin files in ${BIN_FOLDER} "
	rm -f ${BIN_FOLDER}/*
else
	echo "Making ${BIN_FOLDER}"
	mkdir -p ${BIN_FOLDER}
fi

if [ ! -e ${HW_SETTING_HEADER} ]; then
	echo "Error: ${BOOTCODE} not found, exit!"
	exit 1;
fi

if [ ! -e ${HW_SETTING} ]; then
	echo "Error: ${HW_SETTING} not found, exit!"
	exit 1;
fi

cat ${HW_SETTING_HEADER} ${HW_SETTING} > ${HW_SETTING_BIN}

if [ -e ${BOOTCODE_BIN} ]; then 
	cp ${BOOTCODE_BIN} $BIN_FOLDER
else
	echo "Error: ${BOOTCODE_BIN} not found, exit!"
	exit 1;
fi
 
 
if [ -e ${FSBL_BIN} ]; then 
	cp ${FSBL_BIN} $BIN_FOLDER
else
	echo "Error: ${FSBL} not found, exit"
	exit 1;
fi 



if [ -e ${SECURE_OS_BIN} ]; then 
	cp ${SECURE_OS_BIN} $BIN_FOLDER
else
	echo "Error: ${SECURE_OS_SIG} not found, exit!" 
	exit 1;
fi 

if [ -e ${BL31_BIN} ]; then 
	cp ${BL31_BIN} $BIN_FOLDER
else
	echo "Error: ${BL31} not found, exit!" 
	exit 1;
fi 




cd ${BIN_FOLDER}
tar -cvf ${TAR_FILE_NAME} *
ls ${TAR_FILE_NAME} -al
cd ${CURR}

