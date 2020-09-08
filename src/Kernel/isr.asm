%macro EXCEPT 1
[global except%1]
except%1:
    cli
    mov di, %1
    jmp except_stub
%endmacro

[extern except_handler]
[global except_stub]
except_stub:
    call except_handler
.hang:
    hlt
    jmp .hang

[global default_isr]
default_isr:
    iretq

[global cascade_irq]
cascade_irq:
    push rax

    mov al, 0x20
    out 0x20, al

    pop rax
    iretq

[global keyboard_irq]
keyboard_irq:
    iretq

times 256 db 0

[global except_table]
except_table:
%assign i 0

%rep 32
EXCEPT i
%assign i i+1
%endrep