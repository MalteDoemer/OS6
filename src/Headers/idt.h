#ifndef IDT_H
#define IDT_H

#include "kernel.h"

#define SLAVE_IRQS 0b11111111
#define MASTER_IRQS 0b11111000

typedef struct idt_entry_t {
    uint16_t low_bits;
    uint16_t selector;
    uint8_t reserved1;
    uint8_t attributes;
    uint16_t middle_bits;
    duint16_t high_bits;
    duint16_t reserved2;
} __attribute__((__packed__)) idt_entry_t;

typedef struct idt_t {
    idt_entry_t entries[256];
} __attribute__((__packed__)) idt_t;

typedef struct int_stub_t {
    uint8_t uint8_ts[14];
} __attribute__((__packed__)) int_stub_t;

extern int_stub_t int_table[256];

/* Initializes the Interrupt Descriptor Table */
void init_idt();

/* Function defined in assembly.asm to load the idt */
void load_idt(uint16_t limit, quint16_t base);

/* Set an entry in the Interrupt Descriptor Table*/
void set_idt_entry(int index, void* int_sub, uint16_t selector, uint8_t attributes);

#endif // #ifndef IDT_H