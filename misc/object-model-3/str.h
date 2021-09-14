#ifndef CO_STR_H
#define CO_STR_H

struct co_str_t;

#include <stdlib.h>
#include <string.h>

#include "object.h"

typedef struct co_str_t {
    CO_OBJECT_HEAD;
    char *encoding;
    size_t len;
    char *items;
} co_str_t;

#endif
