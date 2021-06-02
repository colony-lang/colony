#ifndef CO_BYTES_H
#define CO_BYTES_H

struct co_bytes_t;

#include "./object.h"

typedef struct co_bytes_t {
    size_t len;
    char *items;
} co_bytes_t;


// () -> bytes
struct co_object_t *co_bytes_new(struct co_ctx_t *ctx, size_t len, char *items);

// (self: bytes) -> Result
struct co_object_t *co_bytes_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bytes) -> str | Err
struct co_object_t *co_bytes_repr(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bytes) -> u64 | Err
struct co_object_t *co_bytes_hash(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bytes, other: bytes) -> bytes
struct co_object_t *co_bytes_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: bytes, index: i64) -> bytes
struct co_object_t *co_bytes_getitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: bytes, index: i64, byte: bytes) -> bytes
struct co_object_t *co_bytes_setitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *byte);

// (self: bytes, index: i64) -> bytes
struct co_object_t *co_bytes_delitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: bytes, begin: i64, end: i64) -> bytes
struct co_object_t *co_bytes_get_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: bytes, begin: i64, end: i64, other: bytes) -> bytes
struct co_object_t *co_bytes_set_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end, struct co_object_t *other);

// (self: bytes, begin: i64, end: i64) -> bytes
struct co_object_t *co_bytes_del_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: bytes, pattern: bytes) -> i64 | Err
struct co_object_t *co_bytes_find(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: bytes, pattern: bytes) -> list[i64] | Err
struct co_object_t *co_bytes_find_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: bytes, pattern: bytes, replacement: bytes) -> bytes | Err
struct co_object_t *co_bytes_replace(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: bytes, pattern: bytes, replacement: bytes) -> bytes | Err
struct co_object_t *co_bytes_replace_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: bytes) -> str | Err
struct co_object_t *co_bytes_decode(struct co_ctx_t *ctx, struct co_object_t *self);

#endif
