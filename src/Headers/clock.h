#ifndef CLOCK_H
#define CLOCK_H

#include "kernel.h"

#define PIT_FREQUENCY 1

/* Initialize the PIT clock */
void init_clock();

/* Interrupt handler for the clock */
void clock_handler(cpu_state_t* stack);

/* Total amount of PIT clock ticks since startup */
extern uint64_t ticks;

#endif // #ifndef CLOCK_H
