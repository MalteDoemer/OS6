BITS 16

extern kernel_start             ; memory address of kernel provided by linker script
extern kernel_end               ; memory address of kernel end
extern kernel_main              ; entry of kernel

start:                          ; entrypoint at 0x7C00
cli                             ; clear interrupts
jmp 0:.clear_seg                ; perform a jump to correct our segments
.clear_seg:                     ; zero out all segment registers
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov bp, start               ; set up the stack at 0x7C00
    mov sp, bp
    cld                         ; clear direction flag
sti                             ; restore interrupts

mov byte [boot_drive], dl       ; the bios fills dl with our initial boot drive

xor ax, ax
int 13                          ; reset the disk to known state


mov al, 1                       ; read one sector
mov cl, 2                       ; start at second sector
mov dl, byte [boot_drive]       ; read from our boot drive
mov bx, second_sector           ; load at memory addr of second sector (0x7E00)
call read_disk                  ; read from disk

enableA20:
    mov ax, 0x2403              ; A20-Line support
    int 0x15                    ; use int 0x15 to get info about A20-Line

    jb .fail                    ; check if this machine supports A20-Line
    cmp ah, 0
    jnz .fail

    mov ax, 0x2402              ; A20-Line status
    int 0x15                    ; now get the status of the A20-Line it may be already enabled

    jb .fail                    ; check if the function could complete
    cmp ah, 0
    jnz .fail

    cmp al, 1                   ; fucntion returns 1 if A20-Line is already enabled
    jz .done                    ; jump to end

    mov ax, 0x2401              ; A20-Line activate
    int 0x15                    ; Activate the A20-Line

    jb .fail                    ; check if A20-Line was enabled sucessfully
    cmp ah, 0
    jnz .fail

    .done:
        jmp unreal_mode         ; go on to enable unreal mode

    .fail:
        mov si, .A20_FAILED     ; get the failure message
        call print16            ; print the message
        cli                     ; clear interrupts
    .hang:                      ; wait forever
        hlt
        jmp .hang


    .A20_FAILED: db "Failed to enabeld A20-Line.", 10, 13, 0

unreal_mode:                    ; enter "unreal mode" to get more address space
    cli                         ; no more interrupts
    push ds                     ; save ds on the stack

    lgdt [GDT_32.info]          ; load temporary gdt

    mov eax, cr0                ; enabel pmode
    or eax, 1                   ; by setting first bit in cr0
    mov cr0, eax

    jmp $+2                     ; tell 386/486 to not crash

    mov bx, 0x08                ; fist descriptor
    mov ds, bx

    mov eax, cr0                ; go back to real mode
    and al, 0xFE                ; by clearing the first bit in cr0
    mov cr0, eax

    pop ds                      ; get ds back
    sti                         ; restore interrupts

    jmp second_sector           ; go into second sector

boot_drive: db 0                ; boot drive is stored here
print16:
    .loop_head:
        mov al, [si]            ; read char from string
        cmp al, 0               ; check for the 0 terminator
        jne .print16_char       ; else print the char
        ret

    .print16_char:
        mov ah, 0x0e            ; teletype output
        int 0x10                ; write the char
        inc si                  ; increment the pointer
        jmp .loop_head          ; loop

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

GDT_32:
    dd 0, 0
    db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0

    .info:
        dw GDT_32 - $ - 1
        dd GDT_32

times 510-($-$$) db 0           ; padding to 510 bytes
dw 0xAA55                       ; magic signature

second_sector:

mov cl, 3                       ; start to read at third sector
mov al, 1                       ; read mode
mov dl, byte [boot_drive]       ; read from boot drive
mov bx, 0x8000                  ; some random address that's free
mov edi, kernel_start           ; kernel will be loaded here

load_kernel:
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
    jne load_kernel             ; loop otherwise

cli                             ; clear interrupts

mov edi, 0x1000                 ; page table is at 0x1000
mov cr3, edi                    ; tell the processor where the table is

