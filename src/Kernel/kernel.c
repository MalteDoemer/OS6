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

    init_ata();

    select_ata(ATA_PRIMARY_IO, false);

    char buffer[512];
    memsetb(buffer, 0, 512);
    memcpyb(buffer, "Fett", 4);
    ata_write_block((uint16_t*)buffer, 0);

    sti();

    for (;;)
        hlt();
}