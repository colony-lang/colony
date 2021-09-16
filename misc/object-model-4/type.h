#ifndef CO_TYPE_H
#define CO_TYPE_H

struct _co_type_t;
struct co_type_t;

#define CO_TYPE_HEAD \
    struct co_object_t *type; \
    struct co_object_t *name; \
    struct co_object_t *bases; \
    struct co_object_t *attrs;

#include <stdlib.h>

#include "object.h"

typedef struct _co_type_t {
    CO_GC_HEAD;
    CO_TYPE_HEAD;
} _co_type_t;

typedef struct co_type_t {
    CO_OBJECT_HEAD;
    struct _co_type_t *_type;
} co_type_t;

static co_type_t CO_TYPE_TYPE = {
    .k = CO_KIND_TYPE,
    ._type = NULL,
};

/* (cls: type, name: str, bases: list[type], attrs: dict[str, object]) -> 'Self' */
struct co_object_t *co_type_new(struct co_object_t *ctx, struct co_object_t *type, struct co_object_t *name, struct co_object_t *bases, struct co_object_t *attrs);

/* (self: 'Self') -> object */
struct co_object_t *co_type_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: type, args: list[object], kwargs: dict[str, object]) -> 'Self' */
struct co_object_t *co_type_call(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *args, struct co_object_t *kwargs);;

#endif
