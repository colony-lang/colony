#ifndef CO_STR_H
#define CO_STR_H

struct _co_str_t;
struct co_str_t;

#include <stdlib.h>
#include <string.h>

#include "object.h"

typedef struct _co_str_t {
    CO_GC_HEAD;
    // FIXME: ownership
    char *encoding;
    size_t len;
    char *items;
} _co_str_t;

typedef struct co_str_t {
    CO_OBJECT_HEAD;
    struct _co_str_t *str;
} co_str_t;

struct co_object_t *_co_str_new(struct co_object_t *ctx, char *encoding, size_t len, char *items);
struct co_object_t *_co_str_new_with_value(struct co_object_t *ctx, union co_value_t v);
struct co_object_t *co_str_new(struct co_object_t *ctx, struct co_object_t *other);
struct co_object_t *co_str_free(struct co_object_t *ctx, struct co_object_t *self);

#endif
