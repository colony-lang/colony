#include "object.h"

/*
 * object
 */
inline size_t co_object_incref(struct co_ctx_t *ctx, struct co_object_t *self) {
    size_t rc = -1;
    co_gc_t *gc = NULL;

    switch (self->t) {
        case CO_TYPE_BYTES:
            gc = (struct co_gc_t*)(self->v.bytes);
            break;
        case CO_TYPE_STR:
            gc = (struct co_gc_t*)(self->v.str);
            break;
        case CO_TYPE_STRUCT:
            gc = (struct co_gc_t*)(self->v.struct_);
            break;
        case CO_TYPE_UNION:
            gc = (struct co_gc_t*)(self->v.union_);
            break;
        case CO_TYPE_LIST:
            gc = (struct co_gc_t*)(self->v.list);
            break;
        case CO_TYPE_DICT:
            gc = (struct co_gc_t*)(self->v.dict);
            break;
        case CO_TYPE_TUPLE:
            gc = (struct co_gc_t*)(self->v.tuple);
            break;
        case CO_TYPE_BLOCK:
            gc = (struct co_gc_t*)(self->v.block);
            break;
        case CO_TYPE_CODE:
            gc = (struct co_gc_t*)(self->v.code);
            break;
        case CO_TYPE_FN:
            gc = (struct co_gc_t*)(self->v.fn);
            break;
        case CO_TYPE_OPTION:
            gc = (struct co_gc_t*)(self->v.option);
            break;
        case CO_TYPE_SOME:
            gc = (struct co_gc_t*)(self->v.some);
            break;
        case CO_TYPE_NONE:
            gc = (struct co_gc_t*)(self->v.none);
            break;
        case CO_TYPE_RESULT:
            gc = (struct co_gc_t*)(self->v.result);
            break;
        case CO_TYPE_OK:
            gc = (struct co_gc_t*)(self->v.ok);
            break;
        case CO_TYPE_ERR:
            gc = (struct co_gc_t*)(self->v.err);
            break;
        case CO_TYPE_TYPE:
            gc = (struct co_gc_t*)(self->v.type);
            break;
        default:
            gc = NULL;
            break;
    }

    if (gc != NULL) {
        rc = ++gc->rc;
    }

    return rc;
}

inline size_t co_object_decref(struct co_ctx_t *ctx, struct co_object_t *self) {
    size_t rc = -1;
    struct co_gc_t *gc = NULL;

    switch (self->t) {
        case CO_TYPE_BYTES:
            gc = (struct co_gc_t*)(self->v.bytes);
            break;
        case CO_TYPE_STR:
            gc = (struct co_gc_t*)(self->v.str);
            break;
        case CO_TYPE_STRUCT:
            gc = (struct co_gc_t*)(self->v.struct_);
            break;
        case CO_TYPE_UNION:
            gc = (struct co_gc_t*)(self->v.union_);
            break;
        case CO_TYPE_LIST:
            gc = (struct co_gc_t*)(self->v.list);
            break;
        case CO_TYPE_DICT:
            gc = (struct co_gc_t*)(self->v.dict);
            break;
        case CO_TYPE_TUPLE:
            gc = (struct co_gc_t*)(self->v.tuple);
            break;
        case CO_TYPE_BLOCK:
            gc = (struct co_gc_t*)(self->v.block);
            break;
        case CO_TYPE_CODE:
            gc = (struct co_gc_t*)(self->v.code);
            break;
        case CO_TYPE_FN:
            gc = (struct co_gc_t*)(self->v.fn);
            break;
        case CO_TYPE_OPTION:
            gc = (struct co_gc_t*)(self->v.option);
            break;
        case CO_TYPE_SOME:
            gc = (struct co_gc_t*)(self->v.some);
            break;
        case CO_TYPE_NONE:
            gc = (struct co_gc_t*)(self->v.none);
            break;
        case CO_TYPE_RESULT:
            gc = (struct co_gc_t*)(self->v.result);
            break;
        case CO_TYPE_OK:
            gc = (struct co_gc_t*)(self->v.ok);
            break;
        case CO_TYPE_ERR:
            gc = (struct co_gc_t*)(self->v.err);
            break;
        case CO_TYPE_TYPE:
            gc = (struct co_gc_t*)(self->v.type);
            break;
        default:
            gc = NULL;
            break;
    }

    if (gc != NULL) {
        rc = --gc->rc;
        
        if (rc == 0) {
            co_object_free(ctx, self);
        }
    }

    return rc;
}

struct co_object_t *co_object_free(struct co_ctx_t *ctx, struct co_object_t *self) {
    // FIXME: implement me
    switch (self->t) {
        case CO_TYPE_BYTES:
            break;
        case CO_TYPE_STR:
            break;
        case CO_TYPE_STRUCT:
            break;
        case CO_TYPE_UNION:
            break;
        case CO_TYPE_LIST:
            break;
        case CO_TYPE_DICT:
            break;
        case CO_TYPE_TUPLE:
            break;
        case CO_TYPE_BLOCK:
            break;
        case CO_TYPE_CODE:
            break;
        case CO_TYPE_FN:
            break;
        case CO_TYPE_OPTION:
            break;
        case CO_TYPE_SOME:
            break;
        case CO_TYPE_NONE:
            break;
        case CO_TYPE_RESULT:
            break;
        case CO_TYPE_OK:
            break;
        case CO_TYPE_ERR:
            break;
        case CO_TYPE_TYPE:
            break;
        default:
            free(self);
            break;
    }

    return NULL;
}