OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_entry32)
KERNEL_VMA = 0xFFFFFFFF80000000;
SECTIONS
{
	. = 1M;
	_kernel_start = .;
	
	.bootstrap :
	{
		*(.multiboot .bootstrap)
	}
	
	. += KERNEL_VMA;
	.text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VMA)
	{
		*(.text .rodata* .eh_frame)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VMA)
	{
		*(.data)
	}
	
	.bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VMA)
	{
		_kernel_bss = . - KERNEL_VMA;
		*(.bss)
	}

	. = ALIGN(4K);
	_kernel_end = . - KERNEL_VMA;

	/DISCARD/ :
	{
		*(.comment)
	}
}