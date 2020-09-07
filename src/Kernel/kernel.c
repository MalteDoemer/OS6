#include "kernel.h"

void kernel_main()
{
    init_idt();
    init_gdt();
    init_vga();

    vga_puts("Welcome to FettOS\n");
    sti();
    
    __asm ("int $0");
}