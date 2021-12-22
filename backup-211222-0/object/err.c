#include "./err.h"

// (result_type: Result[V, E]) -> typeof(Err[E])
struct co_object_t *co_err_type_new(struct co_ctx_t *ctx,
                                    struct co_object_t *result_type) {
    return co_err_type_get(ctx, result_type);
}

// (result_type: Result[V, E]) -> typeof(Err[E])
struct co_object_t *co_err_type_get(struct co_ctx_t *ctx,
                                    struct co_object_t *result_type) {
    // alloc err
    co_err_t *err = co_ctx_mem_alloc(ctx, sizeof(co_err_t));

    // set result_type
    err->result_type = result_type;
    CO_OBJECT_INC_RC(ctx, result_type);

    // type is not set
    err->type = NULL;

    // e is not set
    err->e = NULL;

    // cls
    co_object_t *cls = co_object_new(ctx, CO_KIND_ERR, (co_value_t){.err = err});
    return cls;
}

// (typeof(Err[E])) -> Result
struct co_object_t *co_err_type_free(struct co_ctx_t *ctx,
                                     struct co_object_t *cls) {
    // get value, result_value
    co_err_t *err = cls->value.err;
    
    // unset result_type
    co_object_t *result_type = err->result_type;
    CO_OBJECT_DEC_RC(ctx, result_type);
    
    // free result_value, cls
    co_ctx_mem_free(ctx, err);
    co_ctx_mem_free(ctx, cls);

    // ok
    co_object_t *res = co_ctx_ok(ctx, "`Err` type freed");
    return res;
}

// (e: E) -> Err[E]
struct co_object_t *_co_err_new(struct co_ctx_t *ctx,
                                struct co_object_t *e) {
    // alloc err
    co_err_t *err = co_ctx_mem_alloc(ctx, sizeof(co_err_t));

    // result_type is not set
    err->result_type = NULL;

    // type is not set
    err->type = NULL;

    // set e
    err->e = e;
    CO_OBJECT_INC_RC(ctx, e);

    // err
    co_object_t *self = co_object_new(ctx, CO_KIND_ERR, (co_value_t){.err = err});
    return self;
}

// (cls: typeof(Err), e: E) -> Err[E]
struct co_object_t *co_err_new(struct co_ctx_t *ctx,
                               struct co_object_t *cls,
                               struct co_object_t *e) {
    // alloc err
    co_err_t *err = co_ctx_mem_alloc(ctx, sizeof(co_err_t));

    // result_type is not set
    err->result_type = NULL;

    // set result_type
    err->type = cls;
    CO_OBJECT_INC_RC(ctx, cls);

    // set v
    err->e = e;
    CO_OBJECT_INC_RC(ctx, e);

    // err
    co_object_t *self = co_object_new(ctx, CO_KIND_ERR, (co_value_t){.err = err});
    return self;
}

// (self: Err) -> Result
struct co_object_t *co_err_free(struct co_ctx_t *ctx,
                                struct co_object_t *self) {
    // get value, result_value
    co_err_t *err = self->value.err;
    
    // unset result_type
    co_object_t *result_type = err->result_type;

    if (result_type != NULL) {
        CO_OBJECT_DEC_RC(ctx, result_type);
    }

    // unset type
    co_object_t *type = err->type;

    if (type != NULL) {
        CO_OBJECT_DEC_RC(ctx, type);
    }
    
    // unset e
    co_object_t *e = err->e;

    if (e != NULL) {
        CO_OBJECT_DEC_RC(ctx, e);
    }

    // free result_value, cls
    co_ctx_mem_free(ctx, err);
    co_ctx_mem_free(ctx, self);

    // ok
    co_object_t *res = co_ctx_ok(ctx, "`Err` instance freed");
    return res;
}
