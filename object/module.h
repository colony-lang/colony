#ifndef CO_MODULE_H
#define CO_MODULE_H

#include "../core/ctx.h"
#include "object.h"

co_object_t co_module_new(co_ctx_t *ctx, co_object_t obj);
co_object_t co_module_free(co_ctx_t *ctx, co_object_t obj);

#endif
