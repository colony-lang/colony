#include "frame.h"

struct co_frame_t *co_frame_new(struct co_ctx_t *ctx, struct co_frame_t *parent) {
    co_frame_t *frame = malloc(sizeof(co_frame_t));
    frame->ctx = ctx;
    frame->parent = parent;
    frame->regs = (co_object_t){}; // FIXME:
    return frame;
}

int co_frame_free(struct co_ctx_t *ctx, struct co_frame_t *frame) {
    co_object_decref_c(ctx, frame->regs);
    free(frame);
}
