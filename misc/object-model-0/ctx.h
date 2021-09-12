#ifndef CO_CTX_H
#define CO_CTX_H

struct co_ctx_t;

#include <stdlib.h>

#include "object.h"

/*
ctx_A: Context = Context(None, None, (message: str) -> object {
    message == 'set_x_10' ? {
        ns.x = 10
    } : message == 'set_y_20' ? {
        ns.y = 20
    } : message == 'set_z' ? {
        ns.z = ns.x + ns.y
    } : message == 'get_z' ? {
        ns.z
    } : {
        panic('ctx_A: unknown message')
    }
})

ctx_A.post_message('set_x_10')
ctx_A.post_message('set_y_20')
ctx_A.post_message('set_z')
z := ctx_A.post_message('get_z')
*/

typedef struct co_ctx_t {
    struct co_object_t *parent;         // parent: Option[Context] = None
    struct co_object_t *ns;             // ns: Option[Namespace] = None
    struct co_object_t *on_message_cb;  // on_message_cb: Option[fn[Callable, object]] = None
    struct co_object_t *message_queue;  // Queue[str]()
} co_ctx_t;

struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns, struct co_object_t *on_message_cb);
struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self);
struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb /* fn[Callable, object] */);
struct co_object_t *co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message /* str */);

#endif
