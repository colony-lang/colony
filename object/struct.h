#ifndef CO_STRUCT_H
#define CO_STRUCT_H

#include "../core/ctx.h"
#include "object.h"

/* (cls: type) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj);

/* (cls: type, other: struct) -> struct */
co_object_t co_struct_new_from(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields);

/* (ctx, fields_array: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields_array(co_ctx_t *ctx, co_struct_field_t *fields_array);

/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj);

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self);

/* (self, item: int | str) -> object */
co_object_t co_struct_getitem(co_ctx_t *ctx, co_object_t obj);

/* (ctx, index: ssize_t) -> object */
co_object_t co_struct_getitem_c_index(co_ctx_t *ctx, ssize_t index);

/* (ctx, attr_len: size_t, attr: char*) -> object */
co_object_t co_struct_getitem_c_attr(co_ctx_t *ctx, size_t attr_len, char *attr);

/* (self, item: str, struct(cls: type, value: object)) -> struct */
co_object_t co_struct_setitem(co_ctx_t *ctx, co_object_t obj);

/* (ctx, attr_len: size_t, attr: char*, value: co_object_t) -> object */
co_object_t co_struct_setitem_c_attr(co_ctx_t *ctx, size_t attr_len, char *attr, co_object_t value);

/* (self, attr: str) -> object */
co_object_t co_struct_getattr(co_ctx_t *ctx, co_object_t obj);

/* (ctx, attr_len: size_t, attr: char*) -> object */
co_object_t co_struct_getattr_c(co_ctx_t *ctx, size_t attr_len, char *attr);

/* (self, attr: str, struct(cls: type, value: object)) -> struct */
co_object_t co_struct_setattr(co_ctx_t *ctx, co_object_t obj);

/* (ctx, attr_len: size_t, attr: char*, value: co_object_t) -> object */
co_object_t co_struct_setattr_c(co_ctx_t *ctx, size_t attr_len, char *attr, co_object_t value);

/* (self, ...args) -> cls */
co_object_t co_struct_call(co_ctx_t *ctx, co_object_t obj);

#endif
