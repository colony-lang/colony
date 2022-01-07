#include "object.h"

/*
 * GC'ed object
 */
size_t co_object_incref(struct co_ctx_t *ctx, struct co_object_t self) {
    size_t rc = -1;
    enum co_type_t t = self.t;
    union co_value_t v = self.v;
    struct co_gc_t *gc = NULL;

    switch (t) {
        case CO_TYPE_BYTES:
            gc = (struct co_gc_t*)(v.bytes);
            rc = ++gc->rc;
            break;
        case CO_TYPE_STR:
            gc = (struct co_gc_t*)(v.str);
            rc = ++gc->rc;
            break;
        case CO_TYPE_TUPLE:
            gc = (struct co_gc_t*)(v.tuple);
            rc = ++gc->rc;
            break;
        case CO_TYPE_STRUCT:
            gc = (struct co_gc_t*)(v.struct_);
            rc = ++gc->rc;
            break;
        case CO_TYPE_UNION:
            gc = (struct co_gc_t*)(v.union_);
            rc = ++gc->rc;
            break;
        case CO_TYPE_LIST:
            gc = (struct co_gc_t*)(v.list);
            rc = ++gc->rc;
            break;
        case CO_TYPE_DICT:
            gc = (struct co_gc_t*)(v.dict);
            rc = ++gc->rc;
            break;
        case CO_TYPE_BLOCK:
            gc = (struct co_gc_t*)(v.block);
            rc = ++gc->rc;
            break;
        case CO_TYPE_CODE:
            gc = (struct co_gc_t*)(v.code);
            rc = ++gc->rc;
            break;
        case CO_TYPE_FN:
            gc = (struct co_gc_t*)(v.fn);
            rc = ++gc->rc;
            break;
        case CO_TYPE_OPTION:
            gc = (struct co_gc_t*)(v.option);
            rc = ++gc->rc;
            break;
        case CO_TYPE_SOME:
            gc = (struct co_gc_t*)(v.some);
            rc = ++gc->rc;
            break;
        case CO_TYPE_NONE:
            gc = (struct co_gc_t*)(v.none);
            rc = ++gc->rc;
            break;
        case CO_TYPE_RESULT:
            gc = (struct co_gc_t*)(v.result);
            rc = ++gc->rc;
            break;
        case CO_TYPE_OK:
            gc = (struct co_gc_t*)(v.ok);
            rc = ++gc->rc;
            break;
        case CO_TYPE_ERR:
            gc = (struct co_gc_t*)(v.err);
            rc = ++gc->rc;
            break;
        case CO_TYPE_STATIC_TYPE:
            gc = (struct co_gc_t*)(v.static_type);
            rc = ++gc->rc;
            break;
        case CO_TYPE_DYNAMIC_TYPE:
            gc = (struct co_gc_t*)(v.dynamic_type);
            rc = ++gc->rc;
            break;
        default:
            break;
    }

    return rc;
}

size_t co_object_decref(struct co_ctx_t *ctx, struct co_object_t self) {
    size_t rc = -1;
    enum co_type_t t = self.t;
    union co_value_t v = self.v;
    struct co_gc_t *gc = NULL;

    switch (t) {
        case CO_TYPE_BYTES:
            gc = (struct co_gc_t*)(v.bytes);
            break;
        case CO_TYPE_STR:
            gc = (struct co_gc_t*)(v.str);
            break;
        case CO_TYPE_TUPLE:
            gc = (struct co_gc_t*)(v.tuple);
            break;
        case CO_TYPE_STRUCT:
            gc = (struct co_gc_t*)(v.struct_);
            break;
        case CO_TYPE_UNION:
            gc = (struct co_gc_t*)(v.union_);
            break;
        case CO_TYPE_LIST:
            gc = (struct co_gc_t*)(v.list);
            break;
        case CO_TYPE_DICT:
            gc = (struct co_gc_t*)(v.dict);
            break;
        case CO_TYPE_CODE:
            gc = (struct co_gc_t*)(v.code);
            break;
        case CO_TYPE_BLOCK:
            gc = (struct co_gc_t*)(v.block);
            break;
        case CO_TYPE_FN:
            gc = (struct co_gc_t*)(v.fn);
            break;
        case CO_TYPE_OPTION:
            gc = (struct co_gc_t*)(v.option);
            break;
        case CO_TYPE_SOME:
            gc = (struct co_gc_t*)(v.some);
            break;
        case CO_TYPE_NONE:
            gc = (struct co_gc_t*)(v.none);
            break;
        case CO_TYPE_RESULT:
            gc = (struct co_gc_t*)(v.result);
            break;
        case CO_TYPE_OK:
            gc = (struct co_gc_t*)(v.ok);
            break;
        case CO_TYPE_ERR:
            gc = (struct co_gc_t*)(v.err);
            break;
        case CO_TYPE_STATIC_TYPE:
            gc = (struct co_gc_t*)(v.static_type);
            break;
        case CO_TYPE_DYNAMIC_TYPE:
            gc = (struct co_gc_t*)(v.dynamic_type);
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

/*
 * object
 */
struct co_object_t co_object_new_from_c_type_c_value(struct co_ctx_t *ctx, enum co_type_t t, union co_value_t v) {
    struct co_object_t self;
    size_t rc = -1;

    self = (struct co_object_t){
        .t = t,
        .v = v,
    };

    rc = co_object_incref(ctx, self);
    assert(rc == -1 || rc > 0);
    return self;
}

struct co_object_t co_object_free(struct co_ctx_t *ctx, struct co_object_t self) {
    // FIXME: implement me
    switch (self.t) {
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
        case CO_TYPE_CODE:
            break;
        case CO_TYPE_BLOCK:
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
        case CO_TYPE_STATIC_TYPE:
            break;
        case CO_TYPE_DYNAMIC_TYPE:
            break;
        default:
            break;
    }

    return self;
}

/*
 * Result
 */

/*
 * Ok
 */

/*
 * Err
 */

/*
 * Option
 */

/*
 * Some
 */

/*
 * None
 */

/*
 * bool
 */

/*
 * u8
 */

/*
 * i8
 */