#ifndef ISR_H
#define ISR_H

#include "kernel.h"

typedef struct cpu_state_t {
    qword r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx, rax;
    qword err;
    qword rip, cs, flags, rsp, ss;
} cpu_state_t;

typedef void (*isr_t)(cpu_state_t*);

/* Handler called from assembly.asm */
void isr_handler(qword int_num, cpu_state_t* stack);

/* Initialize Interrupt Service Routines */
void init_isr();

/* Register a Interrupt Service Routine */
void register_isr(byte index, isr_t isr);

#endif // #ifndef ISR_H
