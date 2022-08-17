#include "ctx.h"

struct co_ctx_t *co_ctx_new(void) {
    /*
    struct co_ctx_t *ctx = malloc(sizeof(struct co_ctx_t));

    if (parent == NULL) {
        ctx->root = NULL;
        ctx->parent = NULL;
    } else {
        if (parent->root == NULL) {
            ctx->root = parent;
        } else {
            ctx->root = parent->root;
        }

        ctx->parent = parent;
    }

    return ctx;
    */
    struct co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = NULL;
    ctx->ctxs_cap = 8;
    ctx->ctxs_len = 0;
    ctx->ctxs = calloc(ctx->ctxs_cap, sizeof(co_ctx_t*));
    ctx->regs_cap = 8;
    ctx->regs_len = 0;
    ctx->regs = calloc(ctx->regs_cap, sizeof(co_object_t));
    return ctx;
}

struct co_ctx_t *co_ctx_spawn(struct co_ctx_t *ctx) {
    // TODO:
    return NULL;
}

int co_ctx_free(struct co_ctx_t *ctx) {
    ctx->parent = NULL;
    free(ctx->ctxs);
    free(ctx->regs);
    free(ctx);
    return 0;
}
