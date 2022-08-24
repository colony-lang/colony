#include "struct.h"
#include "str.h"

/* (cls: type) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields) {
    co_object_t name;
    co_object_t name_check;
    co_struct_t *v;
    co_object_t self;

    // check cap
    if (!(cap >= 1)) {
        return co_ctx_panic(ctx, "struct: cap should be greater or equal to 1");
    }

    // check len
    if (!(len <= cap)) {
        return co_ctx_panic(ctx, "struct: len should be less or equal to cap");
    }

    // check fields
    if (fields == NULL) {
        return co_ctx_panic(ctx, "struct: fields cannot be NULL");
    }

    // check if the first element of fields is type
    name = fields[0].name;

    if (name.k != CO_KIND_STR) {
        return co_ctx_panic(ctx, "struct: first field's 'name' should always be of type 'str'");
    }

    name_check = co_str_eq_c(ctx, name, 8, "__type__");

    if (name_check.v.b == false) {
        return co_ctx_panic(ctx, "struct: first field's 'name' should always be '__type__'");
    }

    // create struct value
    v = malloc(sizeof(co_struct_t));
    v->rc = 1;
    v->cap = cap;
    v->len = len;
    v->fields = fields;

    // create self object
    self = co_object_new_c_ptr(ctx, CO_KIND_STRUCT, v);
    return self;
}

/* (ctx, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields_array(co_ctx_t *ctx, co_struct_field_t *fields_array) {
    co_struct_field_t field;
    size_t cap = 0;
    size_t len = 0;

    // check fields
    if (fields_array == NULL) {
        return co_ctx_panic(ctx, "struct: fields_array cannot be NULL");
    }

    // find cap and size of fields_array
    for (int i = 0;; i++) {
        field = fields_array[i];

        if (field.name.k == CO_KIND_UNDEFINED &&
            field.cls.k == CO_KIND_UNDEFINED &&
            field.value.k == CO_KIND_UNDEFINED
        ) {
            break;
        }

        cap += 1;
        len += 1;
    }

    // create new fields with found size
    co_struct_field_t *fields = calloc(len, sizeof(co_struct_field_t));

    // copy field by field
    for (int i = 0; i < len; i++) {
        field = fields_array[i];
        fields[i] = field;
    }

    // create struct value
    co_struct_t *v = malloc(sizeof(co_struct_t));
    v->rc = 1;
    v->cap = cap;
    v->len = len;
    v->fields = fields;

    // create struct object
    co_object_t self = co_object_new_c_ptr(ctx, CO_KIND_STRUCT, v);
    return self;
}

/* (cls: type) -> Undefined */
/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, cls: type) -> Undefined */
/* (ctx, self: struct) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self) {
    // free struct value
    co_struct_t *v = (co_struct_t*)self.v.ptr;
    free(v->fields);
    free(v);

    // clear object type
    self.k = CO_KIND_UNDEFINED;
    return self;
}

/* (self, cls: type, item: (attr: str, cls: type, value: object)) -> struct */
co_object_t co_struct_append(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, cls: type, attr: str, cls: type, value: object) -> struct */
co_object_t co_struct_append_c(co_ctx_t *ctx, co_object_t self, co_object_t attr, co_object_t cls, co_object_t value) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, cls: type, attr: str, cls: type, value: object) -> struct */
co_object_t co_struct_mut_append_c(co_ctx_t *ctx, co_object_t self, co_object_t attr, co_object_t cls, co_object_t value) {
    // TODO:
    return ctx->undefined;
}
