#include "compiler.h"

co_compiler_t* co_compiler_new(struct co_vm_t* vm) {
    co_compiler_t* compiler = malloc(sizeof(co_compiler_t));
    compiler->vm = vm;
    return compiler;
}

void co_compiler_free(co_compiler_t* compiler) {
    free(compiler);
}

co_object_t* co_compiler_compile_string(co_compiler_t* compiler, co_object_t* str) {
    // TODO: implement
    co_object_t* code = NULL;
    return code;
}

co_object_t* co_compiler_compile_path(co_compiler_t* compiler, co_object_t* path) {
    // TODO: implement
    co_object_t* code = NULL;
    return code;
}
