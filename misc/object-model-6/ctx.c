#include "ctx.h"

/*
struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns, struct co_object_t *on_message_cb) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_ctx_t));
    self->k = CO_KIND_CTX;
    self->v.ctx = (_co_ctx_t*)malloc(sizeof(_co_ctx_t));
    self->v.ctx->rc = 1;

    // parent
    self->v.ctx->parent = parent;

    if (parent) {
        co_ref(ctx, parent);
    }

    // ns
    self->v.ctx->ns = ns;

    if (ns) {
        co_ref(ctx, ns);
    }

    // on_message_cb
    self->v.ctx->on_message_cb = on_message_cb;

    if (on_message_cb) {
        co_ref(ctx, on_message_cb);
    }

    // message_queue
    co_object_t *message_queue = NULL; // FIXME: co_mut_list_new_with_cap(self, 8);
    self->v.ctx->message_queue = message_queue;

    return self;
}

struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self) {
    co_unref(ctx, self->v.ctx->parent);
    co_unref(ctx, self->v.ctx->ns);
    co_unref(ctx, self->v.ctx->on_message_cb);
    co_unref(ctx, self->v.ctx->message_queue);
    free(self->v.ctx);
    free(self);
    return NULL;
}

struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb) {
    // on_message_cb
    if (self->v.ctx->on_message_cb) {
        co_unref(ctx, self->v.ctx->on_message_cb);
    }

    self->v.ctx->on_message_cb = on_message_cb;
    co_ref(ctx, on_message_cb);

    // FIXME: probaby return None of Optional[object]
    return NULL;
}

struct co_object_t *co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message) {
    // FIXME:
    //  co_object_t *message_queue = co_mut_list_append(ctx, context->message_queue, message);
    // NOTE: message_queue is same as context->message_queue

    // FIXME: probaby return None of Optional[object]
    return NULL;
}
*/