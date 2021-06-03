#ifndef CO_STR_H
#define CO_STR_H

#include "./object.h"

typedef struct co_str_t {
    size_t len;
    size_t items_len;
    char *items;
} co_str_t;

// () -> str
struct co_object_t *co_str_new(struct co_ctx_t *ctx, size_t len, size_t items_len, char *items);

// (self: str) -> Result
struct co_object_t *co_str_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: str) -> str | Err
struct co_object_t *co_str_repr(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: str) -> u64 | Err
struct co_object_t *co_str_hash(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: str, other: str) -> str
struct co_object_t *co_str_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: str, index: i64) -> str
struct co_object_t *co_str_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: str, index: i64, byte: str) -> str
struct co_object_t *co_str_set(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *byte);

// (self: str, index: i64) -> str
struct co_object_t *co_str_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: str, begin: i64, end: i64) -> str
struct co_object_t *co_str_get_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: str, begin: i64, end: i64, other: str) -> str
struct co_object_t *co_str_set_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end, struct co_object_t *other);

// (self: str, begin: i64, end: i64) -> str
struct co_object_t *co_str_del_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: str, pattern: str) -> i64 | Err
struct co_object_t *co_str_find(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: str, pattern: str) -> list[i64] | Err
struct co_object_t *co_str_find_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: str, pattern: str, replacement: str) -> str | Err
struct co_object_t *co_str_replace(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: str, pattern: str, replacement: str) -> str | Err
struct co_object_t *co_str_replace_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: str) -> bytes | Err
struct co_object_t *co_str_encode(struct co_ctx_t *ctx, struct co_object_t *self);

#endif
