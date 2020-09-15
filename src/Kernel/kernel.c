#include "kernel.h"

void kernel_main(boot_info_t* info)
{
    init_kheap();
    init_gdt();
    init_idt();
    init_isr();
    init_paging();
    init_vga();
    init_keyboard();
    init_clock();

    vga_puts("Welcome to FettOS\n");

    sti();

    for (;;) {
        hlt();
        vga_puth(ticks);
        vga_putc('\n');
    }
}