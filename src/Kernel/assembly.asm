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

[global load_idt]
load_idt:
    lidt [rdi]
    ret

[global load_gdt]
load_gdt:
    lgdt [rdi]
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
.hang:
    hlt
    jmp .hang


[global isr_stub]
isr_stub:
    sti 
    add rsp, 4
    iretq

times 256 db 0          ; padding to force a 16 bit jump

[global isr_table]
isr_table:

%assign i 0
%rep 32
EXCEPT i
%assign i i+1
%endrep


%assign i 0
%rep 224
ISR i
%assign i i+1
%endrep