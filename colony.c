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
        gc_value->rc++;

        #if CO_GC_DEBUG == 1
        printf("incref  \t%s  \t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
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
        gc_value->rc--;
        
        #if CO_GC_DEBUG == 1
        printf("decref  \t%s  \t%d\t%p\t%zu\t%s\n", filename, line, gc_value, gc_value->rc, funcname);
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
            res = co_bool_c_free(ctx, obj);
            break;
        case CO_KIND_I64:
            res = co_i64_c_free(ctx, obj);
            break;
        case CO_KIND_F64:
            res = co_f64_c_free(ctx, obj);
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
            res = co_bytes_c_free(ctx, obj);
            break;
        case CO_KIND_STR:
            res = co_str_c_free(ctx, obj);
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
co_object_t co_bool_c_new(co_object_t ctx, co_bool_t b) {
    co_object_t res;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = b,
        }
    };

    return res;
}

co_object_t co_bool_c_free(co_object_t ctx, co_object_t obj) {
    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_bool_c_hash(co_object_t ctx, co_object_t obj) {
    return co_i64_c_new(ctx, obj.v.b);
}

co_object_t co_bool_c_not(co_object_t ctx, co_object_t obj) {
    return co_bool_c_new(ctx, !(obj.v.b));
}

co_object_t co_bool_c_and(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b && other.v.b);
}

co_object_t co_bool_c_or(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b || other.v.b);
}

co_object_t co_bool_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b < other.v.b);
}

co_object_t co_bool_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b <= other.v.b);
}

co_object_t co_bool_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b == other.v.b);
}

co_object_t co_bool_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b != other.v.b);
}

co_object_t co_bool_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b >= other.v.b);
}

co_object_t co_bool_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.b > other.v.b);
}

co_object_t co_bool_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_bool_c_free(ctx, obj);
}

/*
 * i64
 */
co_object_t co_i64_c_new(co_object_t ctx, co_i64_t i64) {
    co_object_t res;

    res = (co_object_t){
        .k = CO_KIND_I64,
        .v = {
            .i64 = i64,
        }
    };

    return res;
}

co_object_t co_i64_c_free(co_object_t ctx, co_object_t obj) {
    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_i64_c_hash(co_object_t ctx, co_object_t obj) {
    return co_i64_c_new(ctx, obj.v.i64);
}

co_object_t co_i64_c_repr(co_object_t ctx, co_object_t obj) {

}

co_object_t co_i64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 < other.v.i64);
}

co_object_t co_i64_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 <= other.v.i64);
}

co_object_t co_i64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 == other.v.i64);
}

co_object_t co_i64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 != other.v.i64);
}

co_object_t co_i64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 >= other.v.i64);
}

co_object_t co_i64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.i64 > other.v.i64);
}

co_object_t co_i64_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 + other.v.i64);
}

co_object_t co_i64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 - other.v.i64);
}

co_object_t co_i64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 * other.v.i64);
}

// FIXME: Result<int, str>
co_object_t co_i64_c_div(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 / other.v.i64);
}

co_object_t co_i64_c_mod(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 % other.v.i64);
}

co_object_t co_i64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, (co_i64_t)pow(obj.v.i64, other.v.i64));
}

co_object_t co_i64_c_shl(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 << other.v.i64);
}

co_object_t co_i64_c_shr(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 >> other.v.i64);
}

co_object_t co_i64_c_bitinv(co_object_t ctx, co_object_t obj) {
    return co_i64_c_new(ctx, ~obj.v.i64);
}

co_object_t co_i64_c_bitand(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 & other.v.i64);
}

co_object_t co_i64_c_bitor(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 | other.v.i64);
}

co_object_t co_i64_c_bitxor(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_i64_c_new(ctx, obj.v.i64 ^ other.v.i64);
}

co_object_t co_i64_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_i64_c_free(ctx, obj);
}

/*
 * f64
 */
co_object_t co_f64_c_new(co_object_t ctx, co_f64_t f64) {
    co_object_t res;

    res = (co_object_t){
        .k = CO_KIND_F64,
        .v = {
            .f64 = f64,
        }
    };

    return res;
}

co_object_t co_f64_c_free(co_object_t ctx, co_object_t obj) {
    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_f64_c_hash(co_object_t ctx, co_object_t obj) {
    _co_int_float_t num;
    num.f64 = obj.v.f64;
    return co_i64_c_new(ctx, num.i64);
}

co_object_t co_f64_c_repr(co_object_t ctx, co_object_t obj) {

}

co_object_t co_f64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 < other.v.f64);
}

co_object_t co_f64_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 <= other.v.f64);
}

co_object_t co_f64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 == other.v.f64);
}

co_object_t co_f64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 != other.v.f64);
}

co_object_t co_f64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 >= other.v.f64);
}

co_object_t co_f64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_bool_c_new(ctx, obj.v.f64 > other.v.f64);
}

co_object_t co_f64_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_f64_c_new(ctx, obj.v.f64 + other.v.f64);
}

co_object_t co_f64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_f64_c_new(ctx, obj.v.f64 - other.v.f64);
}

