#include "ctx.h"

struct co_ctx_t *co_ctx_new(struct co_ctx_t *parent) {
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
}

int co_ctx_free(struct co_ctx_t *ctx) {
    ctx->root = NULL;
    ctx->parent = NULL;
    free(ctx);
    return 0;
}
