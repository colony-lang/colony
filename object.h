#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"

#define CO_OBJECT_INC_RC (ctx, obj) { obj->rc++; }

#define CO_OBJECT_DEC_RC (ctx, obj) { \
    obj->rc--; \
    if (obj.rc == 0) { \
        co_object_free(ctx, obj); \
    } \
}

co_object_t *co_object_new(co_ctx_t * ctx, co_kind_t kind, co_value_t value);
co_object_t *co_object_free(co_ctx_t * ctx, co_object_t *self);

// (self: any) -> str | Err
co_object_t *co_object_repr(co_ctx_t * ctx, co_object_t *self);

// (self: any) -> u64 | Err
co_object_t *co_object_hash(co_ctx_t * ctx, co_object_t *self);

#endif
