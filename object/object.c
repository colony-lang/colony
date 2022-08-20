#include "object.h"
#include "struct.h"
#include "bytes.h"
#include "str.h"

inline co_object_t co_object_new_c(co_ctx_t *ctx, co_type_t t, co_value_t v) {
    co_object_t self = {.t = t, .v = v};
    return self;
}

inline struct co_object_t co_object_new_c_ptr(struct co_ctx_t *ctx, enum co_type_t t, void *ptr) {
    co_value_t v = {.ptr = ptr};
    co_object_t self = {.t = t, .v = v};
    return self;
}

inline int co_object_free_c(co_ctx_t *ctx, co_object_t self) {
    int rc = 0;
    co_object_t ret;
    co_gc_ptr_t *gc_ptr = NULL;

    switch (self.t) {
        case CO_TYPE_UNDEFINED:
            break;
        case CO_TYPE_BOOL:
            break;
        case CO_TYPE_U8:
            break;
        case CO_TYPE_I8:
            break;
        case CO_TYPE_U16:
            break;
        case CO_TYPE_I16:
            break;
        case CO_TYPE_U32:
            break;
        case CO_TYPE_I32:
            break;
        case CO_TYPE_U64:
            break;
        case CO_TYPE_I64:
            break;
        case CO_TYPE_F32:
            break;
        case CO_TYPE_F64:
            break;
        case CO_TYPE_PTR:
            break;
        case CO_TYPE_GC_PTR:
            gc_ptr = self.v.ptr;
            rc = gc_ptr->free_cb(ctx, self);

            if (rc) {
                co_ctx_panic(ctx, "Object of type 'gc_ptr' failed to free resources");
            }

            break;
        case CO_TYPE_STRUCT:
            ret = co_struct_free_c(ctx, self);
            break;
        case CO_TYPE_STRUCT_INSTANCE:
            break;
        case CO_TYPE_GENERIC_STRUCT:
            break;
        case CO_TYPE_GENERIC_STRUCT_INSTANCE:
            break;
        case CO_TYPE_PARAM_STRUCT:
            break;
        case CO_TYPE_PARAM_STRUCT_INSTANCE:
            break;
        case CO_TYPE_UNION:
            break;
        case CO_TYPE_PARAM_UNION:
            break;
        case CO_TYPE_MODULE:
            break;
        case CO_TYPE_CODE:
            break;
        case CO_TYPE_FN:
            break;
        case CO_TYPE_FN_DECL:
            break;
        case CO_TYPE_PARAM_FN:
            break;
        case CO_TYPE_PARAM_FN_DECL:
            break;
        case CO_TYPE_BYTES:
            ret = co_bytes_free_c(ctx, self);
            break;
        case CO_TYPE_STR:
            ret = co_str_free_c(ctx, self);
            break;
        case CO_TYPE_LIST:
            break;
        case CO_TYPE_DICT:
            break;
        case CO_TYPE_RESULT:
            break;
        case CO_TYPE_OK:
            break;
        case CO_TYPE_ERR:
            break;
        case CO_TYPE_OPTION:
            break;
        case CO_TYPE_SOME:
            break;
        case CO_TYPE_NONE:
            break;
        default:
            break;
    }

    assert(self.t == CO_TYPE_UNDEFINED);
    return 0;
}
