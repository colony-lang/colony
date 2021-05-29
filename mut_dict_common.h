#ifndef CO_MUT_DICT_COMMON_H
#define CO_MUT_DICT_COMMON_H

#include <stdlib.h>
#include "mut_dict_item.h"

typedef struct co_mut_dict_t {
    size_t cap;
    size_t len;
    co_mut_dict_item_t *items;
} co_mut_dict_t;

#endif
