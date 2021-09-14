#include "ctx.h"

struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns, struct co_object_t *on_message_cb) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_ctx_t));
    self->rc = 1;
    self->k = CO_KIND_CTX;
    
    // parent
    CO_CTX(self)->parent = parent;

    if (parent) {
        co_ref(ctx, parent);
    }

    // ns
    CO_CTX(self)->ns = ns;

    if (ns) {
        co_ref(ctx, ns);
    }

    // on_message_cb
    CO_CTX(self)->on_message_cb = on_message_cb;

    if (on_message_cb) {
        co_ref(ctx, on_message_cb);
    }

    // message_queue
    co_object_t *message_queue = NULL; // FIXME: co_mut_list_new_with_cap(self, 8);
    CO_CTX(self)->message_queue = message_queue;

    return self;
}

struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self) {
    co_unref(ctx, CO_CTX(self)->parent);
    co_unref(ctx, CO_CTX(self)->ns);
    co_unref(ctx, CO_CTX(self)->on_message_cb);
    co_unref(ctx, CO_CTX(self)->message_queue);
    free(self);
    return NULL;
}

struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb /* fn[Callable, object] */) {
    // on_message_cb
    if (CO_CTX(self)->on_message_cb) {
        co_unref(ctx, CO_CTX(self)->on_message_cb);
    }

    CO_CTX(self)->on_message_cb = on_message_cb;
    co_ref(ctx, on_message_cb);

    // FIXME: probaby return None of Optional[object]
    return NULL;
}

struct co_object_t *co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message /* str */) {
    // FIXME:
    //  co_object_t *message_queue = co_mut_list_append(ctx, context->message_queue, message);
    // NOTE: message_queue is same as context->message_queue

    // FIXME: probaby return None of Optional[object]
    return NULL;
}
