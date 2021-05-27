#ifndef CO_I64_H
#define CO_I64_H

#include "object_common.h"

// () -> i64
co_object_t *co_i64_new(co_ctx_t *ctx, int64_t v);

// (self: i64) -> Result
co_object_t *co_i64_free(co_ctx_t *ctx, co_object_t *self);

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
co_object_t *co_i64_repr(co_ctx_t *ctx, co_object_t *self);

// (self: i64) -> u64 | Err
co_object_t *co_i64_hash(co_ctx_t *ctx, co_object_t *self);

// (self: i64) -> i64
co_object_t *co_i64_pos(co_ctx_t *ctx, co_object_t *self);

// (self: i64) -> i64
co_object_t *co_i64_neg(co_ctx_t *ctx, co_object_t *self);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_sub(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_mul(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64 | Err
co_object_t *co_i64_div(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_mod(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_pow(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64) -> i64
co_object_t *co_i64_inv(co_ctx_t *ctx, co_object_t *self);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_and(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_or(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_xor(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_lshift(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: i64, other: i64) -> i64
co_object_t *co_i64_rshift(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

#endif
