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


[global cascade_irq]
cascade_irq:
    push rax
    mov al, 0x20
    out 0x20, al
    pop rax
    iretq

[global interrupt_gate]
interrupt_gate:
    iretq

[global exception_00]
exception_00:
    mov al, 0
    jmp exception_gate

[global exception_01]
exception_01:
    mov al, 1
    jmp exception_gate

[global exception_02]
exception_02:
    mov al, 2
    jmp exception_gate

[global exception_03]
exception_03:
    mov al, 3
    jmp exception_gate

[global exception_04]
exception_04:
    mov al, 4
    jmp exception_gate

[global exception_05]
exception_05:
    mov al, 5
    jmp exception_gate

[global exception_06]
exception_06:
    mov al, 6
    jmp exception_gate

[global exception_07]
exception_07:
    mov al, 7
    jmp exception_gate

[global exception_08]
exception_08:
    mov al, 8
    jmp exception_gate

[global exception_09]
exception_09:
    mov al, 9
    jmp exception_gate

[global exception_10]
exception_10:
    mov al, 10
    jmp exception_gate

[global exception_11]
exception_11:
    mov al, 11
    jmp exception_gate

[global exception_12]
exception_12:
    mov al, 12
    jmp exception_gate

[global exception_13]
exception_13:
    mov al, 13
    jmp exception_gate

[global exception_14]
exception_14:
    mov al, 14
    jmp exception_gate

[global exception_15]
exception_15:
    mov al, 15
    jmp exception_gate

[global exception_16]
exception_16:
    mov al, 16
    jmp exception_gate

[global exception_17]
exception_17:
    mov al, 17
    jmp exception_gate

[global exception_18]
exception_18:
    mov al, 18
    jmp exception_gate

[global exception_19]
exception_19:
    mov al, 19
    jmp exception_gate

[global exception_gate]
exception_gate:
    cli
    .hang:
        hlt
        jmp .hang