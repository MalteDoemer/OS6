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

%macro EXCEPT 1
[global except%1]
except%1:
    cli
    mov eax, %1
    jmp except_stub
%endmacro

%macro ISR 1
[global isr%1]
isr%1:
    cli
    push %1
    jmp isr_stub
%endmacro

[global except_stub]
except_stub:
    hlt
    jmp except_stub

[global isr_stub]
isr_stub:
    sti
    add rsp, 4
    iretq

times 256 db 0

[global isr_table]
isr_table:

%assign i 0

%rep 32
EXCEPT i
%assign i i+1
%endrep

%rep 224
ISR i
%assign i i+1
%endrep