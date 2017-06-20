#ifndef __IRQ_H__
#define __IRQ_H__

#include "types.h"

#define IRQ_PIC_START_1			32
#define IRQ_PIC_END_1			39
#define IRQ_PIC_START_2			40
#define IRQ_PIC_END_2			47

#define IRQ_NUM_DIV_BY_ZERO		0			// Divide-by-zero
#define IRQ_NUM_DEBUG			1			// Debug
#define IRQ_NUM_NON_MASK_INT	2			// Non-maskable interrupt
#define IRQ_NUM_BREAKPOINT		3			// Breakpoint
#define IRQ_NUM_OVERFLOW		4			// Into detected overflow
#define IRQ_NUM_OUT_OF_BOUNDS	5			// Out-of-bounds
#define IRQ_NUM_BAD_OPCODE		6			// Invalid opcode
#define IRQ_NUM_NO_COPROC		7			// No coprocessor
#define IRQ_NUM_DOUBLE_FAULT	8			// Double fault
#define IRQ_NUM_SEG_OVERRUN		9			// Coprocessor segment overrun
#define IRQ_NUM_BAD_TSS			10			// Bad TSS
#define IRQ_NUM_BAD_SEGMENT		11			// Segment not present
#define IRQ_NUM_STACK_FAULT		12			// Stack fault
#define IRQ_NUM_GEN_PROT_FAULT	13			// General protection fault
#define IRQ_NUM_PAGE_FAULT		14			// Page fault
#define IRQ_NUM_RESERVED		15			// Reserved
#define IRQ_NUM_COPROC_FAULT	16			// Coprocessor fault
#define IRQ_NUM_ALIGN_CHECK		17			// Alignment check
#define IRQ_NUM_MACHINE_CHECK	18			// Machine check
#define IRQ_NUM_FLOAT_EX		19			// Floating point exception
#define IRQ_NUM_VIRTUAL_EX		20			// Virtualization exception
#define IRQ_NUM_CONTROL_PROT	21			// Control protection exception
#define IRQ_NUM_SYS_CALL		48			// System call

#define IRQ_NUM_PIT				32			// (00) Programmable Interrupt Timer
#define IRQ_NUM_KEYB			33			// (01) Keyboard
#define IRQ_NUM_COM2			35			// (03) Serial 2
#define IRQ_NUM_COM1			36			// (04) Serial 1
#define IRQ_NUM_LPT2			37			// (05) Printer 2
#define IRQ_NUM_FDD				38			// (06) Floppy Disk
#define IRQ_NUM_LPT1			39			// (07) Printer 1
#define IRQ_NUM_RTC				40			// (08) CMOS Real-time clock
#define IRQ_NUM_MOUSE			44			// (12) PS2 Mouse
#define IRQ_NUM_FPU				45			// (13) Math Coprocessor
#define IRQ_NUM_HDD1			46			// (14) Primary Hard Disk
#define IRQ_NUM_HDD2			47			// (15) Secondary Hard Disk

typedef struct irq_regs
{
	uint64_t ds;
	uint64_t rdi, rsi, rbp, rsp, rdx, rcx, rbx, rax;
	uint64_t irq_no, err_code;
	uint64_t rip, cs, eflags, user_esp, ss;
} irq_regs_t;

typedef void(*irq_t)(irq_regs_t *);

void init_irq();

void free_irq();

void irq_add_callback(uint8_t irq, irq_t callback);

void irq_rem_callback(uint8_t irq, irq_t callback);

void dump_irq_callbacks();

#endif // __IRQ_H__