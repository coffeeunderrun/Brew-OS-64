#include <console.h>
#include <cpu.h>
//#include <heap.h>
#include <idt.h>
#include <irq.h>
#include <panic.h>
#include <string.h>

#define MAX_IRQ_HANDLERS		16

/* Structure definitions */
typedef struct irq_callback
{
	irq_t *ptr;
	struct irq_callback *prev;
	struct irq_callback *next;
} irq_callback_t;

/* External function headers */
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();
extern void _irq16();
extern void _irq17();
extern void _irq18();
extern void _irq19();
extern void _irq20();
extern void _irq21();
extern void _irq22();
extern void _irq23();
extern void _irq24();
extern void _irq25();
extern void _irq26();
extern void _irq27();
extern void _irq28();
extern void _irq29();
extern void _irq30();
extern void _irq31();
extern void _irq32();
extern void _irq33();
extern void _irq34();
extern void _irq35();
extern void _irq36();
extern void _irq37();
extern void _irq38();
extern void _irq39();
extern void _irq40();
extern void _irq41();
extern void _irq42();
extern void _irq43();
extern void _irq44();
extern void _irq45();
extern void _irq46();
extern void _irq47();

/* Private variables */
static irq_callback_t irq_callbacks[MAX_IRQ_HANDLERS];

/* Global function implementations */
void init_irq()
{
	idt_set_gate(0, _irq0, IDT_FLG_INT_GATE);
	idt_set_gate(1, _irq1, IDT_FLG_INT_GATE);
	idt_set_gate(2, _irq2, IDT_FLG_INT_GATE);
	idt_set_gate(3, _irq3, IDT_FLG_INT_GATE);
	idt_set_gate(4, _irq4, IDT_FLG_INT_GATE);
	idt_set_gate(5, _irq5, IDT_FLG_INT_GATE);
	idt_set_gate(6, _irq6, IDT_FLG_INT_GATE);
	idt_set_gate(7, _irq7, IDT_FLG_INT_GATE);
	idt_set_gate(8, _irq8, IDT_FLG_INT_GATE);
	idt_set_gate(9, _irq9, IDT_FLG_INT_GATE);
	idt_set_gate(10, _irq10, IDT_FLG_INT_GATE);
	idt_set_gate(11, _irq11, IDT_FLG_INT_GATE);
	idt_set_gate(12, _irq12, IDT_FLG_INT_GATE);
	idt_set_gate(13, _irq13, IDT_FLG_INT_GATE);
	idt_set_gate(14, _irq14, IDT_FLG_INT_GATE);
	idt_set_gate(15, _irq15, IDT_FLG_INT_GATE);
	idt_set_gate(16, _irq16, IDT_FLG_INT_GATE);
	idt_set_gate(17, _irq17, IDT_FLG_INT_GATE);
	idt_set_gate(18, _irq18, IDT_FLG_INT_GATE);
	idt_set_gate(19, _irq19, IDT_FLG_INT_GATE);
	idt_set_gate(20, _irq20, IDT_FLG_INT_GATE);
	idt_set_gate(21, _irq21, IDT_FLG_INT_GATE);
	idt_set_gate(22, _irq22, IDT_FLG_INT_GATE);
	idt_set_gate(23, _irq23, IDT_FLG_INT_GATE);
	idt_set_gate(24, _irq24, IDT_FLG_INT_GATE);
	idt_set_gate(25, _irq25, IDT_FLG_INT_GATE);
	idt_set_gate(26, _irq26, IDT_FLG_INT_GATE);
	idt_set_gate(27, _irq27, IDT_FLG_INT_GATE);
	idt_set_gate(28, _irq28, IDT_FLG_INT_GATE);
	idt_set_gate(29, _irq29, IDT_FLG_INT_GATE);
	idt_set_gate(30, _irq30, IDT_FLG_INT_GATE);
	idt_set_gate(31, _irq31, IDT_FLG_INT_GATE);
	idt_set_gate(32, _irq32, IDT_FLG_INT_GATE);
	idt_set_gate(33, _irq33, IDT_FLG_INT_GATE);
	idt_set_gate(34, _irq34, IDT_FLG_INT_GATE);
	idt_set_gate(35, _irq35, IDT_FLG_INT_GATE);
	idt_set_gate(36, _irq36, IDT_FLG_INT_GATE);
	idt_set_gate(37, _irq37, IDT_FLG_INT_GATE);
	idt_set_gate(38, _irq38, IDT_FLG_INT_GATE);
	idt_set_gate(39, _irq39, IDT_FLG_INT_GATE);
	idt_set_gate(40, _irq40, IDT_FLG_INT_GATE);
	idt_set_gate(41, _irq41, IDT_FLG_INT_GATE);
	idt_set_gate(42, _irq42, IDT_FLG_INT_GATE);
	idt_set_gate(43, _irq43, IDT_FLG_INT_GATE);
	idt_set_gate(44, _irq44, IDT_FLG_INT_GATE);
	idt_set_gate(45, _irq45, IDT_FLG_INT_GATE);
	idt_set_gate(46, _irq46, IDT_FLG_INT_GATE);
	idt_set_gate(47, _irq47, IDT_FLG_INT_GATE);

	//mem_set(&irq_callbacks, 0, sizeof(irq_callback_t) * MAX_IRQ_HANDLERS);
}

