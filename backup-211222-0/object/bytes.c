#include "bytes.h"

// () -> bytes
struct co_object_t *co_bytes_new(struct co_ctx_t *ctx, size_t len, char *items) {
    // alloc bytes
    co_bytes_t *bytes = co_ctx_mem_alloc(ctx, sizeof(co_bytes_t));

    // len is not set
    bytes->len = len;

    // items is not set
    bytes->items = items;

    // bytes
    co_object_t *self = co_object_new(ctx, CO_KIND_BYTES, (co_value_t){.bytes = bytes});
    return self;
}

// (self: bytes) -> Result
struct co_object_t *co_bytes_free(struct co_ctx_t *ctx, struct co_object_t *self) {
    // free self
    co_ctx_mem_free(ctx, self);
    
    // ok
    co_object_t *res = co_ctx_ok(ctx, "`bytes` instance freed");
    return res;
}