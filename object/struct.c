#include "struct.h"
#include "str.h"

/* (cls: type, other: struct) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj) {

}

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields) {
    // struct value
    co_struct_t *v = malloc(sizeof(co_struct_t));
    v->rc = 1;
    v->cap = cap;
    v->len = len;
    v->fields = fields;

    // self object
    co_object_t self = co_object_new_c_ptr(ctx, CO_TYPE_STRUCT, v);
    return self;
}

/* (ctx, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields(co_ctx_t *ctx, co_struct_field_t *fields_array) {
    co_struct_field_t field;
    size_t cap = 0;
    size_t len = 0;

    for (int i = 0;; i++) {
        field = fields_array[i];

        if (field.name.t == CO_TYPE_UNDEFINED &&
            field.type.t == CO_TYPE_UNDEFINED &&
            field.default_value.t == CO_TYPE_UNDEFINED
        ) {
            break;
        }

        cap += 1;
        len += 1;
    }

    co_struct_field_t *fields = calloc(len, sizeof(co_struct_field_t));

    for (int i = 0; i < len; i++) {
        field = fields_array[i];
        fields[i] = field;
    }

    co_struct_t *v = malloc(sizeof(co_struct_t));
    v->rc = 1;
    v->cap = cap;
    v->len = len;
    v->fields = fields;

    co_object_t self = co_object_new_c_ptr(ctx, CO_TYPE_STRUCT, v);
    return self;
}

/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj) {

}

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self) {

}
