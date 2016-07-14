#!/bin/bash
SCRIPTDIR=$PWD
#TARGETDIR=~/tftp_dir_159.bootcode.fb.201606061950
TARGETDIR=$PWD/out
DVRBOOTEXE=$SCRIPTDIR/examples/flash_writer_u/dvrboot.exe.bin

#
mkdir $PWD/out
#
rm $TARGETDIR/wd_monarch.uboot32.fb.dvrboot.exe.bin
rm $TARGETDIR/wd_pelican.uboot32.fb.dvrboot.exe.bin

# Monarch
#
make distclean;make wd_monarch_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/wd_monarch.uboot32.fb.dvrboot.exe.bin
# Pelican
#
make distclean;make wd_pelican_config;make clean;make
cp $DVRBOOTEXE      $TARGETDIR/wd_pelican.uboot32.fb.dvrboot.exe.bin


ls -l $TARGETDIR/129?_spi_*.bin $TARGETDIR/129?_emmc_*.bin $TARGETDIR/wd_*.bin
