#ifndef ISR_H
#define ISR_H

#include "kernel.h"

typedef struct isr_stack_t {
    qword r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx, rax;
    qword err;
    qword rip, cs, flags, rsp, ss;
} isr_stack_t;

typedef void (*isr_t)(isr_stack_t*);

void isr_handler(qword int_num, isr_stack_t* stack);
void init_isr();
void register_isr(byte index, isr_t isr);

#endif // #ifndef ISR_H
