#ifndef CO_BYTES_H
#define CO_BYTES_H

struct _co_bytes_t;
struct co_bytes_t;

#include <stdlib.h>
#include <string.h>

#include "object.h"

typedef struct _co_bytes_t {
    enum co_own_t own;  // ownnership of items
    size_t len;
    char *items;
} _co_bytes_t;

typedef struct co_bytes_t {
    CO_OBJECT_HEAD;
    struct _co_bytes_t *bytes;
} co_bytes_t;

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

#endif
