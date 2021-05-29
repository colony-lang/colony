#ifndef CO_MUT_DICT_ITEM_H
#define CO_MUT_DICT_ITEM_H

#include "object_common.h"

typedef struct co_mut_dict_item_t {
    co_object_t *key;   // any
    co_object_t *value; // any
} co_mut_dict_item_t;

#endif
