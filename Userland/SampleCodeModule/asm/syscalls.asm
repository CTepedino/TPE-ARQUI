global sys_write
global sys_read
global sys_textPosition
global sys_screenInfo
global sys_time
global sys_regData

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

sys_textPosition:
    systemcall 2

sys_screenInfo:
    systemcall 3

sys_time:
    systemcall 4

sys_regData:
    systemcall 5

