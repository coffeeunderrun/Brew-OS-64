#ifndef __CPU_H__
#define __CPU_H__

#include <types.h>

/* CPU */
#define CR0_PROTECTED_MODE		0x0
#define CR0_WRITE_PROTECT		0x10000
#define CR0_PAGING_ENABLED		0x80000000

#define CR4_PAE_MODE			0x20
#define CR4_GLOBAL_PAGING		0x80

/* Interrupt Controller */
#define PIC_CONTROL_PORT_1		0x20
#define PIC_DATA_PORT_1			0x21
#define PIC_CONTROL_PORT_2		0xA0
#define PIC_DATA_PORT_2			0xA1
#define PIC_END_IRQ				0x20

#define ICW1					0x11
#define ICW2_MASTER				0x20
#define ICW2_SLAVE				0x28
#define ICW3_MASTER				0x04
#define ICW3_SLAVE				0x02
#define ICW4					0x01

/* Text Mode */
#define VGA_STATUS_PORT			0x3DA

#define VGA_CRTC_ADDR_PORT		0x3D4
#define VGA_CRTC_DATA_PORT		0x3D5
#define VGA_CURSOR_POS_HI_IDX	0x0E
#define VGA_CURSOR_POS_LO_IDX	0x0F

#define VGA_ATTR_ADDR_PORT		0x3C0
#define VGA_ATTR_DATA_PORT		0x3C0
#define VGA_ATTR_PAS			0x30
#define VGA_ATTR_CONTROL_IDX	0x10
#define VGA_ATTR_BLINK			0x08

#define DISABLE_INTERRUPTS		__asm__("cli;")
#define ENABLE_INTERRUPTS		__asm__("sti;")
#define HALT					__asm__("hlt;")

inline uint8_t in_port(uint16_t port)
{
	uint8_t val;

	__asm__ __volatile__(
	    "inb al, dx;"
	    : "=a" (val)
	    : "d" (port));

	return val;
}

inline void out_port(uint16_t port, uint8_t val)
{
	__asm__ __volatile__(
	    "outb dx, al;"
	    :
	    : "d" (port), "a" (val));
}

inline void load_idt(void *p)
{
	__asm__ __volatile__(
	    "mov rax, %0;"
	    "lidt [rax];"
	    :
	    : "m" (p)
	    : "rax");
}

#endif // __CPU_H__
