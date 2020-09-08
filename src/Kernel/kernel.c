#include "kernel.h"

void kernel_main()
{
    init_gdt();
    init_idt();

    sti();

    init_vga();
    vga_puts("Welcome to FettOS\n");
}