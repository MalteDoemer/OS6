#include "kernel.h"

void kernel_main()
{
    init_gdt();
    init_idt();
    init_vga();
    vga_puts("Welcome to FettOS\n");

    sti();
    int i = 10 / 0;
}