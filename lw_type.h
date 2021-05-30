#ifndef CO_LW_TYPE_H
#define CO_LW_TYPE_H

struct co_lw_type_item_t;
struct co_lw_type_t;

#include <stdlib.h>
#include "ctx.h"
#include "object.h"

typedef struct co_lw_type_item_t {
    co_object_t *attr;
    co_object_t *type;
    co_object_t *value;
} co_lw_type_item_t;

typedef struct co_lw_type_t {
    co_lw_type_item_t *items;
} co_lw_type_t;

#endif