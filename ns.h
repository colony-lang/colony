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

/*
 * c-level
 */
// () -> Namespace
struct co_object_t *co_ns_new(struct co_ctx_t *ctx);

// (self: Namespace) -> Result
struct co_object_t *co_ns_free(struct co_ctx_t *ctx,
                               struct co_object_t *self);

// (self: Namespace, key: str, value: any) -> Namespace
struct co_object_t *co_ns_set(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key,
                              struct co_object_t *type,
                              struct co_object_t *value);

// (self: Namespace, key: str) -> (type, any) | Err
struct co_object_t *co_ns_get(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key);

// (self: Namespace, key: str) -> (Namespace, (type, any)) | Err
struct co_object_t *co_ns_del(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key);

// (self: Namespace, key: str) -> bool
struct co_object_t *co_ns_has(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key);

// (self: Namespace, other: Namespace) -> Namespace
struct co_object_t *co_ns_add(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *other);

// (self: Namespace) -> list[(str, type, any)]
struct co_object_t *co_ns_items(struct co_ctx_t *ctx,
                                struct co_object_t *self);

/*
 * colony-level
 */
struct co_object_t *co_ns_create_co_type(struct co_ctx_t *ctx);

#endif
