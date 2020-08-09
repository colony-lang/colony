#ifndef CO_COMPILER_H
#define CO_COMPILER_H

#include <stdlib.h>

#include "vm.h"
#include "object.h"

typedef struct co_compiler_t {
    struct co_vm_t* vm;
} co_compiler_t;

struct co_compiler_t* co_compiler_new(co_vm_t* vm);
void co_compiler_free(struct co_compiler_t* compiler);
struct co_object_t* co_compiler_compile_string(struct co_compiler_t* compiler, struct co_object_t* str);
struct co_object_t* co_compiler_compile_path(struct co_compiler_t* compiler, struct co_object_t* path);

#endif
