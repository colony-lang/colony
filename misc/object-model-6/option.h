#ifndef CO_OPTION_H
#define CO_OPTION_H

struct _co_some_type_t;
struct co_some_type_t;
struct _co_some_t;
struct co_some_t;
struct co_none_t;
struct _co_option_type_t;
struct co_option_type_t;

#include <stdlib.h>

#include "option.h"

/*
 * Some[V]
 */
typedef struct _co_some_type_t {
    CO_GC_HEAD;
    struct co_object_t *V;
} _co_some_type_t;

typedef struct co_some_type_t {
    CO_OBJECT_HEAD;
    struct _co_some_type_t *some_type;
} co_some_type_t;

/*
 * o = Some[V](v)
 */
typedef struct _co_some_t {
    CO_GC_HEAD;
    struct co_object_t *v;
} _co_some_t;

typedef struct co_some_t {
    CO_OBJECT_HEAD;
    struct _co_some_t *some;
} co_some_t;

/*
 * n = None
 */
typedef struct co_none_t {
    CO_OBJECT_HEAD;
} co_name_t;

/*
 * Option[V]
 * Option := Some[V] | None
 */
typedef struct _co_option_type_t {
    CO_GC_HEAD;
    struct co_object_t *some_type;
} _co_option_type_t;

typedef struct co_option_type_t {
    CO_OBJECT_HEAD;
    struct _co_option_type_t *option_type;
} co_option_type_t;

#endif

