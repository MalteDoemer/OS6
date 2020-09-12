section .text

%include "config.inc"

[global memsetb]
memsetb:                           ; function to set bytes
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    mov rax, rsi                   ; fill rax with arg2
    rep stosb                      ; write the bytes
    mov rax, rdx                   ; restore pointer
    ret                            ; return

[global memcpyb]
memcpyb:                           ; funtion to copy bytes
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    rep movsb                      ; copy the bytes
    mov rax, rdx                   ; restore the pointer
    ret                            ; return

[global memsetw]
memsetw:                           ; function to set words
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    mov rax, rsi                   ; fill rax with arg2
    rep stosw                      ; write the words
    mov rax, rdx                   ; restore the pointer
    ret                            ; return

[global memcpyw]
memcpyw:                           ; function to copy words
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    rep movsw                      ; copy the words
    mov rax, rdx                   ; restore the pointer
    ret                            ; return

[global memsetd]
memsetd:                           ; function to set dwords
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    mov rax, rsi                   ; fill rax with arg2
    rep stosd                      ; write the dwords
    mov rax, rdx                   ; restore pointer
    ret                            ; return

[global memcpyd]
memcpyd:                           ; function to copy dwords
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    rep movsd                      ; copy the dwords
    mov rax, rdx                   ; restore the pointer
    ret                            ; return

[global memsetq]
memsetq:                           ; function to set qwords
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    mov rax, rsi                   ; fill rax with arg2
    rep stosq                      ; write the qwords
    mov rax, rdx                   ; restore pointer
    ret                            ; return

[global memcpyq]
memcpyq:                           ; function to copy qwords
    mov rcx, rdx                   ; init loop counter with arg3
    mov rdx, rdi                   ; backup the pointer
    rep movsq                      ; copy the qwords
    mov rax, rdx                   ; restore the pointer
    ret                            ; return

IDT_INFO:                          ; holds information about the idt
    .limit:  dw 0                  ; size of idt in bytes
    .base: dq 0                    ; address of idt

[global load_idt]
load_idt:                          ; function to load the idt
    mov word [IDT_INFO.limit], di  ; store the size of the idt
    mov qword [IDT_INFO.base], rsi ; store the address of the idt
    lidt [IDT_INFO]                ; load the idt
    ret                            ; return

GDT_INFO:                          ; holds information about gdt
    .limit: dw 0                   ; the size of the gdt
    .base: dq 0                    ; the address of the gdt

[global load_gdt]
load_gdt:                          ; function to load the gdt
    mov word [GDT_INFO.limit], di  ; store the size of the gdt
    mov qword [GDT_INFO.base], rsi ; store the address of the gdt
    lgdt [GDT_INFO]                ; load the gdt
    ret                            ; return

[global flush_tss]
flush_tss:                         ; function to reload the tss
    mov ax, TSS_ENTRY              ; mov the tss descriptor into ax
    ltr ax                         ; load the tss
    ret                            ; return

%macro ISR_ERR 1                   ; macro for an interrupt with errorcode
[global isr%1]                     ; the code generated should be 14 bytes in size
isr%1:
    cli                            ; clear interrupts
    nop                            ; padding to 14 bytes
    nop
    push rax                       ; save rax
    mov rax, %1                    ; move the isr number into rax
    jmp isr_stub                   ; jump to the handler
%endmacro

%macro ISR 1                       ; macro for an interrupt without errorcode
[global isr%1]                     ; the code generated should also be 14 bytes
isr%1:
    cli                            ; clear interrupts
    push 0                         ; push a zero to balance the stack
    push rax                       ; save rax
    mov rax, %1                    ; move the isr number into rax
    jmp isr_stub                   ; jump to the handler
%endmacro

[extern isr_handler]
[global isr_stub]
isr_stub:                          ; a common isr handler to set up the stack
    push rbx                       ; push all registers, rax is already pushed
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rdi, rax                   ; initialize arg1
    mov rsi, rsp                   ; initialize arg2
    call isr_handler               ; call the c function

    pop r15                        ; pop the ragisters back
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    add rsp, 8                     ; pop the error code or zero from the stack
    sti                            ; restore interrupts
    iretq                          ; return from interrupt

times 256 db 0                     ; this is necessery to force a 16-bit offset in all isr's

[global isr_table]
isr_table:                         ; the start of all the isr's

ISR 0                              ; divide by zero
ISR 1                              ; debug
ISR 2                              ; non-maskable interrupt
ISR 3                              ; breakpoint
ISR 4                              ; overflow
ISR 5                              ; bound ragne suceeded
ISR 6                              ; invalid opcode
ISR 7                              ; device not available
ISR_ERR 8                          ; double fault
ISR 9                              ; coprocessor segment overrun
ISR_ERR 10                         ; invalid tss
ISR_ERR 11                         ; segment not present
ISR_ERR 12                         ; stack segment fault
ISR_ERR 13                         ; general protection fault
ISR_ERR 14                         ; paage fault
ISR 15                             ; reserved
ISR 16                             ; x87 floating point exception
ISR_ERR 17                         ; alignment check
ISR 18                             ; machine check
ISR 19                             ; SIMD floating point exception
ISR 20                             ; virtualization exception
ISR 21                             ; reserved
ISR 22                             ; reserved
ISR 23                             ; reserved
ISR 24                             ; reserved
ISR 25                             ; reserved
ISR 26                             ; reserved
ISR 27                             ; reserved
ISR 28                             ; reserved
ISR 29                             ; reserved
ISR_ERR 30                         ; security exception
ISR 31                             ; reserved


%assign i 32
%rep 224                           ; give the rest int's a isr
ISR i
%assign i i+1
%endrep