xor eax, eax
mov ecx, 0x1000
rep stosd                       ; clear out 0x1000 dwords for the table

; PML4T -> 0x1000               ; Page map level 4 table
; PDPT -> 0x2000                ; Page directory pointer table
; PDT -> 0x3000                 ; Page directory table
; PT -> 0x4000                  ; Page table

mov edi, 0x1000
mov dword [edi], 0x2003         ; PML4T[0] = 0x2003 (PDPT)
add edi, 0x1000
mov dword [edi], 0x3003         ; PDPT[0] = 0x3003  (PDT)
add edi, 0x1000
mov dword [edi], 0x4003         ; PDT[0] = 0x4003 (PT1)
mov dword [edi + 8], 0x5003     ; PDT[1] = 0x5003 (PT2)
add edi, 0x1000

mov ebx, 3                      ; Read/Write and Present bit
mov ecx, 2 * 512                ; fill two PT's each 512 bytes

.set_entry:                     ; identery map first PT
    mov dword [edi], ebx        ; store ebx
    add ebx, 0x1000             ; increment ebx
    add edi, 8                  ; PT entry is 8 bytes
    loop .set_entry

mov eax, cr4
or eax, 1 << 5
mov cr4, eax

mov ecx, 0xC0000080
rdmsr
or eax, 1 << 8
wrmsr

mov eax, cr0
or eax, 1 << 31
or eax, 1 << 0
mov cr0, eax

lgdt [GDT_64.Pointer]
jmp GDT_64.Code:long_mode


checklm:
    pushfd                      ; push eflags to the stack
    pop eax                     ; pop eflags from stack to eax
    mov ecx, eax                ; back up eax in ecx

    xor eax, 1 << 21            ; flip 21st bit of eax to 1 if it isn't already

    push eax                    ; put eax back into eflags and then back into eax
    popfd
    pushfd
    pop eax

    xor eax, ecx                ; return true if eax and original eflags (backed up in ecx) are different
    jz .fail                    ; if 0, jump to .fail



    mov eax, 0x80000000         ; test if cpuid supports extended processor info
    cpuid
    cmp eax, 0x80000001         ; eax must be larger than or equal to 0x80000001
    jb .fail                    ; if it is not, jump to .fail



    mov eax, 0x80000001         ; test if CPU supports long mode
    cpuid
    test edx, 1 << 29           ; if the 29th bit of edx is 1, we have long mode
    jz .fail                    ; if not, jump to .fail

    mov si, .YES_LM
    call print16
    ret

    .fail:
    popa
    mov si, .NO_LM
    call print16
    cli
    .hang:
    hlt
    jmp .hang

    .NO_LM: db "Long mode not supported.", 10, 13, 0
    .YES_LM: db "Long mode supported.", 10, 13, 0

GDT_64:
    .Null: equ $ - GDT_64
        dw 0
        dw 0
        db 0
        db 0
        db 0
        db 0

    .Code: equ $ - GDT_64
        dw 0                    ; base
        dw 0                    ; limit
        db 0                    ; base
        db 10011000b            ; access  Pr = 1, Privl = 0, S = 1, Ex = 1, Dc = 0, Rw = 0, Ac = 0
        db 00100000b            ; flags  Gr = 0 Sz = 1  /  limit = 0
        db 0                    ; base

    .Data: equ $ -GDT_64
        dw 0                    ; base
        dw 0                    ; limit
        db 0                    ; base
        db 10000000b            ; access Pr = 1, Privl = 0, S = 0, Ex = 0, Dc = 0, Rw = 0, Ac = 0
        db 0                    ; flags Gr = 0, Sz = 0, / limit = 0
        db 0                    ; base

    .Pointer:
        dw $ - GDT_64 - 1
        dq GDT_64

[BITS 64]

long_mode:
    mov rsp, 0x1000
    call kernel_main

times 512-($-$$-512) db 0