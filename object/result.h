#ifndef CO_RESULT_H
#define CO_RESULT_H

struct co_result_t;

#include <stdlib.h>
#include "./object.h"
#include "./value.h"

// Result: type = Ok | Err
typedef struct co_result_t {
    struct co_object_t *V; // type
    struct co_object_t *E; // type
} co_result_t;

// (V: type, E: type) -> typeof(Result[V, E])
struct co_object_t *co_result_type_new(struct co_ctx_t *ctx,
                                       struct co_object_t *V,
                                       struct co_object_t *E);

// (V: type, E: type) -> typeof(Result[V, E])
struct co_object_t *co_result_type_get(struct co_ctx_t *ctx,
                                       struct co_object_t *V,
                                       struct co_object_t *E);

// (typeof(Result[V, E])) -> Result
struct co_object_t *co_result_type_free(struct co_ctx_t *ctx,
                                        struct co_object_t *cls);

// (self: Result) -> Result
// self: Result == self: Ok | Err
struct co_object_t *co_result_free(struct co_ctx_t *ctx,
                                   struct co_object_t *self);

#endif
