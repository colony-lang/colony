#include "colony.h"

/*
 * object
 */
#if CO_GC_DEBUG == 1
    inline void co_object_c_incref(co_object_t ctx, co_object_t obj, char *filename, int line, const char *funcname)
#else
    inline void co_object_c_incref(co_object_t ctx, co_object_t obj)
#endif
{
    co_gc_t *gc_value;

    if (obj.k >= CO_KIND_GC) {
        gc_value = (co_gc_t*)obj.v.p;

        // #if CO_GC_DEBUG == 1
        // printf("incref [0] %s\t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
        // #endif

        gc_value->rc++;

        #if CO_GC_DEBUG == 1
        printf("incref [1] %s\t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
        #endif
    }
}

#if CO_GC_DEBUG == 1
    inline void co_object_c_decref(co_object_t ctx, co_object_t obj, char *filename, int line, const char *funcname)
#else
    inline void co_object_c_decref(co_object_t ctx, co_object_t obj)
#endif
{
    co_gc_t *gc_value;

    if (obj.k >= CO_KIND_GC) {
        gc_value = (co_gc_t*)obj.v.p;

        // #if CO_GC_DEBUG == 1
        // printf("decref [0] %s\t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
        // #endif
        
        gc_value->rc--;
        
        #if CO_GC_DEBUG == 1
        printf("decref [1] %s\t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
        #endif
        
        if (gc_value->rc == 0) {
            co_object_free(ctx, obj, CO_OBJECT_UNDEFINED, CO_OBJECT_UNDEFINED);
        }
    }
}

co_object_t co_object_c_free(co_object_t ctx, co_object_t obj) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            break;
        case CO_KIND_BOOL:
            break;
        case CO_KIND_I64:
            break;
        case CO_KIND_F64:
            break;
        case CO_KIND_GC:
            break;
        case CO_KIND_CTX:
            res = co_ctx_c_free(ctx, obj);
            break;
        case CO_KIND_FRAME:
            res = co_frame_c_free(ctx, obj);
            break;
        case CO_KIND_MODULE:
            break;
        case CO_KIND_BYTES:
            // res = co_bytes_c_free(ctx, obj);
            break;
        case CO_KIND_STR:
            // res = co_str_c_free(ctx, obj);
            break;
        case CO_KIND_LIST:
            break;
        case CO_KIND_DICT:
            break;
        case CO_KIND_BLOCK:
            break;
        case CO_KIND_CODE:
            break;
        case CO_KIND_FN:
            break;
        case CO_KIND_STRUCT:
            break;
        case CO_KIND_UNION:
            break;
        case CO_KIND_GENERIC:
            break;
        case CO_KIND_GENERIC_STRUCT:
            break;
        case CO_KIND_GENERIC_UNION:
            break;
        case CO_KIND_GENERIC_TYPE:
            break;
        case CO_KIND_GENERIC_FN:
            break;
        case CO_KIND_NONE:
            break;
        case CO_KIND_SOME:
            break;
        case CO_KIND_OPTION:
            break;
        case CO_KIND_OK:
            break;
        case CO_KIND_ERR:
            break;
        case CO_KIND_RESULT:
            break;
        default:
            exit(1);
            break;
    }

    return res;
}

co_object_t co_object_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_object_c_free(ctx, obj);
}

/*
 * bool
 */
inline co_object_t co_bool_c_new(co_object_t ctx, bool b) {
    co_object_t res;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = b,
        }
    };

    return res;
}

inline co_object_t co_bool_c_free(co_object_t ctx, co_object_t obj) {
    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

inline co_object_t co_bool_c_not(co_object_t ctx, co_object_t obj) {
    return co_bool_c_new(ctx, !(obj.v.b));
}

inline co_object_t co_bool_c_and(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b && other.v.b);
}

inline co_object_t co_bool_c_or(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b || other.v.b);
}

co_object_t co_bool_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_bool_c_free(ctx, obj);
}

/*
 * ctx
 */
co_object_t co_ctx_c_new_root(void) {
    co_object_t ctx;
    co_ctx_t *ctx_value;
    co_object_t current_frame;

    ctx_value = calloc(1, sizeof(co_ctx_t));
    ctx_value->rc = 1;

    ctx = (co_object_t){
        .k = CO_KIND_CTX,
        .v = {
            .p = (co_gc_t*)ctx_value,
        }
    };
    
    // parent_ctx
    ctx_value->parent_ctx = CO_OBJECT_UNDEFINED;      // already zeroed
    CO_OBJECT_C_INCREF(ctx, ctx_value->parent_ctx);
    
    // current_frame
    current_frame = co_frame_c_new(ctx, CO_OBJECT_UNDEFINED);
    ctx_value->current_frame = current_frame;

    return ctx;
}

co_object_t co_ctx_c_free(co_object_t ctx, co_object_t obj) {
    co_ctx_t *ctx_value = (co_ctx_t*)obj.v.p;
    CO_OBJECT_C_DECREF(ctx, ctx_value->parent_ctx);
    CO_OBJECT_C_DECREF(ctx, ctx_value->current_frame);
    free(ctx_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_ctx_c_spawn(co_object_t ctx) {
    co_object_t child_ctx;
    co_ctx_t *child_ctx_value;
    co_ctx_t *ctx_value;
    co_object_t current_frame;
    co_object_t parent_frame;

    child_ctx_value = calloc(1, sizeof(co_ctx_t));
    child_ctx_value->rc = 1;

    child_ctx = (co_object_t){
        .k = CO_KIND_CTX,
        .v = {
            .p = (co_gc_t*)child_ctx_value,
        }
    };
    
    // ctx
    child_ctx_value->parent_ctx = ctx;
    CO_OBJECT_C_INCREF(child_ctx, child_ctx_value->parent_ctx);
    
    // current_frame
    ctx_value = (co_ctx_t*)ctx.v.p;
    parent_frame = ctx_value->current_frame;
    current_frame = co_frame_c_new(child_ctx, parent_frame);
    child_ctx_value->current_frame = current_frame;

    return child_ctx;
}

co_object_t co_ctx_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_ctx_c_free(ctx, obj);
}

co_object_t co_ctx_spawn(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_ctx_c_spawn(ctx);
}

/*
 * frame
 */
co_object_t co_frame_c_new(co_object_t ctx, co_object_t parent_frame) {
    co_object_t frame;
    co_frame_t *frame_value;
    co_object_t closure;

    frame_value = calloc(1, sizeof(co_frame_t));
    frame_value->rc = 1;
    
    frame = (co_object_t){
        .k = CO_KIND_FRAME,
        .v = {
            .p = (co_gc_t*)frame_value,
        }
    };

    // parent_frame
    frame_value->parent_frame = parent_frame;
    CO_OBJECT_C_INCREF(ctx, parent_frame);
    
    // closure
    closure = CO_OBJECT_UNDEFINED; // FIXME:
    frame_value->closure = closure;
    CO_OBJECT_C_INCREF(ctx, closure);

    return frame;
}

co_object_t co_frame_c_free(co_object_t ctx, co_object_t obj) {
    co_frame_t *frame_value = (co_frame_t*)obj.v.p;
    CO_OBJECT_C_DECREF(ctx, frame_value->parent_frame);
    CO_OBJECT_C_DECREF(ctx, frame_value->closure);
    free(frame_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_frame_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_frame_c_free(ctx, obj);
}
