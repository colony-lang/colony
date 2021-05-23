#ifndef CO_I64_H
#define CO_I64_H

#include "object_common.h"

co_object_t *co_i64_new(co_ctx_t *ctx, int64_t v);
co_object_t *co_i64_free(co_ctx_t *ctx, co_object_t *self);

#endif
