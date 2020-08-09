#ifndef CO_VM_H
#define CO_VM_H

#include <stdlib.h>


struct co_vm_t;
struct co_frame_t;


typedef struct co_vm_t {
    void* _dummy;
} co_vm_t;

typedef struct co_frame_t {
    struct co_vm_t* vm;
    struct co_frame_t* prev_frame;
    struct co_object_t** regs;
    struct co_code_t* code;
} co_frame_t;


co_vm_t* co_vm_new(void);
void co_vm_free(co_vm_t* vm);

#endif
