#include "object.h"

/*inline void co_ref(struct co_ctx_t *ctx, struct co_object_t *obj) {
    obj->rc++;
}

inline void co_unref(struct co_ctx_t *ctx, struct co_object_t *obj) {
    obj->rc--;
    
    if (obj->rc == 0) {
        co_object_free(ctx, obj);
    }
}

struct co_object_t *co_object_new(struct co_object_t *ctx, enum co_kind_t k, union co_value_t v) {
    co_object_t *self = malloc(sizeof(co_object_t));
    self->rc = 1;
    self->k = k;
    self->v = v;
    return self;
}

struct co_object_t *co_object_free(struct co_ctx_t *ctx, struct co_object_t *self) {
    switch (self->k) {
        case CO_KIND_CTX:
            co_ctx_free(ctx, self);
            break;
        case CO_KIND_STR:
            ;
        default:
            ;
    }

    free(self);
    return NULL;
}
*/