#include "./result.h"

// (V: type, E: type) -> typeof(Result[V, E])
struct co_object_t *co_result_type_new(struct co_ctx_t *ctx,
                                       struct co_object_t *V,
                                       struct co_object_t *E) {
    return co_result_type_get(ctx, V, E);
}

// (V: type, E: type) -> typeof(Result[V, E])
struct co_object_t *co_result_type_get(struct co_ctx_t *ctx,
                                       struct co_object_t *V,
                                       struct co_object_t *E) {
    // alloc value
    co_result_t *result = co_ctx_mem_alloc(ctx, sizeof(co_result_t));
    
    // set V
    result->V = V;
    CO_OBJECT_INC_RC(ctx, V);
    
    // set E
    result->E = E;
    CO_OBJECT_INC_RC(ctx, E);

    // cls
    co_object_t *cls = co_object_new(ctx, CO_KIND_RESULT, (co_value_t){.result = result});
    return cls;
}

// (typeof(Result[V, E])) -> Result
struct co_object_t *co_result_type_free(struct co_ctx_t *ctx,
                                        struct co_object_t *cls) {
    // get value, value
    co_result_t *result = cls->value.result;
    
    // unset V
    co_object_t *V = result->V;
    CO_OBJECT_DEC_RC(ctx, V);
    
    // unset E
    co_object_t *E = result->E;
    CO_OBJECT_DEC_RC(ctx, E);
    
    // free result, cls
    co_ctx_mem_free(ctx, result);
    co_ctx_mem_free(ctx, cls);

    // ok
    co_object_t *res = co_ctx_ok(ctx, "`Result` type freed");
    return res;
}

// (self: Result) -> Result
// self: Result == self: Ok | Err
struct co_object_t *co_result_free(struct co_ctx_t *ctx,
                                   struct co_object_t *self) {
    switch (self->kind) {
        case CO_KIND_OK:
            return co_ok_free(ctx, self);
        case CO_KIND_ERR:
            return co_err_free(ctx, self);
        default:
            return co_ctx_err(ctx, "did not recevie `self` of `Result` type");
    }
}
