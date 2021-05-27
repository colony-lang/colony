#ifndef CO_STR_H
#define CO_STR_H

#include "object_common.h"

typedef struct co_str_t {
    size_t len;
    size_t items_len;
    char *items;
} co_str_t;

// () -> str
co_object_t *co_str_new(co_ctx_t *ctx, size_t len, size_t items_len, char *items);

// (self: str) -> Result
co_object_t *co_str_free(co_ctx_t *ctx, co_object_t *self);

// (self: str) -> str | Err
co_object_t *co_str_repr(co_ctx_t *ctx, co_object_t *self);

// (self: str) -> u64 | Err
co_object_t *co_str_hash(co_ctx_t *ctx, co_object_t *self);

// (self: str, other: str) -> str
co_object_t *co_str_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: str, index: i64) -> str
co_object_t *co_str_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: str, index: i64, byte: str) -> str
co_object_t *co_str_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *byte);

// (self: str, index: i64) -> str
co_object_t *co_str_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: str, begin: i64, end: i64) -> str
co_object_t *co_str_get_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end);

// (self: str, begin: i64, end: i64, other: str) -> str
co_object_t *co_str_set_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end, co_object_t *other);

// (self: str, begin: i64, end: i64) -> str
co_object_t *co_str_del_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end);

// (self: str, pattern: str) -> i64 | Err
co_object_t *co_str_find(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern);

// (self: str, pattern: str) -> list[i64] | Err
co_object_t *co_str_find_all(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern);

// (self: str, pattern: str, replacement: str) -> str | Err
co_object_t *co_str_replace(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern, co_object_t *replacement);

// (self: str, pattern: str, replacement: str) -> str | Err
co_object_t *co_str_replace_all(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern, co_object_t *replacement);

// (self: str) -> bytes | Err
co_object_t *co_str_encode(co_ctx_t *ctx, co_object_t *self);

#endif
