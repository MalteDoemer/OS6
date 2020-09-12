#ifndef TABLES_H
#define TABLES_H

#include "kernel.h"

#define SLAVE_IRQS 0b11111111
#define MASTER_IRQS 0b11111011

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

extern idt_entry_t idt[256];
extern gtd_entry_t gdt[3];
extern int_stub_t isr_table[256];

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

#endif // #ifndef TABLES_H
