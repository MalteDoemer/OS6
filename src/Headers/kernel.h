#ifndef KERNEL_H
#define KERNEL_H

#define KERNEL_STACK 0x1000

#include "clock.h"
#include "common.h"
#include "config.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "keyboard.h"
#include "kheap.h"
#include "monitor.h"
#include "paging.h"
#include "tables.h"
#include "types.h"

typedef struct boot_info_t {
    qword kernel_stack;
    qword kernel_base;
    qword kernel_size;
    qword low_mem_size;
    qword high_mem_size;
    byte boot_drive;
} __attribute__((packed)) boot_info_t;

/* The entrypoint of the kernel */
void kernel_main(boot_info_t* info);

#endif // #ifndef KERNEL_H
