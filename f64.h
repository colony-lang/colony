#ifndef CO_F64_H
#define CO_F64_H

#include "object.h"

// () -> f64
co_object_t *co_f64_new(co_ctx_t *ctx, double v);

// (self: f64) -> Result
co_object_t *co_f64_free(co_ctx_t *ctx, co_object_t *self);

// (self: f64) -> str | Err
co_object_t *co_f64_repr(co_ctx_t *ctx, co_object_t *self);

// (self: f64) -> u64 | Err
co_object_t *co_f64_hash(co_ctx_t *ctx, co_object_t *self);

// (self: f64) -> f64
co_object_t *co_f64_pos(co_ctx_t *ctx, co_object_t *self);

// (self: f64) -> f64
co_object_t *co_i64_neg(co_ctx_t *ctx, co_object_t *self);

// (self: f64, other: f64) -> f64
co_object_t *co_f64_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: f64, other: f64) -> f64
co_object_t *co_f64_sub(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: f64, other: f64) -> f64
co_object_t *co_f64_mul(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: f64, other: f64) -> f64 | Err
co_object_t *co_f64_div(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

#endif
