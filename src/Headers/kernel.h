#ifndef KERNEL_H
#define KERNEL_H

#define KERNEL_STACK 0x1000

#define PAGE_TABLE_BASE 0x200000
#define PAGE_TABLE_SIZE (256 * 4096)

#define KHEAP_BASE (PAGE_TABLE_BASE + PAGE_TABLE_SIZE)
#define KHEAP_SIZE 0x200000

#include "types.h"
#include "common.h"
#include "kheap.h"
#include "tables.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "paging.h"
#include "process.h"
#include "clock.h"
#include "keyboard.h"
#include "monitor.h"

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
