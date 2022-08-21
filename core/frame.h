#ifndef CO_FRAME_H
#define CO_FRAME_H

struct co_frame_t;

#include "ctx.h"
#include "ns.h"

typedef struct co_frame_t {
    struct co_ctx_t *ctx;
    struct co_frame_t *parent;
    struct co_ns_t *ns;
} co_frame_t;

struct co_frame_t *co_frame_new(struct co_ctx_t *ctx, struct co_frame_t *parent);
int co_frame_free(struct co_frame_t *frame);

#endif
