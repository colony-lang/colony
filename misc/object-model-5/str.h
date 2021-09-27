#ifndef CO_STR_H
#define CO_STR_H

struct _co_str_t;
struct co_str_t;

#include <stdlib.h>
#include <string.h>

#include "object.h"

typedef struct _co_str_t {
    CO_GC_HEAD;
    enum co_own_t own;  // ownnership of items
    size_t len;         // len of items
    char *items;        // items
    char *encoding;     // encoding of items
} _co_str_t;

typedef struct co_str_t {
    CO_OBJECT_HEAD;
    struct _co_str_t *str;
} co_str_t;

/* (...) -> str */
struct co_object_t *co_str_alloc(struct co_object_t *ctx, enum co_own_t own, size_t len, char *items, char *encoding);

/* (cls: type, other: Option[object]=None) -> str */
struct co_object_t *co_str_new(struct co_object_t *ctx, struct co_object_t *cls, struct co_object_t *other);

/* (self: str) -> None */
struct co_object_t *co_str_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: str) -> bytes */
struct co_object_t *co_str_encode(struct co_object_t *ctx, struct co_object_t *self);

/* (self: str, other: str) -> str */
struct co_object_t *co_str_add(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *other);

#endif
