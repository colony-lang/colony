#ifndef CO_DICT_ITEM_H
#define CO_DICT_ITEM_H

#include "object_common.h"

typedef struct co_dict_item_t {
    co_object_t *key;   // any
    co_object_t *value; // any
} co_dict_item_t;

#endif
