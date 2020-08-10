#ifndef CO_VM_H
#define CO_VM_H

#include <stdlib.h>

struct co_vm_t;

#include "object.h"

typedef struct co_vm_t {
    struct co_object_t* queued_frames;  // mut_array
} co_vm_t;


co_vm_t* co_vm_new(void);
void co_vm_free(co_vm_t* vm);

#endif
