#ifndef CO_BOOL_H
#define CO_BOOL_H

#include "./object.h"

// () -> bool
struct co_object_t *co_bool_new(struct co_ctx_t *ctx, _Bool v);

// (self: bool) -> Result
struct co_object_t *co_bool_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bool) -> str | Err
struct co_object_t *co_bool_repr(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bool) -> u64 | Err
struct co_object_t *co_bool_hash(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bool) -> bool
struct co_object_t *co_bool_inv(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: bool, other: bool) -> bool
struct co_object_t *co_bool_and(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: bool, other: bool) -> bool
struct co_object_t *co_bool_or(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: bool, other: bool) -> bool
struct co_object_t *co_bool_xor(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

#endif
