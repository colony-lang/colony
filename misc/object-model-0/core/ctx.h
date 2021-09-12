#ifndef CO_CTX_H
#define CO_CTX_H

struct co_ctx_t;

#include <stdlib.h>

typedef struct co_ctx_t {
    size_t rc;
    struct co_ctx_t *root; // auto
    struct co_ctx_t *parent;
} co_ctx_t;

struct co_ctx_t *co_ctx_new(struct co_ctx_t *parent);
void co_ctx_free(struct co_ctx_t *ctx);
void co_ctx_rel(struct co_ctx_t *ctx);

#endif
