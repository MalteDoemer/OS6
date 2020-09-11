#ifndef KERNEL_H
#define KERNEL_H

#define LF_LINE_END

#include "common.h"
#include "isr.h"
#include "kheap.h"
#include "monitor.h"
#include "paging.h"
#include "tables.h"
#include "types.h"

void kernel_main();

#endif // #ifndef KERNEL_H
