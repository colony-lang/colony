#ifndef CO_FRAME_H
#define CO_FRAME_H

#include "vm.h"
#include "object.h"

struct co_frame_t;

typedef struct co_frame_t {
    struct co_vm_t* vm;
    struct co_code_t* code;
    struct co_frame_t* prev_frame;
    struct co_object_t** regs;
} co_frame_t;


#endif
