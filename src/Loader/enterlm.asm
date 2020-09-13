enter_lm:
    mov eax, cr4
    or eax, 1 << 5            ; PAE Physical Address Extension
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8            ; LME Long mode enable
    or eax, 1 << 11           ; NXE No-Execute enable
    wrmsr

    mov eax, cr0
    or eax, 1 << 31           ; PG paging
    or eax, 1 << 0            ; PE Protected Mode Enable
    mov cr0, eax

    lgdt [GDT_64.Pointer]     ; load global descriptor table
    jmp GDT_64.Code:long_mode ; make the jump to long mode

    GDT_64:
    .Null: equ $ - GDT_64
        dw 0
        dw 0
        db 0
        db 0
        db 0
        db 0

    .Code: equ $ - GDT_64
        dw 0                  ; base
        dw 0                  ; limit
        db 0                  ; base
        db 10011000b          ; access  Pr = 1, Privl = 0, S = 1, Ex = 1, Dc = 0, Rw = 0, Ac = 0
        db 00100000b          ; flags  Gr = 0 Sz = 1  /  limit = 0
        db 0                  ; base

    .Data: equ $ -GDT_64
        dw 0                  ; base
        dw 0                  ; limit
        db 0                  ; base
        db 10000000b          ; access Pr = 1, Privl = 0, S = 0, Ex = 0, Dc = 0, Rw = 0, Ac = 0
        db 0                  ; flags Gr = 0, Sz = 0, / limit = 0
        db 0                  ; base

    .Pointer:
        dw $ - GDT_64 - 1
        dq GDT_64
