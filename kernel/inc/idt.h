#ifndef __IDT_H__
#define __IDT_H__

#include "types.h"

#define IDT_FLG_PRESENT			(1 << 7)
#define IDT_FLG_RING_0			(0 << 5)
#define IDT_FLG_RING_1			(1 << 5)
#define IDT_FLG_RING_2			(2 << 5)
#define IDT_FLG_RING_3			(3 << 5)
#define IDT_FLG_INT_GATE		(0 << 0)
#define IDT_FLG_TRAP_GATE		(1 << 0)

void init_idt();

void free_idt();

void idt_set_gate(uint8_t idx, void *p, uint8_t flags);

#endif // __IDT_H__