void free_irq()
{
	for (int i = 0; i < MAX_IRQ_HANDLERS; i++)
	{
		// Clear any additional callbacks on the heap
		/*		for (irq_callback_t *callback = irq_callbacks[i].next;
				        callback;
				        callback = callback->next)
				{
					heap_free(callback);
				}*/

		// Clear initial callback
		irq_callbacks[i].ptr = NULL;
		irq_callbacks[i].prev = NULL;
		irq_callbacks[i].next = NULL;
	}
}

void irq_add_callback(uint8_t irq, irq_t callback)
{

}

void irq_rem_callback(uint8_t irq, irq_t callback)
{

}

void dump_irq_callbacks()
{

}

/* Called by assembly routine */
void _irq_handler(irq_regs_t regs)
{
	if (regs.irq_no >= MAX_IRQ_HANDLERS)
		return;

	/*	for (irq_callback_t *callback = &irq_callbacks[regs.irq_no];
		        callback && callback->ptr;
		        callback = callback->next)
		{
			(*callback->ptr)(&regs);
		}*/

	switch (regs.irq_no)
	{
	case IRQ_NUM_DIV_BY_ZERO:
	case IRQ_NUM_DEBUG:
	case IRQ_NUM_NON_MASK_INT:
	case IRQ_NUM_BREAKPOINT:
	case IRQ_NUM_OVERFLOW:
	case IRQ_NUM_OUT_OF_BOUNDS:
	case IRQ_NUM_BAD_OPCODE:
	case IRQ_NUM_NO_COPROC:
	case IRQ_NUM_DOUBLE_FAULT:
	case IRQ_NUM_SEG_OVERRUN:
	case IRQ_NUM_BAD_TSS:
	case IRQ_NUM_BAD_SEGMENT:
	case IRQ_NUM_STACK_FAULT:
	case IRQ_NUM_GEN_PROT_FAULT:
	case IRQ_NUM_PAGE_FAULT:
	case IRQ_NUM_RESERVED:
	case IRQ_NUM_COPROC_FAULT:
	case IRQ_NUM_ALIGN_CHECK:
	case IRQ_NUM_MACHINE_CHECK:
	case IRQ_NUM_FLOAT_EX:
	case IRQ_NUM_VIRTUAL_EX:
	case IRQ_NUM_CONTROL_PROT:
	case IRQ_NUM_SYS_CALL:
		panic("== EXCEPTION ==================================================================="
		      "             IRQ                 ERR               FLAGS                 RIP    "
		      "%*016lX    %*016lX    %*016lX    %*016lX    "
		      "             RSI                 RDI                 RBP                 RSP    "
		      "%*016lX    %*016lX    %*016lX    %*016lX    "
		      "             RAX                 RBX                 RCX                 RDX    "
		      "%*016lX    %*016lX    %*016lX    %*016lX    "
		      "              CS                  DS                  SS                        "
		      "%*016lX    %*016lX    %*016lX                        "
		      "================================================================================",
		      regs.irq_no, regs.err_code, regs.eflags, regs.rip,
		      regs.rsi, regs.rdi, regs.rbp, regs.rsp,
		      regs.rax, regs.rbx, regs.rcx, regs.rdx,
		      regs.cs, regs.ds, regs.ss);
		HALT;
		break;
	}

	// Notify PICs that we have hanlded the interrupt
	if (regs.irq_no >= IRQ_PIC_START_1 && regs.irq_no <= IRQ_PIC_END_1)
		out_port(PIC_CONTROL_PORT_1, PIC_END_IRQ);
	else if (regs.irq_no >= IRQ_PIC_START_2 && regs.irq_no <= IRQ_PIC_END_2)
		out_port(PIC_CONTROL_PORT_2, PIC_END_IRQ);
}