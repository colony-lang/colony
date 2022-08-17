#include "object.h"

inline struct co_object_t co_object_new_c(struct co_ctx_t *ctx, enum co_type_t t, union co_value_t v) {
    co_object_t self = {.v = v, .t = t};
    return self;
}

inline int co_object_free_c(struct co_ctx_t *ctx, struct co_object_t self) {
    // TODO:
    return 0;
}