#include "kernel.h"

typedef struct lol_t
{
    int a;
    int b;
    int c;
} lol_t;

void kernel_main()
{
    init_gdt();
    init_idt();
    init_isr();
    init_vga();
    vga_puts("Welcome to FettOS\n");

    init_kheap();

    lol_t *lol = kmalloc(sizeof(lol_t));

    lol->a = 36;
    lol->b = 42;
    lol->c = 69;

    lol_t *arr = kmalloc(sizeof(lol_t) * 36);

    for (int i = 0; i < 36; i++)
    {
        arr[i].a = 0;
        arr[i].b = 36;
        arr[i].c = 69;
    }

    kfree(arr);
    kfree(lol);

    sti();
}