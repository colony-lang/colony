#ifndef CO_DICT_H
#define CO_DICT_H

struct co_dict_item_t;
struct co_dict_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_dict_item_t {
    struct co_object_t *key;   // any
    struct co_object_t *value; // any
} co_dict_item_t;

typedef struct co_dict_t {
    size_t len;
    struct co_dict_item_t *items;
} co_dict_t;

// (cls: DictType, len: 'size_t'=0, items: Option['co_dict_item_t *']=None) -> dict[any, any]
struct co_object_t *co_dict_type_new(struct co_ctx_t *ctx, struct co_object_t *cls, size_t len, co_dict_item_t *items);

// (cls: DictType, types: (key: any, value: any)) -> dict[types.key, types.value]
struct co_object_t *co_dict_type_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key_type, struct co_object_t *value_type);

// (self: dict) -> Result
struct co_object_t *co_dict_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: dict, key: any, value: any) -> dict
struct co_object_t *co_dict_set(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key, struct co_object_t *value);

// (self: dict, key: any) -> any | Err
struct co_object_t *co_dict_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: dict, key: any) -> dict | Err
struct co_object_t *co_dict_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: dict, key: any) -> bool
struct co_object_t *co_dict_has(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: dict, other: dict) -> dict
struct co_object_t *co_dict_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: dict) -> list[(any, any)]
struct co_object_t *co_dict_items(struct co_ctx_t *ctx, struct co_object_t *self);

#endif
