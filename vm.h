#ifndef CO_VM_H
#define CO_VM_H

#include <stdlib.h>


typedef struct co_vm_t {
    void* _dummy;
} co_vm_t;


struct co_vm_t* co_vm_new(void);
void co_vm_free(struct co_vm_t* vm);

#endif
