global _irq01Handler
global _cli
global _sti
global picMasterMask
global picSlaveMask
global _syscallHandler
extern irqDispatcher
extern read
extern write

section .text

%macro irqHandlerMaster 1
    pushState
    mov rdi, %1 ; pasaje de parámetro
    call irqDispatcher

    ; signal pic EOI (End of Interrupt)
    mov al, 20h
    out 20h, al

    popState
    iretq
%endmacro

_irq01Handler:
    irqHandlerMaster 1

_syscallHandler:
    cmp rax, 0
    je readHandler
    cmp rax, 1
    je writeHandler
    ret

readHandler:
    call read

writeHandler:
    call write

_cli:
    cli 
    ret

_sti:
    sti 
    ret

picMasterMask:
    mov al, dil
    out 0x21, al
    ret

picSlaveMask:
    mov al, dil
    out 0xA1, al
    ret

