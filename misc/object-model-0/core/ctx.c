#include "ctx.h"

struct co_object_t *co_ctx_new(struct co_object_t *parent) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    co_object_t *self = co_object_new(parent, CO_KIND_CTX, {.ctx = ctx});
    self->rc = 1;

    // parent
    ctx->parent = parent;

    if (parent) {
        parent->rc++;
    }

    return ctx;
}

void co_ctx_free(struct co_ctx_t *ctx) {
    free(ctx);
}

void co_ctx_rel(struct co_ctx_t *ctx) {
    if (ctx->root) {
        co_ctx_rel(ctx->root);
    }

    if (ctx->parent) {
        co_ctx_rel(ctx->parent);
    }

    ctx->rc--;

    if (ctx->rc == 0) {
        co_ctx_free(ctx);
    }
}
