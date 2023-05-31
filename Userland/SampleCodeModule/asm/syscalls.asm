GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_colorWrite
GLOBAL sys_writeMatrix
GLOBAL sys_screenInfo
GLOBAL sys_textPosition
GLOBAL sys_getRTC
GLOBAL sys_regData
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

sys_colorWrite:
    systemcall 2

sys_writeMatrix:
    systemcall 3

sys_screenInfo:
    systemcall 4

sys_textPosition:
    systemcall 5

sys_getRTC:
    systemcall 6


sys_regData:
    ret ;TODO

sys_playSound:
    ret ;TODO