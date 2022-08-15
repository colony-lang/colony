#ifndef CO_MODULE_H
#define CO_MODULE_H

#include "../core/ctx.h"
#include "object.h"

struct co_object_t co_module_new(struct co_ctx_t *ctx, struct co_object_t obj);
struct co_object_t co_module_free(struct co_ctx_t *ctx, struct co_object_t obj);

#endif
