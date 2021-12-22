#ifndef CO_I64_H
#define CO_I64_H

#include "./object.h"

// () -> i64
struct co_object_t *co_i64_new(struct co_ctx_t *ctx, int64_t v);

// (self: i64) -> Result
struct co_object_t *co_i64_free(struct co_ctx_t *ctx, struct co_object_t *self);

// a: i64 = 1
// b: i64 = 2
// c := a + b
// c: any = a + b
// Result: type = Ok | Err
// c: i64 | Result[i64, str] = a + b
// c := typeof(c) ? {
//      i64 => { c }
//      Err => { panic(-1) }   
// }

// (self: i64) -> str | Err
struct co_object_t *co_i64_repr(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: i64) -> u64 | Err
struct co_object_t *co_i64_hash(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: i64) -> i64
struct co_object_t *co_i64_pos(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: i64) -> i64
struct co_object_t *co_i64_neg(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_sub(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_mul(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64 | Err
struct co_object_t *co_i64_div(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_mod(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_pow(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64) -> i64
struct co_object_t *co_i64_inv(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_and(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_or(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_xor(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_lshift(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: i64, other: i64) -> i64
struct co_object_t *co_i64_rshift(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

#endif
