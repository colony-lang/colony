#include "ns.h"

/*
 * c-level
 */
// () -> Namespace
struct co_object_t *co_ns_new(struct co_ctx_t *ctx) {
    co_ns_t *ns = co_ctx_mem_alloc(ctx, sizeof(co_ns_t));
    ns->len = 8;
    ns->items = co_ctx_mem_alloc(ctx, ns->len * sizeof(co_ns_item_t));
    co_object_t *self = co_object_new(ctx, CO_KIND_NS, (co_value_t){.ns = ns});
    return self;
}

// (self: Namespace) -> Result
struct co_object_t *co_ns_free(struct co_ctx_t *ctx,
                               struct co_object_t *self) {
    co_ns_t *ns = self->value.ns;

    co_ctx_mem_free(ctx, ns->items);
    ns->items = NULL;

    co_ctx_mem_free(ctx, ns);
    self->value.ns = NULL;

    co_ctx_mem_free(ctx, self);
    return NULL;
}

// (self: Namespace, key: str, value: any) -> Namespace
struct co_object_t *co_ns_set(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key,
                              struct co_object_t *type,
                              struct co_object_t *value) {
    return NULL;
}

// (self: Namespace, key: str) -> (type, any) | Err
struct co_object_t *co_ns_get(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key) {
    return NULL;
}

// (self: Namespace, key: str) -> (Namespace, (type, any)) | Err
struct co_object_t *co_ns_del(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key) {
    return NULL;
}

// (self: Namespace, key: str) -> bool
struct co_object_t *co_ns_has(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *key) {
    return NULL;
}

// (self: Namespace, other: Namespace) -> Namespace
struct co_object_t *co_ns_add(struct co_ctx_t *ctx,
                              struct co_object_t *self,
                              struct co_object_t *other) {
    return NULL;
}

// (self: Namespace) -> list[(str, type, any)]
struct co_object_t *co_ns_items(struct co_ctx_t *ctx,
                                struct co_object_t *self) {
    return NULL;
}

/*
 * colony-level
 */
struct co_object_t *co_ns_create_co_type(struct co_ctx_t *ctx) {
    // co_object_t *cls = co_

    return NULL;
}
