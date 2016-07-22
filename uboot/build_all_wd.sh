#!/bin/bash
SCRIPTDIR=$PWD
TARGETDIR=$PWD/out
DVRBOOTEXE=$SCRIPTDIR/examples/flash_writer_u/dvrboot.exe.bin

if [ $# == 0 ]
then
    echo "Error, missing argument"
    echo "Usage: $0 [pelican|monarch|all]"
    exit
fi

if [ -d $PWM/out ]
then
    rm -rf $PWM/out
fi

#
mkdir -p $PWD/out

# Monarch
#
if [ ! "$1" = "pelican" ] ;then
    make distclean;make wd_monarch_config;make clean;make
    cp $DVRBOOTEXE      $TARGETDIR/wd_monarch.uboot32.fb.dvrboot.exe.bin
fi
# Pelican
#

if [ ! "$1" = "monarch" ]; then
    make distclean;make wd_pelican_config;make clean;make
    cp $DVRBOOTEXE      $TARGETDIR/wd_pelican.uboot32.fb.dvrboot.exe.bin
fi

ls -l $TARGETDIR/129?_spi_*.bin $TARGETDIR/129?_emmc_*.bin $TARGETDIR/wd_*.bin
