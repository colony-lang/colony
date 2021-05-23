#ifndef CO_VALUE_H
#define CO_VALUE_H

#include <stdlib.h>
#include "ctx.h"
#include "object_common.h"
#include "i64.h"

#define CO_INC_REF (ctx, obj) { obj->rc++; }
#define CO_DEC_REF (ctx, obj) { obj->rc--; if (obj.rc == 0) co_object_free(ctx, obj); }

co_object_t *co_object_new(co_ctx_t * ctx, co_kind_t kind, co_value_t value);
co_object_t *co_object_free(co_ctx_t * ctx, co_object_t *self);

#endif
