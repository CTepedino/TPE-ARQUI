GLOBAL cpuVendor
GLOBAL setTimeFormat
GLOBAL getTime
GLOBAL getREGS

GLOBAL beepSound
GLOBAL onSpeaker
GLOBAL offSpeaker
GLOBAL delayLoop

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


setTimeFormat: ;Para no devolver el tiempo en BCD
   push rbp
   mov rbp, rsp

   mov al,0x0B
   out 70h,al
   in al, 71h
   or al, 4
   out 71h, al

   mov rsp, rbp
   pop rbp
   ret

getTime:

    push rbp
    mov rbp, rsp

    mov rax, rdi
    out 70h, al
    in al, 71h

    mov rsp, rbp
    pop rbp
    ret

getREGS:
    mov [regs], rax
    mov [regs+8], rbx
    mov [regs+8*2], rcx
    mov [regs+8*3], rdx
    mov [regs+8*4], rbp
    mov [regs+8*5], rsi
    mov [regs+8*6], rdi
    mov [regs+8*7], r8
    mov [regs+8*8], r9
    mov [regs+8*9], r10
    mov [regs+8*10], r11
    mov [regs+8*11], r12
    mov [regs+8*12], r13
    mov [regs+8*13], r14
    mov [regs+8*14], r15
    mov [regs+8*15], rsp
    mov rax, [rsp]
    mov [regs+8*16], rax ;rip
    pushfq
    pop QWORD [regs+8*17] ;rflags
    mov rax, regs
    ret


;de https://github.com/mlombardia/arqui_tpe
beepSound:
	push rbp
  	mov rbp, rsp

	mov rdi, 0x0000000000000A00
	call onSpeaker

	mov rdi, 10000000
	call delayLoop

	call offSpeaker

	mov rsp, rbp
  	pop rbp
	ret

onSpeaker:
	push rbp
  	mov rbp, rsp


	mov al, 182
	out 0x43, al
	mov ax, di
	out 0x42, al
	mov al, ah
	out 0x42, al
	in al, 0x61
	or al, 0x03
	out 0x61, al

	mov rsp, rbp
  	pop rbp
	ret

offSpeaker:
	push rbp
  	mov rbp, rsp

	in al, 0x61
	and al, 0xFC
	out 0x61, al

	mov rsp, rbp
  	pop rbp
	ret

delayLoop:
	push rbp
  	mov rbp, rsp

	push rax
	mov rax, 0
	.delay:
		inc rax
		cmp rax, rdi
		je .fin
		jmp .delay

	.fin:
	pop rax
	mov rsp, rbp
  	pop rbp
	ret


section .bss
regs resb 8*17