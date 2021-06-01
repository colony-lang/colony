#ifndef CO_BUILTINS_H
#define CO_BUILTINS_H

#include <stdlib.h>
#include "ctx.h"
#include "ns.h"

// () -> Result
struct co_object_t *co_builtins_init(struct co_ctx_t *ctx);

#endif
