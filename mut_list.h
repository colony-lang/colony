#ifndef CO_MUT_LIST_H
#define CO_MUT_LIST_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"
#include "list_item.h"

typedef struct co_mut_list_t {
    size_t cap;
    size_t len;
    co_list_item_t *items;
} co_mut_list_t;

// () -> mut_list
co_object_t *co_mut_list_new(co_ctx_t *ctx);

// (self: mut_list) -> Result
co_object_t *co_mut_list_free(co_ctx_t *ctx, co_object_t *self);

// (self: mut_list, index: any, type_: type, value: any) -> mut_list
co_object_t *co_mut_list_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *type_, co_object_t *value);

// (self: mut_list, index: any, value: any) -> mut_list
co_object_t *co_mut_list_set(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *value);

// (self: mut_list, index: any) -> (type, any) | Err
co_object_t *co_mut_list_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list, index: any) -> any | Err
co_object_t *co_mut_list_get(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list, index: any) -> (mut_list, type, any) | Err
co_object_t *co_mut_list_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list, index: any) -> mut_list | Err
co_object_t *co_mut_list_del(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list, index: any, type_: type) -> bool
co_object_t *co_mut_list_hasitem(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *type_);

// (self: mut_list, index: any) -> bool
co_object_t *co_mut_list_has(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list, other: mut_list) -> mut_list
co_object_t *co_mut_list_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: mut_list, value: any) -> mut_list
co_object_t *co_mut_list_prepend(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: mut_list, value: any) -> mut_list
co_object_t *co_mut_list_append(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: mut_list, value: any) -> mut_list | Err
co_object_t *co_mut_list_remove(co_ctx_t *ctx, co_object_t *self, co_object_t *value);

// (self: mut_list, index: i64, value: any) -> mut_list
co_object_t *co_mut_list_insert(co_ctx_t *ctx, co_object_t *self, co_object_t *index, co_object_t *value);

// (self: mut_list, index: Option[i64]=None) -> (mut_list, any) | Err
co_object_t *co_mut_list_pop(co_ctx_t *ctx, co_object_t *self, co_object_t *index);

// (self: mut_list) -> mut_list[(i64, type, any)]
co_object_t *co_mut_list_items(co_ctx_t *ctx, co_object_t *self);

// (self: mut_list) -> mut_list[(i64, any)]
co_object_t *co_mut_list_entries(co_ctx_t *ctx, co_object_t *self);

#endif
