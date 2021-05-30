#ifndef CO_CTX_H
#define CO_CTX_H

struct co_ctx_t;

#include <stdlib.h>
#include "object.h"

typedef struct co_ctx_t {
    struct co_ctx_t *parent;    // parent context, default NULL which means root
    struct co_object_t *ns;     // attr: type = value; ... 
} co_ctx_t;

co_ctx_t *co_ctx_new(co_ctx_t *parent);
co_ctx_t *co_ctx_new_with_ns(co_ctx_t *parent, struct co_object_t *ns);
void co_ctx_free(co_ctx_t *ctx);
void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size);
void co_ctx_mem_free(co_ctx_t *ctx, void *ptr);
struct co_object_t * *co_ctx_eval(co_ctx_t *ctx, void *code);

#endif
