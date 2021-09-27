#ifndef CO_RESULT_H
#define CO_RESULT_H

struct _co_ok_type_t;
struct co_ok_type_t;
struct _co_ok_t;
struct co_ok_t;
struct _co_err_type_t;
struct co_err_type_t;
struct _co_err_t;
struct co_err_t;
struct _co_result_type_t;
struct co_result_type_t;

#include <stdlib.h>

#include "object.h"

/*
 * Ok[V]
 */
typedef struct _co_ok_type_t {
    CO_GC_HEAD;
    struct co_object_t *V;
} _co_ok_type_t;

typedef struct co_ok_type_t {
    CO_OBJECT_HEAD;
    struct _co_ok_type_t *ok_type;
} co_ok_type_t;

/*
 * ok = Ok[V](v)
 */
typedef struct _co_ok_t {
    CO_GC_HEAD;
    struct co_object_t *v;
} _co_ok_t;

typedef struct co_ok_t {
    CO_OBJECT_HEAD;
    struct _co_ok_t *ok;
} co_ok_t;

/*
 * Err[E]
 */
typedef struct _co_err_type_t {
    CO_GC_HEAD;
    struct co_object_t *E;
} _co_err_type_t;

typedef struct co_err_type_t {
    CO_OBJECT_HEAD;
    struct co_err_type_t *err_type;
} co_err_type_t;

/*
 * err = Err[E](e)
 */
typedef struct _co_err_t {
    CO_GC_HEAD;
    struct co_object_t *e;
} _co_err_t;

typedef struct co_err_t {
    CO_OBJECT_HEAD;
    struct _co_err_t *err;
} co_err_t;

/*
 * Result[V, E]
 * Result := Ok[V] | Err[E]
 */
typedef struct _co_result_type_t {
    CO_GC_HEAD;
    struct co_object_t *ok_type;
    struct co_object_t *err_type;
} _co_result_type_t;

typedef struct co_result_type_t {
    CO_OBJECT_HEAD;
    struct _co_result_type_t *result_type;
} co_result_type_t;

#endif
