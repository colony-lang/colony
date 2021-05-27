#ifndef CO_MUT_DICT_H
#define CO_MUT_DICT_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"
#include "mut_dict_common.h"

// (cap: u64, len: u64, key_type: type, value_type: type items: mut_dict[any, any]) -> mut_dict[any, any]
co_object_t *co_mut_dict_new(co_ctx_t *ctx, size_t cap, size_t len, co_object_t *key_type, co_object_t *value_type, co_dict_item_t *items);

// (self: mut_dict) -> Result
co_object_t *co_mut_dict_free(co_ctx_t *ctx, co_object_t *self);

// (self: mut_dict, key: any, type_: type, value: any) -> mut_dict
co_object_t *co_mut_dict_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *type_, co_object_t *value);

// (self: mut_dict, key: any, value: any) -> mut_dict
co_object_t *co_mut_dict_set(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *value);

// (self: mut_dict, key: any) -> (type, any) | Err
co_object_t *co_mut_dict_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any) -> any | Err
co_object_t *co_mut_dict_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any) -> (mut_dict, type, any) | Err
co_object_t *co_mut_dict_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any) -> mut_dict | Err
co_object_t *co_mut_dict_del(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any, type_: type) -> bool
co_object_t *co_mut_dict_hasitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *type_);

// (self: mut_dict, key: any) -> bool
co_object_t *co_mut_dict_has(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, other: mut_dict) -> mut_dict
co_object_t *co_mut_dict_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: mut_dict) -> list[(any, type, any)]
co_object_t *co_mut_dict_items(co_ctx_t *ctx, co_object_t *self);

// (self: mut_dict) -> list[(any, any)]
co_object_t *co_mut_dict_entries(co_ctx_t *ctx, co_object_t *self);

#endif
