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
            break;
        case CO_KIND_BOOL:
            break;
        case CO_KIND_U8:
            break;
        case CO_KIND_U16:
            break;
        case CO_KIND_U32:
            break;
        case CO_KIND_U64:
            break;
        case CO_KIND_I8:
            break;
        case CO_KIND_I16:
            break;
        case CO_KIND_I32:
            break;
        case CO_KIND_I64:
            co_i64_free(ctx, self);
            break;
        case CO_KIND_F32:
            break;
        case CO_KIND_F64:
            break;
        case CO_KIND_BYTES:
            break;
        case CO_KIND_STR:
            break;
        case CO_KIND_LIST:
            break;
        case CO_KIND_MUT_LIST:
            break;
        case CO_KIND_DICT:
            break;
        case CO_KIND_MUT_DICT:
            break;
        case CO_KIND_CODE:
            break;
        case CO_KIND_FUNC:
            break;
        case CO_KIND_CLOSURE:
            break;
        case CO_KIND_TUPLE:
            break;
        case CO_KIND_UNION:
            break;
        case CO_KIND_OPTION:
            break;
        case CO_KIND_SOME:
            break;
        case CO_KIND_NONE:
            break;
        case CO_KIND_RESULT:
            break;
        case CO_KIND_OK:
            break;
        case CO_KIND_ERR:
            break;
        case CO_KIND_PTR:
            break;
        default:
            // TODO: return KindError('unknown kind')
            break;
    }

    // TODO: return Ok(None)
    return NULL;
}
