#ifndef CO_MUT_LIST_H
#define CO_MUT_LIST_H

struct co_mut_list_t;

#include <stdlib.h>
#include "./object.h"

typedef struct co_mut_list_t {
    size_t cap;
    size_t len;
    struct co_object_t *type;
    struct co_object_t *items;
} co_mut_list_t;

// (cap: u64, len: u64, type: type, items: mut_list[any]) -> mut_list[type]
struct co_object_t *co_mut_list_new(struct co_ctx_t *ctx, size_t cap, size_t len, struct co_object_t *type, struct co_object_t *items);

// (self: mut_list) -> Result
struct co_object_t *co_mut_list_free(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: mut_list, index: any, type_: type, value: any) -> mut_list
struct co_object_t *co_mut_list_setitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *type_, struct co_object_t *value);

// (self: mut_list, index: any, value: any) -> mut_list
struct co_object_t *co_mut_list_set(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *value);

// (self: mut_list, index: any) -> (type, any) | Err
struct co_object_t *co_mut_list_getitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list, index: any) -> any | Err
struct co_object_t *co_mut_list_get(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list, index: any) -> (mut_list, type, any) | Err
struct co_object_t *co_mut_list_delitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list, index: any) -> mut_list | Err
struct co_object_t *co_mut_list_del(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list, index: any, type_: type) -> bool
struct co_object_t *co_mut_list_hasitem(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *type_);

// (self: mut_list, index: any) -> bool
struct co_object_t *co_mut_list_has(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list, other: mut_list) -> mut_list
struct co_object_t *co_mut_list_add(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *other);

// (self: mut_list, value: any) -> mut_list
struct co_object_t *co_mut_list_prepend(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: mut_list, value: any) -> mut_list
struct co_object_t *co_mut_list_append(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: mut_list, value: any) -> mut_list | Err
struct co_object_t *co_mut_list_remove(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *value);

// (self: mut_list, index: i64, value: any) -> mut_list
struct co_object_t *co_mut_list_insert(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index, struct co_object_t *value);

// (self: mut_list, index: Option[i64]=None) -> (mut_list, any) | Err
struct co_object_t *co_mut_list_pop(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *index);

// (self: mut_list) -> mut_list[(i64, type, any)]
struct co_object_t *co_mut_list_items(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: mut_list) -> mut_list[(i64, any)]
struct co_object_t *co_mut_list_entries(struct co_ctx_t *ctx, struct co_object_t *self);

// (self: mut_list, begin: i64, end: i64) -> mut_list
struct co_object_t *co_mut_list_get_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: mut_list, begin: i64, end: i64, other: bytes) -> mut_list
struct co_object_t *co_list_set_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end, struct co_object_t *other);

// (self: mut_list, begin: i64, end: i64) -> mut_list
struct co_object_t *co_mut_list_del_slice(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *begin, struct co_object_t *end);

// (self: mut_list, pattern: any) -> i64 | Err
struct co_object_t *co_mut_list_find(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: mut_list, pattern: any) -> mut_list[i64] | Err
struct co_object_t *co_mut_list_find_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern);

// (self: mut_list, pattern: any, replacement: any) -> mut_list | Err
struct co_object_t *co_mut_list_replace(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

// (self: mut_list, pattern: any, replacement: any) -> mut_list | Err
struct co_object_t *co_mut_list_replace_all(struct co_ctx_t *ctx, struct co_object_t *self, struct co_object_t *pattern, struct co_object_t *replacement);

#endif
