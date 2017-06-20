extern _irq_handler

bits 64

section .text
%macro push_all 0
	push rax

	mov rax, rsp							; Save current stack pointer
	add rax, 8								; We want the stack pointer before the previous push

	push rbx
	push rcx
	push rdx
	
	push rax								; Push the saved stack pointer

	push rbp
	push rsi
	push rdi
%endmacro

%macro pop_all 0
	pop rdi
	pop rsi
	pop rbp

	add rsp, 8								; Trash the saved stack pointer

	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro IRQ 0
	push_all

	mov ax, ds
	push rax

	call _irq_handler

	pop rax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	pop_all

	add rsp, 16					; Trash the IRQ and interrupt number still on stack
%endmacro

%macro IRQ_NOERRCODE 2
global _irq%1
_irq%1:
	cli

	push qword %2				; Store code
	push qword %1				; Store interrupt number

	IRQ

	sti
	iretq
%endmacro

%macro IRQ_ERRCODE 1
global _irq%1
_irq%1:
	cli

	push qword %1				; Store interrupt number

	IRQ

	sti
	iretq
%endmacro

; Software interrupts
IRQ_ERRCODE 8
IRQ_ERRCODE 10
IRQ_ERRCODE 11
IRQ_ERRCODE 12
IRQ_ERRCODE 13
IRQ_ERRCODE 14

IRQ_NOERRCODE 0, 0
IRQ_NOERRCODE 1, 0
IRQ_NOERRCODE 2, 0
IRQ_NOERRCODE 3, 0
IRQ_NOERRCODE 4, 0
IRQ_NOERRCODE 5, 0
IRQ_NOERRCODE 6, 0
IRQ_NOERRCODE 7, 0
IRQ_NOERRCODE 9, 0
IRQ_NOERRCODE 15, 0
IRQ_NOERRCODE 16, 0
IRQ_NOERRCODE 17, 0
IRQ_NOERRCODE 18, 0
IRQ_NOERRCODE 19, 0
IRQ_NOERRCODE 20, 0
IRQ_NOERRCODE 21, 0
IRQ_NOERRCODE 22, 0
IRQ_NOERRCODE 23, 0
IRQ_NOERRCODE 24, 0
IRQ_NOERRCODE 25, 0
IRQ_NOERRCODE 26, 0
IRQ_NOERRCODE 27, 0
IRQ_NOERRCODE 28, 0
IRQ_NOERRCODE 29, 0
IRQ_NOERRCODE 30, 0
IRQ_NOERRCODE 31, 0

; Hardware interrupts
IRQ_NOERRCODE 32, 0
IRQ_NOERRCODE 33, 1
IRQ_NOERRCODE 34, 2
IRQ_NOERRCODE 35, 3
IRQ_NOERRCODE 36, 4
IRQ_NOERRCODE 37, 5
IRQ_NOERRCODE 38, 6
IRQ_NOERRCODE 39, 7
IRQ_NOERRCODE 40, 8
IRQ_NOERRCODE 41, 9
IRQ_NOERRCODE 42, 10
IRQ_NOERRCODE 43, 11
IRQ_NOERRCODE 44, 12
IRQ_NOERRCODE 45, 13
IRQ_NOERRCODE 46, 14
IRQ_NOERRCODE 47, 15
