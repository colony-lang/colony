#ifndef CO_TYPE_H
#define CO_TYPE_H

struct _co_type_t;
struct co_type_t;

#include <stdlib.h>

#include "object.h"

typedef struct _co_type_t {
    CO_GC_HEAD;
    struct co_object_t *type;
    struct co_object_t *name;
    struct co_object_t *bases;
    struct co_object_t *attrs;
} _co_type_t;

typedef struct co_type_t {
    CO_OBJECT_HEAD;
    struct _co_type_t *type;
} co_type_t;

struct co_object_t *co_type_new(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *type, struct co_object_t *name, struct co_object_t *bases, struct co_object_t *attrs) /* type */;
struct co_object_t *co_type_free(struct co_object_t *ctx, struct co_object_t *self);
struct co_object_t *co_type_call(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *args, struct co_object_t *kwargs); /* instance of type */;

#endif
