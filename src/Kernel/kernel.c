#include "kernel.h"


void kernel_main()
{
    init_idt();
    init_gdt();
}