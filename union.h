#ifndef CO_UNION_H
#define CO_UNION_H

struct co_union_t;

#include <stdlib.h>
#include "object.h"

typedef struct co_union_t {
    struct co_object_t *type;       // type
    struct co_object_t *name;       // str
    struct co_object_t *bases;      // list[type]
} co_union_t;

#endif
