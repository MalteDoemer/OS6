#ifndef ISR_H
#define ISR_H

#include "kernel.h"

typedef struct _ISR_STACK
{
    qword r9, r8, rdi, rsi, rdx, rcx, rax;
    qword err;
    qword rip, cs, flags;
} ISR_STACK;

typedef void (*ISR)(ISR_STACK *);


void isr_handler(qword int_num, ISR_STACK *stack);
void init_isr();
void register_isr(byte index, ISR isr);

#endif // #ifndef ISR_H
