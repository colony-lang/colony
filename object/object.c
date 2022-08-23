#include "object.h"
#include "struct.h"
#include "bytes.h"
#include "str.h"

/* (cls: type) -> cls */
struct co_object_t co_object_new(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, k: co_kind_t, v: co_value_t) -> co_object_t */
inline co_object_t co_object_new_c(co_ctx_t *ctx, co_kind_t k, co_value_t v) {
    co_object_t self = {.k = k, .v = v};
    return self;
}

/* (ctx, k: co_kind_t, ptr: void*) -> co_object_t */
inline struct co_object_t co_object_new_c_ptr(struct co_ctx_t *ctx, enum co_kind_t k, void *ptr) {
    co_value_t v = {.ptr = ptr};
    co_object_t self = {.k = k, .v = v};
    return self;
}

/* (self) -> undefined */
struct co_object_t co_object_free(struct co_ctx_t *ctx, struct co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, self: co_object_t) -> co_object_t */
struct co_object_t co_object_free_c(co_ctx_t *ctx, co_object_t self) {
    co_object_t ret = ctx->undefined;
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
            ret = gc_ptr->free_cb(ctx, self);
            
            if (ret.k != CO_KIND_UNDEFINED) {
                co_ctx_panic(ctx, "Object of type 'gc_ptr' failed to free resources");
            }

            break;
        case CO_KIND_STRUCT:
            ret = co_struct_free_c(ctx, self);
            break;
        case CO_KIND_GENERIC_STRUCT:
            break;
        case CO_KIND_PARAM_STRUCT:
            break;
        case CO_KIND_UNION:
            break;
        case CO_KIND_PARAM_UNION:
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
    assert(ret.k == CO_KIND_UNDEFINED);
    return ret;
}

/* (ctx, self: co_object_t) -> void */
inline void co_object_incref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc++;
}

/* (ctx, self: co_object_t) -> void */
inline void co_object_decref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    struct co_object_t ret = ctx->undefined;
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc--;

    if (gc->rc == 0) {
        ret = co_object_free_c(ctx, self);
        assert(ret.k == CO_KIND_UNDEFINED);
    }
}

/* (ctx, self: co_object_t) -> void */
inline void co_object_rstref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc = 1;
}

/* (ctx, self: co_object_t) -> void */
inline void co_object_clrref_c(struct co_ctx_t *ctx, struct co_object_t self) {
    if (self.k < CO_KIND_PTR) return;
    co_gc_t *gc = (co_gc_t*)self.v.ptr;
    gc->rc = 0;
}
