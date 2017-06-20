extern _init_paging32
extern _pml4
extern _kernel_main

bits 32

section .bootstrap
global _entry32
_entry32:
	cli										; No interrupts
	cld										; Index registers increment

check_multiboot:
	cmp eax, 0x36D76289						; Check if we were loaded with multiboot
	je .passed

	hlt										; Multiboot check failed

.passed:
	mov [mb_ptr], ebx						; Store the multiboot info pointer

check_longmode:
	mov eax, 0x80000001
	cpuid
	mov ebp, edx
	
	bt ebp, 29								; Check if long mode is supported
	jc .passed

	hlt										; Long mode check failed so halt

.passed:
	call _init_paging32						; Map kernel pages

enable_paging:
	mov eax, _pml4							; Load PML4
	mov cr3, eax
	
	mov eax, cr4							; Enable PAE
	bts eax, 5
	
	bt ebp, 26								; Check if global pages is supported
	jnc .no_global
	
	bts eax, 7								; Enable global pages
	
.no_global:
	mov cr4, eax
	
enable_longmode:
	mov ecx, 0xC0000080
	rdmsr
	bts eax, 8								; Enable long mode
	
	bt ebp, 20								; Check if NX is supported
	jnc .no_nx

	bts eax, 11								; Enable NX
	
.no_nx:
	wrmsr
	
	mov eax, cr0
	bts eax, 31								; Enable paging
	mov cr0, eax

	lgdt [gdt64.ptr_lo]						; Load GDT using physical address (lower half)
	
	jmp gdt64.code:trampoline64				; Jump to long mode

align 8
mb_ptr:		dq 0							; Pointer to multiboot info

bits 64

trampoline64:
	mov ax, 0								; Long mode ignores data segments so wipe them out
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; RIP is still in lower half so we cannot clean up the paging table just yet
	; We will clean that up after we have jumped into higher half

	mov rbx, [mb_ptr]						; Save multiboot pointer
	mov rax, entry64						; Indirect jump since higher half is out of range
	jmp rax									; Jump to higher half

gdt64:		dq 0
.code:		equ $ - gdt64
			dq 0x20980000000000				; 64-bit, Present, Code Selector
.ptr_lo:	dw $ - gdt64 - 1				; Physical address pointer
			dq gdt64
.ptr_hi:	dw .end - gdt64 - 1				; Linear address pointer
			dq gdt64 + 0xFFFFFFFF80000000

.end:
    
section .text
entry64:
	mov rdi, _pml4							; Zero out lower half of PML4
	mov rax, 0								; Fill with 0
	mov rcx, 512							; Set counter to 512 (256 entries, 64 bits each)
	rep stosd								; Repeat until counter is 0

	invlpg [_pml4]							; Flush PML4

	mov rax, gdt64.ptr_hi					; Load GDT using linear address (higher half)
    add rax, 0xFFFFFFFF80000000				; Page fault will occur if we do not reload using linear address
	lgdt [rax]								; This occurs because we unmap the lower half which the GDT previously used

	mov rsp, stack_top						; Set stack pointer
	mov rdi, rbx							; Pass multiboot pointer as 1st parameter
	jmp _kernel_main						; Parameter order (RDI, RSI, RDX, RCX, R8, R9, stack)

section .bss
stack_bottom:	resb 4096 * 4
stack_top:
