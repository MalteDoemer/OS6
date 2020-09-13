read_disk:
    mov ah, 0x02                ; read mode
    mov ch, 0x00                ; cylinder 0
    mov dh, 0x00                ; head 0
    int 0x13                    ; read from disk

    jc .error                   ; bios sets the carry flag if it wasn't able to read
    ret

    .error:
        mov si, .ERROR_MSG      ; message to print
        call print16            ; display the fail message
        cli                     ; clear interrupts
    .hang:                      ; wait forever
        hlt
        jmp .hang

    .ERROR_MSG: db "Error loading disk.", 10, 13, 0

boot_drive: db 0