GLOBAL runDivideByZero
GLOBAL runInvalidOpCode

section .text

runDivideByZero:
    mov rax, 5
    mov rbx, 0
    div rbx
    ret

runInvalidOpCode:
    ud2
    ret