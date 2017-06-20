bits 32

section .bootstrap
global _init_paging32
_init_paging32:
	mov edi, _pml4							; Zero out PML4
	mov eax, 0								; Fill with 0
	mov ecx, 1024							; Set counter to 1024 (512 entries, 64 bits each)
	rep stosd								; Repeat until counter is 0

	mov edi, _pml4 + 4072					; Entry 509
	mov eax, _pml4							; Point to PML4 for recursion
	or eax, 0x3								; Present and writable
	stosd

	mov edi, _pml4							; Start at first entry for lower half
	mov eax, _pml3							; First entry points to PML3
	or eax, 0x3								; Present and writable
	stosd									; Store entry

	mov edi, _pml4 + 4088					; Entry 511 (-512GB)
	stosd									; Store entry

	; Both entries point to the same physical address. We want to keep the
	; upper half from now on but the lower half is only important until we
	; jump to 64 bit code.
	
map_pml3:
	mov edi, _pml3							; Zero out PML3
	mov eax, 0								; Fill with 0
	mov ecx, 1024							; Set counter to 1024 (512 entries, 64 bits each)
	rep stosd								; Repeat until counter is 0

	mov edi, _pml3 + 4072					; Entry 509
	mov eax, _pml3							; Point to PML3 for recursion
	or eax, 0x3								; Present and writable
	stosd

	mov edi, _pml3							; Start at first entry in PML3
	mov eax, _pml2							; First entry points to PML2
	or eax, 0x3								; Present and writable
	stosd									; Store entry

	mov edi, _pml3 + 4080					; Entry 510 (-2GB)
	stosd									; Store entry

map_pml2:
	mov edi, _pml2							; Zero out PML2
	mov eax, 0								; Fill with 0
	mov ecx, 1024							; Set counter to 1024 (512 entries, 64 bits each)
	rep stosd								; Repeat until counter is 0

	mov edi, _pml2 + 4072					; Entry 509
	mov eax, _pml2							; Point to PML2 for recursion
	or eax, 0x3								; Present and writable
	stosd

	mov edi, _pml2							; Start at first entry in PML2
	mov eax, 0								; Start at first physical frame
	or eax, 0x83							; Present, writable, and large pages (2MB)
	xor ebx, ebx							; Clear upper half of physical frame pointer
	xor edx, edx							; Clear temp storage
	mov ecx, 64								; 64 * 2MB = 128 MB total
.loop:
	stosd									; Lower half of physical frame pointer (bits 0-31)
	xchg eax, edx							; Save current frame pointer
	stosd									; Upper half of physical frame pointer (bits 32-63)
	xchg eax, edx							; Load current frame pointer
	add eax, 0x200000						; Point to next 2MB physical frame
	adc edx, ebx							; Increase upper half if lower half wraps at 4GB
	loop .loop

	ret

align 4096
global _pml4
_pml4:		times 4096 db 0

global _pml3
_pml3:		times 4096 db 0

global _pml2
_pml2:		times 4096 db 0
