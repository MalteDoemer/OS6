#ifndef KERNEL_H
#define KERNEL_H

#define LF_LINE_END

#include "types.h"
#include "common.h"
#include "kheap.h"
#include "tables.h"
#include "paging.h"
#include "isr.h"
#include "monitor.h"

void kernel_main();

#endif // #ifndef KERNEL_H
