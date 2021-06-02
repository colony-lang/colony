#ifndef CO_OK_H
#define CO_OK_H

struct co_ok_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_ok_t {
    struct co_object_t *result_type;
    struct co_object_t *v;
} co_ok_t;

#endif
