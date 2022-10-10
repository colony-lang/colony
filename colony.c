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
            exit(1);
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
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CTX:
            res = co_ctx_c_free(ctx, obj);
            break;
        case CO_KIND_FRAME:
            res = co_frame_c_free(ctx, obj);
            break;
        case CO_KIND_MODULE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BYTES:
            res = co_bytes_c_free(ctx, obj);
            break;
        case CO_KIND_STR:
            res = co_str_c_free(ctx, obj);
            break;
        case CO_KIND_LIST:
            res = co_list_c_free(ctx, obj);
            break;
        case CO_KIND_DICT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BLOCK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CODE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_TYPE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_NONE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_SOME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OPTION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_ERR:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_RESULT:
            // FIXME: implement
            exit(1);
            break;
        default:
            // FIXME: implement
            exit(1);
            break;
    }

    return res;
}

co_object_t co_object_c_repr(co_object_t ctx, co_object_t obj) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_BOOL:
            res = co_bool_c_repr(ctx, obj);
            break;
        case CO_KIND_I64:
            res = co_i64_c_repr(ctx, obj);
            break;
        case CO_KIND_F64:
            res = co_f64_c_repr(ctx, obj);
            break;
        case CO_KIND_GC:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_CTX:
            res = co_ctx_c_repr(ctx, obj);
            break;
        case CO_KIND_FRAME:
            res = co_frame_c_repr(ctx, obj);
            break;
        case CO_KIND_MODULE:
            break;
        case CO_KIND_BYTES:
            res = co_bytes_c_repr(ctx, obj);
            break;
        case CO_KIND_STR:
            res = co_str_c_repr(ctx, obj);
            break;
        case CO_KIND_LIST:
            res = co_list_c_repr(ctx, obj);
            break;
        case CO_KIND_DICT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BLOCK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CODE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_TYPE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_NONE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_SOME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OPTION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_ERR:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_RESULT:
            // FIXME: implement
            exit(1);
            break;
        default:
            // FIXME: implement
            exit(1);
            break;
    }

    return res;
}

co_object_t co_object_c_hash(co_object_t ctx, co_object_t obj) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_BOOL:
            res = co_bool_c_hash(ctx, obj);
            break;
        case CO_KIND_I64:
            res = co_i64_c_hash(ctx, obj);
            break;
        case CO_KIND_F64:
            res = co_f64_c_hash(ctx, obj);
            break;
        case CO_KIND_GC:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_CTX:
            res = co_ctx_c_hash(ctx, obj);
            break;
        case CO_KIND_FRAME:
            res = co_frame_c_hash(ctx, obj);
            break;
        case CO_KIND_MODULE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BYTES:
            res = co_bytes_c_hash(ctx, obj);
            break;
        case CO_KIND_STR:
            res = co_str_c_hash(ctx, obj);
            break;
        case CO_KIND_LIST:
            res = co_list_c_hash(ctx, obj);
            break;
        case CO_KIND_DICT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BLOCK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CODE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_TYPE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_NONE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_SOME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OPTION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_ERR:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_RESULT:
            // FIXME: implement
            exit(1);
            break;
        default:
            // FIXME: implement
            exit(1);
            break;
    }

    return res;
}

co_object_t co_object_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_BOOL:
            res = co_bool_c_lt(ctx, obj, other);
            break;
        case CO_KIND_I64:
            res = co_i64_c_lt(ctx, obj, other);
            break;
        case CO_KIND_F64:
            res = co_f64_c_lt(ctx, obj, other);
            break;
        case CO_KIND_GC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CTX:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FRAME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_MODULE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BYTES:
            res = co_bytes_c_lt(ctx, obj, other);
            break;
        case CO_KIND_STR:
            res = co_str_c_lt(ctx, obj, other);
            break;
        case CO_KIND_LIST:
            res = co_list_c_lt(ctx, obj, other);
            break;
        case CO_KIND_DICT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BLOCK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CODE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_TYPE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_NONE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_SOME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OPTION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_ERR:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_RESULT:
            // FIXME: implement
            exit(1);
            break;
        default:
            // FIXME: implement
            exit(1);
            break;
    }

    return res;
}

