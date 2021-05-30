#ifndef CO_BYTES_H
#define CO_BYTES_H

struct co_bytes_t;

#include "object.h"

typedef struct co_bytes_t {
    size_t len;
    char *items;
} co_bytes_t;


// () -> bytes
co_object_t *co_bytes_new(co_ctx_t *ctx, size_t len, char *items);

// (self: bytes) -> Result
co_object_t *co_bytes_free(co_ctx_t *ctx, co_object_t *self);

// (self: bytes) -> str | Err
co_object_t *co_bytes_repr(co_ctx_t *ctx, co_object_t *self);

// (self: bytes) -> u64 | Err
co_object_t *co_bytes_hash(co_ctx_t *ctx, co_object_t *self);

// (self: bytes, other: bytes) -> bytes
co_object_t *co_bytes_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: bytes, index: i64) -> bytes
co_object_t *co_bytes_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: bytes, index: i64, byte: bytes) -> bytes
co_object_t *co_bytes_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *byte);

// (self: bytes, index: i64) -> bytes
co_object_t *co_bytes_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: bytes, begin: i64, end: i64) -> bytes
co_object_t *co_bytes_get_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end);

// (self: bytes, begin: i64, end: i64, other: bytes) -> bytes
co_object_t *co_bytes_set_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end, co_object_t *other);

// (self: bytes, begin: i64, end: i64) -> bytes
co_object_t *co_bytes_del_slice(co_ctx_t *ctx, co_object_t *self, co_object_t *begin, co_object_t *end);

// (self: bytes, pattern: bytes) -> i64 | Err
co_object_t *co_bytes_find(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern);

// (self: bytes, pattern: bytes) -> list[i64] | Err
co_object_t *co_bytes_find_all(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern);

// (self: bytes, pattern: bytes, replacement: bytes) -> bytes | Err
co_object_t *co_bytes_replace(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern, co_object_t *replacement);

// (self: bytes, pattern: bytes, replacement: bytes) -> bytes | Err
co_object_t *co_bytes_replace_all(co_ctx_t *ctx, co_object_t *self, co_object_t *pattern, co_object_t *replacement);

// (self: bytes) -> str | Err
co_object_t *co_bytes_decode(co_ctx_t *ctx, co_object_t *self);

#endif
