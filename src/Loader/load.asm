load_kernel:
    mov cl, 3                       ; start to read at third sector
    mov al, 1                       ; read mode
    mov dl, byte [boot_drive]       ; read from boot drive
    mov bx, 0x8000                  ; some random address that's free
    mov edi, kernel_start           ; kernel will be loaded here

    .load:
        call read_disk              ; read one sector from disk

        push ecx                    ; save ecx
        push eax                    ; save eax

        mov esi, 0x8000             ; we will be copying from esi -> edi
        mov ecx, 128                ; copy 128 dwords

        .copy:
            mov eax, dword [es:esi] ; load value at esi
            mov dword [es:edi], eax ; store value at edi
            add esi, 4              ; increment esi
            add edi, 4              ; increment edi
            loop .copy              ; loop

        pop eax                     ; restore eax
        pop ecx                     ; restore ecx

        inc cl                      ; increment the read sector
        cmp edi, kernel_end         ; check if we are done
        jne .load                   ; loop otherwise
        ret
