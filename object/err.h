#ifndef CO_ERR_H
#define CO_ERR_H

struct co_err_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_err_t {
    struct co_object_t *result_type;
    struct co_object_t *e;
} co_err_t;

#endif
