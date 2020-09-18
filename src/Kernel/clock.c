#include "kernel.h"

quint16_t ticks;

void init_clock()
{
    register_isr(0x20, clock_handler);

    duint16_t divisor = 1193180 / PIT_FREQUENCY;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}

void clock_handler(cpu_state_t* stack)
{
    ticks++;
    outb(0x20, 0x20); // EOI
}