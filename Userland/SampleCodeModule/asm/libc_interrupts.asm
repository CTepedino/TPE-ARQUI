global sys_write
global sys_read
global sys_time

section .text

sys_read:
    mov rax, 0
    int 0x80
    ret

sys_write:
    mov rax, 1
    int 0x80
    ret

sys_time:
    mov rax, 2
    int 0x80
    ret