GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_writeMatrix
GLOBAL sys_screenInfo
GLOBAL sys_textPosition
GLOBAL sys_getRTC
GLOBAL sys_regdump
GLOBAL sys_playSound

section .text

%macro systemcall 1
    mov rax, %1
    int 0x80
    ret
%endmacro

sys_read:
    systemcall 0

sys_write:
    systemcall 1

sys_writeMatrix:
    systemcall 2

sys_screenInfo:
    systemcall 3

sys_textPosition:
    systemcall 4

sys_getRTC:
    systemcall 5

sys_regdump:
    systemcall 6

sys_playSound:
    ret ;TODO