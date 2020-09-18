#include "kernel.h"

process_t* current_proc;
process_t* root_proc;

int pid;

void scheduler(cpu_state_t* stack)
{
    memcpyq(&current_proc->cpu_state, stack, sizeof(cpu_state_t) / 4);

    current_proc = current_proc->next;
    if (current_proc == NULL)
        current_proc = root_proc;

    while (current_proc->state == PROC_ASLEEP) {
        current_proc = current_proc->next;
        if (current_proc == NULL)
            current_proc = root_proc;
    }

    memcpyq(stack, &current_proc->cpu_state, sizeof(cpu_state_t) / 4);
    set_activ_dir(current_proc->page_dir);
}

void init_procs(process_t* root)
{
    root_proc = root;
    root_proc->next = NULL;
    root_proc->parent = NULL;
    root_proc->type = PROC_ROOT;
    root_proc->state = PROC_RUNNING;
    current_proc = root_proc;
}