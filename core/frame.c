#include "frame.h"

struct co_frame_t *co_frame_new(struct co_ctx_t *ctx, struct co_frame_t *parent) {
    co_frame_t *frame = malloc(sizeof(co_frame_t));
    frame->ctx = ctx;
    frame->parent = parent;
    frame->ns = co_ns_new(ctx, frame);
    return frame;
}

int co_frame_free(struct co_ctx_t *ctx, struct co_frame_t *frame) {
    int rc;
    rc = co_ns_free(ctx, frame->ns);
    free(frame);
}
