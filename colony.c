#include <stdlib.h>

#include "vm.h"
#include "frame.h"
#include "object.h"


int main(int argc, char** argv) {
    co_vm_t* vm = co_vm_new();
    co_vm_free(vm);
    return 0;
}
