#ifndef CO_BYTES_H
#define CO_BYTES_H

#include "../core/ctx.h"
#include "object.h"

struct co_object_t co_bytes_new(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_free(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_lt(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_eq(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_hash(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_add(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_split(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_get_slice(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_set_slice(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_get_item(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_bytes_set_item(struct co_ctx_t *ctx, struct co_object_t obj);

#endif
