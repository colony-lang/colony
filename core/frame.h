#ifndef CO_FRAME_H
#define CO_FRAME_H

struct co_frame_t;

#include "ctx.h"
#include "../object/object.h"

typedef struct co_frame_t {
    struct co_ctx_t *ctx;
    struct co_frame_t *parent;
    
    // array of regs, repeating seq of:
    //  +0: name: str
    //  +1: type: type
    //  +2: value: object
    struct co_object_t regs;   // list<object>
} co_frame_t;

struct co_frame_t *co_frame_new(struct co_ctx_t *ctx, struct co_frame_t *parent);
int co_frame_free(struct co_ctx_t *ctx, struct co_frame_t *frame);

#endif
