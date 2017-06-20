#include <cpu.h>
#include <idt.h>
#include <irq.h>
#include <string.h>

#define IDT_ENTRIES 256

/* Structure definitions */
typedef struct idt_entry
{
	uint16_t base_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_mid;
	uint32_t base_high;
	uint32_t reserved;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) idt_ptr_t;

/* Private variables */
static idt_entry_t _idt[IDT_ENTRIES];
static idt_ptr_t _idt_ptr;

/* Private function headers */
static void init_pics();

/* Global function implementations */
void init_idt()
{
	init_pics();

	// Clear memory for IDT
	mem_set(&_idt, 0, sizeof(idt_entry_t) * IDT_ENTRIES);
	mem_set(&_idt_ptr, 0, sizeof(idt_ptr_t));

	// Add interrupt handler entries to IDT
	init_irq();

	// Set pointer to IDT
	_idt_ptr.base = (uint64_t)&_idt;
	_idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;

	load_idt(&_idt_ptr);
}

void free_idt()
{
	free_irq();
}

void idt_set_gate(uint8_t idx, void *p, uint8_t flags)
{
	_idt[idx].base_low = (uint64_t)p & 0xFFFF;
	_idt[idx].base_mid = ((uint64_t)p >> 16) & 0xFFFF;
	_idt[idx].base_high = ((uint64_t)p >> 32) & 0xFFFFFFFF;

	_idt[idx].selector = 0x08;

	// Bits 1-3 and 7 must be on, bit 4 must be off
	_idt[idx].flags = (flags | 0x8E) & 0xEF;

	_idt[idx].zero = 0;
	_idt[idx].reserved = 0;
}

static void init_pics()
{
	// Initialize PICs
	out_port(PIC_CONTROL_PORT_1, ICW1);
	out_port(PIC_CONTROL_PORT_2, ICW1);

	// Remap PICs as first 32 interrupts are reserved
	out_port(PIC_DATA_PORT_1, ICW2_MASTER);
	out_port(PIC_DATA_PORT_2, ICW2_SLAVE);

	// Cascading
	out_port(PIC_DATA_PORT_1, ICW3_MASTER);
	out_port(PIC_DATA_PORT_2, ICW3_SLAVE);

	// Environment info
	out_port(PIC_DATA_PORT_1, ICW4);
	out_port(PIC_DATA_PORT_2, ICW4);

	// Mask interrupts
	out_port(PIC_DATA_PORT_1, 0x0);
	out_port(PIC_DATA_PORT_2, 0x0);
}