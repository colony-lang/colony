#ifndef CO_F64_H
#define CO_F64_H

#include "./object.h"

// () -> f64
struct co_object_t *co_f64_new(struct co_ctx_t *ctx, double v);

// (self: f64) -> Result
struct co_object_t *co_f64_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: f64) -> str | Err
struct co_object_t *co_f64_repr(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: f64) -> u64 | Err
struct co_object_t *co_f64_hash(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: f64) -> f64
struct co_object_t *co_f64_pos(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: f64) -> f64
struct co_object_t *co_i64_neg(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: f64, other: f64) -> f64
struct co_object_t *co_f64_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: f64, other: f64) -> f64
struct co_object_t *co_f64_sub(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: f64, other: f64) -> f64
struct co_object_t *co_f64_mul(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: f64, other: f64) -> f64 | Err
struct co_object_t *co_f64_div(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

#endif
