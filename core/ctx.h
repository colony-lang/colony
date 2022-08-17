#ifndef CO_CTX_H
#define CO_CTX_H

struct co_ctx_t;

#include <stdlib.h>
#include "../object/object.h"


typedef struct co_ctx_t {
    struct co_ctx_t *parent;
    
    // C array of ctx's
    size_t ctxs_cap;
    size_t ctxs_len;
    struct co_ctx_t **ctxs;

    // C array of objects
    size_t regs_cap;
    size_t regs_len;
    struct co_object_t *regs;
} co_ctx_t;

struct co_ctx_t *co_ctx_new(void);
struct co_ctx_t *co_ctx_spawn(struct co_ctx_t *ctx);
int co_ctx_free(struct co_ctx_t *ctx);

#endif
