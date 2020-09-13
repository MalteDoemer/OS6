#ifndef KERNEL_H
#define KERNEL_H

#include "config.h"
#include "types.h"
#include "common.h"
#include "kheap.h"
#include "gdt.h"
#include "idt.h"
#include "paging.h"
#include "isr.h"
#include "clock.h"
#include "tables.h"
#include "monitor.h"
#include "keyboard.h"

typedef struct boot_info_t {
    qword kernel_stack;
    qword kernel_base;
    qword kernel_size;

    qword low_mem_size;
    
} boot_info_t;

/* The entrypoint of the kernel */
void kernel_main();

#endif // #ifndef KERNEL_H
