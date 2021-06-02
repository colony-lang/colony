#ifndef CO_OPTION_H
#define CO_OPTION_H

struct co_option_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_option_t {
    struct co_object_t *some_type;
    struct co_object_t *none_type;
} co_option_t;

#endif
