#include "ctx.h"

co_ctx_t *co_ctx_new(void) {
    co_ctx_t *ctx = malloc(sizeof(co_ctx_t));
    return ctx;
}

void co_ctx_free(co_ctx_t *ctx) {
    free(ctx);
}

void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size) {
    return malloc(size);
}

void co_ctx_mem_free(co_ctx_t *ctx, void *ptr) {
    free(ptr);
}
