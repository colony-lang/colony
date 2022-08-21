#include "bytes.h"
#include "struct.h"

/* (cls: type, other: bytes) -> bytes */
co_object_t co_bytes_new(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    co_struct_field_t fields_array[] = {
        // {{.t = CO_KIND_STR, .v = {.str = }}},
        // CO_STRUCT_FIELDS_DEF("cls", "type", ctx->undefined),
        // CO_STRUCT_FIELDS_DEF("other", "struct", ctx->undefined),
        CO_STRUCT_FIELDS_END
    };

    co_object_t struct_type_bytes = co_struct_new_c_fields_array(ctx, fields_array);

    // TODO:
    return ctx->undefined;
}

/* (ctx, len: size_t, items: char*) -> bytes */
co_object_t co_bytes_new_c(co_ctx_t *ctx, size_t len, char *items) {
    // create bytes value
    co_bytes_t *v = malloc(sizeof(co_bytes_t));
    v->rc = 1;
    v->len = len;
    v->items = items;

    // create self object
    co_object_t self = co_object_new_c_ptr(ctx, CO_KIND_BYTES, v);
    return self;
}

/* (self: bytes) -> Undefined */
co_object_t co_bytes_free(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, v: co_bytes_t*) -> Undefined */
co_object_t co_bytes_free_c(co_ctx_t *ctx, co_object_t self) {
    // free bytes value
    co_bytes_t *v = (co_bytes_t*)self.v.ptr;
    free(v->items);
    free(v);

    // clear object type
    self.k = CO_KIND_UNDEFINED;
    return self;
}

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_lt(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, other: bytes) -> bool */
co_object_t co_bytes_eq(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, self: bytes, len: size_t, items: char*) -> bool */
co_object_t co_bytes_eq_c(co_ctx_t *ctx, co_object_t self, size_t len, char *items) {
    co_bytes_t *v = (co_bytes_t*)self.v.ptr;
    co_object_t res;

    if (v->len != len) {
        res = (co_object_t){
            .k = CO_KIND_BOOL,
            .v = {
                .b = false
            }
        };

        return res;
    }

    if (strncmp(v->items, items, len) != 0) {
        res = (co_object_t){
            .k = CO_KIND_BOOL,
            .v = {
                .b = false
            }
        };

        return res;
    }

    res = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = true
        }
    };

    return res;
}

/* (self: bytes) -> u64 */
co_object_t co_bytes_hash(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes) -> u64 */
co_object_t co_bytes_len(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, other: bytes) -> bytes */
co_object_t co_bytes_add(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, other: bytes) -> list<bytes> */
co_object_t co_bytes_split(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, from: u64, to: u64) -> bytes */
co_object_t co_bytes_get_slice(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, from: u64, to: u64, other: bytes) -> bytes */
co_object_t co_bytes_set_slice(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, index: u64) -> bytes */
co_object_t co_bytes_get_item(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes, index: u64, value: bytes) -> bytes */
co_object_t co_bytes_set_item(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: bytes) -> str */
co_object_t co_bytes_decode(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}
