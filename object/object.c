#include "./object.h"

co_object_t *co_object_new(co_ctx_t * ctx, co_kind_t kind, co_value_t value) {
    co_object_t *self = co_ctx_mem_alloc(ctx, sizeof(co_object_t));
    self->rc = 1;
    self->kind = kind;
    self->value = value;
    return self;
}

co_object_t *co_object_free(co_ctx_t * ctx, co_object_t *self) {
    switch (self->kind) {
        case CO_KIND_TYPE:
            return NULL;
        case CO_KIND_BOOL:
            return NULL;
        case CO_KIND_U8:
            return NULL;
        case CO_KIND_U16:
            return NULL;
        case CO_KIND_U32:
            return NULL;
        case CO_KIND_U64:
            return NULL;
        case CO_KIND_I8:
            return NULL;
        case CO_KIND_I16:
            return NULL;
        case CO_KIND_I32:
            return NULL;
        case CO_KIND_I64:
            return co_i64_free(ctx, self);
        case CO_KIND_F32:
            return NULL;
        case CO_KIND_F64:
            return NULL;
        case CO_KIND_BYTES:
            return NULL;
        case CO_KIND_STR:
            return NULL;
        case CO_KIND_LIST:
            return NULL;
        case CO_KIND_MUT_LIST:
            return NULL;
        case CO_KIND_DICT:
            return NULL;
        case CO_KIND_MUT_DICT:
            return NULL;
        case CO_KIND_CODE:
            return NULL;
        case CO_KIND_FUNC:
            return NULL;
        case CO_KIND_CLOSURE:
            return NULL;
        case CO_KIND_TUPLE:
            return NULL;
        case CO_KIND_UNION:
            return NULL;
        case CO_KIND_OPTION:
            return NULL;
        case CO_KIND_SOME:
            return NULL;
        case CO_KIND_NONE:
            return NULL;
        case CO_KIND_RESULT:
            return co_result_free(ctx, self);
        case CO_KIND_OK:
            return co_ok_free(ctx, self);
        case CO_KIND_ERR:
            return co_err_free(ctx, self);
        case CO_KIND_PTR:
            return NULL;
        default:
            // err
            return co_ctx_err(ctx, "KindError, unknown kind");
    }
}
