#include "colony.h"

/*
 * ctx
 */
co_object_t co_ctx_new(co_object_t obj, co_object_t args, co_object_t kwargs) {
    co_object_t self;
    co_ctx_t *ctx;

    ctx = calloc(1, sizeof(co_ctx_t));
    ctx->rc = 1;

    self = (co_object_t){
        .k = CO_KIND_CTX,
        .v = ctx,
    };

    return self;
}

co_object_t co_ctx_free(co_object_t obj, co_object_t args, co_object_t kwargs) {
    co_object_t self;
    return self;
}

co_object_t co_ctx_spawn(co_object_t ctx, co_object_t args, co_object_t kwargs) {
    co_object_t self;
    return self;
}
