#include "i64.h"

co_object_t *co_i64_new(co_ctx_t *ctx, int64_t v) {
    co_object_t *self = co_ctx_mem_alloc(ctx, sizeof(co_object_t));
    self->rc = 1;
    self->kind = CO_KIND_I64;
    self->value.i64 = v;
    return self;
}

co_object_t *co_i64_free(co_ctx_t *ctx, co_object_t *self) {
    co_ctx_mem_free(ctx, self);

    // TODO: return Ok(None)
    return NULL;
}
