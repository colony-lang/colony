#include "object.h"

inline void co_ref(struct co_object_t *ctx, struct co_object_t *obj) {
    if (!obj) return;
    obj->rc++;
}

inline void co_unref(struct co_object_t *ctx, struct co_object_t *obj) {
    if (!obj) return;
    obj->rc--;
    
    if (obj->rc == 0) {
        co_object_free(ctx, obj);
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
