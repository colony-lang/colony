#ifndef CO_RESULT_H
#define CO_RESULT_H

struct co_result_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_result_t {
    struct co_object_t *ok_type;
    struct co_object_t *err_type;
} co_result_t;

#endif
