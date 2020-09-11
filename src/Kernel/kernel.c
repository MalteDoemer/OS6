#include "kernel.h"

void kernel_main()
{
    init_gdt();
    init_idt();
    init_isr();
    init_kheap();
    init_vga();


    init_paging();

    vga_puts("Welcome to FettOS\n");
    
    sti();
    for (;;)
        hlt();
}