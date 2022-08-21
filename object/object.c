#include "object.h"
#include "struct.h"
#include "bytes.h"
#include "str.h"

inline co_object_t co_object_new_c(co_ctx_t *ctx, co_kind_t k, co_value_t v) {
    co_object_t self = {.k = k, .v = v};
    return self;
}

inline struct co_object_t co_object_new_c_ptr(struct co_ctx_t *ctx, enum co_kind_t k, void *ptr) {
    co_value_t v = {.ptr = ptr};
    co_object_t self = {.k = k, .v = v};
    return self;
}

inline int co_object_free_c(co_ctx_t *ctx, co_object_t self) {
    int rc = 0;
    co_object_t ret;
    co_gc_ptr_t *gc_ptr = NULL;

    switch (self.k) {
        case CO_KIND_UNDEFINED:
            break;
        case CO_KIND_BOOL:
            break;
        case CO_KIND_U8:
            break;
        case CO_KIND_I8:
            break;
        case CO_KIND_U16:
            break;
        case CO_KIND_I16:
            break;
        case CO_KIND_U32:
            break;
        case CO_KIND_I32:
            break;
        case CO_KIND_U64:
            break;
        case CO_KIND_I64:
            break;
        case CO_KIND_F32:
            break;
        case CO_KIND_F64:
            break;
        case CO_KIND_PTR:
            break;
        case CO_KIND_GC_PTR:
            gc_ptr = self.v.ptr;
            rc = gc_ptr->free_cb(ctx, self);

            if (rc) {
                co_ctx_panic(ctx, "Object of type 'gc_ptr' failed to free resources");
            }

            break;
        case CO_KIND_STRUCT:
            ret = co_struct_free_c(ctx, self);
            break;
        case CO_KIND_STRUCT_INSTANCE:
            break;
        case CO_KIND_GENERIC_STRUCT:
            break;
        case CO_KIND_GENERIC_STRUCT_INSTANCE:
            break;
        case CO_KIND_PARAM_STRUCT:
            break;
        case CO_KIND_PARAM_STRUCT_INSTANCE:
            break;
        case CO_KIND_UNION:
            break;
        case CO_KIND_PARAM_UNION:
            break;
        case CO_KIND_MODULE:
            break;
        case CO_KIND_CODE:
            break;
        case CO_KIND_FN:
            break;
        case CO_KIND_FN_DECL:
            break;
        case CO_KIND_PARAM_FN:
            break;
        case CO_KIND_PARAM_FN_DECL:
            break;
        case CO_KIND_BYTES:
            ret = co_bytes_free_c(ctx, self);
            break;
        case CO_KIND_STR:
            ret = co_str_free_c(ctx, self);
            break;
        case CO_KIND_LIST:
            break;
        case CO_KIND_DICT:
            break;
        case CO_KIND_RESULT:
            break;
        case CO_KIND_OK:
            break;
        case CO_KIND_ERR:
            break;
        case CO_KIND_OPTION:
            break;
        case CO_KIND_SOME:
            break;
        case CO_KIND_NONE:
            break;
        default:
            break;
    }

    assert(self.k == CO_KIND_UNDEFINED);
    return 0;
}

inline void co_object_incref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc++;
}

inline void co_object_decref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc--;

    if (gc->rc == 0) {
        co_object_free_c(ctx, self);
    }
}

inline void co_object_rstref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc = 1;
}

inline void co_object_clrref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc = 0;
}
