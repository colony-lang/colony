#ifndef CO_LIST_H
#define CO_LIST_H

struct co_list_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_list_t {
    size_t len;
    struct co_object_t *type;
    struct co_object_t *items;
} co_list_t;

// (len: u64, type: type, items: list[any]) -> list[type]
struct co_object_t *co_list_new(struct co_ctx_t *ctx, size_t len, struct co_object_t *type, struct co_object_t *items);

// (self: list) -> Result
struct co_object_t *co_list_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: list, index: any, type_: type, value: any) -> list
struct co_object_t *co_list_setitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *type_, struct co_object_t *value);

// (self: list, index: any, value: any) -> list
struct co_object_t *co_list_set(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *value);

// (self: list, index: any) -> (type, any) | Err
struct co_object_t *co_list_getitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list, index: any) -> any | Err
struct co_object_t *co_list_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list, index: any) -> (list, type, any) | Err
struct co_object_t *co_list_delitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list, index: any) -> list | Err
struct co_object_t *co_list_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list, index: any, type_: type) -> bool
struct co_object_t *co_list_hasitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *type_);

// (self: list, index: any) -> bool
struct co_object_t *co_list_has(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list, other: list) -> list
struct co_object_t *co_list_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: list, value: any) -> list
struct co_object_t *co_list_prepend(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: list, value: any) -> list
struct co_object_t *co_list_append(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: list, value: any) -> list | Err
struct co_object_t *co_list_remove(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: list, index: i64, value: any) -> list
struct co_object_t *co_list_insert(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *value);

// (self: list, index: Option[i64]=None) -> (list, any) | Err
struct co_object_t *co_list_pop(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: list) -> list[(i64, type, any)]
struct co_object_t *co_list_items(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: list) -> list[(i64, any)]
struct co_object_t *co_list_entries(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: list, begin: i64, end: i64) -> list
struct co_object_t *co_list_get_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: list, begin: i64, end: i64, other: bytes) -> list
struct co_object_t *co_list_set_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end, struct co_object_t *other);

// (self: list, begin: i64, end: i64) -> list
struct co_object_t *co_list_del_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: list, pattern: any) -> i64 | Err
struct co_object_t *co_list_find(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: list, pattern: any) -> list[i64] | Err
struct co_object_t *co_list_find_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: list, pattern: any, replacement: any) -> list | Err
struct co_object_t *co_list_replace(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: list, pattern: any, replacement: any) -> list | Err
struct co_object_t *co_list_replace_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

#endif