co_object_t co_object_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    co_object_t res = CO_OBJECT_UNDEFINED;

    switch (obj.k) {
        case CO_KIND_UNDEFINED:
            // FIXME: implement
            assert(obj.k != CO_KIND_UNDEFINED);
            exit(1);
            break;
        case CO_KIND_BOOL:
            res = co_bool_c_eq(ctx, obj, other);
            break;
        case CO_KIND_I64:
            res = co_i64_c_eq(ctx, obj, other);
            break;
        case CO_KIND_F64:
            res = co_f64_c_eq(ctx, obj, other);
            break;
        case CO_KIND_GC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CTX:
            res = co_ctx_c_eq(ctx, obj, other);
            break;
        case CO_KIND_FRAME:
            res = co_frame_c_eq(ctx, obj, other);
            break;
        case CO_KIND_MODULE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BYTES:
            res = co_bytes_c_eq(ctx, obj, other);
            break;
        case CO_KIND_STR:
            res = co_str_c_eq(ctx, obj, other);
            break;
        case CO_KIND_LIST:
            res = co_list_c_eq(ctx, obj, other);
            break;
        case CO_KIND_DICT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_BLOCK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_CODE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_STRUCT:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_UNION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_TYPE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_GENERIC_FN:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_NONE:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_SOME:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OPTION:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_OK:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_ERR:
            // FIXME: implement
            exit(1);
            break;
        case CO_KIND_RESULT:
            // FIXME: implement
            exit(1);
            break;
        default:
            // FIXME: implement
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
    assert(obj.k == CO_KIND_BOOL);

    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_bool_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BOOL);
    co_object_t res;

    if (obj.v.b == true) {
        res = co_str_c_new(ctx, 4, "true", CO_OWN_TRANS_COPY);
    } else {
        res = co_str_c_new(ctx, 5, "false", CO_OWN_TRANS_COPY);
    }

    return res;
}

co_object_t co_bool_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BOOL);
    return co_i64_c_new(ctx, obj.v.b);
}

co_object_t co_bool_c_not(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, !(obj.v.b));
}

co_object_t co_bool_c_and(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b && other.v.b);
}

co_object_t co_bool_c_or(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b || other.v.b);
}

co_object_t co_bool_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b < other.v.b);
}

co_object_t co_bool_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b <= other.v.b);
}

co_object_t co_bool_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b == other.v.b);
}

co_object_t co_bool_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b != other.v.b);
}

co_object_t co_bool_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
    return co_bool_c_new(ctx, obj.v.b >= other.v.b);
}

co_object_t co_bool_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BOOL);
    assert(other.k == CO_KIND_BOOL);
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
    assert(obj.k == CO_KIND_I64);

    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_i64_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64);
}

co_object_t co_i64_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_I64);

    co_i64_t v = obj.v.i64;
    int size = snprintf(NULL, 0, "%lld", v);
    char *items = calloc(size, sizeof(char));
    snprintf(items, size + 1, "%lld", v);
    
    co_object_t res = co_str_c_new(ctx, size, items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_i64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 < other.v.i64);
}

co_object_t co_i64_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 <= other.v.i64);
}

co_object_t co_i64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 == other.v.i64);
}

co_object_t co_i64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 != other.v.i64);
}

co_object_t co_i64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 >= other.v.i64);
}

co_object_t co_i64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_bool_c_new(ctx, obj.v.i64 > other.v.i64);
}

co_object_t co_i64_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 + other.v.i64);
}

co_object_t co_i64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 - other.v.i64);
}

co_object_t co_i64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 * other.v.i64);
}

// FIXME: Result<int, str>
co_object_t co_i64_c_div(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    // FIXME:
    return co_i64_c_new(ctx, obj.v.i64 / other.v.i64);
}

co_object_t co_i64_c_mod(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 % other.v.i64);
}

co_object_t co_i64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, (co_i64_t)pow(obj.v.i64, other.v.i64));
}

co_object_t co_i64_c_shl(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 << other.v.i64);
}

