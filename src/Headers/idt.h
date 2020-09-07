#ifndef TABLES_H
#define TABLES_H

#include "kernel.h"

#define SLAVE_IRQS 0b11111111
#define MASTER_IRQS 0b11111011

typedef struct _IDT_ENTRY
{
    word low_bits;
    word selector;
    byte reserved1;
    byte attributes;
    word middle_bits;
    dword high_bits;
    dword reserved2;
} IDT_ENTRY;

typedef struct _IDT_PTR
{
    word limit;
    qword base;
} IDT_PTR;

extern IDT_ENTRY idt[256];
extern IDT_PTR idtptr;

void init_idt();
void load_idt(IDT_PTR *);
void set_idt_entry(int index, void (*int_sub)(), word selector, byte attributes);

#endif // #ifndef TABLES_H
