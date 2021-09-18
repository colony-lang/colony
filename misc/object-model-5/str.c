#include "str.h"

/*
struct co_object_t *co_str_c_new(struct co_object_t *ctx, size_t len, char *items, enum co_own_t own, char *encoding) {
    co_object_t *self = (co_object_t*)malloc(sizeof(co_object_t));
    self->k = CO_KIND_STR;
    self->v.str = (_co_str_t*)malloc(sizeof(_co_str_t));
    self->v.str->rc = 1;
    self->v.str->len = len;

    switch (own) {
        case CO_OWN_NONE:
            self->v.str->items = items;
            break;
        case CO_OWN_FULL:
            memcpy(self->v.str->items, items, len);
            break;
    }

    self->v.str->own = own;

    if (encoding) {
        self->v.str->encoding = encoding;
    } else {
        self->v.str->encoding = "ascii";
    }

    return self;
}

struct co_object_t *co_str_new(struct co_object_t *ctx, struct co_object_t *other) {
    // FIXME: depends on Result[str, str]
    return NULL;
}

struct co_object_t *co_str_free(struct co_object_t *ctx, struct co_object_t *self) {
    switch (self->v.str->own) {
        case CO_OWN_NONE:
            break;
        case CO_OWN_FULL:
            free(self->v.str->items);
            break;
    }

    free(self->v.str);
    free(self);
    return NULL;
}

struct co_object_t *co_str_encode(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *encoding) {
    // FIXME: implement me
    return NULL;
}

struct co_object_t *co_str_add(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *other) {
    // co_object_t *res = (co_object_t*)malloc(sizeof(co_object_t));
    // res->k = CO_KIND_STR;
    // res->v.str = (_co_str_t*)malloc(sizeof(_co_str_t));
    // res->v.str->rc = 1;
    // res->v.str->len = self->v.str->;

    // memcpy(res->v.str->items, items, len);
    // res->v.str->own = CO_OWN_FULL;

    // res->v.str->encoding = encoding;
    // return res;

    // FIXME: implement me
    return NULL;
}
*/
