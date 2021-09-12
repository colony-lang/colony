#include "ctx.h"

struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns, struct co_object_t *on_message_cb) {
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

    // on_message_cb
    context->on_message_cb = on_message_cb;

    if (on_message_cb) {
        co_ref(ctx, on_message_cb);
    }

    // self (ctx object)
    co_object_t *self = co_object_new(parent, CO_KIND_CTX, (co_value_t){.ctx = context});
    self->rc = 1;
    
    // message_queue
    co_object_t *message_queue = NULL; // FIXME: co_mut_list_new_with_cap(self, 8);
    context->message_queue = message_queue;
    
    return self;
}

struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self) {
    co_ctx_t *context = self->v.ctx;
    co_unref(ctx, context->parent);
    co_unref(ctx, context->ns);
    co_unref(ctx, context->on_message_cb);
    co_unref(ctx, context->message_queue);
    free(self);
    return NULL;
}

struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb /* fn[Callable, object] */) {
    co_ctx_t *context = self->v.ctx;
    
    // on_message_cb
    if (context->on_message_cb) {
        co_unref(ctx, context->on_message_cb);
    }

    context->on_message_cb = on_message_cb;
    co_ref(ctx, on_message_cb);

    // FIXME: probaby return None of Optional[object]
    return NULL;
}

struct co_object_t *co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message /* str */) {
    co_ctx_t *context = self->v.ctx;

    // FIXME:
    //  co_object_t *message_queue = co_mut_list_append(ctx, context->message_queue, message);
    // NOTE: message_queue is same as context->message_queue
    
    // FIXME: probaby return None of Optional[object]
    return NULL;
}
