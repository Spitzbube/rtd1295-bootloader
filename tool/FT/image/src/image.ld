SECTIONS
{
    . = 0x80000000;  /*. = 0x81b00000;*/

    .text :{*(.text)}
    .data :{*(.data)}
	.bss :{*(.bss)}
}
