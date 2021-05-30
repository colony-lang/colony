#ifndef CO_MUT_DICT_H
#define CO_MUT_DICT_H

struct co_mut_dict_item_t;
struct co_mut_dict_t;

#include <stdlib.h>
#include "ctx.h"
#include "object.h"

typedef struct co_mut_dict_item_t {
    struct co_object_t *key;   // any
    struct co_object_t *value; // any
} co_mut_dict_item_t;

typedef struct co_mut_dict_t {
    size_t cap;
    size_t len;
    struct co_mut_dict_item_t *items;
} co_mut_dict_t;

// (cap: u64, len: u64, items: mut_dict[any, any]) -> mut_dict[any, any]
co_object_t *co_mut_dict_new(co_ctx_t *ctx, co_object_t *cls, size_t cap, size_t len, co_mut_dict_item_t *items);

// (self: mut_dict) -> Result
co_object_t *co_mut_dict_free(co_ctx_t *ctx, co_object_t *self);

// (self: mut_dict, key: any, value: any) -> mut_dict
co_object_t *co_mut_dict_set(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *value);

// (self: mut_dict, key: any) -> any | Err
co_object_t *co_mut_dict_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any) -> mut_dict | Err
co_object_t *co_mut_dict_del(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, key: any) -> bool
co_object_t *co_mut_dict_has(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: mut_dict, other: mut_dict) -> mut_dict
co_object_t *co_mut_dict_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: mut_dict) -> list[(any, any)]
co_object_t *co_mut_dict_items(co_ctx_t *ctx, co_object_t *self);

#endif
