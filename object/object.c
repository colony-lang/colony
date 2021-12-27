#include "object.h"

/*
 * object
 */
size_t co_object_incref(struct co_ctx_t *ctx, struct co_object_t *self) {
    switch (self->t) {
        case CO_TYPE_BYTES:
        case CO_TYPE_STR:
        case CO_TYPE_STRUCT:
        case CO_TYPE_UNION:
        case CO_TYPE_LIST:
        case CO_TYPE_DICT:
        case CO_TYPE_TUPLE:
        case CO_TYPE_CODE:
        case CO_TYPE_FN:
        case CO_TYPE_OPTION:
        case CO_TYPE_SOME:
        case CO_TYPE_NONE:
        case CO_TYPE_RESULT:
        case CO_TYPE_OK:
        case CO_TYPE_ERR:
        case CO_TYPE_TYPE:
            struct co_gc_t *gc = (struct co_gc_t*)(self);
            gc->rc++;
            break;
        default:
            break;
    }

    return gc->rc;
}

size_t co_object_decref(struct co_ctx_t *ctx, struct co_object_t *self) {
    switch (self->t) {
        case CO_TYPE_BYTES:
        case CO_TYPE_STR:
        case CO_TYPE_STRUCT:
        case CO_TYPE_UNION:
        case CO_TYPE_LIST:
        case CO_TYPE_DICT:
        case CO_TYPE_TUPLE:
        case CO_TYPE_CODE:
        case CO_TYPE_FN:
        case CO_TYPE_OPTION:
        case CO_TYPE_SOME:
        case CO_TYPE_NONE:
        case CO_TYPE_RESULT:
        case CO_TYPE_OK:
        case CO_TYPE_ERR:
        case CO_TYPE_TYPE:
            struct co_gc_t *gc = (struct co_gc_t*)(self);
            gc->rc--;

            // FIXME: free

            break;
        default:
            break;
    }

    return gc->rc;
}
