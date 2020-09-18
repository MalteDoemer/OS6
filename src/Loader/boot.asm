[bits 16]

extern kernel_start       ; memory address of kernel provided by linker script
extern kernel_end         ; memory address of kernel end also from linker
extern kernel_stack       ; memory address of kernel stack
extern kernel_main        ; entry of kernel

start:
cli
jmp 0:.clear_seg
.clear_seg:
 xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov bp, start         ; set up the stack at 0x7C00
    mov sp, bp
    cld                   ; clear direction flag
sti                       ; restore interrupts

mov uint8_t [boot_drive], dl ; the bios fills dl with our initial boot drive

xor ax, ax
int 13                    ; reset the disk to known state

mov al, 1                 ; read one sector
mov cl, 2                 ; start at second sector
mov dl, uint8_t [boot_drive] ; read from our boot drive
mov bx, second_sector     ; load at memory addr of second sector (0x7E00)
call read_disk            ; read from disk

call enable_a20           ; enables A20-Line
call unreal_mode          ; drops us into unreal mode
call memory_detect        ; gets information about ram

jmp second_sector         ; go on to the second sector

%include "src/Loader/print.asm"
%include "src/Loader/disk.asm"
%include "src/Loader/A20.asm"
%include "src/Loader/unreal.asm"
%include "src/Loader/memory.asm"

times 510-($-$$) db 0     ; padding to 510 uint8_ts
dw 0xAA55                 ; magic signature for the bios

second_sector:
    call check_lm
    call load_kernel
    call setup_paging
    call enter_lm

%include "src/Loader/checklm.asm"
%include "src/Loader/load.asm"
%include "src/Loader/paging.asm"
%include "src/Loader/enterlm.asm"

[bits 64]
long_mode:
    mov rsp, kernel_stack
    mov rdi, 0
    call kernel_main

times 512-($-$$-512) db 0