global loader
global reboot
extern main
extern initializeKernelBinary
extern getStackBase

section .text

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get the stack address
	mov rsp, rax				; Set up the stack with the returned address
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang

reboot:
    call getStackBase
    mov rsp, rax
    call main