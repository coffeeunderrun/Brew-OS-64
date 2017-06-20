#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <console.h>
#include <cpu.h>

#define KERNEL_VMA				0xFFFFFFFF80000000

#define	ASSERT(expr)			if (!expr) { \
								panic("Assertion failed. System halted."); \
								DISABLE_INTERRUPTS; \
								HALT; }

#endif // __KERNEL_H__
