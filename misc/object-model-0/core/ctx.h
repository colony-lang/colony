#ifndef CO_CTX_H
#define CO_CTX_H

struct co_ctx_t;

#include <stdlib.h>

#include "../core/object.h"

typedef struct co_ctx_t {
    struct co_object_t *parent;
} co_ctx_t;

struct co_object_t *co_ctx_new(struct co_object_t *parent);
struct co_object_t *co_ctx_free(struct co_object_t *self);

#endif
