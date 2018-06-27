#ifndef __SMP_H__
#define __SMP_H__

#include <stdint.h>
#include <stddef.h>
#include <task.h>

#define MAX_CPUS 128

#define current_cpu ({ \
    size_t cpu_number; \
    asm volatile ("mov rax, qword ptr fs:[0]" : "=a" (cpu_number)); \
    cpu_number; \
})

typedef struct {
    /* DO NOT MOVE THESE MEMBERS FROM THESE LOCATIONS */
    /* DO NOT CHANGE THEIR TYPES */
    size_t cpu_number;
    size_t kernel_stack;
    /* Feel free to move every other member, and use any type as you see fit */
    pid_t current_process;
    tid_t current_thread;
    uint8_t lapic_id;
    int reset_scheduler;
} cpu_local_t;

extern cpu_local_t cpu_locals[MAX_CPUS];

void init_smp(void);
void smp_init_cpu0_local(void *, void *);
void *smp_prepare_trampoline(void *, void *, void *, void *, void *);
int smp_check_ap_flag(void);

extern size_t smp_cpu_count;

#endif
