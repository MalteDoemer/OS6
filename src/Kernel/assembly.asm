section .text

[global memsetb]
memsetb:
    mov rcx, rdx
    mov rdx, rdi
    mov rax, rsi
    rep stosb
    mov rax, rdx
    ret

[global memcpyb]
memcpyb:
    mov rcx, rdx
    mov rdx, rdi
    rep movsb
    mov rax, rdx
    ret

[global memsetw]
memsetw:
    mov rcx, rdx
    mov rdx, rdi
    mov rax, rsi
    rep stosw
    mov rax, rdx
    ret

[global memcpyw]
memcpyw:
    mov rcx, rdx
    mov rdx, rdi
    rep movsw
    mov rax, rdx
    ret

[global memsetd]
memsetd:
    mov rcx, rdx
    mov rdx, rdi
    mov rax, rsi
    rep stosd
    mov rax, rdx
    ret

[global memcpyd]
memcpyd:
    mov rcx, rdx
    mov rdx, rdi
    rep movsd
    mov rax, rdx
    ret

[global memsetq]
memsetq:
    mov rcx, rdx
    mov rdx, rdi
    mov rax, rsi
    rep stosq
    mov rax, rdx
    ret

[global memcpyq]
memcpyq:
    mov rcx, rdx
    mov rdx, rdi
    rep movsq
    mov rax, rdx
    ret

IDT_INFO:
    .limit:  dw 0
    .base: dq 0

[global load_idt]
load_idt:
    mov word [IDT_INFO.limit], di
    mov qword [IDT_INFO.base], rsi
    lidt [IDT_INFO]
    ret

GDT_INFO:
    .limit: dw 0
    .base: dq 0

[global load_gdt]
load_gdt:
    mov word [GDT_INFO.limit], di
    mov qword [GDT_INFO.base], rsi
    lgdt [GDT_INFO]
    ret


%macro ISR_ERR 1
[global isr%1]
isr%1:
    cli 
    nop
    nop
    push rax
    mov rax, %1
    jmp isr_stub
%endmacro 

%macro ISR 1
[global isr%1]
isr%1:
    cli
    push 0
    push rax
    mov rax, %1
    jmp isr_stub
%endmacro

[extern isr_handler]
[global isr_stub]
isr_stub:
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9

    mov rdi, rax
    mov rsi, rsp
    call isr_handler

    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax
    add rsp, 8
    sti
    iretq

times 256 db 0

[global isr_table]
isr_table:

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR_ERR 8
ISR 9
ISR_ERR 10
ISR_ERR 11 
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR 15
ISR 16
ISR_ERR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR_ERR 30
ISR 31

%assign i 32
%rep 224
ISR i
%assign i i+1
%endrep