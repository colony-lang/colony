#include "object.h"

inline void co_ref(struct co_object_t *ctx, struct co_object_t *self) {
    if (!self) return;

    switch (self->k) {
        case CO_KIND_BOOL:
        case CO_KIND_I8:
        case CO_KIND_I16:
        case CO_KIND_I32:
        case CO_KIND_I64:
        case CO_KIND_U8:
        case CO_KIND_U16:
        case CO_KIND_U32:
        case CO_KIND_U64:
        case CO_KIND_F32:
        case CO_KIND_F64:
            return;
        default:
            self->v.gc->rc++;
    }
}

inline void co_unref(struct co_object_t *ctx, struct co_object_t *self) {
    if (!self) return;

    switch (self->k) {
        case CO_KIND_BOOL:
        case CO_KIND_I8:
        case CO_KIND_I16:
        case CO_KIND_I32:
        case CO_KIND_I64:
        case CO_KIND_U8:
        case CO_KIND_U16:
        case CO_KIND_U32:
        case CO_KIND_U64:
        case CO_KIND_F32:
        case CO_KIND_F64:
            return;
        default:
            if (--self->v.gc->rc == 0) co_object_free(ctx, self);
    }
}

inline void co_object_gc_ref(struct co_object_t *ctx, struct co_object_t *self, struct co_gc_t *gc) {
    gc->rc++;
}

inline void co_object_gc_unref(struct co_object_t *ctx, struct co_object_t *self, struct co_gc_t *gc) {
    if (--gc->rc == 0) {
        co_object_free(ctx, self);
    }
}

inline void co_object_value_ref(struct co_object_t *ctx, struct co_object_t *self, union co_value_t *v) {
    v->gc->rc++;
}

inline void co_object_value_unref(struct co_object_t *ctx, struct co_object_t *self, union co_value_t *v) {
    if (--v->gc->rc == 0) {
        co_object_free(ctx, self);
    }
}

struct co_object_t *co_object_new(struct co_object_t *ctx, enum co_kind_t k, union co_value_t v) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_ctx_t));
    self->k = k;
    self->v = v;
    self->v.ctx->rc++;
    return self;
}

struct co_object_t *co_object_free(struct co_object_t *ctx, struct co_object_t *self) {
    switch (self->k) {
        case CO_KIND_CTX:
            co_ctx_free(ctx, self);
            break;
        default:
            ;
    }

    return NULL;
}
