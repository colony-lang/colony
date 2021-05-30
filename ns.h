#ifndef CO_NS_H
#define CO_NS_H

struct co_ns_item_t;
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
} co_ns_t;

// // (cls: DictType, len: 'size_t'=0, items: Option['co_dict_item_t *']=None) -> dict[any, any]
// co_object_t *co_dict_type_new(co_ctx_t *ctx, co_object_t *cls, size_t len, co_ns_item_t *items);

// // (cls: DictType, types: (key: any, value: any)) -> dict[types.key, types.value]
// co_object_t *co_dict_type_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key_type, co_object_t *value_type);

/*
 * c-level
 */

// (self: dict) -> Result
struct co_object_t *co_ns_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: dict, key: any, value: any) -> dict
struct co_object_t *co_ns_set(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key,
                              struct co_object_t *type,
                              struct co_object_t *value);

// (self: ns, key: any) -> any | Err
struct co_object_t *co_ns_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: ns, key: any) -> ns | Err
struct co_object_t *co_ns_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: ns, key: any) -> bool
struct co_object_t *co_ns_has(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *key);

// (self: ns, other: ns) -> ns
struct co_object_t *co_ns_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: ns) -> list[(any, type, any)]
struct co_object_t *co_ns_items(struct co_ctx_t *ctx, struct co_object_t *self);

/*
 * colony-level
 */
struct co_object_t *co_ns_create_co_type(struct co_ctx_t *ctx);

#endif
