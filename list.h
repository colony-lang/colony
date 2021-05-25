#ifndef CO_LIST_H
#define CO_LIST_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"
#include "list_item.h"

typedef struct co_list_t {
    size_t len;
    co_list_item_t *items;
} co_list_t;

// () -> list
co_object_t *co_list_new(co_ctx_t *ctx);

// (self: list) -> Result
co_object_t *co_list_free(co_ctx_t *ctx, co_object_t *self);

// (self: list, index: any, type_: type, value: any) -> list
co_object_t *co_list_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *type_, co_object_t *value);

// (self: list, index: any, value: any) -> list
co_object_t *co_list_set(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *value);

// (self: list, index: any) -> (type, any) | Err
co_object_t *co_list_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list, index: any) -> any | Err
co_object_t *co_list_get(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list, index: any) -> (list, type, any) | Err
co_object_t *co_list_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list, index: any) -> list | Err
co_object_t *co_list_del(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list, index: any, type_: type) -> bool
co_object_t *co_list_hasitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *type_);

// (self: list, index: any) -> bool
co_object_t *co_list_has(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list, other: list) -> list
co_object_t *co_list_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: list, value: any) -> list
co_object_t *co_list_prepend(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: list, value: any) -> list
co_object_t *co_list_append(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: list, value: any) -> list | Err
co_object_t *co_list_remove(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: list, index: i64, value: any) -> list
co_object_t *co_list_insert(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *value);

// (self: list, index: Option[i64]=None) -> (list, any) | Err
co_object_t *co_list_pop(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: list) -> list[(i64, type, any)]
co_object_t *co_list_items(co_ctx_t *ctx, co_object_t *self);

// (self: list) -> list[(i64, any)]
co_object_t *co_list_entries(co_ctx_t *ctx, co_object_t *self);

#endif
