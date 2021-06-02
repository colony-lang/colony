#ifndef CO_TYPE_H
#define CO_TYPE_H

enum co_type_kind_t;
struct co_type_t;

#include <stdlib.h>
#include "./object.h"

typedef enum co_type_kind_t {
    CO_TYPE_KIND_C,
    CO_TYPE_KIND_CO
} co_type_kind_t;

typedef union co_type_value_t {
    enum co_kind_t kind;
    struct co_object_t *type;
} co_type_value_t;

typedef struct co_type_t {
    enum co_type_kind_t kind;
    union co_type_value_t;
} co_type_t;

#endif
