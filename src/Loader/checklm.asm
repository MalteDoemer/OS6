check_lm:
    pushfd              ; push eflags to the stack
    pop eax             ; pop eflags from stack to eax
    mov ecx, eax        ; back up eax in ecx

    xor eax, 1 << 21    ; flip 21st bit of eax to 1 if it isn't already

    push eax            ; put eax back into eflags and then back into eax
    popfd
    pushfd
    pop eax

    xor eax, ecx        ; return true if eax and original eflags (backed up in ecx) are different
    jz .fail            ; if 0, jump to .fail

    mov eax, 0x80000000 ; test if cpuid supports extended processor info
    cpuid
    cmp eax, 0x80000001 ; eax must be larger than or equal to 0x80000001
    jb .fail            ; if it is not, jump to .fail

    mov eax, 0x80000001 ; test if CPU supports long mode
    cpuid
    test edx, 1 << 29   ; if the 29th bit of edx is 1, we have long mode
    jz .fail            ; if not, jump to .fail

    ret                 ; return

    .fail:
    mov si, .NO_LM      ; print failiure message
    call print16
    cli
    .hang:
        hlt
        jmp .hang

    .NO_LM: db "Long mode not supported.", 10, 13, 0