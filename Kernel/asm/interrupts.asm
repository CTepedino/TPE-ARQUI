global _irq01Handler
global _cli
global _sti
global picMasterMask
global picSlaveMask
extern irqDispatcher

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

