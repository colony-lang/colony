#ifndef CO_DICT_COMMON_H
#define CO_DICT_COMMON_H

#include <stdlib.h>
#include "dict_item.h"

typedef struct co_dict_t {
    size_t len;
    co_object_t *key_type;
    co_object_t *value_type;
    co_dict_item_t *items;
} co_dict_t;

#endif
