#include "kernel.h"

ISR isr_handlers[256];

void register_isr(byte index, ISR isr)
{
    isr_handlers[index] = isr;
}

void isr_handler(qword int_num, ISR_STACK *stack)
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


void isr_divide_by_zero(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Divide-by-zero Error\n");

    while (1)
        hlt();
}

void isr_overflow(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Overflow\n");

    while (1)
        hlt();
}

void isr_invalid_opcode(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid Opcode\n");

    while (1)
        hlt();
}

void isr_double_fault(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Double Fault\n");

    while (1)
        hlt();
}

void isr_invalid_tss(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Invalid TSS\n");

    while (1)
        hlt();
}

void isr_general_protection_fault(ISR_STACK *stack)
{
    vga_attrib = 0x1F;
    vga_clear();
    vga_puts("Fatal: Gerneral Protection Fault\n");

    while (1)
        hlt();
}

void init_isr()
{
    register_isr(0x00, isr_divide_by_zero);
    register_isr(0x04, isr_overflow);
    register_isr(0x06, isr_invalid_opcode);
    register_isr(0x08, isr_double_fault);
    register_isr(0x0A, isr_invalid_tss);
    register_isr(0x0D, isr_general_protection_fault);
}