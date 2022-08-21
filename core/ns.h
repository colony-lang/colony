#ifndef CO_NS_H
#define CO_NS_H

struct co_ns_t;

#include <stdlib.h>
#include "ctx.h"
#include "frame.h"

typedef struct co_ns_t {
    struct co_ctx_t *ctx;
    struct co_frame_t *frame;

    // attrs
    size_t attrs_cap;
    size_t attrs_len;
    struct co_object_t *attrs;
} co_ns_t;

struct co_ns_t *co_ns_new(struct co_ctx_t *ctx, struct co_frame_t *frame);
int co_ns_free(struct co_ctx_t *ctx, struct co_ns_t *ns);

struct co_object_t co_ns_getattr(struct co_ns_t *ns, struct co_object_t attr);
struct co_object_t co_ns_setattr(struct co_ns_t *ns, struct co_object_t attr, struct co_object_t value);

#endif
