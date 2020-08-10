#ifndef CO_COMPILER_H
#define CO_COMPILER_H

#include <stdlib.h>

struct co_compiler_t;

#include "vm.h"
#include "object.h"

typedef struct co_compiler_t {
    struct co_vm_t* vm;
} co_compiler_t;

co_compiler_t* co_compiler_new(struct co_vm_t* vm);
void co_compiler_free(co_compiler_t* compiler);
co_object_t* co_compiler_compile_string(co_compiler_t* compiler, co_object_t* str);
co_object_t* co_compiler_compile_path(co_compiler_t* compiler, co_object_t* path);

#endif
