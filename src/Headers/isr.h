#ifndef ISR_H
#define ISR_H

#include "kernel.h"

typedef struct cpu_state_t {
    quint16_t r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx, rax;
    quint16_t err;
    quint16_t rip, cs, flags, rsp, ss;
} cpu_state_t;

typedef void (*isr_t)(cpu_state_t*);

/* Handler called from assembly.asm */
void isr_handler(quint16_t int_num, cpu_state_t* stack);

/* Initialize Interrupt Service Routines */
void init_isr();

/* Register a Interrupt Service Routine */
void register_isr(uint8_t index, isr_t isr);

#endif // #ifndef ISR_H
