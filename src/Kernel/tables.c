#include "kernel.h"

IDT_ENTRY idt[256];
GDT_ENTRY gdt[3];

void init_idt()
{
    // remap pic
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20); // map IRQ's from pic0 to 0x20 - 0x27
    outb(0xA1, 0x28); // map IRQ's from pic1 to 0x28 - 0x2F

    outb(0x21, 0x04); // tell master pic that there is a slave pic at IRQ2
    outb(0xA1, 0x02); // tell slave pic aoubt its cascade identity

    outb(0x21, 0x01); // 8086 mode
    outb(0xA1, 0x01); // 8086 mode

    outb(0x21, MASTER_IRQS); // Mask all unused master irq's
    outb(0xA1, SLAVE_IRQS);  // Mask all unused slave irq's

    for (int i = 0; i < 32; i++)
        set_idt_entry(i, isr_table + i, 0x08, 0x8F);

    for (int i = 32; i < 256; i++)
        set_idt_entry(i, isr_table + i, 0x08, 0x8E);

    load_idt(sizeof(idt) - 1, (qword)idt);
}

void set_idt_entry(int index, void *int_sub, word selector, byte attributes)
{
    qword addr = (qword)int_sub;

    idt[index].reserved1 = 0;
    idt[index].reserved2 = 0;
    idt[index].attributes = attributes;
    idt[index].selector = selector;

    idt[index].low_bits = addr;
    addr = addr >> 16;
    idt[index].middle_bits = addr;
    addr = addr >> 16;
    idt[index].high_bits = addr;
}

void init_gdt()
{
    set_gdt_entry(0, 0, 0, 0, 0);               // null descriptor
    set_gdt_entry(1, 0, 0, 0b10011000, 0b0010); // kernel code descriptor
    set_gdt_entry(2, 0, 0, 0b10000000, 0b0000); // kernel data descriptor

    load_gdt(sizeof(gdt) - 1, (qword)gdt);
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