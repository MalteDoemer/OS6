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

extern IDT_ENTRY idt[256];

extern GDT_ENTRY gdt[3];

void init_idt();
void init_gdt();

void load_idt(word limit, qword base);
void load_gdt(word limit, qword base);

void set_idt_entry(int index, void (*int_sub)(), word selector, byte attributes);
void set_gdt_entry(int index, dword base, dword limit, byte access, byte flags);

void exception_00();
void exception_01();
void exception_02();
void exception_03();
void exception_04();
void exception_05();
void exception_06();
void exception_07();
void exception_08();
void exception_09();
void exception_10();
void exception_11();
void exception_12();
void exception_13();
void exception_14();
void exception_15();
void exception_16();
void exception_17();
void exception_18();
void exception_19();

void exception_gate(); // default exception gate
void interrupt_gate(); // default interrupt gate

void cascade_irq();

#endif // #ifndef TABLES_H
