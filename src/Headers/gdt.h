#ifndef GDT_H
#define GDT_H

#include "kernel.h"

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

typedef struct _GDT_PTR
{
    word limit;
    qword base;
} GDT_PTR;

extern GDT_ENTRY gdt[3];
extern GDT_PTR gdtptr;

void init_gdt();
void load_gdt(GDT_PTR *);
void set_gdt_entry(int index, dword base, dword limit, byte access, byte flags);


#endif // #ifndef GDT_H
