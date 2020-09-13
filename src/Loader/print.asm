print16:
    .loop_head:
        mov al, [si]      ; read char from string
        cmp al, 0         ; check for the 0 terminator
        jne .print16_char ; else print the char
        ret

    .print16_char:
        mov ah, 0x0e      ; teletype output
        int 0x10          ; write the char
        inc si            ; increment the pointer
        jmp .loop_head    ; loop
