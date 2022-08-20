#ifndef CO_STRUCT_H
#define CO_STRUCT_H

#include "../core/ctx.h"
#include "object.h"

/* (cls: type, other: struct) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields);

/* (ctx, fields_array: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields(co_ctx_t *ctx, co_struct_field_t *fields_array);

/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self);

#endif