co_object_t co_i64_c_shr(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 >> other.v.i64);
}

co_object_t co_i64_c_bitinv(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_I64);
    return co_i64_c_new(ctx, ~obj.v.i64);
}

co_object_t co_i64_c_bitand(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 & other.v.i64);
}

co_object_t co_i64_c_bitor(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
    return co_i64_c_new(ctx, obj.v.i64 | other.v.i64);
}

co_object_t co_i64_c_bitxor(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_I64);
    assert(other.k == CO_KIND_I64);
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
    assert(obj.k == CO_KIND_F64);

    // NOTE: nothing to free
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_f64_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_F64);

    _co_num_t num;
    num.f64 = obj.v.f64;
    return co_i64_c_new(ctx, num.i64);
}

co_object_t co_f64_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_F64);

    co_f64_t v = obj.v.f64;
    int size = snprintf(NULL, 0, "%f", v);
    
    char *items = calloc(size + 1, sizeof(char));
    snprintf(items, size + 1, "%f", v);
    
    co_object_t res = co_str_c_new(ctx, size, items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_f64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 < other.v.f64);
}

co_object_t co_f64_c_le(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 <= other.v.f64);
}

co_object_t co_f64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 == other.v.f64);
}

co_object_t co_f64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 != other.v.f64);
}

co_object_t co_f64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 >= other.v.f64);
}

co_object_t co_f64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_bool_c_new(ctx, obj.v.f64 > other.v.f64);
}

co_object_t co_f64_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_f64_c_new(ctx, obj.v.f64 + other.v.f64);
}

co_object_t co_f64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_f64_c_new(ctx, obj.v.f64 - other.v.f64);
}

co_object_t co_f64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    return co_f64_c_new(ctx, obj.v.f64 * other.v.f64);
}

// FIXME: Result<f64, str>
co_object_t co_f64_c_div(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
    // FIXME:
    return co_f64_c_new(ctx, obj.v.f64 / other.v.f64);
}

co_object_t co_f64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_F64);
    assert(other.k == CO_KIND_F64);
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
    CO_INCREF(ctx, ctx_value->parent_ctx);
    
    // current_frame
    current_frame = co_frame_c_new(ctx, CO_OBJECT_UNDEFINED);
    ctx_value->current_frame = current_frame;

    return ctx;
}

co_object_t co_ctx_c_free(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_CTX);

    co_ctx_t *ctx_value = (co_ctx_t*)obj.v.p;
    CO_DECREF(ctx, ctx_value->parent_ctx);
    CO_DECREF(ctx, ctx_value->current_frame);
    free(ctx_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_ctx_c_spawn(co_object_t ctx) {
    assert(ctx.k == CO_KIND_CTX);

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
    CO_INCREF(child_ctx, child_ctx_value->parent_ctx);
    
    // current_frame
    ctx_value = (co_ctx_t*)ctx.v.p;
    parent_frame = ctx_value->current_frame;
    current_frame = co_frame_c_new(child_ctx, parent_frame);
    child_ctx_value->current_frame = current_frame;

    return child_ctx;
}

co_object_t co_ctx_c_hash(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_CTX);

    _co_num_t num = { .p = obj.v.p };
    co_i64_t hash_value = num.i64;
    co_object_t hash = co_i64_c_new(ctx, hash_value);
    return hash;
}

co_object_t co_ctx_c_repr(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_CTX);

    co_object_t res;
    co_ctx_t *ctx_value = (co_ctx_t*)obj.v.p;
    
    int size = snprintf(NULL, 0, "(ctx at %p)", ctx_value);
    
    char *repr_items = calloc(size, sizeof(char));
    snprintf(repr_items, size + 1, "(ctx at %p)", ctx_value);

    res = co_str_c_new(ctx, size, repr_items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_ctx_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_CTX);
    assert(other.k == CO_KIND_CTX);

    bool res_value = (obj.v.p == other.v.p);
    co_object_t res = co_bool_c_new(ctx, res_value);
    return res;
}

