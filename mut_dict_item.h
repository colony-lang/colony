#ifndef CO_MUT_DICT_ITEM_H
#define CO_MUT_DICT_ITEM_H

struct co_mut_dict_item_t;

#include "object.h"

typedef struct co_mut_dict_item_t {
    struct co_object_t *key;   // any
    struct co_object_t *value; // any
} co_mut_dict_item_t;

#endif
