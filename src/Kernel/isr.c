#include "kernel.h"

isr_t isr_handlers[256];

void register_isr(byte index, isr_t isr)
{
    isr_handlers[index] = isr;
}

void isr_handler(qword int_num, isr_stack_t *stack)
{
    if (isr_handlers[int_num])
        isr_handlers[int_num](stack);
    else
    {
        vga_attrib = 0x1F;
        vga_clear();
        vga_puts("Fatal: Unhandled Interrupt: ");
        vga_puth(int_num);
        vga_putc('\n');

        while (1)
            hlt();
    }
}

void isr_divide_by_zero(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Divide-by-zero Error\n");

    while (1)
        hlt();
}

void isr_overflow(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Overflow\n");

    while (1)
        hlt();
}

void isr_invalid_opcode(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid Opcode\n");

    while (1)
        hlt();
}

void isr_double_fault(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Double Fault\n");

    while (1)
        hlt();
}

void isr_invalid_tss(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid TSS\n");

    while (1)
        hlt();
}

void isr_general_protection_fault(isr_stack_t *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Gerneral Protection Fault\n");

    while (1)
        hlt();
}

void cascade_irq()
{
    outb(0x20, 0x20); // EOI
}

void init_isr()
{
    register_isr(0x00, isr_divide_by_zero);
    register_isr(0x04, isr_overflow);
    register_isr(0x06, isr_invalid_opcode);
    register_isr(0x08, isr_double_fault);
    register_isr(0x0A, isr_invalid_tss);
    register_isr(0x0D, isr_general_protection_fault);
    register_isr(0x22, cascade_irq);
}