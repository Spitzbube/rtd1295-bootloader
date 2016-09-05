#!/bin/bash

### Change TOOLCHAIN_PATH to your configuration before running this script 
TOOLCHAIN_PATH=/home/rivers/projects/firmware_updater/firmware_update/toolchain/asdk-4.8.1-a7-EL-3.10-0.9.33-a32nt-130828/bin
PWD=$(pwd)

if [ -f $PWD/tools/env/fw_printenv ]
then
	echo "Removing $PWD/tools/env/fw_printenv"	
    	rm $PWD/tools/env/fw_printenv
fi

make HOSTCC=$TOOLCHAIN_PATH/arm-linux-gcc HOSTSTRIP=$TOOLCHAIN_PATH/arm-linux-strip env
