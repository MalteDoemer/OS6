#include "kernel.h"

idt_t* idt;

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
    outb(0xA1, SLAVE_IRQS); // Mask all unused slave irq's

    idt = kmalloc(sizeof(idt_t));
    memsetb((byte*)idt, 0, sizeof(idt_t));

    for (int i = 0; i < 32; i++)
        set_idt_entry(i, int_table + i, 0x08, 0x8F);

    for (int i = 32; i < 256; i++)
        set_idt_entry(i, int_table + i, 0x08, 0x8E);

    load_idt(sizeof(idt_t) - 1, (qword)idt);
}

void set_idt_entry(int index, void* int_sub, word selector, byte attributes)
{
    qword addr = (qword)int_sub;

    idt->entries[index].reserved1 = 0;
    idt->entries[index].reserved2 = 0;
    idt->entries[index].attributes = attributes;
    idt->entries[index].selector = selector;

    idt->entries[index].low_bits = addr;
    addr = addr >> 16;
    idt->entries[index].middle_bits = addr;
    addr = addr >> 16;
    idt->entries[index].high_bits = addr;
}
