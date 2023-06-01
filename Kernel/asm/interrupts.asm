GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL _syscallHandler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher


SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1

    push rax

    mov [regs], rax
    mov [regs+8], rbx
    mov [regs+8*2], rcx
    mov [regs+8*3], rdx
    mov [regs+8*4], rsi
    mov [regs+8*5], rdi
    mov [regs+8*6], r8
    mov [regs+8*7], r9
    mov [regs+8*8], r10
    mov [regs+8*9], r11
    mov [regs+8*10], r12
    mov [regs+8*11], r13
    mov [regs+8*12], r14
    mov [regs+8*13], r15
    mov [regs+8*14], rbp
    mov rax, rsp
    add rax, 8*6
    mov [regs+8*15], rax ;rsp previo
    mov rax, [rsp+8]
    mov [regs+8*16], rax ;rip previo
    ;TODO: revisar que rsp y rip esten bien
    pop rax
    pushState

	mov rdi, %1
	mov rsi, regs
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret




picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn




;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5



;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Opcode Exception
_exception6Handler:
    exceptionHandler 6



;System Calls
_syscallHandler:
    mov rcx, r10
    push rax
    call syscallDispatcher
    add rsp, 8
    iretq
    ;los parametros de las syscalls se pasan como en linux: RAX para el ID, y los otros argumentos que se necesiten por RDI, RSI, RDX, R10, R8, R9.

haltcpu:
	cli
	hlt
	ret


SECTION .bss
	aux resq 1
    regs resb 8*17