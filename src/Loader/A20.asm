enable_a20:
    mov ax, 0x2403      ; A20-Line support
    int 0x15            ; use int 0x15 to get info about A20-Line

    jb .fail            ; check if this machine supports A20-Line
    cmp ah, 0
    jnz .fail

    mov ax, 0x2402      ; A20-Line status
    int 0x15            ; now get the status of the A20-Line it may be already enabled

    jb .fail            ; check if the function could complete
    cmp ah, 0
    jnz .fail

    cmp al, 1           ; fucntion returns 1 if A20-Line is already enabled
    jz .done            ; jump to end

    mov ax, 0x2401      ; A20-Line activate
    int 0x15            ; Activate the A20-Line

    jb .fail            ; check if A20-Line was enabled sucessfully
    cmp ah, 0
    jnz .fail

    .done:
    ret                 ; return

    .fail:
    mov si, .A20_FAILED ; get the failure message
    call print16        ; print the message
    cli                 ; clear interrupts
    .hang:              ; wait forever
        hlt
        jmp .hang

    .A20_FAILED: db "Failed to enabeld A20-Line.", 10, 13, 0