co_object_t co_ctx_c_get_current_frame(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_CTX);

    co_ctx_t *ctx_value = (co_ctx_t*)obj.v.p;
    co_object_t current_frame = ctx_value->current_frame;
    return current_frame;
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
    assert(ctx.k == CO_KIND_CTX);
    assert(parent_frame.k == CO_KIND_FRAME || parent_frame.k == CO_KIND_UNDEFINED);

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
    CO_INCREF(ctx, parent_frame);
    
    // closure
    closure = CO_OBJECT_UNDEFINED; // FIXME:
    frame_value->closure = closure;
    CO_INCREF(ctx, closure);

    return frame;
}

co_object_t co_frame_c_free(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_FRAME);

    co_frame_t *frame_value = (co_frame_t*)obj.v.p;
    CO_DECREF(ctx, frame_value->parent_frame);
    CO_DECREF(ctx, frame_value->closure);
    free(frame_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_frame_c_hash(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_FRAME);

    _co_num_t num = { .p = obj.v.p };
    co_i64_t hash_value = num.i64;
    co_object_t hash = co_i64_c_new(ctx, hash_value);
    return hash;
}

co_object_t co_frame_c_repr(co_object_t ctx, co_object_t obj) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_FRAME);

    co_object_t res;
    co_frame_t *frame_value = (co_frame_t*)obj.v.p;
    
    int size = snprintf(NULL, 0, "(frame at %p)", frame_value);
    
    char *repr_items = calloc(size, sizeof(char));
    snprintf(repr_items, size + 1, "(frame at %p)", frame_value);

    res = co_str_c_new(ctx, size, repr_items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_frame_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(ctx.k == CO_KIND_CTX);
    assert(obj.k == CO_KIND_FRAME);
    assert(other.k == CO_KIND_FRAME);

    bool res_value = (obj.v.p == other.v.p);
    co_object_t res = co_bool_c_new(ctx, res_value);
    return res;
}

co_object_t co_frame_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_frame_c_free(ctx, obj);
}

/*
 * bytes
 */
co_object_t co_bytes_c_new(co_object_t ctx, co_u64_t len, char *items, co_own_trans_t ot) {
    co_object_t obj;
    co_bytes_t *bytes_value;

    bytes_value = calloc(1, sizeof(co_bytes_t));
    bytes_value->rc = 1;
    bytes_value->len = len;
    bytes_value->ot = ot;

    switch (ot) {
        case CO_OWN_TRANS_NONE:
        case CO_OWN_TRANS_MOVE:
            bytes_value->items = items;
            break;
        case CO_OWN_TRANS_COPY:
            bytes_value->items = calloc(len, sizeof(char));
            bytes_value->items = memmove(bytes_value->items, items, len);
            break;
    }

    // precompute hash
    bytes_value->hash = co_c_cstr_hash(ctx, bytes_value->len, bytes_value->items);

    obj = (co_object_t){
        .k = CO_KIND_BYTES,
        .v = {
            .p = (co_gc_t*)bytes_value,
        }
    };

    return obj;
}

co_object_t co_bytes_c_free(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BYTES);

    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    co_own_trans_t ot = bytes_value->ot;
    
    switch (ot) {
        case CO_OWN_TRANS_NONE:
            break;
        case CO_OWN_TRANS_COPY:
        case CO_OWN_TRANS_MOVE:
            free(bytes_value->items);
            break;
    }

    free(bytes_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_bytes_c_len(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BYTES);
    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    return co_i64_c_new(ctx, bytes_value->len);
}

co_object_t co_bytes_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BYTES);
    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    return co_i64_c_new(ctx, bytes_value->hash);
}

