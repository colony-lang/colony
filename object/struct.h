#ifndef CO_STRUCT_H
#define CO_STRUCT_H

struct co_struct_t;
struct co_struct_item_t;

#include <stdlib.h>
#include "object.h"

typedef struct co_struct_item_t {
    struct co_object_t *attr;       // int | str
    struct co_object_t *type;       // type
    struct co_object_t *value;      // any
} co_struct_item_t;

typedef struct co_struct_t {
    struct co_object_t *type;       // type
    struct co_object_t *name;       // str
    struct co_object_t *bases;      // list[type]
    struct co_object_t *methods;    // dict[str, fn]
    struct co_struct_item_t *items; // items definitions
} co_struct_t;

#endif
