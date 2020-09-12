#include "kernel.h"

void kernel_main()
{
    init_gdt();
    init_idt();
    init_isr();
    init_kheap();
    init_paging();
    init_vga();
    init_keyboard();

    vga_puts("Welcome to FettOS\n");

    sti();
    
    for (;;)
        vga_putc(read_char());

    for (;;)
        hlt();
}