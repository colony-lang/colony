#ifndef CO_DICT_H
#define CO_DICT_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"
#include "dict_item.h"

typedef struct co_dict_t {
    size_t len;
    co_dict_item_t *items;
} co_dict_t;

// () -> dict
co_object_t *co_dict_new(co_ctx_t *ctx);

// (self: dict) -> Result
co_object_t *co_dict_free(co_ctx_t *ctx, co_object_t *self);

// (self: dict, key: any, type_: type, value: any) -> dict
co_object_t *co_dict_setitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *type_, co_object_t *value);

// (self: dict, key: any, value: any) -> dict
co_object_t *co_dict_set(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *value);

// (self: dict, key: any) -> (type, any) | Err
co_object_t *co_dict_getitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> any | Err
co_object_t *co_dict_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> (dict, type, any) | Err
co_object_t *co_dict_delitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> dict | Err
co_object_t *co_dict_del(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any, type_: type) -> bool
co_object_t *co_dict_hasitem(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *type_);

// (self: dict, key: any) -> bool
co_object_t *co_dict_has(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, other: dict) -> dict
co_object_t *co_dict_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: dict) -> list[(any, type, any)]
co_object_t *co_dict_items(co_ctx_t *ctx, co_object_t *self);

// (self: dict) -> list[(any, any)]
co_object_t *co_dict_entries(co_ctx_t *ctx, co_object_t *self);

#endif
