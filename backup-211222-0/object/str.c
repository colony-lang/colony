#include "str.h"

// () -> str
struct co_object_t *co_str_new(struct co_ctx_t *ctx, size_t len, size_t items_len, char *items) {
    // alloc str
    co_str_t *str = co_ctx_mem_alloc(ctx, sizeof(co_str_t));

    // len is not set
    str->len = len;

    // items_len is not set
    str->items_len = items_len;

    // items is not set
    str->items = items;

    // str
    co_object_t *self = co_object_new(ctx, CO_KIND_STR, (co_value_t){.str = str});
    return self;
}

// (self: str) -> Result
struct co_object_t *co_str_free(struct co_ctx_t *ctx, struct co_object_t *self) {
    // free self
    co_ctx_mem_free(ctx, self);
    
    // ok
    co_object_t *res = co_ctx_ok(ctx, "`str` instance freed");
    return res;
}
