#include "module.h"

struct co_object_t co_module_new(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:

    // co_module_t *self_v = 

    // co_object_t self = {
    //     .t = CO_KIND_MODULE,
    //     .v = (co_module_t*)malloc(sizeof(co_module_t))
    // };
    co_object_t self;

    self = (co_object_t){
        .k = CO_KIND_MODULE
    };

    return self;
}

struct co_object_t co_module_free(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:
    return ctx->undefined;
}