co_object_t co_bytes_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_BYTES);
    co_object_t res;

    co_bytes_t *bytes_value = (co_bytes_t*)obj.v.p;
    char *repr_items = calloc(bytes_value->len, sizeof(char));
    char c;

    for (co_u64_t i = 0; i < bytes_value->len; i++) {
        c = bytes_value->items[i];

        if (isprint(c)) {
           repr_items[i] = c;
        } else {
            repr_items[i] = '?';
        }
    }

    res = co_str_c_new(ctx, bytes_value->len, repr_items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_bytes_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    co_bytes_t *obj_bytes_value = (co_bytes_t*)obj.v.p;
    co_bytes_t *other_bytes_value = (co_bytes_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    size_t min_len = MIN(obj_bytes_value->len, other_bytes_value->len);
    int c = memcmp(obj_bytes_value->items, other_bytes_value->items, min_len);
    bool v = c == 0;

    res = co_bool_c_new(ctx, v);
    return res;
}

co_object_t co_bytes_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    co_bytes_t *obj_bytes_value = (co_bytes_t*)obj.v.p;
    co_bytes_t *other_bytes_value = (co_bytes_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    size_t min_len = MIN(obj_bytes_value->len, other_bytes_value->len);
    int c = memcmp(obj_bytes_value->items, other_bytes_value->items, min_len);
    bool v = c < 0;

    res = co_bool_c_new(ctx, v);
    return res;
}

co_object_t co_bytes_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    co_bytes_t *obj_bytes_value = (co_bytes_t*)obj.v.p;
    co_bytes_t *other_bytes_value = (co_bytes_t*)other.v.p;
    co_object_t res;

    assert(obj.k == CO_KIND_BYTES);
    assert(other.k == CO_KIND_BYTES);

    size_t len = obj_bytes_value->len + other_bytes_value->len;
    char *items = calloc(len, sizeof(char));
    memmove(items, obj_bytes_value->items, obj_bytes_value->len);
    memmove(items + obj_bytes_value->len, other_bytes_value->items, other_bytes_value->len);
    
    res = co_bytes_c_new(ctx, len, items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_bytes_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_bytes_c_free(ctx, obj);
}

/*
 * str
 */
co_object_t co_str_c_new(co_object_t ctx, co_u64_t len, char *items, co_own_trans_t ot) {
    co_object_t obj;
    co_str_t *str_value;

    str_value = calloc(1, sizeof(co_str_t));
    str_value->rc = 1;
    str_value->len = len;
    str_value->ot = ot;

    switch (ot) {
        case CO_OWN_TRANS_NONE:
        case CO_OWN_TRANS_MOVE:
            str_value->items = items;
            break;
        case CO_OWN_TRANS_COPY:
            str_value->items = calloc(len, sizeof(char));
            str_value->items = memmove(str_value->items, items, len);
            break;
    }

    // precompute hash
    str_value->hash = co_c_cstr_hash(ctx, str_value->len, str_value->items);

    // object
    obj = (co_object_t){
        .k = CO_KIND_STR,
        .v = {
            .p = (co_gc_t*)str_value,
        }
    };

    return obj;
}

co_object_t co_str_c_free(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_STR);

    co_str_t *str_value = (co_str_t*)obj.v.p;
    co_own_trans_t ot = str_value->ot;

    switch (ot) {
        case CO_OWN_TRANS_NONE:
            break;
        case CO_OWN_TRANS_COPY:
        case CO_OWN_TRANS_MOVE:
            free(str_value->items);
            break;
    }

    free(str_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_str_c_len(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_STR);
    co_str_t *str_value = (co_str_t*)obj.v.p;
    return co_i64_c_new(ctx, str_value->len);
}

co_object_t co_str_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_STR);
    co_str_t *str_value = (co_str_t*)obj.v.p;
    return co_i64_c_new(ctx, str_value->hash);
}

co_object_t co_str_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_STR);

    co_object_t res;
    co_str_t *str_value = (co_str_t*)obj.v.p;
    char *repr_items = calloc(str_value->len, sizeof(char));
    char c;

    for (co_u64_t i = 0; i < str_value->len; i++) {
        c = str_value->items[i];

        if (isprint(c)) {
           repr_items[i] = c;
        } else {
            repr_items[i] = '?';
        }
    }

    res = co_str_c_new(ctx, str_value->len, repr_items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_str_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_STR);
    assert(other.k == CO_KIND_STR);

    co_str_t *obj_str_value = (co_str_t*)obj.v.p;
    co_str_t *other_str_value = (co_str_t*)other.v.p;
    co_object_t res;

    size_t min_len = MIN(obj_str_value->len, other_str_value->len);
    int c = memcmp(obj_str_value->items, other_str_value->items, min_len);
    bool v = c == 0;

    res = co_bool_c_new(ctx, v);
    return res;
}

