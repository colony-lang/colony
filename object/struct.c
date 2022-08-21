#include "struct.h"
#include "str.h"

/* (cls: type, other: struct) -> struct */
co_object_t co_struct_new(co_ctx_t *ctx, co_object_t obj) {

}

/* (ctx, cap: size_t, len: size_t, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c(co_ctx_t *ctx, size_t cap, size_t len, co_struct_field_t *fields) {
    // create struct value
    co_struct_t *v = malloc(sizeof(co_struct_t));
    v->rc = 1;
    v->cap = cap;
    v->len = len;
    v->fields = fields;

    // create self object
    co_object_t self = co_object_new_c_ptr(ctx, CO_KIND_STRUCT, v);
    return self;
}

/* (ctx, fields: co_struct_field_t*) -> struct */
co_object_t co_struct_new_c_fields_array(co_ctx_t *ctx, co_struct_field_t *fields_array) {
    co_struct_field_t field;
    size_t cap = 0;
    size_t len = 0;

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

/* (self: struct) -> Undefined */
co_object_t co_struct_free(co_ctx_t *ctx, co_object_t obj) {

}

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_struct_free_c(co_ctx_t *ctx, co_object_t self) {
    // free struct value
    co_struct_t *v = (co_struct_t*)self.v.ptr;
    free(v->fields);
    free(v);

    // clear object type
    self.k = CO_KIND_UNDEFINED;
    return self;
}
