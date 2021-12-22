#ifndef CO_OPTION_H
#define CO_OPTION_H

struct co_option_t;

#include <stdlib.h>
#include "./object.h"

// Option: type = Some | None
typedef struct co_option_t {
    struct co_object_t *some_type;
    struct co_object_t *none_type;
} co_option_t;

// // (some_type: type, none_type: type) -> Option[some_type]
// struct co_object_t *co_option_new(struct co_ctx_t *ctx, struct co_object_t *some_type, struct co_object_t *none_type);

// // (self: Option) -> Result
// struct co_object_t *co_option_free(struct co_ctx_t *ctx, struct co_object_t *self);

#endif
