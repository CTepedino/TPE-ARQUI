GLOBAL cpuVendor

GLOBAL getHour
GLOBAL getMin
GLOBAL getSec

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

%macro getTime 1
	push rbp
        mov rbp, rsp

        mov al, %1
        out 70h, al
        in al, 71h

        mov rsp, rbp
        pop rbp
        ret
%endmacro


getHour:
    getTime 4

getMin:
    getTime 2

getSec:
    getTime 0
