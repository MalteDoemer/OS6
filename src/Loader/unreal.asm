unreal_mode:
    cli                ; no more interrupts
    push ds            ; save ds on the stack

    lgdt [GDT_32.info] ; load temporary gdt

    mov eax, cr0       ; enabel pmode
    or eax, 1          ; by setting first bit in cr0
    mov cr0, eax

    jmp $+2            ; tell 386/486 to not crash

    mov bx, 0x08       ; fist descriptor
    mov ds, bx

    mov eax, cr0       ; go back to real mode
    and al, 0xFE       ; by clearing the first bit in cr0
    mov cr0, eax

    pop ds             ; get ds back
    sti                ; restore interrupts
    ret

GDT_32:
    dd 0, 0
    db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0

    .info:
        dw GDT_32 - $ - 1
        dd GDT_32