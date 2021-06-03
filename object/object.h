#ifndef CO_OBJECT_H
#define CO_OBJECT_H

struct co_object_t;

#include <stdlib.h>
#include <stdint.h>
#include "../core/ctx.h"
#include "./kind.h"
#include "./value.h"

#define CO_OBJECT_INC_RC(ctx, obj) do { \
    ((struct co_object_t *)(obj))->rc++; \
} while(0)

#define CO_OBJECT_DEC_RC(ctx, obj) do { \
    if (obj == NULL) break; \
    ((struct co_object_t *)(obj))->rc--; \
    if (((struct co_object_t *)(obj))->rc == 0) { \
        co_object_free(ctx, (struct co_object_t *)(obj)); \
    } \
} while(0)

typedef struct co_object_t {
    size_t rc;
    enum co_kind_t kind;
    union co_value_t value;
} co_object_t;

co_object_t *co_object_new(struct co_ctx_t * ctx, co_kind_t kind, co_value_t value);
co_object_t *co_object_free(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> str | Err
co_object_t *co_object_repr(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> u64 | Err
co_object_t *co_object_hash(struct co_ctx_t * ctx, co_object_t *self);

#endif
