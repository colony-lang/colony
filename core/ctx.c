#include "ctx.h"

/*
 * c-level
 */
co_ctx_t *co_ctx_new(co_ctx_t *parent) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = parent;
    ctx->ns = NULL;
    return ctx;
}

co_ctx_t *co_ctx_new_with_ns(co_ctx_t *parent, struct co_object_t *ns) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = parent;

    CO_OBJECT_INC_RC(ctx, ns);
    ctx->ns = ns;

    return ctx;
}

void co_ctx_free(co_ctx_t *ctx) {
    ctx->parent = NULL;

    CO_OBJECT_DEC_RC(ctx, ctx->ns);
    ctx->ns = NULL;
    
    free(ctx);
}

void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size) {
    return malloc(size);
}

void co_ctx_mem_free(co_ctx_t *ctx, void *ptr) {
    free(ptr);
}

struct co_object_t *co_ctx_def(co_ctx_t *ctx,
                               struct co_object_t *key,
                               struct co_object_t *type,
                               struct co_object_t *value) {
    // FIXME:
    // return co_ns_set(ctx, ctx->ns, key, type, value);
    return NULL;
}

struct co_object_t *co_ctx_eval(co_ctx_t *ctx, struct co_object_t *code) {
    // FIXME: implement
    return NULL;
}

struct co_object_t *co_ctx_ok(co_ctx_t *ctx, char *msg) {
    return NULL;
}

struct co_object_t *co_ctx_err(co_ctx_t *ctx, char *msg) {
    return NULL;
}