#ifndef CO_MUT_DICT_H
#define CO_MUT_DICT_H

struct co_mut_dict_item_t;
struct co_mut_dict_t;

#include <stdlib.h>
#include "./object.h"

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
struct co_object_t *co_mut_dict_new(struct co_ctx_t *ctx, struct co_object_t *cls, size_t cap, size_t len, co_mut_dict_item_t *items);

// (self: mut_dict) -> Result
struct co_object_t *co_mut_dict_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: mut_dict, key: any, value: any) -> mut_dict
struct co_object_t *co_mut_dict_set(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key, struct co_object_t *value);

// (self: mut_dict, key: any) -> any | Err
struct co_object_t *co_mut_dict_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: mut_dict, key: any) -> mut_dict | Err
struct co_object_t *co_mut_dict_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: mut_dict, key: any) -> bool
struct co_object_t *co_mut_dict_has(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: mut_dict, other: mut_dict) -> mut_dict
struct co_object_t *co_mut_dict_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: mut_dict) -> list[(any, any)]
struct co_object_t *co_mut_dict_items(struct co_ctx_t *ctx, struct co_object_t *self);

#endif
