ENTRY(start)

MEMORY
{
         ram0 : org = 0x00000000, len = 0x8000
         ram1 : org = 0x00008000, len = 0x1c000
         ram2 : org = 0x00008000, len = 0x1c000
}

SECTIONS
{	

       	/* program sections */
	.boot 	: 
	{ 
		*(.data.boot);
		_bftext = .;
		*(.text.boot);
		betext = .;
	} >ram0

	.text 	0x00008000: AT(0x00008000) 
	{ 
		_ftext = .;
		*(.text);
		etext = .;
	} >ram2
	. = ALIGN(4);
	__exidx_start = .;
	PROVIDE(__exidx_start = __exidx_start);

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > ram2 /* index entries for section unwinding */

	. = ALIGN(4);
	__exidx_end = .;
	PROVIDE(__exidx_end = __exidx_end);
	.data	: { 
	*(.data) *(.sdata) *(.lit4) *(.lit8) *(.rodata) *(.rodata.*); 
	} > ram2

	.eh_frame : {KEEP(*(.eh_frame))} > ram1

	_gp = .;
	.bss	: 
	{
 
		. = ALIGN(4);
		__bss_start = .; 
		*(.sbss) *(.bss) *(.scommon)
		. = ALIGN(4);
		__bss_end = .; 
	} > ram2

        _end = ALIGN(0x10);
				   
}





