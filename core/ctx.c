#include "ctx.h"

struct co_ctx_t *co_ctx_new(void) {
    struct co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = NULL;
    
    // predefined values
    ctx->undefined = (co_object_t){
        .k = CO_KIND_UNDEFINED,
        .v = {
            .ptr = NULL
        }
    };

    ctx->builtins = (co_object_t){
        .k = CO_KIND_UNDEFINED,
        .v = {
            .ptr = NULL
        }
    };

    // ctxs
    ctx->ctxs_cap = 8;
    ctx->ctxs_len = 0;
    ctx->ctxs = calloc(ctx->ctxs_cap, sizeof(co_ctx_t*));
    
    // frames
    ctx->frames_cap = 8;
    ctx->frames_len = 0;
    ctx->frames = calloc(ctx->frames_cap, sizeof(co_frame_t*));
    
    return ctx;
}

struct co_ctx_t *co_ctx_spawn(struct co_ctx_t *ctx) {
    // TODO:
    return NULL;
}

int co_ctx_free(struct co_ctx_t *ctx) {
    free(ctx->ctxs);
    free(ctx->frames);
    free(ctx);
    return 0;
}

void co_ctx_panic(struct co_ctx_t *ctx, char *msg) {
    // FIXME: print trackback
    printf("panic: %s\n", msg);

    // FIXME: panic only current context
    exit(1);
}