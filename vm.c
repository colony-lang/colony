#include "vm.h"

struct co_vm_t* co_vm_new(void) {
    struct co_vm_t* vm = malloc(sizeof(struct co_vm_t));
    return vm;
}

void co_vm_free(struct co_vm_t* vm) {
    free(vm);
}