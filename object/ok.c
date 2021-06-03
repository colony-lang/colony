#include "./ok.h"

// (result_type: Result[V, E]) -> typeof(Ok[V])
struct co_object_t *co_ok_type_new(struct co_ctx_t *ctx,
                                   struct co_object_t *result_type) {
    return co_ok_type_get(ctx, result_type);
}

// (result_type: Result[V, E]) -> typeof(Ok[V])
struct co_object_t *co_ok_type_get(struct co_ctx_t *ctx,
                                   struct co_object_t *result_type) {
    // alloc ok
    co_ok_t *ok = co_ctx_mem_alloc(ctx, sizeof(co_ok_t));

    // set result_type
    ok->result_type = result_type;
    CO_OBJECT_INC_RC(ctx, result_type);

    // type is not set
    ok->type = NULL;

    // v is not set
    ok->v = NULL;

    // create cls; cls == Result
    co_object_t *cls = co_object_new(ctx, CO_KIND_OK, (co_value_t){.ok = ok});
    return cls;
}

// (typeof(Ok[V])) -> Result
struct co_object_t *co_ok_type_free(struct co_ctx_t *ctx,
                                    struct co_object_t *cls) {
    // get value, result_value
    co_ok_t *ok = cls->value.ok;
    
    // unset result_type
    co_object_t *result_type = ok->result_type;
    CO_OBJECT_DEC_RC(ctx, result_type);
    
    // free result_value, cls
    co_ctx_mem_free(ctx, ok);
    co_ctx_mem_free(ctx, cls);

    // ok
    co_object_t *res = co_ctx_ok(ctx, "`Ok` type freed");
    return res;
}

// (v: V) -> Ok[V]
struct co_object_t *_co_ok_new(struct co_ctx_t *ctx,
                               struct co_object_t *v) {
    // alloc ok
    co_ok_t *ok = co_ctx_mem_alloc(ctx, sizeof(co_ok_t));

    // result_type is not set
    ok->result_type = NULL;

    // type is not set
    ok->type = NULL;

    // set v
    ok->v = v;
    CO_OBJECT_INC_RC(ctx, v);

    // create cls; cls == Result
    co_object_t *self = co_object_new(ctx, CO_KIND_OK, (co_value_t){.ok = ok});
    return self;
}

// (cls: typeof(Ok), v: V) -> Ok[V]
struct co_object_t *co_ok_new(struct co_ctx_t *ctx,
                              struct co_object_t *cls,
                              struct co_object_t *v) {
    // alloc ok
    co_ok_t *ok = co_ctx_mem_alloc(ctx, sizeof(co_ok_t));

    // result_type is not set
    ok->result_type = NULL;

    // set result_type
    ok->type = cls;
    CO_OBJECT_INC_RC(ctx, cls);

    // set v
    ok->v = v;
    CO_OBJECT_INC_RC(ctx, v);

    // create cls; cls == Result
    co_object_t *self = co_object_new(ctx, CO_KIND_OK, (co_value_t){.ok = ok});
    return self;
}

// (self: Ok[V]) -> Result
struct co_object_t *co_ok_free(struct co_ctx_t *ctx,
                               struct co_object_t *self) {
    // get value, result_value
    co_ok_t *ok = self->value.ok;
    
    // unset result_type
    co_object_t *result_type = ok->result_type;

    if (result_type != NULL) {
        CO_OBJECT_DEC_RC(ctx, result_type);
    }

    // unset type
    co_object_t *type = ok->type;

    if (type != NULL) {
        CO_OBJECT_DEC_RC(ctx, type);
    }
    
    // unset v
    co_object_t *v = ok->v;

    if (v != NULL) {
        CO_OBJECT_DEC_RC(ctx, v);
    }

    // free result_value, cls
    co_ctx_mem_free(ctx, ok);
    co_ctx_mem_free(ctx, self);

    // ok
    co_object_t *res = co_ctx_ok(ctx, "`Ok` instance freed");
    return res;
}
