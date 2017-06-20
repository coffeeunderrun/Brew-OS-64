#include <cpu.h>
#include <idt.h>
#include <kernel.h>
#include <multiboot.h>
#include <string.h>

/* External variables */
extern uint64_t _build_date, _build_number;

/* Private function headers */
static void do_welcome();
static void parse_mb_info(struct multiboot_tag *tag);

/* Global function implementations */
void _kernel_main(uint64_t mb)
{
	// Initialize console
	init_con();

	// Initialize interrupts
	init_idt();

	do_welcome();

	int t1 = 0;
	int t2 = 1 / t1;

	ENABLE_INTERRUPTS;

	while (1);
}

/* Private function implementations */
static void do_welcome()
{
	char buf1[32], buf2[32];

	con_write_fmt("Welcome to BrewOS! Build %u-%u x64\n",
		&_build_date, &_build_number);

	con_write_ln("Copyright (C) 2015-2017 by Jamie Plude\n");

	/*	con_write_fmt("Mem:  &G%* 7s / %* 7s&x\n",
					  unit_fmt(buf1, pmem_get_free(), UNIT_MAX),
					  unit_fmt(buf2, pmem_get_total(), UNIT_MAX));

		con_write_fmt("Heap: &R%* 7s / %* 7s&x\n",
					  unit_fmt(buf1, heap_get_free(), UNIT_MAX),
					  unit_fmt(buf2, heap_get_total(), UNIT_MAX));*/
}

static void parse_mb_info(struct multiboot_tag *tag)
{
	// Iterate through all tags (last tag should be an END type)
	while (tag->type != MULTIBOOT_TAG_TYPE_END)
	{
		switch (tag->type)
		{
		case MULTIBOOT_TAG_TYPE_MMAP:		// Initialize physical memory manager
			//init_pmem(tag);
			break;
		}

		// Move tag pointer to the next tag
		tag = (struct multiboot_tag *)
			((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7));
	}
}