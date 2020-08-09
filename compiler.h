#ifndef CO_COMPILER_H
#define CO_COMPILER_H

#include <stdlib.h>
#include "object.h"

typedef struct co_compiler_t {
    void* dummy;
} co_compiler_t;

struct co_compiler_t* co_compiler_new(void);
void co_compiler_free(struct co_compiler_t* compiler);
struct co_object_t* co_compiler_compile_string(struct co_compiler_t* compiler, struct co_object_t* str);
struct co_object_t* co_compiler_compile_path(struct co_compiler_t* compiler, struct co_object_t* path);

#endif
