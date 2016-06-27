ENTRY(start)

MEMORY
{
         boot : org = 0x00000000, len = 0x8000
         ram0 : org = 0x80008000, len = 0x10000
}

SECTIONS
{	

       	/* program sections */
	.boot :
	{ 
		*(.boot.data);
		*(.boot.text);
	} > boot

	.text 0x80008000: AT(0x00008000)
	{ 
		_ftext = .;
		*(.text);
		*(.text.*);
		etext = .;
	} > ram0
	. = ALIGN(4);
	__exidx_start = .;
	PROVIDE(__exidx_start = __exidx_start);

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > ram0 /* index entries for section unwinding */

	. = ALIGN(4);
	__exidx_end = .;
	PROVIDE(__exidx_end = __exidx_end);
	.data	: { 
	*(.data) *(.sdata) *(.lit4) *(.lit8) *(.rodata) *(.rodata.*); 
	} > ram0

	.eh_frame : {KEEP(*(.eh_frame))} > ram0

	_gp = .;
	.bss	: 
	{
 
		. = ALIGN(4);
		__bss_start = .; 
		*(.sbss) *(.bss) *(.scommon)
		. = ALIGN(4);
		__bss_end = .; 
	} > ram0

        _end = ALIGN(0x10);
				   
}





