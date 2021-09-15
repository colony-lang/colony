#include "str.h"

struct co_object_t *_co_str_new(struct co_object_t *ctx, char *encoding, size_t len, char *items) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_object_t));
    self->k = CO_KIND_STR;
    self->v.str = (_co_str_t*)malloc(sizeof(_co_str_t));
    self->v.str->rc = 1;
    self->v.str->encoding = encoding;
    self->v.str->len = len;
    self->v.str->items = items;
    return self;
}

struct co_object_t *_co_str_new_with_value(struct co_object_t *ctx, union co_value_t v) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_object_t));
    self->k = CO_KIND_STR;
    self->v = v;
    self->v.str->rc++;
    return self;
}

struct co_object_t *co_str_new(struct co_object_t *ctx, struct co_object_t *other) {
    // FIXME: depends on Result[str, str]
    return NULL;
}

struct co_object_t *co_str_free(struct co_object_t *ctx, struct co_object_t *self) {
    free(self->v.str);
    free(self);
    return NULL;
}
