#include "ctx.h"
#include "object.h"

co_ctx_t *co_ctx_new(co_ctx_t *parent) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = parent;
    ctx->ns_types = NULL;
    ctx->ns_values = NULL;
    return ctx;
}

co_ctx_t *co_ctx_new_with_ns(struct co_ctx_t *parent, void *ns_types, void *ns_values) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = parent;

    // CO_OBJECT_INC_RC(ctx, (co_object_t *)ns_types);
    ctx->ns_types = ns_types;

    // CO_OBJECT_INC_RC(ctx, (co_object_t *)ns_values);
    ctx->ns_values = ns_values;
    return ctx;
}

void co_ctx_free(co_ctx_t *ctx) {
    ctx->parent = NULL;
    ctx->ns_types = NULL;
    ctx->ns_values = NULL;
    free(ctx);
}

void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size) {
    return malloc(size);
}

void co_ctx_mem_free(co_ctx_t *ctx, void *ptr) {
    free(ptr);
}
