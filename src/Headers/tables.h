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

typedef struct _GDT_ENTRY
{
    word limit_low;
    word base_low;
    byte base_middle;
    byte access;
    byte limit_high : 4;
    byte flags : 4;
    byte base_high;
} GDT_ENTRY;

typedef struct _INT_SUB
{
    byte bytes[11];
} INT_SUB;

extern IDT_ENTRY idt[256];
extern GDT_ENTRY gdt[3];
extern INT_SUB isr_table[256];

void init_idt();
void init_gdt();

void load_idt(word limit, qword base);
void load_gdt(word limit, qword base);

void set_idt_entry(int index, void *int_sub, word selector, byte attributes);
void set_gdt_entry(int index, dword base, dword limit, byte access, byte flags);

#endif // #ifndef TABLES_H
