#ifndef TABLES_H
#define TABLES_H

#include "kernel.h"

typedef struct idt_entry_t {
    word low_bits;
    word selector;
    byte reserved1;
    byte attributes;
    word middle_bits;
    dword high_bits;
    dword reserved2;
} __attribute__((__packed__)) idt_entry_t;

typedef struct gtd_entry_t {
    word limit_low;
    word base_low;
    byte base_middle;
    byte access;
    byte limit_high : 4;
    byte flags : 4;
    byte base_high;
} __attribute__((__packed__)) gtd_entry_t;

typedef struct int_stub_t {
    byte bytes[14];
} __attribute__((__packed__)) int_stub_t;

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

extern idt_entry_t idt[256];
extern gtd_entry_t gdt[6];
extern int_stub_t isr_table[256];
extern tss_t tss;

/* Initializes the Interrupt Descriptor Table */
void init_idt();

/* Initializes the Global Descriptor Table */
void init_gdt();

/* Function defined in assembly.asm to load the idt */
void load_idt(word limit, qword base);

/* Function defined in assembly.asm to load the gdt */
void load_gdt(word limit, qword base);

/* Set an entry in the Interrupt Descriptor Table*/
void set_idt_entry(int index, void* int_sub, word selector, byte attributes);

/* Set an entry in the Global Descriptor Table */
void set_gdt_entry(int index, dword base, dword limit, byte access, byte flags);

/* Writes a tss entry into the gdt */
void write_tss(int index, qword rsp);

/* Function defined in assembly.asm to reload the tss */
void flush_tss();

/* Sets rsp0 in the tss data structure */
void set_kernel_stack(qword rsp);

#endif // #ifndef TABLES_H
