#ifndef CO_CTX_H
#define CO_CTX_H

#include <stdlib.h>

struct co_ctx_t;

typedef struct co_ctx_t {
    struct co_ctx_t *parent;    // parent context, default NULL which means root
    void *ns_types;      // dict[str, type]
    void *ns_values;     // dict[str, any]
} co_ctx_t;

co_ctx_t *co_ctx_new(struct co_ctx_t *parent);
co_ctx_t *co_ctx_new_with_ns(struct co_ctx_t *parent, void *ns_types, void *ns_values);
void co_ctx_free(co_ctx_t *ctx);
void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size);
void co_ctx_mem_free(co_ctx_t *ctx, void *ptr);
void *co_ctx_eval(co_ctx_t *ctx, void *code);

#endif
