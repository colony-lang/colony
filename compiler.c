#include "compiler.h"

struct co_compiler_t* co_compiler_new(void) {
    struct co_compiler_t* compiler = malloc(sizeof(struct co_compiler_t));
    return compiler;
}

void co_compiler_free(struct co_compiler_t* compiler) {
    free(compiler);
}

struct co_object_t* co_compiler_compile_string(struct co_compiler_t* compiler, struct co_object_t* str) {
    co_object_t* code = NULL;
    return code;
}

struct co_object_t* co_compiler_compile_path(struct co_compiler_t* compiler, struct co_object_t* path) {
    co_object_t* code = NULL;
    return code;
}
