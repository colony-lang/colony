#ifndef CO_BOOL_H
#define CO_BOOL_H

#include "./object.h"

// () -> bool
co_object_t *co_bool_new(co_ctx_t *ctx, _Bool v);

// (self: bool) -> Result
co_object_t *co_bool_free(co_ctx_t *ctx, co_object_t *self);

// (self: bool) -> str | Err
co_object_t *co_bool_repr(co_ctx_t *ctx, co_object_t *self);

// (self: bool) -> u64 | Err
co_object_t *co_bool_hash(co_ctx_t *ctx, co_object_t *self);

// (self: bool) -> bool
co_object_t *co_bool_inv(co_ctx_t *ctx, co_object_t *self);

// (self: bool, other: bool) -> bool
co_object_t *co_bool_and(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: bool, other: bool) -> bool
co_object_t *co_bool_or(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: bool, other: bool) -> bool
co_object_t *co_bool_xor(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

#endif
