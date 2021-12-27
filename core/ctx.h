#ifndef CO_CTX_H
#define CO_CTX_H

#include <stdlib.h>

struct co_ctx_t;

typedef struct co_ctx_t {
    struct co_ctx_t *root;
    struct co_ctx_t *parent;
} co_ctx_t;

struct co_ctx_t *co_ctx_new(struct co_ctx_t *parent);
int co_ctx_free(struct co_ctx_t *ctx);

#endif