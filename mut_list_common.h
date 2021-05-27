#ifndef CO_MUT_LIST_COMMON_H
#define CO_MUT_LIST_COMMON_H

#include <stdint.h>
#include "object_common.h"

typedef struct co_mut_list_t {
    size_t cap;
    size_t len;
    co_object_t *type;
    co_object_t *items;
} co_mut_list_t;

#endif
