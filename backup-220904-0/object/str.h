#ifndef CO_STR_H
#define CO_STR_H

#include <string.h>
#include <stdbool.h>

#include "../core/ctx.h"
#include "object.h"

/* (cls: type) -> str */
co_object_t co_str_new(co_ctx_t *ctx, co_object_t obj);

/* (ctx, len: size_t, items: char*) -> str */
co_object_t co_str_new_c(co_ctx_t *ctx, size_t len, char *items);

/* (self: str) -> Undefined */
co_object_t co_str_free(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_str_free_c(co_ctx_t *ctx, co_object_t self);

/* (self: str, other: str) -> bool */
co_object_t co_str_lt(co_ctx_t *ctx, co_object_t obj);

/* (self: str, other: str) -> bool */
co_object_t co_str_eq(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: str, len: size_t, items: char*) -> bool */
co_object_t co_str_eq_c(co_ctx_t *ctx, co_object_t self, size_t len, char *items);

/* (self: str) -> u64 */
co_object_t co_str_hash(co_ctx_t *ctx, co_object_t obj);

/* (self: str) -> u64 */
co_object_t co_str_len(co_ctx_t *ctx, co_object_t obj);

/* (self: str, other: str) -> str */
co_object_t co_str_add(co_ctx_t *ctx, co_object_t obj);

/* (self: str, other: str) -> list<str> */
co_object_t co_str_split(co_ctx_t *ctx, co_object_t obj);

/* (self: str, from: u64, to: u64) -> str */
co_object_t co_str_get_slice(co_ctx_t *ctx, co_object_t obj);

/* (self: str, from: u64, to: u64, other: str) -> str */
co_object_t co_str_set_slice(co_ctx_t *ctx, co_object_t obj);

/* (self: str, index: u64) -> str */
co_object_t co_str_get_item(co_ctx_t *ctx, co_object_t obj);

/* (self: str, index: u64, value: str) -> str */
co_object_t co_str_set_item(co_ctx_t *ctx, co_object_t obj);

/* (self: str) -> bytes */
co_object_t co_str_encode(co_ctx_t *ctx, co_object_t obj);

#endif
