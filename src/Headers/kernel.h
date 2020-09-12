#ifndef KERNEL_H
#define KERNEL_H

#include "config.h"
#include "types.h"
#include "common.h"
#include "kheap.h"
#include "tables.h"
#include "paging.h"
#include "isr.h"
#include "monitor.h"

/* The entrypoint of the kernel */
void kernel_main();

#endif // #ifndef KERNEL_H
