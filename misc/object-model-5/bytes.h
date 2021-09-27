#ifndef CO_BYTES_H
#define CO_BYTES_H

struct _co_bytes_t;
struct co_bytes_t;

#include <stdlib.h>
#include <string.h>

#include "object.h"

typedef struct _co_bytes_t {
    CO_GC_HEAD;
    enum co_own_t own;  // ownnership of items
    size_t len;
    char *items;
} _co_bytes_t;

typedef struct co_bytes_t {
    CO_OBJECT_HEAD;
    struct _co_bytes_t *bytes;
} co_bytes_t;

/* (...) -> bytes */
struct co_object_t *co_bytes_alloc(struct co_object_t *ctx, enum co_own_t own, size_t len, char *items);

/* (cls: type, other: Option[object]=None) -> bytes */
struct co_object_t *co_bytes_new(struct co_object_t *ctx, struct co_object_t *cls, struct co_object_t *other);

/* (self: bytes) -> None */
struct co_object_t *co_bytes_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: bytes) -> str */
struct co_object_t *co_bytes_decode(struct co_object_t *ctx, struct co_object_t *self);

/* (self: bytes, other: bytes) -> bytes */
struct co_object_t *co_bytes_add(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *other);

/*
static struct co_type_t co_type_type;
static struct co_type_t co_bytes_type;

void _co_type_static_init(void) {
    // type
    co_type_type = (struct co_type_t){
        .k = CO_KIND_TYPE,
        ._type = &(struct _co_type_t){
            .rc = 1,
            .type = NULL,
            .name = NULL,
            .bases = NULL,
            .attrs = NULL,
        },
    };

    co_type_type._type->type = (struct co_object_t*)&co_type_type;

    // bytes
    co_bytes_type = (struct co_type_t){
        .k = CO_KIND_TYPE,
        ._type = &(struct _co_type_t){
            .rc = 1,
            .type = (struct co_object_t*)&co_type_type,
            .name = NULL,
            .bases = NULL,
            .attrs = NULL,
        },
    };
};
*/

#endif
