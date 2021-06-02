#ifndef CO_BUILTINS_H
#define CO_BUILTINS_H

#include <stdlib.h>
#include "../core/ctx.h"
#include "../object/ns.h"

// () -> Result
struct co_object_t *co_builtins_init(struct co_ctx_t *ctx);

#endif
