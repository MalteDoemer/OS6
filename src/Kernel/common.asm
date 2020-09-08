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