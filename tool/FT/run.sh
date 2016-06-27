make distclean;
if [ "$1" = "1195" ]
then
make rtd1195_qa_config;
make;
rm -rf ./1195_ft_spi.bin
cp -rf ./examples/flash_writer_u/dvrboot.exe.bin ./1195_ft_spi.bin
elif [ "$1" = "1095" ]
then
make rtd1095_qa_config;
make ;
rm -rf ./1095_ft_spi.bin
cp -rf ./examples/flash_writer_u/dvrboot.exe.bin ./1095_ft_spi.bin
else
    echo "SPI error !"
fi
