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

    // set all defined cpu excepions
    set_idt_entry(0, exception_00, 0x08, 0x8F);
    set_idt_entry(1, exception_01, 0x08, 0x8F);
    set_idt_entry(2, exception_02, 0x08, 0x8F);
    set_idt_entry(3, exception_03, 0x08, 0x8F);
    set_idt_entry(4, exception_04, 0x08, 0x8F);
    set_idt_entry(5, exception_05, 0x08, 0x8F);
    set_idt_entry(6, exception_06, 0x08, 0x8F);
    set_idt_entry(7, exception_07, 0x08, 0x8F);
    set_idt_entry(8, exception_08, 0x08, 0x8F);
    set_idt_entry(9, exception_09, 0x08, 0x8F);
    set_idt_entry(10, exception_10, 0x08, 0x8F);
    set_idt_entry(11, exception_11, 0x08, 0x8F);
    set_idt_entry(12, exception_12, 0x08, 0x8F);
    set_idt_entry(13, exception_13, 0x08, 0x8F);
    set_idt_entry(14, exception_14, 0x08, 0x8F);
    set_idt_entry(15, exception_15, 0x08, 0x8F);
    set_idt_entry(16, exception_16, 0x08, 0x8F);
    set_idt_entry(17, exception_17, 0x08, 0x8F);
    set_idt_entry(18, exception_18, 0x08, 0x8F);
    set_idt_entry(19, exception_19, 0x08, 0x8F);

    // fill out rest of the exceptions with a default handler
    for (int i = 20; i < 32; i++)
        set_idt_entry(i, exception_gate, 0x08, 0x8F);

    // fill out rest of the interrupts with a default handler
    for (int i = 32; i < 256; i++)
        set_idt_entry(i, interrupt_gate, 0x08, 0x8E);

    // set up master->slave cascade irq
    set_idt_entry(0x22, cascade_irq, 0x08, 0x8E);

    load_idt(sizeof(idt) - 1, (qword)idt);
}

void set_idt_entry(int index, void (*int_sub)(), word selector, byte attributes)
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