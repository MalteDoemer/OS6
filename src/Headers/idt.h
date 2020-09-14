#ifndef IDT_H
#define IDT_H

#include "kernel.h"

#define SLAVE_IRQS 0b11111111
#define MASTER_IRQS 0b11111000

typedef struct idt_entry_t {
    word low_bits;
    word selector;
    byte reserved1;
    byte attributes;
    word middle_bits;
    dword high_bits;
    dword reserved2;
} __attribute__((__packed__)) idt_entry_t;

typedef struct idt_t {
    idt_entry_t entries[256];
} __attribute__((__packed__)) idt_t;

typedef struct int_stub_t {
    byte bytes[14];
} __attribute__((__packed__)) int_stub_t;

extern int_stub_t int_table[256];

/* Initializes the Interrupt Descriptor Table */
void init_idt();

/* Function defined in assembly.asm to load the idt */
void load_idt(word limit, qword base);

/* Set an entry in the Interrupt Descriptor Table*/
void set_idt_entry(int index, void* int_sub, word selector, byte attributes);

#endif // #ifndef IDT_H