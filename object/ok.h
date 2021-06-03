#ifndef CO_OK_H
#define CO_OK_H

struct co_ok_t;

#include <stdlib.h>
#include "./object.h"

// Ok: type = struct(...)
typedef struct co_ok_t {
    struct co_object_t *result_type;    // type
                                        // used for Ok[V] type
                                        // can be NULL in case co_ctx_ok
    
    struct co_object_t *type;           // typeof(Ok[result_type.V])
                                        // used for Ok[V] instance
                                        // can be NULL in case co_ctx_ok
    
    struct co_object_t *v;              // result_type.V
                                        // used for Ok[V] instance
} co_ok_t;

// (result_type: Result[V, E]) -> typeof(Ok[V])
struct co_object_t *co_ok_type_new(struct co_ctx_t *ctx,
                                   struct co_object_t *result_type);

// (result_type: Result[V, E]) -> typeof(Ok[V])
struct co_object_t *co_ok_type_get(struct co_ctx_t *ctx,
                                   struct co_object_t *result_type);

// (typeof(Ok[V])) -> Result
struct co_object_t *co_ok_type_free(struct co_ctx_t *ctx,
                                    struct co_object_t *cls);

// (v: V) -> Ok[V]
struct co_object_t *_co_ok_new(struct co_ctx_t *ctx,
                               struct co_object_t *v);

// (cls: typeof(Ok), v: V) -> Ok[V]
struct co_object_t *co_ok_new(struct co_ctx_t *ctx,
                              struct co_object_t *cls,
                              struct co_object_t *v);

// (self: Ok[V]) -> Result
struct co_object_t *co_ok_free(struct co_ctx_t *ctx,
                               struct co_object_t *self);

#endif
