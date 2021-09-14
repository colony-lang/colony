#ifndef CO_CTX_H
#define CO_CTX_H

struct _co_ctx_t;
struct co_ctx_t;

#include <stdlib.h>

#include "object.h"

/*
ctx_A: Context = Context(None, None, None)

ctx_A.on_message((message: str) -> Result[str, str] {
    message == 'set_x_10' ? {
        ns.x = 10
        Ok('')
    } : message == 'set_y_20' ? {
        ns.y = 20
        Ok('')
    } : message == 'set_z' ? {
        ns.z = ns.x + ns.y
        Ok('')
    } : message == 'get_z' ? {
        ns.z
        Ok('')
    } : {
        Err('ctx_A: unknown message')
    }
})

ctx_A.post_message('set_x_10')
ctx_A.post_message('set_y_20')
ctx_A.post_message('set_z')

// NOTE: post_message returns `Future[str]`
z: str = ctx_A.post_message('get_z').await()
*/

typedef struct _co_ctx_t {
    size_t rc;
    struct co_object_t *parent;         // parent: Option[Context] = None
    struct co_object_t *ns;             // ns: Option[Namespace] = None
    struct co_object_t *on_message_cb;  // on_message_cb: Option[fn[Callable, Result[str, str]]] = None
    struct co_object_t *message_queue;  // message_queue: Queue[str]() = Queue[str]()
} _co_ctx_t;

typedef struct co_ctx_t {
    CO_OBJECT_HEAD;
    struct _co_ctx_t *ctx;
} co_ctx_t;

struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns, struct co_object_t *on_message_cb);
struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self);
struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb /* fn[Callable, Result[str, str]] */);
struct co_object_t * /* Future[str] */ co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message /* str */);

#endif
