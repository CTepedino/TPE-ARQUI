global putCharHandler
global getCharHandler

section .text

putCharHandler:
    mov rax, 1
    int 0x80
    ret

getCharHandler:
    mov rax, 0
    int 0x80
    ret

