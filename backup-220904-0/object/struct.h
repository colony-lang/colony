#ifndef CO_STRUCT_H
#define CO_STRUCT_H

#include "../core/ctx.h"
#include "object.h"

/* (cls: type, attrs: list<struct(attr: str, cls: type, value: object)>) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields);

/* (ctx, fields_array: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields_array(co_ctx_t *ctx, co_struct_field_t *fields_array);

/* (cls: type) -> Undefined */
/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls: type) -> Undefined */
/* (ctx, self: struct) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self);

/* (self, cls: type, item: (attr: str, cls: type, value: object)) -> struct */
co_object_t co_struct_append(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls: type, attr: str, cls: type, value: object) -> struct */
co_object_t co_struct_append_c(co_ctx_t *ctx, co_object_t self, co_object_t attr, co_object_t cls, co_object_t value);

/* (ctx, cls: type, attr: str, cls: type, value: object) -> struct */
co_object_t co_struct_mut_append_c(co_ctx_t *ctx, co_object_t self, co_object_t attr, co_object_t cls, co_object_t value);

/* (cls, item: int | str) -> object */
/* (self, item: int | str) -> object */
co_object_t co_struct_getitem(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls, index: ssize_t) -> object */
/* (ctx, self, index: ssize_t) -> object */
co_object_t co_struct_getitem_c_index(co_ctx_t *ctx, co_object_t self, ssize_t index);

/* (ctx, cls, attr_len: size_t, attr: char*) -> object */
/* (ctx, self, attr_len: size_t, attr: char*) -> object */
co_object_t co_struct_getitem_c_attr(co_ctx_t *ctx, co_object_t self, size_t attr_len, char *attr);

/* (cls, item: int | str, value: object) -> struct */
/* (self, item: int | str, value: object) -> object */
co_object_t co_struct_setitem(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls, attr_len: size_t, attr: char*, value: co_object_t) -> struct */
/* (ctx, self, attr_len: size_t, attr: char*, value: co_object_t) -> object */
co_object_t co_struct_setitem_c_attr(co_ctx_t *ctx, co_object_t self, size_t attr_len, char *attr, co_object_t value);

/* (cls, attr: str) -> object */
/* (self, attr: str) -> object */
co_object_t co_struct_getattr(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls, attr_len: size_t, attr: char*) -> object */
/* (ctx, self, attr_len: size_t, attr: char*) -> object */
co_object_t co_struct_getattr_c(co_ctx_t *ctx, co_object_t self, size_t attr_len, char *attr);

/* (self, cls, attr: str, struct(cls: type, value: object)) -> struct */
/* (self, self, attr: str, struct(cls: type, value: object)) -> object */
co_object_t co_struct_setattr(co_ctx_t *ctx, co_object_t obj);

/* (ctx, cls, attr_len: size_t, attr: char*, value: co_object_t) -> struct */
/* (ctx, self, attr_len: size_t, attr: char*, value: co_object_t) -> object */
co_object_t co_struct_setattr_c(co_ctx_t *ctx, co_object_t self, size_t attr_len, char *attr, co_object_t value);

/* (cls, args, kwargs) -> object */
co_object_t co_struct_call(co_ctx_t *ctx, co_object_t obj);

#endif
