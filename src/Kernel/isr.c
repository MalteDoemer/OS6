#include "kernel.h"

isr_t* isr_handlers;

void register_isr(uint8_t index, isr_t isr) { isr_handlers[index] = isr; }

void isr_handler(uint64_t int_num, cpu_state_t* stack)
{
    if (isr_handlers[int_num])
        isr_handlers[int_num](stack);
    else {
        vga_attrib = 0x1F;
        vga_clear();
        vga_puts("Fatal: Unhandled Interrupt: ");
        vga_puth(int_num);
        vga_putc('\n');

        for (;;)
            hlt();
    }
}

void isr_divide_by_zero(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Divide-by-zero Error\n");

    for (;;)
        hlt();
}

void isr_overflow(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Overflow\n");

    for (;;)
        hlt();
}

void isr_invalid_opcode(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid Opcode\n");

    for (;;)
        hlt();
}

void isr_double_fault(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Double Fault\n");

    for (;;)
        hlt();
}

void isr_invalid_tss(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid TSS\n");

    for (;;)
        hlt();
}

void isr_general_protection_fault(cpu_state_t* stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Gerneral Protection Fault\n");

    for (;;)
        hlt();
}

void cascade_irq()
{
    outb(0x20, 0x20); // EOI
}

void init_isr()
{
    isr_handlers = kmalloc(sizeof(isr_t) * 256);
    memsetb(isr_handlers, 0, sizeof(isr_t) * 256);
    register_isr(0x00, isr_divide_by_zero);
    register_isr(0x04, isr_overflow);
    register_isr(0x06, isr_invalid_opcode);
    register_isr(0x08, isr_double_fault);
    register_isr(0x0A, isr_invalid_tss);
    register_isr(0x0D, isr_general_protection_fault);
    register_isr(0x22, cascade_irq);
}