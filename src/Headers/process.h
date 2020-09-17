#ifndef PROCESS_H
#define PROCESS_H

#include "kernel.h"

#define MAX_PROCS 256

typedef struct process_t {
    page_dir_t* page_dir;
    cpu_state_t cpu_state;
    char* name;
    int pid;
    int state;
    int type;

    struct process_t* parent;
    struct process_t* next;
} process_t;

void init_procs();
void scheduler(cpu_state_t* stack);

#endif // #ifndef PROCESS_H
