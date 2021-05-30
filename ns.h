#ifndef CO_NS_H
#define CO_NS_H

struct co_ns_item_t
struct co_ns_t;

#include <stdlib.h>
#include "ctx.h"
#include "object.h"

typedef struct co_ns_item_t {
    struct co_object_t *key;   // any
    struct co_object_t *type;   // any
    struct co_object_t *value; // any
} co_ns_item_t;

typedef struct co_ns_t {
    size_t len;
    struct co_ns_item_t *items;
} co_dict_t;

// (cls: DictType, len: 'size_t'=0, items: Option['co_dict_item_t *']=None) -> dict[any, any]
co_object_t *co_dict_type_new(co_ctx_t *ctx, co_object_t *cls, size_t len, co_dict_item_t *items);

// (cls: DictType, types: (key: any, value: any)) -> dict[types.key, types.value]
co_object_t *co_dict_type_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key_type, co_object_t *value_type);

// (self: dict) -> Result
co_object_t *co_dict_free(co_ctx_t *ctx, co_object_t *self);

// (self: dict, key: any, value: any) -> dict
co_object_t *co_dict_set(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *value);

// (self: dict, key: any) -> any | Err
co_object_t *co_dict_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> dict | Err
co_object_t *co_dict_del(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> bool
co_object_t *co_dict_has(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, other: dict) -> dict
co_object_t *co_dict_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: dict) -> list[(any, any)]
co_object_t *co_dict_items(co_ctx_t *ctx, co_object_t *self);


#endif