co_object_t co_f64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_f64_c_new(ctx, obj.v.f64 * other.v.f64);
}

// FIXME: Result<f64, str>
co_object_t co_f64_c_div(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_f64_c_new(ctx, obj.v.f64 / other.v.f64);
}

co_object_t co_f64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other) {
    return co_f64_c_new(ctx, pow(obj.v.f64, other.v.f64));
}

co_object_t co_f64_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_f64_c_free(ctx, obj);
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

/*
 * bytes
 */
co_object_t co_bytes_c_new(co_object_t ctx, co_i64_t len, char *items) {
    co_object_t obj;
    co_bytes_t *bytes_value;

    bytes_value = calloc(1, sizeof(co_bytes_t));
    bytes_value->rc = 1;
    bytes_value->len = len;
    bytes_value->items = calloc(len, sizeof(char));

    obj = (co_object_t){
        .k = CO_KIND_BYTES,
        .v = {
            .p = (co_gc_t*)bytes_value,
        }
    };

    return obj;
}

co_object_t co_bytes_c_free(co_object_t ctx, co_object_t obj) {
    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    free(bytes_value->items);
    free(bytes_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_bytes_c_len(co_object_t ctx, co_object_t obj) {
    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    return co_i64_c_new(ctx, bytes_value->len);
}

co_object_t co_bytes_c_hash(co_object_t ctx, co_object_t obj) {
    // djb2 hashing algorithm
    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    co_u64_t hash = 5381;
    int c;
    
    for (co_u64_t i=0; i < bytes_value->len; i++) {
        c = bytes_value->items[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    _co_int_float_t num;
    num.u64 = hash;
    return co_i64_c_new(ctx, num.i64);
}

co_object_t co_bytes_c_repr(co_object_t ctx, co_object_t obj) {

}

co_object_t co_bytes_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_bytes_t *obj_bytes_value = (co_bytes_t*)obj.v.p;
    co_bytes_t *other_bytes_value = (co_bytes_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    size_t min_len = MIN(obj_bytes_value->len, other_bytes_value->len);
    int c = memcmp(obj_bytes_value->items, other_bytes_value->items, min_len);
    bool v = c == 0;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = v,
        }
    };

    return res;
}

co_object_t co_bytes_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_bytes_t *obj_bytes_value = (co_bytes_t*)obj.v.p;
    co_bytes_t *other_bytes_value = (co_bytes_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    size_t min_len = MIN(obj_bytes_value->len, other_bytes_value->len);
    int c = memcmp(obj_bytes_value->items, other_bytes_value->items, min_len);
    bool v = c < 0;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = v,
        }
    };

    return res;
}

co_object_t co_bytes_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_bytes_c_free(ctx, obj);
}

/*
 * str
 */
co_object_t co_str_c_new(co_object_t ctx, co_i64_t len, char *items) {
    co_object_t obj;
    co_str_t *str_value;

    str_value = calloc(1, sizeof(co_str_t));
    str_value->rc = 1;
    str_value->len = len;
    str_value->items = calloc(len, sizeof(char));

    obj = (co_object_t){
        .k = CO_KIND_STR,
        .v = {
            .p = (co_gc_t*)str_value,
        }
    };

    return obj;
}

co_object_t co_str_c_free(co_object_t ctx, co_object_t obj) {
    co_str_t *str_value = (co_str_t*)obj.v.p;
    free(str_value->items);
    free(str_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_str_c_len(co_object_t ctx, co_object_t obj) {
    co_str_t *str_value = (co_str_t*)obj.v.p;
    return co_i64_c_new(ctx, str_value->len);
}

co_object_t co_str_c_hash(co_object_t ctx, co_object_t obj) {
    // djb2 hashing algorithm
    co_str_t *str_value = (co_str_t*)obj.v.p;
    co_u64_t hash = 5381;
    int c;
    
    for (co_u64_t i=0; i < str_value->len; i++) {
        c = str_value->items[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    _co_int_float_t num;
    num.u64 = hash;
    return co_i64_c_new(ctx, num.i64);
}

co_object_t co_str_c_repr(co_object_t ctx, co_object_t obj) {

}

co_object_t co_str_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_str_t *obj_str_value = (co_str_t*)obj.v.p;
    co_str_t *other_str_value = (co_str_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_STR);
    assert(other.k == CO_KIND_STR);

    size_t min_len = MIN(obj_str_value->len, other_str_value->len);
    int c = memcmp(obj_str_value->items, other_str_value->items, min_len);
    bool v = c == 0;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = v,
        }
    };

    return res;
}

co_object_t co_str_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_str_t *obj_str_value = (co_str_t*)obj.v.p;
    co_str_t *other_str_value = (co_str_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_STR);
    assert(other.k == CO_KIND_STR);

    size_t min_len = MIN(obj_str_value->len, other_str_value->len);
    int c = memcmp(obj_str_value->items, other_str_value->items, min_len);
    bool v = c < 0;

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = v,
        }
    };

    return res;
}

co_object_t co_str_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_str_c_free(ctx, obj);
}
