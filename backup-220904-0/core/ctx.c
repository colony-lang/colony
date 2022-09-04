#include "ctx.h"

struct co_ctx_t *co_ctx_new(void) {
    struct co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    ctx->parent = NULL;
    
    // predefined values
    ctx->undefined = co_object_new_c_ptr(ctx, CO_KIND_UNDEFINED, NULL);
    ctx->panic = co_object_new_c_ptr(ctx, CO_KIND_PANIC, NULL);
    ctx->builtins = co_object_new_c_ptr(ctx, CO_KIND_UNDEFINED, NULL);

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
    CO_DECREF(ctx, ctx->undefined);
    CO_DECREF(ctx, ctx->panic);
    CO_DECREF(ctx, ctx->builtins);
    free(ctx->ctxs);
    free(ctx->frames);
    free(ctx);
    return 0;
}

struct co_object_t co_ctx_panic(struct co_ctx_t *ctx, char *msg) {
    // FIXME: print trackback
    printf("panic: %s\n", msg);

    // "general" panic
    return ctx->panic;
}

/* (self: ctx, attr: str) -> object */
struct co_object_t co_ctx_getvar(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, attr: char*) -> object */
struct co_object_t co_ctx_getvar_c(struct co_ctx_t *ctx, size_t attr_len, char *attr) {
    // TODO:
    return ctx->undefined;
}

/* (self: ctx, attr: str, cls: type, value: object) -> object */
struct co_object_t co_ctx_setvar(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, attr: char*, cls: co_object_t, value: co_object_t) -> object */
struct co_object_t co_ctx_setvar_c(struct co_ctx_t *ctx, size_t attr_len, char *attr, struct co_object_t cls, struct co_object_t value) {
    // TODO:
    return ctx->undefined;
}
