#include "colony.h"

/*
 * object
 */
inline void co_object_c_incref(co_object_t ctx, co_object_t obj) {
    co_gc_t *gc_value;

    if (obj.k >= CO_KIND_GC) {
        gc_value = (co_gc_t*)obj.v.p;

        #ifdef CO_GC_DEBUG
        #if CO_GC_DEBUG == 1
        printf("incref [0] %p %zu\n", gc_value, gc_value->rc);
        #endif
        #endif

        gc_value->rc++;

        #ifdef CO_GC_DEBUG
        #if CO_GC_DEBUG == 1
        printf("incref [1] %p %zu\n", gc_value, gc_value->rc);
        #endif
        #endif
    }
}

inline void co_object_c_decref(co_object_t ctx, co_object_t obj) {
    co_gc_t *gc_value;

    if (obj.k >= CO_KIND_GC) {
        gc_value = (co_gc_t*)obj.v.p;

        #ifdef CO_GC_DEBUG
        #if CO_GC_DEBUG == 1
        printf("decref [0] %p %zu\n", gc_value, gc_value->rc);
        #endif
        #endif

        gc_value->rc--;
        
        #ifdef CO_GC_DEBUG
        #if CO_GC_DEBUG == 1
        printf("decref [1] %p %zu\n", gc_value, gc_value->rc);
        #endif
        #endif

        if (gc_value->rc == 0) {
            co_object_free(ctx, obj, CO_OBJECT_UNDEFINED, CO_OBJECT_UNDEFINED);
        }
    }
}

co_object_t co_object_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            break;
        case CO_KIND_BOOL:
            break;
        case CO_KIND_INT:
            break;
        case CO_KIND_FLOAT:
            break;
        case CO_KIND_GC:
            break;
        case CO_KIND_CTX:
            res = co_ctx_free(ctx, obj, CO_OBJECT_UNDEFINED, CO_OBJECT_UNDEFINED);
            break;
        case CO_KIND_FRAME:
            res = co_frame_free(ctx, obj, CO_OBJECT_UNDEFINED, CO_OBJECT_UNDEFINED);
            break;
        case CO_KIND_MODULE:
            break;
        case CO_KIND_BYTES:
            break;
        case CO_KIND_STR:
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

/*
 * ctx
 */
co_object_t co_ctx_c_new_root(void) {
    co_object_t ctx;
    co_ctx_t *ctx_value;
    co_object_t current_frame;

    // ctx_value = calloc(1, sizeof(co_ctx_t));
    ctx_value = malloc(sizeof(co_ctx_t));
    ctx_value->rc = 1;

    ctx = (co_object_t){
        .k = CO_KIND_CTX,
        .v = {
            .p = (co_gc_t*)ctx_value,
        }
    };
    
    ctx_value->parent_ctx = CO_OBJECT_UNDEFINED;      // already zeroed
    co_object_c_incref(ctx, ctx_value->parent_ctx);
    
    current_frame = co_frame_c_new(ctx, CO_OBJECT_UNDEFINED);
    ctx_value->current_frame = current_frame;

    // NOTE: memory leak
    // co_object_c_incref(ctx, ctx_value->current_frame);

    return ctx;
}

co_object_t co_ctx_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    co_ctx_t *ctx_value = (co_ctx_t*)obj.v.p;
    co_object_c_decref(ctx, ctx_value->parent_ctx);
    co_object_c_decref(ctx, ctx_value->current_frame);
    free(ctx_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_ctx_spawn(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    // co_object_t self;
    return CO_OBJECT_UNDEFINED;
}

/*
 * frame
 */
co_object_t co_frame_c_new(co_object_t ctx, co_object_t parent_frame) {
    co_object_t frame;
    co_frame_t *frame_value;
    co_object_t closure;

    // frame_value = calloc(1, sizeof(co_frame_t));
    frame_value = malloc(sizeof(co_frame_t));
    frame_value->rc = 1;
    
    frame = (co_object_t){
        .k = CO_KIND_FRAME,
        .v = {
            .p = (co_gc_t*)frame_value,
        }
    };

    frame_value->parent_frame = parent_frame;
    co_object_c_incref(ctx, parent_frame);
    
    closure = CO_OBJECT_UNDEFINED; // FIXME:
    frame_value->closure = closure;
    co_object_c_incref(ctx, closure);

    return frame;
}

co_object_t co_frame_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    co_frame_t *frame_value = (co_frame_t*)obj.v.p;
    co_object_c_decref(ctx, frame_value->parent_frame);
    co_object_c_decref(ctx, frame_value->closure);
    free(frame_value);
    return CO_OBJECT_UNDEFINED;
}
