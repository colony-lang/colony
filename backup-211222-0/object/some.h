#ifndef CO_SOME_H
#define CO_SOME_H

struct co_some_t;

#include <stdlib.h>
#include "./object.h"

// Some: type = struct(...)
typedef struct co_some_t {
    struct co_object_t *option_type;
    struct co_object_t *v;
} co_some_t;



#endif
