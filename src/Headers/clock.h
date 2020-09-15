#ifndef CLOCK_H
#define CLOCK_H

#include "kernel.h"

#define PIT_FREQUENCY 1

/* Initialize the PIT clock */
void init_clock();

/* Interrupt handler for the clock */
void clock_handler(isr_stack_t* stack);

/* Total amount of PIT clock ticks since startup */
extern qword ticks;

#endif // #ifndef CLOCK_H
