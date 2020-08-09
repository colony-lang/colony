#include "vm.h"

co_vm_t* co_vm_new(void) {
    co_vm_t* vm = malloc(sizeof(co_vm_t));
    return vm;
}

void co_vm_free(co_vm_t* vm) {
    free(vm);
}
