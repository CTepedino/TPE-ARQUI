GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_sleep
GLOBAL sys_screenInfo
GLOBAL sys_textPosition
GLOBAL sys_getRTC
GLOBAL sys_getREGS
GLOBAL sys_beep
GLOBAL sys_putRectangle
GLOBAL sys_putCircle
GLOBAL sys_getCurrentKeyPress
GLOBAL sys_getCurrentReleasedKeys

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

sys_sleep:
    systemcall 2

sys_screenInfo:
    systemcall 3

sys_textPosition:
    systemcall 4

sys_getRTC:
    systemcall 5

sys_getREGS:
    systemcall 6

sys_beep:
    systemcall 7

sys_putRectangle:
    systemcall 8

sys_putCircle:
    systemcall 9

sys_getCurrentKeyPress:
    systemcall 10

sys_getCurrentReleasedKeys:
    systemcall 11


