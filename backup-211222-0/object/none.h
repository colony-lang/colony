#ifndef CO_NONE_H
#define CO_NONE_H

struct co_none_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_none_t {
    struct co_object_t *option_type;
} co_none_t;

#endif
