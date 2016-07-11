#!/bin/bash
SCRIPTDIR=$PWD
#TARGETDIR=~/tftp_dir_159.bootcode.fb.201606061950
TARGETDIR=$PWD/out
DVRBOOTEXE=$SCRIPTDIR/examples/flash_writer_u/dvrboot.exe.bin

#
mkdir $PWD/out
#
rm $TARGETDIR/1295_spi_a00_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_spi_a00_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_spi_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_spi_a01_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1296_spi_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_emmc_a00_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_emmc_a00_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_emmc_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1295_emmc_a01_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1296_emmc_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1296_emmc_a01_2ddr4_1GB.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/1296_emmc_a01_4ddr4_2GB.uboot32.fb.dvrboot.exe.bin

# SPI
make distclean;make rtd1295_qa_spi_a00_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_spi_a00_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_spi_a00_2ddr4_2GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_spi_a00_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_spi_a01_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_spi_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_spi_a01_2ddr4_2GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_spi_a01_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1296_qa_spi_a01_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1296_spi_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
# eMMC
make distclean;make rtd1295_qa_emmc_a00_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_emmc_a00_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_emmc_a00_2ddr4_2GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_emmc_a00_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_emmc_a01_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_emmc_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1295_qa_emmc_a01_2ddr4_2GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1295_emmc_a01_2ddr4_2GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1296_qa_emmc_a01_2ddr3_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1296_emmc_a01_2ddr3_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1296_qa_emmc_a01_2ddr4_1GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1296_emmc_a01_2ddr4_1GB.uboot32.fb.dvrboot.exe.bin
#
make distclean;make rtd1296_qa_emmc_a01_4ddr4_2GB_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/1296_emmc_a01_4ddr4_2GB.uboot32.fb.dvrboot.exe.bin
#
ls -l $TARGETDIR/129?_spi_*.bin $TARGETDIR/129?_emmc_*.bin
