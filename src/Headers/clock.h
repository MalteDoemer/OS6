#ifndef CLOCK_H
#define CLOCK_H

#include "kernel.h"

void init_clock();
void clock_handler(isr_stack_t* stack);

extern qword ticks;

#endif // #ifndef CLOCK_H
