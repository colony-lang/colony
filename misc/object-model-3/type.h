#ifndef CO_TYPE_H
#define CO_TYPE_H

struct _co_type_t;
struct co_type_t;

#include <stdlib.h>

#include "object.h"

typedef struct _co_type_t {
    CO_GC_HEAD;
} _co_type_t;

typedef struct co_type_t {
    CO_OBJECT_HEAD;
    struct _co_type_t *type;
} co_type_t;

#endif