co_object_t co_str_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_STR);
    assert(other.k == CO_KIND_STR);

    co_str_t *obj_str_value = (co_str_t*)obj.v.p;
    co_str_t *other_str_value = (co_str_t*)other.v.p;
    co_object_t res;

    size_t min_len = MIN(obj_str_value->len, other_str_value->len);
    int c = memcmp(obj_str_value->items, other_str_value->items, min_len);
    bool v = c < 0;

    res = co_bool_c_new(ctx, v);
    return res;
}

co_object_t co_str_c_add(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_STR);
    assert(other.k == CO_KIND_STR);

    co_str_t *obj_str_value = (co_str_t*)obj.v.p;
    co_str_t *other_str_value = (co_str_t*)other.v.p;
    co_object_t res;

    size_t len = obj_str_value->len + other_str_value->len;
    char *items = calloc(len, sizeof(char));
    memmove(items, obj_str_value->items, obj_str_value->len);
    memmove(items + obj_str_value->len, other_str_value->items, other_str_value->len);
    
    res = co_str_c_new(ctx, len, items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_str_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    return co_str_c_free(ctx, obj);
}

/*
 * list
 */
co_object_t co_list_c_new(co_object_t ctx, co_object_t item_type, co_u64_t len, co_object_t *items) {
    co_object_t obj;
    co_list_t *list_value;
    co_object_t value;

    list_value = calloc(1, sizeof(co_list_t));
    list_value->rc = 1;
    list_value->len = len;

    // items
    list_value->items = calloc(len, sizeof(co_object_t));
    list_value->items = memmove(list_value->items, items, len * sizeof(co_object_t));

    for (co_u64_t i = 0; i < list_value->len; i++) {
        value = list_value->items[i];
        CO_INCREF(ctx, value);
    }

    // precompute hash
    list_value->hash = co_c_clistitems_hash(ctx, list_value->len, list_value->items);

    // object
    obj = (co_object_t){
        .k = CO_KIND_LIST,
        .v = {
            .p = (co_gc_t*)list_value,
        }
    };

    return obj;
}

co_object_t co_list_c_free(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_LIST);

    co_object_t value;
    co_list_t *list_value = (co_list_t*)obj.v.p;

    for (co_u64_t i = 0; i < list_value->len; i++) {
        value = list_value->items[i];
        CO_DECREF(ctx, value);
    }

    free(list_value->items);
    free(list_value);
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_len(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_LIST);

    co_list_t *list_value = (co_list_t*)obj.v.p;
    return co_i64_c_new(ctx, list_value->len);
}

co_object_t co_list_c_lt(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_LIST);
    assert(other.k == CO_KIND_LIST);

    co_object_t res;
    bool res_value = true;

    co_list_t *obj_value = (co_list_t*)obj.v.p;
    co_list_t *other_value = (co_list_t*)other.v.p;
    co_object_t obj_item;
    co_object_t other_item;
    co_object_t t;

    if (obj_value->len < other_value->len) {
        res_value = true;
        goto return_res;
    }

    if (obj_value->len > other_value->len) {
        res_value = false;
        goto return_res;
    }

    for (co_u64_t i = 0; i < obj_value->len; i++) {
        obj_item = obj_value->items[i];
        other_item = other_value->items[i];
        t = co_object_c_lt(ctx, obj_item, other_item);
        
        assert(t.k == CO_KIND_BOOL);

        if (t.v.b == false) {
            res_value = false;
            goto return_res;
        }
    }

return_res:
    res = co_bool_c_new(ctx, res_value);
    return res;
}

