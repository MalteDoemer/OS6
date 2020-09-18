setup_paging:
    cli                         ; clear interrupts

    mov edi, 0x1000             ; page table is at 0x1000
    mov cr3, edi                ; tell the processor where the table is

    xor eax, eax
    mov ecx, 0x1000
    rep stosd                   ; clear out 0x1000 duint16_ts for the table

    mov edi, 0x1000
    mov duint16_t [edi], 0x2003     ; PML4T[0] = 0x2003 (PDPT)
    add edi, 0x1000
    mov duint16_t [edi], 0x3003     ; PDPT[0] = 0x3003  (PDT)
    add edi, 0x1000
    mov duint16_t [edi], 0x4003     ; PDT[0] = 0x4003 (PT1)
    mov duint16_t [edi + 8], 0x5003 ; PDT[1] = 0x5003 (PT2)
    add edi, 0x1000

    mov ebx, 11b                ; Read/Write and Present bit
    mov ecx, 2 * 512            ; fill two PT's each 512 uint8_ts

    .set_entry:                 ; identery map PT's
        mov duint16_t [edi], ebx    ; store ebx
        add ebx, 0x1000         ; increment ebx
        add edi, 8              ; PT entry is 8 uint8_ts
        loop .set_entry         ; loop
    ret                         ; return

