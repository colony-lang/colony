#ifndef CO_BYTES_H
#define CO_BYTES_H

#include "../core/ctx.h"
#include "object.h"

/* (cls: type) -> bytes */
co_object_t co_bytes_new(co_ctx_t *ctx, co_object_t obj);

/* (ctx, len: size_t, items: char*) -> bytes */
co_object_t co_bytes_new_c(co_ctx_t *ctx, size_t len, char *items);

/* (self: bytes) -> Undefined */
co_object_t co_bytes_free(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_bytes_free_c(co_ctx_t *ctx, co_object_t self);

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_lt(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_eq(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: bytes, len: size_t, items: char*) -> bool */
co_object_t co_bytes_eq_c(co_ctx_t *ctx, co_object_t self, size_t len, char *items);

/* (self: bytes) -> u64 */
co_object_t co_bytes_hash(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes) -> u64 */
co_object_t co_bytes_len(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, other: bytes) -> bytes */
co_object_t co_bytes_add(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, other: bytes) -> list<bytes> */
co_object_t co_bytes_split(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, from: u64, to: u64) -> bytes */
co_object_t co_bytes_get_slice(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, from: u64, to: u64, other: bytes) -> bytes */
co_object_t co_bytes_set_slice(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, index: u64) -> bytes */
co_object_t co_bytes_get_item(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes, index: u64, value: bytes) -> bytes */
co_object_t co_bytes_set_item(co_ctx_t *ctx, co_object_t obj);

/* (self: bytes) -> str */
co_object_t co_bytes_decode(co_ctx_t *ctx, co_object_t obj);

#endif