co_object_t co_list_c_eq(co_object_t ctx, co_object_t obj, co_object_t other) {
    assert(obj.k == CO_KIND_LIST);
    assert(other.k == CO_KIND_LIST);

    co_object_t res;
    bool res_value = true;

    co_list_t *obj_value = (co_list_t*)obj.v.p;
    co_list_t *other_value = (co_list_t*)other.v.p;
    co_object_t obj_item;
    co_object_t other_item;
    co_object_t t;

    if (obj_value->len != other_value->len) {
        res_value = false;
        goto return_res;
    }

    for (co_u64_t i = 0; i < obj_value->len; i++) {
        obj_item = obj_value->items[i];
        other_item = other_value->items[i];
        t = co_object_c_eq(ctx, obj_item, other_item);
        
        assert(t.k == CO_KIND_BOOL);

        if (t.v.b == false) {
            res_value = false;
            goto return_res;
        }
    }

return_res:
    res = co_bool_c_new(ctx, res_value);
    return res;
}

co_object_t co_list_c_hash(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_LIST);

    co_list_t *list_value = (co_list_t*)obj.v.p;
    return co_i64_c_new(ctx, list_value->hash);
}

co_object_t co_list_c_repr(co_object_t ctx, co_object_t obj) {
    assert(obj.k == CO_KIND_LIST);

    co_object_t res;
    co_list_t *list_value = (co_list_t*)obj.v.p;
    
    int size = snprintf(NULL, 0, "[list at %p of len %lld]", list_value, list_value->len);
    
    char *repr_items = calloc(size, sizeof(char));
    snprintf(repr_items, size + 1, "[list at %p of len %lld]", list_value, list_value->len);

    res = co_str_c_new(ctx, size, repr_items, CO_OWN_TRANS_MOVE);
    return res;
}

co_object_t co_list_c_get(co_object_t ctx, co_object_t obj, co_object_t index) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_set(co_object_t ctx, co_object_t obj, co_object_t index, co_object_t value) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_del(co_object_t ctx, co_object_t obj, co_object_t index) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_append(co_object_t ctx, co_object_t obj, co_object_t value) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_prepend(co_object_t ctx, co_object_t obj, co_object_t value) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_insert(co_object_t ctx, co_object_t obj, co_object_t index, co_object_t value) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_remove(co_object_t ctx, co_object_t obj, co_object_t value, co_object_t n) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_replace(co_object_t ctx, co_object_t obj, co_object_t value, co_object_t other, co_object_t n) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_c_pop(co_object_t ctx, co_object_t obj) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}

co_object_t co_list_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs) {
    // FIXME: implement
    return CO_OBJECT_UNDEFINED;
}


/*
 * c builtins
 */
co_i64_t co_c_cstr_hash(co_object_t ctx, size_t len, char *items) {
    // djb2 hashing algorithm
    co_u64_t h = 5381;
    int c;
    
    for (co_u64_t i = 0; i < len; i++) {
        c = items[i];
        h = ((h << 5) + h) + c; /* h * 33 + c */
    }

    _co_num_t num;
    num.u64 = h;
    co_i64_t hash = num.i64;
    return hash;
}

co_i64_t co_c_clistitems_hash(co_object_t ctx, size_t len, co_object_t *items) {
    co_i64_t hash = 5381;
    co_object_t value;
    co_object_t h;
    co_i64_t h_value;

    for (co_u64_t i = 0; i < len; i++) {
        value = items[i];
        h = co_object_c_hash(ctx, value);
        
        assert(h.k == CO_KIND_I64);
        
        h_value = h.v.i64;
        CO_DECREF(ctx, h);
        hash ^= h_value;
    }

    return hash;
}

co_object_t co_print_c(co_object_t ctx, co_object_t obj) {
    // repr
    co_object_t repr_obj = co_object_c_repr(ctx, obj);
    co_str_t *repr_str_value = (co_str_t*)repr_obj.v.p;
    size_t repr_len = repr_str_value->len;
    char *repr_items = repr_str_value->items;
    
    // buf_fmt
    int size = snprintf(NULL, 0, "%%%lus\n", repr_len);
    size += 1;
    char *buf_fmt = calloc(size, sizeof(char));
    snprintf(buf_fmt, size, "%%%lus\n", repr_len);

    // print
    printf(buf_fmt, repr_items);

    // cleanup
    free(buf_fmt);
    CO_DECREF(ctx, repr_obj);
    return CO_OBJECT_UNDEFINED;
}
