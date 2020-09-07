#include "kernel.h"

GDT_PTR gdtptr;
GDT_ENTRY gdt[3];

void init_gdt()
{
    set_gdt_entry(0, 0, 0, 0, 0);               // null descriptor
    set_gdt_entry(1, 0, 0, 0b10011000, 0b0010); // kernel code descriptor
    set_gdt_entry(2, 0, 0, 0b10000000, 0b0000); // kernel data descriptor

    gdtptr.limit = sizeof(gdt) - 1;
    gdtptr.base = (qword)gdt;

    load_gdt(&gdtptr);
}

void set_gdt_entry(int index, dword base, dword limit, byte access, byte flags)
{
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;
    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].limit_high = (limit >> 16) & 0x0F;
    gdt[index].flags = flags;
    gdt[index].access = access;
}