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
        case CO_KIND_CTX:
            self->v.ctx->rc++;
            break;
        default:
            ;
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
        case CO_KIND_CTX:
            if (--self->v.ctx->rc == 0) co_object_free(ctx, self);
            break;
        default:
            ;
    }
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
