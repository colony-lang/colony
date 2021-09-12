#include "ctx.h"

struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns) {
    co_ctx_t *context = (co_ctx_t*)malloc(sizeof(co_ctx_t));

    // parent
    context->parent = parent;

    if (parent) {
        co_ref(ctx, parent);
    }

    // ns
    context->ns = ns;

    if (ns) {
        co_ref(ctx, ns);
    }

    // object
    co_object_t *self = co_object_new(parent, CO_KIND_CTX, (co_value_t){.ctx = context});
    self->rc = 1;
    return ctx;
}

struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self) {
    co_ctx_t *context = self->v.ctx;
    co_unref(ctx, context->parent);
    co_unref(ctx, context->ns);
    free(self);
    return NULL;
}
