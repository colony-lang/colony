#include "bytes.h"

#define CO_STRUCT_FIELDS_END (co_struct_field_t){ \
    .name = {.t = CO_TYPE_UNDEFINED, .v = (co_value_t){.ptr = NULL}}, \
    .type = {.t = CO_TYPE_UNDEFINED, .v = (co_value_t){.ptr = NULL}}, \
    .default_value = {.t = CO_TYPE_UNDEFINED, .v = (co_value_t){.ptr = NULL}} \
}

/* (cls: type, other: bytes) -> bytes */
co_object_t co_bytes_new(co_ctx_t *ctx, co_object_t obj) {
    co_struct_new_c_fields fields_array[] = {
        CO_STRUCT_FIELDS_END
    };

    co_object_t struct_type_bytes = co_struct_new_c_fields(ctx, fields_array);
}

/* (ctx, len: size_t, items: char*) -> bytes */
co_object_t co_bytes_new_c(co_ctx_t *ctx, size_t len, char *items) {
    // bytes value
    co_bytes_t *v = malloc(sizeof(co_bytes_t));
    v->rc = 1;
    v->len = len;
    v->items = items;

    // self object
    co_object_t self = co_object_new_c_ptr(ctx, CO_TYPE_BYTES, v);
    return self;
}

/* (self: bytes) -> Undefined */
co_object_t co_bytes_free(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_lt(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_eq(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes) -> u64 */
co_object_t co_bytes_hash(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes) -> u64 */
co_object_t co_bytes_len(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, other: bytes) -> bytes */
co_object_t co_bytes_add(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, other: bytes) -> list<bytes> */
co_object_t co_bytes_split(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, from: u64, to: u64) -> bytes */
co_object_t co_bytes_get_slice(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, from: u64, to: u64, other: bytes) -> bytes */
co_object_t co_bytes_set_slice(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, index: u64) -> bytes */
co_object_t co_bytes_get_item(co_ctx_t *ctx, co_object_t obj) {

}

/* (self: bytes, index: u64, value: bytes) -> bytes */
co_object_t co_bytes_set_item(co_ctx_t *ctx, co_object_t obj) {

}
