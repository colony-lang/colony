#ifndef CO_BYTES_H
#define CO_BYTES_H

#include "../core/ctx.h"
#include "object.h"

/* (self: bytes, other: bytes) -> bytes */
struct co_object_t co_bytes_new(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes) -> Undefined */
struct co_object_t co_bytes_free(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, other: bytes) -> bool */
struct co_object_t co_bytes_lt(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, other: bytes) -> bool */
struct co_object_t co_bytes_eq(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes) -> u64 */
struct co_object_t co_bytes_hash(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes) -> u64 */
struct co_object_t co_bytes_len(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, other: bytes) -> bytes */
struct co_object_t co_bytes_add(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, other: bytes) -> list<bytes> */
struct co_object_t co_bytes_split(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, from: u64, to: u64) -> bytes */
struct co_object_t co_bytes_get_slice(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, from: u64, to: u64, other: bytes) -> bytes */
struct co_object_t co_bytes_set_slice(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, index: u64) -> bytes */
struct co_object_t co_bytes_get_item(struct co_ctx_t *ctx, struct co_object_t obj);
/* (self: bytes, index: u64, value: bytes) -> bytes */
struct co_object_t co_bytes_set_item(struct co_ctx_t *ctx, struct co_object_t obj);

#endif
