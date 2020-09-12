#ifndef GDT_H
#define GDT_H

#include "kernel.h"

typedef struct tss_t {
    dword r1;
    qword rsp0;
    qword rsp1;
    qword rsp2;
    qword r2;
    qword ist1;
    qword ist2;
    qword ist3;
    qword ist4;
    qword ist5;
    qword ist6;
    qword ist7;
    qword r3;
    word r4;
    word IOPB;
} __attribute__((__packed__)) tss_t;

typedef struct gdt_seg_desc_t {
    qword : 40;
    byte : 1;
    byte : 1;
    byte : 1;
    byte cd : 1;
    byte s : 1;
    byte dpl : 2;
    byte p : 1;
    byte : 5;
    byte l : 1;
    word : 10;
} __attribute__((__packed__)) gdt_seg_desc_t;

typedef struct gdt_tss_desc_t {
    word limit;
    dword base_low : 24;
    byte type : 4;
    byte : 1;
    byte dpl : 2;
    byte p : 1;
    byte : 8;
    byte : 4;
    qword base_high : 40;
    dword : 32;
} __attribute__((__packed__)) gdt_tss_desc_t;

typedef struct gdt_t {
    gdt_seg_desc_t null_desc;
    gdt_seg_desc_t kernel_code;
    gdt_seg_desc_t kernel_data;
    gdt_seg_desc_t user_code;
    gdt_seg_desc_t user_data;
    gdt_tss_desc_t tss_desc;
} __attribute__((__packed__)) gdt_t;

/* Initializes the Global Descriptor Table */
void init_gdt();

/* Function defined in assembly.asm to load the gdt */
void load_gdt(word limit, qword base);

/* Set an entry in the Global Descriptor Table */
void set_gdt_seg(gdt_seg_desc_t* desc, byte dpl, bool code);

/* Writes a tss entry into the gdt */
void set_gdt_tss(gdt_tss_desc_t* desc, byte dpl, qword base, word limit);

/* Function defined in assembly.asm to reload the tss */
void flush_tss();

/* Sets rsp0 in the tss data structure */
void set_kernel_stack(qword rsp);

#endif // #ifndef GDT_H
