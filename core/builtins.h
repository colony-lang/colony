#ifndef CO_BUILTINS_H
#define CO_BUILTINS_H

#include "ctx.h"
#include "../object/object.h"
#include "../object/module.h"

struct co_object_t co_builtins_c_populate_ctx(struct co_ctx_t *ctx);

#endif
