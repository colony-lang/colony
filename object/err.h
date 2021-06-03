#ifndef CO_ERR_H
#define CO_ERR_H

struct co_err_t;

#include <stdlib.h>
#include "./object.h"

// Err: type = struct(...)
typedef struct co_err_t {
    struct co_object_t *result_type;    // type
                                        // used for Err[E] type
                                        // can be NULL in case co_ctx_err
    
    struct co_object_t *type;           // typeof(Err[result_type.E])
                                        // used for Err[E] instance
                                        // can be NULL in case co_ctx_err
    
    struct co_object_t *e;              // result_type.E
                                        // used for Err[E] instance
} co_err_t;

// (result_type: Result[V, E]) -> typeof(Err[E])
struct co_object_t *co_err_type_new(struct co_ctx_t *ctx,
                                    struct co_object_t *result_type);

// (result_type: Result[V, E]) -> typeof(Err[E])
struct co_object_t *co_err_type_get(struct co_ctx_t *ctx,
                                    struct co_object_t *result_type);

// (typeof(Err[E])) -> Result
struct co_object_t *co_err_type_free(struct co_ctx_t *ctx,
                                     struct co_object_t *cls);

// (e: E) -> Err[E]
struct co_object_t *_co_err_new(struct co_ctx_t *ctx,
                                struct co_object_t *e);

// (cls: typeof(Err), e: E) -> Err[E]
struct co_object_t *co_err_new(struct co_ctx_t *ctx,
                               struct co_object_t *cls,
                               struct co_object_t *e);

// (self: Err) -> Result
struct co_object_t *co_err_free(struct co_ctx_t *ctx,
                                struct co_object_t *self);

#endif
